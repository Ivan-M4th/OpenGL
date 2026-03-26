#include "ClientUpdatePacketListener.h"

#include "../objects/Player.h"

#include "../packets/PlayerUpdatePacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        ClientUpdatePacketListener::ClientUpdatePacketListener(gdn::Server* server, Players* players)
        {
          this->server = server;
          this->players = players;
        }

        ClientUpdatePacketListener::ClientUpdatePacketListener(const ClientUpdatePacketListener& listener)
        {
          server = listener.server;
          players = listener.players;
        }

        ClientUpdatePacketListener& ClientUpdatePacketListener::operator=(const ClientUpdatePacketListener& listener)
        {
          server = listener.server;
          players = listener.players;
          return *this;
        }

        void ClientUpdatePacketListener::onEvent(gdse::ClientUpdatePacketReceiveEvent* event)
        {
          gdso::Player* player = players->getPlayer(event->getClientId());
          if(player != NULL)
          {
            player->transformation.position = event->getPosition();
            player->speed = event->getSpeed();
            player->transformation.rotation = event->getRotation();
            player->rotationSpeed = event->getRotationSpeed();

            server->sendPacketToOtherClients(event->getClientId(), gdsp::PlayerUpdatePacket(event->getClientId(), player));
          }
        }
      }
    }
  }
}
