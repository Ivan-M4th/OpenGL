#include "TextRenderer.h"

#include "../graphics/Rendering.h"

#include "../data/Assets.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      TextRenderer::TextRenderer(gdg::Shader* shader)
      {
        this->shader = shader;
      }

      TextRenderer::TextRenderer(const TextRenderer& renderer)
      {
        shader = renderer.shader;
      }

      TextRenderer& TextRenderer::operator=(const TextRenderer& renderer)
      {
        shader = renderer.shader;
        return *this;
      }

      void TextRenderer::prepare(float screenRatio)
      {
        shader->bind();
        shader->loadVariable(0, screenRatio);
      }

      void TextRenderer::bindShader()
      {
        shader->bind();
      }

      void TextRenderer::render(const Text& text)
      {
        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::DEFAULT_FONT_ATLAS_TEXTURE)->getId());
        shader->loadVariable(1, text.position);
        shader->loadVariable(2, text.color);
        shader->loadVariable(3, text.width);
        shader->loadVariable(4, text.borderWidth);
        gdg::render2DIMesh(text.getMesh());
      }
    }
  }
}
