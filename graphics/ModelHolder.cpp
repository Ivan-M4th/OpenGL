#include "ModelHolder.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      ModelHolder::ModelHolder()
      {
        model = NULL;
      }

      ModelHolder::ModelHolder(const ModelHolder& holder)
      {
        model = holder.model;
      }

      ModelHolder& ModelHolder::operator=(const ModelHolder& holder)
      {
        model = holder.model;
        return *this;
      }

      ModelHolder::~ModelHolder()
      {

      }

      bool ModelHolder::isEmpty() const
      {
        return model == NULL;
      }

      MeshModel* ModelHolder::getModel() const
      {
        return model;
      }

      void ModelHolder::clear()
      {
        model = NULL;
      }

      void ModelHolder::setModel(MeshModel* model)
      {
        this->model = model;
      }

      gdm::Matrix4x4 ModelHolder::getTransformation() const
      {
        return gdm::Matrix4x4();
      }
    }
  }
}
