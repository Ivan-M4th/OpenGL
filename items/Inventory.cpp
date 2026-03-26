#include "Inventory.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace items
    {

      Inventory::Inventory()
      {
        width = 5;
        height = 3;
        generateStacks();
      }

      Inventory::Inventory(unsigned int width, unsigned int height)
      {
        this->width = width;
        this->height = height;
        generateStacks();
      }

      Inventory::~Inventory()
      {
        deleteStacks();
      }

      Inventory::Inventory(const Inventory& inventory)
      {
        width = inventory.width;
        height = inventory.height;
        generateStacks();
        int size = getSize();
        for(int i=0;i<size;i++)
        {
          *(itemStacks + i) = *(inventory.itemStacks + i);
        }
      }

      Inventory& Inventory::operator=(const Inventory& inventory)
      {
        deleteStacks();
        width = inventory.width;
        height = inventory.height;
        generateStacks();
        int size = getSize();
        for(int i=0;i<size;i++)
        {
          *(itemStacks + i) = *(inventory.itemStacks + i);
        }
        return *this;
      }

      void Inventory::deleteStacks()
      {
        if(itemStacks != NULL)
        {
          delete[] itemStacks;
        }
      }

      void Inventory::generateStacks()
      {
        int size = width*height;
        itemStacks = new ItemStack[size];
      }

      unsigned int Inventory::getSize() const
      {
        return width*height;
      }

      void Inventory::setItemStack(unsigned int i, const ItemStack& stack)
      {
        assert(i < getSize());
        *(itemStacks + i) = stack;
      }

      ItemStack* Inventory::getItemStack(unsigned int i) const
      {
        assert(i < getSize());
        return itemStacks + i;
      }

      unsigned int Inventory::getWidth() const
      {
        return width;
      }

      unsigned int Inventory::getHeight() const
      {
        return height;
      }
    }
  }
}
