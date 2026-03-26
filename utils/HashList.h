#ifndef GD_UTILS_HASHLIST_H
#define GD_UTILS_HASHLIST_H

#include <cassert>

#include "Hashing.h"
#include "LinkedList.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename Type> class HashList
      {
      private:
        unsigned int amount;
        LinkedList<Type>* lists;

        void deleteData()
        {
          delete[] lists;
        }

        unsigned int getIndex(const Type& element)
        {
          return hash(element)%size;
        }

        void findElement(const Type& element, LinkedList<Type>* list, bool* found, LinkedListIterator<Type>* iterator)
        {
          *iterator = LinkedListIterator<Type>(list);
          while(iterator->isValid())
          {
            if(iterator.value() == element)
            {
              *found = true;
              return;
            }
            iterator->next();
          }
          *found = false;
        }

      public:
        HashList()
        {
          amount = 100;
          lists = new LinkedList<Type>[amount];
        }

        HashList(unsigned int amount)
        {
          assert(amount > 0);
          this->amount = amount;
          lists = new LinkedList<Type>[amount];
        }

        HashList(const HashList<Type>& hashList)
        {
          amount = hashList.amount;
          lists = new LinkedList<Type>[amount];
          for(unsigned int i=0;i<amount;i++)
          {
            *(lists + i) = *(hashList.lists + i);
          }
        }

        HashList<Type>& operator=(const HashList<Type>& hashList)
        {
          deleteData();
          amount = hashList.amount;
          lists = new LinkedList<Type>[amount];
          for(unsigned int i=0;i<amount;i++)
          {
            *(lists + i) = *(hashList.lists + i);
          }
          return *this;
        }

        ~HashList()
        {
          deleteData();
        }

        void add(const Type& element)
        {
          LinkedList<Type>* list = lists + getIndex(element);
          bool found;
          LinkedListIterator<Type> iterator;
          findElement(element, list, &found, &iterator);
          if(!found)
          {
            list->add(element);
          }
        }

        void remove(const Type& element)
        {
          LinkedList<Type>* list = lists + getIndex(element);
          bool found;
          LinkedListIterator<Type> iterator;
          findElement(element, list, &found, &iterator);
          if(found)
          {
            iterator.remove();
          }
        }

        bool contains(const Type& element) const
        {
          LinkedList<Type>* list = lists + getIndex(element);
          bool found;
          LinkedListIterator<Type> iterator;
          findElement(element, list, &found, &iterator);
          return found;
        }
      };
    }
  }
}

#endif
