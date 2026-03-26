#ifndef GD_MATH_DBVT_TREEITERATOR_H
#define GD_MATH_DBVT_TREEITERATOR_H

#include "Tree.h"

#include "../../utils/ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace dbvt
      {
        class TreeIterator
        {
        private:
          const Tree* tree;
          ArrayList<unsigned int> nodeIndices;

        public:
          TreeIterator(const Tree*);
          TreeIterator(const TreeIterator&);
          TreeIterator& operator=(const TreeIterator&);

          bool isValid() const;
          const Node& getNode() const;
          void next();
        };
      }
    }
  }
}

#endif
