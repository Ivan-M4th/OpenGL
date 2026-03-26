#include "ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      ItemStack::ItemStack()
      {
        amount = 0;
      }

      ItemStack::ItemStack(unsigned int itemId, int amount)
      {
        item = Pointer<Item>(new Item(itemId), false);
        this->amount = amount;
      }

      ItemStack::ItemStack(const Pointer<Item>& item, int amount)
      {
        this->item = item;
        this->amount = amount;
      }

      ItemStack::ItemStack(const ItemStack& itemStack)
      {
        item = itemStack.item;
        amount = itemStack.amount;
      }

      ItemStack& ItemStack::operator=(const ItemStack itemStack)
      {
        item = itemStack.item;
        amount = itemStack.amount;
        return *this;
      }

      unsigned int ItemStack::getItemId() const
      {
        if(item.value() == NULL)
        {
          return 0;
        }
        return item.value()->getId();
      }

      bool ItemStack::isEmpty() const
      {
        return amount <= 0;
      }

      void ItemStack::clear()
      {
        item.deletePointer();
        amount = 0;
      }
    }
  }
}
