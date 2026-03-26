#include "UIntPair.h"

#include "../utils/Hashing.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      UIntPair::UIntPair(unsigned int id1, unsigned int id2)
      {
        this->id1 = id1;
        this->id2 = id2;
      }

      UIntPair::UIntPair(const UIntPair& pair)
      {
        id1 = pair.id1;
        id2 = pair.id2;
      }

      UIntPair& UIntPair::operator=(const UIntPair& pair)
      {
        id1 = pair.id1;
        id2 = pair.id2;
        return *this;
      }

      bool UIntPair::operator==(const UIntPair& pair) const
      {
        if(id1 == pair.id1 && id2 == pair.id2)
        {
          return true;
        }
        return id1 == pair.id2 && id2 == pair.id1;
      }

      bool UIntPair::contains(unsigned int id) const
      {
        if(id1 == id)
        {
          return true;
        }
        return id2 == id;
      }

      std::ostream& operator<<(std::ostream& os, const UIntPair& pair)
      {
        os << "(" << pair.id1 << ", " << pair.id2 << ")";
        return os;
      }
    }

    namespace utils
    {
      unsigned int hash(const gdm::UIntPair& pair)
      {
        if(pair.id1 < pair.id2)
        {
          return hash(pair.id1, pair.id2);
        }
        return hash(pair.id2, pair.id1);
      }
    }
  }
}
