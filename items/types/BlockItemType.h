#ifndef GD_ITEMS_TYPES_ITEMTYPE_H
#define GD_ITEMS_TYPES_ITEMTYPE_H

#include "../ItemType.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      namespace types
      {
        class BlockItemType : public ItemType
        {
        private:
          unsigned int materialId;

        public:
          BlockItemType(unsigned int, unsigned int, const gdu::String&);
          BlockItemType(const BlockItemType&);
          BlockItemType& operator=(const BlockItemType&);
          virtual ~BlockItemType();

          unsigned int getMaterialId() const;

          virtual unsigned int getTypeId() const override;
        };
      }
    }
  }
}

#endif
