#ifndef GD_CLIENT_EVENTS_CONNECTIONPACKETRECEIVEEVENT_H
#define GD_CLIENT_EVENTS_CONNECTIONPACKETRECEIVEEVENT_H

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
        class ConnectionPacketReceiveEvent : public gde::Event
        {
        private:
          unsigned int maxPlayers;

        public:
          static unsigned int getStaticType();

          ConnectionPacketReceiveEvent(unsigned int);
          ConnectionPacketReceiveEvent(const ConnectionPacketReceiveEvent&);
          ConnectionPacketReceiveEvent& operator=(const ConnectionPacketReceiveEvent&);

          unsigned int getMaxPlayers() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
