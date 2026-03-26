#ifndef GD_SERVER_EVENTS_CHUNKREQUESTEVENT_H
#define GD_SERVER_EVENTS_CHUNKREQUESTEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        class ChunkRequestEvent : public gde::Event
        {
        private:
          unsigned int clientId;

          int cx;
          int cy;
          int cz;

        public:
          static unsigned int getStaticType();

          ChunkRequestEvent(unsigned int, int, int, int);
          ChunkRequestEvent(const ChunkRequestEvent&);
          ChunkRequestEvent& operator=(const ChunkRequestEvent&);

          unsigned int getClientId() const;
          int getCX() const;
          int getCY() const;
          int getCZ() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
