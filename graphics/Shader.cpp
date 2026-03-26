#include "Shader.h"

#include <stdlib.h>

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {

      Shader::Shader(const gdu::String& file)
      {
        program = glCreateProgram();
        vertexShader = createShader(file + ".vsh", GL_VERTEX_SHADER);
        fragmentShader = createShader(file + ".fsh", GL_FRAGMENT_SHADER);

        glAttachShader(program, vertexShader);
        glAttachShader(program, fragmentShader);

        glLinkProgram(program);
        checkShaderError(program, GL_LINK_STATUS, true, "Shader program failed to link!");

        glValidateProgram(program);
        checkShaderError(program, GL_VALIDATE_STATUS, true, "Shader program is invalid!");

        bind();
      }

      Shader::Shader(const Shader& shader)
      {

      }

      void Shader::operator=(const Shader& shader)
      {

      }

      Shader::~Shader()
      {
        glDetachShader(program, vertexShader);
        glDeleteShader(vertexShader);
        glDetachShader(program, fragmentShader);
        glDeleteShader(fragmentShader);
        glDeleteProgram(program);
      }

      void Shader::bind()
      {
        glUseProgram(program);
      }

      void Shader::registerArray(const char* name, int size)
      {
        for(int i=0;i<size;i++)
        {
          char intstr[10];
          sprintf(intstr, "%d", i);
          gdu::String varName = gdu::String(name) + gdu::String("[") + gdu::String(intstr) + gdu::String("]");
          registerVariable(varName.toChars());
        }
      }

      void Shader::loadArray(int id, const gdm::Matrix4x4* list, int size)
      {
        for(int i=0;i<size;i++)
        {
          loadVariable(id + i, *(list + i));
        }
      }

      void Shader::registerVariable(const char* name)
      {
        GLint id = glGetUniformLocation(program, name);
        if(id == -1)
        {
          std::cerr << "Variable " << name << " not found!" << std::endl;
        }
        else
        {
          std::cout << name << " was found! id = " << variables.size() << std::endl;
        }
        variables.add(id);
      }

      void Shader::loadVariable(int index, const gdm::Matrix4x4& matrix)
      {
        float values[16];
        matrix.toArray(values);
        glUniformMatrix4fv(variables[index], 1, false, values);
      }

      void Shader::loadVariable(int index, float x)
      {
        glUniform1f(variables[index], x);
      }

      void Shader::loadVariable(int index, float x, float y)
      {
        glUniform2f(variables[index], x, y);
      }

      void Shader::loadVariable(int index, float x, float y, float z)
      {
        glUniform3f(variables[index], x, y, z);
      }

      void Shader::loadVariable(int index, const gdm::Vector3& v)
      {
        glUniform3f(variables[index], v.getX(), v.getY(), v.getZ());
      }

      void Shader::loadVariable(int index, const gdm::Vector2& v)
      {
        glUniform2f(variables[index], v.x, v.y);
      }

      void Shader::loadVariable(int index, int i)
      {
        glUniform1i(variables[index], i);
      }

      void Shader::loadVariable(int index, bool b1, bool b2)
      {
        glUniform2i(variables[index], b1, b2);
      }

      void Shader::loadVariable(int index, float a, float b, float c, float d)
      {
        glUniform4f(variables[index], a, b, c, d);
      }

      GLuint Shader::createShader(const gdu::String& name, GLenum shaderType)
      {
        gdu::String codeStr = gdu::fileToString(name.toChars());
        GLuint shader = glCreateShader(shaderType);
        if(shader == 0)
        {
          std::cerr << "Shader creation failed!" << std::endl;
          exit(EXIT_FAILURE);
        }
        int codeSize = codeStr.size();
        const char* code = codeStr.toChars();

        const GLchar* p[1];
        *p = code;
        GLint lengths[1];
        *lengths = codeSize;

        std::cout << "shader code: " << code << std::endl;

        glShaderSource(shader, 1, p, lengths);
        glCompileShader(shader);
        checkShaderError(shader, GL_COMPILE_STATUS, false, "Error compiling shader!");
        return shader;
      }

      void Shader::checkShaderError(GLuint shader, GLuint flag, bool isProgram, const char* errorMessage)
      {
        GLint success = 0;
        GLchar error[1024] = {0};
        if(isProgram)
        {
          glGetProgramiv(shader, flag, &success);
        }
        else
        {
          glGetShaderiv(shader, flag, &success);
        }

        if(success == GL_FALSE)
        {
          if(isProgram)
          {
            glGetProgramInfoLog(shader, sizeof(error), NULL, error);
          }
          else
          {
            glGetShaderInfoLog(shader, sizeof(error), NULL, error);
          }
          std::cerr << errorMessage << ": '" << error << "'" << std::endl;
          exit(EXIT_FAILURE);
        }
      }

    }
  }
}
