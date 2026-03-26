#include "RequestSpawnPacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace events
      {
        unsigned int RequestSpawnPacketReceiveEvent::getStaticType()
        {
          return gde::SERVER_REQUEST_SPAWN_PACKET_RECEIVE_EVENT;
        }

        RequestSpawnPacketReceiveEvent::RequestSpawnPacketReceiveEvent(unsigned int clientId)
        {
          this->clientId = clientId;
        }

        RequestSpawnPacketReceiveEvent::RequestSpawnPacketReceiveEvent(const RequestSpawnPacketReceiveEvent& event)
        {
          clientId = event.clientId;
        }

        RequestSpawnPacketReceiveEvent& RequestSpawnPacketReceiveEvent::operator=(const RequestSpawnPacketReceiveEvent& event)
        {
          clientId = event.clientId;
          return *this;
        }

        unsigned int RequestSpawnPacketReceiveEvent::getClientId() const
        {
          return clientId;
        }

        unsigned int RequestSpawnPacketReceiveEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
