#include "ChunkSetPositionCalculator.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      ChunkSetPositionCalculator::ChunkSetPositionCalculator(int newX, int newY, int newZ, int oldX, int oldY, int oldZ)
      {
        this->newX = newX;
        this->newY = newY;
        this->newZ = newZ;

        this->oldX = oldX;
        this->oldY = oldY;
        this->oldZ = oldZ;
      }

      ChunkSetPositionCalculator::ChunkSetPositionCalculator(const ChunkSetPositionCalculator& calculator)
      {
        newX = calculator.newX;
        newY = calculator.newY;
        newZ = calculator.newZ;

        oldX = calculator.oldX;
        oldY = calculator.oldY;
        oldZ = calculator.oldZ;
      }

      ChunkSetPositionCalculator& ChunkSetPositionCalculator::operator=(const ChunkSetPositionCalculator& calculator)
      {
        newX = calculator.newX;
        newY = calculator.newY;
        newZ = calculator.newZ;

        oldX = calculator.oldX;
        oldY = calculator.oldY;
        oldZ = calculator.oldZ;
        return *this;
      }

      void ChunkSetPositionCalculator::newLocalToAbsolute(int lx, int ly, int lz, int* ax, int* ay, int* az) const
      {
        *ax = newX + lx;
        *ay = newY + ly;
        *az = newZ + lz;
      }

      void ChunkSetPositionCalculator::absoluteToOldLocal(int ax, int ay, int az, int* lx, int* ly, int* lz) const
      {
        *lx = ax - oldX;
        *ly = ay - oldY;
        *lz = az - oldZ;
      }

      void ChunkSetPositionCalculator::oldLocalToAbsolute(int lx, int ly, int lz, int* ax, int* ay, int* az) const
      {
        *ax = oldX + lx;
        *ay = oldY + ly;
        *az = oldZ + lz;
      }

      void ChunkSetPositionCalculator::absoluteToNewLocal(int ax, int ay, int az, int* lx, int* ly, int* lz) const
      {
        *lx = ax - newX;
        *ly = ay - newY;
        *lz = az - newZ;
      }

      void ChunkSetPositionCalculator::newLocalToOldLocal(int x, int y, int z, int* lx, int* ly, int* lz) const
      {
        int ax;
        int ay;
        int az;
        newLocalToAbsolute(x, y, z, &ax, &ay, &az);
        absoluteToOldLocal(ax, ay, az, lx, ly, lz);
      }

      void ChunkSetPositionCalculator::oldLocalToNewLocal(int x, int y, int z, int* lx, int* ly, int* lz) const
      {
        int ax;
        int ay;
        int az;
        oldLocalToAbsolute(x, y, z, &ax, &ay, &az);
        absoluteToNewLocal(ax, ay, az, lx, ly, lz);
      }
    }
  }
}
