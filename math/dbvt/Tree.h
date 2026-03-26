#ifndef GD_MATH_DBVT_TREE_H
#define GD_MATH_DBVT_TREE_H

#include "../../gddef.h"

#include "Node.h"

#include "../UIntPair.h"
#include "../Vector2i.h"

#include "../geometry/AABB.h"

#include "../../utils/ArrayList.h"
#include "../../utils/IDGenerator.h"
#include "../../utils/LinkedList.h"
#include "../../utils/LinkedHashList.h"
#include "../../utils/MemoryArray.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace dbvt
      {
        class Tree
        {
          friend class TreeIterator;

        private:
          gdu::MemoryArray<gdmg::AABB>* aabbs;

          ArrayList<Node> nodes;
          int rootNodeIndex;
          int amount;
          gdu::IDGenerator indexGenerator;

          int createNode();
          void deleteNode(int);
          int createLeafNode(int, int);
          void getBestSibling(const gdmg::AABB*, int, float, int*, float*) const;
          int getBestSibling(int) const;
          void recalculateAABBs(int);

          //void checkCrossedCollisions(unsigned int, unsigned int) const;
          //void checkInternalCollisions(unsigned int) const;
        public:
          Tree();
          Tree(const Tree&);
          Tree& operator=(const Tree&);

          int size() const;
          void setAabbs(gdu::MemoryArray<gdmg::AABB>*);

          int getAabbId(int) const;
          int insert(int, int); //objectId, aabbId
          void remove(int); //nodeId (must be leaf)
          //void updateCollidingPairs() const;

          void getCollisions(int, const gdmg::AABB*, gdu::LinkedHashList<UIntPair>*) const;
        };
      }
    }
  }
}

#endif
