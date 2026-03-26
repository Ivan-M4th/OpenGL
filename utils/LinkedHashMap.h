#ifndef GD_UTILS_LINKEDHASHMAP_H
#define GD_UTILS_LINKEDHASHMAP_H

#include "HashMap.h"
#include "LinkedList.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename KeyType, typename ValueType> class LinkedHashMap
      {
        template<typename KeyType1, typename ValueType1> friend class LinkedHashMapIterator;

      private:
        LinkedList<HashNode<KeyType*, ValueType>> nodes;
        HashMap<KeyType, LinkedListIterator<HashNode<KeyType*, ValueType>>> hashMap;

      public:


        LinkedHashMap()
        {

        }

        LinkedHashMap(unsigned int size) : hashMap(size)
        {

        }

        LinkedHashMap(const LinkedHashMap<KeyType, ValueType>& linkedHashMap)
        {
          ConstLinkedListIterator<HashNode<KeyType*, ValueType>> iterator(&linkedHashMap.nodes);
          while(iterator.isValid())
          {
            set(*iterator.value().key, iterator.value().value);
            iterator.next();
          }
        }

        LinkedHashMap<KeyType, ValueType>& operator=(const LinkedHashMap<KeyType, ValueType>& linkedHashMap)
        {
          nodes = LinkedList<HashNode<KeyType*, ValueType>>();
          hashMap = HashMap<KeyType, LinkedListIterator<HashNode<KeyType*, ValueType>>>(hashMap.getSize());

          ConstLinkedListIterator<HashNode<KeyType*, ValueType>> iterator(&linkedHashMap.nodes);
          while(iterator.isValid())
          {
            set(*iterator.value().key, iterator.value().value);
            iterator.next();
          }
          return *this;
        }

        void set(const KeyType& key, const ValueType& value)
        {
          LinkedListIterator<HashNode<KeyType*, ValueType>>* foundIterator = hashMap.get(key);
          if(foundIterator == NULL)
          {
            nodes.add(HashNode<KeyType*, ValueType>(NULL, value));
            LinkedListIterator<HashNode<KeyType*, ValueType>> iterator(&nodes, false);
            HashNode<KeyType, LinkedListIterator<HashNode<KeyType*, ValueType>>>* node = hashMap.createNode(key, iterator); //?
            iterator.value().key = &node->key;
          }
          else
          {
            foundIterator->value().value = value;
          }
        }

        ValueType* get(const KeyType& key) const
        {
          LinkedListIterator<HashNode<KeyType*, ValueType>>* iterator = hashMap.get(key);
          if(iterator == NULL)
          {
            return NULL;
          }
          return &iterator->value().value;
        }

        void remove(const KeyType& key)
        {
          LinkedListIterator<HashNode<KeyType*, ValueType>>* iterator = hashMap.get(key);
          if(iterator != NULL)
          {
            iterator->remove();
            hashMap.remove(key);
          }
        }

        int size() const
        {
          return nodes.size();
        }
      };

      template<typename KeyType, typename ValueType> class LinkedHashMapIterator
      {
      private:
        LinkedHashMap<KeyType, ValueType>* linkedHashMap;
        LinkedListIterator<HashNode<KeyType*, ValueType>> nodesIterator;

      public:
        LinkedHashMapIterator(LinkedHashMap<KeyType, ValueType>* linkedHashMap) : nodesIterator(&linkedHashMap->nodes)
        {
          this->linkedHashMap = linkedHashMap;
        }

        bool isValid() const
        {
          return nodesIterator.isValid();
        }

        const KeyType& getKey() const
        {
          return *nodesIterator.value().key;
        }

        const ValueType& getValue() const
        {
          return nodesIterator.value().value;
        }

        void next()
        {
          nodesIterator.next();
        }

        void remove()
        {
          linkedHashMap->hashMap.remove(*nodesIterator.value().key);
          nodesIterator.remove();
        }
      };

      template<typename KeyType, typename ValueType> class ConstLinkedHashMapIterator
      {
      private:
        const LinkedHashMap<KeyType, ValueType>* linkedHashMap;
        ConstLinkedListIterator<HashNode<KeyType*, ValueType>> nodesIterator;

      public:
        ConstLinkedHashMapIterator(const LinkedHashMap<KeyType, ValueType>* linkedHashMap) : nodesIterator(&linkedHashMap->nodes)
        {
          this->linkedHashMap = linkedHashMap;
        }

        ConstLinkedHashMapIterator(const ConstLinkedHashMapIterator<KeyType, ValueType>& iterator) : nodesIterator(iterator.nodesIterator)
        {
          linkedHashMap = iterator.linkedHashMap;
        }

        ConstLinkedHashMapIterator<KeyType, ValueType>& operator=(const ConstLinkedHashMapIterator<KeyType, ValueType>& iterator)
        {
          linkedHashMap = iterator.linkedHashMap;
          nodesIterator = iterator.nodesIterator;
          return *this;
        }

        bool isValid() const
        {
          return nodesIterator.isValid();
        }

        const KeyType& getKey() const
        {
          return *nodesIterator.value().key;
        }

        const ValueType& getValue() const
        {
          return nodesIterator.value().value;
        }

        void next()
        {
          nodesIterator.next();
        }
      };

      template<typename KeyType, typename ValueType> std::ostream& operator<<(std::ostream& os, const LinkedHashMap<KeyType, ValueType>& linkedHashMap)
      {
        ConstLinkedHashMapIterator<KeyType, ValueType> iterator(&linkedHashMap);
        while(iterator.isValid())
        {
          os << iterator.getKey() << " : " << iterator.getValue() << std::endl;
          iterator.next();
        }
        return os;
      }
    }
  }
}

#endif
