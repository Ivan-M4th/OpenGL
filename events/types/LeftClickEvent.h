#ifndef GD_EVENTS_TYPES_LEFTCLICKEVENT_H
#define GD_EVENTS_TYPES_LEFTCLICKEVENT_H

#include "../Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        class LeftClickEvent : public Event
        {
        public:
          static unsigned int getStaticType();

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
