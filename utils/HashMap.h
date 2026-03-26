#ifndef GD_UTILS_HASHMAP_H
#define GD_UTILS_HASHMAP_H

#include "Hashing.h"
#include "LinkedList.h"
#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename KeyType, typename ValueType> class HashNode
      {
      public:
        KeyType key;
        ValueType value;

        HashNode(const KeyType& key, const ValueType& value) : key(key), value(value)
        {

        }

        HashNode(const HashNode<KeyType, ValueType>& node) : key(node.key), value(node.value)
        {

        }

        HashNode<KeyType, ValueType>& operator=(const HashNode<KeyType, ValueType>& node)
        {
          key = node.key;
          value = node.value;
          return *this;
        }
      };

      template<typename KeyType, typename ValueType> class HashMap
      {
        template<typename Type> friend class LinkedHashList;
        template<typename KeyType1, typename ValueType1> friend class LinkedHashMap;

      private:
        unsigned int size;
        LinkedList<HashNode<KeyType, ValueType>>* lists;

        void deleteData()
        {
          delete[] lists;
        }

        unsigned int getIndex(const KeyType& key) const
        {
          return hash(key)%size;
        }

        LinkedListIterator<HashNode<KeyType, ValueType>> findNode(const KeyType& key, LinkedList<HashNode<KeyType, ValueType>>** list, bool* found) const
        {
          *list = lists + getIndex(key);
          *found = false;
          LinkedListIterator<HashNode<KeyType, ValueType>> iterator(*list);

          while(iterator.isValid())
          {
            HashNode<KeyType, ValueType>& node = iterator.value();
            if(node.key == key)
            {
              *found = true;
              return iterator;
            }

            iterator.next();
          }
          return iterator;
        }

        HashNode<KeyType, ValueType>* createNode(const KeyType& key, const ValueType& value)
        {
          bool found;
          LinkedList<HashNode<KeyType, ValueType>>* list;
          LinkedListIterator<HashNode<KeyType, ValueType>> iterator = findNode(key, &list, &found);
          if(found)
          {
            return &iterator.value();
          }
          else
          {
            list->add(HashNode<KeyType, ValueType>(key, value));
            return &list->getLast();
          }
        }

        HashNode<KeyType, ValueType>* getNode(const KeyType& key) const
        {
          bool found;
          LinkedList<HashNode<KeyType, ValueType>>* list;
          LinkedListIterator<HashNode<KeyType, ValueType>> iterator = findNode(key, &list, &found);
          if(found)
          {
            return &iterator.value();
          }
          else
          {
            return NULL;
          }
        }
      public:
        HashMap()
        {
          size = 1000;
          lists = new LinkedList<HashNode<KeyType, ValueType>>[size];
        }

        HashMap(unsigned int size)
        {
          assert(size > 0);
          this->size = size;
          lists = new LinkedList<HashNode<KeyType, ValueType>>[size];
        }

        HashMap(const HashMap<KeyType, ValueType>& hashMap)
        {
          size = hashMap.size;
          lists = new LinkedList<HashNode<KeyType, ValueType>>[size];
          for(unsigned int i=0;i<size;i++)
          {
            *(lists + i) = *(hashMap.lists + i);
          }
        }

        HashMap<KeyType, ValueType>& operator=(const HashMap<KeyType, ValueType>& hashMap)
        {
          deleteData();
          size = hashMap.size;
          lists = new LinkedList<HashNode<KeyType, ValueType>>[size];
          for(unsigned int i=0;i<size;i++)
          {
            *(lists + i) = *(hashMap.lists + i);
          }
          return *this;
        }

        ~HashMap()
        {
          deleteData();
        }

        unsigned int getSize() const
        {
          return size;
        }

        void set(const KeyType& key, const ValueType& value)
        {
          HashNode<KeyType, ValueType>* node = createNode(key, value);
          node->value = value;
        }

        ValueType* get(const KeyType& key) const
        {
          HashNode<KeyType, ValueType>* node = getNode(key);
          if(node == NULL)
          {
            return NULL;
          }
          return &node->value;
        }

        void remove(const KeyType& key)
        {
          bool found;
          LinkedList<HashNode<KeyType, ValueType>>* list;
          LinkedListIterator<HashNode<KeyType, ValueType>> iterator = findNode(key, &list, &found);
          if(found)
          {
            return iterator.remove();
          }
        }
      };
    }
  }
}

#endif
