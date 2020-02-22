//
// Created by fusionbolt on 2020/2/10.
//

#include <iostream>
#include <memory>
#include <thread>
#include <SDL.h>

#include "Player.h"

//TODO:音频初始化提取
//TODO:锁的问题
//TODO:后台不同步 两个版本的对比
//TODO:错误处理
GWUI::Player::Player(const std::string& path, const GWUI::Renderer& renderer):
        _formatContext(nullptr, avformat_close_input),
        _swsContext(nullptr, sws_freeContext),
        _videoCodecContext(nullptr, avcodec_close),
        _audioCodecContext(nullptr, avcodec_close),
        _frame(nullptr)
{
    _FormatContextInfoInit(path);
    _VideoInit();
    _AudioInit();

    if(_texture == nullptr)
    {
        _texture = renderer.CreateTexture(SDL_PIXELFORMAT_IYUV,
                SDL_TEXTUREACCESS_STREAMING,
                _videoCodecContext->width,
                _videoCodecContext->height);
    }

    _ThreadStart();
}

void GWUI::Player::Draw(Renderer &renderer)
{
    pthread_mutex_lock(&_frameMutex);
    auto flush = [&](){
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
    };

    auto shouldFlush = _needFlush.load();
    if(shouldFlush)
    {
        flush();
        _needFlush = false;
        if(_frame != nullptr)
        {
            av_frame_free(&_frame);
            _frame = nullptr;
        }
    }
    renderer.RendererCopy(_texture);
    pthread_mutex_unlock(&_frameMutex);
}

int GWUI::Player::_OpenCodec(std::shared_ptr<AVStream> stream, std::shared_ptr<AVCodecContext>& codecContext)
{
    //codec.reset(avcodec_find_decoder(stream->codecpar->codec_id));
    // codec = std::shared_ptr<AVCodec>(avcodec_find_decoder(stream->codecpar->codec_id));
    auto codec = avcodec_find_decoder(stream->codecpar->codec_id);

    if(codec == nullptr)
    {
        std::cout << "null codec" << std::endl;
        //error
        return -1;
    }
    codecContext.reset(avcodec_alloc_context3(codec), avcodec_close);
    if(codecContext == nullptr)
    {
        std::cout << "null codecContext" << std::endl;

        // error
        return -1;
    }
    if(avcodec_parameters_to_context(codecContext.get(), stream->codecpar))
    {
        std::cout << "avcodec_parameters_to_context failed" << std::endl;
        // error
        return -1;
    }
    // open
    if(avcodec_open2(codecContext.get(), codec, nullptr) < 0)
    {
        // error
        std::cout << "avcodec_open2 failed" << std::endl;
        return -1;
    }
    return 0;
}

void GWUI::Player::_ReadPacketThread()
{
    AVPacket* packet = av_packet_alloc();
    while(!_quit)
    {
        if(_audioStreamIndex != -1)
        {
            // TODO:这个数据影响
            if(_audioPacketQueue.size() >= AudioQueueMaxSize)
            {
                std::cout << "read Packet Audio size:" << _audioPacketQueue.size() << std::endl;
                SDL_Delay(WaitTimeMs);
                continue;
            }
        }
        // 如果视频流卡住了音频流也会卡住
        if(_videoStreamIndex != -1)
        {
            if(_videoPacketQueue.size() >= VideoQueueMaxSize)
            {
                std::cout << "read Packet Video size:" << _videoPacketQueue.size() << std::endl;
                SDL_Delay(WaitTimeMs);
                continue;
            }
        }
        if(av_read_frame(_formatContext.get(), packet) < 0)
        {
            // read finish
            std::cout << "read audio finished" << std::endl;
            break;
        }
        // TODO:智能指针 生命周期，释放的问题

        AVPacket *pkt = av_packet_clone(packet);
        av_packet_unref(packet);

        if(pkt->stream_index == _videoStreamIndex)
        {
            std::cout << "video push packet" << std::endl;
            _videoPacketQueue.push(pkt);
        }
        else if(pkt->stream_index == _audioStreamIndex)
        {
            std::cout << "audio push packet" << std::endl;
            _audioPacketQueue.push(pkt);
        }
    }
    std::cout << "Read Packet Thread End" << std::endl;
}

void GWUI::Player::_AudioThread()
{
    // TODO:发送数据，生命周期的问题
    std::shared_ptr<AVFrame> frame(av_frame_alloc(), [](AVFrame* p){av_frame_free(&p);});

    int maxBufferSize = av_samples_get_buffer_size(NULL, _audioCodecContext->channels, AudioSampleBufferSize, AV_SAMPLE_FMT_S16, 1);
    std::shared_ptr<uint8_t> buffer(static_cast<uint8_t *>(av_malloc(maxBufferSize)));

    SDL_Delay(20); //等待包填充
    while(!_quit)
    {
        AVPacket *pkt = nullptr;

        //TODO : thread safe error
        if(!_audioPacketQueue.empty())
        {
            _audioPacketQueue.pop(pkt);
        }

        if(pkt == nullptr)
        {
            int leftSize = SDL_GetQueuedAudioSize(_deviceID);
            std::cout << "pkt null leftSize:" << leftSize << std::endl;
            if (leftSize > 0)
            {
                SDL_Delay(WaitTimeMs);
                continue;
            }
            else
            {
                std::cout << "null spin" << std::endl;
                continue;
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

        while(avcodec_receive_frame(_audioCodecContext.get(), frame.get()) >= 0)
        {
            auto bufferPtr = buffer.get();
            int outSamples = swr_convert(_swr.get(), &bufferPtr, AudioSampleBufferSize,
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
    std::cout << "Audio Thread End" << std::endl;
}

void GWUI::Player::_VideoThread()
{
    std::shared_ptr<AVFrame> frame(av_frame_alloc(), [](AVFrame* p){av_frame_free(&p);});
    // AVFrame *frame = av_frame_alloc();
    int numBytes = av_image_get_buffer_size(AV_PIX_FMT_YUV420P,
                                            _videoCodecContext->width,
                                            _videoCodecContext->height,
                                            1);

    //在dispFrame中加入buffer空间（av_frame_alloc没有创建空间）
    // uint8_t *buffer = static_cast<uint8_t *>(av_malloc(numBytes * sizeof(uint8_t)));
    std::shared_ptr<uint8_t> buffer(static_cast<uint8_t *>(av_malloc(numBytes * sizeof(uint8_t))));

    while(!_quit)
    {
        pthread_mutex_lock(&_frameMutex);
        if (_frame != nullptr)
        {
            pthread_mutex_unlock(&_frameMutex);
            SDL_Delay(WaitTimeMs);
            continue;
        }

        AVPacket *pkt = nullptr;
        //TODO:thread safe
        if(!_videoPacketQueue.empty())
        {
            _videoPacketQueue.pop(pkt);
        }

        if (pkt == nullptr)
        {
            pthread_mutex_unlock(&_frameMutex);
            SDL_Delay(WaitTimeMs);
            continue;
        }
        if (avcodec_send_packet(_videoCodecContext.get(), pkt) < 0)
        {
            std::cout << "video thread avcodec_send_packet failed" << std::endl;
            // error
        }

        auto ret = avcodec_receive_frame(_videoCodecContext.get(), frame.get());
        if (ret == AVERROR(EAGAIN))//有时需要预读多个视频帧才能有新的视频帧生成（例如：非关键帧）
        {
            pthread_mutex_unlock(&_frameMutex);
            continue;
        }
        else if (ret < 0)
        {
            std::cout << "video thread error" << std::endl;
            // error
        }

        _frame = av_frame_alloc();

        // _frame.reset(av_frame_alloc(), [](AVFrame*p){av_frame_free(&p);});

        av_image_fill_arrays(_frame->data,
                             _frame->linesize,
                             buffer.get(),
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
        pthread_mutex_unlock(&_frameMutex);

        auto delayMs = _GetVideoRefreshDelay(frame);

        _DelayRefresh(delayMs);

        av_packet_free(&pkt);
    }

    std::cout << "Video Thread End" << std::endl;
}

int GWUI::Player::_GetVideoRefreshDelay(std::shared_ptr<AVFrame> frame)
{
    double audioClock = _GetCurAudioClock();

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

double GWUI::Player::_GetCurAudioClock()
{
    int sampleBytesPerSec = _audioCodecContext->channels * SampleByte * _audioCodecContext->sample_rate; //每秒采样大小
    int leftBytes = SDL_GetQueuedAudioSize(_deviceID); //音频设备缓冲区未播放的大小
    std::cout << "huanchong:" << leftBytes << std::endl;
    double leftSecs = 1.0 * leftBytes / sampleBytesPerSec;
    double clock = _audioClock - leftSecs;
    return clock;
}

void GWUI::Player::_DelayRefresh(int delay)
{
    // schedule an SDL timer
    int ret = SDL_AddTimer(delay, _RefreshCallback, this);

    if (ret == 0)
    {
        printf("Could not schedule refresh callback: %s.\n.", SDL_GetError());
    }
}

Uint32 GWUI::Player::_RefreshCallback(Uint32 interval, void *param)
{
    static_cast<Player *>(param)->_SetNeedFlush();
    return 0;
}

void GWUI::Player::_SetNeedFlush()
{
    _needFlush = true;
}

GWUI::Player::~Player()
{
    _quit = true;
    _readPacketThread->join();
    _audioThread->join();
    _videoThread->join();
}

void GWUI::Player::_AudioInit()
{
    if(_OpenCodec(_audioStream, _audioCodecContext) != 0)
    {
        std::cout << "Open Audio Codec Failed" << std::endl;
    }

    SDL_AudioSpec wanted_specs;
    SDL_AudioSpec specs;

    wanted_specs.freq = _audioCodecContext->sample_rate;
    wanted_specs.format = AUDIO_S16SYS; //!!!应该是AUDIO开头的变量，而不是AV开头的变量
    wanted_specs.channels = _audioCodecContext->channels;
    wanted_specs.silence = 0;
    wanted_specs.samples = AudioSampleBufferSize; //frame buffer size
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
}

void GWUI::Player::_VideoInit()
{
    if(_OpenCodec(_videoStream, _videoCodecContext) != 0)
    {
        std::cout << "Open Video Codec Failed" << std::endl;
    }

    _swsContext.reset(sws_getContext(
            _videoCodecContext->width,
            _videoCodecContext->height,
            _videoCodecContext->pix_fmt,
            _videoCodecContext->width,
            _videoCodecContext->height,
            AV_PIX_FMT_YUV420P,
            SWS_BILINEAR,
            nullptr,
            nullptr,
            nullptr
    ), sws_freeContext);
}

void GWUI::Player::_FormatContextInfoInit(const std::string& path)
{
    AVFormatContext *ptr = nullptr;
    if (avformat_open_input(&ptr, path.c_str(), nullptr, nullptr))
    {
        std::cout << "Open Failed" << std::endl;
    }
    //TODO: release error
    //_formatContext.reset(ptr, [](AVFormatContext* f){avformat_close_input(&f);});
    _formatContext.reset(ptr);

    if (avformat_find_stream_info(_formatContext.get(), nullptr) < 0)
    {
        std::cout << "Find StreamInfo Failed" << std::endl;
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
}

void GWUI::Player::_ThreadStart()
{
    _readPacketThread = std::make_shared<std::thread>(std::bind(&Player::_ReadPacketThread, this));
    _audioThread = std::make_shared<std::thread>(std::bind(&Player::_AudioThread, this));
    _videoThread = std::make_shared<std::thread>(std::bind(&Player::_VideoThread, this));
}
