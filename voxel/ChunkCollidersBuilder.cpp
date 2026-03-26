#include "ChunkCollidersBuilder.h"

#include "VoxelData.h"
#include "Materials.h"
#include "TerrainStructure.h"

#include "../math/Vector3.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      const unsigned int LIST_SIZE = CHUNK_SIZE*CHUNK_SIZE*CHUNK_SIZE;

      ChunkCollidersBuilder::ChunkCollidersBuilder(Chunk* chunk, int cx, int cy, int cz)
      {
        this->chunk = chunk;
        tested = new bool[LIST_SIZE];
        clearTestedBlocks();
        this->cx = cx;
        this->cy = cy;
        this->cz = cz;
      }

      ChunkCollidersBuilder::ChunkCollidersBuilder(const ChunkCollidersBuilder& builder)
      {
        chunk = builder.chunk;
        tested = new bool[LIST_SIZE];
        for(unsigned int i=0;i<LIST_SIZE;i++)
        {
          *(tested + i) = *(builder.tested + i);
        }
        cx = builder.cx;
        cy = builder.cy;
        cz = builder.cz;
      }

      ChunkCollidersBuilder& ChunkCollidersBuilder::operator=(const ChunkCollidersBuilder& builder)
      {
        deleteData();
        chunk = builder.chunk;
        tested = new bool[LIST_SIZE];
        for(unsigned int i=0;i<LIST_SIZE;i++)
        {
          *(tested + i) = *(builder.tested + i);
        }
        cx = builder.cx;
        cy = builder.cy;
        cz = builder.cz;
        return *this;
      }

      ChunkCollidersBuilder::~ChunkCollidersBuilder()
      {
        deleteData();
      }

      void ChunkCollidersBuilder::deleteData()
      {
        delete[] tested;
      }

      void ChunkCollidersBuilder::clearTestedBlocks()
      {
        for(unsigned int i=0;i<LIST_SIZE;i++)
        {
          *(tested + i) = false;
        }
      }

      bool& ChunkCollidersBuilder::getTested(unsigned int x, unsigned int y, unsigned int z) const
      {
        unsigned int index = (x*CHUNK_SIZE + y)*CHUNK_SIZE + z;
        assert(index < LIST_SIZE);
        return *(tested + index);
      }

      void ChunkCollidersBuilder::tryExpandX(unsigned int x, unsigned int y, unsigned int z, unsigned int sizeY, unsigned int sizeZ, bool* canExpand) const
      {
        if(x >= CHUNK_SIZE)
        {
          *canExpand = false;
          return;
        }

        for(unsigned int dy=0;dy<sizeY;dy++)
        {
          for(unsigned int dz=0;dz<sizeZ;dz++)
          {
            unsigned int by = y + dy;
            unsigned int bz = z + dz;

            if(getTested(x, by, bz) || !getMaterial(chunk->getBlock(x, by, bz)->getMaterialId())->isSolid())
            {
              *canExpand = false;
              return;
            }
          }
        }

        *canExpand = true;
        for(unsigned int dy=0;dy<sizeY;dy++)
        {
          for(unsigned int dz=0;dz<sizeZ;dz++)
          {
            unsigned int by = y + dy;
            unsigned int bz = z + dz;

            getTested(x, by, bz) = true;
          }
        }
      }

      void ChunkCollidersBuilder::tryExpandY(unsigned int x, unsigned int y, unsigned int z, unsigned int sizeX, unsigned int sizeZ, bool* canExpand) const
      {
        if(y >= CHUNK_SIZE)
        {
          *canExpand = false;
          return;
        }

        for(unsigned int dx=0;dx<sizeX;dx++)
        {
          for(unsigned int dz=0;dz<sizeZ;dz++)
          {
            unsigned int bx = x + dx;
            unsigned int bz = z + dz;

            if(getTested(bx, y, bz) || !getMaterial(chunk->getBlock(bx, y, bz)->getMaterialId())->isSolid())
            {
              *canExpand = false;
              return;
            }
          }
        }

        *canExpand = true;
        for(unsigned int dx=0;dx<sizeX;dx++)
        {
          for(unsigned int dz=0;dz<sizeZ;dz++)
          {
            unsigned int bx = x + dx;
            unsigned int bz = z + dz;

            getTested(bx, y, bz) = true;
          }
        }
      }

      void ChunkCollidersBuilder::tryExpandZ(unsigned int x, unsigned int y, unsigned int z, unsigned int sizeX, unsigned int sizeY, bool* canExpand) const
      {
        if(z >= CHUNK_SIZE)
        {
          *canExpand = false;
          return;
        }

        for(unsigned int dx=0;dx<sizeX;dx++)
        {
          for(unsigned int dy=0;dy<sizeY;dy++)
          {
            unsigned int bx = x + dx;
            unsigned int by = y + dy;

            if(getTested(bx, by, z) || !getMaterial(chunk->getBlock(bx, by, z)->getMaterialId())->isSolid())
            {
              *canExpand = false;
              return;
            }
          }
        }

        *canExpand = true;
        for(unsigned int dx=0;dx<sizeX;dx++)
        {
          for(unsigned int dy=0;dy<sizeY;dy++)
          {
            unsigned int bx = x + dx;
            unsigned int by = y + dy;

            getTested(bx, by, z) = true;
          }
        }
      }

      void ChunkCollidersBuilder::buildCollider(unsigned int x, unsigned int y, unsigned int z)
      {
        if(getTested(x, y, z) || !getMaterial(chunk->getBlock(x, y, z)->getMaterialId())->isSolid())
        {
          return;
        }

        unsigned int sizeX = 1;
        unsigned int sizeY = 1;
        unsigned int sizeZ = 1;
        bool canExpand;

        tryExpandX(x + sizeX, y, z, sizeY, sizeZ, &canExpand);
        while(canExpand)
        {
          sizeX++;
          tryExpandX(x + sizeX, y, z, sizeY, sizeZ, &canExpand);
        }

        tryExpandY(x, y + sizeY, z, sizeX, sizeZ, &canExpand);
        while(canExpand)
        {
          sizeY++;
          tryExpandY(x, y + sizeY, z, sizeX, sizeZ, &canExpand);
        }

        tryExpandZ(x, y, z + sizeZ, sizeX, sizeY, &canExpand);
        while(canExpand)
        {
          sizeZ++;
          tryExpandZ(x, y, z + sizeZ, sizeX, sizeY, &canExpand);
        }

        float xf = (float)(cx*(int)CHUNK_SIZE + (int)x);
        float sizeXf = (float)sizeX;

        float yf = (float)(cy*(int)CHUNK_SIZE + (int)y);
        float sizeYf = (float)sizeY;

        float zf = (float)(cz*(int)CHUNK_SIZE + (int)z);
        float sizeZf = (float)sizeZ;

        colliders.add(gdmg::ConvexPolyhedron(gdm::Vector3(xf, yf, zf), gdm::Vector3(sizeXf, sizeYf, sizeZf)));
      }

      void ChunkCollidersBuilder::buildColliders()
      {
        for(unsigned int x=0;x<CHUNK_SIZE;x++)
        {
          for(unsigned int y=0;y<CHUNK_SIZE;y++)
          {
            for(unsigned int z=0;z<CHUNK_SIZE;z++)
            {
              buildCollider(x, y, z);
            }
          }
        }

        std::cout << "coliders created: " << colliders.size() << std::endl;
      }

      void ChunkCollidersBuilder::loadColliders(ChunkCollider* collider) const
      {
        collider->size = colliders.size();

        if(collider->size > 0)
        {
          collider->structures = new TerrainStructure[collider->size];
          collider->simulationIds = new unsigned int[collider->size];
          for(int i=0;i<collider->size;i++)
          {
            *(collider->structures + i) = TerrainStructure(colliders[i]);
          }
        }
        else
        {
          collider->structures = NULL;
          collider->simulationIds = NULL;
        }
      }
    }
  }
}
