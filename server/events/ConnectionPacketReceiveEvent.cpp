#include "ConnectionPacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {

        unsigned int ConnectionPacketReceiveEvent::getStaticType()
        {
          return gde::SERVER_CONNECTION_PACKET_RECEIVE;
        }

        ConnectionPacketReceiveEvent::ConnectionPacketReceiveEvent(unsigned int clientId)
        {
          this->clientId = clientId;
        }

        ConnectionPacketReceiveEvent::ConnectionPacketReceiveEvent(const ConnectionPacketReceiveEvent& event)
        {
          clientId = event.clientId;
        }

        ConnectionPacketReceiveEvent& ConnectionPacketReceiveEvent::operator=(const ConnectionPacketReceiveEvent& event)
        {
          clientId = event.clientId;
          return *this;
        }

        unsigned int ConnectionPacketReceiveEvent::getClientId() const
        {
          return clientId;
        }

        unsigned int ConnectionPacketReceiveEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
