#ifndef GD_GUI_TRANSITION_H
#define GD_GUI_TRANSITION_H

#include "../gddef.h"

#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace gui
    {
      class Transition
      {
      protected:
        float duration;
        float time;

      public:
        Transition(float);
        Transition(const Transition&);
        Transition& operator=(const Transition&);
        virtual ~Transition();

        bool isFinished() const;

        virtual void update(float);
        virtual gdm::Vector2 getPosition(const gdm::Vector2&) const;
      };
    }
  }
}

#endif
