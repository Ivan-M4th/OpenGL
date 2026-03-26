#ifndef GD_CLIENT_EVENTS_PLAYERDESPAWNPACKETRECEIVEEVENT_H
#define GD_CLIENT_EVENTS_PLAYERDESPAWNPACKETRECEIVEEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class PlayerDespawnPacketReceiveEvent : public gde::Event
        {
        private:
          unsigned int clientId;

        public:
          static unsigned int getStaticType();

          PlayerDespawnPacketReceiveEvent(unsigned int);
          PlayerDespawnPacketReceiveEvent(const PlayerDespawnPacketReceiveEvent&);
          PlayerDespawnPacketReceiveEvent& operator=(const PlayerDespawnPacketReceiveEvent&);

          unsigned int getClientId() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
