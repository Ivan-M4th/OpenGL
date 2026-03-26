#ifndef GD_UTILS_CHARARRAY_H
#define GD_UTILS_CHARARRAY_H

namespace gt
{
  namespace doubovik
  {
    class CharArray
    {
    private:
      char* array;
      int size;

      void intToChars(char*, int, int, int) const;
    public:
      CharArray();
      CharArray(int);
      CharArray(float);
      CharArray(const CharArray&);
      CharArray& operator=(const CharArray&);
      ~CharArray();

      void print() const;
      void add(const char*, int);
      void add(const char*);
      void add(int);
      void add(float);

      const char* value() const;

      void operator+=(const CharArray&);
    };
  }
}

#endif
