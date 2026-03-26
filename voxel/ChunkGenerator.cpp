#include "ChunkGenerator.h"

#include "Materials.h"
#include "VoxelData.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      ChunkGenerator::ChunkGenerator(gds::GameDataManager* gameDataManager) : random(435)
      {
        this->gameDataManager = gameDataManager;
      }

      ChunkGenerator::ChunkGenerator(const ChunkGenerator& generator) : random(generator.random)
      {
        gameDataManager = generator.gameDataManager;
      }

      ChunkGenerator& ChunkGenerator::operator=(const ChunkGenerator& generator)
      {
        random = generator.random;
        gameDataManager = generator.gameDataManager;
        return *this;
      }

      void ChunkGenerator::createTree(int x, int y, int z, gdsv::ChunkStructures* structures)
      {
        int objectId;
        gdso::Tree* tree;

        gameDataManager->createTree(&objectId, &tree);

        structures->trees.add(objectId);

        tree->transformation.position = gdm::Vector3((float)x + 0.5, (float)(y + 1), (float)z + 0.5);
        tree->calculateInformation();

        gdp::Simulation* simulation = gameDataManager->getSimulationDataManager()->getSimulation();
        simulation->addStructure(gameDataManager->getTreesManager()->getSimulationId(objectId));

        std::cout << "tree created!" << std::endl;
      }

      void ChunkGenerator::createBoar(int cx, int cy, int cz, int x, int y, int z, ArrayList<int>* boars)
      {
        int objectId;
        gdso::Boar* boar;

        gameDataManager->createBoar(&objectId, &boar);
        gameDataManager->getBoarsManager()->setChunkPosition(objectId, cx, cy, cz);

        boars->add(objectId);

        boar->transformation.position = gdm::Vector3((float)x + 0.5, (float)(y + 1), (float)z + 0.5);
        boar->calculateInformation();

        gdp::Simulation* simulation = gameDataManager->getSimulationDataManager()->getSimulation();
        simulation->add(gameDataManager->getBoarsManager()->getSimulationId(objectId));
        std::cout << "boar created!" << std::endl;
      }

      void ChunkGenerator::generateBlock(int cx, int cy, int cz, int x, int y, int z, Block* block, gdsv::ChunkStructures* structures, gdsv::ChunkCreatures* creatures)
      {
        float bx = (float)x;
        float bz = (float)z;
        bx/=50.0;
        bz/=50.0;

        float r = random.getInterpolatedNoise(bx, bz);
        //r+= 0.5*random.getInterpolatedNoise(2.0*bx, 2.0*bz);
        //r+= 0.25*random.getInterpolatedNoise(4.0*bx, 4.0*bz);
        int h = -80 + (int)((150.0)*r); //int h = -150 + (int)((150.0)*r);
        if(y == h)
        {
          float value = random.getRandomFloat(x, z);
          if(value < 0.01)
          {
            //block->setMaterial(WOOD_PLANKS);
            block->setMaterial(GRASS);
            createTree(x, y, z, structures);
          }
          else if(value < 0.0105)
          {
            block->setMaterial(WOOD_PLANKS);
            createBoar(cx, cy, cz, x, y, z, &creatures->boars);
          }
          else
          {
            block->setMaterial(GRASS);
          }
        }
        else if(y < h && y >= h - 10)
        {
          block->setMaterial(DIRT);
        }
        else if(y < h)
        {
          block->setMaterial(STONE);
        }
        else
        {
          block->setMaterial(AIR);
        }
      }

      void ChunkGenerator::generateChunk(int cx, int cy, int cz, Chunk* chunk, gdsv::ChunkStructures* structures, gdsv::ChunkCreatures* creatures)
      {
        int bcx = cx*CHUNK_SIZE;
        int bcy = cy*CHUNK_SIZE;
        int bcz = cz*CHUNK_SIZE;
        for(unsigned int x=0;x<CHUNK_SIZE;x++)
        {
          for(unsigned int y=0;y<CHUNK_SIZE;y++)
          {
            for(unsigned int z=0;z<CHUNK_SIZE;z++)
            {
              generateBlock(cx, cy, cz, x + bcx, y + bcy, z + bcz, chunk->getBlock(x, y, z), structures, creatures);
            }
          }
        }
      }
    }
  }
}
