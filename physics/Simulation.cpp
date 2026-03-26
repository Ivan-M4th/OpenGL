#include "Simulation.h"

#include <cmath>

#include "../math/geometry/AABB.h"
#include "../math/geometry/CollisionCalculator.h"

namespace gt
{
  namespace doubovik
  {
    namespace physics
    {
      Simulation::Simulation(gdu::MemoryArray<ObjectSimulationData>* objects, gdu::MemoryArray<gdmd::Tree>* trees, gdu::MemoryArray<gdmg::AABB>* aabbs, GridSpacePartition* terrainGrid, GridSpacePartition* objectsGrid)
      {
        this->objects = objects;
        this->trees = trees;
        this->aabbs = aabbs;
        this->terrainGrid = terrainGrid;
        this->objectsGrid = objectsGrid;
      }

      Simulation::Simulation(const Simulation& simulation)
      {
        objects = simulation.objects;
        trees = simulation.trees;
        aabbs = simulation.aabbs;
      }

      Simulation& Simulation::operator=(const Simulation& simulation)
      {
        objects = simulation.objects;
        trees = simulation.trees;
        aabbs = simulation.aabbs;
        return *this;
      }

      int Simulation::getMainTreeId() const
      {
        return 0;
      }

      void Simulation::createAABB(int objectId, const gdm::Vector3& space)
      {
        ObjectSimulationData* objectSimulationData = &(*objects)[objectId];
        Object* object = objectSimulationData->object;
        int aabbId = objectSimulationData->aabbId;


        const gdm::Matrix4x4* transformation = &object->transformation.toMatrix4x4();
        const gdm::Matrix4x4* iLinearTransformation = &object->transformation.getILinearTransformation();
        gdmg::AABB aabb = object->collider->getAABB(transformation, iLinearTransformation);

        aabb.minPos = aabb.minPos - space;
        aabb.maxPos = aabb.maxPos + space;

        (*aabbs)[aabbId] = aabb;
      }

      bool Simulation::updateAABB(int objectId, const gdm::Vector3& space)
      {
        Object* object = (*objects)[objectId].object;
        int aabbId = (*objects)[objectId].aabbId;
        gdmg::AABB* currentAABB = &(*aabbs)[aabbId];

        const gdm::Matrix4x4* transformation = &object->transformation.toMatrix4x4();
        const gdm::Matrix4x4* iLinearTransformation = &object->transformation.getILinearTransformation();
        gdmg::AABB aabb = object->collider->getAABB(transformation, iLinearTransformation);

        if(currentAABB->minPos.getX() <= aabb.minPos.getX() && currentAABB->maxPos.getX() >= aabb.maxPos.getX())
        {
          if(currentAABB->minPos.getY() <= aabb.minPos.getY() && currentAABB->maxPos.getY() >= aabb.maxPos.getY())
          {
            if(currentAABB->minPos.getZ() <= aabb.minPos.getZ() && currentAABB->maxPos.getZ() >= aabb.maxPos.getZ())
            {
              return false;
            }
          }
        }

        aabb.minPos = aabb.minPos - space;
        aabb.maxPos = aabb.maxPos + space;

        (*aabbs)[aabbId] = aabb;

        return true;
      }

      void Simulation::addToObjectsGrid(int objectId)
      {
        ObjectSimulationData* objectSimulationData = &(*objects)[objectId];
        int aabbId = objectSimulationData->aabbId;
        objectsGrid->add(objectId, aabbId, &objectSimulationData->objectsGridDatas);
      }

      void Simulation::removeFromObjectGrid(int objectId)
      {
        ObjectSimulationData* objectSimulationData = &(*objects)[objectId];
        objectsGrid->remove(&objectSimulationData->objectsGridDatas);
      }

      void Simulation::add(int objectId) //ok
      {
        createAABB(objectId, gdm::Vector3(0.3,0.3,0.3));
        addToObjectsGrid(objectId);
      }

      void Simulation::addTerrain(int x, int y, int z, int objectId)
      {
        createAABB(objectId, gdm::Vector3());

        ObjectSimulationData* objectSimulationData = &(*objects)[objectId];
        int aabbId = objectSimulationData->aabbId;
        terrainGrid->add(x, y, z, objectId, aabbId, &objectSimulationData->terrainGridDatas);
      }

      void Simulation::addStructure(int objectId)
      {
        createAABB(objectId, gdm::Vector3());
        addToObjectsGrid(objectId);
      }

      void Simulation::remove(int objectId) //OK
      {
        //std::cout << "removing " << objectId << std::endl;
        ObjectSimulationData* objectSimulationData = &(*objects)[objectId];
        //std::cout << "removing from terrain grid" << std::endl;
        terrainGrid->remove(&objectSimulationData->terrainGridDatas);

        //std::cout << "removing from structures grid" << std::endl;
        objectsGrid->remove(&objectSimulationData->objectsGridDatas);

        //std::cout << "done removing" << std::endl;
      }

      void Simulation::updateObject(float timePassed, Object* object)
      {
        object->physicalInformation.onGround = false;
        object->transformation.position = object->transformation.position + timePassed*object->speed;
        object->transformation.rotation = gdm::Quaternion(object->getRotationSpeedAngle()*timePassed, object->getRotationDirection())*object->transformation.rotation;

        if(object->physicalInformation.useGravity)
        {
          object->speed = object->speed + timePassed*gdm::Vector3(0.0, -9.81, 0.0);
        }

        object->calculateInformation();

        object->update(timePassed);
      }

      void Simulation::updateObjects(float timePassed, gdu::LinkedHashList<int>* objectsToUpdate)
      {
        gdu::ConstLinkedHashListIterator<int> iterator(objectsToUpdate);
        while(iterator.isValid())
        {
          int objectId = iterator.value();
          updateObject(timePassed, (*objects)[objectId].object);

          if(updateAABB(objectId, gdm::Vector3(0.3, 0.3, 0.3)))
          {
            removeFromObjectGrid(objectId);
            addToObjectsGrid(objectId);
          }

          iterator.next();
        }
      }

      void Simulation::getObjectCollisions(int objectId, gdu::LinkedHashList<gdm::UIntPair>* collisions) const
      {
        int aabbId = (*objects)[objectId].aabbId;
        gdmg::AABB* aabb = &(*aabbs)[aabbId];

        terrainGrid->getCollisions(objectId, aabb, collisions); //collisions with terrain
        objectsGrid->getCollisions(objectId, aabb, collisions);
      }

      void Simulation::getObjectsCollisions(gdu::LinkedHashList<gdm::UIntPair>* collisions, gdu::LinkedHashList<int>* objectsToUpdate) const //OK
      {
        gdu::ConstLinkedHashListIterator<int> iterator(objectsToUpdate);
        while(iterator.isValid())
        {
          getObjectCollisions(iterator.value(), collisions);

          iterator.next();
        }
      }

      void Simulation::getCollisionResponseValues(Object* object1, Object* object2, const gdm::Vector3& normal, const gdm::Vector3& contact, gdm::Vector3* v1, gdm::Vector3* w1, gdm::Vector3* v2, gdm::Vector3* w2) const
      {
        float toRad = M_PI/180.0;
        float toDeg = 1.0/toRad;

        gdm::Vector3 r1 = contact - object1->transformation.position;
        gdm::Vector3 r2 = contact - object2->transformation.position;

        gdm::Vector3 vp1 = object1->speed + (toRad*object1->rotationSpeed).cross(r1);
        gdm::Vector3 vp2 = object2->speed + (toRad*object2->rotationSpeed).cross(r2);

        gdm::Vector3 vr = vp2 - vp1;

        float a = -2.0*vr.dot(normal);

        gdm::Vector3 r1n = r1.cross(normal);
        gdm::Vector3 i1r1n = object1->physicalInformation.getIInertiaMatrix()*r1n;
        gdm::Vector3 t1 = i1r1n.cross(r1);

        gdm::Vector3 r2n = r2.cross(normal);
        gdm::Vector3 i2r2n = object2->physicalInformation.getIInertiaMatrix()*r2n;
        gdm::Vector3 t2 = i2r2n.cross(r2);

        float m1 = object1->physicalInformation.mass;
        float m2 = object2->physicalInformation.mass;

        float j = a/((1.0/m1) + (1.0/m2) + (t1 + t2).dot(normal));

        *v1 = object1->speed - (j/m1)*normal;
        *v2 = object2->speed + (j/m2)*normal;

        *w1 = object1->rotationSpeed - toDeg*j*i1r1n;
        *w2 = object2->rotationSpeed + toDeg*j*i2r2n;
      }

      void Simulation::getStaticCollisionResponseValues(bool isFirst, Object* object, const gdm::Vector3& normal, const gdm::Vector3& contact, gdm::Vector3* v, gdm::Vector3* w) const
      {
        float toRad = M_PI/180.0;
        float toDeg = 1.0/toRad;

        gdm::Vector3 r = contact - object->transformation.position;

        gdm::Vector3 vp = object->speed + (toRad*object->rotationSpeed).cross(r);

        gdm::Vector3 vr = vp;
        if(isFirst)
        {
          vr = -vr;
        }

        float a = -1.02*vr.dot(normal);

        gdm::Vector3 rn = r.cross(normal);
        gdm::Vector3 irn = object->physicalInformation.getIInertiaMatrix()*rn;
        gdm::Vector3 t = irn.cross(r);

        float m = object->physicalInformation.mass;

        float j = a/((1.0/m) + t.dot(normal));

        if(isFirst)
        {
          *v = object->speed - (j/m)*normal;
          *w = object->rotationSpeed - toDeg*j*irn;
        }
        else
        {
          *v = object->speed + (j/m)*normal;
          *w = object->rotationSpeed + toDeg*j*irn;
        }
      }

      void Simulation::checkCollision(Object* object1, Object* object2)
      {
        gdmg::CollisionCalculator collisionCalculator(&object1->transformation.toMatrix4x4(), &object1->transformation.getILinearTransformation(), &object2->transformation.toMatrix4x4(), &object2->transformation.getILinearTransformation());
        bool collision;
        float penetration;
        gdm::Vector3 normal;
        gdm::Vector3 contact;

        collisionCalculator.checkCollision(*object1->collider, *object2->collider, &collision, &penetration, &normal, &contact);
        normal.normalize();

        if(collision)
        {
          //std::cout << "GJK collision: " << object1Index << " / " << object2Index << std::endl;

          float toAdd1 = 0.0;
          float toAdd2 = 0.0;
          float m1 = object1->physicalInformation.mass;
          float m2 = object2->physicalInformation.mass;

          if(normal.dot(gdm::Vector3(0.0, 1.0, 0.0)) > 0.5)
          {
            object2->physicalInformation.onGround = true;
          }
          if(normal.dot(gdm::Vector3(0.0, -1.0, 0.0)) > 0.5)
          {
            object1->physicalInformation.onGround = true;
          }

          if(object1->physicalInformation.moveable && object2->physicalInformation.moveable)
          {
            toAdd1 = penetration*(m2/(m1 + m2));
            toAdd2 = penetration*(m1/(m1 + m2));
          }
          else if(object1->physicalInformation.moveable)
          {
            toAdd1 = penetration;
          }
          else if(object2->physicalInformation.moveable)
          {
            toAdd2 = penetration;
          }

          object1->transformation.position = object1->transformation.position - toAdd1*normal;
          object2->transformation.position = object2->transformation.position + toAdd2*normal;

          object1->calculateInformation();
          object2->calculateInformation();



          if(object1->physicalInformation.moveable && object2->physicalInformation.moveable)
          {
            gdm::Vector3 v1;
            gdm::Vector3 w1;
            gdm::Vector3 v2;
            gdm::Vector3 w2;
            getCollisionResponseValues(object1, object2, normal, contact, &v1, &w1, &v2, &w2);

            if(object1->physicalInformation.objectType == FREE_OBJECT)
            {
              object1->speed = v1;
              object1->rotationSpeed = w1;
            }
            else
            {
              object1->speed = object1->speed - object1->speed.dot(normal)*normal;
            }

            if(object2->physicalInformation.objectType == FREE_OBJECT)
            {
              object2->speed = v2;
              object2->rotationSpeed = w2;
            }
            else
            {
              object2->speed = object2->speed - object2->speed.dot(normal)*normal;
            }
          }
          else if(object1->physicalInformation.moveable)
          {
            gdm::Vector3 v;
            gdm::Vector3 w;
            getStaticCollisionResponseValues(true, object1, normal, contact, &v, &w);
            if(object1->physicalInformation.objectType == FREE_OBJECT)
            {
              object1->speed = v;
              object1->rotationSpeed = w;
            }
            else
            {
              object1->speed = object1->speed - object1->speed.dot(normal)*normal;
            }
          }
          else if(object2->physicalInformation.moveable)
          {
            gdm::Vector3 v;
            gdm::Vector3 w;
            getStaticCollisionResponseValues(false, object2, normal, contact, &v, &w);
            if(object2->physicalInformation.objectType == FREE_OBJECT)
            {
              object2->speed = v;
              object2->rotationSpeed = w;
            }
            else
            {
              object2->speed = object2->speed - object2->speed.dot(normal)*normal;
            }
          }
        }
      }

      void Simulation::resolveObjectCollisions(const gdu::LinkedHashList<gdm::UIntPair>* collisions)
      {
        gdu::ConstLinkedHashListIterator<gdm::UIntPair> iterator(collisions);
        while(iterator.isValid())
        {
          //std::cout << "collisision: " << iterator.getKey() << std::endl;

          Object* object1 = (*objects)[iterator.value().id1].object;
          Object* object2 = (*objects)[iterator.value().id2].object;

          checkCollision(object1, object2);
          iterator.next();
        }
      }

      void Simulation::update(float timePassed, gdu::LinkedHashList<int>* objectsToUpdate)
      {
        std::cout << "---------------[SIMULATION STATUS]---------------" << std::endl;
        //std::cout << "static objects:" << std::endl;
        //std::cout << staticObjects << std::endl;
        std::cout << "objects to update:" << std::endl;
        std::cout << *objectsToUpdate << std::endl;
        std::cout << "-------------------------------------------------" << std::endl;

        updateObjects(timePassed, objectsToUpdate);

        gdu::LinkedHashList<gdm::UIntPair> objectCollisions;
        getObjectsCollisions(&objectCollisions, objectsToUpdate);

        std::cout << "---------------[DBVT STATUS]---------------" << std::endl;
        std::cout << "object collisions:" << std::endl;
        std::cout << objectCollisions << std::endl;
        std::cout << "-------------------------------------------" << std::endl;

        resolveObjectCollisions(&objectCollisions);
      }
    }
  }
}
