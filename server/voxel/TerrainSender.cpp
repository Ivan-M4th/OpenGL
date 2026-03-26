#include "TerrainSender.h"

#include <iostream>

#include "../../voxel/Chunk.h"

#include "../../utils/OuterSpiralIterator.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace voxel
      {
        TerrainSender::TerrainSender(int numPlayers, ServerManager* serverManager, gdv::Terrain* terrain, GameDataManager* gameDataManager)
        {
          this->numPlayers = numPlayers;
          this->serverManager = serverManager;
          this->terrain = terrain;
          this->gameDataManager = gameDataManager;

          loadedTerrains = new LoadedTerrain[numPlayers];
        }

        TerrainSender::~TerrainSender()
        {
          delete [] loadedTerrains;
        }

        bool TerrainSender::sendNextChunkInColumn(int clientId, int x, int z)
        {
          LoadedTerrain* loadedTerrain = loadedTerrains + clientId;
          for(int y=0;y<loadedTerrain->getHeight();y++)
          {
            if(!loadedTerrain->isLoaded(x, y, z))
            {
              //std::cout << "processing chunk to send " << x << " : " << y << " : " << z << std::endl;

              int cx = loadedTerrain->getPosition().x + x;
              int cy = loadedTerrain->getPosition().y + y;
              int cz = loadedTerrain->getPosition().z + z;

              gdv::RegionNode* regionNode = terrain->getChunk(cx, cy, cz);
              if(regionNode != NULL)
              {
                serverManager->sendChunkPacket(clientId, cx, cy, cz, &regionNode->chunk);

                if(regionNode->structures.trees.size() > 0)
                {
                  serverManager->sendChunkTreesPacket(clientId, gameDataManager, cx, cy, cz, &regionNode->structures.trees);
                }
                if(regionNode->creatures.boars.size() > 0)
                {
                  serverManager->sendChunkBoarsPacket(clientId, gameDataManager, cx, cy, cz, &regionNode->creatures.boars);
                }
                //std::cout << "Chunk sent" << std::endl;
              }
              else
              {
                regionNode = terrain->generateChunk(cx, cy, cz);
                if(regionNode != NULL)
                {
                  serverManager->sendChunkPacket(clientId, cx, cy, cz, &regionNode->chunk);

                  if(regionNode->structures.trees.size() > 0)
                  {
                    serverManager->sendChunkTreesPacket(clientId, gameDataManager, cx, cy, cz, &regionNode->structures.trees);
                  }
                  if(regionNode->creatures.boars.size() > 0)
                  {
                    serverManager->sendChunkBoarsPacket(clientId, gameDataManager, cx, cy, cz, &regionNode->creatures.boars);
                  }
                  //std::cout << "Chunk sent" << std::endl;
                }
                else
                {
                  std::cout << "processing chunk to send " << x << " : " << y << " : " << z << std::endl;
                  std::cout << "ERROR! chunk is NULL!" << std::endl;
                }
              }

              loadedTerrain->setLoaded(x, y, z, true);
              return true;
            }
          }
          return false;
        }

        void TerrainSender::sendNextChunkTo(int clientId)
        {
          LoadedTerrain* loadedTerrain = loadedTerrains + clientId;
          for(OuterSpiralIterator osi(loadedTerrain->getHWidth(), loadedTerrain->getHWidth());osi.isValid();osi.next())
          {
            if(sendNextChunkInColumn(clientId, osi.getX(), osi.getY()))
            {
              return;
            }
          }
        }

        void TerrainSender::sendNextChunk()
        {
          for(int i=0;i<numPlayers;i++)
          {
            if(serverManager->isOnline(i))
            {
              sendNextChunkTo(i);
            }
          }
        }

        void TerrainSender::setPosition(int clientId, const gdm::Vector3i& position)
        {
          (loadedTerrains + clientId)->setPosition(position);
        }

        void TerrainSender::requestChunk(int clientId, int cx, int cy, int cz)
        {
          LoadedTerrain* loadedTerrain = (loadedTerrains + clientId);
          int x = cx - loadedTerrain->getPosition().x;
          int y = cy - loadedTerrain->getPosition().y;
          int z = cz - loadedTerrain->getPosition().z;

          if(loadedTerrain->isValid(x, y, z))
          {
            //std::cout << "client requested " << x << " : " << x << " : " << y << " : " << z << std::endl;
            loadedTerrain->setLoaded(x, y, z, false);
          }
        }
      }
    }
  }
}
