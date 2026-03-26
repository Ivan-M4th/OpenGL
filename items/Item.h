#ifndef GD_ITEMS_ITEM_H
#define GD_ITEMS_ITEM_H

#include "../gddef.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      class Item
      {
      private:
        unsigned int id;

      public:
        Item();
        Item(unsigned int);
        Item(const Item&);
        Item& operator=(const Item&);

        unsigned int getId() const;
      };
    }
  }
}

#endif
