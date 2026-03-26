#ifndef GD_VOXEL_CHUNKMESHBUILDER_H
#define GD_VOXEL_CHUNKMESHBUILDER_H

#include "Chunk.h"
#include "ChunkMesh.h"
#include "BlockBuilder.h"
#include "Material.h"
#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class ChunkMeshBuilder
      {
      private:
        ArrayList<float> positions;
        ArrayList<float> uvs;
        ArrayList<float> normals;
        ArrayList<unsigned int> indices;

        int vertexAmount;
        BlockBuilder* blockBuilder;
        Chunk* chunk;
        ChunkMesh* chunkMesh;
        int cx;
        int cy;
        int cz;
        Chunk* xm;
        Chunk* xp;
        Chunk* ym;
        Chunk* yp;
        Chunk* zm;
        Chunk* zp;

        Block* getTopBlock(unsigned int, unsigned int, unsigned int) const;
        Block* getBottomBlock(unsigned int, unsigned int, unsigned int) const;
        Block* getFrontBlock(unsigned int, unsigned int, unsigned int) const;
        Block* getBackBlock(unsigned int, unsigned int, unsigned int) const;
        Block* getRightBlock(unsigned int, unsigned int, unsigned int) const;
        Block* getLeftBlock(unsigned int, unsigned int, unsigned int) const;

        bool isVisible(Block*) const;

        void buildTopFace(unsigned int, unsigned int, unsigned int, Material*);
        void buildBottomFace(unsigned int, unsigned int, unsigned int, Material*);
        void buildFrontFace(unsigned int, unsigned int, unsigned int, Material*);
        void buildBackFace(unsigned int, unsigned int, unsigned int, Material*);
        void buildRightFace(unsigned int, unsigned int, unsigned int, Material*);
        void buildLeftFace(unsigned int, unsigned int, unsigned int, Material*);

        void buildBlockMesh(unsigned int, unsigned int, unsigned int);
      public:
        ChunkMeshBuilder(BlockBuilder*, Chunk*, ChunkMesh*, int, int, int, Chunk*, Chunk*, Chunk*, Chunk*, Chunk*, Chunk*);
        ChunkMeshBuilder(const ChunkMeshBuilder&);
        ChunkMeshBuilder& operator=(const ChunkMeshBuilder&);

        void calculateMesh();
        void loadData();
        void clear();

        void buildMesh();
      };
    }
  }
}

#endif
