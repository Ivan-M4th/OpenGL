#ifndef GD_UTILS_BUFFERWRITER_H
#define GD_UTILS_BUFFERWRITER_H

#include "../gddef.h"

#include "Buffer.h"

#include "../math/Vector3i.h"
#include "../math/Vector3.h"
#include "../math/Quaternion.h"

#include "../voxel/Block.h"
#include "../voxel/Chunk.h"

#include "../items/ItemStack.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class BufferWriter
      {
      private:
        Buffer* buffer;

      public:
        BufferWriter(Buffer*);
        BufferWriter(const BufferWriter&);
        BufferWriter& operator=(const BufferWriter&);

        void addData(const char*, unsigned int) const;
        void addData(const char*) const;

        void addChar(char) const;
        void addSpace() const;
        void addEndOfLine() const;
        void addData(unsigned int) const;
        void addData(int) const;
        void addData(float) const;

        void addData(const gdm::Vector3i&) const;
        void addData(const gdm::Vector3&) const;
        void addData(const gdm::Quaternion&) const;
        void addData(const gdv::Block*) const;
        void addData(const gdv::Chunk*) const;
        void addData(const gdi::ItemStack*) const;
      };
    }
  }
}

#endif
