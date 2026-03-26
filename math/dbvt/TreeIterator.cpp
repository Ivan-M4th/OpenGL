#include "TreeIterator.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace dbvt
      {
        TreeIterator::TreeIterator(const Tree* tree)
        {
          this->tree = tree;
          nodeIndices.add(tree->rootNodeIndex);
        }

        TreeIterator::TreeIterator(const TreeIterator& iterator)
        {
          tree = iterator.tree;
          nodeIndices = iterator.nodeIndices;
        }

        TreeIterator& TreeIterator::operator=(const TreeIterator& iterator)
        {
          tree = iterator.tree;
          nodeIndices = iterator.nodeIndices;
          return *this;
        }

        bool TreeIterator::isValid() const
        {
          return nodeIndices.size() > 0;
        }

        const Node& TreeIterator::getNode() const
        {
          assert(isValid());
          return tree->nodes[nodeIndices[0]];
        }

        void TreeIterator::next()
        {
          assert(isValid());
          if(!getNode().isLeaf)
          {
            nodeIndices.add(getNode().child1Index);
            nodeIndices.add(getNode().child2Index);
          }
          nodeIndices.remove(0);
        }
      }
    }
  }
}
