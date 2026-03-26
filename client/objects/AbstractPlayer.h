#ifndef GD_CLIENT_OBJECTS_ABSTRACTPLAYER_H
#define GD_CLIENT_OBJECTS_ABSTRACTPLAYER_H

#include "../../gddef.h"

#include "Character.h"

#include "../../utils/String.h"

#include "../../math/Vector3.h"
#include "../../math/Matrix4x4.h"

#include "../../items/ItemStack.h"

#include "../../graphics/animation/ArmatureAnimator.h"
#include "../../graphics/animation/JointLinker.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        class AbstractPlayer : public Character
        {
        private:
          gdga::ArmatureAnimator topBodyAnimator;
          gdga::ArmatureAnimator bottomBodyAnimator;
          gdga::JointLinker cameraLinker;
          gdga::JointLinker rightHandLinker;

          void generateArmatureData();
        public:
          AbstractPlayer();
          AbstractPlayer(const AbstractPlayer&);
          AbstractPlayer& operator=(const AbstractPlayer&);

          gdm::Matrix4x4 getCameraTransformation() const;
          gdm::Matrix4x4 getRightHandTransformation() const;
          void onItemEquip();
          void useItem();

          virtual gdi::ItemStack* getItemInRightHand();
          virtual void update(float) override;
        };
      }
    }
  }
}

#endif
