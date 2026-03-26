#ifndef GD_UTILS_MEMORYARRAY_H
#define GD_UTILS_MEMORYARRAY_H

#include "ArrayList.h"
#include "StorageArray.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename Type> class MemoryArray
      {
      private:
        unsigned int freeIndex;
        StorageArray<Type> storage;
        ArrayList<unsigned int> freeIndices;

      public:
        MemoryArray()
        {
          freeIndex = 0;
        }

        MemoryArray(const MemoryArray<Type>& array)
        {
          freeIndex = array.freeIndex;
          storage = array.storage;
          freeIndices = array.freeIndices;
        }

        MemoryArray<Type>& operator=(const MemoryArray<Type>& array)
        {
          freeIndex = array.freeIndex;
          storage = array.storage;
          freeIndices = array.freeIndices;
          return *this;
        }

        void setSize(unsigned int size)
        {
          storage.setSize(size);
        }

        unsigned int genSlot()
        {
          if(freeIndices.size() > 0)
          {
            unsigned int index = freeIndices[freeIndices.size()-1];
            freeIndices.remove(freeIndices.size()-1);
            storage.use(index);
            return index;
          }
          else
          {
            unsigned int index = freeIndex;
            freeIndex++;
            storage.use(index);
            return index;
          }
        }

        unsigned int add(const Type& value)
        {
          if(freeIndices.size() > 0)
          {
            unsigned int index = freeIndices[freeIndices.size()-1];
            freeIndices.remove(freeIndices.size()-1);
            storage.use(index);
            storage[index] = value;
            return index;
          }
          else
          {
            unsigned int index = freeIndex;
            freeIndex++;
            storage.use(index);
            storage[index] = value;
            return index;
          }
        }

        bool isUsed(unsigned int index) const
        {
          return storage.isUsed(index);
        }

        void use(unsigned int index)
        {
          storage.use(index);
        }

        void free(unsigned int index)
        {
          freeIndices.add(index);
          storage.free(index);
        }

        Type& operator[](unsigned int index) const
        {
          return storage[index];
        }
      };
    }
  }
}

#endif
