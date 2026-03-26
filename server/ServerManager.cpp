#include "ServerManager.h"

#include "objects/Boar.h"

#include "../networking/Packet.h"

#include "../utils/BufferWriter.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      ServerManager::ServerManager(gdn::Server* server, gdu::Buffer* buffer)
      {
        this->server = server;
        this->buffer = buffer;
      }

      bool ServerManager::isOnline(int clientId) const
      {
        return server->isOnline(clientId);
      }

      void ServerManager::sendSetBlockPacket(int bx, int by, int bz, int materialId)
      {
        buffer->clear();
        gdu::BufferWriter writer(buffer);

        writer.addData(gdn::TERRAIN_INFO);
        writer.addSpace();
        writer.addData(gdn::SET_BLOCK);
        writer.addSpace();
        writer.addData(bx);
        writer.addSpace();
        writer.addData(by);
        writer.addSpace();
        writer.addData(bz);
        writer.addSpace();
        writer.addData(materialId);

        writer.addEndOfLine();

        server->sendBuffer();
      }

      void ServerManager::sendPlayerEquipedItemPacket(int clientId, int location, const gdi::ItemStack* itemStack)
      {
        buffer->clear();
        gdu::BufferWriter writer(buffer);

        writer.addData(gdn::INVENTORY_INFO);
        writer.addSpace();
        writer.addData(gdn::PLAYER_EQUIPED_ITEM);
        writer.addSpace();
        writer.addData(clientId);
        writer.addSpace();
        writer.addData(location);
        writer.addSpace();
        writer.addData(itemStack);

        writer.addEndOfLine();

        server->sendBufferToOthers(clientId);
      }

      void ServerManager::sendChunkPacket(int clientId, int cx, int cy, int cz, const gdv::Chunk* chunk)
      {
        buffer->clear();
        gdu::BufferWriter writer(buffer);

        writer.addData(gdn::TERRAIN_INFO);
        writer.addSpace();
        writer.addData(gdn::SEND_CHUNK);
        writer.addSpace();
        writer.addData(cx);
        writer.addSpace();
        writer.addData(cy);
        writer.addSpace();
        writer.addData(cz);
        writer.addSpace();
        writer.addData(chunk);

        writer.addEndOfLine();

        server->sendBufferTo(clientId);
      }

      void ServerManager::sendChunkTreesPacket(int clientId, GameDataManager* gameDataManager, int cx, int cy, int cz, const ArrayList<int>* trees)
      {
        buffer->clear();
        gdu::BufferWriter writer(buffer);

        writer.addData(gdn::TERRAIN_INFO);
        writer.addSpace();
        writer.addData(gdn::SEND_CHUNK_TREES);
        writer.addSpace();
        writer.addData(cx);
        writer.addSpace();
        writer.addData(cy);
        writer.addSpace();
        writer.addData(cz);
        writer.addSpace();
        writer.addData(trees->size());
        for(int i=0;i<trees->size();i++)
        {
          int objectId = (*trees)[i];
          gdso::Tree* tree = gameDataManager->getTree(objectId);

          writer.addSpace();
          writer.addData(objectId);

          writer.addSpace();
          writer.addData(tree->transformation.position);

          writer.addSpace();
          writer.addData(tree->transformation.rotation);
        }

        writer.addEndOfLine();

        server->sendBufferTo(clientId);
      }

      void ServerManager::sendChunkBoarsPacket(int clientId, GameDataManager* gameDataManager, int cx, int cy, int cz, const ArrayList<int>* boars)
      {
        buffer->clear();
        gdu::BufferWriter writer(buffer);

        writer.addData(gdn::TERRAIN_INFO);
        writer.addSpace();
        writer.addData(gdn::SEND_CHUNK_BOARS);
        writer.addSpace();
        writer.addData(cx);
        writer.addSpace();
        writer.addData(cy);
        writer.addSpace();
        writer.addData(cz);
        writer.addSpace();
        writer.addData(boars->size());
        for(int i=0;i<boars->size();i++)
        {
          int objectId = (*boars)[i];
          gdso::Boar* boar = gameDataManager->getBoar(objectId);

          writer.addSpace();
          writer.addData(objectId);

          writer.addSpace();
          writer.addData(boar->transformation.position);

          writer.addSpace();
          writer.addData(boar->transformation.rotation);
        }

        writer.addEndOfLine();

        server->sendBufferTo(clientId);
      }

      void ServerManager::sendUpdateBoarPacket(GameDataManager* gameDataManager, int objectId)
      {
        gdso::Boar* boar = gameDataManager->getBoar(objectId);

        buffer->clear();
        gdu::BufferWriter writer(buffer);

        writer.addData(gdn::GAME_INFO);
        writer.addSpace();
        writer.addData(gdn::UPDATE_BOAR);
        writer.addSpace();
        writer.addData(objectId);
        writer.addSpace();
        writer.addData(boar->transformation.position);
        writer.addSpace();
        writer.addData(boar->speed);
        writer.addSpace();
        writer.addData(boar->transformation.rotation);
        writer.addSpace();
        writer.addData(boar->rotationSpeed);

        writer.addEndOfLine();

        server->sendBuffer();
      }
    }
  }
}
