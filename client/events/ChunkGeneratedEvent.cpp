#include "ChunkGeneratedEvent.h"

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace events
      {
        unsigned int ChunkGeneratedEvent::getStaticType()
        {
          return gde::CHUNK_GENERATED_EVENT;
        }

        ChunkGeneratedEvent::ChunkGeneratedEvent(int cx, int cy, int cz, const Pointer<gdv::Chunk>& chunk)
        {
          this->cx = cx;
          this->cy = cy;
          this->cz = cz;
          this->chunk = chunk;
        }

        ChunkGeneratedEvent::ChunkGeneratedEvent(const ChunkGeneratedEvent& event)
        {
          cx = event.cx;
          cy = event.cy;
          cz = event.cz;
          chunk = event.chunk;
        }

        ChunkGeneratedEvent& ChunkGeneratedEvent::operator=(const ChunkGeneratedEvent& event)
        {
          cx = event.cx;
          cy = event.cy;
          cz = event.cz;
          chunk = event.chunk;
          return *this;
        }

        int ChunkGeneratedEvent::getCX() const
        {
          return cx;
        }

        int ChunkGeneratedEvent::getCY() const
        {
          return cy;
        }

        int ChunkGeneratedEvent::getCZ() const
        {
          return cz;
        }

        const Pointer<gdv::Chunk>& ChunkGeneratedEvent::getChunkPointer() const
        {
          return chunk;
        }

        gdv::Chunk* ChunkGeneratedEvent::getChunk() const
        {
          return chunk.value();
        }

        unsigned int ChunkGeneratedEvent::getType() const
        {
          return getStaticType();
        }
      }
    }
  }
}
