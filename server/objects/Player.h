#ifndef GD_SERVER_OBJECTS_PLAYER_H
#define GD_SERVER_OBJECTS_PLAYER_H

#include "../../gddef.h"

#include "Character.h"

#include "../../utils/String.h"

#include "../../math/Vector3.h"

#include "../../items/ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        class Player : public Character
        {
        protected:
          int selectedSlot;

        public:
          Player();
          Player(const Player&);
          Player& operator=(const Player&);

          void setSelectedSlot(int);
          gdi::ItemStack* getItemStackInRightHand() const;
        };
      }
    }
  }
}

#endif
