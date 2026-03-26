#include "ItemType.h"

#include "../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      const unsigned int DEFAULT = 0;
      const unsigned int BLOCK_TYPE = 1;

      ItemType::ItemType()
      {
        name = gdu::String("NULL type");
        stackSize = 1;
        holderState = 0;
      }

      ItemType::ItemType(unsigned int stackSize, unsigned int holderState, const gdu::String& name)
      {
        this->stackSize = stackSize;
        this->holderState = holderState;
        this->name = name;
      }

      ItemType::ItemType(const gdu::String& name)
      {
        this->name = name;
        stackSize = 100;
        holderState = 0;
      }

      ItemType::ItemType(const ItemType& itemType)
      {
        stackSize = itemType.stackSize;
        holderState = itemType.holderState;
        name = itemType.name;
      }

      ItemType& ItemType::operator=(const ItemType& itemType)
      {
        stackSize = itemType.stackSize;
        holderState = itemType.holderState;
        name = itemType.name;
        return *this;
      }

      ItemType::~ItemType()
      {

      }

      unsigned int ItemType::getHolderState() const
      {
        return holderState;
      }

      const gdu::String& ItemType::getName() const
      {
        return name;
      }

      unsigned int ItemType::getTypeId() const
      {
        return DEFAULT;
      }
    }
  }
}
