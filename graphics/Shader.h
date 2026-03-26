#ifndef GD_GRAPHICS_SHADER_H
#define GD_GRAPHICS_SHADER_H

#include <GL/glew.h>

#include "../gddef.h"

#include "../utils/String.h"
#include "../utils/ArrayList.h"
#include "../math/Matrix4x4.h"
#include "../math/Vector3.h"
#include "../math/Vector2.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class Shader
      {
      private:
        GLuint program;
        GLuint vertexShader;
        GLuint fragmentShader;
        ArrayList<GLint> variables;

        Shader(const Shader&);
        void operator=(const Shader&);
        GLuint createShader(const gdu::String&, GLenum);
        void checkShaderError(GLuint, GLuint, bool, const char*);
      public:
        Shader(const gdu::String&);
        virtual ~Shader();
        void bind();
        void registerVariable(const char*);
        void registerArray(const char*, int);
        void loadVariable(int, const gdm::Matrix4x4&);
        void loadVariable(int, const gdm::Vector3&);
        void loadVariable(int, const gdm::Vector2&);
        void loadVariable(int, float, float, float, float);
        void loadVariable(int, float, float, float);
        void loadVariable(int, float, float);
        void loadVariable(int, float);
        void loadVariable(int, int);
        void loadVariable(int, bool, bool);
        void loadArray(int, const gdm::Matrix4x4*, int);
      };
    }
  }
}

#endif
