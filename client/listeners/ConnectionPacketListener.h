#ifndef GD_CLIENT_LISTENERS_CONNECTIONPACKETLISTENER_H
#define GD_CLIENT_LISTENERS_CONNECTIONPACKETLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/ConnectionPacketReceiveEvent.h"

#include "../../networking/Client.h"

#include "../Players.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class ConnectionPacketListener : public gde::Listener<gdce::ConnectionPacketReceiveEvent>
        {
        private:
          gdn::Client* client;
          Players* players;

        public:
          ConnectionPacketListener(gdn::Client*, Players*);
          ConnectionPacketListener(const ConnectionPacketListener&);
          ConnectionPacketListener& operator=(const ConnectionPacketListener&);

          void onEvent(gdce::ConnectionPacketReceiveEvent*) override;
        };
      }
    }
  }
}

#endif
