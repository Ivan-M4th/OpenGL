#include "LoadedTerrain.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace voxel
      {

        LoadedTerrain::LoadedTerrain()
        {
          hwidth = 20;
          hheight = 4;
          calculateSize();

          array = new bool[size];
          clear();

          position = gdm::Vector3i(7, -2,7);
        }

        LoadedTerrain::LoadedTerrain(const LoadedTerrain& loadedTerrain)
        {
          hwidth = loadedTerrain.hwidth;
          hheight = loadedTerrain.hheight;

          width = loadedTerrain.width;
          height = loadedTerrain.height;
          size = loadedTerrain.size;
          position = loadedTerrain.position;

          array = new bool[size];
          for(int i=0;i<size;i++)
          {
            *(array + i) = *(loadedTerrain.array + i);
          }
        }

        LoadedTerrain& LoadedTerrain::operator=(const LoadedTerrain& loadedTerrain)
        {
          delete [] array;

          hwidth = loadedTerrain.hwidth;
          hheight = loadedTerrain.hheight;

          width = loadedTerrain.width;
          height = loadedTerrain.height;
          size = loadedTerrain.size;
          position = loadedTerrain.position;

          array = new bool[size];
          for(int i=0;i<size;i++)
          {
            *(array + i) = *(loadedTerrain.array + i);
          }

          return *this;
        }

        LoadedTerrain::~LoadedTerrain()
        {
          delete [] array;
        }

        void LoadedTerrain::calculateSize()
        {
          width = 2*hwidth + 1;
          height = 2*hheight + 1;
          size = width*width*height;
        }

        void LoadedTerrain::clear()
        {
          for(int i=0;i<size;i++)
          {
            *(array + i) = false;
          }
        }

        bool LoadedTerrain::isValid(int x, int y, int z) const
        {
          if(0 <= x && x < width)
          {
            if(0 <= y && y < height)
            {
              if(0 <= z && z < width)
              {
                return true;
              }
            }
          }
          return false;
        }

        int LoadedTerrain::getIndex(int x, int y, int z) const
        {
          return (width*y + x)*width + z;
        }

        int LoadedTerrain::getHWidth() const
        {
          return hwidth;
        }

        int LoadedTerrain::getHHeight() const
        {
          return hheight;
        }

        int LoadedTerrain::getHeight() const
        {
          return height;
        }

        bool LoadedTerrain::isLoaded(int x, int y, int z) const
        {
          assert(isValid(x, y, z));
          return *(array + getIndex(x, y, z));
        }

        void LoadedTerrain::setLoaded(int x, int y, int z, bool loaded)
        {
          assert(isValid(x, y, z));
          *(array + getIndex(x, y, z)) = loaded;
        }

        const gdm::Vector3i& LoadedTerrain::getPosition() const
        {
          return position;
        }

        void LoadedTerrain::setPosition(const gdm::Vector3i& newPosition)
        {
          gdm::Vector3i translation = newPosition - position;
          bool* newArray = new bool[size];

          for(int x=0;x<width;x++)
          {
            for(int y=0;y<height;y++)
            {
              for(int z=0;z<width;z++)
              {

                int oldX = translation.x + x;
                int oldY = translation.y + y;
                int oldZ = translation.z + z;

                if(isValid(oldX, oldY, oldZ))
                {
                  *(newArray + getIndex(x, y, z)) = *(array + getIndex(oldX, oldY, oldZ));
                }
                else
                {
                  *(newArray + getIndex(x, y, z)) = false;
                }
              }
            }
          }
          delete [] array;

          array = newArray;
          position = newPosition;
        }
      }
    }
  }
}
