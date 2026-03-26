#ifndef GD_GRAPHICS_TEXTUREDMESH_H
#define GD_GRAPHICS_TEXTUREDMESH_H

#include "Mesh.h"
#include "Texture.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class TexturedMesh
      {
      public:
        Mesh* mesh;
        Texture* texture;

        TexturedMesh();
        TexturedMesh(Mesh*, Texture*);
        TexturedMesh(const TexturedMesh&);
        TexturedMesh& operator=(const TexturedMesh&);
      };
    }
  }
}

#endif
