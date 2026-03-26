#ifndef GD_VOXEL_TERRAIN_H
#define GD_VOXEL_TERRAIN_H

#include "../gddef.h"

#include "Region.h"
#include "Chunk.h"
#include "Block.h"
#include "ChunkGenerator.h"

#include "../utils/ArrayList.h"
#include "../utils/MemoryArray.h"
#include "../utils/LinkedHashMap.h"
#include "../utils/LinkedHashList.h"

#include "../math/Vector3i.h"

#include "../server/GameDataManager.h"
#include "../server/ObjectsToUpdate.h"
#include "../server/objects/Player.h"
#include "../server/objects/Tree.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class Terrain
      {
      private:
        gdu::LinkedHashMap<gdm::Vector3i, int> regionIds;
        gdu::MemoryArray<RegionNode> nodes;
        gdu::MemoryArray<Region> regions;

        gds::GameDataManager* gameDataManager;
        ChunkGenerator* chunkGenerator;

      public:
        Terrain(gds::GameDataManager*, ChunkGenerator*);
        Terrain(const Terrain&);
        Terrain& operator=(const Terrain&);

        int loadedRegionsSize() const;

        Region* getRegion(const gdm::Vector3i&) const; //region coords
        Region* getRegionAtChunk(int, int, int) const; //chunk coords
        RegionNode* getChunk(int, int, int) const; //chunk coords
        void updateChunk(int, int, int); //chunk coords
        void updateChunkAtBlock(int, int, int); //block coords
        Block* getBlock(int, int, int) const; //block coords

        RegionNode* generateChunk(int, int, int);
        void loadRegion(const gdm::Vector3i&);
        void unLoadRegion(const gdm::Vector3i&);

        bool isNear(const gdm::Vector3i&, const gdm::Vector3i&, int) const;
        bool isNearPlayer(const gdm::Vector3i&, gdso::Player*, int) const;
        bool isFarRegion(const ArrayList<gdso::Player*>&, const gdm::Vector3i&) const;
        void removeFarRegions(const ArrayList<gdso::Player*>&);

        void loadRegionsNear(const gdm::Vector3i&, int);
        void loadNearRegions(const ArrayList<gdso::Player*>&);

        void update(const ArrayList<gdso::Player*>&);

        void getObjectsToUpdate(const gdm::Vector3i&, int, gds::ObjectsToUpdate*) const;
        void getObjectsToUpdate(const ArrayList<gdso::Player*>*, gds::ObjectsToUpdate*) const;

        void removeBoar(const gdm::Vector3i&, int);
        bool addBoar(const gdm::Vector3i&, int); //sucess?
      };
    }
  }
}

#endif
