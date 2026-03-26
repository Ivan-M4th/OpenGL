#include "PlayerDespawnPacketListener.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        PlayerDespawnPacketListener::PlayerDespawnPacketListener(Players* players)
        {
          this->players = players;
        }

        PlayerDespawnPacketListener::PlayerDespawnPacketListener(const PlayerDespawnPacketListener& listener)
        {
          players = listener.players;
        }

        PlayerDespawnPacketListener& PlayerDespawnPacketListener::operator=(const PlayerDespawnPacketListener& listener)
        {
          players = listener.players;
          return *this;
        }

        void PlayerDespawnPacketListener::onEvent(gdce::PlayerDespawnPacketReceiveEvent* event)
        {
          std::cout << "player: " << event->getClientId() << " despawned!" << std::endl;
          players->removePlayer(event->getClientId());
        }
      }
    }
  }
}
