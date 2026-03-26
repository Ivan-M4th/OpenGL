#ifndef GD_CLIENT_LISTENERS_CHUNKGENERATEDLISTENER_H
#define GD_CLIENT_LISTENERS_CHUNKGENERATEDLISTENER_H

#include "../../gddef.h"

#include "../../events/Listener.h"

#include "../events/ChunkGeneratedEvent.h"

#include "../../voxel/ChunkGrid.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        class ChunkGeneratedListener : public gde::Listener<gdce::ChunkGeneratedEvent>
        {
        private:
          gdv::ChunkGrid* chunkGrid;

        public:
          ChunkGeneratedListener(gdv::ChunkGrid*);
          ChunkGeneratedListener(const ChunkGeneratedListener&);
          ChunkGeneratedListener& operator=(const ChunkGeneratedListener&);

          void onEvent(gdce::ChunkGeneratedEvent*) override;
        };
      }
    }
  }
}

#endif
