#ifndef GD_UTILS_STRING_H
#define GD_UTILS_STRING_H

#include <iostream>
#include <cstring>

#include "ArrayList.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class String
      {
      private:
        ArrayList<char> chars;

        bool isChars(unsigned int, const char*, unsigned int) const;
        void getStringToNextRejex(unsigned int*, String*, const char*, unsigned int) const;
      public:
        String();
        String(unsigned int);
        String(const char*);
        String(int, unsigned int);
        String(float, unsigned int);
        String(const String&);
        String& operator=(const String&);

        unsigned int size() const;
        void addChar(char);
        const char* toChars() const;
        String replace(const char*, const char*) const;
        ArrayList<String> split(const char*) const;

        template<typename Type> ArrayList<Type> toList(const char* rejex) const
        {
          ArrayList<Type> list;
          unsigned int rejexSize = strlen(rejex);

          unsigned int index = 0;
          while(index < size())
          {
            String string;
            getStringToNextRejex(&index, &string, rejex, rejexSize);
            Type element = string;
            list.add(element);
          }

          return list;
        }

        operator double() const;
        operator float() const;
        operator int() const;
        operator unsigned int() const;

        char operator[](unsigned int) const;

        bool operator==(const String&) const;
        String& operator+=(const String&);
        String& operator+=(const char*);
        String operator+(const String&) const;
      };

      String operator+(const String&, const char*);
      String operator+(const char*, const String&);
      bool operator==(const String&, const char*);
      bool operator==(const char*, const String&);

      std::ostream& operator<<(std::ostream&, const String&);

      String fileToString(const char*);
    }
  }
}

#endif
