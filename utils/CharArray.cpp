#include "CharArray.h"

#include <cmath>
#include <iostream>
#include <cstring>
#include <cassert>

namespace gt
{
  namespace doubovik
  {
    CharArray::CharArray()
    {
      size = 0;
      array = NULL;
    }

    CharArray::CharArray(int x)
    {
      int intSize;
      if(x == 0)
      {
        intSize = 1;
        size = intSize;
      }
      else if(x > 0)
      {
        intSize = floor(log10(x)) + 1;
        size = intSize;
      }
      else
      {
        intSize = floor(log10(-x)) + 1;
        size = intSize + 1;
      }

      array = new char[size + 1];
      intToChars(array, size, x, intSize);
      *(array + size) = '\0';
    }

    CharArray::CharArray(float x)
    {
      char buffer[64];
      size = snprintf(buffer, sizeof(char)*64, "%f", x);
      assert(size > 0);
      assert(size <= 64);
      array = new char[size + 1];
      for(int i=0;i<size;i++)
      {
        *(array + i) = *(buffer + i);
      }
      *(array + size) = '\0';
    }

    CharArray::CharArray(const CharArray& charArray)
    {
      size = charArray.size;
      array = new char[size + 1];
      for(int i=0;i<size;i++)
      {
        *(array + i) = *(charArray.array + i);
      }
      *(array + size) = '\0';
    }

    CharArray& CharArray::operator=(const CharArray& charArray)
    {
      delete[] array;
      size = charArray.size;
      array = new char[size + 1];
      for(int i=0;i<size;i++)
      {
        *(array + i) = *(charArray.array + i);
      }
      *(array + size) = '\0';
      return *this;
    }

    CharArray::~CharArray()
    {
      delete[] array;
    }

    void CharArray::intToChars(char* chars, int charsSize, int x, int intSize) const
    {
      if(x < 0)
      {
        x = -x;
        *chars = '-';
      }
      for(int i=0;i<intSize;i++)
      {
        int r = x%10;
        x = (x - r)/10;
        *(chars + charsSize - 1 - i) = '0' + r;
      }
    }

    void CharArray::print() const
    {
      if(array != NULL)
      {
        std::cout << array << std::endl;
      }
    }

    void CharArray::add(const char* chars, int charsSize)
    {
      int newSize = size + charsSize;
      char* newArray = new char[newSize + 1];
      for(int i=0;i<size;i++)
      {
        *(newArray + i) = *(array + i);
      }
      for(int i=0;i<charsSize;i++)
      {
        *(newArray + size + i) = *(chars + i);
      }
      *(newArray + newSize) = '\0';

      delete[] array;
      size = newSize;
      array = newArray;
    }

    void CharArray::add(const char* chars)
    {
      add(chars, strlen(chars));
    }

    void CharArray::add(int x)
    {
      CharArray intCharArray(x);
      (*this)+=intCharArray;
    }

    void CharArray::add(float x)
    {
      CharArray floatCharArray(x);
      (*this)+=floatCharArray;
    }

    const char* CharArray::value() const
    {
      return array;
    }

    void CharArray::operator+=(const CharArray& charArray)
    {
      add(charArray.array, charArray.size);
    }
  }
}
