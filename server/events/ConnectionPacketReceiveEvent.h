#ifndef GD_SERVER_EVENTS_CONNECTIONPACKETRECEIVEEVENT_H
#define GD_SERVER_EVENTS_CONNECTIONPACKETRECEIVEEVENT_H

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
        class ConnectionPacketReceiveEvent : public gde::Event
        {
        private:
          unsigned int clientId;

        public:
          static unsigned int getStaticType();

          ConnectionPacketReceiveEvent(unsigned int);
          ConnectionPacketReceiveEvent(const ConnectionPacketReceiveEvent&);
          ConnectionPacketReceiveEvent& operator=(const ConnectionPacketReceiveEvent&);

          unsigned int getClientId() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
