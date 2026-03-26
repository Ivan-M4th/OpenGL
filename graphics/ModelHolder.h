#ifndef GD_GRAPHICS_MODELHOLDER_H
#define GD_GRAPHICS_MODELHOLDER_H

#include "../gddef.h"

#include "MeshModel.h"

#include "../math/Matrix4x4.h"

namespace gt
{
  namespace doubovik
  {
    namespace graphics
    {
      class ModelHolder
      {
      public:
        MeshModel* model;

        ModelHolder();
        ModelHolder(const ModelHolder&);
        ModelHolder& operator=(const ModelHolder&);
        virtual ~ModelHolder();

        bool isEmpty() const;
        MeshModel* getModel() const;
        void clear();
        void setModel(MeshModel*);

        virtual gdm::Matrix4x4 getTransformation() const;
      };
    }
  }
}

#endif
