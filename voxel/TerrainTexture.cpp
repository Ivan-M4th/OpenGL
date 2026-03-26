#include "TerrainTexture.h"

#include <cmath>

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      TerrainTexture::TerrainTexture(int sizex, int sizey, gdg::Texture* texture)
      {
        this->sizex = sizex;
        this->sizey = sizey;
        this->texture = texture;
      }

      TerrainTexture::TerrainTexture(const TerrainTexture& terrainTexture)
      {
        sizex = terrainTexture.sizex;
        sizey = terrainTexture.sizey;
        texture = terrainTexture.texture;
      }

      TerrainTexture& TerrainTexture::operator=(const TerrainTexture& terrainTexture)
      {
        sizex = terrainTexture.sizex;
        sizey = terrainTexture.sizey;
        texture = terrainTexture.texture;
        return *this;
      }

      void TerrainTexture::getTexturePosition(int id, float* x, float* y) const
      {
        int xi = id%sizex;
        int yi = (id - xi)/sizey;

        *x = ((float)xi)/((float)sizex);
        *y = ((float)yi)/((float)sizey);
      }

      void TerrainTexture::getUVs(int id, float* xmin, float* ymin, float* xmax, float* ymax) const
      {
        getTexturePosition(id, xmin, ymin);
        *xmax = *xmin + (1.0/((float)sizex));
        *ymax = *ymin + (1.0/((float)sizey));

        float error = 1.0/4000.0;
        (*xmin)+=error;
        (*ymin)+=error;
        (*xmax)-=error;
        (*ymax)-=error;
      }
    }
  }
}
