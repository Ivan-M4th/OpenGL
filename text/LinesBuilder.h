#ifndef GD_TEXT_LINEBUILDER_H
#define GD_TEXT_LINEBUILDER_H

#include "../gddef.h"

#include "Font.h"
#include "Line.h"

#include "../utils/String.h"
#include "../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class LinesBuilder
      {
      private:
        const Font* font;
        const gdu::String* string;
        float size;
        float maxLineSize;

        unsigned int index;
        ArrayList<Line> lines;

        bool isValid() const;
        void skip(char);

        void addSpaces(float*);
        bool addWord(float*);
        void buildLine();
      public:
        LinesBuilder(const Font*, const gdu::String*, float, float);
        LinesBuilder(const LinesBuilder&);
        LinesBuilder& operator=(const LinesBuilder&);

        void build();
        const ArrayList<Line>& getLines() const;
      };
    }
  }
}

#endif
