#ifndef GD_DATA_ASSETS_H
#define GD_DATA_ASSETS_H

#include "../gddef.h"

#include "../graphics/Mesh.h"
#include "../graphics/Texture.h"
#include "../graphics/TexturedMesh.h"
#include "../graphics/MeshModel.h"
#include "../graphics/animation/Armature.h"
#include "../graphics/animation/Animation.h"

#include "../math/geometry/ConvexPolyhedron.h"

namespace gt
{
  namespace doubovik
  {
    namespace data
    {
      //new

      extern const int TERRAIN_ATLAS_TEXTURE;
      extern const int STONE_PICKAXE_TEXTURE;

      extern const int PLAYER_H_HEAD_TEXTURE;
      extern const int PLAYER_H_CORE_TEXTURE;
      extern const int PLAYER_H_LEGS_TEXTURE;
      extern const int PLAYER_H_FEET_TEXTURE;

      extern const int BIRCH1_TREE_TEXTURE;
      extern const int BIRCH1_LEAVES1_TEXTURE;
      extern const int BIRCH1_LEAVES2_TEXTURE;
      extern const int BIRCH1_LEAVES3_TEXTURE;
      extern const int BIRCH1_LEAVES4_TEXTURE;

      extern const int CRATE1_TEXTURE;

      extern const int DEFAULT_FONT_ATLAS_TEXTURE;

      extern const int FRAME_CORNER_TEXTURE;
      extern const int FRAME_BORDER_TEXTURE;
      extern const int FRAME_CORE_TEXTURE;

      extern const int GUI_HOVERED_TEXTURE;
      extern const int ITEM_SELECTOR_TEXTURE;

      extern const int INVENTORY_BUTTON_TEXTURE;
      extern const int CRAFTING_BUTTON_TEXTURE;
      extern const int SKILLS_BUTTON_TEXTURE;

      extern const int QUAD_SHAPE_TEXTURE;
      extern const int TRIANGLE_SHAPE_TEXTURE;
      extern const int ROUNDED_SHAPE_TEXTURE;

      extern const int INVENTORY_ICON_TEXTURE;
      extern const int BOAR_TEXTURE;

      //mesh ids
      extern const int FRAME_CORNER_TL_MESH;
      extern const int FRAME_BORDER_L_MESH;
      extern const int FRAME_CORE_MESH;

      extern const int FRAME_CORNER_BL_MESH;
      extern const int FRAME_BORDER_B_MESH;

      extern const int FRAME_CORNER_BR_MESH;
      extern const int FRAME_BORDER_R_MESH;

      extern const int FRAME_CORNER_TR_MESH;
      extern const int FRAME_BORDER_T_MESH;

      extern const int STONE_PICKAXE_MESH;

      extern const int CUBE_MESH;

      extern const int BIRCH1_TREE_MESH;
      extern const int BIRCH1_LEAVES1_MESH;
      extern const int BIRCH1_LEAVES2_MESH;
      extern const int BIRCH1_LEAVES3_MESH;
      extern const int BIRCH1_LEAVES4_MESH;

      extern const int PLAYER_H_ENIRONEMENT_HITBOX_MESH;

      extern const int STRUCTURE_RAMP_MESH;
      extern const int STRUCTURE_AABB_MESH;

      extern const int BIRCH1_COLLIDER1_MESH;

      extern const int PLATFORM1_MESH;
      extern const int CRATE1_MESH;

      extern const int BOAR_MESH;

      extern const int PLAYER_H_HEAD_MESH;
      extern const int PLAYER_H_CORE_MESH;
      extern const int PLAYER_H_LEGS_MESH;
      extern const int PLAYER_H_FEET_MESH;

      const int BIRCH2_TREE_MESH = 1027;
      const int BIRCH2_LEAVES1_MESH = 1028;
      const int BIRCH2_LEAVES2_MESH = 1029;
      const int BIRCH2_LEAVES3_MESH = 1030;
      const int BIRCH2_LEAVES4_MESH = 1031;

      //armatures
      extern const int PLAYER_ARMATURE;
      extern const int BOAR_ARMATURE;

      //animations

      extern const int PLAYER_IDLE_ANIMATION;
      extern const int PLAYER_WALK_ANIMATION;
      extern const int PLAYER_RUN_ANIMATION;
      extern const int PLAYER_HOLD_BLOCK_ANIMATION;
      extern const int PLAYER_USE_BLOCK_ANIMATION;
      extern const int PLAYER_HOLD_PICKAXE_ANIMATION;
      extern const int PLAYER_USE_PICKAXE_ANIMATION;

      extern const int BOAR_IDLE_ANIMATION;

      //convex shapes
      extern const int CUBE_SHAPE;
      extern const int PLAYER_H_ENIRONEMENT_HITBOX_SHAPE;
      extern const int STRUCTURE_RAMP_SHAPE;
      extern const int BIRCH1_COLLIDER1_SHAPE;
      extern const int PLATFORM1_SHAPE;
      const int BIRCH2_COLLIDER_SHAPE = 5;
      const int BOAR_HITBOX_SHAPE = 6;

      struct AnimatedModelData
      {
        ArrayList<gdu::String> jointNames;
        ArrayList<gdu::String> idNames;
      };

      gdg::Texture* getTexture(int);
      gdg::Mesh* getMesh(int);
      const gdga::Armature* getArmature(int);
      gdg::Mesh* getItemIconMesh(int);
      const gdmg::ConvexPolyhedron* getConvexShape(int);
      gdga::Animation* getAnimation(int);

      void loadConvexShapes();
      void deleteConvexShapes();

      void loadRessources();
      void deleteRessources();
    }
  }
}

#endif
