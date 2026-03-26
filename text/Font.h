#ifndef GD_TEXT_FONT_H
#define GD_TEXT_FONT_H

#include "CharData.h"

#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class Font
      {
      private:
        float lineHeight;
        ArrayList<CharData> charDatas;

      public:
        Font();
        Font(float, const ArrayList<CharData>&);
        Font(const Font&);
        Font& operator=(const Font&);

        float getPX1() const;
        float getPX2() const;
        float getPY1() const;
        float getPY2() const;
        float getLineHeight() const;
        const CharData& getCharData(char) const;
      };
    }
  }
}

#endif
