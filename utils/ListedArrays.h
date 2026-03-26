#ifndef GD_UTILS_LISTEDARRAYS_H
#define GD_UTILS_LISTEDARRAYS_H

#include "ArrayList.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename Type> class ListedArrays
      {
      private:
        int arraySize;

        ArrayList<Type*> arrays;
        int amount;

        void deleteData()
        {
          for(int i=0;i<arrays.size();i++)
          {
            delete [] arrays[i];
          }
        }

        void getIndices(int index, int* i, int* j) const
        {
          *i = (int)(index/arraySize);
          *j = index - (*i)*arraySize;
        }

        bool isValid(int index) const
        {
          return 0 <= index && index < amount;
        }

      public:
        ListedArrays()
        {
          arraySize = 500;
          arrays.add(new Type[arraySize]);
          amount = 0;
        }

        ListedArrays(const ListedArrays<Type>& list)
        {
          arraySize = list.arraySize;
          amount = list.amount;

          for(int i=0;i<list.arrays.size();i++)
          {
            arrays.add(new Type[arraySize]);
            for(int j=0;j<arraySize;j++)
            {
              *(arrays[i] + j) = *(list.arrays[i] + j);
            }
          }
        }

        ListedArrays<Type>& operator=(const ListedArrays<Type>& list)
        {
          deleteData();

          arrays.clear();

          arraySize = list.arraySize;
          amount = list.amount;

          for(int i=0;i<list.arrays.size();i++)
          {
            arrays.add(new Type[arraySize]);
            for(int j=0;j<arraySize;j++)
            {
              *(arrays[i] + j) = *(list.arrays[i] + j);
            }
          }

          return *this;
        }

        ~ListedArrays()
        {
          deleteData();
        }

        int size() const
        {
          return amount;
        }

        void setSize(int size)
        {
          if(size > amount)
          {
            int k = (int)((size  + 1)/arraySize);
            while(k >= arrays.size())
            {
              arrays.add(new Type[arraySize]);
            }
          }

          amount = size;
        }

        void add(const Type& element)
        {
          int i;
          int j;
          getIndices(amount, &i, &j);

          setSize(amount + 1);

          *(arrays[i] + j) = element;
        }

        Type& operator[](int index) const
        {
          assert(isValid(index));
          int i;
          int j;
          getIndices(index, &i, &j);
          return *(arrays[i] + j);
        }
      };

      template<typename Type> std::ostream& operator<<(std::ostream& os, const ListedArrays<Type>& list)
      {
        for(int i=0;i<list.size();i++)
        {
          os << list[i];
          if(i < list.size() - 1)
          {
            os << "\n";
          }
        }
        return os;
      }
    }
  }
}

#endif
