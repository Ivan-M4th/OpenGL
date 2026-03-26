#include "MainPlayerSetItemStackListener.h"

#include "../objects/MainPlayer.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        MainPlayerSetItemStackListener::MainPlayerSetItemStackListener(Players* players)
        {
          this->players = players;
        }

        MainPlayerSetItemStackListener::MainPlayerSetItemStackListener(const MainPlayerSetItemStackListener& listener)
        {
          players = listener.players;
        }

        MainPlayerSetItemStackListener& MainPlayerSetItemStackListener::operator=(const MainPlayerSetItemStackListener& listener)
        {
          players = listener.players;
          return *this;
        }

        void MainPlayerSetItemStackListener::onEvent(gdce::MainPlayerSetItemStackEvent* event)
        {
          unsigned int slot = event->getSlot();
          gdco::MainPlayer* player = players->getMainPlayer();
          if(player != NULL)
          {
            player->getInventory()->setItemStack(slot, *event->getItemStack());
          }
        }
      }
    }
  }
}
