#include "Rendering.h"

#include <GL/glew.h>

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      void render2DIMesh(const Mesh* mesh)
      {
        glBindVertexArray(mesh->getVao());
        glEnableVertexAttribArray(0);
        glEnableVertexAttribArray(1);

        glDrawElements(GL_TRIANGLES, mesh->getIndicesAmount(), GL_UNSIGNED_INT, 0);

        glDisableVertexAttribArray(0);
        glDisableVertexAttribArray(1);
        glBindVertexArray(0);
      }
    }
  }
}
