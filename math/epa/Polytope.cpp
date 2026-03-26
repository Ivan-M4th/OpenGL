#include "Polytope.h"

#include "HalfEdge.h"

#include <cassert>

namespace gt
{
  namespace doubovik
  {
    namespace math
    {
      namespace epa
      {
        Polytope::Polytope(const gdmg::SupportVertex& v1, const gdmg::SupportVertex& v2, const gdmg::SupportVertex& v3, const gdmg::SupportVertex& v4)
        {
          vertices.add(v1);
          vertices.add(v2);
          vertices.add(v3);
          vertices.add(v4);

          //face 0
          HalfEdge f0e0(0,1,1);
          HalfEdge f0e1(2,3,1);
          HalfEdge f0e2(1,2,1);
          Face f0(f0e0, f0e1, f0e2);

          //face 1 / 3
          HalfEdge f1e0(0,3,2);
          HalfEdge f1e1(1,0,0); //ok
          HalfEdge f1e2(3,2,0);
          Face f1(f1e0, f1e1, f1e2);

          //face 2 / 6
          HalfEdge f2e0(1,1,2);
          HalfEdge f2e1(2,0,2);
          HalfEdge f2e2(3,3,0);
          Face f2(f2e0, f2e1, f2e2);

          //face 3 / 9
          HalfEdge f3e0(2,2,2);
          HalfEdge f3e1(0,0,1);
          HalfEdge f3e2(3,1,0);
          Face f3(f3e0, f3e1, f3e2);

          faces.add(f0);
          faces.add(f1);
          faces.add(f2);
          faces.add(f3);
        }

        Vector3 Polytope::getNormal(unsigned int faceIndex) const
        {
          Vector3 OA = vertices[faces[faceIndex].edges->positionIndex].getMDifference();
          Vector3 OB = vertices[(faces[faceIndex].edges + 1)->positionIndex].getMDifference();
          Vector3 OC = vertices[(faces[faceIndex].edges + 2)->positionIndex].getMDifference();

          Vector3 AB = OB - OA;
          Vector3 AC = OC - OA;
          return AB.cross(AC);
        }

        Vector3 Polytope::getFacePoint(unsigned int faceIndex) const
        {
          return vertices[faces[faceIndex].edges->positionIndex].getMDifference();
        }

        gdmg::SupportVertex Polytope::getFaceOriginProjection(unsigned int faceIndex) const
        {
          Vector3 OA = vertices[faces[faceIndex].edges->positionIndex].getMDifference();
          Vector3 OB = vertices[(faces[faceIndex].edges + 1)->positionIndex].getMDifference();
          Vector3 OC = vertices[(faces[faceIndex].edges + 2)->positionIndex].getMDifference();

          Vector3 AB = OB - OA;
          Vector3 AC = OC - OA;
          Vector3 AO = -OA;

          float ABAB = AB.dot(AB);
          float ABAC = AB.dot(AC);
          float ABAO = AB.dot(AO);

          float ACAC = AC.dot(AC);
          float ACAO = AC.dot(AO);

          float denom = ABAB*ACAC - ABAC*ABAC;
          if(denom == 0.0)
          {
            return vertices[faces[faceIndex].edges->positionIndex];
          }

          float v = (ABAO*ACAC - ACAO*ABAC)/denom;
          float w = (ABAB*ACAO - ABAC*ABAO)/denom;

          float u = 1.0 - v - w;
          return u*vertices[faces[faceIndex].edges->positionIndex] + v*vertices[(faces[faceIndex].edges + 1)->positionIndex] + w*vertices[(faces[faceIndex].edges + 2)->positionIndex];
        }

        unsigned int Polytope::getNextEdge(unsigned int index) const
        {
          index++;
          return index%3;
        }

        unsigned int Polytope::getPreviousEdge(unsigned int index) const
        {
          if(index <= 0)
          {
            return 2;
          }
          index--;
          return index;
        }

        unsigned int Polytope::getFirstUsedFaceId() const
        {
          unsigned int index = 0;
          while(index < faces.size() && faces[index].flag == 0)
          {
            index++;
          }
          assert(index < faces.size());
          return index;
        }

        bool Polytope::isVisibleFrom(unsigned int faceIndex, const Vector3& position) const
        {
          Vector3 facePosition = vertices[faces[faceIndex].edges->positionIndex].getMDifference();
          Vector3 normal = getNormal(faceIndex);
          return normal.dot(position - facePosition) > 0.0;
        }

        void Polytope::getClosestFaceId(unsigned int* faceIndex, float* distance, Vector3* normal) const
        {
          *faceIndex = getFirstUsedFaceId();
          *normal = getNormal(*faceIndex);
          normal->normalize();

          unsigned int vertexIndex = faces[*faceIndex].edges->positionIndex;
          Vector3 position = vertices[vertexIndex].getMDifference();

          *distance = position.dot(*normal);
          //std::cout << "distance: " << *distance << std::endl;

          for(unsigned int i= *faceIndex + 1;i<faces.size();i++)
          {
            if(faces[i].flag != 0)
            {
              vertexIndex = faces[i].edges->positionIndex;
              position = vertices[vertexIndex].getMDifference();

              Vector3 testNormal = getNormal(i);
              testNormal.normalize();

              float testDistance = position.dot(testNormal);
              //std::cout << "distance: " << testDistance << std::endl;

              if(testDistance < *distance)
              {
                *faceIndex = i;
                *distance = testDistance;
                *normal = testNormal;
              }
            }
          }
        }

        void Polytope::removeFace(unsigned int faceIndex)
        {
          faces[faceIndex].flag = 0;
          freeFaces.add(faceIndex);
        }

        unsigned int Polytope::getNewFaceIndex()
        {
          if(freeFaces.size() > 0)
          {
            unsigned int index = freeFaces.getFirst();
            freeFaces.removeFirst();
            return index;
          }
          else
          {
            unsigned int index = faces.size();
            faces.setSize(faces.size() + 1);
            return index;
          }
        }

        gdu::LinkedList<Vector2ui> Polytope::getSilhouette(const Vector3& position, unsigned int faceIndex, unsigned int edgeIndex)
        {
          if(faces[faceIndex].flag != 0)
          {
            if(isVisibleFrom(faceIndex, position))
            {
              Face& face = faces[faceIndex];
              //remove face
              removeFace(faceIndex);

              unsigned int edge2Index = getNextEdge(edgeIndex);
              unsigned int edge3Index = getNextEdge(edge2Index);
              gdu::LinkedList<Vector2ui> list1 = getSilhouette(position, (face.edges + edge2Index)->oppFaceIndex, (face.edges + edge2Index)->oppIndex);
              gdu::LinkedList<Vector2ui> list2 = getSilhouette(position, (face.edges + edge3Index)->oppFaceIndex, (face.edges + edge3Index)->oppIndex);
              list1.concatenate(list2);
              return list1;
            }
            else
            {
              gdu::LinkedList<Vector2ui> list;
              list.add(Vector2ui(faceIndex, edgeIndex));
              return list;
            }
          }
          return gdu::LinkedList<Vector2ui>();
        }

        unsigned int Polytope::addFace(const Face& face)
        {
          unsigned int index = getNewFaceIndex();
          faces[index] = face;
          return index;
        }

        void Polytope::linkEdges(unsigned int face1Index, unsigned int edge1Index, unsigned int face2Index, unsigned int edge2Index)
        {
          HalfEdge& edge1 = *(faces[face1Index].edges + edge1Index);
          HalfEdge& edge2 = *(faces[face2Index].edges + edge2Index);

          edge1.oppFaceIndex = face2Index;
          edge1.oppIndex = edge2Index;

          edge2.oppFaceIndex = face1Index;
          edge2.oppIndex = edge1Index;
        }

        unsigned int Polytope::createConeFace(unsigned int sfaceIndex, unsigned int sedgeIndex, unsigned int vertex3Index)
        {
          unsigned int sedgeIndex2 = getPreviousEdge(sedgeIndex);
          unsigned int vertex1Index = (faces[sfaceIndex].edges + sedgeIndex)->positionIndex;
          unsigned int vertex2Index = (faces[sfaceIndex].edges + sedgeIndex2)->positionIndex;
          HalfEdge edge1(vertex1Index, 0, 0);
          HalfEdge edge2(vertex2Index, 0, 0);
          HalfEdge edge3(vertex3Index, 0, 0);
          Face face(edge1, edge2, edge3);
          unsigned int faceIndex = addFace(face);
          linkEdges(faceIndex, 1, sfaceIndex, sedgeIndex);

          //std::cout << "added cone face from " << vertex1Index << " to " << vertex2Index << std::endl;
          return faceIndex;
        }

        void Polytope::createCone(unsigned int vertexIndex, gdu::LinkedList<Vector2ui>& silhouette)
        {
          unsigned int firstFaceIndex = createConeFace(silhouette.getFirst().x, silhouette.getFirst().y, vertexIndex);
          unsigned int previousFaceIndex = firstFaceIndex;

          silhouette.removeFirst();
          while(silhouette.size() > 0)
          {
            unsigned int faceIndex = createConeFace(silhouette.getFirst().x, silhouette.getFirst().y, vertexIndex);
            linkEdges(faceIndex, 0, previousFaceIndex, 2);

            previousFaceIndex = faceIndex;
            silhouette.removeFirst();
          }

          linkEdges(firstFaceIndex, 0, previousFaceIndex, 2);
        }

        void Polytope::addVertex(const gdmg::SupportVertex& v, unsigned int visibleFaceIndex)
        {
          Vector3 position = v.getMDifference();

          Face& face = faces[visibleFaceIndex];
          //remove face
          removeFace(visibleFaceIndex);

          gdu::LinkedList<Vector2ui> silhouette;
          for(unsigned int i=0;i<3;i++)
          {
            gdu::LinkedList<Vector2ui> list = getSilhouette(position, (face.edges + i)->oppFaceIndex, (face.edges + i)->oppIndex);
            silhouette.concatenate(list);
          }

          unsigned int vertexIndex = vertices.size();
          vertices.add(v);

          createCone(vertexIndex, silhouette);
        }
      }
    }
  }
}
