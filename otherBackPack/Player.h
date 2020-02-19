//
// Created by fusionbolt on 2020/2/10.
//

#ifndef GWUI_PLAYER_H
#define GWUI_PLAYER_H

extern "C"
{
#include <libavcodec/avcodec.h>
#include <libavformat/avformat.h>
#include <libswscale/swscale.h>
#include <libavutil/imgutils.h>
#include <libswresample/swresample.h>
}
#include <unistd.h>
#include <sys/stat.h>
#include <string>
#include <SDL_audio.h>

#include "LockFreeQueue.h"
#include "units/Renderer.hpp"

namespace GWUI
{
    //TODO:replace
#define V_QUEUE_MAX_SIZE 100          //视频的包队列最大长度
#define A_QUEUE_MAX_SIZE 200          //音频的包队列最大长度
#define AUDIO_SAMPLE_BUFFER_SIZE 2048 //音频设备内部缓存区的大小（单位为采样数）
#define WAIT_TIME_MS 5                //轮询等待时间
#define SAMPLE_BYTE 2                 //采样编码对应的字节数
#define DISPLAY_WIDTH 800             //播放窗口最大宽度
#define DISPLAY_HEIGHT 600            //播放窗口最大高度

#define FF_REFRESH_EVENT (SDL_USEREVENT)  //播放刷新事件
#define FF_QUIT_EVENT (SDL_USEREVENT + 1) //退出事件

    class Player
    {
    public:
        Player(const std::string& path);

        void Draw(Renderer renderer);

    private:
        int OpenCodec(std::shared_ptr<AVStream> stream, std::shared_ptr<AVCodecContext>& codecContext);

        void readPacketThread();

        void audioThread();

        void videoPrepare();

        int GetVideoRefreshDelay(AVFrame* frame);

        double GetCurAudioClock();

        void DelayRefresh(int delay);

        static Uint32 refreshCallback(Uint32 interval, void *param);

        // std::shared_ptr<AVCodec> _videoCodec, _audioCodec;
        std::shared_ptr<AVFormatContext> _formatContext;
        std::shared_ptr<AVCodecContext> _videoCodecContext, _audioCodecContext;
        AVFrame* _frame;
        std::shared_ptr<SwsContext> _swsContext;
        std::shared_ptr<AVStream> _videoStream, _audioStream;
        std::shared_ptr<SwrContext> _swr;
        int _videoStreamIndex = -1;
        int _audioStreamIndex = -1;
        SafeQueue<AVPacket*> _videoPacketQueue, _audioPacketQueue;
        std::shared_ptr<SDL_Texture> _texture;

        bool _quit = false;
        double _audioClock = 0;
        SDL_AudioDeviceID _deviceID;

        pthread_mutex_t _mutex;
    };
}

#endif //GWUI_PLAYER_H
