#include "ServerTerrainSimulation.h"

#include "../math/geometry/AABB.h"
#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      ServerTerrainSimulation::ServerTerrainSimulation(Region* region, ArrayList<Pointer<gdp::Object>>* objects)
      {
        this->region = region;
        this->objects = objects;
      }

      ServerTerrainSimulation::ServerTerrainSimulation(const ServerTerrainSimulation& simulation)
      {
        region = simulation.region;
        objects = simulation.objects;
      }

      ServerTerrainSimulation& ServerTerrainSimulation::operator=(const ServerTerrainSimulation& simulation)
      {
        region = simulation.region;
        objects = simulation.objects;
        return *this;
      }

      void ServerTerrainSimulation::updateCollisions(gdp::Object* object) const
      {
        object->physicalInformation.onGround = false;
        gdmg::AABB box(object->transformation.position - gdm::Vector3(0.45,0.0,0.45), gdm::Vector3(0.9,1.9,0.9));
        //region->checkCollisions(&box);

        if(object->transformation.position.getY() < box.getPosition().getY())
        {
          object->physicalInformation.onGround = true;
          object->speed.getY() = 0.0;
        }

        object->transformation.position = box.getPosition() + gdm::Vector3(0.45,0.0,0.45);
      }

      void ServerTerrainSimulation::update(float timePassed)
      {
        for(unsigned int i=0;i<objects->size();i++)
        {
          updateCollisions((*objects)[i].value());
        }
      }
    }
  }
}
