#ifndef GD_TEXT_FONTREADER_H
#define GD_TEXT_FONTREADER_H

#include "../gddef.h"

#include "CharData.h"
#include "Font.h"

#include "../utils/String.h"
#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class FontReader
      {
      private:
        gdu::String file;
        int atlasWidth;
        int atlasHeight;

        unsigned int index;

        float px1;
        float px2;
        float py1;
        float py2;

        float lineHeight;

        bool isValid() const;
        void skip(char);
        void skipTo(char);
        gdu::String readTo(char);
        void skipToNextLine();
        float readValue(const char*);

        void readInfo();
        void readCommun();
        void readChar(ArrayList<CharData>*);
      public:
        FontReader(const char*, int, int);

        Font read();
      };
    }
  }
}

#endif
