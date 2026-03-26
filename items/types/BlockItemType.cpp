#include "BlockItemType.h"

#include "../../gddef.h"

#include "../../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      namespace types
      {
        BlockItemType::BlockItemType(unsigned int materialId, unsigned int stackSize, const gdu::String& name) : ItemType(stackSize, 3, name)
        {
          this->materialId = materialId;
        }

        BlockItemType::BlockItemType(const BlockItemType& type) : ItemType(type)
        {
          materialId = type.materialId;
        }

        BlockItemType& BlockItemType::operator=(const BlockItemType& type)
        {
          ItemType::operator=(type);
          materialId = type.materialId;
          return *this;
        }

        BlockItemType::~BlockItemType()
        {

        }

        unsigned int BlockItemType::getMaterialId() const
        {
          return materialId;
        }

        unsigned int BlockItemType::getTypeId() const
        {
          return BLOCK_TYPE;
        }
      }
    }
  }
}
