//
// Created by fusionbolt on 2020-01-24.
//

#ifndef GWUI_TIMER_H
#define GWUI_TIMER_H

namespace GWUI
{
    class Timer
    {
    public:
        //初始化变量
        Timer() noexcept;
        //各种时钟动作
        void Start() noexcept;

        void Stop() noexcept;

        void Pause() noexcept;

        void UnPause() noexcept;
        //获取计时器时间
        int GetTicks() noexcept;
        //检查计时器状态
        bool IsStarted() noexcept;

        bool IsPaused() noexcept;

    private:
        int _GetTicks() noexcept;
        //计时器启动时的时间
        int _startTicks;
        //计时器暂停时保存的滴答数
        int _pausedTicks;
        //计时器状态
        bool _paused;

        bool _started;
    };
}


#endif //GWUI_TIMER_H
