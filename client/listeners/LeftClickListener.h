#ifndef GD_CLIENT_LISTENERS_LEFTCLICKLISTENER_H
#define GD_CLIENT_LISTENERS_LEFTCLICKLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"
#include "../../events/types/LeftClickEvent.h"

#include "../Players.h"

#include "../../graphics/Camera.h"

#include "../../voxel/ChunkGrid.h"

#include "../../networking/Client.h"

#include "../objects/MainPlayer.h"
#include "../../items/types/BlockItemType.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class LeftClickListener : public gde::Listener<gdet::LeftClickEvent>
        {
        private:
          gdn::Client* client;
          Players* players;
          gdg::Camera* camera;
          gdv::ChunkGrid* chunkGrid;

          void placeBlock(gdco::MainPlayer* player, gdit::BlockItemType* itemType);
          void breakBlock(gdco::MainPlayer* player);
        public:
          LeftClickListener(gdn::Client*, Players*, gdg::Camera*, gdv::ChunkGrid*);

          void onEvent(gdet::LeftClickEvent*) override;
        };
      }
    }
  }
}

#endif
