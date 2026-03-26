#ifndef GD_CLIENT_OBJECTS_PLAYER_H
#define GD_CLIENT_OBJECTS_PLAYER_H

#include "../../gddef.h"

#include "AbstractPlayer.h"

#include "../../utils/String.h"

#include "../../math/Vector3.h"

#include "../../items/ItemStack.h"

#include "../../graphics/animation/Armature.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        class Player : public AbstractPlayer
        {
        public:
          gdi::ItemStack itemStackInRightHand;

          Player();
          Player(const Player&);
          Player& operator=(const Player&);

          virtual gdi::ItemStack* getItemInRightHand() override;
          virtual void update(float) override;
        };
      }
    }
  }
}

#endif
