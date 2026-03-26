#ifndef GD_PHYSICS_GRIDTREEDATA_H
#define GD_PHYSICS_GRIDTREEDATA_H

#include "../gddef.h"

#include "TreeData.h"

#include "../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      struct GridTreeData
      {
        TreeData treeData;
        gdm::Vector3i position;
      };
    }
  }
}

#endif
