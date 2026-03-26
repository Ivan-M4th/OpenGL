#ifndef GD_EVENTS_ABSTRACTLISTENER_H
#define GD_EVENTS_ABSTRACTLISTENER_H

#include "Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      class AbstractListener
      {
      public:
        virtual unsigned int getEventType() const = 0;
        virtual void onEvent(Event*) = 0;
      };
    }
  }
}

#endif
