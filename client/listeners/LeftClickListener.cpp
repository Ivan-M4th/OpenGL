#include "LeftClickListener.h"

#include <iostream>

#include "../../items/ItemStack.h"
#include "../../items/ItemType.h"
#include "../../items/Items.h"

#include "../../voxel/Block.h"

#include "../../math/Vector3i.h"

#include "../packets/PlaceBlockPacket.h"
#include "../packets/BreakBlockPacket.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        LeftClickListener::LeftClickListener(gdn::Client* client, Players* players, gdg::Camera* camera, gdv::ChunkGrid* chunkGrid)
        {
          this->client = client;
          this->players = players;
          this->camera = camera;
          this->chunkGrid = chunkGrid;
        }

        void LeftClickListener::onEvent(gdet::LeftClickEvent* event)
        {
          std::cout << "LEFT CLICK" << std::endl;
          gdco::MainPlayer* player = players->getMainPlayer();

          if(player != NULL)
          {
            gdi::ItemStack* itemStack = player->getItemInRightHand();
            player->useItem();
            if(!itemStack->isEmpty())
            {

              gdi::ItemType* itemType = gdi::getItemType(itemStack->getItemId());
              std::cout << "item id: " << itemStack->getItemId() << std::endl;

              std::cout << "item type: " << itemType->getTypeId() << std::endl;
              if((*itemType).getTypeId() == gdi::BLOCK_TYPE)
              {
                placeBlock(player, (gdit::BlockItemType*)itemType);
              }
              else
              {
                breakBlock(player);
              }
            }
          }
        }

        void LeftClickListener::placeBlock(gdco::MainPlayer* player, gdit::BlockItemType* itemType)
        {
          gdm::Vector3 direction = camera->getDirection();
          gdm::Vector3 position = camera->getPosition();

          gdv::BlockInfo blockInfo;

          //std::cout << "placing block..." << std::endl;
          chunkGrid->raycastToBlockBefore(position, direction, &blockInfo);
          if(blockInfo.block != NULL)
          {
            std::cout << "placing block at: " << blockInfo.position.x << " : " << blockInfo.position.x << " : " << blockInfo.position.x << std::endl;
            client->sendPacket(gdcp::PlaceBlockPacket(blockInfo.position.x, blockInfo.position.y, blockInfo.position.z, itemType->getMaterialId()));
          }
        }

        void LeftClickListener::breakBlock(gdco::MainPlayer* player)
        {
          gdm::Vector3 direction = camera->getDirection();
          gdm::Vector3 position = camera->getPosition();

          gdv::BlockInfo blockInfo;

          chunkGrid->raycastToBlock(position, direction, &blockInfo);
          if(blockInfo.block != NULL)
          {
            std::cout << "breaking block at: " << blockInfo.position.x << " : " << blockInfo.position.x << " : " << blockInfo.position.x << std::endl;
            client->sendPacket(gdcp::BreakBlockPacket(blockInfo.position.x, blockInfo.position.y, blockInfo.position.z));
          }

        }
      }
    }
  }
}
