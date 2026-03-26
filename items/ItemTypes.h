#ifndef GD_ITEMS_ITEMTYPES_H
#define GD_ITEMS_ITEMTYPES_H

#include "ItemType.h"

#include "../utils/Pointer.h"
#include "../utils/String.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class ItemTypes
      {
      private:
        unsigned int amount;
        Pointer<ItemType>* itemTypes;

        void deleteData();
      public:
        ItemTypes(unsigned int);
        ItemTypes(const ItemTypes&);
        ItemTypes& operator=(const ItemTypes&);
        ~ItemTypes();

        ItemType* getUnsafeItemType(unsigned int) const;
        ItemType* getItemType(unsigned int) const;

        void setItemType(unsigned int, const Pointer<ItemType>&);
        void setBlockItemType(unsigned int, unsigned int, unsigned int, const gdu::String&);
      };
    }
  }
}

#endif
