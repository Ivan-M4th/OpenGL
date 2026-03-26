#include "TexturedMesh.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {

      TexturedMesh::TexturedMesh()
      {
        mesh = NULL;
        texture = NULL;
      }

      TexturedMesh::TexturedMesh(Mesh* mesh, Texture* texture)
      {
        this->mesh = mesh;
        this->texture = texture;
      }

      TexturedMesh::TexturedMesh(const TexturedMesh& texturedMesh)
      {
        mesh = texturedMesh.mesh;
        texture = texturedMesh.texture;
      }

      TexturedMesh& TexturedMesh::operator=(const TexturedMesh& texturedMesh)
      {
        mesh = texturedMesh.mesh;
        texture = texturedMesh.texture;
        return *this;
      }
    }
  }
}
