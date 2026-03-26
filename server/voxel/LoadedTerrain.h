#ifndef GD_SERVER_VOXEL_LOADEDTERRAIN_H
#define GD_SERVER_VOXEL_LOADEDTERRAIN_H

#include "../../gddef.h"

#include "../../math/Vector3i.h"

namespace gt
{
  namespace doubovik
  {
    namespace server
    {
      namespace voxel
      {
        class LoadedTerrain
        {
        private:
          int hwidth;
          int hheight;

          int width;
          int height;
          int size;
          bool* array;
          gdm::Vector3i position;

          void calculateSize();
          void clear();
          int getIndex(int, int, int) const;

        public:
          LoadedTerrain();
          LoadedTerrain(const LoadedTerrain&);
          LoadedTerrain& operator=(const LoadedTerrain&);
          ~LoadedTerrain();

          bool isValid(int, int, int) const;
          int getHWidth() const;
          int getHHeight() const;
          int getHeight() const;
          bool isLoaded(int, int, int) const;
          void setLoaded(int, int, int, bool);

          const gdm::Vector3i& getPosition() const;
          void setPosition(const gdm::Vector3i&); //chunk coords
        };
      }
    }
  }
}

#endif
