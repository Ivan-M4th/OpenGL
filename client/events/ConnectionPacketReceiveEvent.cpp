#include "ConnectionPacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int ConnectionPacketReceiveEvent::getStaticType()
        {
          return gde::CLIENT_CONNECTION_PACKET_RECEIVE_EVENT;
        }

        ConnectionPacketReceiveEvent::ConnectionPacketReceiveEvent(unsigned int maxPlayers)
        {
          this->maxPlayers = maxPlayers;
        }

        ConnectionPacketReceiveEvent::ConnectionPacketReceiveEvent(const ConnectionPacketReceiveEvent& event)
        {
          maxPlayers = event.maxPlayers;
        }

        ConnectionPacketReceiveEvent& ConnectionPacketReceiveEvent::operator=(const ConnectionPacketReceiveEvent& event)
        {
          maxPlayers = event.maxPlayers;
          return *this;
        }

        unsigned int ConnectionPacketReceiveEvent::getMaxPlayers() const
        {
          return maxPlayers;
        }

        unsigned int ConnectionPacketReceiveEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
