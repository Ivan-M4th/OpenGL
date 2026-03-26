#include "TerrainStructure.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      TerrainStructure::TerrainStructure() : gdp::Structure(gdm::Vector3())
      {
        collider = &this->shape;
        physicalInformation.setBoxIntertiaMatrix(16.0, 16.0, 16.0);
      }

      TerrainStructure::TerrainStructure(const gdmg::ConvexPolyhedron& shape) : gdp::Structure(gdm::Vector3())
      {
        this->shape = shape;
        collider = &this->shape;
      }

      TerrainStructure::TerrainStructure(const TerrainStructure& structure) : gdp::Structure(structure)
      {
        shape = structure.shape;
        collider = &this->shape;
      }

      TerrainStructure& TerrainStructure::operator=(const TerrainStructure& structure)
      {
        gdp::Structure::operator=(structure);
        shape = structure.shape;
        collider = &this->shape;
        return *this;
      }
    }
  }
}
