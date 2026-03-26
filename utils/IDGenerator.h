#ifndef GD_UTILS_IDGENERATOR_H
#define GD_UTILS_IDGENERATOR_H

#include "ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class IDGenerator
      {
      private:
        unsigned int amount;
        ArrayList<unsigned int> freeIds;

      public:
        IDGenerator();
        IDGenerator(const IDGenerator&);
        IDGenerator& operator=(const IDGenerator&);

        unsigned int genID();
        void free(unsigned int);
      };
    }
  }
}

#endif
