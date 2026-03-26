#include "Node.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace dbvt
      {
        Node::Node()
        {
          objectId = -1;
          aabbId = -1;
          parentIndex = -1;
          child1Index = -1;
          child2Index = -1;
          isLeaf = false;
        }

        Node::Node(Node& node)
        {
          objectId = node.objectId;
          aabbId = node.aabbId;
          parentIndex = node.parentIndex;
          child1Index = node.child1Index;
          child2Index = node.child2Index;
          isLeaf = node.isLeaf;
        }

        Node& Node::operator=(Node& node)
        {
          objectId = node.objectId;
          aabbId = node.aabbId;
          parentIndex = node.parentIndex;
          child1Index = node.child1Index;
          child2Index = node.child2Index;
          isLeaf = node.isLeaf;
          return *this;
        }
      }
    }
  }
}
