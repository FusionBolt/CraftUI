//
// Created by fusionbolt on 2020-01-24.
//

#include "Timer.h"
#include "SDL.h"

GWUI::Timer::Timer() noexcept:
        _startTicks(0), _pausedTicks(0), _paused(false), _started(false)
{

}

void GWUI::Timer::Start() noexcept
{
    //启动计时器
    _started = true;
    //将计时器设为非暂停状态
    _paused = false;
    //获取当前时钟时间
    _startTicks = SDL_GetTicks();
}

void GWUI::Timer::Stop() noexcept
{
    //停止计时器
    _started = false;
    //将计时器设为非暂停状态
    _paused = false;
}

void GWUI::Timer::Pause() noexcept
{
    //如果计时器正在运行但没有暂停
    if ((_started) && (_paused))
    {
        //暂停计时器
        _paused = true;
        //计算暂停时的滴答数
        _pausedTicks = _GetTicks() - _startTicks;
    }
}

void GWUI::Timer::UnPause() noexcept
{
    //如果计时器暂停中
    if (_paused)
    {
        //取消暂停
        _paused = false;
        //重置开始时间
        _startTicks = _GetTicks() - _pausedTicks;
        //重置暂停时间
        _pausedTicks = 0;
    }
}

int GWUI::Timer::GetTicks() noexcept
{
    //如果计时器正在运行
    if (_started)
    {
        //如果计时器暂停中
        if (_paused)
        {
            //返回计时器暂停时的滴答数
            return _pausedTicks;
        }
        else
        {
            //返回当前时间减去启动时间的差值
            return _GetTicks() - _startTicks;
        }
    }
    //如果计时器没有在运行
    return 0;
}

bool GWUI::Timer::IsStarted() noexcept
{
    return _started;
}

bool GWUI::Timer::IsPaused() noexcept
{
    return _paused;
}

int GWUI::Timer::_GetTicks() noexcept
{
    return static_cast<int>(SDL_GetTicks());
}
