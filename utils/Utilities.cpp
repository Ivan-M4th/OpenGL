#include "Utilities.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      void nextMatrix4x4(unsigned int* index, const ArrayList<float>& data, gdm::Matrix4x4* matrix)
      {
        unsigned int i = 0;
        unsigned int j = 0;

        for(unsigned int k=0;k<16;k++)
        {
          matrix->get(i, j) = data[*index];

          j++;
          if(j >= 4)
          {
            j = 0;
            i++;
          }
          (*index)++;
        }
      }

      gdm::Matrix4x4 toMatrix4x4(const String& string)
      {
        ArrayList<float> data = string.toList<float>(" ");
        unsigned int i = 0;
        gdm::Matrix4x4 matrix;
        nextMatrix4x4(&i, data, &matrix);
        return matrix;
      }

      ArrayList<gdm::Matrix4x4> toMatrix4x4Array(const String& string)
      {
        ArrayList<float> data = string.toList<float>(" ");
        unsigned int i = 0;

        ArrayList<gdm::Matrix4x4> matrices;

        while(i < data.size())
        {
          gdm::Matrix4x4 matrix;
          nextMatrix4x4(&i, data, &matrix);
          matrices.add(matrix);
        }
        return matrices;
      }
    }
  }
}
