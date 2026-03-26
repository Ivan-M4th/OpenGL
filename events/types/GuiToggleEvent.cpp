#include "GuiToggleEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        unsigned int GuiToggleEvent::getStaticType()
        {
          return GUI_TOGGLE_EVENT;
        }

        GuiToggleEvent::GuiToggleEvent(bool open)
        {
          this->open = open;
        }

        GuiToggleEvent::GuiToggleEvent(const GuiToggleEvent& event)
        {
          open = event.open;
        }

        GuiToggleEvent& GuiToggleEvent::operator=(const GuiToggleEvent& event)
        {
          open = event.open;
          return *this;
        }

        bool GuiToggleEvent::isOpen() const
        {
          return open;
        }

        unsigned int GuiToggleEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
