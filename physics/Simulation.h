#ifndef GD_PHYSICS_SIMULATION_H
#define GD_PHYSICS_SIMULATION_H

#include "../gddef.h"

#include "ObjectSimulationData.h"
#include "GridSpacePartition.h"

#include "../math/UIntPair.h"
#include "../math/Vector3.h"
#include "../math/Vector2i.h"
#include "../math/dbvt/TreeIterator.h"

#include "../utils/MemoryArray.h"
#include "../utils/ArrayList.h"
#include "../utils/LinkedHashList.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      class Simulation
      {
      private:
        gdu::MemoryArray<ObjectSimulationData>* objects;
        gdu::MemoryArray<gdmd::Tree>* trees;
        gdu::MemoryArray<gdmg::AABB>* aabbs;

        GridSpacePartition* terrainGrid;
        GridSpacePartition* objectsGrid;

        void addToObjectsGrid(int); //id
        void removeFromObjectGrid(int); //id

        void updateObject(float, Object*);
        void updateObjects(float, gdu::LinkedHashList<int>*);

        void getObjectCollisions(int, gdu::LinkedHashList<gdm::UIntPair>*) const;
        void getObjectsCollisions(gdu::LinkedHashList<gdm::UIntPair>*, gdu::LinkedHashList<int>*) const;

        void getCollisionResponseValues(Object*, Object*, const gdm::Vector3&, const gdm::Vector3&, gdm::Vector3*, gdm::Vector3*, gdm::Vector3*, gdm::Vector3*) const;
        void getStaticCollisionResponseValues(bool, Object*, const gdm::Vector3&, const gdm::Vector3&, gdm::Vector3*, gdm::Vector3*) const;
        void checkCollision(Object*, Object*);
      public:
        Simulation(gdu::MemoryArray<ObjectSimulationData>*, gdu::MemoryArray<gdmd::Tree>*, gdu::MemoryArray<gdmg::AABB>*, GridSpacePartition*, GridSpacePartition*);
        Simulation(const Simulation&);
        Simulation& operator=(const Simulation&);

        int getMainTreeId() const;

        void createAABB(int, const gdm::Vector3&);
        bool updateAABB(int, const gdm::Vector3&); //updated?

        void add(int);
        void addTerrain(int, int, int, int);
        void addStructure(int);
        void remove(int);

        void resolveObjectCollisions(const gdu::LinkedHashList<gdm::UIntPair>*);
        void update(float, gdu::LinkedHashList<int>*);
      };
    }
  }
}

#endif
