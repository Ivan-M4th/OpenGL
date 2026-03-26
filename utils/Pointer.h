#ifndef GD_UTILS_POINTER_H
#define GD_UTILS_POINTER_H

#include <cstddef>

namespace gt
{
  namespace doubovik
  {
    template<typename Type> class Pointer
    {
    private:
      unsigned int* amount;
      Type* ptr;

      bool list;

      void deleteSingleData()
      {
        delete ptr;
        ptr = NULL;
      }

      void deleteListData()
      {
        delete[] ptr;
        ptr = NULL;
      }

      void deleteData()
      {
        if(list)
        {
          deleteListData();
        }
        else
        {
          deleteSingleData();
        }
        delete amount;
        amount = NULL;
      }

      void removePointer()
      {
        if(amount != NULL)
        {
          (*amount)--;
          if(*amount == 0)
          {
            deleteData();
          }
        }
      }

      void addPointer() const
      {
        if(amount != NULL)
        {
          (*amount)++;
        }
      }

    public:
      Pointer()
      {
        ptr = NULL;
        amount = NULL;
        list = false;
      }

      Pointer(Type* ptr, bool list)
      {
        this->ptr = ptr;
        this->list = list;
        amount = new unsigned int(1);
      }

      Pointer(const Pointer<Type>& pointer)
      {
        if(pointer.ptr == NULL)
        {
          ptr = NULL;
          amount = NULL;
          list = false;
        }
        else
        {
          ptr = pointer.ptr;
          amount = pointer.amount;
          list = pointer.list;
          addPointer();
        }
      }

      Pointer<Type>& operator=(const Pointer<Type>& pointer)
      {
        removePointer();
        if(pointer.ptr != NULL)
        {
          ptr = pointer.ptr;
          amount = pointer.amount;
          list = pointer.list;
          addPointer();
        }
        else
        {
          ptr = NULL;
          amount = NULL;
          list = false;
        }
        return *this;
      }

      ~Pointer()
      {
        removePointer();
      }

      void deletePointer()
      {
        removePointer();
        ptr = NULL;
        amount = NULL;
        list = false;
      }

      Type* value() const
      {
        return ptr;
      }

      unsigned int count() const
      {
        return *amount;
      }

      bool operator==(const Pointer<Type>& pointer)
      {
        return ptr == pointer.ptr;
      }
    };
  }
}

#endif
