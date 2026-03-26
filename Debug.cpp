#include "Debug.h"

namespace gt
{
  namespace doubovik
  {
    Debug DEBUG;

    Debug::Debug()
    {

    }

    void Debug::endl() const
    {
      if(use)
      {
        std::cout << std::endl;
      }
    }
  }
}
