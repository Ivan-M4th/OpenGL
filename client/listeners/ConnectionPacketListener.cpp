#include "ConnectionPacketListener.h"

#include "../../Debug.h"

#include "../packets/RequestSpawnPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        ConnectionPacketListener::ConnectionPacketListener(gdn::Client* client, Players* players)
        {
          this->client = client;
          this->players = players;
        }

        ConnectionPacketListener::ConnectionPacketListener(const ConnectionPacketListener& listener)
        {
          client = listener.client;
          players = listener.players;
        }
        ConnectionPacketListener& ConnectionPacketListener::operator=(const ConnectionPacketListener& listener)
        {
          client = listener.client;
          players = listener.players;
          return *this;
        }

        void ConnectionPacketListener::onEvent(gdce::ConnectionPacketReceiveEvent* event)
        {
          DEBUG << "connection info received: " << event->getMaxPlayers() << " initialising data...",
          DEBUG.endl();
          
          players->setMaxPlayers(event->getMaxPlayers());
          client->sendPacket(gdcp::RequestSpawnPacket());
        }
      }
    }
  }
}
