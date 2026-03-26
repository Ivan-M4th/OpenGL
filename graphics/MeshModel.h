#ifndef GD_GRAPHICS_MESHMODEL_H
#define GD_GRAPHICS_MESHMODEL_H

#include "../gddef.h"

#include "TexturedMesh.h"

#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      extern const unsigned int MODEL;
      extern const unsigned int INDEXED_MODEL;

      class MeshModel
      {
      protected:
        TexturedMesh mesh;
        gdm::Vector3 position;
        unsigned int dataType;

      public:
        MeshModel();
        MeshModel(const TexturedMesh&);
        MeshModel(const TexturedMesh&, const gdm::Vector3&);
        MeshModel(const TexturedMesh&, const gdm::Vector3&, unsigned int);

        MeshModel(const MeshModel&);
        MeshModel& operator=(const MeshModel&);
        virtual ~MeshModel();

        TexturedMesh getMesh() const;
        const gdm::Vector3& getPosition() const;
        unsigned int getDataType() const;
      };
    }
  }
}

#endif
