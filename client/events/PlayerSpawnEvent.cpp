#include "PlayerSpawnEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int PlayerSpawnEvent::getStaticType()
        {
          return gde::CLIENT_PLAYER_SPAWN_EVENT;
        }

        PlayerSpawnEvent::PlayerSpawnEvent(unsigned int clientId, const Pointer<gdco::Player>& player)
        {
          this->clientId = clientId;
          this->player = player;
        }

        PlayerSpawnEvent::PlayerSpawnEvent(const PlayerSpawnEvent& event)
        {
          clientId = event.clientId;
          player = event.player;
        }

        PlayerSpawnEvent& PlayerSpawnEvent::operator=(const PlayerSpawnEvent& event)
        {
          clientId = event.clientId;
          player = event.player;
          return *this;
        }

        unsigned int PlayerSpawnEvent::getClientId() const
        {
          return clientId;
        }

        const Pointer<gdco::Player>& PlayerSpawnEvent::getPlayerPointer() const
        {
          return player;
        }

        gdco::Player* PlayerSpawnEvent::getPlayer() const
        {
          return player.value();
        }

        unsigned int PlayerSpawnEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
