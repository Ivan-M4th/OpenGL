#ifndef GD_ITEMS_ITEMS_H
#define GD_ITEMS_ITEMS_H

#include "../gddef.h"

#include "ItemType.h"

#include "../graphics/TexturedMesh.h"

#include "../graphics/MeshModel.h"

namespace gt
{
  namespace doubovik
  {
    namespace items
    {
      void createItemTypes();
      void deleteItemTypes();
      ItemType* getItemType(unsigned int);
    }
  }
}

#endif
