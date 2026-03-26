#include "PacketListener.h"

#include <iostream>

#include "../../utils/Pointer.h"

#include "../../math/Vector3.h"
#include "../../math/Quaternion.h"

#include "../objects/MainPlayer.h"
#include "../objects/Player.h"
#include "../objects/Tree.h"

#include "../../voxel/Chunk.h"
#include "../../voxel/Block.h"

#include "../../items/ItemStack.h"

#include "../../networking/Packet.h"

#include "../../events/Events.h"

#include "../events/ConnectionPacketReceiveEvent.h"
#include "../events/MainPlayerSpawnEvent.h"
#include "../events/ChunkGeneratedEvent.h"
#include "../events/PlayerSpawnEvent.h"
#include "../events/PlayerUpdatePacketReceiveEvent.h"
#include "../events/PlayerDespawnPacketReceiveEvent.h"
#include "../events/MainPlayerSetItemStackEvent.h"


namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        PacketListener::PacketListener(gdn::Client* client, Players* players, gdv::ChunkGrid* chunkGrid, GameDataManager* gameDataManager)
        {
          this->client = client;
          this->players = players;
          this->chunkGrid = chunkGrid;
          this->gameDataManager = gameDataManager;
        }

        PacketListener::PacketListener(const PacketListener& listener)
        {
          client = listener.client;
          players = listener.players;
          chunkGrid = listener.chunkGrid;
          gameDataManager = listener.gameDataManager;
        }

        PacketListener& PacketListener::operator=(const PacketListener& listener)
        {
          client = listener.client;
          players = listener.players;
          chunkGrid = listener.chunkGrid;
          gameDataManager = listener.gameDataManager;
          return *this;
        }

        void PacketListener::handleConnection(gdu::BufferReader* reader) const
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::SERVER_INFO)
          {
            handleServerInfo(reader);
          }
        }

        void PacketListener::handleServerInfo(gdu::BufferReader* reader) const
        {
          unsigned int maxPlayers = reader->readNextUInt();
          gdce::ConnectionPacketReceiveEvent event(maxPlayers);
          gde::onEvent(event);
        }

        void PacketListener::handleGameInfo(gdu::BufferReader* reader) const
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::MAIN_PLAYER_SPAWN)
          {
            handleMainPlayerSpawn(reader);
          }
          else if(dataFlag == gdn::PLAYER_SPAWN)
          {
            handlePlayerSpawn(reader);
          }
          else if(dataFlag == gdn::PLAYER_UPDATE)
          {
            handlePlayerUpdate(reader);
          }
          else if(dataFlag == gdn::PLAYER_DESPAWN)
          {
            handlePlayerDespawn(reader);
          }
          else if(dataFlag == gdn::PLAYER_PLAY_ACTION)
          {
            handlePlayerPlayAction(reader);
          }
          else if(dataFlag == gdn::UPDATE_BOAR)
          {
            handleBoarUpdate(reader);
          }
        }

        void PacketListener::handleMainPlayerSpawn(gdu::BufferReader* reader) const
        {
          std::cout << "main player spawning at log rot:" << std::endl;
          gdm::Vector3 position = reader->readNextVector3();
          position.print();
          gdm::Quaternion rotation = reader->readNextQuaternion();
          rotation.print();

          Pointer<gdco::MainPlayer> player(new gdco::MainPlayer(), false);
          player.value()->transformation.position = position;
          player.value()->transformation.rotation = rotation;
          player.value()->calculateInformation();

          gdce::MainPlayerSpawnEvent event(player);
          gde::onEvent(event);
        }

        void PacketListener::handlePlayerSpawn(gdu::BufferReader* reader) const
        {
          unsigned int clientId = reader->readNextUInt();
          gdm::Vector3 position = reader->readNextVector3();
          gdm::Quaternion rotation = reader->readNextQuaternion();

          Pointer<gdco::Player> player(new gdco::Player(), false);
          player.value()->transformation.position = position;
          player.value()->transformation.rotation = rotation;
          player.value()->calculateInformation();

          gdce::PlayerSpawnEvent event(clientId, player);
          gde::onEvent(event);
        }

        void PacketListener::handlePlayerUpdate(gdu::BufferReader* reader) const
        {
          unsigned int clientId = reader->readNextInt();

          gdm::Vector3 position = reader->readNextVector3();
          gdm::Vector3 speed = reader->readNextVector3();
          gdm::Quaternion rotation = reader->readNextQuaternion();
          gdm::Vector3 rotationSpeed = reader->readNextVector3();

          gdce::PlayerUpdatePacketReceiveEvent event(clientId, &position, &speed, &rotation, &rotationSpeed);
          gde::onEvent(event);
        }

        void PacketListener::handlePlayerDespawn(gdu::BufferReader* reader) const
        {
          unsigned int clientId = reader->readNextUInt();

          gdce::PlayerDespawnPacketReceiveEvent event(clientId);
          gde::onEvent(event);
        }

        void PacketListener::handlePlayerPlayAction(gdu::BufferReader* reader) const
        {
          unsigned int clientId = reader->readNextUInt();
          gdco::Player* player = players->getPlayer(clientId);
          if(player != NULL)
          {
            player->useItem();
          }
        }

        void PacketListener::handleBoarUpdate(gdu::BufferReader* reader) const
        {
          int objectId = reader->readNextInt();
          gdm::Vector3 position = reader->readNextVector3();
          gdm::Vector3 speed = reader->readNextVector3();
          gdm::Quaternion rotation = reader->readNextQuaternion();
          gdm::Vector3 rotationSpeed = reader->readNextVector3();
          //std::cout << "updating boar: " << objectId << " at position:" << std::endl;
          //std::cout << position.getX() << " : " << position.getY() << " : " << position.getZ() << std::endl;

          if(gameDataManager->getBoarsManager()->isUsed(objectId))
          {
            gdco::Boar* boar = gameDataManager->getBoarsManager()->get(objectId);
            boar->transformation.position = position;
            boar->transformation.rotation = rotation;

            boar->calculateInformation();
            //std::cout << "sucess updating boar: " << objectId << std::endl;
          }
        }

        void PacketListener::handleTerrainInfo(gdu::BufferReader* reader) const
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::SEND_CHUNK)
          {
            handleChunkReceive(reader);
          }
          else if(dataFlag == gdn::SET_BLOCK)
          {
            handleSetBlock(reader);
          }
          else if(dataFlag == gdn::SEND_CHUNK_TREES)
          {
            handleChunkTreesReceive(reader);
          }
          else if(dataFlag == gdn::SEND_CHUNK_BOARS)
          {
            handleChunkBoarsReceive(reader);
          }
        }

        void PacketListener::handleChunkReceive(gdu::BufferReader* reader) const
        {
          int cx = reader->readNextInt();
          int cy = reader->readNextInt();
          int cz = reader->readNextInt();
          Pointer<gdv::Chunk> chunk = reader->readNextChunk();
          gdce::ChunkGeneratedEvent event(cx, cy, cz, chunk);
          gde::onEvent(event);
        }

        void PacketListener::handleSetBlock(gdu::BufferReader* reader) const
        {
          int bx = reader->readNextInt();
          int by = reader->readNextInt();
          int bz = reader->readNextInt();

          gdv::Block* block = chunkGrid->getBlock(bx, by, bz);
          if(block != NULL)
          {
            unsigned int materialId = reader->readNextUInt();
            block->setMaterial(materialId);
            chunkGrid->updateBlock(bx, by, bz);
          }
        }

        void PacketListener::handleChunkTreesReceive(gdu::BufferReader* reader) const
        {
          int cx = reader->readNextInt();
          int cy = reader->readNextInt();
          int cz = reader->readNextInt();
          int amount = reader->readNextInt();
          std::cout << "Loading chunk trees at " << cx << " : " << cy << " : " << cz << std::endl;
          std::cout << "received: " << amount << " trees" << std::endl;

          chunkGrid->deleteChunkTrees(cx, cy, cz);

          ArrayList<int> trees;
          for(int i=0;i<amount;i++)
          {
            int objectId = reader->readNextInt();
            gdm::Vector3 position = reader->readNextVector3();
            gdm::Quaternion rotation = reader->readNextQuaternion();

            std::cout << "received tree: " << objectId << " at position " << position << std::endl;

            if(gameDataManager->getTreesManager()->isUsed(objectId))
            {
              std::cout << "tree already created!" << std::endl;
            }
            else
            {
              std::cout << "creating tree with id: " << objectId << std::endl;
              gdco::Tree* tree = gameDataManager->getTreesManager()->createData(objectId);
              tree->transformation.position = position;
              tree->transformation.rotation = rotation;
              tree->calculateInformation();

              gameDataManager->getSimulation()->addStructure(gameDataManager->getTreesManager()->getSimulationId(objectId));
              gameDataManager->getTreesManager()->setChunkPosition(objectId, cx, cy, cz);
            }


            trees.add(objectId);
          }
          chunkGrid->loadChunkTrees(cx, cy, cz, &trees);
          //assert(false); for receive test
        }

        void PacketListener::handleChunkBoarsReceive(gdu::BufferReader* reader) const
        {
          int cx = reader->readNextInt();
          int cy = reader->readNextInt();
          int cz = reader->readNextInt();
          int amount = reader->readNextInt();
          std::cout << "Loading chunk boars at " << cx << " : " << cy << " : " << cz << std::endl;
          std::cout << "received: " << amount << " boars" << std::endl;

          chunkGrid->deleteChunkBoars(cx, cy, cz);

          ArrayList<int> boars;
          for(int i=0;i<amount;i++)
          {
            int objectId = reader->readNextInt();
            gdm::Vector3 position = reader->readNextVector3();
            gdm::Quaternion rotation = reader->readNextQuaternion();

            std::cout << "received boar: " << objectId << " at position " << position << std::endl;

            if(gameDataManager->getBoarsManager()->isUsed(objectId))
            {
              std::cout << "boar already created!" << std::endl;
            }
            else
            {
              std::cout << "creating boar with id: " << objectId << std::endl;
              gdco::Boar* boar = gameDataManager->getBoarsManager()->createData(objectId);
              boar->transformation.position = position;
              boar->transformation.rotation = rotation;
              boar->calculateInformation();

              gameDataManager->getSimulation()->add(gameDataManager->getBoarsManager()->getSimulationId(objectId));
              gameDataManager->getBoarsManager()->setChunkPosition(objectId, cx, cy, cz);
            }

            //add to simulation

            boars.add(objectId);
          }
          chunkGrid->loadChunkBoars(cx, cy, cz, &boars);
        }

        void PacketListener::handleInventoryInfo(gdu::BufferReader* reader) const
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::SET_ITEM)
          {
            handleSetItem(reader);
          }
          else if(dataFlag == gdn::PLAYER_EQUIPED_ITEM)
          {
            handlePlayerEquipedItem(reader);
          }
        }

        void PacketListener::handleSetItem(gdu::BufferReader* reader) const
        {
          unsigned int slot = reader->readNextUInt();
          gdi::ItemStack itemStack = reader->readNextItemStack();
          if(!itemStack.isEmpty())
          {
            gdce::MainPlayerSetItemStackEvent event(slot, &itemStack);
            gde::onEvent(event);
          }
        }

        void PacketListener::handlePlayerEquipedItem(gdu::BufferReader* reader) const
        {
          unsigned int clientId = reader->readNextUInt();
          gdco::Player* player = players->getPlayer(clientId);
          if(player != NULL)
          {
            unsigned int location = reader->readNextUInt();

            player->itemStackInRightHand = reader->readNextItemStack();
            player->onItemEquip();
          }
        }

        void PacketListener::onEvent(gdce::PacketReceiveEvent* event)
        {
          gdu::BufferReader* reader = event->getReader();
          unsigned int dataType = reader->readNextUInt();
          if(dataType == gdn::CONNECTION)
          {
            handleConnection(reader);
          }
          else if(dataType == gdn::GAME_INFO)
          {
            handleGameInfo(reader);
          }
          else if(dataType == gdn::TERRAIN_INFO)
          {
            handleTerrainInfo(reader);
          }
          else if(dataType == gdn::INVENTORY_INFO)
          {
            handleInventoryInfo(reader);
          }
        }
      }
    }
  }
}
