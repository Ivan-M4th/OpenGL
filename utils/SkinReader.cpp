#include "SkinReader.h"

#include <iostream>

namespace gt
{
  namespace doubovik
  {
    namespace utils
    {
      SkinReader::SkinReader()
      {
        file = NULL;
        meshReader = NULL;
        referenceJointNames = NULL;
      }

      SkinReader::SkinReader(XMLNode* file, const MeshReader* meshReader)
      {
        this->file = file;
        this->meshReader = meshReader;
        referenceJointNames = NULL;
      }

      SkinReader::SkinReader(const SkinReader& reader)
      {
        file = reader.file;
        meshReader = reader.meshReader;
        referenceJointNames = reader.referenceJointNames;

        jointsOffset = reader.jointsOffset;
        jointsSource = reader.jointsSource;

        weightsOffset = reader.weightsOffset;
        weightsSource = reader.weightsSource;

        jointsPerVertex = reader.jointsPerVertex;
        jwIds = reader.jwIds;
        weightsValues = reader.weightsValues;

        vertexIndex = reader.vertexIndex;
        jwIndex = reader.jwIndex;

        rawJointIds = reader.rawJointIds;
        rawWeights = reader.rawWeights;

        jointNames = reader.jointNames;
        jointIds = reader.jointIds;
        weights = reader.weights;
      }

      SkinReader& SkinReader::operator=(const SkinReader& reader)
      {
        file = reader.file;
        meshReader = reader.meshReader;
        referenceJointNames = reader.referenceJointNames;

        jointsOffset = reader.jointsOffset;
        jointsSource = reader.jointsSource;

        weightsOffset = reader.weightsOffset;
        weightsSource = reader.weightsSource;

        jointsPerVertex = reader.jointsPerVertex;
        jwIds = reader.jwIds;
        weightsValues = reader.weightsValues;

        vertexIndex = reader.vertexIndex;
        jwIndex = reader.jwIndex;

        rawJointIds = reader.rawJointIds;
        rawWeights = reader.rawWeights;

        jointNames = reader.jointNames;
        jointIds = reader.jointIds;
        weights = reader.weights;
        return *this;
      }

      void SkinReader::loadSkin(gdg::Mesh* mesh)
      {
        mesh->addIVbo(3, 3, jointIds.getData(), jointIds.size());
        mesh->addVbo(4, 3, weights.getData(), weights.size());
      }

      void SkinReader::read()
      {
        readSkin((*file)["COLLADA"]["library_controllers"]["controller"]["skin"]);
      }

      const ArrayList<String>& SkinReader::getJointNames() const
      {
        return jointNames;
      }

      void SkinReader::readSource(const XMLNode& node, const String& dataType, String* source, unsigned int* offset) const
      {
        const XMLNode& input = node.getByAttribute("input", "semantic", dataType);
        *source = input.getAttribute("source").replace("#", "");
        *offset = input.getAttribute("offset");
      }

      void SkinReader::readWeights(const XMLNode& node)
      {
        readSource(node, "JOINT", &jointsSource, &jointsOffset);
        readSource(node, "WEIGHT", &weightsSource, &weightsOffset);

        jointsPerVertex = node["vcount"].getData().toList<unsigned int>(" ");
        jwIds = node["v"].getData().toList<unsigned int>(" ");
      }

      void SkinReader::getReferenceJointId(unsigned int* jointId)
      {
        const String& jointName = jointNames[*jointId];
        if(jointName == (*referenceJointNames)[*jointId])
        {
          return;
        }
        for(unsigned int i=0;i<referenceJointNames->size();i++)
        {
          if((*referenceJointNames)[i] == jointName)
          {
            *jointId = i;
            return;
          }
        }
        assert(false);
      }

      void SkinReader::getNextJW(unsigned int* jointId, float* weight)
      {
        unsigned int numSources = 2;
        *jointId = jwIds[jwIndex + jointsOffset];

        if(referenceJointNames != NULL)
        {
          getReferenceJointId(jointId);
        }

        unsigned int weightId = jwIds[jwIndex + weightsOffset];
        *weight = weightsValues[weightId];

        jwIndex+=numSources;
      }

      void SkinReader::getMostWeightedJoints(unsigned int jointAmount)
      {
        unsigned int jointId1 = 0;
        float weight1 = 0.0;

        unsigned int jointId2 = 0;
        float weight2 = 0.0;

        unsigned int jointId3 = 0;
        float weight3 = 0.0;

        for(unsigned int i=0;i<jointAmount;i++)
        {
          unsigned int jointId;
          float weight;
          getNextJW(&jointId, &weight);

          if(weight > weight1)
          {
            jointId3 = jointId2;
            weight3 = weight2;

            jointId2 = jointId1;
            weight2 = weight1;

            jointId1 = jointId;
            weight1 = weight;
          }
          else if(weight > weight2)
          {
            jointId3 = jointId2;
            weight3 = weight2;

            jointId2 = jointId;
            weight2 = weight;
          }
          else if(weight > weight3)
          {
            jointId3 = jointId;
            weight3 = weight;
          }
        }

        float totalWeight = weight1 + weight2 + weight3;

        if(totalWeight > 0.000001)
        {
          weight1/=totalWeight;
          weight2/=totalWeight;
          weight3/=totalWeight;
        }

        rawJointIds.add(jointId1);
        rawWeights.add(weight1);

        rawJointIds.add(jointId2);
        rawWeights.add(weight2);

        rawJointIds.add(jointId3);
        rawWeights.add(weight3);
      }

      void SkinReader::sortNextVertexData()
      {
        unsigned int jointAmount = jointsPerVertex[vertexIndex];

        if(jointAmount <= 3)
        {
          for(unsigned int i=0;i<3;i++)
          {
            if(i < jointAmount)
            {
              unsigned int jointId;
              float weight;
              getNextJW(&jointId, &weight);
              rawJointIds.add(jointId);
              rawWeights.add(weight);
            }
            else
            {
              rawJointIds.add(0);
              rawWeights.add(0.0);
            }
          }
        }
        else
        {
          getMostWeightedJoints(jointAmount);
        }
        vertexIndex++;
      }

      void SkinReader::sortData()
      {
        vertexIndex = 0;
        jwIndex = 0;

        while(vertexIndex < jointsPerVertex.size())
        {
          sortNextVertexData();
        }
      }

      void SkinReader::sortToTriangles()
      {
        jointIds.setSize(meshReader->getTrianglesCount()*9);
        weights.setSize(meshReader->getTrianglesCount()*9);

        unsigned int sourcesCount = 3;

        unsigned int k = 0;
        for(unsigned int i=0;i<meshReader->getTriangles().size();i+=sourcesCount)
        {
          unsigned int positionId = meshReader->getTriangles()[i + meshReader->getPositionsOffset()];

          jointIds[3*k] = rawJointIds[3*positionId];
          jointIds[3*k + 1] = rawJointIds[3*positionId + 1];
          jointIds[3*k + 2] = rawJointIds[3*positionId + 2];

          weights[3*k] = rawWeights[3*positionId];
          weights[3*k + 1] = rawWeights[3*positionId + 1];
          weights[3*k + 2] = rawWeights[3*positionId + 2];

          k++;
        }
      }

      void SkinReader::setReferenceJointNames(const ArrayList<String>* referenceJointNames)
      {
        this->referenceJointNames = referenceJointNames;
      }

      void SkinReader::readSkin(const XMLNode& skin)
      {
        readWeights(skin["vertex_weights"]);
        weightsValues = skin.getByAttribute("source", "id", weightsSource)["float_array"].getData().toList<float>(" ");
        jointNames = skin.getByAttribute("source", "id", jointsSource)["Name_array"].getData().toList<String>(" ");

        sortData();
        sortToTriangles();
      }
    }
  }
}
