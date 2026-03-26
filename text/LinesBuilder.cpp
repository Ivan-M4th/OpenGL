#include "LinesBuilder.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      LinesBuilder::LinesBuilder(const Font* font, const gdu::String* string, float size, float maxLineSize)
      {
        this->font = font;
        this->string = string;
        this->size = size;
        this->maxLineSize = maxLineSize;
        index = 0;
      }

      LinesBuilder::LinesBuilder(const LinesBuilder& builder)
      {
        font = builder.font;
        string = builder.string;
        size = builder.size;
        maxLineSize = builder.maxLineSize;
        index = builder.index;
        lines = builder.lines;
      }

      LinesBuilder& LinesBuilder::operator=(const LinesBuilder& builder)
      {
        font = builder.font;
        string = builder.string;
        size = builder.size;
        maxLineSize = builder.maxLineSize;
        index = builder.index;
        lines = builder.lines;
        return *this;
      }

      bool LinesBuilder::isValid() const
      {
        return index < string->size();
      }

      void LinesBuilder::skip(char c)
      {
        while(isValid() && (*string)[index] == c)
        {
          index++;
        }
      }

      void LinesBuilder::addSpaces(float* lineSize)
      {
        while(isValid() && (*string)[index] == ' ')
        {
          float charSize = font->getCharData((*string)[index]).xadvance;
          (*lineSize)+=charSize*size;
          index++;
        }
      }

      bool LinesBuilder::addWord(float* lineSize)
      {
        while(isValid() && (*string)[index] != ' ')
        {
          if((*string)[index] == '\n')
          {
            return true;
            break;
          }

          float charSize = font->getCharData((*string)[index]).xadvance;
          (*lineSize)+=charSize*size;
          index++;
        }
        return false;
      }

      void LinesBuilder::buildLine()
      {
        skip(' ');
        unsigned int startIndex = index;
        float lineSize = 0.0;

        addWord(&lineSize);

        while(isValid())
        {
          unsigned int oldIndex = index;
          float oldLineSize = lineSize;

          addSpaces(&lineSize);
          bool quitLine = addWord(&lineSize);

          if(lineSize > maxLineSize)
          {
            index = oldIndex;
            lineSize = oldLineSize;
            break;
          }
          else if(quitLine)
          {
            lines.add(Line(startIndex, index, lineSize));
            index++;
            return;
          }
        }

        lines.add(Line(startIndex, index, lineSize));
      }

      void LinesBuilder::build()
      {
        while(isValid())
        {
          buildLine();
        }
      }

      const ArrayList<Line>& LinesBuilder::getLines() const
      {
        return lines;
      }
    }
  }
}
