#ifndef GD_UTILS_TIMER_H
#define GD_UTILS_TIMER_H

namespace gt
{
  namespace doubovik
  {
    class Timer
    {
    private:
      float time;
    public:
      Timer();
      Timer(const Timer&);
      Timer& operator=(const Timer&);

      void update(float);
      float getTime() const;
      void reset();
    };
  }
}

#endif
