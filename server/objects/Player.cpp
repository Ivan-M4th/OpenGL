#include "Player.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace objects
      {
        Player::Player() : Character()
        {
          name = gdu::String("Player");
          selectedSlot = 0;

          inventory = gdi::Inventory(6, 30);
        }

        Player::Player(const Player& player) : Character(player)
        {
          selectedSlot = player.selectedSlot;
        }

        Player& Player::operator=(const Player& player)
        {
          Character::operator=(player);
          selectedSlot = player.selectedSlot;
          return *this;
        }

        void Player::setSelectedSlot(int selectedSlot)
        {
          this->selectedSlot = selectedSlot;
        }

        gdi::ItemStack* Player::getItemStackInRightHand() const
        {
          return inventory.getItemStack(selectedSlot);
        }
      }
    }
  }
}
