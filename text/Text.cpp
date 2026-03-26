#include "Text.h"

#include "Fonts.h"
#include "TextBuilder.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      Text::Text()
      {
        font = getFont(DEFAULT_FONT);
        size = 0.07;
        maxLineSize = 0.5;
        centered = false;
      }

      Text::Text(const Font* font, float size, float maxLineSize, bool centered)
      {
        this->font = font;
        this->size = size;
        this->maxLineSize = maxLineSize;
        this->centered = centered;
      }

      Text::Text(const Text& text)
      {
        font = text.font;
        size = text.size;
        maxLineSize = text.maxLineSize;
        centered = text.centered;
        string = text.string;

        position = text.position;
        color = text.color;
        width = text.width;
        borderWidth = text.borderWidth;

        buildMesh();
      }

      Text& Text::operator=(const Text& text)
      {
        font = text.font;
        size = text.size;
        maxLineSize = text.maxLineSize;
        centered = text.centered;
        string = text.string;

        position = text.position;
        color = text.color;
        width = text.width;
        borderWidth = text.borderWidth;

        buildMesh();
        return *this;
      }

      void Text::buildMesh()
      {
        if(font == NULL)
        {
          return;
        }
        if(string.size() == 0)
        {
          return;
        }
        TextBuilder builder(font, &string, size, maxLineSize, centered);
        builder.build();
        mesh.deleteData();
        builder.loadMesh(&mesh);
      }

      void Text::setText(const gdu::String& string)
      {
        this->string = string;
        buildMesh();
      }

      const gdg::Mesh* Text::getMesh() const
      {
        return &mesh;
      }

      void Text::updateMesh()
      {
        buildMesh();
      }
    }
  }
}
