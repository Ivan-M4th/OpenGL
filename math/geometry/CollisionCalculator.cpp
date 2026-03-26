#include "CollisionCalculator.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace geometry
      {
        CollisionCalculator::CollisionCalculator(const Matrix4x4* transformation1, const Matrix4x4* iTransformation1, const Matrix4x4* transformation2, const Matrix4x4* iTransformation2)
        {
          supportCalculator = SupportVertexCalculator(transformation1, iTransformation1, transformation2, iTransformation2);
          speed1 = NULL;
          speed2 = NULL;
        }

        CollisionCalculator::CollisionCalculator(const Matrix4x4* transformation1, const Matrix4x4* iTransformation1, const Matrix4x4* transformation2, const Matrix4x4* iTransformation2, const Vector3* speed1, const Vector3* speed2)
        {
          supportCalculator = SupportVertexCalculator(transformation1, iTransformation1, transformation2, iTransformation2);
          this->speed1 = speed1;
          this->speed2 = speed2;
        }

        CollisionCalculator::CollisionCalculator(const CollisionCalculator& calculator)
        {
          supportCalculator = calculator.supportCalculator;
          speed1 = calculator.speed1;
          speed2 = calculator.speed2;
        }

        CollisionCalculator& CollisionCalculator::operator=(const CollisionCalculator& calculator)
        {
          supportCalculator = calculator.supportCalculator;
          speed1 = calculator.speed1;
          speed2 = calculator.speed2;
          return *this;
        }

        void CollisionCalculator::setCalculatorRadius(float radius1, float radius2)
        {
          supportCalculator.radius1 = radius1;
          supportCalculator.radius2 = radius2;
        }

        void CollisionCalculator::runGJK(const Vector3* location, const ConvexPolyhedron& poly1, const ConvexPolyhedron& poly2, Simplex* simplex, float* distance) const
        {
          SupportVertex v = supportCalculator.support(Vector3(1.0,0.0,0.0), poly1, poly2);

          *simplex = Simplex(location);
          Vector3 vmd = v.getMDifference() - *location;
          SupportVertex w = supportCalculator.support(-vmd, poly1, poly2);
          Vector3 wmd = w.getMDifference() - *location;

          unsigned int iterations = 0;
          while(vmd.dot(vmd) - vmd.dot(wmd) > 0.0000001)
          {
            //std::cout << "iteration: " << iterations << ", value: " << vmd.dot(vmd) - vmd.dot(wmd) << std::endl;
            //std::cout << "Simplex size: " << simplex->getSize() << std::endl;

            if(!simplex->contains(w))
            {
              simplex->add(w);
            }
            else
            {
              //std::cout << "float presision error, exiting early, iterations: " << iterations << std::endl;
              *distance = vmd.getLength();
              return;
            }

            if(simplex->getSize() >= 4)
            {
              //std::cout << "simplex 4 created, iterations: " << iterations << std::endl;
              *distance = 0.0;
              return;
            }

            SupportVertex newV;
            bool dbz;
            simplex->getClosestPosition(&newV, &dbz);
            if(dbz)
            {
              //std::cout << "GJK: dbz, value: " << vmd.getLength() << std::endl;
              *distance = vmd.getLength();
              return;
            }

            v = newV;
            vmd = v.getMDifference() - *location;
            w = supportCalculator.support(-vmd, poly1, poly2);
            wmd = w.getMDifference() - *location;
            //std::cout << "vmd:" << std::endl;
            //vmd.print();

            iterations++;
            if(iterations > 50)
            {
              //std::cout << "GJK "<< iterations << " iterations: " << vmd.dot(vmd) - vmd.dot(wmd) << ", value: " << vmd.getLength() << std::endl;
              *distance = vmd.getLength();
              return;
            }
          }

          //std::cout << "final GJK "<< iterations << " iterations: " << vmd.dot(vmd) - vmd.dot(wmd) << ", value: " << vmd.getLength() << std::endl;
          *distance = vmd.getLength();
        }

        void CollisionCalculator::fillLine(const ConvexPolyhedron& poly1, const ConvexPolyhedron& poly2, Simplex* simplex, bool* collision) const
        {
          Vector3 OA = (*simplex)[0].getMDifference();
          Vector3 OB = (*simplex)[1].getMDifference();

          Vector3 AB = OB - OA;
          Vector3 v1(0.0, 0.0, 0.0);
          if(AB.getX() < AB.getY() && AB.getX() < AB.getZ())
          {
            v1.getX() = 1.0;
          }
          else if(AB.getY() < AB.getZ())
          {
            v1.getY() = 1.0;
          }
          else
          {
            v1.getZ() = 1.0;
          }

          Vector3 v2 = v1.cross(AB);
          v1 = v2.cross(AB);
          SupportVertex sv1 = supportCalculator.support(v1, poly1, poly2);
          SupportVertex sv2 = supportCalculator.support(v2, poly1, poly2);

          simplex->forceAdd(sv1);
          simplex->forceAdd(sv2);

          Vector3 OC = sv1.getMDifference();
          Vector3 OD = sv2.getMDifference();

          if(OC.dot(v1) - OA.dot(v1) > 0.00001)
          {
            if(OD.dot(v2) - OA.dot(v2) > 0.00001)
            {
              *collision = true;
            }
          }
          *collision = false;
        }

        void CollisionCalculator::fillTriangle(const ConvexPolyhedron& poly1, const ConvexPolyhedron& poly2, Simplex* simplex, bool* collision) const
        {
          Vector3 OA = (*simplex)[0].getMDifference();
          Vector3 OB = (*simplex)[1].getMDifference();
          Vector3 OC = (*simplex)[2].getMDifference();

          Vector3 AB = OB - OA;
          Vector3 AC = OC - OA;

          Vector3 v = AB.cross(AC);

          SupportVertex sv = supportCalculator.support(v, poly1, poly2);
          simplex->forceAdd(sv);

          Vector3 OD = sv.getMDifference();
          if(OD.dot(v) - OA.dot(v) > 0.00001)
          {
            *collision = true;
          }
          *collision = false;
        }

        void CollisionCalculator::fillSimplex(const ConvexPolyhedron& poly1, const ConvexPolyhedron& poly2, Simplex* simplex, bool* collision) const
        {
          if(simplex->getSize() == 2)
          {
            fillLine(poly1, poly2, simplex, collision);
          }
          else if(simplex->getSize() == 3)
          {
            fillTriangle(poly1, poly2, simplex, collision);
          }
        }

        void CollisionCalculator::getCollisionInformation(const ConvexPolyhedron& poly1, const ConvexPolyhedron& poly2, const Simplex& simplex, float* penetration, Vector3* normal, Vector3* contact) const
        {
          gdme::Polytope polytope(simplex[0], simplex[1], simplex[2], simplex[3]);

          unsigned int faceIndex;
          polytope.getClosestFaceId(&faceIndex, penetration, normal);
          SupportVertex sv = supportCalculator.support(*normal, poly1, poly2);

          unsigned int iterations = 0;
          while(normal->dot(sv.getMDifference() - polytope.getFacePoint(faceIndex)) > 0.000001)
          {
            //std::cout << "EPA iteration: " << iterations << " value: " << normal.dot(sv.getMDifference() - polytope.getFacePoint(faceIndex)) << std::endl;

            polytope.addVertex(sv, faceIndex);

            polytope.getClosestFaceId(&faceIndex, penetration, normal);
            sv = supportCalculator.support(*normal, poly1, poly2);

            iterations++;
            if(iterations > 100)
            {
              //std::cout << "EPA diverging! value: " << *penetration << std::endl;
              SupportVertex contactv = polytope.getFaceOriginProjection(faceIndex);
              *contact = 0.5*(contactv.position1 + contactv.position2);
              break;
            }
          }

          //std::cout << "EPA iterations: " << iterations << " final value: " << normal->dot(sv.getMDifference() - polytope.getFacePoint(faceIndex)) << std::endl;
          //std::cout << "penetration distance: " << *penetration << std::endl;
          //std::cout << "contact: " << std::endl;
          SupportVertex contactv = polytope.getFaceOriginProjection(faceIndex);
          //contactv.position1.print();
          //contactv.position2.print();
          *contact = 0.5*(contactv.position1 + contactv.position2);
        }

        void CollisionCalculator::checkCollision(const ConvexPolyhedron& poly1, const ConvexPolyhedron& poly2, bool* collision, float* penetration, Vector3* normal, Vector3* contact)
        {
          Vector3 location(0.0, 0.0, 0.0);
          Simplex simplex(&location);
          float distance;
          runGJK(&location, poly1, poly2, &simplex, &distance);

          //std::cout << "gjk distance: " << distance << std::endl;
          //std::cout << "final simplex size: " << simplex.getSize() << std::endl;

          if(simplex.getSize() == 4)
          {
            //yes
            *collision = true;
          }
          else if(distance == 0.0 && simplex.getSize() > 1)
          {
            fillSimplex(poly1, poly2, &simplex, collision);
          }
          else
          {
            //no
            *collision = false;
          }

          if(*collision)
          {
            getCollisionInformation(poly1, poly2, simplex, penetration, normal, contact);
          }
        }

        void CollisionCalculator::checkGJKRayCastCollision(const ConvexPolyhedron& poly1, const ConvexPolyhedron& poly2, float maxLambda, bool* collision, float* lambda, Vector3* normal) const
        {
          assert(speed1 != NULL && speed2 != NULL);
          *lambda = 0.0;
          Vector3 location(0.0, 0.0, 0.0);
          *normal = Vector3(0.0,0.0,0.0);
          SupportVertex sv = supportCalculator.support(Vector3(1.0,0.0,0.0), poly1, poly2);
          Vector3 v = location - sv.getMDifference();
          Simplex simplex(&location);
          Vector3 direction = *speed2 - *speed1;

          unsigned int iterations = 0;
          while(v.dot(v) > 0.000001)
          {
            SupportVertex p = supportCalculator.support(v, poly1, poly2);
            Vector3 w = location - p.getMDifference();

            float vw = v.dot(w);
            if(vw > 0.0)
            {
              float vr = v.dot(direction);
              if(vr >= 0.0)
              {
                //no collision
                *collision = false;
                *lambda = maxLambda;
                return;
              }
              else
              {
                *lambda = *lambda - (vw/vr);
                if(*lambda > maxLambda)
                {
                  //no collision
                  *collision = false;
                  *lambda = maxLambda;
                  return;
                }
                else
                {
                  location = (*lambda) * direction;
                  *normal = v;
                }
              }
            }

            if(!simplex.contains(p))
            {
              simplex.add(p);
            }

            SupportVertex newSv;
            bool dbz;
            simplex.getClosestPosition(&newSv, &dbz);
            if(dbz)
            {
              std::cout << "ERROR: division by zero!" << std::endl;
              *lambda = 0.0;
              *collision = true;
              return;
            }
            else
            {
              sv = newSv;
              v = location - sv.getMDifference();
            }

            iterations++;
            if(iterations > 100)
            {
              std::cout << "ERROR: no convergence, value = " << v.dot(v) << std::endl;
              *collision = true;
              return;
            }

          }

          *collision = true;
          return;
        }
      }
    }
  }
}
