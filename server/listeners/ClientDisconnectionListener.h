#ifndef GD_SERVER_LISTENERS_CLIENTDISCONNECTIONLISTENER_H
#define GD_SERVER_LISTENERS_CLIENTDISCONNECTIONLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/ClientDisconnectEvent.h"

#include "../Players.h"

#include "../../networking/Server.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        class ClientDisconnectionListener : public gde::Listener<gdse::ClientDisconnectEvent>
        {
        private:
          gdn::Server* server;
          Players* players;

        public:
          ClientDisconnectionListener(gdn::Server*, Players*);
          ClientDisconnectionListener(const ClientDisconnectionListener&);
          ClientDisconnectionListener& operator=(const ClientDisconnectionListener&);

          void onEvent(gdse::ClientDisconnectEvent*) override;
        };
      }
    }
  }
}

#endif
