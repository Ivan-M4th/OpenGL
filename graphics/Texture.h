#ifndef GD_GRAPHICS_TEXTURE_H
#define GD_GRAPHICS_TEXTURE_H

#include <GL/glew.h>

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Texture
      {
      private:
        GLuint id;

        void deleteData();

        Texture(const Texture&);
        void operator=(const Texture&);
      public:
        Texture();
        Texture(GLuint);
        ~Texture();

        void setId(GLuint);
        GLuint getId() const;
      };
    }
  }
}

#endif
