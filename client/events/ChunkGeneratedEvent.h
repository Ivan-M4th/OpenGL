#ifndef GD_CLIENT_EVENTS_CHUNKGENERATEDEVENT_H
#define GD_CLIENT_EVENTS_CHUNKGENERATEDEVENT_H

#include "../../gddef.h"

#include "../../events/Event.h"

#include "../../utils/Pointer.h"

#include "../../voxel/Chunk.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        class ChunkGeneratedEvent : public gde::Event
        {
        private:
          int cx;
          int cy;
          int cz;
          Pointer<gdv::Chunk> chunk;

        public:
          static unsigned int getStaticType();

          ChunkGeneratedEvent(int, int, int, const Pointer<gdv::Chunk>&);
          ChunkGeneratedEvent(const ChunkGeneratedEvent&);
          ChunkGeneratedEvent& operator=(const ChunkGeneratedEvent&);

          int getCX() const;
          int getCY() const;
          int getCZ() const;
          const Pointer<gdv::Chunk>& getChunkPointer() const;
          gdv::Chunk* getChunk() const;

          unsigned int getType() const override;
        };
      }
    }
  }
}

#endif
