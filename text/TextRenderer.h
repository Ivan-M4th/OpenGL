#ifndef GD_TEXT_TEXTRENDERER_H
#define GD_TEXT_TEXTRENDERER_H

#include "../gddef.h"

#include "Text.h"

#include "../graphics/Shader.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class TextRenderer
      {
      private:
        gdg::Shader* shader;

      public:
        TextRenderer(gdg::Shader*);
        TextRenderer(const TextRenderer&);
        TextRenderer& operator=(const TextRenderer&);

        void prepare(float);
        void bindShader();
        void render(const Text&);
      };
    }
  }
}

#endif
