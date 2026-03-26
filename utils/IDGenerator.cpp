#include "IDGenerator.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      IDGenerator::IDGenerator()
      {
        amount = 0;
      }

      IDGenerator::IDGenerator(const IDGenerator& generator)
      {
        amount = generator.amount;
        freeIds = generator.freeIds;
      }

      IDGenerator& IDGenerator::operator=(const IDGenerator& generator)
      {
        amount = generator.amount;
        freeIds = generator.freeIds;
        return *this;
      }

      unsigned int IDGenerator::genID()
      {
        if(freeIds.size() > 0)
        {
          unsigned int id = freeIds[0];
          freeIds.remove(0);
          return id;
        }
        unsigned int id = amount;
        amount++;
        return id;
      }

      void IDGenerator::free(unsigned int id)
      {
        if(!freeIds.contains(id))
        {
          freeIds.add(id);
        }
      }
    }
  }
}
