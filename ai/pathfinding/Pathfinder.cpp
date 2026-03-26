#include "Pathfinder.h"

#include <iostream>
#include <cmath>
#include <cassert>

#include "../../voxel/Materials.h"

namespace gt
{
  namespace doubovik
  {
    namespace ai
    {
      namespace pathfinding
      {
        const int BORDER_SIZE = 4;

        Pathfinder::Pathfinder(gdv::ChunkGrid* chunkGrid, const gdm::Vector3i& start, const gdm::Vector3i& end)
        {
          this->chunkGrid = chunkGrid;

          minPosition.x = std::min(start.x, end.x) - BORDER_SIZE;
          minPosition.y = std::min(start.y, end.y) - BORDER_SIZE;
          minPosition.z = std::min(start.z, end.z) - BORDER_SIZE;

          maxPosition.x = std::max(start.x, end.x) + BORDER_SIZE;
          maxPosition.y = std::max(start.y, end.y) + BORDER_SIZE;
          maxPosition.z = std::max(start.z, end.z) + BORDER_SIZE;

          startPosition = start - minPosition;
          endPosition = end - minPosition;

          gdm::Vector3i toMax = maxPosition - minPosition;
          size = std::max(toMax.x, toMax.y);
          size = std::max(size, toMax.z);

          arraySize = size*size*size;

          array = new int[arraySize];
          for(int i=0;i<arraySize;i++)
          {
            *(array + i) = -1;
          }

          lastNodeId = -1;
        }

        Pathfinder::~Pathfinder()
        {
          delete [] array;
        }

        bool Pathfinder::isValid(int x, int y, int z) const
        {
          if(0 <= x && x < size)
          {
            if(0 <= y && y < size)
            {
              if(0 <= z && z < size)
              {
                return true;
              }
            }
          }
          return false;
        }

        gdv::Block* Pathfinder::getBlock(int x, int y, int z) const
        {
          return chunkGrid->getBlock(minPosition.x + x, minPosition.y + y, minPosition.z + z);
        }

        int Pathfinder::getIndex(int x, int y, int z) const
        {
          return (x*size + y)*size + z;
        }

        int Pathfinder::calculateHValue(int x, int y, int z) const
        {
          return abs(endPosition.x - x) + abs(endPosition.y - y) + abs(endPosition.z - z);
        }

        int Pathfinder::calculateFValue(int gValue, int hValue) const
        {
          return gValue + hValue;
        }

        int Pathfinder::getNextNode() const
        {
          assert(openList.size() > 0);
          int id = openList[0];
          for(int i=1;i<openList.size();i++)
          {
            if(nodes[id].fValue > nodes[openList[i]].fValue)
            {
              id = openList[i];
            }
          }
          return id;
        }

        void Pathfinder::removeFromOpenList(int id)
        {
          assert(openList.size() > 0);
          for(int i=0;i<openList.size();)
          {
            if(openList[i] == id)
            {
              openList.remove(i);
            }
            else
            {
              i++;
            }
          }
        }

        void Pathfinder::createStartNode()
        {
          int id = nodes.genSlot();
          Node* node = &nodes[id];

          node->position = startPosition;

          node->gValue = 0;
          node->hValue = 0;
          node->fValue = 0;

          node->processed = true;

          assert(isValid(startPosition.x, startPosition.y, startPosition.z));
          *(array + getIndex(startPosition.x, startPosition.y, startPosition.z)) = id;

          openList.add(id);
        }

        void Pathfinder::processChild(int x, int y, int z, int gValue, int parentId)
        {
          if(!isValid(x, y, z))
          {
            return;
          }

          int index = getIndex(x, y, z);
          int id = *(array + index);
          if(id != -1)
          {
            Node* node = &nodes[id];
            if(node->processed)
            {
              return;
            }

            int fValue = calculateFValue(gValue, node->hValue);

            if(fValue < node->fValue)
            {
              node->gValue = gValue;
              node->fValue = fValue;

              node->parent = parentId;
            }
          }
          else
          {
            //check if process

            id = nodes.genSlot();
            *(array + index) = id;

            Node* node = &nodes[id];

            node->position = gdm::Vector3i(x, y, z);

            node->gValue = gValue;
            node->hValue = calculateHValue(x, y, z);
            node->fValue = calculateFValue(node->gValue, node->hValue);

            node->parent = parentId;

            node->processed = false;

            //add to openList
            openList.add(id);
          }
        }

        void Pathfinder::processBlock(int x, int y, int z, int gValue, int id)
        {
          gdv::Block* block = getBlock(x, y, z);

          if(block != NULL)
          {
            if(gdv::getMaterial(block->getMaterialId())->isSolid())
            {
              gdv::Block* ypBlock = getBlock(x, y + 1, z);
              if(ypBlock != NULL)
              {
                if(!gdv::getMaterial(ypBlock->getMaterialId())->isSolid())
                {
                  processChild(x, y + 1, z, gValue + 14, id);
                }
              }
            }
            else
            {
              processChild(x, y, z, gValue + 10, id);
            }
          }
        }

        bool Pathfinder::processNode(Node* node, int id)
        {
          node->processed = true;

          if(node->position == endPosition)
          {
            return true;
          }

          int x = node->position.x;
          int y = node->position.y;
          int z = node->position.z;


          gdv::Block* ymBlock = getBlock(x, y - 1, z);
          if(ymBlock != NULL)
          {
            if(gdv::getMaterial(ymBlock->getMaterialId())->isSolid())
            {
              processBlock(x - 1, y, z, node->gValue, id);
              processBlock(x + 1, y, z, node->gValue, id);

              processBlock(x, y, z - 1, node->gValue, id);
              processBlock(x, y, z + 1, node->gValue, id);
            }
            else
            {
              gdv::Block* ymmBlock = getBlock(x, y - 2, z);
              if(ymmBlock != NULL)
              {
                if(gdv::getMaterial(ymmBlock->getMaterialId())->isSolid())
                {
                  processBlock(x, y - 1, z, node->gValue, id);
                }
              }
            }
          }

          return false;
        }

        void Pathfinder::processNodes()
        {
          int MAX_ITT = 1000;
          int i = 0;

          while(openList.size() > 0)
          {
            int id = getNextNode();
            Node* node = &nodes[id];

            if(processNode(node, id))
            {
              lastNodeId = id;
              break;
            }

            removeFromOpenList(id);

            i++;
            if(i >= MAX_ITT)
            {
              break;
            }
          }
        }

        void Pathfinder::buildPath()
        {
          assert(lastNodeId != -1);
          int id = lastNodeId;

          while(id != -1)
          {
            Node* node = &nodes[id];
            path.add(minPosition + node->position);
            id = node->parent;
          }
        }

        void Pathfinder::calculatePath()
        {
          createStartNode();
          processNodes();
          buildPath();
        }

        const ArrayList<gdm::Vector3i>* Pathfinder::getPath() const
        {
          return &path;
        }
      }
    }
  }
}
