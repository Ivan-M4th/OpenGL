#ifndef GD_UTILS_BUFFER_H
#define GD_UTILS_BUFFER_H

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class Buffer
      {
      private:
        unsigned int memorySize;
        char* data;

        void deleteData();
      public:
        unsigned int size;

        Buffer(unsigned int);
        Buffer(const Buffer&);
        Buffer& operator=(const Buffer&);
        ~Buffer();

        unsigned int getMemorySize() const;
        unsigned int getFreeSpace() const;
        char* getData() const;

        void clear();

        void print();
      };
    }
  }
}

#endif
