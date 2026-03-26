#include "Fonts.h"

#include <cassert>

#include "FontReader.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      const unsigned int DEFAULT_FONT = 0;

      Font* FONTS = NULL;
      const unsigned int FONTS_AMOUNT = 1;

      void loadFont(unsigned int index, const char* file, int atlasWidth, int atlasHeight)
      {
        FontReader reader(file, atlasWidth, atlasHeight);
        *(FONTS + index) = reader.read();
      }

      void loadFonts()
      {
        FONTS = new Font[FONTS_AMOUNT];
        loadFont(DEFAULT_FONT, "resources/fonts/default.fnt", 512 ,512);
      }

      void deleteFonts()
      {
        delete[] FONTS;
        FONTS = NULL;
      }

      Font* getFont(unsigned int index)
      {
        assert(FONTS != NULL);
        assert(index < FONTS_AMOUNT);
        return FONTS + index;
      }
    }
  }
}
