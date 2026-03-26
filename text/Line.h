#ifndef GD_TEXT_LINE_H
#define GD_TEXT_LINE_H

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class Line
      {
      public:
        unsigned int startIndex;
        unsigned int endIndex;
        float size;

        Line();
        Line(unsigned int, unsigned int, float);
        Line(const Line&);
        Line& operator=(const Line&);
      };
    }
  }
}

#endif
