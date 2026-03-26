#ifndef GD_CLIENT_OBJECTS_TREE_H
#define GD_CLIENT_OBJECTS_TREE_H

#include "../../gddef.h"

#include "../../physics/Structure.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace objects
      {
        class Tree : public gdp::Structure
        {
        public:
          Tree();
          Tree(const Tree&);
          Tree& operator=(const Tree&);
          virtual ~Tree() override;
        };
      }
    }
  }
}

#endif
