#ifndef GD_EVENTS_TYPES_KEYPRESSEDEVENT_H
#define GD_EVENTS_TYPES_KEYPRESSEDEVENT_H

#include "../Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        class KeyPressedEvent : public Event
        {
        protected:
          unsigned int keyCode;

        public:
          static unsigned int getStaticType();

          KeyPressedEvent(unsigned int);
          KeyPressedEvent(const KeyPressedEvent&);
          KeyPressedEvent& operator=(const KeyPressedEvent&);

          unsigned int getKeyCode() const;

          virtual unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
