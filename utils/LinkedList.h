#ifndef GD_UTILS_LINKEDLIST_H
#define GD_UTILS_LINKEDLIST_H

#include <cassert>
#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      template<typename Type> class LinkedListNode
      {
      public:
        Type value;
        LinkedListNode<Type>* next;
        LinkedListNode<Type>* previous;

        LinkedListNode(const Type& value) : value(value)
        {
          next = NULL;
          previous = NULL;
        }

        LinkedListNode(const LinkedListNode<Type>& node) : value(node.value)
        {
          next = node.next;
          previous = node.previous;
        }

        LinkedListNode<Type>& operator=(const LinkedListNode<Type>& node)
        {
          value = node.value;
          next = node.next;
          previous = node.previous;
          return *this;
        }
      };

      template<typename Type> class LinkedList
      {
        template<typename Type1> friend class LinkedListIterator;
        template<typename Type1> friend class ConstLinkedListIterator;

      private:
        unsigned int amount;
        LinkedListNode<Type>* start;
        LinkedListNode<Type>* end;

        void deleteData()
        {
          LinkedListNode<Type>* node = start;
          while(node != NULL)
          {
            LinkedListNode<Type>* nextNode = node->next;
            delete node;
            node = nextNode;
          }
        }

      public:

        LinkedList()
        {
          amount = 0;
          start = NULL;
          end = NULL;
        }

        LinkedList(const LinkedList<Type>& list)
        {
          start = NULL;
          end = NULL;
          amount = 0;
          LinkedListNode<Type>* node = list.start;
          while(node != NULL)
          {
            add(node->value);
            node = node->next;
          }
        }

        LinkedList<Type>& operator=(const LinkedList<Type>& list)
        {
          deleteData();
          start = NULL;
          end = NULL;

          amount = 0;
          LinkedListNode<Type>* node = list.start;
          while(node != NULL)
          {
            add(node->value);
            node = node->next;
          }
          return *this;
        }

        ~LinkedList()
        {
          deleteData();
        }

        void add(const Type& value)
        {
          if(end == NULL)
          {
            start = new LinkedListNode<Type>(value);
            end = start;
            amount++;
          }
          else
          {
            LinkedListNode<Type>* newEnd = new LinkedListNode<Type>(value);
            newEnd->next = end->next;
            newEnd->previous = end;

            end->next = newEnd;
            end = newEnd;
            amount++;
          }
        }

        void addFirst(const Type& value)
        {
          if(start == NULL)
          {
            start = new LinkedListNode<Type>(value);
            end = start;
            amount++;
          }
          else
          {
            LinkedListNode<Type>* newStart = new LinkedListNode<Type>(value);
            newStart->next = start;

            start->previous = newStart;

            start = newStart;
            amount++;
          }
        }

        Type& getFirst() const
        {
          assert(start != NULL);
          return start->value;
        }

        Type& getLast() const
        {
          assert(end != NULL);
          return end->value;
        }

        void removeFirst()
        {
          assert(start != NULL);
          if(start == end)
          {
            delete start;
            start = NULL;
            end = NULL;
            amount = 0;
          }
          else
          {
            LinkedListNode<Type>* newStart = start->next;
            newStart->previous = NULL;
            delete start;
            start = newStart;
            amount--;
          }
        }

        void removeLast()
        {
          assert(end != NULL);
          if(start == end)
          {
            delete start;
            start = NULL;
            end = NULL;
            amount = 0;
          }
          else
          {
            LinkedListNode<Type>* newEnd = end->previous;
            newEnd->next = NULL;
            delete end;
            end = newEnd;
            amount--;
          }
        }

        void concatenate(LinkedList<Type>& list)
        {
          if(list.size() == 0)
          {
            return;
          }

          if(start == NULL)
          {
            start = list.start;
            end = list.end;
            amount = list.amount;
          }
          else
          {
            end->next = list.start;
            list.start->previous = end;
            end = list.end;

            amount = amount + list.amount;
          }

          list.amount = 0;
          list.start = NULL;
          list.end = NULL;
        }

        unsigned int size() const
        {
          return amount;
        }
      };

      template<typename Type> class ConstLinkedListIterator
      {
      private:
        const LinkedListNode<Type>* node;
        const LinkedList<Type>* list;

      public:
        ConstLinkedListIterator(const LinkedList<Type>* list)
        {
          this->list = list;
          node = list->start;
        }

        ConstLinkedListIterator(const ConstLinkedListIterator<Type>& iterator)
        {
          list = iterator.list;
          node = iterator.node;
        }

        ConstLinkedListIterator<Type>& operator=(const ConstLinkedListIterator<Type>& iterator)
        {
          list = iterator.list;
          node = iterator.node;
          return *this;
        }

        bool isValid() const
        {
          return node != NULL;
        }

        const Type& value() const
        {
          return node->value;
        }

        void next()
        {
          assert(isValid());
          node = node->next;
        }
      };

      template<typename Type> class LinkedListIterator
      {
      private:
        LinkedListNode<Type>* node;
        LinkedList<Type>* list;

      public:
        LinkedListIterator(LinkedList<Type>* list)
        {
          this->list = list;
          node = list->start;
        }

        LinkedListIterator(LinkedList<Type>* list, bool start)
        {
          this->list = list;
          if(start)
          {
            node = list->start;
          }
          else
          {
            node = list->end;
          }
        }

        LinkedListIterator(const LinkedListIterator<Type>& iterator)
        {
          list = iterator.list;
          node = iterator.node;
        }

        LinkedListIterator<Type>& operator=(const LinkedListIterator<Type>& iterator)
        {
          list = iterator.list;
          node = iterator.node;
          return *this;
        }

        bool isValid() const
        {
          return node != NULL;
        }

        bool hasNext() const
        {
          assert(isValid());
          return node->next != NULL;
        }

        bool hasPrevious() const
        {
          assert(isValid());
          return node->previous != NULL;
        }

        void reset()
        {
          node = list->start;
        }

        Type& value() const
        {
          assert(isValid());
          return node->value;
        }

        Type& next()
        {
          assert(isValid());
          node = node->next;
          return node->value;
        }

        Type& previous()
        {
          assert(isValid());
          node = node->previous;
          return node->value;
        }

        void insert(const Type& value)
        {
          assert(isValid());

          if(!hasPrevious())
          {
            //addfirst
            list->addFirst(value);
            node = list->start;
          }
          else
          {
            LinkedListNode<Type>* previousNode = node->previous;

            LinkedListNode<Type>* newNode = new LinkedListNode<Type>(value);
            newNode->previous = previousNode;
            newNode->next = node;

            previousNode->next = newNode;
            node->previous = newNode;

            node = newNode;

            list->amount++;
          }
        }

        void insert(unsigned int index, const Type& value)
        {
          reset();
          for(unsigned int i=0;i<index;i++)
          {
            next();
          }
          insert(value);
        }

        void remove()
        {
          assert(isValid());

          if(!hasPrevious())
          {
            list->removeFirst();
            node = list->start;
          }
          else if(!hasNext())
          {
            list->removeLast();
            node = NULL;
          }
          else
          {
            LinkedListNode<Type>* nextNode = node->next;
            LinkedListNode<Type>* previousNode = node->previous;
            delete node;
            node = nextNode;

            previousNode->next = node;
            node->previous = previousNode;

            list->amount--;
          }
        }

        void remove(unsigned int index)
        {
          reset();
          for(unsigned int i=0;i<index;i++)
          {
            next();
          }
          remove();
        }

        void removeElement(const Type& element)
        {
          reset();
          while(isValid())
          {
            if(value() == element)
            {
              remove();
              return;
            }
            next();
          }
        }
      };

      template<typename Type> std::ostream& operator<<(std::ostream& os, const LinkedList<Type>& list)
      {
        ConstLinkedListIterator<Type> iterator(&list);
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
