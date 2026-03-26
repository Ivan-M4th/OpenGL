#ifndef GD_EVENTS_TYPES_BLOCKSETEVENT_H
#define GD_EVENTS_TYPES_BLOCKSETEVENT_H

#include "../Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace events
    {
      namespace types
      {
        class BlockSetEvent : public Event
        {
        private:
          int bx;
          int by;
          int bz;
          int id;

        public:
          static unsigned int getStaticType();

          BlockSetEvent(int, int, int, int);
          BlockSetEvent(const BlockSetEvent&);
          BlockSetEvent& operator=(const BlockSetEvent&);

          unsigned int getType() const override;

          int getBX() const;
          int getBY() const;
          int getBZ() const;
          int getID() const;
        };
      }
    }
  }
}

#endif
