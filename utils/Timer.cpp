#include "Timer.h"

namespace gt
{
  namespace doubovik
  {
    Timer::Timer()
    {
      time = 0.0;
    }

    Timer::Timer(const Timer& timer)
    {
      time = timer.time;
    }

    Timer& Timer::operator=(const Timer& timer)
    {
      time = timer.time;
      return *this;
    }

    void Timer::update(float timePassed)
    {
      time+=timePassed;
    }

    float Timer::getTime() const
    {
      return time;
    }

    void Timer::reset()
    {
      time = 0.0;
    }
  }
}
