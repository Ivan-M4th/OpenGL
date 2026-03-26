#include "Transition.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      Transition::Transition(float duration)
      {
        this->duration = duration;
        time = 0.0;
      }

      Transition::Transition(const Transition& transition)
      {
        duration = transition.duration;
        time = transition.time;
      }

      Transition& Transition::operator=(const Transition& transition)
      {
        duration = transition.duration;
        time = transition.time;
        return *this;
      }

      Transition::~Transition()
      {

      }

      bool Transition::isFinished() const
      {
        return time > duration;
      }

      void Transition::update(float timePassed)
      {
        time+=timePassed;
      }

      gdm::Vector2 Transition::getPosition(const gdm::Vector2& position) const
      {
        return position;
      }
    }
  }
}
