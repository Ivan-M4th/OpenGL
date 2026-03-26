#include "CharArrayParser.h"

#include <cstring>
#include <cassert>
#include <cstdio>
#include <cstdlib>

namespace gt
{
  namespace doubovik
  {
    CharArrayParser::CharArrayParser(const char* data)
    {
      this->data = data;
      size = strlen(data);
      index = 0;
    }

    CharArrayParser::CharArrayParser(const CharArrayParser& parser)
    {
      data = parser.data;
      size = parser.size;
      index = parser.index;
    }

    CharArrayParser& CharArrayParser::operator=(const CharArrayParser& parser)
    {
      data = parser.data;
      size = parser.size;
      index = parser.index;
      return *this;
    }

    int CharArrayParser::readFigure()
    {
      char c = *(data + index);
      assert(c <= '9' && c >= '0' && "Parsing error known figure!");
      index++;
      return c - '0';
    }

    bool CharArrayParser::readSign()
    {
      if(*(data + index) == '-')
      {
        index++;
        return false;
      }
      return true;
    }

    int CharArrayParser::toInt()
    {
      bool positive = readSign();
      int x = 0;
      while(index < size)
      {
        x*=10;
        x+=readFigure();
      }
      if(!positive)
      {
        x*=-1;
      }
      return x;
    }

    float CharArrayParser::toFloat()
    {
      return atof(data);
    }
  }
}
