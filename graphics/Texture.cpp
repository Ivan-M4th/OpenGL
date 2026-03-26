#include "Texture.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      Texture::Texture()
      {
        id = 0;
      }

      Texture::Texture(GLuint id)
      {
        this->id = id;
      }

      Texture::~Texture()
      {
        deleteData();
      }

      Texture::Texture(const Texture&)
      {

      }

      void Texture::operator=(const Texture&)
      {

      }

      void Texture::deleteData()
      {
        if(id != 0)
        {
          glDeleteTextures(1, &id);
          id = 0;
        }
      }

      void Texture::setId(GLuint id)
      {
        deleteData();
        this->id = id;
      }

      GLuint Texture::getId() const
      {
        return id;
      }
    }
  }
}
