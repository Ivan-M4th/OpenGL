#include "Block.h"

#include "Materials.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      Block::Block()
      {
        materialId = AIR;
      }

      Block::Block(int materialId)
      {
        this->materialId = materialId;
      }

      Block::Block(const Block& block)
      {
        materialId = block.materialId;
      }

      Block& Block::operator=(const Block& block)
      {
        materialId = block.materialId;
        return *this;
      }

      int Block::getMaterialId() const
      {
        return materialId;
      }

      void Block::setMaterial(int materialId)
      {
        this->materialId = materialId;
      }

      int toBlockCoord(float x)
      {
        int bx = (int)x;
        if(x >= 0.0)
        {
          return bx;
        }
        return bx - 1;
      }

      void toBlockCoords(float x, float y, float z, int* bx, int* by, int* bz)
      {
        *bx = toBlockCoord(x);
        *by = toBlockCoord(y);
        *bz = toBlockCoord(z);
      }
    }
  }
}
