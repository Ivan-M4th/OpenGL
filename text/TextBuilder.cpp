#include "TextBuilder.h"

#include "LinesBuilder.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      TextBuilder::TextBuilder(const Font* font, const gdu::String* string, float size, float maxLineSize, bool centered)
      {
        this->font = font;
        this->string = string;
        this->size = size;
        this->maxLineSize = maxLineSize;
        this->centered = centered;
      }

      TextBuilder::TextBuilder(const TextBuilder& builder)
      {
        font = builder.font;
        string = builder.string;
        size = builder.size;
        maxLineSize = builder.maxLineSize;
        centered = builder.centered;

        cx = builder.cx;
        cy = builder.cy;

        indices = builder.indices;
        positions = builder.positions;
        uvs = builder.uvs;
      }

      TextBuilder& TextBuilder::operator=(const TextBuilder& builder)
      {
        font = builder.font;
        string = builder.string;
        size = builder.size;
        maxLineSize = builder.maxLineSize;
        centered = builder.centered;

        cx = builder.cx;
        cy = builder.cy;

        indices = builder.indices;
        positions = builder.positions;
        uvs = builder.uvs;
        return *this;
      }

      void TextBuilder::buildCharQuad(float minX, float minY, float maxX, float maxY, float uvMinX, float uvMinY, float uvMaxX, float uvMaxY)
      {
        unsigned int index = positions.size()/2;
        indices.add(index);
        indices.add(index + 1);
        indices.add(index + 2);

        indices.add(index + 2);
        indices.add(index + 3);
        indices.add(index);

        positions.add(minX);
        positions.add(minY);

        positions.add(maxX);
        positions.add(minY);

        positions.add(maxX);
        positions.add(maxY);

        positions.add(minX);
        positions.add(maxY);

        uvs.add(uvMinX);
        uvs.add(uvMaxY);

        uvs.add(uvMaxX);
        uvs.add(uvMaxY);

        uvs.add(uvMaxX);
        uvs.add(uvMinY);

        uvs.add(uvMinX);
        uvs.add(uvMinY);
      }

      void TextBuilder::buildChar(char c)
      {
        const CharData& charData = font->getCharData(c);

        float minX = cx + charData.xoffset*size;
        float maxX = minX + charData.width*size;

        float maxY = cy - charData.yoffset*size;
        float minY = maxY - charData.height*size;


        float uvMinX = charData.x;
        float uvMinY = charData.y;
        float uvMaxX = uvMinX + charData.width;
        float uvMaxY = uvMinY + charData.height;

        buildCharQuad(minX, minY, maxX, maxY, uvMinX, uvMinY, uvMaxX, uvMaxY);

        cx+=(charData.xadvance*size);
      }

      void TextBuilder::buildLine(const Line& line)
      {
        if(centered)
        {
          cx = (maxLineSize - line.size)/2.0;
        }
        else
        {
          cx = 0.0;
        }

        for(unsigned int i=line.startIndex;i<line.endIndex;i++)
        {
          buildChar((*string)[i]);
        }
        cy-=(font->getLineHeight()*size);
      }

      void TextBuilder::build()
      {
        LinesBuilder builder(font, string, size, maxLineSize);
        builder.build();
        cx = 0.0;
        cy = 0.0;
        for(unsigned int i=0;i<builder.getLines().size();i++)
        {
          buildLine(builder.getLines()[i]);
        }
      }

      void TextBuilder::loadMesh(gdg::Mesh* mesh) const
      {
        mesh->addIndices(indices.getData(), indices.size());
        mesh->addVbo(0, 2, positions.getData(), positions.size());
        mesh->addVbo(1, 2, uvs.getData(), uvs.size());
      }
    }
  }
}
