#include "Buffer.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      Buffer::Buffer(unsigned int memorySize)
      {
        this->memorySize = memorySize;
        size = 0;
        data = new char[memorySize];
      }

      Buffer::Buffer(const Buffer& buffer)
      {
        memorySize = buffer.memorySize;
        size = buffer.size;
        data = new char[memorySize];
        for(unsigned int i=0;i<size;i++)
        {
          *(data + i) = *(buffer.data + i);
        }
      }

      Buffer& Buffer::operator=(const Buffer& buffer)
      {
        deleteData();
        memorySize = buffer.memorySize;
        size = buffer.size;
        data = new char[memorySize];
        for(unsigned int i=0;i<size;i++)
        {
          *(data + i) = *(buffer.data + i);
        }
        return *this;
      }

      Buffer::~Buffer()
      {
        deleteData();
      }

      void Buffer::deleteData()
      {
        delete[] data;
      }

      unsigned int Buffer::getMemorySize() const
      {
        return memorySize;
      }

      unsigned int Buffer::getFreeSpace() const
      {
        return memorySize - size;
      }

      char* Buffer::getData() const
      {
        return data;
      }

      void Buffer::clear()
      {
        size = 0;
      }
      void Buffer::print()
      {
        char* toPrint = new char[size + 1];
        for(unsigned int i=0;i<size;i++)
        {
          *(toPrint + i) = *(data + i);
        }
        *(toPrint + size) = '\0';
        std::cout << toPrint << std::endl;
        delete[] toPrint;
      }
    }
  }
}
