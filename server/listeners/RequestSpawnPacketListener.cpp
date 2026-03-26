#include "RequestSpawnPacketListener.h"

#include "../../Debug.h"

#include "../../math/Vector3.h"

#include "../../utils/Pointer.h"

#include "../objects/Player.h"

#include "../packets/MainPlayerSpawnPacket.h"
#include "../packets/PlayerSpawnPacket.h"
#include "../packets/SetItemStackPacket.h"

#include "../../voxel/Materials.h"

#include "../../items/ItemIds.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace listeners
      {
        RequestSpawnPacketListener::RequestSpawnPacketListener(gdn::Server* server, Players* players)
        {
          this->server = server;
          this->players = players;
        }

        RequestSpawnPacketListener::RequestSpawnPacketListener(const RequestSpawnPacketListener& listener)
        {
          server = listener.server;
          players = listener.players;
        }

        RequestSpawnPacketListener& RequestSpawnPacketListener::operator=(const RequestSpawnPacketListener& listener)
        {
          server = listener.server;
          players = listener.players;
          return *this;
        }

        void RequestSpawnPacketListener::setItemStack(unsigned int clientId, unsigned int slot, const gdi::ItemStack& itemStack)
        {
          gdso::Player* player = players->getPlayer(clientId);
          if(player != NULL)
          {
            player->getInventory()->setItemStack(slot, itemStack);
            server->sendPacketTo(clientId, gdsp::SetItemStackPacket(slot, &itemStack));
          }
        }

        void RequestSpawnPacketListener::onEvent(gdse::RequestSpawnPacketReceiveEvent* event)
        {
          DEBUG << "client: " << event->getClientId() << " is requesting spawn!";
          DEBUG.endl();

          gdm::Vector3 spawn(164, 40, 164);
          Pointer<gdso::Player> player(new gdso::Player(), false);

          player.value()->transformation.position = spawn;
          player.value()->calculateInformation();

          players->setPlayer(event->getClientId(), player);
          server->sendPacketTo(event->getClientId(), gdsp::MainPlayerSpawnPacket(player.value()));
          server->sendPacketToOtherClients(event->getClientId(), gdsp::PlayerSpawnPacket(event->getClientId(), player.value()));

          setItemStack(event->getClientId(), 1, gdi::ItemStack(gdv::GRASS, 30));
          setItemStack(event->getClientId(), 2, gdi::ItemStack(gdv::DIRT, 30));
          setItemStack(event->getClientId(), 3, gdi::ItemStack(gdv::STONE, 30));
          setItemStack(event->getClientId(), 4, gdi::ItemStack(gdv::WOOD_PLANKS, 30));
          setItemStack(event->getClientId(), 5, gdi::ItemStack(gdv::STONE_BRICKS, 30));
          setItemStack(event->getClientId(), 6, gdi::ItemStack(gdi::STONE_PICKAXE, 30));
          setItemStack(event->getClientId(), 7, gdi::ItemStack(gdv::RED_BRICKS, 30));
          setItemStack(event->getClientId(), 8, gdi::ItemStack(gdv::CONCRETE, 30));

          setItemStack(event->getClientId(), 9, gdi::ItemStack(gdv::CLAY, 30));
          setItemStack(event->getClientId(), 10, gdi::ItemStack(gdv::ANTHRACITE, 30));
          setItemStack(event->getClientId(), 11, gdi::ItemStack(gdv::BITUMINOUS_COAL, 30));
          setItemStack(event->getClientId(), 12, gdi::ItemStack(gdv::LIGNITE, 30));
          setItemStack(event->getClientId(), 13, gdi::ItemStack(gdv::PEAT, 30));
          setItemStack(event->getClientId(), 14, gdi::ItemStack(gdv::ANHYDRITE, 30));
          setItemStack(event->getClientId(), 15, gdi::ItemStack(gdv::GYPSUM, 30));
          setItemStack(event->getClientId(), 16, gdi::ItemStack(gdv::HALITE, 30));
          setItemStack(event->getClientId(), 17, gdi::ItemStack(gdv::POTASH, 30));
          setItemStack(event->getClientId(), 18, gdi::ItemStack(gdv::LIMESTONE, 30));
          setItemStack(event->getClientId(), 19, gdi::ItemStack(gdv::CHALK, 30));
          setItemStack(event->getClientId(), 20, gdi::ItemStack(gdv::DOLOMITE, 30));
          setItemStack(event->getClientId(), 21, gdi::ItemStack(gdv::MARL, 30));
          setItemStack(event->getClientId(), 22, gdi::ItemStack(gdv::TUFA, 30));
          setItemStack(event->getClientId(), 23, gdi::ItemStack(gdv::PHOSPHORITE, 30));
          setItemStack(event->getClientId(), 24, gdi::ItemStack(gdv::DIATOMITE, 30));
          setItemStack(event->getClientId(), 25, gdi::ItemStack(gdv::SANDSTONE, 30));
          setItemStack(event->getClientId(), 26, gdi::ItemStack(gdv::RADIOLARITE, 30));
          setItemStack(event->getClientId(), 27, gdi::ItemStack(gdv::FLINT, 30));
          setItemStack(event->getClientId(), 28, gdi::ItemStack(gdv::SPICULITE, 30));
        }
      }
    }
  }
}
