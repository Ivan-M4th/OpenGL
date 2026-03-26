#include "MeshModel.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      const unsigned int MODEL = 0;
      const unsigned int INDEXED_MODEL = 1;

      MeshModel::MeshModel()
      {
        
      }

      MeshModel::MeshModel(const TexturedMesh& mesh)
      {
        this->mesh = mesh;
        dataType = MODEL;
      }

      MeshModel::MeshModel(const TexturedMesh& mesh, const gdm::Vector3& position)
      {
        this->mesh = mesh;
        this->position = position;
        dataType = MODEL;
      }

      MeshModel::MeshModel(const TexturedMesh& mesh, const gdm::Vector3& position, unsigned int dataType)
      {
        this->mesh = mesh;
        this->position = position;
        this->dataType = dataType;
      }

      MeshModel::MeshModel(const MeshModel& model)
      {
        mesh = model.mesh;
        position = model.position;
        dataType = model.dataType;
      }

      MeshModel& MeshModel::operator=(const MeshModel& model)
      {
        mesh = model.mesh;
        position = model.position;
        dataType = model.dataType;
        return *this;
      }

      MeshModel::~MeshModel()
      {

      }

      TexturedMesh MeshModel::getMesh() const
      {
        return mesh;
      }

      const gdm::Vector3& MeshModel::getPosition() const
      {
        return position;
      }

      unsigned int MeshModel::getDataType() const
      {
        return dataType;
      }
    }
  }
}
