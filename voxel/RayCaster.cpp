#include "RayCaster.h"

#include "VoxelPositionCalculator.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      RayCaster::RayCaster(const gdm::Vector3& position, const gdm::Vector3& direction)
      {
        int bx;
        int by;
        int bz;

        VoxelPositionCalculator calculator(position);
        calculator.calculateBlockCoords(&bx, &by, &bz);
        blockPosition.x = bx;
        blockPosition.y = by;
        blockPosition.z = bz;

        calculateParameters(bx, position.getX(), direction.getX(), &toNextBlock.x, &stepsToNext.getX(), &steps.getX(), &useX);
        calculateParameters(by, position.getY(), direction.getY(), &toNextBlock.y, &stepsToNext.getY(), &steps.getY(), &useY);
        calculateParameters(bz, position.getZ(), direction.getZ(), &toNextBlock.z, &stepsToNext.getZ(), &steps.getZ(), &useZ);
        count = 0;
      }

      void RayCaster::calculateParameters(int bx, float x, float directionx, int* toNextBlockX, float* stepsToNextx, float* stepsx, bool* useX) const
      {
        if(directionx*directionx < 0.0000001)
        {
          *useX = false;
        }
        *useX = true;

        if(directionx > 0.0)
        {
          *toNextBlockX = 1;
          *stepsToNextx = ((float)(bx + 1) - x)/directionx;
          *stepsx = 1.0/directionx;
        }
        else
        {
          *toNextBlockX = -1;
          *stepsToNextx = ((float)bx - x)/directionx;
          *stepsx = -1.0/directionx;
        }
      }

      void RayCaster::next(int toNextBlockX, float stepsx, int* x, float* stepsToNextX) const
      {
        (*x)+=toNextBlockX;
        (*stepsToNextX)+=stepsx;
      }

      void RayCaster::next(int toNextBlockX, float stepsx, int* x, float* stepsToNextX, int toNextBlockY, float stepsy, int* y, float* stepsToNextY) const
      {
        if(*stepsToNextX < *stepsToNextY)
        {
          next(toNextBlockX, stepsx, x, stepsToNextX);
        }
        else
        {
          next(toNextBlockY, stepsy, y, stepsToNextY);
        }
      }

      void RayCaster::next(int toNextBlockX, float stepsx, int* x, float* stepsToNextX, int toNextBlockY, float stepsy, int* y, float* stepsToNextY, int toNextBlockZ, float stepsz, int* z, float* stepsToNextZ) const
      {
        if(*stepsToNextX < *stepsToNextZ && *stepsToNextX < *stepsToNextY)
        {
          next(toNextBlockX, stepsx, x, stepsToNextX);
        }
        else if(*stepsToNextY < *stepsToNextZ)
        {
          next(toNextBlockY, stepsy, y, stepsToNextY);
        }
        else
        {
          next(toNextBlockZ, stepsz, z, stepsToNextZ);
        }
      }

      void RayCaster::next()
      {
        count++;
        if(useX)
        {
          if(useY)
          {
            if(useZ)
            {
              next(toNextBlock.x, steps.getX(), &blockPosition.x, &stepsToNext.getX(), toNextBlock.y, steps.getY(), &blockPosition.y, &stepsToNext.getY(), toNextBlock.z, steps.getZ(), &blockPosition.z, &stepsToNext.getZ());
            }
            else
            {
              next(toNextBlock.x, steps.getX(), &blockPosition.x, &stepsToNext.getX(), toNextBlock.y, steps.getY(), &blockPosition.y, &stepsToNext.getY());
            }
          }
          else if(useZ)
          {
            next(toNextBlock.x, steps.getX(), &blockPosition.x, &stepsToNext.getX(), toNextBlock.z, steps.getZ(), &blockPosition.z, &stepsToNext.getZ());
          }
          else
          {
            next(toNextBlock.x, steps.getX(), &blockPosition.x, &stepsToNext.getX());
          }
        }
        else if(useY)
        {
          if(useZ)
          {
            next(toNextBlock.y, steps.getY(), &blockPosition.y, &stepsToNext.getY(), toNextBlock.z, steps.getZ(), &blockPosition.z, &stepsToNext.getZ());
          }
          else
          {
            next(toNextBlock.y, steps.getY(), &blockPosition.y, &stepsToNext.getY());
          }
        }
        else
        {
          next(toNextBlock.z, steps.getZ(), &blockPosition.z, &stepsToNext.getZ());
        }
      }

      const gdm::Vector3i& RayCaster::getPosition() const
      {
        return blockPosition;
      }

      unsigned int RayCaster::getIterrations() const
      {
        return count;
      }
    }
  }
}
