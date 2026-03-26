#ifndef GD_MATH_DBVT_NODE_H
#define GD_MATH_DBVT_NODE_H

#include "../../gddef.h"

#include "../geometry/AABB.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace dbvt
      {
        class Node
        {
        public:
          int objectId;
          int aabbId;

          int parentIndex;
          int child1Index;
          int child2Index;

          bool isLeaf;

          Node();
          Node(Node&);
          Node& operator=(Node&);
        };
      }
    }
  }
}

#endif
