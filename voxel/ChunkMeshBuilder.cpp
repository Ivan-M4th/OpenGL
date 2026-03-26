#include "ChunkMeshBuilder.h"

#include "Block.h"
#include "Materials.h"
#include "VoxelData.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      ChunkMeshBuilder::ChunkMeshBuilder(BlockBuilder* blockBuilder, Chunk* chunk, ChunkMesh* chunkMesh, int cx, int cy, int cz, Chunk* xm, Chunk* xp, Chunk* ym, Chunk* yp, Chunk* zm, Chunk* zp)
      {
        vertexAmount = 0;
        this->blockBuilder = blockBuilder;
        this->chunk = chunk;
        this->chunkMesh = chunkMesh;
        this->cx = cx;
        this->cy = cy;
        this->cz = cz;
        this->xm = xm;
        this->xp = xp;
        this->ym = ym;
        this->yp = yp;
        this->zm = zm;
        this->zp = zp;
      }

      ChunkMeshBuilder::ChunkMeshBuilder(const ChunkMeshBuilder& builder)
      {
        positions = builder.positions;
        uvs = builder.uvs;
        normals = builder.normals;
        indices = builder.indices;

        vertexAmount = builder.vertexAmount;
        blockBuilder = builder.blockBuilder;
        chunk = builder.chunk;
        chunkMesh = builder.chunkMesh;
        cx = builder.cx;
        cy = builder.cy;
        cz = builder.cz;
        xm = builder.xm;
        xp = builder.xp;
        ym = builder.ym;
        yp = builder.yp;
        zm = builder.zm;
        zp = builder.zp;
      }

      ChunkMeshBuilder& ChunkMeshBuilder::operator=(const ChunkMeshBuilder& builder)
      {
        positions = builder.positions;
        uvs = builder.uvs;
        normals = builder.normals;
        indices = builder.indices;

        vertexAmount = builder.vertexAmount;
        blockBuilder = builder.blockBuilder;
        chunk = builder.chunk;
        chunkMesh = builder.chunkMesh;
        cx = builder.cx;
        cy = builder.cy;
        cz = builder.cz;
        xm = builder.xm;
        xp = builder.xp;
        ym = builder.ym;
        yp = builder.yp;
        zm = builder.zm;
        zp = builder.zp;
        return *this;
      }

      Block* ChunkMeshBuilder::getTopBlock(unsigned int x, unsigned int y, unsigned int z) const
      {
        y++;
        if(y >= CHUNK_SIZE)
        {
          if(yp == NULL)
          {
            return NULL;
          }
          else
          {
            return yp->getBlock(x, 0, z);
          }
        }
        return chunk->getBlock(x, y, z);
      }

      Block* ChunkMeshBuilder::getBottomBlock(unsigned int x, unsigned int y, unsigned int z) const
      {
        if(y == 0)
        {
          if(ym == NULL)
          {
            return NULL;
          }
          else
          {
            return ym->getBlock(x, CHUNK_SIZE - 1, z);
          }
        }
        y--;
        return chunk->getBlock(x, y, z);
      }

      Block* ChunkMeshBuilder::getFrontBlock(unsigned int x, unsigned int y, unsigned int z) const
      {
        if(z == 0)
        {
          if(zm == NULL)
          {
            return NULL;
          }
          else
          {
            return zm->getBlock(x, y, CHUNK_SIZE - 1);
          }
        }
        z--;
        return chunk->getBlock(x, y, z);
      }

      Block* ChunkMeshBuilder::getBackBlock(unsigned int x, unsigned int y, unsigned int z) const
      {
        z++;
        if(z >= CHUNK_SIZE)
        {
          if(zp == NULL)
          {
            return NULL;
          }
          else
          {
            return zp->getBlock(x, y, 0);
          }
        }
        return chunk->getBlock(x, y, z);
      }

      Block* ChunkMeshBuilder::getRightBlock(unsigned int x, unsigned int y, unsigned int z) const
      {
        x++;
        if(x >= CHUNK_SIZE)
        {
          if(xp == NULL)
          {
            return NULL;
          }
          else
          {
            return xp->getBlock(0, y, z);
          }
        }
        return chunk->getBlock(x, y, z);
      }

      Block* ChunkMeshBuilder::getLeftBlock(unsigned int x, unsigned int y, unsigned int z) const
      {
        if(x == 0)
        {
          if(xm == NULL)
          {
            return NULL;
          }
          else
          {
            return xm->getBlock(CHUNK_SIZE - 1, y, z);
          }
        }
        x--;
        return chunk->getBlock(x, y, z);
      }

      bool ChunkMeshBuilder::isVisible(Block* block) const
      {
        if(block == NULL)
        {
          return true; //true
        }
        Material* material = getMaterial(block->getMaterialId());
        return material->isVisible();
      }

      void ChunkMeshBuilder::buildTopFace(unsigned int x, unsigned int y, unsigned int z, Material* material)
      {
        Block* block = getTopBlock(x, y, z);
        if(!isVisible(block))
        {
          blockBuilder->addTopFace(material->getTopTextureId(), &positions, &vertexAmount, &uvs, &normals, &indices);
        }
      }

      void ChunkMeshBuilder::buildBottomFace(unsigned int x, unsigned int y, unsigned int z, Material* material)
      {
        Block* block = getBottomBlock(x, y, z);
        if(!isVisible(block))
        {
          blockBuilder->addBottomFace(material->getBottomTextureId(), &positions, &vertexAmount, &uvs, &normals, &indices);
        }
      }

      void ChunkMeshBuilder::buildFrontFace(unsigned int x, unsigned int y, unsigned int z, Material* material)
      {
        Block* block = getFrontBlock(x, y, z);
        if(!isVisible(block))
        {
          blockBuilder->addFrontFace(material->getSideTextureId(), &positions, &vertexAmount, &uvs, &normals, &indices);
        }
      }

      void ChunkMeshBuilder::buildBackFace(unsigned int x, unsigned int y, unsigned int z, Material* material)
      {
        Block* block = getBackBlock(x, y, z);
        if(!isVisible(block))
        {
          blockBuilder->addBackFace(material->getSideTextureId(), &positions, &vertexAmount, &uvs, &normals, &indices);
        }
      }

      void ChunkMeshBuilder::buildRightFace(unsigned int x, unsigned int y, unsigned int z, Material* material)
      {
        Block* block = getRightBlock(x, y, z);
        if(!isVisible(block))
        {
          blockBuilder->addRightFace(material->getSideTextureId(), &positions, &vertexAmount, &uvs, &normals, &indices);
        }
      }

      void ChunkMeshBuilder::buildLeftFace(unsigned int x, unsigned int y, unsigned int z, Material* material)
      {
        Block* block = getLeftBlock(x, y, z);
        if(!isVisible(block))
        {
          blockBuilder->addLeftFace(material->getSideTextureId(), &positions, &vertexAmount, &uvs, &normals, &indices);
        }
      }

      void ChunkMeshBuilder::buildBlockMesh(unsigned int x, unsigned int y, unsigned int z)
      {
        Block* block = chunk->getBlock(x, y, z);
        Material* material = getMaterial(block->getMaterialId());
        if(!material->isVisible())
        {
          return;
        }
        blockBuilder->setPosition((float)cx + x, (float)cy + y, (float)cz + z);
        buildTopFace(x, y, z, material);
        buildBottomFace(x, y, z, material);
        buildFrontFace(x, y, z, material);
        buildBackFace(x, y, z, material);
        buildRightFace(x, y, z, material);
        buildLeftFace(x, y, z, material);
      }

      void ChunkMeshBuilder::calculateMesh()
      {
        for(unsigned int x=0;x<CHUNK_SIZE;x++)
        {
          for(unsigned int y=0;y<CHUNK_SIZE;y++)
          {
            for(unsigned int z=0;z<CHUNK_SIZE;z++)
            {
              buildBlockMesh(x, y, z);
            }
          }
        }
      }

      void ChunkMeshBuilder::loadData()
      {
        chunkMesh->loadData(positions, uvs, normals, indices);
      }

      void ChunkMeshBuilder::clear()
      {
        positions.clear();
        uvs.clear();
        normals.clear();
        indices.clear();
        vertexAmount = 0;
      }

      void ChunkMeshBuilder::buildMesh()
      {
        calculateMesh();
        loadData();
        clear();
      }
    }
  }
}
