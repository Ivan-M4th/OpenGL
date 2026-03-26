#include "Terrain.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      Terrain::Terrain(gds::GameDataManager* gameDataManager, ChunkGenerator* chunkGenerator)
      {
        loadRegion(gdm::Vector3i(0,0,0));

        this->gameDataManager = gameDataManager;
        this->chunkGenerator = chunkGenerator;
      }

      Terrain::Terrain(const Terrain& terrain)
      {
        //to do
        gameDataManager = terrain.gameDataManager;
        chunkGenerator = terrain.chunkGenerator;
      }

      Terrain& Terrain::operator=(const Terrain& terrain)
      {
        //to do
        gameDataManager = terrain.gameDataManager;
        chunkGenerator = terrain.chunkGenerator;
        return *this;
      }

      int Terrain::loadedRegionsSize() const
      {
        return regionIds.size();
      }

      Region* Terrain::getRegion(const gdm::Vector3i& position) const //ok
      {
        int* id = regionIds.get(position);
        if(id == NULL)
        {
          return NULL;
        }
        assert(*id != -1);
        return &regions[*id];
      }

      Region* Terrain::getRegionAtChunk(int cx, int cy, int cz) const //ok
      {
        gdm::Vector3i position;
        chunkCoordsToRegionCoords(cx, cy, cz, &position.x, &position.y, &position.z);
        return getRegion(position);
      }

      RegionNode* Terrain::getChunk(int cx, int cy, int cz) const //ok
      {
        gdm::Vector3i regionPosition;
        chunkCoordsToRegionCoords(cx, cy, cz, &regionPosition.x, &regionPosition.y, &regionPosition.z);
        Region* region = getRegion(regionPosition);

        if(region == NULL)
        {
          return NULL;
        }

        int lcx;
        int lcy;
        int lcz;
        chunkCoordsToLocalRegionChunkCoords(regionPosition.x, regionPosition.y, regionPosition.z, cx, cy, cz, &lcx, &lcy, &lcz);

        return region->getNode(lcx, lcy, lcz);
      }

      void Terrain::updateChunk(int cx, int cy, int cz)
      {
        RegionNode* regionNode = getChunk(cx, cy, cz);
        if(regionNode != NULL)
        {
          Chunk* chunk = &regionNode->chunk;
          ChunkCollider* collider = &regionNode->collider;

          unregisterChunkCollider(gameDataManager->getSimulationDataManager(), collider);
          deleteChunkCollider(collider);
          createChunkCollider(cx, cy, cz, chunk, collider);
          registerChunkCollider(gameDataManager->getSimulationDataManager(), cx, cy, cz, collider);
        }
      }

      void Terrain::updateChunkAtBlock(int bx, int by, int bz)
      {
        int cx;
        int cy;
        int cz;
        blockCoordsToChunkCoords(bx, by, bz, &cx, &cy, &cz);
        updateChunk(cx, cy, cz);
      }

      Block* Terrain::getBlock(int bx, int by, int bz) const
      {
        int cx;
        int cy;
        int cz;
        blockCoordsToChunkCoords(bx, by, bz, &cx, &cy, &cz);

        RegionNode* regionNode = getChunk(cx, cy, cz);
        if(regionNode == NULL)
        {
          return NULL;
        }

        int lbx;
        int lby;
        int lbz;
        blockCoordsToLocalChunkBlockCoords(cx, cy, cz, bx, by, bz, &lbx, &lby, &lbz);

        return regionNode->chunk.getBlock(lbx, lby, lbz);
      }

      RegionNode* Terrain::generateChunk(int cx, int cy, int cz)
      {
        gdm::Vector3i regionPosition;
        chunkCoordsToRegionCoords(cx, cy, cz, &regionPosition.x, &regionPosition.y, &regionPosition.z);
        Region* region = getRegion(regionPosition);

        if(region == NULL)
        {
          std::cout << "REGION NULL!" << std::endl;
          return NULL;
        }

        int lcx;
        int lcy;
        int lcz;
        chunkCoordsToLocalRegionChunkCoords(regionPosition.x, regionPosition.y, regionPosition.z, cx, cy, cz, &lcx, &lcy, &lcz);

        RegionNode* regionNode = region->getNode(lcx, lcy, lcz);

        if(regionNode == NULL)
        {
          regionNode = region->genNode(lcx, lcy, lcz);
          chunkGenerator->generateChunk(cx, cy, cz, &regionNode->chunk, &regionNode->structures, &regionNode->creatures);

          createChunkCollider(cx, cy, cz, &regionNode->chunk, &regionNode->collider);
          registerChunkCollider(gameDataManager->getSimulationDataManager(), cx, cy, cz, &regionNode->collider);
        }
        return regionNode;
      }

      void Terrain::loadRegion(const gdm::Vector3i& position)
      {
        int* id = regionIds.get(position);
        if(id != NULL)
        {
          assert(*id != -1);
          return;
        }
        int newId = regions.genSlot();
        regions[newId].nodes = &nodes;
        regionIds.set(position, newId);

        id = regionIds.get(position);
        if(id == NULL)
        {
          std::cout << "error creating region at " << position << std::endl;
        }
        else
        {
          std::cout << "created region at postion " << position << std::endl;
          std::cout << "with id " << *id << std::endl;
        }
      }

      void Terrain::unLoadRegion(const gdm::Vector3i& position)
      {
        int* id = regionIds.get(position);
        if(id == NULL)
        {
          return;
        }

        assert(*id != -1);
        Region* region = &regions[*id];

        //unloading region
        region->deleteChunks(gameDataManager);

        //freeing space
        regions.free(*id);
        regionIds.remove(position);
      }

      bool Terrain::isNear(const gdm::Vector3i& v1, const gdm::Vector3i& v2, int distance) const
      {
        gdm::Vector3i d = v2 - v1;
        if(-distance <= d.x && d.x <= distance)
        {
          if(-distance <= d.y && d.y <= distance)
          {
            if(-distance <= d.z && d.z <= distance)
            {
              return true;
            }
          }
        }
        return false;
      }

      bool Terrain::isNearPlayer(const gdm::Vector3i& v, gdso::Player* player, int distance) const
      {
        int bx;
        int by;
        int bz;
        toBlockCoords(player->transformation.position.getX(), player->transformation.position.getY(), player->transformation.position.getZ(), &bx, &by, &bz);

        int cx;
        int cy;
        int cz;
        blockCoordsToChunkCoords(bx, by, bz, &cx, &cy, &cz);

        gdm::Vector3i regionCoords;
        chunkCoordsToRegionCoords(cx, cy, cz, &regionCoords.x, &regionCoords.y, &regionCoords.z);

        return isNear(v, regionCoords, distance);
      }

      bool Terrain::isFarRegion(const ArrayList<gdso::Player*>& players, const gdm::Vector3i& v) const
      {
        if(v == gdm::Vector3i(0,0,0))
        {
          return false;
        }

        for(int i=0;i<players.size();i++)
        {
          if(isNearPlayer(v, players[i], 4))
          {
            return false;
          }
        }
        return true;
      }

      void Terrain::removeFarRegions(const ArrayList<gdso::Player*>& players)
      {
        gdu::LinkedHashMapIterator<gdm::Vector3i, int> iterator(&regionIds);
        while(iterator.isValid())
        {
          if(isFarRegion(players, iterator.getKey()))
          {
            std::cout << "unloading region " << iterator.getKey() << " with id " << iterator.getValue() << std::endl;

            int id = iterator.getValue();
            assert(id != -1);
            regions[id].deleteChunks(gameDataManager);
            regions.free(id);

            iterator.remove();
          }
          else
          {
            iterator.next();
          }
        }
      }

      void Terrain::loadRegionsNear(const gdm::Vector3i& v, int distance)
      {
        for(int x=-distance;x<=distance;x++)
        {
          for(int y=-distance;y<=distance;y++)
          {
            for(int z=-distance;z<=distance;z++)
            {
              gdm::Vector3i position = v + gdm::Vector3i(x, y, z);
              loadRegion(position);
            }
          }
        }
      }

      void Terrain::loadNearRegions(const ArrayList<gdso::Player*>& players)
      {
        for(int i=0;i<players.size();i++)
        {
          int bx;
          int by;
          int bz;
          toBlockCoords(players[i]->transformation.position.getX(), players[i]->transformation.position.getY(), players[i]->transformation.position.getZ(), &bx, &by, &bz);

          int cx;
          int cy;
          int cz;
          blockCoordsToChunkCoords(bx, by, bz, &cx, &cy, &cz);

          gdm::Vector3i regionCoords;
          chunkCoordsToRegionCoords(cx, cy, cz, &regionCoords.x, &regionCoords.y, &regionCoords.z);
          loadRegionsNear(regionCoords, 2);
        }
      }

      void Terrain::update(const ArrayList<gdso::Player*>& players)
      {
        removeFarRegions(players);
        loadNearRegions(players);
      }

      void Terrain::getObjectsToUpdate(const gdm::Vector3i& position, int distance, gds::ObjectsToUpdate* objectsToUpdate) const
      {
        for(int ix=-distance;ix<=distance;ix++)
        {
          for(int iy=-distance;iy<=distance;iy++)
          {
            for(int iz=-distance;iz<=distance;iz++)
            {
              int cx = position.x + ix;
              int cy = position.y + iy;
              int cz = position.z + iz;

              RegionNode* regionNode = getChunk(cx, cy, cz);
              if(regionNode != NULL)
              {
                ArrayList<int>* boars = &regionNode->creatures.boars;
                for(int i=0;i<boars->size();i++)
                {
                  int objectId = (*boars)[i];
                  objectsToUpdate->boars.add(objectId);

                  int simulationId = gameDataManager->getBoarsManager()->getSimulationId(objectId);
                  objectsToUpdate->simulationIds.add(simulationId);
                }
              }
            }
          }
        }
      }

      void Terrain::getObjectsToUpdate(const ArrayList<gdso::Player*>* players, gds::ObjectsToUpdate* objectsToUpdate) const
      {
        for(int i=0;i<players->size();i++)
        {
          gdso::Player* player = (*players)[i];
          int bx;
          int by;
          int bz;
          toBlockCoords(player->transformation.position.getX(), player->transformation.position.getY(), player->transformation.position.getZ(), &bx, &by, &bz);

          gdm::Vector3i position;
          blockCoordsToChunkCoords(bx, by, bz, &position.x, &position.y, &position.z);
          getObjectsToUpdate(position, 2, objectsToUpdate);
        }
      }

      void Terrain::removeBoar(const gdm::Vector3i& chunkPosition, int objectId)
      {
        RegionNode* regionNode = getChunk(chunkPosition.x, chunkPosition.y, chunkPosition.z);
        assert(regionNode != NULL);
        regionNode->creatures.boars.removeElement(objectId);
      }

      bool Terrain::addBoar(const gdm::Vector3i& chunkPosition, int objectId)
      {
        RegionNode* regionNode = getChunk(chunkPosition.x, chunkPosition.y, chunkPosition.z);
        if(regionNode == NULL)
        {
          return false;
        }
        regionNode->creatures.boars.add(objectId);
        return true;
      }
    }
  }
}
