#include "BufferReader.h"

#include <cassert>
#include <cstdlib>
#include <iostream>

#include "../voxel/VoxelData.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      BufferReader::BufferReader(Buffer* buffer)
      {
        index = 0;
        this->buffer = buffer;
      }

      BufferReader::BufferReader(const BufferReader& reader)
      {
        index = reader.index;
        buffer = reader.buffer;
      }

      BufferReader& BufferReader::operator=(const BufferReader& reader)
      {
        index = reader.index;
        buffer = reader.buffer;
        return *this;
      }

      char BufferReader::getChar() const
      {
        assert(isValid());
        return *(buffer->getData() + index);
      }

      bool BufferReader::isValid() const
      {
        return index < buffer->size;
      }

      void BufferReader::skipSpaces()
      {
        while(isValid() && getChar() == ' ')
        {
          index++;
        }
      }

      void BufferReader::readNext(char* data, unsigned int maxSize)
      {
        unsigned int i = 0;
        while(isValid() && i < maxSize - 1 && getChar() != ' ')
        {
          *(data + i) = getChar();
          i++;
          index++;
        }
        *(data + i) = '\0';
        skipSpaces();
      }

      int BufferReader::readNextInt()
      {
        char data[60];
        readNext(data, 60);
        return atoi(data);
      }

      unsigned int BufferReader::readNextUInt()
      {
        return readNextInt();
      }

      float BufferReader::readNextFloat()
      {
        char data[60];
        readNext(data, 60);
        return atof(data);
      }

      gdm::Vector3i BufferReader::readNextVector3i()
      {
        int x = readNextInt();
        int y = readNextInt();
        int z = readNextInt();
        return gdm::Vector3i(x, y, z);
      }

      gdm::Vector3 BufferReader::readNextVector3()
      {
        float x = readNextFloat();
        float y = readNextFloat();
        float z = readNextFloat();
        return gdm::Vector3(x, y, z);
      }

      gdm::Quaternion BufferReader::readNextQuaternion()
      {
        float a = readNextFloat();
        float b = readNextFloat();
        float c = readNextFloat();
        float d = readNextFloat();
        return gdm::Quaternion(a, b, c, d);
      }

      Pointer<gdv::Chunk> BufferReader::readNextChunk()
      {
        Pointer<gdv::Chunk> chunkPtr(new gdv::Chunk(), false);
        gdv::Chunk* chunk = chunkPtr.value();

        for(unsigned int x=0;x<gdv::CHUNK_SIZE;x++)
        {
          for(unsigned int y=0;y<gdv::CHUNK_SIZE;y++)
          {
            for(unsigned int z=0;z<gdv::CHUNK_SIZE;z++)
            {
              int materialId = readNextInt();
              chunk->getBlock(x, y, z)->setMaterial(materialId);
            }
          }
        }
        return chunkPtr;
      }

      gdi::ItemStack BufferReader::readNextItemStack()
      {
        int itemId = readNextInt();
        int amount = readNextInt();
        return gdi::ItemStack(Pointer<gdi::Item>(new gdi::Item(itemId), false), amount);
      }

      void BufferReader::moveToStart(unsigned int index)
      {
        if(index >= buffer->size)
        {
          buffer->clear();
          return;
        }
        for(unsigned int i=0;i<buffer->size;i++)
        {
          *(buffer->getData() + i) = *(buffer->getData() + index + i);
        }
        buffer->size = buffer->size - index;
      }

      void BufferReader::readPacket(Buffer* packetBuffer)
      {
        unsigned int i = 0;
        while(i < buffer->size)
        {
          if(*(buffer->getData() + i) == '\n')
          {
            packetBuffer->size+=i;
            moveToStart(i+1);
            return;
          }
          assert(packetBuffer->size + i < packetBuffer->getMemorySize());
          *(packetBuffer->getData() + packetBuffer->size + i) = *(buffer->getData() + i);
          i++;
        }
      }
    }
  }
}
