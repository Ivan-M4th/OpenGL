#ifndef GD_UTILS_LINKEDHASHLIST_H
#define GD_UTILS_LINKEDHASHLIST_H

#include <iostream>

#include "LinkedList.h"
#include "HashMap.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename Type> class LinkedHashList
      {
        template<typename Type1> friend class ConstLinkedHashListIterator;

      private:
        LinkedList<Type*> values;
        HashMap<Type, LinkedListIterator<Type*>> hashMap;

      public:
        LinkedHashList()
        {

        }

        LinkedHashList(unsigned int amount) : hashMap(amount)
        {

        }

        LinkedHashList(const LinkedHashList<Type>& linkedHashList)
        {
          ConstLinkedListIterator<Type*> iterator(&linkedHashList.values);
          while(iterator.isValid())
          {
            add(*iterator.value());
            iterator.next();
          }
        }

        LinkedHashList<Type>& operator=(const LinkedHashList<Type>& linkedHashList)
        {
          values = LinkedList<Type*>();
          hashMap = HashMap<Type, LinkedListIterator<Type*>>();

          ConstLinkedListIterator<Type*> iterator(&linkedHashList.values);
          while(iterator.isValid())
          {
            add(*iterator.value());
            iterator.next();
          }
          return *this;
        }

        void add(const Type& element)
        {
          if(hashMap.get(element) == NULL)
          {
            values.add(NULL);
            LinkedListIterator<Type*> iterator(&values, false);
            HashNode<Type, LinkedListIterator<Type*>>* node = hashMap.createNode(element, iterator);
            iterator.value() = &node->key;
          }
        }

        void remove(const Type& element)
        {
          LinkedListIterator<Type*>* iterator = hashMap.get(element);
          if(iterator != NULL)
          {
            iterator->remove();
            hashMap.remove(element);
          }
        }

        bool contains(const Type& element) const
        {
          return hashMap.get(element) != NULL;
        }
      };

      template<typename Type> class ConstLinkedHashListIterator
      {
      private:
        const LinkedHashList<Type>* linkedHashList;
        ConstLinkedListIterator<Type*> listIterator;

      public:
        ConstLinkedHashListIterator(const LinkedHashList<Type>* linkedHashList) : listIterator(&linkedHashList->values)
        {
          this->linkedHashList = linkedHashList;
        }

        ConstLinkedHashListIterator(const ConstLinkedHashListIterator<Type>& iterator) : listIterator(iterator.listIterator)
        {
          linkedHashList = iterator.linkedHashList;
        }

        ConstLinkedHashListIterator<Type>& operator=(const ConstLinkedHashListIterator<Type>& iterator)
        {
          linkedHashList = iterator.linkedHashList;
          listIterator = iterator.listIterator;
          return *this;
        }

        bool isValid() const
        {
          return listIterator.isValid();
        }

        void next()
        {
          listIterator.next();
        }

        const Type& value() const
        {
          return *listIterator.value();
        }
      };

      template<typename Type> std::ostream& operator<<(std::ostream& os, const LinkedHashList<Type>& linkedHashList)
      {
        ConstLinkedHashListIterator<Type> iterator(&linkedHashList);
        while(iterator.isValid())
        {
          os << iterator.value() << std::endl;
          iterator.next();
        }
        return os;
      }
    }
  }
}

#endif
