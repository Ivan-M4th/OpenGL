#ifndef GD_CLIENT_LISTENERS_PLAYERUPDATEPACKETLISTENER_H
#define GD_CLIENT_LISTENERS_PLAYERUPDATEPACKETLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/PlayerUpdatePacketReceiveEvent.h"

#include "../Players.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class PlayerUpdatePacketListener : public gde::Listener<gdce::PlayerUpdatePacketReceiveEvent>
        {
        private:
          Players* players;

        public:
          PlayerUpdatePacketListener(Players*);
          PlayerUpdatePacketListener(const PlayerUpdatePacketListener&);
          PlayerUpdatePacketListener& operator=(const PlayerUpdatePacketListener&);

          void onEvent(gdce::PlayerUpdatePacketReceiveEvent*) override;
        };
      }
    }
  }
}

#endif
