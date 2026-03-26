#include "LeftClickEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        unsigned int LeftClickEvent::getStaticType()
        {
          return LEFT_CLICK_EVENT;
        }

        unsigned int LeftClickEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
