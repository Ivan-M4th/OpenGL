#include "MainPlayerSetItemStackEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int MainPlayerSetItemStackEvent::getStaticType()
        {
          return gde::CLIENT_MAINPLAYER_SET_ITEMSTACK_EVENT;
        }

        MainPlayerSetItemStackEvent::MainPlayerSetItemStackEvent(unsigned int slot, const gdi::ItemStack* itemStack)
        {
          this->slot = slot;
          this->itemStack = itemStack;
        }

        MainPlayerSetItemStackEvent::MainPlayerSetItemStackEvent(const MainPlayerSetItemStackEvent& event)
        {
          slot = event.slot;
          itemStack = event.itemStack;
        }

        MainPlayerSetItemStackEvent& MainPlayerSetItemStackEvent::operator=(const MainPlayerSetItemStackEvent& event)
        {
          slot = event.slot;
          itemStack = event.itemStack;
          return *this;
        }

        unsigned int MainPlayerSetItemStackEvent::getSlot() const
        {
          return slot;
        }

        const gdi::ItemStack* MainPlayerSetItemStackEvent::getItemStack() const
        {
          return itemStack;
        }

        unsigned int MainPlayerSetItemStackEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
