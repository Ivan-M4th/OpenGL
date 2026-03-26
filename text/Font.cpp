#include "Font.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      Font::Font()
      {
        lineHeight = 0.0;
      }

      Font::Font(float lineHeight, const ArrayList<CharData>& charDatas)
      {
        this->lineHeight = lineHeight;
        this->charDatas = charDatas;
        this->charDatas.trim();
      }

      Font::Font(const Font& font)
      {
        lineHeight = font.lineHeight;
        charDatas = font.charDatas;
      }

      Font& Font::operator=(const Font& font)
      {
        lineHeight = font.lineHeight;
        charDatas = font.charDatas;
        return *this;
      }

      float Font::getLineHeight() const
      {
        return lineHeight;
      }

      const CharData& Font::getCharData(char c) const
      {
        unsigned int id = (unsigned int)c;
        if(id >= charDatas.size())
        {
          return getCharData('?');
        }

        if(!charDatas[id].isUsed)
        {
          return getCharData('?');
        }

        return charDatas[id];
      }
    }
  }
}
