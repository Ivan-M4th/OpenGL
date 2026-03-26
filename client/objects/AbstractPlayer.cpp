#include "AbstractPlayer.h"

#include "../../data/Assets.h"

#include "../../graphics/animation/Joint.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        AbstractPlayer::AbstractPlayer() : Character()
        {
          name = gdu::String("Player");
          armature = *gdd::getArmature(gdd::PLAYER_ARMATURE);

          gdga::Joint* rootJoint = armature.getRoot();
          gdga::Joint* bottomJoint = armature.getJoint("Colonne_vertebrale_5");
          gdga::Joint* topJoint = armature.getJoint("Colonne_vertebrale_1");

          ArrayList<unsigned int> bottomJointIds;
          ArrayList<unsigned int> topJointIds;
          bottomJointIds.add(rootJoint->getIndex());
          bottomJoint->getChildrenIds(&bottomJointIds);
          topJoint->getChildrenIds(&topJointIds);

          topBodyAnimator.setJointIds(topJointIds);
          bottomBodyAnimator.setJointIds(bottomJointIds);

          generateArmatureData();

          physicalInformation.mass = 75.0;
          physicalInformation.setBoxIntertiaMatrix(1.0, 2.0, 1.0);

          topBodyAnimator.setAnimation(gdd::getAnimation(gdd::PLAYER_IDLE_ANIMATION));
          bottomBodyAnimator.setAnimation(gdd::getAnimation(gdd::PLAYER_IDLE_ANIMATION));
        }

        AbstractPlayer::AbstractPlayer(const AbstractPlayer& player) : Character(player), topBodyAnimator(player.topBodyAnimator), bottomBodyAnimator(player.bottomBodyAnimator)
        {
          generateArmatureData();
        }

        AbstractPlayer& AbstractPlayer::operator=(const AbstractPlayer& player)
        {
          Character::operator=(player);
          topBodyAnimator = player.topBodyAnimator;
          bottomBodyAnimator = player.bottomBodyAnimator;
          generateArmatureData();
          return *this;
        }

        void AbstractPlayer::generateArmatureData()
        {
          gdga::Joint* cameraJoint = armature.getJoint("Camera");
          cameraLinker.joint = cameraJoint;

          gdga::Joint* rightHandJoint = armature.getJoint("Objet_main_droite");
          rightHandLinker.joint = rightHandJoint;
        }

        gdm::Matrix4x4 AbstractPlayer::getCameraTransformation() const
        {
          return cameraLinker.getTransformation();
        }

        gdm::Matrix4x4 AbstractPlayer::getRightHandTransformation() const
        {
          return rightHandLinker.getTransformation();
        }

        void AbstractPlayer::onItemEquip()
        {
          if(getItemInRightHand()->isEmpty())
          {
            topBodyAnimator.setAnimation(bottomBodyAnimator.getAnimation());
          }
          else
          {
            //unsigned int animationId = gdd::getItemHolderAnimationsId(getItemInRightHand()->getItemId());
            //topBodyAnimator.setAnimation(gdd::getCreatureAnimations(gdd::PLAYER_ANIMATIONS)[animationId].hold);
          }
        }

        void AbstractPlayer::useItem()
        {
          if(!getItemInRightHand()->isEmpty())
          {
            //unsigned int animationId = gdd::getItemHolderAnimationsId(getItemInRightHand()->getItemId());
            //topBodyAnimator.setAnimation(gdd::getCreatureAnimations(gdd::PLAYER_ANIMATIONS)[animationId].use);
          }
        }

        gdi::ItemStack* AbstractPlayer::getItemInRightHand()
        {
          return NULL;
        }

        void AbstractPlayer::update(float timePassed)
        {
          Character::update(timePassed);

          float xzSpeed = speed.getX()*speed.getX() + speed.getZ()*speed.getZ();
          if(xzSpeed > 1.0)
          {
            bottomBodyAnimator.setAnimation(gdd::getAnimation(gdd::PLAYER_RUN_ANIMATION));
          }
          else
          {
            bottomBodyAnimator.setAnimation(gdd::getAnimation(gdd::PLAYER_IDLE_ANIMATION));
          }

          gdi::ItemStack* itemStack = getItemInRightHand();
          if(!itemStack->isEmpty())
          {
            if(topBodyAnimator.hasPlayedOnce())
            {
              //unsigned int animationId = gdd::getItemHolderAnimationsId(itemStack->getItemId());
              //topBodyAnimator.setAnimation(gdd::getCreatureAnimations(gdd::PLAYER_ANIMATIONS)[animationId].hold);
            }
          }
          else
          {
            topBodyAnimator.setAnimation(bottomBodyAnimator.getAnimation());
          }

          topBodyAnimator.update(timePassed);
          bottomBodyAnimator.update(timePassed);

          gdga::JointPose pose[armature.getJointAmount()];
          topBodyAnimator.getPose(pose);
          bottomBodyAnimator.getPose(pose);

          armature.applyPose(pose);
        }
      }
    }
  }
}
