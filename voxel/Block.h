#ifndef GD_VOXEL_BLOCK_H
#define GD_VOXEL_BLOCK_H

#include "../gddef.h"

#include "../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class Block
      {
      private:
        int materialId;

      public:
        Block();
        Block(int);
        Block(const Block&);
        Block& operator=(const Block&);

        int getMaterialId() const;
        void setMaterial(int);
      };

      int toBlockCoord(float);
      void toBlockCoords(float, float, float, int*, int*, int*);

      struct BlockInfo
      {
        Block* block;
        gdm::Vector3i position;
      };
    }
  }
}

#endif
