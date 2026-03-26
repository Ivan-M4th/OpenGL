#include "ClientDisconnectionListener.h"

#include <iostream>

#include "../packets/PlayerDespawnPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        ClientDisconnectionListener::ClientDisconnectionListener(gdn::Server* server, Players* players)
        {
          this->server = server;
          this->players = players;
        }

        ClientDisconnectionListener::ClientDisconnectionListener(const ClientDisconnectionListener& listener)
        {
          server = listener.server;
          players = listener.players;
        }

        ClientDisconnectionListener& ClientDisconnectionListener::operator=(const ClientDisconnectionListener& listener)
        {
          server = listener.server;
          players = listener.players;
          return *this;
        }

        void ClientDisconnectionListener::onEvent(gdse::ClientDisconnectEvent* event)
        {
          std::cout << "client " << event->getClientId() << " disconnected!" << std::endl;
          players->removePlayer(event->getClientId());
          server->sendPacketToOtherClients(event->getClientId(), gdsp::PlayerDespawnPacket(event->getClientId()));
        }
      }
    }
  }
}
