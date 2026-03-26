#include "BlockSetEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        unsigned int BlockSetEvent::getStaticType()
        {
          return BLOCK_SET_EVENT;
        }

        BlockSetEvent::BlockSetEvent(int bx, int by, int bz, int id)
        {
          this->bx = bx;
          this->by = by;
          this->bz = bz;
          this->id = id;
        }

        BlockSetEvent::BlockSetEvent(const BlockSetEvent& event)
        {
          bx = event.bx;
          by = event.by;
          bz = event.bz;
          id = event.id;
        }

        BlockSetEvent& BlockSetEvent::operator=(const BlockSetEvent& event)
        {
          bx = event.bx;
          by = event.by;
          bz = event.bz;
          id = event.id;
          return *this;
        }

        unsigned int BlockSetEvent::getType() const
        {
          return getStaticType();
        }

        int BlockSetEvent::getBX() const
        {
          return bx;
        }

        int BlockSetEvent::getBY() const
        {
          return by;
        }

        int BlockSetEvent::getBZ() const
        {
          return bz;
        }

        int BlockSetEvent::getID() const
        {
          return id;
        }
      }
    }
  }
}
