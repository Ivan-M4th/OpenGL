#ifndef GD_ITEMS_ITEMSTACK_H
#define GD_ITEMS_ITEMSTACK_H

#include "../gddef.h"

#include "Item.h"

#include "../utils/Pointer.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class ItemStack
      {
      private:
        Pointer<Item> item;

      public:
        int amount;

        ItemStack();
        ItemStack(unsigned int, int);
        ItemStack(const Pointer<Item>&, int);
        ItemStack(const ItemStack&);
        ItemStack& operator=(const ItemStack);

        unsigned int getItemId() const;
        bool isEmpty() const;
        void clear();
      };
    }
  }
}

#endif
