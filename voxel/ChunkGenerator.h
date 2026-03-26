#ifndef GD_VOXEL_CHUNKGENERATOR_H
#define GD_VOXEL_CHUNKGENERATOR_H

#include "../gddef.h"

#include "../math/RandomGenerator.h"
#include "Chunk.h"
#include "Block.h"

#include "../server/GameDataManager.h"
#include "../server/voxel/ChunkStructures.h"
#include "../server/voxel/ChunkCreatures.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class ChunkGenerator
      {
      private:
        gdm::RandomGenerator random;
        gds::GameDataManager* gameDataManager;

      public:
        ChunkGenerator(gds::GameDataManager*);
        ChunkGenerator(const ChunkGenerator&);
        ChunkGenerator& operator=(const ChunkGenerator&);

        void createTree(int, int, int, gdsv::ChunkStructures*);
        void createBoar(int, int, int, int, int, int, ArrayList<int>*);
        void generateBlock(int, int, int, int, int, int, Block*, gdsv::ChunkStructures*, gdsv::ChunkCreatures*);
        void generateChunk(int, int, int, Chunk*, gdsv::ChunkStructures*, gdsv::ChunkCreatures*);
      };
    }
  }
}

#endif
