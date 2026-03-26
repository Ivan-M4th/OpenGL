#include "Item.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      Item::Item()
      {
        id = 0;
      }

      Item::Item(unsigned int id)
      {
        this->id = id;
      }

      Item::Item(const Item& item)
      {
        id = item.id;
      }

      Item& Item::operator=(const Item& item)
      {
        id = item.id;
        return *this;
      }

      unsigned int Item::getId() const
      {
        return id;
      }
    }
  }
}
