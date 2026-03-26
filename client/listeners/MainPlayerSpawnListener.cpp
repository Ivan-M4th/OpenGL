#include "MainPlayerSpawnListener.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        MainPlayerSpawnListener::MainPlayerSpawnListener(Players* players, gdi::PlayerInventoryFrame* inventoryFrame, gdi::InventoryDisplayBelt* inventoryDisplayBelt)
        {
          this->players = players;
          this->inventoryFrame = inventoryFrame;
          this->inventoryDisplayBelt = inventoryDisplayBelt;
        }

        MainPlayerSpawnListener::MainPlayerSpawnListener(const MainPlayerSpawnListener& listener)
        {
          players = listener.players;
          inventoryFrame = listener.inventoryFrame;
          inventoryDisplayBelt = listener.inventoryDisplayBelt;
        }

        MainPlayerSpawnListener& MainPlayerSpawnListener::operator=(const MainPlayerSpawnListener& listener)
        {
          players = listener.players;
          inventoryFrame = listener.inventoryFrame;
          inventoryDisplayBelt = listener.inventoryDisplayBelt;
          return *this;
        }

        void MainPlayerSpawnListener::onEvent(gdce::MainPlayerSpawnEvent* event)
        {
          std::cout << "main player spawning..." << std::endl;
          players->setMainPlayer(event->getPlayerPointer());
          inventoryFrame->setInventories(players->getMainPlayer()->getInventory());
          inventoryDisplayBelt->setInventory(players->getMainPlayer()->getInventory());
          std::cout << "main player spawned!" << std::endl;
        }
      }
    }
  }
}
