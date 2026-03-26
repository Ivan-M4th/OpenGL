#ifndef GD_MATH_UINTPAIR_H
#define GD_MATH_UINTPAIR_H

#include "../gddef.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      class UIntPair
      {
      public:
        unsigned int id1;
        unsigned int id2;

        UIntPair(unsigned int, unsigned int);
        UIntPair(const UIntPair&);
        UIntPair& operator=(const UIntPair&);

        bool operator==(const UIntPair&) const;
        bool contains(unsigned int) const;
      };

      std::ostream& operator<<(std::ostream&, const UIntPair&);
    }


    namespace utils
    {
      unsigned int hash(const gdm::UIntPair&);
    }
  }
}

#endif
