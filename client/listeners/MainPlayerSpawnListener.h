#ifndef GD_CLIENT_LISTENERS_MAINPLAYERSPAWNLISTENER_H
#define GD_CLIENT_LISTENERS_MAINPLAYERSPAWNLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/MainPlayerSpawnEvent.h"

#include "../../items/PlayerInventoryFrame.h"
#include "../../items/InventoryDisplayBelt.h"

#include "../Players.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class MainPlayerSpawnListener : public gde::Listener<gdce::MainPlayerSpawnEvent>
        {
        private:
          Players* players;
          gdi::PlayerInventoryFrame* inventoryFrame;
          gdi::InventoryDisplayBelt* inventoryDisplayBelt;

        public:
          MainPlayerSpawnListener(Players*, gdi::PlayerInventoryFrame*, gdi::InventoryDisplayBelt*);
          MainPlayerSpawnListener(const MainPlayerSpawnListener&);
          MainPlayerSpawnListener& operator=(const MainPlayerSpawnListener&);

          void onEvent(gdce::MainPlayerSpawnEvent*) override;
        };
      }
    }
  }
}

#endif
