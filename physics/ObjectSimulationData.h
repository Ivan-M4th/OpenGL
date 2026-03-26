#ifndef GD_PHYSICS_OBJECTSIMULATIONDATA_H
#define GD_PHYSICS_OBJECTSIMULATIONDATA_H

#include "../gddef.h"

#include "Object.h"
#include "TreeData.h"
#include "GridTreeData.h"

#include "../math/geometry/AABB.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      struct ObjectSimulationData
      {
        Object* object;
        int aabbId = -1;

        ArrayList<GridTreeData> terrainGridDatas;
        ArrayList<GridTreeData> objectsGridDatas;
      };
    }
  }
}

#endif
