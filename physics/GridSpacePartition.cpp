#include "GridSpacePartition.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      GridSpacePartition::GridSpacePartition(float gridSize, gdu::MemoryArray<gdmd::Tree>* trees, gdu::MemoryArray<gdmg::AABB>* aabbs)
      {
        assert(gridSize > 0.0);
        this->gridSize = gridSize;
        this->trees = trees;
        this->aabbs = aabbs;
      }

      GridSpacePartition::GridSpacePartition(const GridSpacePartition& grid)
      {
        gridSize = grid.gridSize;
        trees = grid.trees;
        aabbs = grid.aabbs;
        hashMap = grid.hashMap;
      }

      GridSpacePartition& GridSpacePartition::operator=(const GridSpacePartition& grid)
      {
        gridSize = grid.gridSize;
        trees = grid.trees;
        aabbs = grid.aabbs;
        hashMap = grid.hashMap;
        return *this;
      }

      void GridSpacePartition::add(int x, int y, int z, int objectId, int aabbId, ArrayList<GridTreeData>* gridTreeDatas)
      {
        gdm::Vector3i v(x, y, z);
        int* treeIndexPtr = hashMap.get(v);

        GridTreeData gridTreeData;
        gridTreeData.position = v;

        TreeData* treeData = &gridTreeData.treeData;

        if(treeIndexPtr == NULL)
        {
          int treeId = trees->genSlot();
          //set aabbs
          (*trees)[treeId].setAabbs(aabbs);

          treeData->treeId = treeId;
          hashMap.set(v, treeData->treeId);
        }
        else
        {
          treeData->treeId = *treeIndexPtr;
        }


        treeData->nodeId = (*trees)[treeData->treeId].insert(objectId, aabbId);

        gridTreeDatas->add(gridTreeData);
      }

      void GridSpacePartition::add(int objectId, int aabbId, ArrayList<GridTreeData>* gridTreeDatas)
      {
        gdmg::AABB* aabb = &(*aabbs)[aabbId];

        int px;
        int py;
        int pz;
        getGridCoords(aabb->minPos.getX(), aabb->minPos.getY(), aabb->minPos.getZ(), &px, &py, &pz);
        for(int x=px;x*gridSize<aabb->maxPos.getX();x++)
        {
          for(int y=py;y*gridSize<aabb->maxPos.getY();y++)
          {
            for(int z=pz;z*gridSize<aabb->maxPos.getZ();z++)
            {
              add(x, y, z, objectId, aabbId, gridTreeDatas);
            }
          }
        }
      }

      void GridSpacePartition::remove(GridTreeData* gridTreeData)
      {
        TreeData* treeData = &gridTreeData->treeData;

        int treeId = treeData->treeId;
        int nodeId = treeData->nodeId;

        //std::cout << "deleting grid tree data: " << treeId << " : " << aabbId << std::endl;
        gdmd::Tree* tree = &(*trees)[treeId];
        tree->remove(nodeId);
        //std::cout << "done removing from tree" << std::endl;

        if(tree->size() == 0)
        {
          std::cout << "deleting bounding tree at " << gridTreeData->position << std::endl;
          assert(hashMap.get(gridTreeData->position) != NULL);
          assert(*hashMap.get(gridTreeData->position) == treeId);
          hashMap.remove(gridTreeData->position);
          trees->free(treeId);
        }
      }

      void GridSpacePartition::remove(ArrayList<GridTreeData>* gridTreeDatas)
      {
        for(int i=0;i<gridTreeDatas->size();i++)
        {
          remove(&(*gridTreeDatas)[i]);
        }
        gridTreeDatas->clear();
      }

      int GridSpacePartition::getGridCoord(float x) const
      {
        int res = x/gridSize;
        if(x < 0.0)
        {
          res--;
        }
        return res;
      }

      void GridSpacePartition::getGridCoords(float x, float y, float z, int* gx, int* gy, int* gz) const
      {
        *gx = getGridCoord(x);
        *gy = getGridCoord(y);
        *gz = getGridCoord(z);
      }

      void GridSpacePartition::getCollisions(int objectIndex, const gdmg::AABB* aabb, gdu::LinkedHashList<gdm::UIntPair>* hashList) const
      {
        int gx;
        int gy;
        int gz;
        getGridCoords(aabb->minPos.getX(), aabb->minPos.getY(), aabb->minPos.getZ(), &gx, &gy, &gz);
        for(int xi = 0;xi<=1;xi++)
        {
          for(int yi=0;yi<=1;yi++)
          {
            for(int zi=0;zi<=1;zi++)
            {
              int* treeIndex = hashMap.get(gdm::Vector3i(gx + xi, gy + yi, gz + zi));
              if(treeIndex != NULL)
              {

                (*trees)[*treeIndex].getCollisions(objectIndex, aabb, hashList);
              }
            }
          }
        }
      }
    }
  }
}
