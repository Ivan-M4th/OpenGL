#ifndef GD_CLIENT_OBJECTS_MAINPLAYER_H
#define GD_CLIENT_OBJECTS_MAINPLAYER_H

#include "../../gddef.h"

#include "AbstractPlayer.h"

#include "../../utils/String.h"

#include "../../math/Vector3.h"

#include "../../items/Inventory.h"
#include "../../items/ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        class MainPlayer : public AbstractPlayer
        {
        protected:
          int selectedSlot = 0;

          gdi::Inventory inventory;
        public:
          MainPlayer();
          MainPlayer(const MainPlayer&);
          MainPlayer& operator=(const MainPlayer&);

          void setSelectedSlot(int);
          gdi::Inventory* getInventory();

          virtual gdi::ItemStack* getItemInRightHand() override;
          virtual void update(float) override;
        };
      }
    }
  }
}

#endif
