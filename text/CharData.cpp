#include "CharData.h"

namespace gt
{
  namespace doubovik
  {
    namespace text
    {
      CharData::CharData()
      {
        isUsed = false;
      }

      CharData::CharData(float x, float y, float width, float height, float xoffset, float yoffset, float xadvance)
      {
        this->x = x;
        this->y = y;
        this->width = width;
        this->height = height;
        this->xoffset = xoffset;
        this->yoffset = yoffset;
        this->xadvance = xadvance;
        isUsed = true;
      }

      CharData::CharData(const CharData& data)
      {
        x = data.x;
        y = data.y;
        width = data.width;
        height = data.height;
        xoffset = data.xoffset;
        yoffset = data.yoffset;
        xadvance = data.xadvance;
        isUsed = data.isUsed;
      }

      CharData& CharData::operator=(const CharData& data)
      {
        x = data.x;
        y = data.y;
        width = data.width;
        height = data.height;
        xoffset = data.xoffset;
        yoffset = data.yoffset;
        xadvance = data.xadvance;
        isUsed = data.isUsed;
        return *this;
      }
    }
  }
}
