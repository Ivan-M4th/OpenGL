#ifndef GD_AI_PATHFINDING_PATHFINDER_H
#define GD_AI_PATHFINDING_PATHFINDER_H

#include "../../gddef.h"

#include "../../utils/MemoryArray.h"

#include "../../math/Vector3i.h"

#include "../../voxel/ChunkGrid.h"

namespace gt
{
  namespace doubovik
  {
    namespace ai
    {
      namespace pathfinding
      {
        struct Node
        {
          gdm::Vector3i position;

          int gValue = -1;
          int hValue = -1;
          int fValue = -1;

          int parent = -1;


          bool processed = false;
        };

        class Pathfinder
        {
        private:
          gdu::MemoryArray<Node> nodes;

          int size;
          int arraySize;
          int* array;

          ArrayList<int> openList;

          gdm::Vector3i minPosition; //abs
          gdm::Vector3i maxPosition; //abs
          gdm::Vector3i startPosition; //local
          gdm::Vector3i endPosition; //local

          int lastNodeId;
          ArrayList<gdm::Vector3i> path;

          gdv::ChunkGrid* chunkGrid;

          bool isValid(int, int, int) const;
          int getIndex(int, int, int) const;

          gdv::Block* getBlock(int, int, int) const; //local

          int calculateHValue(int, int, int) const; //local
          int calculateFValue(int, int) const; //g, h

          int getNextNode() const;
          void removeFromOpenList(int);

          void createStartNode();

          void processChild(int, int, int, int, int); //local, g, parentId
          void processBlock(int, int, int, int, int); //local, parentg, parentId
          bool processNode(Node*, int);

          void processNodes();
          void buildPath();
        public:
          Pathfinder(gdv::ChunkGrid*, const gdm::Vector3i&, const gdm::Vector3i&);
          ~Pathfinder();

          void calculatePath();
          const ArrayList<gdm::Vector3i>* getPath() const;
        };
      }
    }
  }
}

#endif
