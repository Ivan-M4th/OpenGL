#ifndef GD_CLIENT_LISTENERS_PLAYERSPAWNLISTENER_H
#define GD_CLIENT_LISTENERS_PLAYERSPAWNLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/PlayerSpawnEvent.h"

#include "../Players.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class PlayerSpawnListener : public gde::Listener<gdce::PlayerSpawnEvent>
        {
        private:
          Players* players;
        public:
          PlayerSpawnListener(Players*);
          PlayerSpawnListener(const PlayerSpawnListener&);
          PlayerSpawnListener& operator=(const PlayerSpawnListener&);

          void onEvent(gdce::PlayerSpawnEvent*) override;
        };
      }
    }
  }
}

#endif
