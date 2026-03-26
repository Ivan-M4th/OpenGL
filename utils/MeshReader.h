#ifndef GD_UTILS_MESHREADER_H
#define GD_UTILS_MESHREADER_H

#include "XMLNode.h"

#include "../gddef.h"

#include "../graphics/Mesh.h"

#include "../math/geometry/ConvexPolyhedron.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class MeshReader
      {
      private:
        XMLNode* file;

        String positionsSourceSource;
        String positionsSource;
        unsigned int positionsOffset;

        String uvsSource;
        unsigned int uvsOffset;

        String normalsSource;
        unsigned int normalsOffset;

        ArrayList<unsigned int> triangles;
        unsigned int trianglesCount;

        ArrayList<float> rawPositions;

        ArrayList<float> positions;
        ArrayList<float> uvs;
        ArrayList<float> normals;

        void readMesh(const XMLNode&);
        void readTriangles(const XMLNode&);
        void readSource(const XMLNode&, const char*, String*, unsigned int*) const;
        void readPositionsSource(const XMLNode&);
        void readSourceFloatArray(const XMLNode&, const String&, ArrayList<float>*) const;
        void sortData(const ArrayList<float>&, const ArrayList<float>&, const ArrayList<float>&);
      public:
        MeshReader();
        MeshReader(XMLNode*);
        MeshReader(const MeshReader&);
        MeshReader& operator=(const MeshReader&);

        void read();
        void loadMesh(gdg::Mesh*) const;
        gdmg::ConvexPolyhedron getConvexShape() const;

        const ArrayList<unsigned int>& getTriangles() const;
        unsigned int getPositionsOffset() const;
        unsigned int getTrianglesCount() const;
      };
    }
  }
}

#endif
