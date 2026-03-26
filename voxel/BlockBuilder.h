#ifndef GD_VOXEL_BLOCKBUILDER_H
#define GD_VOXEL_BLOCKBUILDER_H

#include "../gddef.h"

#include "TerrainTexture.h"
#include "../utils/ArrayList.h"
#include "../graphics/Mesh.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class BlockBuilder
      {
      private:
        float FACE_TOP[12] = {0.0,1.0,0.0, 0.0,1.0,1.0, 1.0,1.0,1.0, 1.0,1.0,0.0};
        float FACE_BOTTOM[12] = {0.0,0.0,1.0, 0.0,0.0,0.0, 1.0,0.0,0.0, 1.0,0.0,1.0};

        float FACE_FRONT[12] = {1.0,1.0,0.0, 1.0,0.0,0.0, 0.0,0.0,0.0, 0.0,1.0,0.0};
        float FACE_BACK[12] = {0.0,1.0,1.0, 0.0,0.0,1.0, 1.0,0.0,1.0, 1.0,1.0,1.0};

        float FACE_RIGHT[12] = {1.0,1.0,1.0, 1.0,0.0,1.0, 1.0,0.0,0.0, 1.0,1.0,0.0};
        float FACE_LEFT[12] = {0.0,1.0,0.0, 0.0,0.0,0.0, 0.0,0.0,1.0, 0.0,1.0,1.0};

        unsigned int INDICES[6] = {0,1,2,2,3,0};

        TerrainTexture* texture;
        int x;
        int y;
        int z;

        void addFace(const float*, ArrayList<float>*, int*, ArrayList<unsigned int>*) const;
        void addUVs(int, ArrayList<float>*) const;
        void addNormals(float, float, float, ArrayList<float>*) const;

      public:
        BlockBuilder(TerrainTexture*);
        BlockBuilder(const BlockBuilder&);
        BlockBuilder& operator=(const BlockBuilder&);

        void addTopFace(int, ArrayList<float>*, int*, ArrayList<float>*, ArrayList<float>*, ArrayList<unsigned int>*) const;
        void addBottomFace(int, ArrayList<float>*, int*, ArrayList<float>*, ArrayList<float>*, ArrayList<unsigned int>*) const;

        void addFrontFace(int, ArrayList<float>*, int*, ArrayList<float>*, ArrayList<float>*, ArrayList<unsigned int>*) const;
        void addBackFace(int, ArrayList<float>*, int*, ArrayList<float>*, ArrayList<float>*, ArrayList<unsigned int>*) const;

        void addRightFace(int, ArrayList<float>*, int*, ArrayList<float>*, ArrayList<float>*, ArrayList<unsigned int>*) const;
        void addLeftFace(int, ArrayList<float>*, int*, ArrayList<float>*, ArrayList<float>*, ArrayList<unsigned int>*) const;

        void addBlock(float, int, ArrayList<float>*, int*, ArrayList<float>*, ArrayList<float>*, ArrayList<unsigned int>*) const;
        void getBlock(float, int, gdg::Mesh*) const;
        void getBlockIcon(int, gdg::Mesh*) const;

        void setPosition(int, int, int);
      };
    }
  }
}

#endif
