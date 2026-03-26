#include "PlayerUpdatePacketListener.h"

#include "../objects/Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        PlayerUpdatePacketListener::PlayerUpdatePacketListener(Players* players)
        {
          this->players = players;
        }

        PlayerUpdatePacketListener::PlayerUpdatePacketListener(const PlayerUpdatePacketListener& listener)
        {
          players = listener.players;
        }

        PlayerUpdatePacketListener& PlayerUpdatePacketListener::operator=(const PlayerUpdatePacketListener& listener)
        {
          players = listener.players;
          return *this;
        }

        void PlayerUpdatePacketListener::onEvent(gdce::PlayerUpdatePacketReceiveEvent* event)
        {
          if(event->getClientId() >= players->getMaxPlayers())
          {
            return;
          }

          gdco::Player* player = players->getPlayer(event->getClientId());
          if(player != NULL)
          {
            player->transformation.position = event->getPosition();
            player->speed = event->getSpeed();
            player->transformation.rotation = event->getRotation();
            player->rotationSpeed = event->getRotationSpeed();
          }
        }
      }
    }
  }
}
