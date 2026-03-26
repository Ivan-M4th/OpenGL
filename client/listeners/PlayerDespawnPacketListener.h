#ifndef GD_CLIENT_LISTENERS_PLAYERDESPAWNPACKETLISTENER_H
#define GD_CLIENT_LISTENERS_PLAYERDESPAWNPACKETLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/PlayerDespawnPacketReceiveEvent.h"

#include "../Players.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class PlayerDespawnPacketListener : public gde::Listener<gdce::PlayerDespawnPacketReceiveEvent>
        {
        private:
          Players* players;

        public:
          PlayerDespawnPacketListener(Players*);
          PlayerDespawnPacketListener(const PlayerDespawnPacketListener&);
          PlayerDespawnPacketListener& operator=(const PlayerDespawnPacketListener&);

          void onEvent(gdce::PlayerDespawnPacketReceiveEvent*);
        };
      }
    }
  }
}

#endif
