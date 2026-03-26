#ifndef GD_SERVER_LISTENERS_REQUESTSPAWNPACKETLISTENER_H
#define GD_SERVER_LISTENERS_REQUESTSPAWNPACKETLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/RequestSpawnPacketReceiveEvent.h"

#include "../../networking/Server.h"

#include "../Players.h"

#include "../../items/ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        class RequestSpawnPacketListener : public gde::Listener<gdse::RequestSpawnPacketReceiveEvent>
        {
        private:
          gdn::Server* server;
          Players* players;

          void setItemStack(unsigned int, unsigned int, const gdi::ItemStack&);
        public:
          RequestSpawnPacketListener(gdn::Server*, Players*);
          RequestSpawnPacketListener(const RequestSpawnPacketListener&);
          RequestSpawnPacketListener& operator=(const RequestSpawnPacketListener&);

          void onEvent(gdse::RequestSpawnPacketReceiveEvent*) override;
        };
      }
    }
  }
}

#endif
