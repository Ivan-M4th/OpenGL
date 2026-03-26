#include "Assets.h"

#include <cassert>

#include "../voxel/TerrainTexture.h"
#include "../voxel/BlockBuilder.h"
#include "../voxel/Materials.h"

#include "../utils/ArrayList.h"
#include "../utils/XMLReader.h"
#include "../utils/XMLNode.h"
#include "../utils/MeshReader.h"
#include "../utils/SkinReader.h"
#include "../utils/ArmatureReader.h"
#include "../utils/AnimationReader.h"

#include "../graphics/GeometryLoader.h"

namespace gt
{
  namespace doubovik
  {
    namespace data
    {
      //texture ids
      const int TERRAIN_ATLAS_TEXTURE = 0;
      const int STONE_PICKAXE_TEXTURE = 1;

      const int PLAYER_H_HEAD_TEXTURE = 2;
      const int PLAYER_H_CORE_TEXTURE = 3;
      const int PLAYER_H_LEGS_TEXTURE = 4;
      const int PLAYER_H_FEET_TEXTURE = 5;

      const int BIRCH1_TREE_TEXTURE = 6;
      const int BIRCH1_LEAVES1_TEXTURE = 7;
      const int BIRCH1_LEAVES2_TEXTURE = 8;
      const int BIRCH1_LEAVES3_TEXTURE = 9;
      const int BIRCH1_LEAVES4_TEXTURE = 10;

      const int CRATE1_TEXTURE = 11;

      const int DEFAULT_FONT_ATLAS_TEXTURE = 12;

      const int FRAME_CORNER_TEXTURE = 13;
      const int FRAME_BORDER_TEXTURE = 14;
      const int FRAME_CORE_TEXTURE = 15;

      const int GUI_HOVERED_TEXTURE = 16;
      const int ITEM_SELECTOR_TEXTURE = 17;

      const int INVENTORY_BUTTON_TEXTURE = 18;
      const int CRAFTING_BUTTON_TEXTURE = 19;
      const int SKILLS_BUTTON_TEXTURE = 20;

      const int QUAD_SHAPE_TEXTURE = 21;
      const int TRIANGLE_SHAPE_TEXTURE = 22;
      const int ROUNDED_SHAPE_TEXTURE = 23;

      const int INVENTORY_ICON_TEXTURE = 24;
      const int BOAR_TEXTURE = 25;

      //mesh ids

      const int FRAME_CORNER_TL_MESH = 1000;
      const int FRAME_BORDER_L_MESH = 1001;
      const int FRAME_CORE_MESH = 1002;

      const int FRAME_CORNER_BL_MESH = 1003;
      const int FRAME_BORDER_B_MESH = 1004;

      const int FRAME_CORNER_BR_MESH = 1005;
      const int FRAME_BORDER_R_MESH = 1006;

      const int FRAME_CORNER_TR_MESH = 1007;
      const int FRAME_BORDER_T_MESH = 1008;

      const int STONE_PICKAXE_MESH = 1009;

      const int CUBE_MESH = 1010;

      const int BIRCH1_TREE_MESH = 1011;
      const int BIRCH1_LEAVES1_MESH = 1012;
      const int BIRCH1_LEAVES2_MESH = 1013;
      const int BIRCH1_LEAVES3_MESH = 1014;
      const int BIRCH1_LEAVES4_MESH = 1015;

      const int PLAYER_H_ENIRONEMENT_HITBOX_MESH = 1016;

      const int STRUCTURE_RAMP_MESH = 1017;
      const int STRUCTURE_AABB_MESH = 1018;

      const int BIRCH1_COLLIDER1_MESH = 1019;

      const int PLATFORM1_MESH = 1020;
      const int CRATE1_MESH = 1021;

      const int BOAR_MESH = 1022;

      const int PLAYER_H_HEAD_MESH = 1023;
      const int PLAYER_H_CORE_MESH = 1024;
      const int PLAYER_H_LEGS_MESH = 1025;
      const int PLAYER_H_FEET_MESH = 1026;

      //armatures
      const int PLAYER_ARMATURE = 0;
      const int BOAR_ARMATURE = 1;

      //animations

      const int PLAYER_IDLE_ANIMATION = 0;
      const int PLAYER_WALK_ANIMATION = 1;
      const int PLAYER_RUN_ANIMATION = 2;
      const int PLAYER_HOLD_BLOCK_ANIMATION = 3;
      const int PLAYER_USE_BLOCK_ANIMATION = 4;
      const int PLAYER_HOLD_PICKAXE_ANIMATION = 5;
      const int PLAYER_USE_PICKAXE_ANIMATION = 6;

      const int BOAR_IDLE_ANIMATION = 7;

      //convex shapes
      const int CUBE_SHAPE = 0;
      const int PLAYER_H_ENIRONEMENT_HITBOX_SHAPE = 1;
      const int STRUCTURE_RAMP_SHAPE = 2;
      const int BIRCH1_COLLIDER1_SHAPE = 3;
      const int PLATFORM1_SHAPE = 4;

      //new

      //textures
      gdg::Texture* TEXTURES = NULL;
      const int TEXTURES_SIZE = 3000;

      //meshes
      gdg::Mesh* MESHES = NULL;
      const int MESHES_SIZE = 3000;

      //animations

      gdga::Armature* ARMATURES = NULL;
      const int ARMATURES_SIZE = 100;

      gdga::Animation* ANIMATIONS = NULL;
      const int ANIMATIONS_SIZE = 100;

      //items
      gdg::Mesh* ITEM_ICON_MESHES = NULL;
      const int ITEM_ICON_MESHES_SIZE = 1000;

      //convex shapes
      gdmg::ConvexPolyhedron* CONVEX_SHAPES = NULL;
      const unsigned int CONVEX_SHAPES_SIZE = 100;

      void loadTexture(gdg::Texture* texture, const char* fileName)
      {
        texture->setId(gdg::loadTexture(fileName));
      }

      void loadTexture(int id, const char* fileName)
      {
        loadTexture(TEXTURES + id, fileName);
      }

      void readModelFile(gdg::Mesh* mesh, const char* fileName)
      {
        gdu::XMLReader reader(fileName);
        gdu::XMLNode xmlFile = reader.read();
        gdu::MeshReader meshReader(&xmlFile);
        meshReader.read();
        meshReader.loadMesh(mesh);
      }

      void readModelFile(int id, const char* fileName)
      {
        readModelFile((MESHES + id), fileName);
      }

      void readConvexShape(gdmg::ConvexPolyhedron* shape, const char* fileName)
      {
        gdu::XMLReader reader(fileName);
        gdu::XMLNode xmlFile = reader.read();
        gdu::MeshReader meshReader(&xmlFile);
        meshReader.read();
        *shape = meshReader.getConvexShape();
      }

      void readConvexShape(int id, const char* fileName)
      {
        readConvexShape(CONVEX_SHAPES + id, fileName);
      }

      void readAnimatedModelFile(gdg::Mesh* mesh, gdga::Armature* armature, const char* fileName, AnimatedModelData* animatedModelData)
      {
        gdu::XMLReader reader(fileName);
        gdu::XMLNode xmlFile = reader.read();
        gdu::MeshReader meshReader(&xmlFile);
        meshReader.read();

        gdu::SkinReader skinReader(&xmlFile, &meshReader);
        skinReader.read();

        gdu::ArmatureReader armatureReader(&xmlFile, &skinReader.getJointNames());

        meshReader.loadMesh(mesh);
        skinReader.loadSkin(mesh);
        *armature = armatureReader.read();

        animatedModelData->jointNames = skinReader.getJointNames();
        animatedModelData->idNames = armatureReader.getIdNames();
      }

      void readAnimatedModelFile(int meshId, int armatureId, const char* fileName, AnimatedModelData* animatedModelData)
      {
        readAnimatedModelFile(MESHES + meshId, ARMATURES + armatureId, fileName, animatedModelData);
      }

      void readAnimatedModelFileByReference(gdg::Mesh* mesh, const ArrayList<gdu::String>* jointNames, const char* fileName)
      {
        gdu::XMLReader reader(fileName);
        gdu::XMLNode xmlFile = reader.read();
        gdu::MeshReader meshReader(&xmlFile);
        meshReader.read();

        gdu::SkinReader skinReader(&xmlFile, &meshReader);
        skinReader.setReferenceJointNames(jointNames);
        skinReader.read();

        meshReader.loadMesh(mesh);
        skinReader.loadSkin(mesh);
      }

      void readAnimatedModelFileByReference(int id, const ArrayList<gdu::String>* jointNames, const char* fileName)
      {
        readAnimatedModelFileByReference(MESHES + id, jointNames, fileName);
      }

      void readAnimationFile(gdga::Animation* animation, const char* fileName, const ArrayList<gdu::String>* idNames)
      {
        gdu::XMLReader reader(fileName);
        gdu::XMLNode xmlFile = reader.read();

        gdu::AnimationReader animationReader(&xmlFile, idNames);
        *animation = animationReader.read();
      }

      void readAnimationFile(int id, const char* fileName, const ArrayList<gdu::String>* idNames)
      {
        readAnimationFile(ANIMATIONS + id, fileName, idNames);
      }

      void generateBlockAsset(gdg::Mesh* iconMesh, gdg::Mesh* blockMesh, int materialId, const gdv::BlockBuilder* builder)
      {
        builder->getBlockIcon(materialId, iconMesh);
        builder->getBlock(0.114, materialId, blockMesh);
      }

      void loadBlocks()
      {
        gdv::TerrainTexture terrainAtlas(20, 20, getTexture(TERRAIN_ATLAS_TEXTURE));
        gdv::BlockBuilder blockBuilder(&terrainAtlas);

        for(unsigned int i=0;i<gdv::getMaterialsAmount();i++)
        {
          generateBlockAsset(ITEM_ICON_MESHES + i, MESHES + i, i, &blockBuilder);
        }
      }

      void createGuiMesh(gdg::Mesh* mesh, const ArrayList<unsigned int>& indices, const ArrayList<float>& positions, const ArrayList<float>& uvs)
      {
        mesh->addIndices(indices.getData(), indices.size());
        mesh->addVbo(0, 2, positions.getData(), positions.size());
        mesh->addVbo(1, 2, uvs.getData(), uvs.size());
      }

      void createGuiMeshes()
      {
        ArrayList<unsigned int> indices;
        indices.add(0);
        indices.add(1);
        indices.add(2);

        indices.add(2);
        indices.add(3);
        indices.add(0);

        ArrayList<float> positions;
        positions.add(0.0);
        positions.add(-1.0);

        positions.add(1.0);
        positions.add(-1.0);

        positions.add(1.0);
        positions.add(0.0);

        positions.add(0.0);
        positions.add(0.0);

        //textures
        ArrayList<float> defaultUvs;
        defaultUvs.add(0.0);
        defaultUvs.add(1.0);

        defaultUvs.add(1.0);
        defaultUvs.add(1.0);

        defaultUvs.add(1.0);
        defaultUvs.add(0.0);

        defaultUvs.add(0.0);
        defaultUvs.add(0.0);

        createGuiMesh(MESHES + FRAME_CORNER_TL_MESH, indices, positions, defaultUvs);
        createGuiMesh(MESHES + FRAME_BORDER_L_MESH, indices, positions, defaultUvs);
        createGuiMesh(MESHES + FRAME_CORE_MESH, indices, positions, defaultUvs);

        ArrayList<float> r90uvs;
        r90uvs.add(0.0);
        r90uvs.add(0.0);

        r90uvs.add(0.0);
        r90uvs.add(1.0);

        r90uvs.add(1.0);
        r90uvs.add(1.0);

        r90uvs.add(1.0);
        r90uvs.add(0.0);

        createGuiMesh(MESHES + FRAME_CORNER_BL_MESH, indices, positions, r90uvs);
        createGuiMesh(MESHES + FRAME_BORDER_B_MESH, indices, positions, r90uvs);

        ArrayList<float> r180uvs;
        r180uvs.add(1.0);
        r180uvs.add(0.0);

        r180uvs.add(0.0);
        r180uvs.add(0.0);

        r180uvs.add(0.0);
        r180uvs.add(1.0);

        r180uvs.add(1.0);
        r180uvs.add(1.0);

        createGuiMesh(MESHES + FRAME_CORNER_BR_MESH, indices, positions, r180uvs);
        createGuiMesh(MESHES + FRAME_BORDER_R_MESH, indices, positions, r180uvs);

        ArrayList<float> r270uvs;
        r270uvs.add(1.0);
        r270uvs.add(1.0);

        r270uvs.add(1.0);
        r270uvs.add(0.0);

        r270uvs.add(0.0);
        r270uvs.add(0.0);

        r270uvs.add(0.0);
        r270uvs.add(1.0);

        createGuiMesh(MESHES + FRAME_CORNER_TR_MESH, indices, positions, r270uvs);
        createGuiMesh(MESHES + FRAME_BORDER_T_MESH, indices, positions, r270uvs);
      }

      void loadTextures()
      {
        loadTexture(TERRAIN_ATLAS_TEXTURE, "resources/terrain/atlas.png");
        loadTexture(STONE_PICKAXE_TEXTURE, "resources/texture_pick_stone.png");

        loadTexture(PLAYER_H_HEAD_TEXTURE, "resources/player/head.png");
        loadTexture(PLAYER_H_CORE_TEXTURE, "resources/player/core.png");
        loadTexture(PLAYER_H_LEGS_TEXTURE, "resources/player/legs.png");
        loadTexture(PLAYER_H_FEET_TEXTURE, "resources/player/feet.png");

        loadTexture(BIRCH1_TREE_TEXTURE, "resources/structures/environment/Birch/tree.png");
        loadTexture(BIRCH1_LEAVES1_TEXTURE, "resources/structures/environment/Birch/leaves1.png");
        loadTexture(BIRCH1_LEAVES2_TEXTURE, "resources/structures/environment/Birch/leaves2.png");
        loadTexture(BIRCH1_LEAVES3_TEXTURE, "resources/structures/environment/Birch/leaves3.png");
        loadTexture(BIRCH1_LEAVES4_TEXTURE, "resources/structures/environment/Birch/leaves4.png");

        loadTexture(CRATE1_TEXTURE, "resources/structures/other/crate.png");

        loadTexture(DEFAULT_FONT_ATLAS_TEXTURE, "resources/fonts/default.png");

        loadTexture(FRAME_CORNER_TEXTURE, "resources/gui/corner.png");
        loadTexture(FRAME_BORDER_TEXTURE, "resources/gui/border.png");
        loadTexture(FRAME_CORE_TEXTURE, "resources/gui/core.png");

        loadTexture(GUI_HOVERED_TEXTURE, "resources/gui/hovered.png");
        loadTexture(ITEM_SELECTOR_TEXTURE, "resources/gui/itemSelector.png");

        loadTexture(INVENTORY_BUTTON_TEXTURE, "resources/gui/buttons/inventory.png");
        loadTexture(CRAFTING_BUTTON_TEXTURE, "resources/gui/buttons/crafting.png");
        loadTexture(SKILLS_BUTTON_TEXTURE, "resources/gui/buttons/skills.png");

        loadTexture(QUAD_SHAPE_TEXTURE, "resources/gui/quad.png");
        loadTexture(TRIANGLE_SHAPE_TEXTURE, "resources/gui/triangle.png");
        loadTexture(ROUNDED_SHAPE_TEXTURE, "resources/gui/rounded.png");

        loadTexture(INVENTORY_ICON_TEXTURE, "resources/gui/inventory_icon.png");
        loadTexture(BOAR_TEXTURE, "resources/boar/Boar.png");
      }

      void loadModels()
      {
        readModelFile(STONE_PICKAXE_MESH, "resources/stone_pickaxe.dae");

        readModelFile(CUBE_MESH, "resources/box.dae");

        readModelFile(BIRCH1_TREE_MESH, "resources/structures/environment/Birch/tree.dae");
        readModelFile(BIRCH1_LEAVES1_MESH, "resources/structures/environment/Birch/leaves1.dae");
        readModelFile(BIRCH1_LEAVES2_MESH, "resources/structures/environment/Birch/leaves2.dae");
        readModelFile(BIRCH1_LEAVES3_MESH, "resources/structures/environment/Birch/leaves3.dae");
        readModelFile(BIRCH1_LEAVES4_MESH, "resources/structures/environment/Birch/leaves4.dae");

        readModelFile(PLAYER_H_ENIRONEMENT_HITBOX_MESH, "resources/player/hitbox.dae");

        readModelFile(STRUCTURE_RAMP_MESH, "resources/ramp.dae");
        readModelFile(STRUCTURE_AABB_MESH, "resources/utils/AABB.dae");

        readModelFile(BIRCH1_COLLIDER1_MESH, "resources/structures/environment/Birch/collider1.dae");

        readModelFile(PLATFORM1_MESH, "resources/structures/other/plateform.dae");
        readModelFile(CRATE1_MESH, "resources/structures/other/crate.dae");

        readModelFile(BIRCH2_TREE_MESH, "resources/structures/environment/Birch/tree2.dae");
        readModelFile(BIRCH2_LEAVES1_MESH, "resources/structures/environment/Birch/leaves2_1.dae");
        readModelFile(BIRCH2_LEAVES2_MESH, "resources/structures/environment/Birch/leaves2_2.dae");
        readModelFile(BIRCH2_LEAVES3_MESH, "resources/structures/environment/Birch/leaves2_3.dae");
        readModelFile(BIRCH2_LEAVES4_MESH, "resources/structures/environment/Birch/leaves2_4.dae");
      }

      void loadPlayer()
      {
        AnimatedModelData animatedModelData;
        readAnimatedModelFile(PLAYER_H_HEAD_MESH, PLAYER_ARMATURE, "resources/player/head.dae", &animatedModelData);

        readAnimatedModelFileByReference(PLAYER_H_CORE_MESH, &animatedModelData.jointNames, "resources/player/core.dae");
        readAnimatedModelFileByReference(PLAYER_H_LEGS_MESH, &animatedModelData.jointNames, "resources/player/legs.dae");
        readAnimatedModelFileByReference(PLAYER_H_FEET_MESH, &animatedModelData.jointNames, "resources/player/feet.dae");

        readAnimationFile(PLAYER_IDLE_ANIMATION, "resources/player/idle.dae", &animatedModelData.idNames);
        readAnimationFile(PLAYER_WALK_ANIMATION, "resources/player/walk.dae", &animatedModelData.idNames);
        readAnimationFile(PLAYER_RUN_ANIMATION, "resources/player/run.dae", &animatedModelData.idNames);

        readAnimationFile(PLAYER_HOLD_BLOCK_ANIMATION, "resources/player/hold_cube.dae", &animatedModelData.idNames);
        readAnimationFile(PLAYER_USE_BLOCK_ANIMATION, "resources/player/place_block.dae", &animatedModelData.idNames);

        readAnimationFile(PLAYER_HOLD_PICKAXE_ANIMATION, "resources/player/hold_pickaxe.dae", &animatedModelData.idNames);
        readAnimationFile(PLAYER_USE_PICKAXE_ANIMATION, "resources/player/use_pickaxe.dae", &animatedModelData.idNames);
      }

      void loadBoar()
      {
        AnimatedModelData animatedModelData;
        readAnimatedModelFile(BOAR_MESH, BOAR_ARMATURE, "resources/boar/Boar.dae", &animatedModelData);

        readAnimationFile(BOAR_IDLE_ANIMATION, "resources/boar/Boar.dae", &animatedModelData.idNames);
      }

      void loadAnimatedModels()
      {
        loadPlayer();
        loadBoar();
      }

      void loadConvexShapes()
      {
        CONVEX_SHAPES = new gdmg::ConvexPolyhedron[CONVEX_SHAPES_SIZE];

        readConvexShape(CUBE_SHAPE, "resources/box.dae");
        readConvexShape(PLAYER_H_ENIRONEMENT_HITBOX_SHAPE, "resources/player/hitbox.dae");
        readConvexShape(STRUCTURE_RAMP_SHAPE, "resources/ramp.dae");
        readConvexShape(BIRCH1_COLLIDER1_SHAPE, "resources/structures/environment/Birch/collider1.dae");
        readConvexShape(PLATFORM1_SHAPE, "resources/structures/other/plateform.dae");
        readConvexShape(BIRCH2_COLLIDER_SHAPE, "resources/structures/environment/Birch/collider2.dae");
        readConvexShape(BOAR_HITBOX_SHAPE, "resources/boar/hitbox.dae");
      }

      void deleteConvexShapes()
      {
        delete [] CONVEX_SHAPES;
        CONVEX_SHAPES = NULL;
      }

      void loadRessources()
      {
        TEXTURES = new gdg::Texture[TEXTURES_SIZE];

        MESHES = new gdg::Mesh[MESHES_SIZE];
        ARMATURES = new gdga::Armature[ARMATURES_SIZE];
        ANIMATIONS = new gdga::Animation[ANIMATIONS_SIZE];

        ITEM_ICON_MESHES = new gdg::Mesh[ITEM_ICON_MESHES_SIZE];

        loadTextures();
        createGuiMeshes();
        loadBlocks();
        loadModels();
        loadAnimatedModels();
      }

      void deleteRessources()
      {
        delete [] TEXTURES;
        delete [] MESHES;
        delete [] ARMATURES;
        delete [] ANIMATIONS;
        delete [] ITEM_ICON_MESHES;

        TEXTURES = NULL;
        MESHES = NULL;
        ARMATURES = NULL;
        ANIMATIONS = NULL;
        ITEM_ICON_MESHES = NULL;
      }

      gdg::Texture* getTexture(int id)
      {
        assert(TEXTURES != NULL);
        return TEXTURES + id;
      }

      gdg::Mesh* getMesh(int id)
      {
        assert(MESHES != NULL);
        return MESHES + id;
      }

      const gdga::Armature* getArmature(int id)
      {
        assert(ARMATURES != NULL);
        return ARMATURES + id;
      }

      gdg::Mesh* getItemIconMesh(int id)
      {
        assert(ITEM_ICON_MESHES != NULL);
        return ITEM_ICON_MESHES + id;
      }

      const gdmg::ConvexPolyhedron* getConvexShape(int id)
      {
        assert(CONVEX_SHAPES != NULL);
        return CONVEX_SHAPES + id;
      }

      gdga::Animation* getAnimation(int id)
      {
        assert(ANIMATIONS != NULL);
        return ANIMATIONS + id;
      }
    }
  }
}
