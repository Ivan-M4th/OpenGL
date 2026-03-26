#ifndef GD_ITEMS_INVENTORY_H
#define GD_ITEMS_INVENTORY_H

#include "ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class Inventory
      {
      private:
        unsigned int width;
        unsigned int height;
        ItemStack* itemStacks;

        void deleteStacks();
        void generateStacks();
      public:
        Inventory();
        Inventory(unsigned int, unsigned int);
        ~Inventory();
        Inventory(const Inventory&);
        Inventory& operator=(const Inventory&);

        unsigned int getSize() const;
        void setItemStack(unsigned int, const ItemStack&);
        ItemStack* getItemStack(unsigned int) const;
        unsigned int getWidth() const;
        unsigned int getHeight() const;
      };
    }
  }
}

#endif
