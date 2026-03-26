#ifndef GD_EVENTS_TYPES_MOUSESCROLLEVENT_H
#define GD_EVENTS_TYPES_MOUSESCROLLEVENT_H

#include "../Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        class MouseScrollEvent : public Event
        {
        private:
          int deltaX;
          int deltaY;

        public:
          static unsigned int getStaticType();

          MouseScrollEvent(int, int);
          MouseScrollEvent(const MouseScrollEvent&);
          MouseScrollEvent& operator=(const MouseScrollEvent&);

          int getDeltaX() const;
          int getDeltaY() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
