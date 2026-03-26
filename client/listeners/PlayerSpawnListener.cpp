#include "PlayerSpawnListener.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        PlayerSpawnListener::PlayerSpawnListener(Players* players)
        {
          this->players = players;
        }

        PlayerSpawnListener::PlayerSpawnListener(const PlayerSpawnListener& listener)
        {
          players = listener.players;
        }

        PlayerSpawnListener& PlayerSpawnListener::operator=(const PlayerSpawnListener& listener)
        {
          players = listener.players;
          return *this;
        }

        void PlayerSpawnListener::onEvent(gdce::PlayerSpawnEvent* event)
        {
          std::cout << "player: " << event->getClientId() << " spawned!" << std::endl;
          players->setPlayer(event->getClientId(), event->getPlayerPointer());
        }
      }
    }
  }
}
