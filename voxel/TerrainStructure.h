#ifndef GD_VOXEL_TERRAINSTUCTURE_H
#define GD_VOXEL_TERRAINSTUCTURE_H

#include "../gddef.h"

#include "../physics/Structure.h"

#include "../math/geometry/ConvexPolyhedron.h"
#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class TerrainStructure : public gdp::Structure
      {
      private:
        gdmg::ConvexPolyhedron shape;

      public:
        TerrainStructure();
        TerrainStructure(const gdmg::ConvexPolyhedron&);
        TerrainStructure(const TerrainStructure&);
        TerrainStructure& operator=(const TerrainStructure&);
      };
    }
  }
}

#endif
