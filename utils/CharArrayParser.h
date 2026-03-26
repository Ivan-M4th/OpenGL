#ifndef GD_UTILS_CHARARRAYPARSER_H
#define GD_UTILS_CHARARRAYPARSER_H

namespace gt
{
  namespace doubovik
  {
    class CharArrayParser
    {
    private:
      const char* data;
      int size;
      int index;

      int readFigure();
      bool readSign();
    public:
      CharArrayParser(const char*);
      CharArrayParser(const CharArrayParser&);
      CharArrayParser& operator=(const CharArrayParser&);

      int toInt();
      float toFloat();
    };
  }
}

#endif
