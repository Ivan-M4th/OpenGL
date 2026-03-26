#include "PlayerDespawnPacketReceiveEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int PlayerDespawnPacketReceiveEvent::getStaticType()
        {
          return gde::CLIENT_PLAYER_DESPAWN_PACKET_RECEIVE_EVENT;
        }

        PlayerDespawnPacketReceiveEvent::PlayerDespawnPacketReceiveEvent(unsigned int clientId)
        {
          this->clientId = clientId;
        }

        PlayerDespawnPacketReceiveEvent::PlayerDespawnPacketReceiveEvent(const PlayerDespawnPacketReceiveEvent& event)
        {
          clientId = event.clientId;
        }

        PlayerDespawnPacketReceiveEvent& PlayerDespawnPacketReceiveEvent::operator=(const PlayerDespawnPacketReceiveEvent& event)
        {
          clientId = event.clientId;
          return *this;
        }

        unsigned int PlayerDespawnPacketReceiveEvent::getClientId() const
        {
          return clientId;
        }

        unsigned int PlayerDespawnPacketReceiveEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
