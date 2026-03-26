#ifndef GD_VOXEL_CHUNKSETPOSITIONCALCULATOR_H
#define GD_VOXEL_CHUNKSETPOSITIONCALCULATOR_H

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class ChunkSetPositionCalculator
      {
      private:
        int newX;
        int newY;
        int newZ;

        int oldX;
        int oldY;
        int oldZ;

      public:
        ChunkSetPositionCalculator(int, int, int, int, int, int);
        ChunkSetPositionCalculator(const ChunkSetPositionCalculator&);
        ChunkSetPositionCalculator& operator=(const ChunkSetPositionCalculator&);

        void newLocalToAbsolute(int, int, int, int*, int*, int*) const;
        void absoluteToOldLocal(int, int, int, int*, int*, int*) const;

        void oldLocalToAbsolute(int, int, int, int*, int*, int*) const;
        void absoluteToNewLocal(int, int, int, int*, int*, int*) const;

        void newLocalToOldLocal(int, int, int, int*, int*, int*) const;
        void oldLocalToNewLocal(int, int, int, int*, int*, int*) const;
      };
    }
  }
}

#endif
