#ifndef GD_UTILS_ARRAY_H
#define GD_UTILS_ARRAY_H

#include <cassert>
#include <cstddef>

namespace gt
{
  namespace doubovik
  {
    template<typename Type> class Array
    {
    private:
      unsigned int amount;
      Type* data;

      void deleteData()
      {
        delete[] data;
      }
    public:
      Array()
      {
        data = NULL;
        amount = 0;
      }

      Array(unsigned int amount)
      {
        this->amount = amount;
        if(amount == 0)
        {
          data = NULL;
        }
        else
        {
          data = new Type[amount];
        }
      }

      Array(const Array<Type>& array)
      {
        amount = array.amount;
        if(amount == 0)
        {
          data = NULL;
        }
        else
        {
          data = new Type[amount];
          for(unsigned int i=0;i<amount;i++)
          {
            *(data + i) = *(array.data + i);
          }
        }
      }

      Array<Type>& operator=(const Array<Type>& array)
      {
        deleteData();
        amount = array.amount;
        if(amount == 0)
        {
          data = NULL;
        }
        else
        {
          data = new Type[amount];
          for(unsigned int i=0;i<amount;i++)
          {
            *(data + i) = *(array.data + i);
          }
        }
        return *this;
      }

      ~Array()
      {
        deleteData();
      }

      unsigned int size() const
      {
        return amount;
      }

      Type& operator[](unsigned int index) const
      {
        assert(index < amount);
        return *(data + index);
      }
    };
  }
}

#endif
