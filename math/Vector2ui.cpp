#include "Vector2ui.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      Vector2ui::Vector2ui(unsigned int x, unsigned int y)
      {
        this->x = x;
        this->y = y;
      }

      Vector2ui::Vector2ui(const Vector2ui& v)
      {
        x = v.x;
        y = v.y;
      }

      Vector2ui& Vector2ui::operator=(const Vector2ui& v)
      {
        x = v.x;
        y = v.y;
        return *this;
      }
    }
  }
}
