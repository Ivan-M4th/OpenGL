#ifndef GD_VOXEL_TERRAINTEXTURE_H
#define GD_VOXEL_TERRAINTEXTURE_H

#include "../gddef.h"

#include "../graphics/Texture.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class TerrainTexture
      {
      private:
        int sizex;
        int sizey;
        gdg::Texture* texture;

        void getTexturePosition(int, float*, float*) const;
      public:
        TerrainTexture(int, int, gdg::Texture*);
        TerrainTexture(const TerrainTexture&);
        TerrainTexture& operator=(const TerrainTexture&);

        void getUVs(int, float*, float*, float*, float*) const;
      };
    }
  }
}

#endif
