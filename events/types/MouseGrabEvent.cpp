#include "MouseGrabEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        unsigned int MouseGrabEvent::getStaticType()
        {
          return MOUSE_GRAB_EVENT;
        }

        MouseGrabEvent::MouseGrabEvent(bool grabed)
        {
          this->grabed = grabed;
        }

        MouseGrabEvent::MouseGrabEvent(const MouseGrabEvent& event)
        {
          grabed = event.grabed;
        }

        MouseGrabEvent& MouseGrabEvent::operator=(const MouseGrabEvent& event)
        {
          grabed = event.grabed;
          return *this;
        }

        bool MouseGrabEvent::isGrabed() const
        {
          return grabed;
        }

        unsigned int MouseGrabEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
