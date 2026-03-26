#include "Hashing.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      unsigned int hash(unsigned int x)
      {
        return x;
      }

      unsigned int hash(int x)
      {
        if(x < 0)
        {
          return -2*x + 1;
        }
        return 2*x;
      }

      unsigned int hash(unsigned int x, unsigned int y)
      {
        unsigned int a = (x + y + 1)*(x + y);
        return (a/2) + y;
      }

      unsigned int hash(int x, int y)
      {
        return hash(hash(x), hash(y));
      }

      unsigned int hash(const gdm::Vector2i& v)
      {
        return hash(v.x, v.y);
      }

      unsigned int hash(const gdm::Vector3i& v)
      {
        return hash(hash(v.x, v.y), hash(v.z));
      }
    }
  }
}
