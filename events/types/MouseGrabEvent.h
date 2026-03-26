#ifndef GD_EVENTS_TYPES_MOUSEGRABEVENT_H
#define GD_EVENTS_TYPES_MOUSEGRABEVENT_H

#include "../Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        class MouseGrabEvent : public Event
        {
        private:
          bool grabed;

        public:
          static unsigned int getStaticType();

          MouseGrabEvent(bool);
          MouseGrabEvent(const MouseGrabEvent&);
          MouseGrabEvent& operator=(const MouseGrabEvent&);

          bool isGrabed() const;

          virtual unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
