#ifndef GD_GRAPHICS_MESH_H
#define GD_GRAPHICS_MESH_H

#include <GL/glew.h>
#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Mesh
      {
      private:
        int vertexAmount = 0;
        int indicesAmount = 0;
        GLuint vao;
        ArrayList<GLuint> vbos;

        void genVao();
        GLuint genVbo();
        Mesh(const Mesh&);
        void operator=(const Mesh&);
      public:
        Mesh();
        ~Mesh();

        void deleteData();
        void addVbo(int, int, const float*, unsigned int);
        void addIVbo(int, int, const unsigned int*, unsigned int);
        void addIndices(const unsigned int*, int);
        GLuint getVao() const;
        int getIndicesAmount() const;
        void setVertexAmount(int);
        int getVertexAmount() const;
      };
    }
  }
}

#endif
