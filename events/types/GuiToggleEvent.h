#ifndef GD_EVENTS_TYPES_GUITOGGLEEVENT_H
#define GD_EVENTS_TYPES_GUITOGGLEEVENT_H

#include "../Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        class GuiToggleEvent : public Event
        {
        private:
          bool open;

        public:
          static unsigned int getStaticType();

          GuiToggleEvent(bool);
          GuiToggleEvent(const GuiToggleEvent&);
          GuiToggleEvent& operator=(const GuiToggleEvent&);

          bool isOpen() const;

          virtual unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
