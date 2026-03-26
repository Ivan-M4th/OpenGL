#include "MainPlayerSwapItemStacksEvent.h"

#include "Events.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int MainPlayerSwapItemStacksEvent::getStaticType()
        {
          return MAIN_PLAYER_SWAP_ITEMSTACKS_EVENT;
        }

        MainPlayerSwapItemStacksEvent::MainPlayerSwapItemStacksEvent(unsigned int index1, unsigned int index2)
        {
          this->index1 = index1;
          this->index2 = index2;
        }

        MainPlayerSwapItemStacksEvent::MainPlayerSwapItemStacksEvent(const MainPlayerSwapItemStacksEvent& event)
        {
          index1 = event.index1;
          index2 = event.index2;
        }

        MainPlayerSwapItemStacksEvent& MainPlayerSwapItemStacksEvent::operator=(const MainPlayerSwapItemStacksEvent& event)
        {
          index1 = event.index1;
          index2 = event.index2;
          return *this;
        }

        unsigned int MainPlayerSwapItemStacksEvent::getIndex1() const
        {
          return index1;
        }

        unsigned int MainPlayerSwapItemStacksEvent::getIndex2() const
        {
          return index2;
        }

        unsigned int MainPlayerSwapItemStacksEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
