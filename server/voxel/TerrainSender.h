#ifndef GD_SERVER_VOXEL_TERRAINSENDER_H
#define GD_SERVER_VOXEL_TERRAINSENDER_H

#include "../../gddef.h"

#include "LoadedTerrain.h"

#include "../GameDataManager.h"
#include "../ServerManager.h"

#include "../../voxel/Terrain.h"

#include "../../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace voxel
      {
        class TerrainSender
        {
        private:
          int numPlayers;
          LoadedTerrain* loadedTerrains;

          ServerManager* serverManager;
          gdv::Terrain* terrain;
          GameDataManager* gameDataManager;

        public:
          TerrainSender(int, ServerManager*, gdv::Terrain*, GameDataManager*);
          ~TerrainSender();

          bool sendNextChunkInColumn(int, int, int);
          void sendNextChunkTo(int);
          void sendNextChunk();
          void setPosition(int, const gdm::Vector3i&);
          void requestChunk(int, int, int, int); //abs coords
        };
      }
    }
  }
}

#endif
