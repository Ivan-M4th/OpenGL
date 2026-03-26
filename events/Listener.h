#ifndef GD_EVENTS_LISTENER_H
#define GD_EVENTS_LISTENER_H

#include "AbstractListener.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      template<typename EventType> class Listener : public AbstractListener
      {
      public:
        virtual unsigned int getEventType() const override
        {
          return EventType::getStaticType();
        }

        virtual void onEvent(Event* event) override
        {
          EventType* e = (EventType*)event;
          onEvent(e);
        }

        virtual void onEvent(EventType*) = 0;
      };
    }
  }
}

#endif
