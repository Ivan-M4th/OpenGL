#ifndef GD_UTILS_SKINREADER_H
#define GD_UTILS_SKINREADER_H

#include "../gddef.h"

#include "XMLNode.h"

#include "ArrayList.h"
#include "String.h"
#include "MeshReader.h"

#include "../graphics/Mesh.h"

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      class SkinReader
      {
      private:
        XMLNode* file;
        const MeshReader* meshReader;
        const ArrayList<String>* referenceJointNames;

        unsigned int jointsOffset;
        String jointsSource;

        unsigned int weightsOffset;
        String weightsSource;

        ArrayList<unsigned int> jointsPerVertex;
        ArrayList<unsigned int> jwIds;
        ArrayList<float> weightsValues;

        unsigned int vertexIndex;
        unsigned int jwIndex;

        ArrayList<unsigned int> rawJointIds;
        ArrayList<float> rawWeights;

        ArrayList<String> jointNames;
        ArrayList<unsigned int> jointIds;
        ArrayList<float> weights;

        void readSource(const XMLNode&, const String&, String*, unsigned int*) const;
        void readWeights(const XMLNode&);


        void getReferenceJointId(unsigned int*);
        void getNextJW(unsigned int*, float*);
        void getMostWeightedJoints(unsigned int);
        void sortNextVertexData();
        void sortData();
        void sortToTriangles();
        void readSkin(const XMLNode&);
      public:
        SkinReader();
        SkinReader(XMLNode*, const MeshReader*);
        SkinReader(const SkinReader&);
        SkinReader& operator=(const SkinReader&);

        void setReferenceJointNames(const ArrayList<String>*);
        void read();
        void loadSkin(gdg::Mesh*);
        const ArrayList<String>& getJointNames() const;
      };
    }
  }
}

#endif
