#include "MeshReader.h"

#include "../math/Vector3.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      MeshReader::MeshReader()
      {
        file = NULL;
      }

      MeshReader::MeshReader(XMLNode* file)
      {
        this->file = file;
      }

      MeshReader::MeshReader(const MeshReader& reader)
      {
        file = reader.file;

        positionsSourceSource = reader.positionsSourceSource;
        positionsSource = reader.positionsSource;
        positionsOffset = reader.positionsOffset;

        uvsSource = reader.uvsSource;
        uvsOffset = reader.uvsOffset;

        normalsSource = reader.normalsSource;
        normalsOffset = reader.normalsOffset;

        triangles = reader.triangles;
        trianglesCount = reader.trianglesCount;

        positions = reader.positions;
        uvs = reader.uvs;
        normals = reader.normals;
      }

      MeshReader& MeshReader::operator=(const MeshReader& reader)
      {
        file = reader.file;

        positionsSourceSource = reader.positionsSourceSource;
        positionsSource = reader.positionsSource;
        positionsOffset = reader.positionsOffset;

        uvsSource = reader.uvsSource;
        uvsOffset = reader.uvsOffset;

        normalsSource = reader.normalsSource;
        normalsOffset = reader.normalsOffset;

        triangles = reader.triangles;
        trianglesCount = reader.trianglesCount;

        positions = reader.positions;
        uvs = reader.uvs;
        normals = reader.normals;

        return *this;
      }

      void MeshReader::read()
      {
        readMesh((*file)["COLLADA"]["library_geometries"]["geometry"]["mesh"]);
      }

      void MeshReader::loadMesh(gdg::Mesh* mesh) const
      {
        mesh->addVbo(0, 3, positions.getData(), positions.size());
        mesh->addVbo(1, 2, uvs.getData(), uvs.size());
        mesh->addVbo(2, 3, normals.getData(), normals.size());
        mesh->setVertexAmount(3*trianglesCount);
      }

      const ArrayList<unsigned int>& MeshReader::getTriangles() const
      {
        return triangles;
      }

      unsigned int MeshReader::getPositionsOffset() const
      {
        return positionsOffset;
      }

      unsigned int MeshReader::getTrianglesCount() const
      {
        return trianglesCount;
      }

      gdmg::ConvexPolyhedron MeshReader::getConvexShape() const
      {
        ArrayList<gdm::Vector3> shapePositions;
        for(unsigned int i=0;i<rawPositions.size();i+=3)
        {
          shapePositions.add(gdm::Vector3(rawPositions[i], rawPositions[i + 1], rawPositions[i + 2]));
        }

        return gdmg::ConvexPolyhedron(shapePositions);
      }

      void MeshReader::readMesh(const XMLNode& node)
      {
        readTriangles(node["triangles"]);
        readPositionsSource(node);
        std::cout << "positions Source: " << positionsSource << std::endl;
        std::cout << "uvs source: " << uvsSource << std::endl;
        std::cout << "normals source: " << normalsSource << std::endl;

        readSourceFloatArray(node, positionsSource, &rawPositions);

        ArrayList<float> rawUvs;
        readSourceFloatArray(node, uvsSource, &rawUvs);

        ArrayList<float> rawNormals;
        readSourceFloatArray(node, normalsSource, &rawNormals);

        std::cout << "triangles count: " << trianglesCount << std::endl;

        sortData(rawPositions, rawUvs, rawNormals);
      }

      void MeshReader::readTriangles(const XMLNode& node)
      {
        trianglesCount = node.getAttribute("count");
        triangles = node["p"].getData().toList<unsigned int>(" ");

        readSource(node, "VERTEX", &positionsSourceSource, &positionsOffset);
        readSource(node, "TEXCOORD", &uvsSource, &uvsOffset);
        readSource(node, "NORMAL", &normalsSource, &normalsOffset);
      }

      void MeshReader::readSource(const XMLNode& triangles, const char* data, String* source, unsigned int* offset) const
      {
        const XMLNode& node = triangles.getByAttribute("input", "semantic", data);
        *source = node.getAttribute("source").replace("#", "");
        *offset = node.getAttribute("offset");
      }

      void MeshReader::readPositionsSource(const XMLNode& mesh)
      {
        positionsSource = mesh.getByAttribute("vertices", "id", positionsSourceSource).getByAttribute("input", "semantic", "POSITION").getAttribute("source").replace("#", "");
      }

      void MeshReader::readSourceFloatArray(const XMLNode& mesh, const String& source, ArrayList<float>* list) const
      {
        *list = mesh.getByAttribute("source", "id", source)["float_array"].getData().toList<float>(" ");
      }

      void MeshReader::sortData(const ArrayList<float>& rawPositions, const ArrayList<float>& rawUvs, const ArrayList<float>& rawNormals)
      {
        unsigned int sourcesCount = 3;
        unsigned int vertexAmount = trianglesCount*3;

        positions.setSize(vertexAmount*3);
        uvs.setSize(vertexAmount*2);
        normals.setSize(vertexAmount*3);

        unsigned int k = 0;
        for(unsigned int i=0;i<triangles.size();i+=sourcesCount)
        {
          unsigned int positionId = triangles[i + positionsOffset];
          unsigned int uvId = triangles[i + uvsOffset];
          unsigned int normalId = triangles[i + normalsOffset];

          positions[3*k] = rawPositions[3*positionId];
          positions[3*k + 1] = rawPositions[3*positionId + 1];
          positions[3*k + 2] = rawPositions[3*positionId + 2];

          uvs[2*k] = rawUvs[2*uvId];
          uvs[2*k + 1] = 1.0 - rawUvs[2*uvId + 1];

          normals[3*k] = rawNormals[3*normalId];
          normals[3*k + 1] = rawNormals[3*normalId + 1];
          normals[3*k + 2] = rawNormals[3*normalId + 2];

          k++;
        }
      }
    }
  }
}
