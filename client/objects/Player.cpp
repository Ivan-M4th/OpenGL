#include "Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        Player::Player() : AbstractPlayer()
        {

        }

        Player::Player(const Player& player) : AbstractPlayer(player)
        {

        }

        Player& Player::operator=(const Player& player)
        {
          AbstractPlayer::operator=(player);
          return *this;
        }

        gdi::ItemStack* Player::getItemInRightHand()
        {
          return &itemStackInRightHand;
        }

        void Player::update(float timePassed)
        {
          AbstractPlayer::update(timePassed);
        }
      }
    }
  }
}
