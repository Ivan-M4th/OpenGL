#include "String.h"

#include <cstdio>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      String::String()
      {
        chars.add('\0');
      }

      String::String(unsigned int capacity) : chars(capacity + 1)
      {
        chars.add('\0');
      }

      String::String(const char* data)
      {
        unsigned int i=0;
        while(*(data + i) != '\0')
        {
          chars.add(*(data + i));
          i++;
        }
        chars.add('\0');
      }

      String::String(int x, unsigned int charsCapacity) : chars(charsCapacity)
      {
        char* array = new char[charsCapacity];
        sprintf(array, "%d", x);

        unsigned int i = 0;
        while(*(array + i) != '\0')
        {
          chars.add(*(array + i));
          i++;
        }
        chars.add('\0');

        delete[] array;
      }

      String::String(float x, unsigned int charsCapacity) : chars(charsCapacity)
      {
        char* array = new char[charsCapacity];
        sprintf(array, "%f", x);

        unsigned int i = 0;
        while(*(array + i) != '\0')
        {
          chars.add(*(array + i));
          i++;
        }
        chars.add('\0');

        delete[] array;
      }

      String::String(const String& string)
      {
        chars = string.chars;
      }

      String& String::operator=(const String& string)
      {
        chars = string.chars;
        return *this;
      }

      unsigned int String::size() const
      {
        return chars.size() - 1;
      }

      void String::addChar(char c)
      {
        chars.insert(chars.size()-1, c);
      }

      const char* String::toChars() const
      {
        return chars.getData();
      }

      bool String::isChars(unsigned int index, const char* data, unsigned int size) const
      {
        for(unsigned int i=0;i<size;i++)
        {
          if(*(data + i) != chars[index + i])
          {
            return false;
          }
        }
        return true;
      }

      String String::replace(const char* from, const char* to) const
      {
        unsigned int fromSize = strlen(from);
        unsigned int toSize = strlen(to);

        String result(size());

        for(unsigned int i=0;i<size()-fromSize+1;)
        {
          if(isChars(i, from, fromSize))
          {
            for(unsigned int j=0;j<toSize;j++)
            {
              result.addChar(*(to + j));
            }
            i+=fromSize;
          }
          else
          {
            result.addChar(chars[i]);
            i++;
          }
        }
        return result;
      }

      void String::getStringToNextRejex(unsigned int* index, String* string, const char* rejex, unsigned int rejexSize) const
      {
        while(*index < size())
        {
          if(*index + rejexSize - 1 < size() && isChars(*index, rejex, rejexSize))
          {
            (*index)+=rejexSize;
            break;
          }
          else
          {
            (*string).addChar(chars[*index]);
            (*index)++;
          }
        }
      }

      ArrayList<String> String::split(const char* rejex) const
      {
        unsigned int rejexSize = strlen(rejex);
        ArrayList<String> result;

        unsigned int index = 0;
        while(index < size())
        {
          String string;
          getStringToNextRejex(&index, &string, rejex, rejexSize);
          result.add(string);
        }

        return result;
      }

      String::operator double() const
      {
        return atof(chars.getData());
      }

      String::operator float() const
      {
        double x = *this;
        return x;
      }

      String::operator int() const
      {
        return atoi(chars.getData());
      }

      String::operator unsigned int() const
      {
        int x = *this;
        return x;
      }

      char String::operator[](unsigned int index) const
      {
        return chars[index];
      }

      bool String::operator==(const String& string) const
      {
        if(size() != string.size())
        {
          return false;
        }
        for(unsigned int i=0;i<size();i++)
        {
          if(chars[i] != string[i])
          {
            return false;
          }
        }
        return true;
      }

      String String::operator+(const String& string) const
      {
        String result(size() + string.size());
        for(unsigned int i=0;i<size();i++)
        {
          result.addChar((*this)[i]);
        }
        for(unsigned int i=0;i<string.size();i++)
        {
          result.addChar(string[i]);
        }
        return result;
      }

      String& String::operator+=(const String& string)
      {
        for(unsigned int i=0;i<string.size();i++)
        {
          addChar(string[i]);
        }
        return *this;
      }

      String& String::operator+=(const char* array)
      {
        unsigned int arrayLen = strlen(array);
        for(unsigned int i=0;i<arrayLen;i++)
        {
          addChar(*(array + i));
        }
        return *this;
      }

      String operator+(const String& string, const char* chars)
      {
        unsigned int charsLen = strlen(chars);
        String result(string.size() + charsLen);
        for(unsigned int i=0;i<string.size();i++)
        {
          result.addChar(string[i]);
        }
        for(unsigned int i=0;i<charsLen;i++)
        {
          result.addChar(*(chars + i));
        }
        return result;
      }

      String operator+(const char* chars, const String& string)
      {
        unsigned int charsLen = strlen(chars);
        String result(string.size() + charsLen + 1);
        for(unsigned int i=0;i<charsLen;i++)
        {
          result.addChar(*(chars + i));
        }
        for(unsigned int i=0;i<string.size();i++)
        {
          result.addChar(string[i]);
        }
        return result;
      }

      bool operator==(const String& string, const char* chars)
      {
        unsigned int charsLen = strlen(chars);
        if(string.size() != charsLen)
        {
          return false;
        }

        for(unsigned int i=0;i<charsLen;i++)
        {
          if(string[i] != *(chars + i))
          {
            return false;
          }
        }
        return true;
      }

      bool operator==(const char* chars, const String& string)
      {
        return string == chars;
      }

      std::ostream& operator<<(std::ostream& os, const String& string)
      {
        for(unsigned int i=0;i<string.size();i++)
        {
          os << string[i];
        }
        return os;
      }

      String fileToString(const char* fileName)
      {
        FILE* file = fopen(fileName, "r");
        if(file == NULL)
        {
          std::cout << "Error: " << fileName << " was not found!" << std::endl;
          exit(EXIT_FAILURE);
        }
        fseek(file, 0, SEEK_END);
        unsigned int fileSize = ftell(file);
        fseek(file, 0, SEEK_SET);

        std::cout << "Size of " << fileName << ": " << fileSize << std::endl;
        String result(fileSize);

        int c;
        c = fgetc(file);
        while(c != EOF)
        {
          result.addChar((char)c);
          c = fgetc(file);
        }
        fclose(file);
        std::cout << fileName << " was read correctly!" << std::endl;

        return result;
      }
    }
  }
}
