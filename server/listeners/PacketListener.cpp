#include "PacketListener.h"

#include <iostream>

#include "../../events/Events.h"

#include "../events/ConnectionPacketReceiveEvent.h"
#include "../events/RequestSpawnPacketReceiveEvent.h"
#include "../events/ChunkRequestEvent.h"
#include "../events/ClientUpdatePacketReceiveEvent.h"

#include "../../networking/Packet.h"

#include "../packets/PlayerPlayActionPacket.h"

#include "../../math/Vector3i.h"
#include "../../math/Vector3.h"
#include "../../math/Quaternion.h"

#include "../objects/Player.h"

#include "../../items/ItemStack.h"

#include "../../voxel/Block.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        PacketListener::PacketListener(ServerManager* serverManager, Players* players, gdv::Terrain* terrain, gdsv::TerrainSender* terrainSender)
        {
          this->serverManager = serverManager;
          this->players = players;
          this->terrain = terrain;
          this->terrainSender = terrainSender;
        }

        PacketListener::PacketListener(const PacketListener& listener)
        {
          serverManager = listener.serverManager;
          players = listener.players;
          terrain = listener.terrain;
          terrainSender = listener.terrainSender;
        }

        PacketListener& PacketListener::operator=(const PacketListener& listener)
        {
          serverManager = listener.serverManager;
          players = listener.players;
          terrain = listener.terrain;
          terrainSender = listener.terrainSender;
          return *this;
        }

        void PacketListener::onEvent(gdse::PacketReceiveEvent* event)
        {
          int clientId = event->getClientId();
          gdu::BufferReader* reader = event->getReader();
          unsigned int dataType = reader->readNextUInt();

          if(dataType == gdn::CONNECTION)
          {
            handleConnection(clientId, reader);
          }
          else if(dataType == gdn::GAME_INFO)
          {
            handleGameData(clientId, reader);
          }
          else if(dataType == gdn::TERRAIN_INFO)
          {
            handleTerrainInfo(clientId, reader);
          }
          else if(dataType == gdn::INVENTORY_INFO)
          {
            handleInventoryInfo(clientId, reader);
          }
        }

        void PacketListener::handleConnection(int clientId, gdu::BufferReader* reader)
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::CLIENT_INFO)
          {
            handleClientInfo(clientId, reader);
          }
        }

        void PacketListener::handleClientInfo(int clientId, gdu::BufferReader* reader)
        {
          gdse::ConnectionPacketReceiveEvent event(clientId);
          gde::onEvent(event);
        }

        void PacketListener::handleGameData(int clientId, gdu::BufferReader* reader)
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::REQUEST_SPAWN)
          {
            handleSpawnRequest(clientId, reader);
          }
          else if(dataFlag == gdn::MAIN_PLAYER_UPDATE)
          {
            handleClientUpdate(clientId, reader);
          }
        }

        void PacketListener::handleSpawnRequest(int clientId, gdu::BufferReader* reader)
        {
          gdse::RequestSpawnPacketReceiveEvent event(clientId);
          gde::onEvent(event);
        }

        void PacketListener::handleClientUpdate(unsigned int clientId, gdu::BufferReader* reader) const
        {
          gdm::Vector3 position = reader->readNextVector3();
          gdm::Vector3 speed = reader->readNextVector3();
          gdm::Quaternion rotation = reader->readNextQuaternion();
          gdm::Vector3 rotationSpeed = reader->readNextVector3();

          gdse::ClientUpdatePacketReceiveEvent event(clientId, &position, &speed, &rotation, &rotationSpeed);
          gde::onEvent(event);
        }

        void PacketListener::handleTerrainInfo(int clientId, gdu::BufferReader* reader)
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::DOWNLOAD_CHUNK)
          {
            handleChunkRequest(clientId, reader);
          }
          else if(dataFlag == gdn::PLACE_BLOCK)
          {
            handlePlaceBlock(clientId, reader);
          }
          else if(dataFlag == gdn::BREAK_BLOCK)
          {
            handleBreakBlock(clientId, reader);
          }
          else if(dataFlag == gdn::UPDATE_GRID_POSITION)
          {
            handleUpdateGridPosition(clientId, reader);
          }
        }

        void PacketListener::handleChunkRequest(int clientId, gdu::BufferReader* reader) const
        {
          int cx = reader->readNextInt();
          int cy = reader->readNextInt();
          int cz = reader->readNextInt();
          terrainSender->requestChunk(clientId, cx, cy, cz);
        }

        void PacketListener::handlePlaceBlock(unsigned int clientId, gdu::BufferReader* reader) const
        {
          int bx = reader->readNextInt();
          int by = reader->readNextInt();
          int bz = reader->readNextInt();
          unsigned int materialId = reader->readNextUInt();
          std::cout << "player " << clientId << " placed block " << bx << " : " << by << " : " << bz << std::endl;

          //server->sendPacketToOtherClients(clientId, gdsp::PlayerPlayActionPacket(clientId, 3));

          gdv::Block* block = terrain->getBlock(bx, by, bz);
          if(block != NULL)
          {
            block->setMaterial(materialId);
            terrain->updateChunkAtBlock(bx, by, bz);
            //server->sendPacket(gdsp::SetBlockPacket(bx, by, bz, materialId));
            serverManager->sendSetBlockPacket(bx, by, bz, materialId);
          }
        }

        void PacketListener::handleBreakBlock(unsigned int clientId, gdu::BufferReader* reader) const
        {
          int bx = reader->readNextInt();
          int by = reader->readNextInt();
          int bz = reader->readNextInt();
          std::cout << "player " << clientId << " breaked block " << bx << " : " << by << " : " << bz << std::endl;

          //server->sendPacketToOtherClients(clientId, gdsp::PlayerPlayActionPacket(clientId, 3));

          gdv::Block* block = terrain->getBlock(bx, by, bz);
          if(block != NULL)
          {
            block->setMaterial(0);
            terrain->updateChunkAtBlock(bx, by, bz);
            //server->sendPacket(gdsp::SetBlockPacket(bx, by, bz, 0));
            serverManager->sendSetBlockPacket(bx, by, bz, 0);
          }
        }

        void PacketListener::handleUpdateGridPosition(int clientId, gdu::BufferReader* reader) const
        {
          gdm::Vector3i position = reader->readNextVector3i();
          std::cout << "player " << clientId << " updated grid position to " << position.x << " : " << position.y << " : " << position.z << std::endl;
          terrainSender->setPosition(clientId, position);
        }

        void PacketListener::handleInventoryInfo(unsigned int clientId, gdu::BufferReader* reader) const
        {
          unsigned int dataFlag = reader->readNextUInt();
          if(dataFlag == gdn::SWAP_ITEMS)
          {
            handleSwapItems(clientId, reader);
          }
          else if(dataFlag == gdn::SELECTED_INVENTORY_SLOT)
          {
            handleSelectedInventorySlot(clientId, reader);
          }
        }

        void PacketListener::handleSwapItems(unsigned int clientId, gdu::BufferReader* reader) const
        {
          gdso::Player* player = players->getPlayer(clientId);
          if(player != NULL)
          {
            unsigned int slot1 = reader->readNextUInt();
            unsigned int slot2 = reader->readNextUInt();

            gdi::ItemStack itemStack = *player->getInventory()->getItemStack(slot1);
            player->getInventory()->setItemStack(slot1, *player->getInventory()->getItemStack(slot2));
            player->getInventory()->setItemStack(slot2, itemStack);

            //server->sendPacketToOtherClients(clientId, gdsp::PlayerEquipedItemPacket(clientId, 0, player->getItemStackInRightHand()));
            serverManager->sendPlayerEquipedItemPacket(clientId, 0, player->getItemStackInRightHand());
          }
        }

        void PacketListener::handleSelectedInventorySlot(unsigned int clientId, gdu::BufferReader* reader) const
        {
          unsigned int slot = reader->readNextUInt();
          gdso::Player* player = players->getPlayer(clientId);
          if(player != NULL)
          {
            player->setSelectedSlot(slot);

            //server->sendPacketToOtherClients(clientId, gdsp::PlayerEquipedItemPacket(clientId, 0, player->getItemStackInRightHand()));
            serverManager->sendPlayerEquipedItemPacket(clientId, 0, player->getItemStackInRightHand());
          }
        }
      }
    }
  }
}
