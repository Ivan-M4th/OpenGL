#include "Line.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      Line::Line()
      {
        startIndex = 0;
        endIndex = 0;
        size = 0.0;
      }

      Line::Line(unsigned int startIndex, unsigned int endIndex, float size)
      {
        this->startIndex = startIndex;
        this->endIndex = endIndex;
        this->size = size;
      }

      Line::Line(const Line& line)
      {
        startIndex = line.startIndex;
        endIndex = line.endIndex;
        size = line.size;
      }

      Line& Line::operator=(const Line& line)
      {
        startIndex = line.startIndex;
        endIndex = line.endIndex;
        size = line.size;
        return *this;
      }
    }
  }
}
