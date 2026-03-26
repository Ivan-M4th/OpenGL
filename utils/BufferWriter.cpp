#include "BufferWriter.h"

#include <cstring>
#include <cassert>
#include <cstdio>
#include <iostream>

#include "../voxel/VoxelData.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      BufferWriter::BufferWriter(Buffer* buffer)
      {
        this->buffer = buffer;
      }

      BufferWriter::BufferWriter(const BufferWriter& writer)
      {
        buffer = writer.buffer;
      }

      BufferWriter& BufferWriter::operator=(const BufferWriter& writer)
      {
        buffer = writer.buffer;
        return *this;
      }

      void BufferWriter::addData(const char* chars, unsigned int charsSize) const
      {
        assert(buffer->size + charsSize < buffer->getMemorySize() && "Error attempt to write out of buffer bounds!");
        for(unsigned int i=0;i<charsSize;i++)
        {
          *(buffer->getData() + buffer->size + i) = *(chars + i);
        }
        buffer->size+=charsSize;
      }

      void BufferWriter::addData(const char* chars) const
      {
        addData(chars, strlen(chars));
      }

      void BufferWriter::addChar(char c) const
      {
        assert(buffer->size < buffer->getMemorySize() && "Error attempt to write out of buffer bounds!");
        *(buffer->getData() + buffer->size) = c;
        buffer->size++;
      }

      void BufferWriter::addSpace() const
      {
        addChar(' ');
      }

      void BufferWriter::addEndOfLine() const
      {
        addChar('\n');
      }

      void BufferWriter::addData(unsigned int x) const
      {
        int intSize = sprintf(buffer->getData() + buffer->size, "%u", x);
        assert(intSize >= 0 && "Writing float to buffer failed!");
        buffer->size+=intSize;
      }

      void BufferWriter::addData(int x) const
      {
        int intSize = sprintf(buffer->getData() + buffer->size, "%d", x);
        assert(intSize >= 0 && "Writing float to buffer failed!");
        buffer->size+=intSize;
      }

      void BufferWriter::addData(float x) const
      {
        int floatSize = sprintf(buffer->getData() + buffer->size, "%f", x);
        assert(floatSize >= 0 && "Writing float to buffer failed!");
        buffer->size+=floatSize;
      }

      void BufferWriter::addData(const gdm::Vector3i& v) const
      {
        addData(v.x);
        addSpace();
        addData(v.y);
        addSpace();
        addData(v.z);
      }

      void BufferWriter::addData(const gdm::Vector3& v) const
      {
        addData(v.getX());
        addSpace();
        addData(v.getY());
        addSpace();
        addData(v.getZ());
      }

      void BufferWriter::addData(const gdm::Quaternion& q) const
      {
        addData(q.a);
        addSpace();
        addData(q.b);
        addSpace();
        addData(q.c);
        addSpace();
        addData(q.d);
      }

      void BufferWriter::addData(const gdv::Block* block) const
      {
        assert(block != NULL && "ERROR: adding null block to packet!");
        addData(block->getMaterialId());
      }

      void BufferWriter::addData(const gdv::Chunk* chunk) const
      {
        for(unsigned int x=0;x<gdv::CHUNK_SIZE;x++)
        {
          for(unsigned int y=0;y<gdv::CHUNK_SIZE;y++)
          {
            for(unsigned int z=0;z<gdv::CHUNK_SIZE;z++)
            {
              addData(chunk->getBlock(x, y, z));
              if(x != gdv::CHUNK_SIZE-1 || y != gdv::CHUNK_SIZE-1 || z != gdv::CHUNK_SIZE-1)
              {
                addSpace();
              }
            }
          }
        }
      }

      void BufferWriter::addData(const gdi::ItemStack* itemStack) const
      {
        addData(itemStack->getItemId());
        addSpace();
        addData(itemStack->amount);
      }
    }
  }
}
