#include "ConnectionPacketListener.h"

#include <iostream>

#include "../packets/ConnectionPacket.h"
#include "../packets/PlayerSpawnPacket.h"

#include "../objects/Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        ConnectionPacketListener::ConnectionPacketListener(gdn::Server* server, Players* players)
        {
          this->server = server;
          this->players = players;
        }

        ConnectionPacketListener::ConnectionPacketListener(const ConnectionPacketListener& listener)
        {
          server = listener.server;
          players = listener.players;
        }

        ConnectionPacketListener& ConnectionPacketListener::operator=(const ConnectionPacketListener& listener)
        {
          server = listener.server;
          players = listener.players;
          return *this;
        }

        void ConnectionPacketListener::sendPlayerData(unsigned int clientId, unsigned int id) const
        {
          gdso::Player* player = players->getPlayer(id);
          if(player != NULL)
          {
            server->sendPacketTo(clientId, gdsp::PlayerSpawnPacket(id, player));
            //server->sendPacketTo(clientId, gdsp::PlayerEquipedItemPacket(id, 0, player->getItemStackInRightHand()));
          }
        }

        void ConnectionPacketListener::sendInitialGameData(unsigned int clientId) const
        {
          for(unsigned int id=0;id<players->getMaxPlayers();id++)
          {
            if(id != clientId)
            {
              sendPlayerData(clientId, id);
            }
          }
        }

        void ConnectionPacketListener::onEvent(gdse::ConnectionPacketReceiveEvent* event)
        {
          std::cout << "client: " << event->getClientId() << " is requesting connection..." << std::endl;
          server->sendPacketTo(event->getClientId(), gdsp::ConnectionPacket(players->getMaxPlayers()));
          sendInitialGameData(event->getClientId());
          std::cout << "connection accepted!" << std::endl;
        }
      }
    }
  }
}
