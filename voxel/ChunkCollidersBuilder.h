#ifndef GD_VOXEL_CHUNKCOLLIDERSBUILDER_H
#define GD_VOXEL_CHUNKCOLLIDERSBUILDER_H

#include "../gddef.h"

#include "Chunk.h"

#include "../utils/ArrayList.h"

#include "../math/geometry/ConvexPolyhedron.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class ChunkCollidersBuilder
      {
      private:
        bool* tested;
        Chunk* chunk;
        int cx;
        int cy;
        int cz;

        ArrayList<gdmg::ConvexPolyhedron> colliders;

        void deleteData();
        void clearTestedBlocks();
        bool& getTested(unsigned int, unsigned int, unsigned int) const;

        void tryExpandX(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool*) const;
        void tryExpandY(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool*) const;
        void tryExpandZ(unsigned int, unsigned int, unsigned int, unsigned int, unsigned int, bool*) const;
        void buildCollider(unsigned int, unsigned int, unsigned int);
      public:
        ChunkCollidersBuilder(Chunk*, int, int, int);
        ChunkCollidersBuilder(const ChunkCollidersBuilder&);
        ChunkCollidersBuilder& operator=(const ChunkCollidersBuilder&);
        ~ChunkCollidersBuilder();

        void buildColliders();
        void loadColliders(ChunkCollider*) const;
      };
    }
  }
}

#endif
