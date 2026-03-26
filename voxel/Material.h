#ifndef GD_VOXEL_MATERIAL_H
#define GD_VOXEL_MATERIAL_H

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      class Material
      {
      private:
        int topTextureId;
        int sideTextureId;
        int bottomTextureId;
        bool visible;
        bool solid;
      public:
        Material();
        Material(int, int, int);
        Material(int, int, int, bool, bool);
        Material(const Material&);
        Material& operator=(const Material&);

        int getTopTextureId() const;
        int getSideTextureId() const;
        int getBottomTextureId() const;
        bool isVisible() const;
        bool isSolid() const;
      };
    }
  }
}

#endif
