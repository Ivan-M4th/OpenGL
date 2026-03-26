#ifndef GD_UTILS_ARRAYLIST_H
#define GD_UTILS_ARRAYLIST_H

#include <cassert>
#include <iostream>

#include "Array.h"

namespace gt
{
  namespace doubovik
  {
    template<typename Type> class ArrayList
    {
    private:
      Type* array;
      unsigned int capacity;
      unsigned int amount;

      void deleteData()
      {
        delete[] array;
      }

      void setCapacity(unsigned int capacity)
      {
        this->capacity = capacity;
        if(amount > capacity)
        {
          amount = capacity;
        }

        Type* newArray = new Type[capacity];
        for(unsigned int i=0;i<amount;i++)
        {
          *(newArray + i) = *(array + i);
        }
        delete[] array;
        array = newArray;
      }

      void expand(unsigned int add)
      {
        if(add > 0)
        {
          capacity+=add;
          Type* newArray = new Type[capacity];
          for(unsigned int i=0;i<amount;i++)
          {
            *(newArray + i) = *(array + i);
          }
          delete[] array;
          array = newArray;
        }
      }

    public:
      ArrayList()
      {
        capacity = 4;//16;
        amount = 0;
        array = new Type[capacity];
      }

      ArrayList(unsigned int capacity)
      {
        assert(capacity > 0);
        this->capacity = capacity;
        amount = 0;
        array = new Type[capacity];
      }

      ArrayList(const ArrayList<Type>& arrayList)
      {
        capacity = arrayList.capacity;
        amount = arrayList.amount;
        array = new Type[capacity];
        for(unsigned int i=0;i<amount;i++)
        {
          *(array + i) = *(arrayList.array + i);
        }
      }

      ArrayList<Type>& operator=(const ArrayList<Type>& arrayList)
      {
        deleteData();
        capacity = arrayList.capacity;
        amount = arrayList.amount;
        array = new Type[capacity];
        for(unsigned int i=0;i<amount;i++)
        {
          *(array + i) = *(arrayList.array + i);
        }
        return *this;
      }

      ~ArrayList()
      {
        deleteData();
      }

      unsigned int size() const
      {
        return amount;
      }

      void setSize(unsigned int newSize)
      {
        if(capacity < newSize)
        {
          expand(newSize - capacity);
        }
        amount = newSize;
      }

      void insert(unsigned int index, const Type& element)
      {
        assert(index <= amount);
        if(amount >= capacity)
        {
          expand(capacity);
        }

        for(unsigned int i=0;i<amount-index;i++)
        {
          unsigned int j = amount - i;
          *(array + j) = *(array + j - 1);
        }
        *(array + index) = element;
        amount++;
      }

      void add(const Type& element)
      {
        insert(amount, element);
      }

      void remove(unsigned int index)
      {
        assert(index < amount);
        for(unsigned int i=index+1;i<amount;i++)
        {
          *(array + i - 1) = *(array + i);
        }
        amount--;
      }

      void removeElement(const Type& element)
      {
        for(unsigned int i=0;i<amount;)
        {
          if(element == *(array + i))
          {
            remove(i);
          }
          else
          {
            i++;
          }
        }
      }

      void removeLast()
      {
        assert(amount > 0);
        remove(amount-1);
      }

      Type& operator[](unsigned int index) const
      {
        assert(index < amount);
        return *(array + index);
      }

      Array<Type> toArray() const
      {
        Array<Type> data(amount);
        for(unsigned int i=0;i<amount;i++)
        {
          data[i] = *(array + i);
        }
        return data;
      }

      const Type* getData() const
      {
        return array;
      }

      void clear()
      {
        amount = 0;
      }

      void trim()
      {
        setCapacity(amount);
      }

      bool contains(const Type& element)  const
      {
        for(unsigned int i=0;i<amount;i++)
        {
          if(element == *(array + i))
          {
            return true;
          }
        }
        return false;
      }
    };

    template<typename Type> std::ostream& operator<<(std::ostream& os, const ArrayList<Type>& list)
    {
      for(unsigned int i=0;i<list.size();i++)
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

#endif
