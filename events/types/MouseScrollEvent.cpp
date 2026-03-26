#include "MouseScrollEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        unsigned int MouseScrollEvent::getStaticType()
        {
          return MOUSE_SCROLL_EVENT;
        }

        MouseScrollEvent::MouseScrollEvent(int deltaX, int deltaY)
        {
          this->deltaX = deltaX;
          this->deltaY = deltaY;
        }

        MouseScrollEvent::MouseScrollEvent(const MouseScrollEvent& event)
        {
          deltaX = event.deltaX;
          deltaY = event.deltaY;
        }

        MouseScrollEvent& MouseScrollEvent::operator=(const MouseScrollEvent& event)
        {
          deltaX = event.deltaX;
          deltaY = event.deltaY;
          return *this;
        }

        int MouseScrollEvent::getDeltaX() const
        {
          return deltaX;
        }

        int MouseScrollEvent::getDeltaY() const
        {
          return deltaY;
        }

        unsigned int MouseScrollEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
