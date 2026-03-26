#include "BlockBuilder.h"

#include "Material.h"
#include "Materials.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      BlockBuilder::BlockBuilder(TerrainTexture* texture)
      {
        x = 0;
        y = 0;
        z = 0;
        this->texture = texture;
      }

      BlockBuilder::BlockBuilder(const BlockBuilder& builder)
      {
        x = builder.x;
        y = builder.y;
        z = builder.z;
        texture = builder.texture;
      }

      BlockBuilder& BlockBuilder::operator=(const BlockBuilder& builder)
      {
        x = builder.x;
        y = builder.y;
        z = builder.z;
        texture = builder.texture;
        return *this;
      }

      void BlockBuilder::addFace(const float* face, ArrayList<float>* positions, int* positionsAmount, ArrayList<unsigned int>* indices) const
      {
        for(int i=0;i<4;i++)
        {
          positions->add(*(face + 3*i) + x);
          positions->add(*(face + 3*i + 1) + y);
          positions->add(*(face + 3*i + 2) + z);
        }

        for(int i=0;i<6;i++)
        {
          indices->add(*positionsAmount + *(INDICES + i));
        }
        (*positionsAmount)+=4;
      }

      void BlockBuilder::addUVs(int id, ArrayList<float>* uvs) const
      {
        float xmin;
        float ymin;

        float xmax;
        float ymax;
        texture->getUVs(id, &xmin, &ymin, &xmax, &ymax);

        uvs->add(xmin);
        uvs->add(ymin);

        uvs->add(xmin);
        uvs->add(ymax);

        uvs->add(xmax);
        uvs->add(ymax);

        uvs->add(xmax);
        uvs->add(ymin);
      }

      void BlockBuilder::addNormals(float x, float y, float z, ArrayList<float>* normals) const
      {
        for(int i=0;i<4;i++)
        {
          normals->add(x);
          normals->add(y);
          normals->add(z);
        }
      }

      void BlockBuilder::addTopFace(int id, ArrayList<float>* positions, int* positionsAmount, ArrayList<float>* uvs, ArrayList<float>* normals, ArrayList<unsigned int>* indices) const
      {
        addFace(FACE_TOP, positions, positionsAmount, indices);
        addUVs(id, uvs);
        addNormals(0.0,1.0,0.0, normals);
      }

      void BlockBuilder::addBottomFace(int id, ArrayList<float>* positions, int* positionsAmount, ArrayList<float>* uvs, ArrayList<float>* normals, ArrayList<unsigned int>* indices) const
      {
        addFace(FACE_BOTTOM, positions, positionsAmount, indices);
        addUVs(id, uvs);
        addNormals(0.0, -1.0, 0.0, normals);
      }

      void BlockBuilder::addFrontFace(int id, ArrayList<float>* positions, int* positionsAmount, ArrayList<float>* uvs, ArrayList<float>* normals, ArrayList<unsigned int>* indices) const
      {
        addFace(FACE_FRONT, positions, positionsAmount, indices);
        addUVs(id, uvs);
        addNormals(0.0,0.0,-1.0, normals);
      }

      void BlockBuilder::addBackFace(int id, ArrayList<float>* positions, int* positionsAmount, ArrayList<float>* uvs, ArrayList<float>* normals, ArrayList<unsigned int>* indices) const
      {
        addFace(FACE_BACK, positions, positionsAmount, indices);
        addUVs(id, uvs);
        addNormals(0.0,0.0,1.0, normals);
      }

      void BlockBuilder::addRightFace(int id, ArrayList<float>* positions, int* positionsAmount, ArrayList<float>* uvs, ArrayList<float>* normals, ArrayList<unsigned int>* indices) const
      {
        addFace(FACE_RIGHT, positions, positionsAmount, indices);
        addUVs(id, uvs);
        addNormals(1.0,0.0,0.0, normals);
      }

      void BlockBuilder::addLeftFace(int id, ArrayList<float>* positions, int* positionsAmount, ArrayList<float>* uvs, ArrayList<float>* normals, ArrayList<unsigned int>* indices) const
      {
        addFace(FACE_LEFT, positions, positionsAmount, indices);
        addUVs(id, uvs);
        addNormals(-1.0,0.0,0.0, normals);
      }

      void BlockBuilder::addBlock(float size, int materialId, ArrayList<float>* positions, int* positionsAmount, ArrayList<float>* uvs, ArrayList<float>* normals, ArrayList<unsigned int>* indices) const
      {
        Material* material = gdv::getMaterial(materialId);

        if(material->isVisible())
        {
          addTopFace(material->getTopTextureId(), positions, positionsAmount, uvs, normals, indices);
          addBottomFace(material->getBottomTextureId(), positions, positionsAmount, uvs, normals, indices);
          addFrontFace(material->getSideTextureId(), positions, positionsAmount, uvs, normals, indices);
          addBackFace(material->getSideTextureId(), positions, positionsAmount, uvs, normals, indices);
          addRightFace(material->getSideTextureId(), positions, positionsAmount, uvs, normals, indices);
          addLeftFace(material->getSideTextureId(), positions, positionsAmount, uvs, normals, indices);

          for(unsigned int i=0;i<positions->size();i++)
          {
            (*positions)[i] = size*(*positions)[i];
          }
        }
      }

      void BlockBuilder::getBlock(float size, int materialId, gdg::Mesh* mesh) const
      {
        ArrayList<float> positions;
        ArrayList<float> uvs;
        ArrayList<float> normals;
        ArrayList<unsigned int> indices;
        int positionsAmount = 0;

        addBlock(size, materialId, &positions, &positionsAmount, &uvs, &normals, &indices);

        mesh->addVbo(0, 3, positions.getData(), positions.size());
        mesh->addVbo(1, 2, uvs.getData(), uvs.size());
        mesh->addVbo(2, 3, normals.getData(), normals.size());
        mesh->addIndices(indices.getData(), indices.size());
      }

      void BlockBuilder::getBlockIcon(int materialId, gdg::Mesh* mesh) const
      {
        Material* material = gdv::getMaterial(materialId);

        ArrayList<float> uvs;
        addUVs(material->getSideTextureId(), &uvs);
        float positions[] = {0.0,0.0, 0.0,-1.0, 1.0,-1.0, 1.0,0.0};
        unsigned int indices[] = {0,1,2,2,3,0};

        mesh->addVbo(0, 2, positions, 8);
        mesh->addVbo(1, 2, uvs.getData(), uvs.size());
        mesh->addIndices(indices, 6);
      }

      void BlockBuilder::setPosition(int x, int y, int z)
      {
        this->x = x;
        this->y = y;
        this->z = z;
      }
    }
  }
}
