#ifndef GD_ITEMS_ITEMTYPE_H
#define GD_ITEMS_ITEMTYPE_H

#include "../gddef.h"

#include "../utils/String.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      extern const unsigned int DEFAULT;
      extern const unsigned int BLOCK_TYPE;

      class ItemType
      {
      protected:
        unsigned int stackSize;
        unsigned int holderState;
        gdu::String name;

      public:
        ItemType();
        ItemType(unsigned int, unsigned int, const gdu::String&);
        ItemType(const gdu::String&);
        ItemType(const ItemType&);
        ItemType& operator=(const ItemType&);
        virtual ~ItemType();

        unsigned int getHolderState() const;
        const gdu::String& getName() const;

        virtual unsigned int getTypeId() const;
      };
    }
  }
}

#endif
