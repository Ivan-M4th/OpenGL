#ifndef GD_SERVER_LISTENERS_CONNECTIONPACKETLISTENER_H
#define GD_SERVER_LISTENERS_CONNECTIONPACKETLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/ConnectionPacketReceiveEvent.h"

#include "../../networking/Server.h"
#include "../Players.h"

//Dont't call PacketReceiveEvent in here!

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        class ConnectionPacketListener : public gde::Listener<gdse::ConnectionPacketReceiveEvent>
        {
        private:
          gdn::Server* server;
          Players* players;

          void sendPlayerData(unsigned int, unsigned int) const;
          void sendInitialGameData(unsigned int) const;
        public:
          ConnectionPacketListener(gdn::Server*, Players*);
          ConnectionPacketListener(const ConnectionPacketListener&);
          ConnectionPacketListener& operator=(const ConnectionPacketListener&);

          void onEvent(gdse::ConnectionPacketReceiveEvent*) override;
        };
      }
    }
  }
}

#endif
