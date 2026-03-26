#ifndef GD_VOXEL_CHUNKGRID_H
#define GD_VOXEL_CHUNKGRID_H

#include "../gddef.h"

#include "Chunk.h"
#include "ChunkMesh.h"
#include "BlockBuilder.h"

#include "../utils/ArrayList.h"
#include "../utils/MemoryArray.h"

#include "../math/Vector3i.h"

#include "../physics/SimulationDataManager.h"

#include "../networking/Client.h"

#include "../client/GameDataManager.h"
#include "../client/voxel/ChunkStructures.h"
#include "../client/voxel/ChunkCreatures.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      struct ChunkGridNode
      {
        Chunk chunk;

        ChunkMesh* mesh = NULL;
        bool updateMesh;

        ChunkCollider collider;
        bool updateCollider;

        gdcv::ChunkStructures structures;
        gdcv::ChunkCreatures creatures;
      };

      class ChunkGrid
      {
      private:
        gdu::MemoryArray<ChunkGridNode> nodes;
        int* nodeIds; //grid
        gdm::Vector3i position; //in chunk coords

        BlockBuilder* blockBuilder;
        gdp::SimulationDataManager* simulationDataManager;
        gdp::GridSpacePartition* terrainSimulationGrid; // to remove
        gdn::Client* client;
        gdc::GameDataManager* gameDataManager;

        void deleteChunkTrees(ArrayList<int>*);
        void deleteStructures(gdcv::ChunkStructures*);

        void deleteChunkBoars(ArrayList<int>*);
        void deleteChunkCreatures(gdcv::ChunkCreatures*);

        int createNode();
        void deleteNode(int);

        int getIndex(int, int, int) const;
        bool isValid(int, int, int) const;
        int getChunkIndex(int, int, int) const;

        bool updateChunkMesh(ChunkGridNode*, int, int, int); //local chunk coords / updated?

        //bool stop = false;
        void registerChunkCollider(ChunkCollider*, int, int, int); //abs chunk coords
        void unregisterChunkCollider(ChunkCollider*);
        void updateChunkCollider(ChunkGridNode*, int, int, int); //local chunk coords

        bool getBorderChunks(int, int, int, Chunk**, Chunk**, Chunk**, Chunk**, Chunk**, Chunk**) const;
      public:
        ChunkGrid(BlockBuilder*, gdp::SimulationDataManager*, gdp::GridSpacePartition*, gdn::Client*, gdc::GameDataManager* gameDataManager);
        ChunkGrid(const ChunkGrid&);
        ChunkGrid& operator=(const ChunkGrid&);
        ~ChunkGrid();

        void clear();
        int getSize() const;
        int getHWidth() const;
        int getHHeight() const;
        const gdm::Vector3i& getPosition() const;

        Chunk* getLocalChunk(int, int, int) const; //local coords
        ChunkGridNode* getNode(int, int, int) const; //local coords
        ChunkGridNode* getNode(int) const;
        ChunkGridNode* getNodeByAbsolute(int, int, int) const; //abs coords
        Chunk* getChunk(int, int, int) const; //abs chunk coords
        Block* getBlock(int, int, int) const; //abs block coords

        void raycastToBlock(const gdm::Vector3&, const gdm::Vector3&, BlockInfo*) const;
        void raycastToBlockBefore(const gdm::Vector3&, const gdm::Vector3&, BlockInfo*) const;

        void setPosition(const gdm::Vector3i&); //in chunk coords

        bool loadNextMeshInColumn(int, int); //stop search?
        void loadNextMesh();

        bool loadNextColliderInColumn(int, int); //stop search?
        void loadNextCollider();

        void requestNextChunksInColumn(int, int, int*);
        void requestNextChunks();

        void loadChunk(int, int, int, Chunk*); //load Chunk

        void deleteChunkTrees(int, int, int); //abs chunk coords
        void loadChunkTrees(int, int, int, ArrayList<int>*); //abs

        void deleteChunkBoars(int, int, int); //abs
        void loadChunkBoars(int, int, int, ArrayList<int>*); //abs

        void updateChunk(int, int, int); //abs chunk coords
        void updateBlock(int, int, int);

        void removeBoar(int, const gdm::Vector3i&); //id, abs
        bool addBoar(int, const gdm::Vector3i&); //id, abs -> succes?
      };
    }
  }
}

#endif
