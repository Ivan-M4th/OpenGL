#ifndef GD_UTILS_STORAGEARRAY_H
#define GD_UTILS_STORAGEARRAY_H

#include "ListedArrays.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename Type> struct StorageArrayNode
      {
        bool used = false;
        Type value;
      };

      template<typename Type> class StorageArray
      {
      private:
        ListedArrays<StorageArrayNode<Type>> list;

      public:
        StorageArray()
        {

        }

        StorageArray(const StorageArray<Type>& array)
        {
          list = array.list;
        }

        StorageArray<Type>& operator=(const StorageArray<Type>& array)
        {
          list = array.list;
          return *this;
        }

        void setSize(unsigned int size)
        {
          list.setSize(size);
        }

        void use(unsigned int index)
        {
          if(index >= list.size())
          {
            list.setSize(index + 1);
          }
          assert(!list[index].used);
          list[index].used = true;
        }

        bool isUsed(unsigned int index) const
        {
          if(index >= list.size())
          {
            return false;
          }
          return list[index].used;
        }

        void free(unsigned int index)
        {
          assert(index < list.size());
          list[index].used = false;
        }

        Type& operator[](unsigned int index) const
        {
          assert(index < list.size());
          assert(list[index].used);
          return list[index].value;
        }
      };
    }
  }
}

#endif
