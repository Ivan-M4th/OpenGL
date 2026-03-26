#ifndef GD_SERVER_LISTENERS_CLIENTUPDATEPACKETLISTENER_H
#define GD_SERVER_LISTENERS_CLIENTUPDATEPACKETLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/ClientUpdatePacketReceiveEvent.h"

#include "../../networking/Server.h"

#include "../Players.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        class ClientUpdatePacketListener : public gde::Listener<gdse::ClientUpdatePacketReceiveEvent>
        {
        private:
          gdn::Server* server;
          Players* players;

        public:
          ClientUpdatePacketListener(gdn::Server*, Players*);
          ClientUpdatePacketListener(const ClientUpdatePacketListener&);
          ClientUpdatePacketListener& operator=(const ClientUpdatePacketListener&);

          void onEvent(gdse::ClientUpdatePacketReceiveEvent*) override;
        };
      }
    }
  }
}

#endif
