//
// Created by fusionbolt on 2020/2/10.
//

#include <iostream>
#include <thread>

#include "Player.h"
#include "utils/Util.hpp"

//TODO:错误处理
GWUI::Player::Player(const std::string& path):
// AVCodec
_formatContext(nullptr, avformat_close_input),
_swsContext(nullptr, sws_freeContext),
_videoCodecContext(nullptr, avcodec_close),
_audioCodecContext(nullptr, avcodec_close),
_frame(nullptr) // TODO:free
{
    AVFormatContext *ptr = nullptr;
    if (avformat_open_input(&ptr, path.c_str(), nullptr, nullptr))
    {
        std::cout << "Open Failed" << std::endl;
    }
    _formatContext.reset(ptr, [](AVFormatContext* f){avformat_close_input(&f);});

    if (avformat_find_stream_info(_formatContext.get(), nullptr) < 0)
    {
        std::cout << "Find StreamInfo Failed" << std::endl;
    }

    if(pthread_mutex_init(&_mutex, nullptr) != 0)
    {
        // error
    }

    for (auto i = 0; i < _formatContext->nb_streams; ++i)
    {
        auto codecType = _formatContext->streams[i]->codecpar->codec_type;
        // if (codecType == AVMEDIA_TYPE_SUBTITLE)
        if (codecType == AVMEDIA_TYPE_VIDEO)
        {
            _videoStream.reset(_formatContext->streams[i]);
            _videoStreamIndex = i;
        }
        else if (codecType == AVMEDIA_TYPE_AUDIO)
        {
            _audioStream.reset(_formatContext->streams[i]);
            _audioStreamIndex = i;
        }
    }
    if (_videoStreamIndex == -1)
    {
        std::cout << "Find Video Stream Failed" << std::endl;
    }
    if (_audioStreamIndex == -1)
    {
        std::cout << "Find Video Stream Failed" << std::endl;
    }


    if(OpenCodec(_videoStream, _videoCodecContext) != 0)
    {
        std::cout << "Open Video Codec Failed" << std::endl;
    }

    _swsContext.reset(sws_getContext(
                    _videoCodecContext->width,
                    _videoCodecContext->height,
                    _videoCodecContext->pix_fmt,
                    _videoCodecContext->width,
                    _videoCodecContext->height,
                    AV_PIX_FMT_RGB24,
                    SWS_BILINEAR,
                    nullptr,
                    nullptr,
                    nullptr
            ), sws_freeContext);




    if(OpenCodec(_audioStream, _audioCodecContext) != 0)
    {
        std::cout << "Open Audio Codec Failed" << std::endl;
    }

    SDL_AudioSpec wanted_specs;
    SDL_AudioSpec specs;

    wanted_specs.freq = _audioCodecContext->sample_rate;
    wanted_specs.format = AUDIO_S16SYS; //!!!应该是AUDIO开头的变量，而不是AV开头的变量
    wanted_specs.channels = _audioCodecContext->channels;
    wanted_specs.silence = 0;
    wanted_specs.samples = AUDIO_SAMPLE_BUFFER_SIZE; //frame buffer size
    wanted_specs.callback = nullptr;
    wanted_specs.userdata = nullptr;


    _deviceID = SDL_OpenAudioDevice(
            NULL,
            0,
            &wanted_specs,
            &specs,
            SDL_AUDIO_ALLOW_FORMAT_CHANGE);

    if (_deviceID == 0)
    {
        printf("failed to open audio device: %s\n", SDL_GetError());
    }

    SDL_PauseAudioDevice(_deviceID, 0);

    _swr.reset(swr_alloc_set_opts(
            nullptr,
            _audioCodecContext->channel_layout,
            AV_SAMPLE_FMT_S16,
            _audioCodecContext->sample_rate,
            _audioCodecContext->channel_layout,
            _audioCodecContext->sample_fmt,
            _audioCodecContext->sample_rate,
            0,
            nullptr
            ), [](SwrContext *p){swr_free(&p);});
    swr_init(_swr.get());


    new std::thread(std::bind(&Player::readPacketThread, this));
    new std::thread(std::bind(&Player::audioThread, this));
    new std::thread(std::bind(&Player::videoPrepare, this));
    // TODO:this 生命周期结束？？
    // 更多关于绑定成员函数
}

void GWUI::Player::Draw(GWUI::Renderer renderer)
{
    pthread_mutex_lock(&_mutex);
    if(_frame == nullptr)
    {
        pthread_mutex_unlock(&_mutex);
        std::cout << "frame nullptr" << std::endl;
        return;
    }
    SDL_UpdateYUVTexture(
            _texture.get(),
            nullptr,
            _frame->data[0],
            _frame->linesize[0],
            _frame->data[1],
            _frame->linesize[1],
            _frame->data[2],
            _frame->linesize[2]
            );
    SDL_RenderCopy(renderer.GetRenderer().get(), _texture.get(), nullptr, nullptr);
    //TODO:reset 是否正确
    av_frame_free(&_frame);
    pthread_mutex_unlock(&_mutex);
}

int GWUI::Player::OpenCodec(std::shared_ptr<AVStream> stream, std::shared_ptr<AVCodecContext>& codecContext)
{
    //codec.reset(avcodec_find_decoder(stream->codecpar->codec_id));
    // codec = std::shared_ptr<AVCodec>(avcodec_find_decoder(stream->codecpar->codec_id));
    auto codec = avcodec_find_decoder(stream->codecpar->codec_id);

    if(codec == nullptr)
    {
        //error
        return -1;
    }
    codecContext.reset(avcodec_alloc_context3(codec), avcodec_close);
    // TODO: 智能指针为空？？
    if(codecContext == nullptr)
    {
        // error
        return -1;
    }
    if(avcodec_parameters_to_context(codecContext.get(), stream->codecpar))
    {
        // error
        return -1;
    }
    // open
    if(avcodec_open2(codecContext.get(), codec, nullptr) < 0)
    {
        // error
        return -1;
    }
    return 0;
}

void GWUI::Player::readPacketThread()
{
    AVPacket* packet = av_packet_alloc();
    while(true)
    {
        if(_audioStreamIndex != -1)
        {
            if(auto audioSize = _audioPacketQueue.size(); audioSize >= A_QUEUE_MAX_SIZE)
            {
                SDL_Delay(WAIT_TIME_MS);
                continue;
            }
        }
        if(_videoStreamIndex != -1)
        {
            if(auto videoSize = _videoPacketQueue.size(); videoSize >= V_QUEUE_MAX_SIZE)
            {
                SDL_Delay(WAIT_TIME_MS);
                continue;
            }
        }

        if(av_read_frame(_formatContext.get(), packet) < 0)
        {
            // read finish
            break;
        }
        // TODO:智能指针 生命周期，释放的问题
        // 直接存clone之前的？？
        AVPacket *pkt = av_packet_clone(packet);
        av_packet_unref(packet);
        if(pkt->stream_index == _videoStreamIndex)
        {
            _videoPacketQueue.push(pkt);
        }
        else if(pkt->stream_index == _audioStreamIndex)
        {
            _audioPacketQueue.push(pkt);
        }
    }
}

void GWUI::Player::audioThread()
{
    // TODO:发送数据，生命周期的问题
    // std::shared_ptr<AVFrame> frame(av_frame_alloc(), [](AVFrame* p){av_frame_free(&p);});
    AVFrame *frame = av_frame_alloc();

    int maxBufferSize = av_samples_get_buffer_size(NULL, _audioCodecContext->channels, AUDIO_SAMPLE_BUFFER_SIZE, AV_SAMPLE_FMT_S16, 1);
    std::shared_ptr<uint8_t> buffer(static_cast<uint8_t *>(av_malloc(maxBufferSize)));

    SDL_Delay(20); //等待包填充
    while(true)
    {
        if(_quit)
        {
            break;
        }

        AVPacket *pkt;
        _audioPacketQueue.pop(pkt);

        if(pkt == nullptr)
        {
            int leftSize = SDL_GetQueuedAudioSize(_deviceID);
            if (leftSize > 0)
            {
                SDL_Delay(WAIT_TIME_MS);
                continue;
            }
            else
            {
                //finish!
                break;
            }
        }

        if(avcodec_send_packet(_audioCodecContext.get(), pkt) < 0)
        {
            // TODO:
            // error exit
            std::cout << "audio avcodec_send_packet error!" << std::endl;
        }

        while(avcodec_receive_frame(_audioCodecContext.get(), frame) >= 0)
        {
            auto bufferPtr = buffer.get();
            int outSamples = swr_convert(_swr.get(), &bufferPtr, AUDIO_SAMPLE_BUFFER_SIZE,
                                         (const uint8_t **)frame->data, frame->nb_samples);
            if(outSamples < 0)
            {
                std::cout << "swr_convert failed!" << std::endl;
                //error
            }

            int outBuffSize = av_samples_get_buffer_size(nullptr,
                    _audioCodecContext->channels, outSamples, AV_SAMPLE_FMT_S16, 1);
            if(SDL_QueueAudio(_deviceID, bufferPtr, outBuffSize) < 0)
            {
                // error
                std::cout << "SDL_QueueAudio failed" << std::endl;
            }
            _audioClock = frame->pts * av_q2d(_audioStream->time_base);
        }
        av_packet_free(&pkt);
    }
    av_frame_free(&frame);
    _quit = true;
}

void GWUI::Player::videoPrepare()
{
    //std::shared_ptr<AVFrame> frame(av_frame_alloc(), [](AVFrame* p){av_frame_free(&p);});
    AVFrame *frame = nullptr;
    while(true)
    {
        if (_quit)
        {
            break;
        }

        pthread_mutex_lock(&_mutex);
        if (_frame != nullptr)
        {
            pthread_mutex_unlock(&_mutex);
            SDL_Delay(WAIT_TIME_MS);
            continue;
        }

        AVPacket *pkt = nullptr;
        _videoPacketQueue.pop(pkt);
        if (pkt == nullptr)
        {
            pthread_mutex_unlock(&_mutex);
            SDL_Delay(WAIT_TIME_MS);
            continue;
        }

        if (avcodec_send_packet(_videoCodecContext.get(), pkt) < 0)
        {
            // error
        }

        auto ret = avcodec_receive_frame(_videoCodecContext.get(), frame);
        if (ret == AVERROR(EAGAIN))//有时需要预读多个视频帧才能有新的视频帧生成（例如：非关键帧）
        {
            pthread_mutex_unlock(&_mutex);
        }
        else if (ret < 0)
        {
            // error
        }

        _frame = av_frame_alloc();
        // _frame.reset(av_frame_alloc(), [](AVFrame*p){av_frame_free(&p);});
        int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P,
                                                _videoCodecContext->width,
                                                _videoCodecContext->height,
                                                1);

        //在dispFrame中加入buffer空间（av_frame_alloc没有创建空间）
        uint8_t *buffer = (uint8_t *) av_malloc(numBytes * sizeof(uint8_t));
        av_image_fill_arrays(_frame->data,
                             _frame->linesize,
                             buffer,
                             AV_PIX_FMT_YUV420P,
                             _videoCodecContext->width,
                             _videoCodecContext->height,
                             1);

        // Convert the image into YUV format that SDL uses
        sws_scale(_swsContext.get(),
                  (uint8_t const *const *) frame->data,
                  frame->linesize,
                  0,
                  _videoCodecContext->height,
                  _frame->data,
                  _frame->linesize);
        pthread_mutex_unlock(&_mutex);

        auto delayMs = GetVideoRefreshDelay(frame);
        DelayRefresh(delayMs);

        av_packet_free(&pkt);
    }
}

int GWUI::Player::GetVideoRefreshDelay(AVFrame* frame)
{
    double audioClock = GetCurAudioClock();

    double videoClock = frame->pts * av_q2d(_videoStream->time_base); //视频帧的时刻
    double diff = videoClock - audioClock;
    int delay = 0;
    if (diff > 0)
    {
        delay = (int)(1000 * diff);
    }
    if (delay == 0)
    {
        delay = 1;
    }
    return delay;
}

double GWUI::Player::GetCurAudioClock()
{
    int sampleBytesPerSec = _audioCodecContext->channels * SAMPLE_BYTE * _audioCodecContext->sample_rate; //每秒采样大小
    int leftBytes = SDL_GetQueuedAudioSize(_deviceID); //音频设备缓冲区未播放的大小
    double leftSecs = 1.0 * leftBytes / sampleBytesPerSec;
    double clock = _audioClock - leftSecs;
    return clock;
}

void GWUI::Player::DelayRefresh(int delay)
{
    // schedule an SDL timer
    int ret = SDL_AddTimer(delay, refreshCallback, NULL);

    if (ret == 0)
    {
        printf("Could not schedule refresh callback: %s.\n.", SDL_GetError());
    }
}

Uint32 GWUI::Player::refreshCallback(Uint32 interval, void *param)
{
    SDL_Event event;
    event.type = FF_REFRESH_EVENT;
    SDL_PushEvent(&event);
    return 0;
}
