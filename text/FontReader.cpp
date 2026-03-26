#include "FontReader.h"

#include <iostream>
#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      FontReader::FontReader(const char* fileName, int atlasWidth, int atlasHeight)
      {
        index = 0;
        file = gdu::fileToString(fileName);
        this->atlasWidth = atlasWidth;
        this->atlasHeight = atlasHeight;

        std::cout << file << std::endl;
      }

      bool FontReader::isValid() const
      {
        return index < file.size();
      }

      void FontReader::skip(char c)
      {
        while(isValid() && file[index] == c)
        {
          index++;
        }
      }

      void FontReader::skipTo(char c)
      {
        while(isValid() && file[index] != c)
        {
          index++;
        }
      }

      gdu::String FontReader::readTo(char c)
      {
        gdu::String string;
        while(isValid() && file[index] != c)
        {
          string.addChar(file[index]);
          index++;
        }
        return string;
      }

      void FontReader::skipToNextLine()
      {
        skipTo('\n');
        skip('\n');
      }

      float FontReader::readValue(const char* chars)
      {
        assert(readTo('=') == chars);
        skip('=');
        float value = readTo(' ');
        skip(' ');
        return value;
      }

      void FontReader::readInfo()
      {
        assert(readTo(' ') == gdu::String("info"));

        for(unsigned int i=0;i<10;i++)
        {
          skipTo(' ');
          skip(' ');
        }

        assert(readTo('=') == gdu::String("padding"));
        skip('=');
        py1 = readTo(',');
        skip(',');

        px2 = readTo(',');
        skip(',');

        py2 = readTo(',');
        skip(',');

        px1 = readTo(' ');
        skipToNextLine();

        px1/=(float)(atlasWidth);
        px2/=(float)(atlasWidth);
        py1/=(float)(atlasHeight);
        py2/=(float)(atlasHeight);

        std::cout << "padding: px1/px2/py1/py2: " << px1 << " / " << px2 << " / " << py1 << " / " << py2 << std::endl;
      }

      void FontReader::readCommun()
      {
        assert(readTo(' ') == gdu::String("common"));
        skip(' ');

        assert(readTo('=') == gdu::String("lineHeight"));
        skip('=');
        lineHeight = readTo(' ');
        lineHeight/=(float)(atlasHeight);
        skipToNextLine();
        std::cout << "line height: " << lineHeight << std::endl;
      }

      void FontReader::readChar(ArrayList<CharData>* charDatas)
      {
        assert(readTo(' ') == gdu::String("char"));
        skip(' ');

        assert(readTo('=') == gdu::String("id"));
        skip('=');
        unsigned int id = readTo(' ');
        skip(' ');

        float x = readValue("x")/(float)(atlasWidth);
        float y = readValue("y")/(float)(atlasHeight);
        float width = readValue("width")/(float)(atlasWidth);
        float height = readValue("height")/(float)(atlasHeight);
        float xoffset = readValue("xoffset")/(float)(atlasWidth);
        float yoffset = readValue("yoffset")/(float)(atlasHeight);
        float xadvance = readValue("xadvance")/(float)(atlasWidth);
        skipToNextLine();

        CharData charData(x, y, width, height, xoffset, yoffset, xadvance);
        if(id >= charDatas->size())
        {
          charDatas->setSize(id + 1);
        }

        (*charDatas)[id] = charData;

        std::cout << "reading char: " << id << std::endl;
        std::cout << "char values: " << x << ", " << y << ", " << width << ", " << height << ", " << xoffset << ", " << yoffset << ", " << xadvance << std::endl;
      }

      Font FontReader::read()
      {
        readInfo();
        readCommun();
        skipToNextLine();
        skipToNextLine();

        ArrayList<CharData> charDatas;
        while(isValid())
        {
          readChar(&charDatas);
        }

        return Font(lineHeight, charDatas);
      }
    }
  }
}
