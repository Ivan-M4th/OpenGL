#include "ChunkGeneratedListener.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace client
    {
      namespace listeners
      {
        ChunkGeneratedListener::ChunkGeneratedListener(gdv::ChunkGrid* chunkGrid)
        {
          this->chunkGrid = chunkGrid;
        }

        ChunkGeneratedListener::ChunkGeneratedListener(const ChunkGeneratedListener& listener)
        {
          chunkGrid = listener.chunkGrid;
        }

        ChunkGeneratedListener& ChunkGeneratedListener::operator=(const ChunkGeneratedListener& listener)
        {
          chunkGrid = listener.chunkGrid;
          return *this;
        }

        void ChunkGeneratedListener::onEvent(gdce::ChunkGeneratedEvent* event)
        {
          chunkGrid->loadChunk(event->getCX(), event->getCY(), event->getCZ(), event->getChunk());
          //std::cout << "CHUNK GENERATED!" << std::endl;
        }
      }
    }
  }
}
