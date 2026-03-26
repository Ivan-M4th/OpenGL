#ifndef GD_TEXT_FONTS_H
#define GD_TEXT_FONTS_H

#include "Font.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      extern const unsigned int DEFAULT_FONT;

      void loadFonts();
      void deleteFonts();

      Font* getFont(unsigned int);
    }
  }
}

#endif
