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
#include <mutex>

#include "LockFreeQueue.h"
#include "../units/Renderer.h"

namespace GWUI
{
constexpr auto VideoQueueMaxSize = 300;
constexpr auto AudioQueueMaxSize = 700;
// constexpr auto AudioSampleBufferSize = 2048;
constexpr auto AudioSampleBufferSize = 4096;
constexpr auto WaitTimeMs = 5;
constexpr auto SampleByte = 2;

    class Player
    {
    public:
        Player(const std::string& path, const GWUI::Renderer& renderer);

        void Draw(Renderer &renderer);

        ~Player();

    private:
        void _FormatContextInfoInit(const std::string& path);

        void _VideoInit();

        void _AudioInit();

        void _ThreadStart();

        int _OpenCodec(std::shared_ptr<AVStream> stream, std::shared_ptr<AVCodecContext>& codecContext);

        void _ReadPacketThread();

        void _AudioThread();

        void _VideoThread();

        int _GetVideoRefreshDelay(std::shared_ptr<AVFrame> frame);

        double _GetCurAudioClock();

        void _DelayRefresh(int delay);

        void _SetNeedFlush();

        static Uint32 _RefreshCallback(Uint32 interval, void *param);

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

        pthread_mutex_t _frameMutex;

        std::atomic<bool> _needFlush = false;

        std::shared_ptr<std::thread> _readPacketThread, _audioThread, _videoThread;
    };
}

#endif //GWUI_PLAYER_H
