#include "Material.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      Material::Material()
      {
        topTextureId = 0;
        sideTextureId = 0;
        bottomTextureId = 0;
        visible = false;
        solid = false;
      }

      Material::Material(int topTextureId, int sideTextureId, int bottomTextureId)
      {
        this->topTextureId = topTextureId;
        this->sideTextureId = sideTextureId;
        this->bottomTextureId = bottomTextureId;
        visible = true;
        solid = true;
      }

      Material::Material(int topTextureId, int sideTextureId, int bottomTextureId, bool visible, bool solid)
      {
        this->topTextureId = topTextureId;
        this->sideTextureId = sideTextureId;
        this->bottomTextureId = bottomTextureId;
        this->visible = visible;
        this->solid = solid;
      }

      Material::Material(const Material& material)
      {
        topTextureId = material.topTextureId;
        sideTextureId = material.sideTextureId;
        bottomTextureId = material.bottomTextureId;
        visible = material.visible;
        solid = material.solid;
      }

      Material& Material::operator=(const Material& material)
      {
        topTextureId = material.topTextureId;
        sideTextureId = material.sideTextureId;
        bottomTextureId = material.bottomTextureId;
        visible = material.visible;
        solid = material.solid;
        return *this;
      }

      int Material::getTopTextureId() const
      {
        return topTextureId;
      }

      int Material::getSideTextureId() const
      {
        return sideTextureId;
      }

      int Material::getBottomTextureId() const
      {
        return bottomTextureId;
      }

      bool Material::isVisible() const
      {
        return visible;
      }

      bool Material::isSolid() const
      {
        return solid;
      }
    }
  }
}
