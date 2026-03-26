#ifndef GD_SERVER_EVENTS_REQUESTSPAWNPACKETRECEIVEEVENT_H
#define GD_SERVER_EVENTS_REQUESTSPAWNPACKETRECEIVEEVENT_H

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
        class RequestSpawnPacketReceiveEvent : public gde::Event
        {
        private:
          unsigned int clientId;

        public:
          static unsigned int getStaticType();

          RequestSpawnPacketReceiveEvent(unsigned int);
          RequestSpawnPacketReceiveEvent(const RequestSpawnPacketReceiveEvent&);
          RequestSpawnPacketReceiveEvent& operator=(const RequestSpawnPacketReceiveEvent&);

          unsigned int getClientId() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
