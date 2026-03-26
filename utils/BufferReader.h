#ifndef GD_UTILS_BUFFERREADER_H
#define GD_UTILS_BUFFERREADER_H

#include "../gddef.h"

#include "Buffer.h"

#include "Pointer.h"

#include "../math/Vector3i.h"
#include "../math/Vector3.h"
#include "../math/Quaternion.h"

#include "../voxel/Chunk.h"

#include "../items/Item.h"
#include "../items/ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class BufferReader
      {
      private:
        unsigned int index;
        Buffer* buffer;

      public:
        BufferReader(Buffer*);
        BufferReader(const BufferReader&);
        BufferReader& operator=(const BufferReader&);

        char getChar() const;
        bool isValid() const;
        void skipSpaces();

        void readNext(char*, unsigned int);
        int readNextInt();
        unsigned int readNextUInt();
        float readNextFloat();

        gdm::Vector3i readNextVector3i();
        gdm::Vector3 readNextVector3();
        gdm::Quaternion readNextQuaternion();
        Pointer<gdv::Chunk> readNextChunk();
        gdi::ItemStack readNextItemStack();

        void moveToStart(unsigned int);
        void readPacket(Buffer* packetBuffer);
      };
    }
  }
}

#endif
