#include "ItemTypes.h"

#include <cassert>

#include "types/BlockItemType.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      ItemTypes::ItemTypes(unsigned int amount)
      {
        this->amount = amount;
        itemTypes = new Pointer<ItemType>[amount];
      }

      ItemTypes::ItemTypes(const ItemTypes& types)
      {
        amount = types.amount;
        itemTypes = new Pointer<ItemType>[amount];
        for(unsigned int i=0;i<amount;i++)
        {
          *(itemTypes + i) = *(types.itemTypes + i);
        }
      }

      ItemTypes& ItemTypes::operator=(const ItemTypes& types)
      {
        deleteData();
        amount = types.amount;
        itemTypes = new Pointer<ItemType>[amount];
        for(unsigned int i=0;i<amount;i++)
        {
          *(itemTypes + i) = *(types.itemTypes + i);
        }
        return *this;
      }

      ItemTypes::~ItemTypes()
      {
        deleteData();
      }

      void ItemTypes::deleteData()
      {
        delete[] itemTypes;
      }

      ItemType* ItemTypes::getUnsafeItemType(unsigned int id) const
      {
        assert(id < amount);
        return (itemTypes + id)->value();
      }

      ItemType* ItemTypes::getItemType(unsigned int id) const
      {
        ItemType* itemType = getUnsafeItemType(id);
        assert(itemType != NULL);
        return itemType;
      }

      void ItemTypes::setItemType(unsigned int id, const Pointer<ItemType>& itemType)
      {
        assert(id < amount);
        *(itemTypes + id) = itemType;
      }

      void ItemTypes::setBlockItemType(unsigned int id, unsigned int materialId, unsigned int stackSize, const gdu::String& name)
      {
        Pointer<ItemType> blockType(new gdit::BlockItemType(materialId, stackSize, name), false);
        setItemType(id, blockType);
      }
    }
  }
}
