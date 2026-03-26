#ifndef GD_DEBUG_H
#define GD_DEBUG_H

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    class Debug
    {
    private:
      bool use = true;

    public:
      Debug();

      void endl() const;

      template<typename Type> Debug& operator<<(const Type& element)
      {
        if(use)
        {
          std::cout << element;
        }
        return *this;
      }
    };

    extern Debug DEBUG;
  }
}

#endif
