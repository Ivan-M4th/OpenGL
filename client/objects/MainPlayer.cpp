#include "MainPlayer.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        MainPlayer::MainPlayer()
        {
          inventory = gdi::Inventory(6, 30);
        }

        MainPlayer::MainPlayer(const MainPlayer& player) : AbstractPlayer(player), inventory(player.inventory)
        {

        }

        MainPlayer& MainPlayer::operator=(const MainPlayer& player)
        {
          AbstractPlayer::operator=(player);
          inventory = player.inventory;
          return *this;
        }

        void MainPlayer::setSelectedSlot(int selectedSlot)
        {
          this->selectedSlot = selectedSlot;
        }

        gdi::Inventory* MainPlayer::getInventory()
        {
          return &inventory;
        }

        gdi::ItemStack* MainPlayer::getItemInRightHand()
        {
          return inventory.getItemStack(selectedSlot);
        }

        void MainPlayer::update(float timePassed)
        {
          AbstractPlayer::update(timePassed);
        }
      }
    }
  }
}
