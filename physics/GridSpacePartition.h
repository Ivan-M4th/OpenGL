#ifndef GD_PHYSICS_GRIDSPACEPARTITION_H
#define GD_PHYSICS_GRIDSPACEPARTITION_H

#include "../gddef.h"

#include "GridTreeData.h"

#include "../utils/HashMap.h"
#include "../utils/MemoryArray.h"
#include "../utils/LinkedHashList.h"

#include "../math/Vector3i.h"
#include "../math/UIntPair.h"
#include "../math/dbvt/Tree.h"
#include "../math/geometry/AABB.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      class GridSpacePartition
      {
        friend class Simulation;

      private:
        float gridSize;
        gdu::MemoryArray<gdmd::Tree>* trees;
        gdu::MemoryArray<gdmg::AABB>* aabbs;

        gdu::HashMap<gdm::Vector3i, int> hashMap;

        int getGridCoord(float) const;
        void getGridCoords(float, float, float, int*, int*, int*) const;
      public:
        GridSpacePartition(float, gdu::MemoryArray<gdmd::Tree>*, gdu::MemoryArray<gdmg::AABB>*);
        GridSpacePartition(const GridSpacePartition&);
        GridSpacePartition& operator=(const GridSpacePartition&);

        void add(int, int, int, int, int, ArrayList<GridTreeData>*);
        void add(int, int, ArrayList<GridTreeData>*); //objectId, aabbId

        void remove(GridTreeData*);
        void remove(ArrayList<GridTreeData>*);

        void getCollisions(int, const gdmg::AABB*, gdu::LinkedHashList<gdm::UIntPair>*) const;
      };
    }
  }
}

#endif
