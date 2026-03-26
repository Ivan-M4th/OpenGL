#ifndef GD_TEXT_CHARDATA_H
#define GD_TEXT_CHARDATA_H

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      class CharData
      {
      public:
        float x;
        float y;
        float width;
        float height;
        float xoffset;
        float yoffset;
        float xadvance;
        bool isUsed;

        CharData();
        CharData(float, float, float, float, float, float, float);
        CharData(const CharData&);
        CharData& operator=(const CharData&);
      };
    }
  }
}

#endif
