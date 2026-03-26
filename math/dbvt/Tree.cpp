#include "Tree.h"

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace dbvt
      {
        Tree::Tree()
        {
          rootNodeIndex = 0;
          amount = 0;
          aabbs = NULL;
        }

        Tree::Tree(const Tree& tree)
        {
          aabbs = tree.aabbs;

          nodes = tree.nodes;
          rootNodeIndex = tree.rootNodeIndex;
          amount = tree.amount;
          indexGenerator = tree.indexGenerator;
        }

        Tree& Tree::operator=(const Tree& tree)
        {
          aabbs = tree.aabbs;

          nodes = tree.nodes;
          rootNodeIndex = tree.rootNodeIndex;
          amount = tree.amount;
          indexGenerator = tree.indexGenerator;
          return *this;
        }

        void Tree::setAabbs(gdu::MemoryArray<gdmg::AABB>* aabbs)
        {
          this->aabbs = aabbs;
        }

        int Tree::createNode()
        {
          int index = indexGenerator.genID();
          if(index >= nodes.size())
          {
            nodes.setSize(index + 1);
          }
          amount++;
          nodes[index].isLeaf = false;
          nodes[index].aabbId = aabbs->genSlot();
          return index;
        }

        void Tree::deleteNode(int nodeIndex)
        {
          if(!nodes[nodeIndex].isLeaf)
          {
            aabbs->free(nodes[nodeIndex].aabbId);
          }

          indexGenerator.free(nodeIndex);
          amount--;
        }

        int Tree::createLeafNode(int objectId, int aabbId)
        {
          unsigned int index = createNode();
          nodes[index].isLeaf = true;
          nodes[index].aabbId = aabbId;
          nodes[index].objectId = objectId;
          return index;
        }

        void Tree::getBestSibling(const gdmg::AABB* aabb, int nodeIndex, float inheritedCost, int* bestNodeIndex, float* minCost) const
        {
          int nodeAabbId = nodes[nodeIndex].aabbId;
          gdmg::AABB* nodeAabb = &(*aabbs)[nodeAabbId];

          float cost = inheritedCost + aabb->group(*nodeAabb).area();

          if(cost < *minCost)
          {
            *minCost = cost;
            *bestNodeIndex = nodeIndex;
          }

          if(!nodes[nodeIndex].isLeaf)
          {
            inheritedCost = cost - nodeAabb->area();

            float lowCost = inheritedCost + aabb->area();
            if(lowCost < *minCost)
            {
              getBestSibling(aabb, nodes[nodeIndex].child1Index, inheritedCost, bestNodeIndex, minCost);
              getBestSibling(aabb, nodes[nodeIndex].child2Index, inheritedCost, bestNodeIndex, minCost);
            }
          }
        }

        int Tree::getBestSibling(int aabbId) const
        {
          gdmg::AABB* aabb = &(*aabbs)[aabbId];

          int rootAabbId = nodes[rootNodeIndex].aabbId;
          gdmg::AABB* rootAabb = &(*aabbs)[rootAabbId];

          int bestNodeIndex = rootNodeIndex;
          float inheritedCost = 0.0;
          float minCost = aabb->group(*rootAabb).area();
          getBestSibling(aabb, rootNodeIndex, inheritedCost, &bestNodeIndex, &minCost);
          return bestNodeIndex;
        }

        void Tree::recalculateAABBs(int nodeIndex)
        {
          while(true)
          {
            int child1Index = nodes[nodeIndex].child1Index;
            int child2Index = nodes[nodeIndex].child2Index;

            int child1AabbId = nodes[child1Index].aabbId;
            gdmg::AABB* child1Aabb = &(*aabbs)[child1AabbId];

            int child2AabbId = nodes[child2Index].aabbId;
            gdmg::AABB* child2Aabb = &(*aabbs)[child2AabbId];

            int nodeAabbId = nodes[nodeIndex].aabbId;
            (*aabbs)[nodeAabbId] = child1Aabb->group(*child2Aabb);

            if(nodeIndex == rootNodeIndex)
            {
              break;
            }
            nodeIndex = nodes[nodeIndex].parentIndex;
          }
        }

        int Tree::size() const
        {
          return amount;
        }

        int Tree::getAabbId(int nodeId) const
        {
          return nodes[nodeId].aabbId;
        }

        int Tree::insert(int objectId, int aabbId)
        {
          if(amount == 0)
          {
            int leafNodeIndex = createLeafNode(objectId, aabbId);
            rootNodeIndex = leafNodeIndex;
            return rootNodeIndex;
          }

          int leafNodeIndex = createLeafNode(objectId, aabbId);

          int siblingIndex = getBestSibling(aabbId);
          int newParentIndex = createNode();

          if(siblingIndex == rootNodeIndex)
          {
            rootNodeIndex = newParentIndex;
          }
          else
          {
            int oldParentIndex = nodes[siblingIndex].parentIndex;

            if(nodes[oldParentIndex].child1Index == siblingIndex)
            {
              nodes[oldParentIndex].child1Index = newParentIndex;
            }
            else
            {
              nodes[oldParentIndex].child2Index = newParentIndex;
            }
            nodes[newParentIndex].parentIndex = oldParentIndex;
          }

          nodes[newParentIndex].child1Index = siblingIndex;
          nodes[newParentIndex].child2Index = leafNodeIndex;

          nodes[siblingIndex].parentIndex = newParentIndex;
          nodes[leafNodeIndex].parentIndex = newParentIndex;

          recalculateAABBs(newParentIndex);

          return leafNodeIndex;
        }

        void Tree::remove(int leafNodeIndex)
        {
          assert(nodes[leafNodeIndex].isLeaf);
          if(rootNodeIndex == leafNodeIndex)
          {
            //std::cout << "removing root" << std::endl;

            deleteNode(leafNodeIndex);
            rootNodeIndex = 0;

            //std::cout << "tree amount: " << amount << std::endl;
            assert(amount == 0);
            return;
          }

          //std::cout << "removing leaf" << std::endl;

          int parentIndex = nodes[leafNodeIndex].parentIndex;
          int siblingIndex = nodes[parentIndex].child1Index;
          if(siblingIndex == leafNodeIndex)
          {
            siblingIndex = nodes[parentIndex].child2Index;
          }

          if(parentIndex == rootNodeIndex)
          {
            rootNodeIndex = siblingIndex;
          }
          else
          {
            int newParentIndex = nodes[parentIndex].parentIndex;

            nodes[siblingIndex].parentIndex = newParentIndex;

            if(nodes[newParentIndex].child1Index == parentIndex)
            {
              nodes[newParentIndex].child1Index = siblingIndex;
            }
            else
            {
              nodes[newParentIndex].child2Index = siblingIndex;
            }
            recalculateAABBs(newParentIndex);
          }

          deleteNode(leafNodeIndex);
          deleteNode(parentIndex);
        }

        /*
        void Tree::checkCrossedCollisions(unsigned int node1Index, unsigned int node2Index) const
        {
          if(nodes[node1Index].aabb.isIntersecting(nodes[node2Index].aabb))
          {
            if(nodes[node1Index].isLeaf && nodes[node2Index].isLeaf)
            {
              std::cout << "DBVT collision: " << nodes[node1Index].objectId << " / " << nodes[node2Index].objectId << std::endl;
            }
            else if(nodes[node1Index].isLeaf)
            {
              unsigned int child1Index = nodes[node2Index].child1Index;
              unsigned int child2Index = nodes[node2Index].child2Index;
              checkCrossedCollisions(node1Index, child1Index);
              checkCrossedCollisions(node1Index, child2Index);
            }
            else if(nodes[node2Index].isLeaf)
            {
              unsigned int child1Index = nodes[node1Index].child1Index;
              unsigned int child2Index = nodes[node1Index].child2Index;
              checkCrossedCollisions(node2Index, child1Index);
              checkCrossedCollisions(node2Index, child2Index);
            }
            else
            {
              unsigned int child11Index = nodes[node1Index].child1Index;
              unsigned int child12Index = nodes[node1Index].child2Index;
              unsigned int child21Index = nodes[node2Index].child1Index;
              unsigned int child22Index = nodes[node2Index].child2Index;
              checkCrossedCollisions(child11Index, child21Index);
              checkCrossedCollisions(child11Index, child22Index);
              checkCrossedCollisions(child12Index, child21Index);
              checkCrossedCollisions(child12Index, child22Index);
            }
          }
        }

        void Tree::checkInternalCollisions(unsigned int nodeIndex) const
        {
          unsigned int child1Index = nodes[nodeIndex].child1Index;
          unsigned int child2Index = nodes[nodeIndex].child2Index;

          checkCrossedCollisions(child1Index, child2Index);
          if(!nodes[child1Index].isLeaf)
          {
            checkInternalCollisions(child1Index);
          }
          if(!nodes[child2Index].isLeaf)
          {
            checkInternalCollisions(child2Index);
          }
        }

        void Tree::updateCollidingPairs() const
        {
          std::cout << "DBVT UPDATING COLLISIONS" << std::endl;
          if(amount > 0 && !nodes[rootNodeIndex].isLeaf)
          {
            std::cout << "DBVT UPDATING COLLISIONS 2" << std::endl;
            checkInternalCollisions(rootNodeIndex);
          }
        }
        */

        void Tree::getCollisions(int objectIndex, const gdmg::AABB* aabb, gdu::LinkedHashList<UIntPair>* hashList) const
        {
          if(amount <= 0)
          {
            return;
          }

          gdu::LinkedList<int> nodesToCheck;
          nodesToCheck.add(rootNodeIndex);
          while(nodesToCheck.size() > 0)
          {
            int nodeIndex = nodesToCheck.getFirst();
            nodesToCheck.removeFirst();

            int nodeAabbId = nodes[nodeIndex].aabbId;
            gdmg::AABB* nodeAabb = &(*aabbs)[nodeAabbId];

            if(nodeAabb->isIntersecting(*aabb))
            {
              if(nodes[nodeIndex].isLeaf)
              {
                if(nodes[nodeIndex].objectId != objectIndex)
                {
                  hashList->add(UIntPair(objectIndex, nodes[nodeIndex].objectId));
                }
              }
              else
              {
                nodesToCheck.add(nodes[nodeIndex].child1Index);
                nodesToCheck.add(nodes[nodeIndex].child2Index);
              }
            }
          }
        }
      }
    }
  }
}
