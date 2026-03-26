#include <iostream>
#include <GL/glew.h>
#include <chrono>
#include <thread>
#include <mutex>

#include <math.h>

#include "gddef.h"

#include "graphics/Mesh.h"
#include "graphics/Display.h"
#include "graphics/GeometryLoader.h"
#include "graphics/Shader.h"
#include "graphics/Camera.h"
#include "graphics/animation/Joint.h"
#include "graphics/animation/Armature.h"
#include "graphics/Texture.h"
#include "graphics/TexturedMesh.h"
#include "graphics/MeshModel.h"

#include "math/Matrix.h"
#include "math/Vector.h"
#include "math/Vector3.h"
#include "math/Quaternion.h"
#include "math/Matrix3x3.h"
#include "math/RandomGenerator.h"

#include "utils/ArrayList.h"
#include "utils/ListedArrays.h"

#include "physics/Object.h"

#include "math/geometry/AABB.h"

#include "items/Item.h"
#include "items/ItemStack.h"
#include "items/Inventory.h"
#include "items/Items.h"

#include "voxel/TerrainTexture.h"
#include "voxel/BlockBuilder.h"
#include "voxel/Chunk.h"
#include "voxel/ChunkMesh.h"
#include "voxel/ChunkMeshBuilder.h"
#include "voxel/VoxelPositionCalculator.h"
#include "voxel/Region.h"
#include "voxel/ServerTerrainSimulation.h"
#include "voxel/Terrain.h"
#include "voxel/ChunkGrid.h"
#include "voxel/Materials.h"

#include "utils/OuterSpiralIterator.h"

#include <SDL2/SDL.h>
#include <SDL2/SDL_net.h>
#include "networking/Server.h"
#include "networking/Client.h"
#include "networking/Packet.h"

#include "utils/Pointer.h"
#include "utils/CharArray.h"

#include "client/GameData.h"
#include "client/GameDataManager.h"
#include "client/ObjectData.h"
#include "client/objects/Player.h"
#include "client/objects/MainPlayer.h"
#include "client/listeners/LeftClickListener.h"
#include "client/Players.h"
#include "client/packets/ConnectionPacket.h"
#include "client/packets/RequestSpawnPacket.h"
#include "client/packets/MainPlayerUpdatePacket.h"
#include "client/packets/SelectedInventorySlotPacket.h"
#include "client/packets/UpdateGridPositionPacket.h"

#include "client/listeners/PacketListener.h"
#include "client/listeners/ConnectionPacketListener.h"
#include "client/listeners/MainPlayerSpawnListener.h"
#include "client/listeners/ChunkGeneratedListener.h"
#include "client/listeners/PlayerSpawnListener.h"
#include "client/listeners/PlayerUpdatePacketListener.h"
#include "client/listeners/PlayerDespawnPacketListener.h"
#include "client/listeners/MainPlayerSetItemStackListener.h"
#include "client/listeners/MainPlayerSwapItemStacksListener.h"

#include "server/ServerManager.h"
#include "server/Players.h"
#include "server/GameData.h"
#include "server/GameDataManager.h"
#include "server/ObjectsToUpdate.h"

#include "server/listeners/PacketListener.h"
#include "server/listeners/ConnectionPacketListener.h"
#include "server/listeners/RequestSpawnPacketListener.h"
#include "server/listeners/ClientDisconnectionListener.h"
#include "server/listeners/ClientUpdatePacketListener.h"
#include "server/voxel/TerrainSender.h"

#include "data/Assets.h"
#include "data/ItemAssets.h"

#include "events/Events.h"

#include "Debug.h"

//temp
#include "utils/XMLReader.h"
#include "utils/XMLNode.h"
#include "utils/MeshReader.h"
#include "utils/SkinReader.h"
#include "utils/ArmatureReader.h"
#include "utils/AnimationReader.h"

#include "graphics/animation/ArmatureAnimator.h"

#include "math/geometry/CollisionCalculator.h"
#include "math/geometry/Collider.h"

#include "physics/Simulation.h"
#include "physics/SimulationData.h"
#include "physics/SimulationDataManager.h"
#include "physics/GridSpacePartition.h"

#include "text/FontReader.h"
#include "text/Font.h"
#include "text/LinesBuilder.h"
#include "text/TextBuilder.h"
#include "text/Text.h"
#include "text/TextRenderer.h"
#include "text/Fonts.h"

#include "gui/Frame.h"
#include "gui/TextArea.h"
#include "gui/Gui.h"
#include "gui/Button.h"
#include "gui/Panel.h"
#include "gui/TabButton.h"
#include "gui/VisibilityTabButton.h"
#include "gui/GameTabs.h"

#include "items/InventoryItemSlot.h"
#include "items/InventoryFrame.h"
#include "items/InventoryDisplayBelt.h"
#include "items/PlayerInventoryFrame.h"

#include "ai/pathfinding/Pathfinder.h"

using namespace gt::doubovik;

gdg::TexturedMesh* playerHeadMesh;
gdg::TexturedMesh* playerLegsMesh;
gdg::TexturedMesh* playerFeetMesh;

gdg::TexturedMesh* grassBlockMesh;
gdg::TexturedMesh* pickAxeMesht;

Pointer<gdg::Shader> animationShader;
Pointer<gdg::Shader> basicShader;

bool TERRAIN_FULL_MESH = true;
bool RENDER_SIMULATION_UTILS = false;

void renderAnimatedModel(gdg::Mesh* mesh, gdg::Texture* texture, const gdga::Armature* armature, const gdm::Matrix4x4* transformation)
{
  //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

  gdg::Shader* shader = animationShader.value();
  shader->bind();

  shader->loadVariable(2, *transformation);

  gdm::Matrix4x4 jointsM[100];
  armature->getPose(jointsM);
  shader->loadArray(5, jointsM, 100);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->getId());
  glBindVertexArray(mesh->getVao());
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);

  glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexAmount());

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);
  glBindVertexArray(0);

  //glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void renderAnimatedModel(unsigned int meshId, unsigned int textureId, const gdga::Armature* armature, const gdm::Matrix4x4* transformation)
{
  renderAnimatedModel(gdd::getMesh(meshId), gdd::getTexture(textureId), armature, transformation);
}

void renderModel(const gdg::Mesh* mesh, const gdg::Texture* texture, const gdm::Matrix4x4* transformation)
{
  gdg::Shader* shader = basicShader.value();
  shader->bind();
  shader->loadVariable(2, *transformation);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->getId());
  glBindVertexArray(mesh->getVao());
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexAmount());

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void renderModel(const gdg::TexturedMesh* texturedMesh, const gdm::Matrix4x4* transformation)
{
  renderModel(texturedMesh->mesh, texturedMesh->texture, transformation);
}

void renderModel(unsigned int meshId, unsigned int textureId, const gdm::Matrix4x4* transformation)
{
  renderModel(gdd::getMesh(meshId), gdd::getTexture(textureId), transformation);
}

void renderIndexedModel(const gdg::TexturedMesh* texturedMesh, gdm::Matrix4x4* transformation)
{
  gdg::Shader* shader = basicShader.value();
  shader->loadVariable(2, *transformation);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texturedMesh->texture->getId());
  glBindVertexArray(texturedMesh->mesh->getVao());
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  glDrawElements(GL_TRIANGLES, texturedMesh->mesh->getIndicesAmount(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void renderMeshModel(const gdg::MeshModel* model, gdm::Matrix4x4* transformation)
{
  basicShader.value()->bind();
  const gdg::TexturedMesh mesh = model->getMesh();
  gdm::Matrix4x4 modelTransformation;
  modelTransformation.get(0,3) = model->getPosition().getX();
  modelTransformation.get(1,3) = model->getPosition().getY();
  modelTransformation.get(2,3) = model->getPosition().getZ();
  *transformation = (*transformation)*modelTransformation;
  if(model->getDataType() == gdg::MODEL)
  {
    renderModel(&mesh, transformation);
  }
  else if(model->getDataType() == gdg::INDEXED_MODEL)
  {
    renderIndexedModel(&mesh, transformation);
  }
}

void renderPlayer(gdco::Player* player)
{
  if(player != NULL)
  {
    animationShader.value()->bind();
    const gdm::Matrix4x4* transformation = &player->transformation.toMatrix4x4();
    renderAnimatedModel(gdd::PLAYER_H_HEAD_MESH, gdd::PLAYER_H_HEAD_TEXTURE, &player->getArmature(), transformation);
    renderAnimatedModel(gdd::PLAYER_H_CORE_MESH, gdd::PLAYER_H_CORE_TEXTURE, &player->getArmature(), transformation);
    renderAnimatedModel(gdd::PLAYER_H_LEGS_MESH, gdd::PLAYER_H_LEGS_TEXTURE, &player->getArmature(), transformation);
    renderAnimatedModel(gdd::PLAYER_H_FEET_MESH, gdd::PLAYER_H_FEET_TEXTURE, &player->getArmature(), transformation);

    if(RENDER_SIMULATION_UTILS)
    {
      glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
      renderModel(gdd::PLAYER_H_ENIRONEMENT_HITBOX_MESH, gdd::TERRAIN_ATLAS_TEXTURE, transformation);
      glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
    }

    //render item
    if(!player->getItemInRightHand()->isEmpty())
    {
      gdm::Matrix4x4 itemTransformation = (*transformation)*player->getRightHandTransformation();
      unsigned int itemId = player->getItemInRightHand()->getItemId();
      //renderMeshModel(gdd::getItemModel(itemId), &itemTransformation);
    }
  }
}

void renderPlayers(gdc::Players* players)
{
  for(unsigned int i=0;i<players->getMaxPlayers();i++)
  {
    gdco::Player* player = players->getPlayer(i);
    renderPlayer(player);
  }
}

void renderClient(gdco::MainPlayer* player)
{
  if(player == NULL)
  {
    return;
  }
  const gdm::Matrix4x4* transformation = &player->transformation.toMatrix4x4();

  renderAnimatedModel(gdd::PLAYER_H_CORE_MESH, gdd::PLAYER_H_CORE_TEXTURE, &player->getArmature(), transformation);
  renderAnimatedModel(gdd::PLAYER_H_LEGS_MESH, gdd::PLAYER_H_LEGS_TEXTURE, &player->getArmature(), transformation);
  renderAnimatedModel(gdd::PLAYER_H_FEET_MESH, gdd::PLAYER_H_FEET_TEXTURE, &player->getArmature(), transformation);

  if(!player->getItemInRightHand()->isEmpty())
  {
    gdm::Matrix4x4 itemTransformation = (*transformation)*player->getRightHandTransformation();
    unsigned int itemId = player->getItemInRightHand()->getItemId();
    //renderMeshModel(gdd::getItemModel(itemId), &itemTransformation);
  }
}

void updatePlayer(float timePassed, gdco::Player* player)
{
  if(player != NULL)
  {
    //player->transformation.position = player->transformation.position + player->speed*timePassed;
    player->speed = player->speed + gdm::Vector3(0,-9.81,0)*timePassed;
    player->transformation.rotation = gdm::Quaternion(player->getRotationSpeedAngle()*timePassed, player->getRotationDirection())*player->transformation.rotation;
    player->calculateInformation();

    gdi::ItemStack* itemStack = player->getItemInRightHand();
    gdi::ItemType* itemType = gdi::getItemType(itemStack->getItemId());

    player->update(timePassed);
  }
}

void updatePlayers(float timePassed, gdc::Players* players)
{
  for(unsigned int i=0;i<players->getMaxPlayers();i++)
  {
    gdco::Player* player = players->getPlayer(i);
    updatePlayer(timePassed, player);
  }
}

Pointer<gdg::Shader> loadVoxelShader(const gdm::Matrix4x4& projection)
{
  Pointer<gdg::Shader> shader(new gdg::Shader("shaders/VoxelShader"), false);
  shader.value()->registerVariable("projection");
  shader.value()->registerVariable("camera");
  shader.value()->registerVariable("sunDirection");
  shader.value()->registerVariable("sunColor");
  shader.value()->bind();
  shader.value()->loadVariable(0, projection);
  return shader;
}

void prepareVoxelShader(const Pointer<gdg::Shader>& shader, const gdg::Camera& camera, const gdm::Vector3& sunDirection, const gdm::Vector3& sunColor, const gdg::Texture& terrainAtlas)
{
  shader.value()->bind();
  shader.value()->loadVariable(1, camera.getTransformation());
  shader.value()->loadVariable(2, sunDirection);
  shader.value()->loadVariable(3, sunColor);
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, terrainAtlas.getId());
}

Pointer<gdg::Shader> loadAnimationShader(const gdm::Matrix4x4& projection)
{
  Pointer<gdg::Shader> shader(new gdg::Shader("shaders/AnimationShader"), false);
  shader.value()->registerVariable("projection");
  shader.value()->registerVariable("camera");
  shader.value()->registerVariable("transformation");
  shader.value()->registerVariable("sunDirection");
  shader.value()->registerVariable("sunColor");
  shader.value()->registerArray("joints", 100);
  shader.value()->bind();
  shader.value()->loadVariable(0, projection);
  return shader;
}

Pointer<gdg::Shader> loadBasicShader(const gdm::Matrix4x4& projection)
{
  Pointer<gdg::Shader> shader(new gdg::Shader("shaders/BasicShader"), false);
  shader.value()->registerVariable("projection");
  shader.value()->registerVariable("camera");
  shader.value()->registerVariable("transformation");
  shader.value()->registerVariable("sunDirection");
  shader.value()->registerVariable("sunColor");
  shader.value()->bind();
  shader.value()->loadVariable(0, projection);
  return shader;
}

void prepareAnimationShader(const gdg::Camera& camera, const gdm::Vector3& sunDirection, const gdm::Vector3& sunColor)
{
  gdg::Shader* shader = animationShader.value();
  shader->bind();
  shader->loadVariable(1, camera.getTransformation());
  shader->loadVariable(3, sunDirection);
  shader->loadVariable(4, sunColor);
}

void prepareBasicShader(const gdg::Camera& camera, const gdm::Vector3& sunDirection, const gdm::Vector3& sunColor)
{
  gdg::Shader* shader = basicShader.value();
  shader->bind();
  shader->loadVariable(1, camera.getTransformation());
  shader->loadVariable(3, sunDirection);
  shader->loadVariable(4, sunColor);
}

void renderChunkGrid(const gdv::ChunkGrid* chunkGrid)
{
  if(!TERRAIN_FULL_MESH)
  {
    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  }

  for(int i=0;i<chunkGrid->getSize();i++)
  {
    gdv::ChunkGridNode* node = chunkGrid->getNode(i);
    if(node != NULL)
    {
      //std::cout << "rendering chuck grid node" << std::endl;
      glBindVertexArray(node->mesh->getMesh()->getVao());
      glEnableVertexAttribArray(0);
      glEnableVertexAttribArray(1);
      glEnableVertexAttribArray(2);

      glDrawElements(GL_TRIANGLES, node->mesh->getMesh()->getIndicesAmount(), GL_UNSIGNED_INT, 0);

      glDisableVertexAttribArray(0);
      glDisableVertexAttribArray(1);
      glDisableVertexAttribArray(2);
      glBindVertexArray(0);
    }
  }

  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void updateControls()
{
  if(gdg::isToggledKey(SDLK_TAB))
  {
    gdg::grabMouse();
  }
}

void updateCamera(gdco::MainPlayer* player, gdg::Camera& camera)
{
  if(player == NULL)
  {
    return;
  }
  gdm::Vector3 front = player->getDirection(gdm::Vector3(0,0,-1));
  float angleY = acos(-front.getZ())*(180.0/M_PI);
  if(front.getX() > 0)
  {
    angleY=-angleY;
  }

  camera.getPosition() = player->transformation.toMatrix4x4()*player->getCameraTransformation()*gdm::Vector3();
  camera.getRotation().getY() = angleY;
}

void updateDebugKeys()
{
  if(gdg::isToggledKey(SDLK_m))
  {
    TERRAIN_FULL_MESH = !TERRAIN_FULL_MESH;
  }
  if(gdg::isToggledKey(SDLK_l))
  {
    RENDER_SIMULATION_UTILS = !RENDER_SIMULATION_UTILS;
  }
}

void updatePlayerSpeed(gdco::MainPlayer* player, gdg::Camera& camera)
{
  gdm::Quaternion cameraRotation(camera.getRotation().getY(), gdm::Vector3(0,1,0));

  gdm::Vector3 playerSpeed;
  if(gdg::isPressed(SDLK_z))
  {
    playerSpeed.getZ() = -1.0;
  }
  if(gdg::isPressed(SDLK_s))
  {
    playerSpeed.getZ() = 1.0;
  }
  if(gdg::isPressed(SDLK_SPACE) && player->physicalInformation.onGround)
  {
    player->speed.getY() = 6.0;
  }

  float speed = 6.0;
  playerSpeed = cameraRotation.rotate(playerSpeed);
  playerSpeed.setLength(speed);
  player->speed.getX() = playerSpeed.getX();
  player->speed.getZ() = playerSpeed.getZ();
}

void updatePlayerRotation(float timePassed, gdco::MainPlayer* player, gdg::Camera& camera)
{
  float rotSpeed = 60.0;
  player->rotationSpeed = gdm::Vector3(0,-gdg::MOUSE_MOVE_X*rotSpeed,0);
  camera.getRotation().getX()+= -gdg::MOUSE_MOVE_Y*rotSpeed*timePassed;
}

void updatePlayerData(float timePassed, gdco::MainPlayer* player, gdg::Camera& camera)
{
  if(player == NULL)
  {
    return;
  }

  updateControls();
  updatePlayerSpeed(player, camera);
  updatePlayerRotation(timePassed, player, camera);
}

void sendPlayerData(gdco::MainPlayer* player, gdn::Client* client)
{
  if(player == NULL)
  {
    return;
  }
  //client->sendPacket(gdnp::PlayerLocationPacket(player->position, player->speed, player->rotation, player->rotationSpeed));
  client->sendPacket(gdcp::MainPlayerUpdatePacket(player));
}

void updateMainPlayerModelInHand(gdco::MainPlayer* player)
{
  if(player == NULL)
  {
    return;
  }
}

void enableFaceCulling()
{
  glEnable(GL_CULL_FACE);
  glCullFace(GL_BACK);
}

void disableFaceCulling()
{
  glDisable(GL_CULL_FACE);
}

void renderTrees(const gdv::ChunkGrid* chunkGrid, const gdc::GameDataManager* gameDataManager, int meshId, int textureId)
{

  gdg::Shader* shader = basicShader.value();
  shader->bind();

  gdg::Mesh* mesh = gdd::getMesh(meshId);
  gdg::Texture* texture = gdd::getTexture(textureId);

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, texture->getId());
  glBindVertexArray(mesh->getVao());
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);

  int distance = 5;

  int dx = distance;
  int dy = distance;
  int dz = distance;

  int hwidth = chunkGrid->getHWidth();
  int hheight = chunkGrid->getHHeight();

  if(dx > hwidth)
  {
    dx = hwidth;
  }

  if(dz > hwidth)
  {
    dz = hwidth;
  }

  if(dy > hheight)
  {
    dy = hheight;
  }

  for(int ix=-dx;ix<=dx;ix++)
  {
    for(int iy=-dy;iy<=dy;iy++)
    {
      for(int iz=-dz;iz<=dz;iz++)
      {
        gdv::ChunkGridNode* node = chunkGrid->getNode(hwidth + ix, hheight + iy, hwidth + iz);
        if(node != NULL)
        {
          //std::cout << "rendering chuck grid node" << std::endl;
          ArrayList<int>* trees = &node->structures.trees;
          for(int i =0;i<trees->size();i++)
          {
            int objectId = (*trees)[i];
            gdco::Tree* tree = gameDataManager->getTreesManager()->get(objectId);

            shader->loadVariable(2, tree->transformation.toMatrix4x4());
            glDrawArrays(GL_TRIANGLES, 0, mesh->getVertexAmount());
          }
        }
      }
    }
  }

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glBindVertexArray(0);
}

void renderBoars(const gdv::ChunkGrid* chunkGrid, const gdc::GameDataManager* gameDataManager, float timePassed)
{

  gdg::Shader* shader = animationShader.value();
  shader->bind();

  gdm::Matrix4x4 jointsM[100];


  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::BOAR_TEXTURE)->getId());
  glBindVertexArray(gdd::getMesh(gdd::BOAR_MESH)->getVao());
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);
  glEnableVertexAttribArray(2);
  glEnableVertexAttribArray(3);
  glEnableVertexAttribArray(4);

  int distance = 2;

  int dx = distance;
  int dy = distance;
  int dz = distance;

  int hwidth = chunkGrid->getHWidth();
  int hheight = chunkGrid->getHHeight();

  if(dx > hwidth)
  {
    dx = hwidth;
  }

  if(dz > hwidth)
  {
    dz = hwidth;
  }

  if(dy > hheight)
  {
    dy = hheight;
  }

  for(int ix=-dx;ix<=dx;ix++)
  {
    for(int iy=-dy;iy<=dy;iy++)
    {
      for(int iz=-dz;iz<=dz;iz++)
      {
        gdv::ChunkGridNode* node = chunkGrid->getNode(hwidth + ix, hheight + iy, hwidth + iz);
        if(node != NULL)
        {
          //std::cout << "rendering chuck grid node" << std::endl;
          ArrayList<int>* boars = &node->creatures.boars;
          for(int i=0;i<boars->size();i++)
          {
            int objectId = (*boars)[i];
            gdco::Boar* boar = gameDataManager->getBoarsManager()->get(objectId);

            shader->loadVariable(2, boar->transformation.toMatrix4x4()); //local

            boar->getArmature().getPose(jointsM); //local
            shader->loadArray(5, jointsM, 100); //local

            glDrawArrays(GL_TRIANGLES, 0, gdd::getMesh(gdd::BOAR_MESH)->getVertexAmount());

          }
        }
      }
    }
  }

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glDisableVertexAttribArray(2);
  glDisableVertexAttribArray(3);
  glDisableVertexAttribArray(4);
  glBindVertexArray(0);
}

void renderAABB(const gdmg::AABB& aabb)
{
  gdm::Matrix4x4 transformation;
  transformation.get(0,3) = aabb.minPos.getX();
  transformation.get(1,3) = aabb.minPos.getY();
  transformation.get(2,3) = aabb.minPos.getZ();

  gdm::Vector3 size = aabb.maxPos - aabb.minPos;
  transformation.get(0,0) = size.getX();
  transformation.get(1,1) = size.getY();
  transformation.get(2,2) = size.getZ();

  renderModel(gdd::STRUCTURE_AABB_MESH, gdd::TERRAIN_ATLAS_TEXTURE, &transformation);
}

void renderSimulationUtils(int treeId, gdu::MemoryArray<gdmd::Tree>* trees, gdu::MemoryArray<gdmg::AABB>* aabbs)
{
  gdmd::TreeIterator iterator(&(*trees)[treeId]) ;
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  disableFaceCulling();
  while(iterator.isValid())
  {
    int aabbId = iterator.getNode().aabbId;
    renderAABB((*aabbs)[aabbId]);
    iterator.next();
  }
  glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  enableFaceCulling();
}

Pointer<gdg::Shader> loadTextShader()
{
  Pointer<gdg::Shader> shader(new gdg::Shader("shaders/TextShader"), false);
  shader.value()->registerVariable("screenRatio");
  shader.value()->registerVariable("translation");
  shader.value()->registerVariable("color");
  shader.value()->registerVariable("width");
  shader.value()->registerVariable("borderWidth");
  return shader;
}

void render2DMesh(const gdg::Mesh* mesh)
{
  glBindVertexArray(mesh->getVao());
  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawElements(GL_TRIANGLES, mesh->getIndicesAmount(), GL_UNSIGNED_INT, 0);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);
  glBindVertexArray(0);
}

Pointer<gdg::Shader> loadGuiShader()
{
  Pointer<gdg::Shader> shader(new gdg::Shader("shaders/GuiShader"), false);
  shader.value()->registerVariable("translation");
  shader.value()->registerVariable("scale");
  shader.value()->registerVariable("useFadeOut");
  shader.value()->registerVariable("fadeOutBounds");
  shader.value()->registerVariable("fadeOutBorderSize");
  shader.value()->registerVariable("blendColor");
  shader.value()->registerVariable("colorBlending");
  shader.value()->registerVariable("componentType");
  shader.value()->registerVariable("color");
  shader.value()->registerVariable("textWidth");
  shader.value()->registerVariable("textBorderWidth");
  return shader;
}

void renderFrame(gdg::Shader* shader)
{
  const float borderWidth = 0.01;
  const float borderHeight = borderWidth*(16.0/9.0);
  const float frameWidth = 0.25;
  const float frameHeight = 0.25;

  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::FRAME_CORE_TEXTURE)->getId());
  shader->loadVariable(0, gdm::Vector2(borderWidth, borderHeight));
  shader->loadVariable(1, gdm::Vector2(frameWidth, frameHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_CORE_MESH));

  glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::FRAME_BORDER_TEXTURE)->getId());
  shader->loadVariable(0, gdm::Vector2(0.0, borderHeight));
  shader->loadVariable(1, gdm::Vector2(borderWidth, frameHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_BORDER_L_MESH));

  shader->loadVariable(0, gdm::Vector2(borderWidth, borderHeight + frameHeight));
  shader->loadVariable(1, gdm::Vector2(frameWidth, borderHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_BORDER_B_MESH));

  shader->loadVariable(0, gdm::Vector2(borderWidth + frameWidth, borderHeight));
  shader->loadVariable(1, gdm::Vector2(borderWidth, frameHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_BORDER_R_MESH));

  shader->loadVariable(0, gdm::Vector2(borderWidth, 0.0));
  shader->loadVariable(1, gdm::Vector2(frameWidth, borderHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_BORDER_T_MESH));

  glBindTexture(GL_TEXTURE_2D, gdd::getTexture(gdd::FRAME_CORNER_TEXTURE)->getId());
  shader->loadVariable(0, gdm::Vector2(0.0, 0.0));
  shader->loadVariable(1, gdm::Vector2(borderWidth, borderHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_CORNER_TL_MESH));

  shader->loadVariable(0, gdm::Vector2(0.0, borderHeight + frameHeight));
  shader->loadVariable(1, gdm::Vector2(borderWidth, borderHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_CORNER_BL_MESH));

  shader->loadVariable(0, gdm::Vector2(borderWidth + frameWidth, borderHeight + frameHeight));
  shader->loadVariable(1, gdm::Vector2(borderWidth, borderHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_CORNER_BR_MESH));

  shader->loadVariable(0, gdm::Vector2(borderWidth + frameWidth, 0.0));
  shader->loadVariable(1, gdm::Vector2(borderWidth, borderHeight));
  render2DMesh(gdd::getMesh(gdd::FRAME_CORNER_TR_MESH));
}

void updateInformationText(gdt::Text* text, gdco::MainPlayer* player)
{
  if(player != NULL)
  {
    gdu::String xstr = gdu::String("x: ") + gdu::String(player->transformation.position.getX(), 10);
    gdu::String ystr = gdu::String("y: ") + gdu::String(player->transformation.position.getY(), 10);
    gdu::String zstr = gdu::String("z: ") + gdu::String(player->transformation.position.getZ(), 10);

    gdu::String string = xstr + "\n" + ystr + "\n" + zstr;
    text->setText(string);
  }
}

void updateChunkGridPosition(const gdm::Vector3& playerPosition, gdv::ChunkGrid* chunkGrid, gdn::Client* client)
{
  gdv::VoxelPositionCalculator calculator(playerPosition);
  int cx;
  int cy;
  int cz;
  calculator.calculateChunkCoords(&cx, &cy, &cz);
  gdm::Vector3i position(cx - chunkGrid->getHWidth(), cy - chunkGrid->getHHeight(), cz - chunkGrid->getHWidth());
  if(position != chunkGrid->getPosition())
  {
    chunkGrid->setPosition(position);
    gdcp::UpdateGridPositionPacket packet(position);
    client->sendPacket(packet);
  }
}

bool calculatePath = true;

void testPathfinding(gdco::MainPlayer* player, gdv::ChunkGrid* chunkGrid)
{
  if(!calculatePath)
  {
    return;
  }
  if(player == NULL)
  {
    return;
  }
  gdm::Vector3 position(127, -24, 83);
  gdm::Vector3 toPosition = position - player->transformation.position;
  if(toPosition.getLength() <= 20.0)
  {
    int x = player->transformation.position.getX();
    int y = player->transformation.position.getY();
    int z = player->transformation.position.getZ();
    gdap::Pathfinder pathfinder(chunkGrid, gdm::Vector3i(127, -24, 83), gdm::Vector3i(x, y, z));
    pathfinder.calculatePath();

    const ArrayList<gdm::Vector3i>* path = pathfinder.getPath();

    for(int i=0;i<path->size();i++)
    {
      gdm::Vector3i* position = &(*path)[i];
      gdv::Block* block = chunkGrid->getBlock(position->x, position->y, position->z);

      if(block != NULL)
      {
        block->setMaterial(gdv::RED_BRICKS);
        chunkGrid->updateBlock(position->x, position->y, position->z);
      }
    }

    calculatePath = false;
  }
}

void getObjectsToUpdate(gdv::ChunkGrid* chunkGrid, gdu::LinkedHashList<int>* simulationIds, gdu::LinkedHashList<int>* boarIds, gdc::GameDataManager* gameDataManager)
{
  int distance = 3;

  int dx = distance;
  int dy = distance;
  int dz = distance;

  int hwidth = chunkGrid->getHWidth();
  int hheight = chunkGrid->getHHeight();

  if(dx > hwidth)
  {
    dx = hwidth;
  }

  if(dz > hwidth)
  {
    dz = hwidth;
  }

  if(dy > hheight)
  {
    dy = hheight;
  }

  for(int ix=-dx;ix<=dx;ix++)
  {
    for(int iy=-dy;iy<=dy;iy++)
    {
      for(int iz=-dz;iz<=dz;iz++)
      {
        gdv::ChunkGridNode* node = chunkGrid->getNode(hwidth + ix, hheight + iy, hwidth + iz);
        if(node != NULL)
        {
          //std::cout << "rendering chuck grid node" << std::endl;
          ArrayList<int>* boars = &node->creatures.boars;
          for(int i=0;i<boars->size();i++)
          {
            int objectId = (*boars)[i];
            boarIds->add(objectId);
            int simulationId = gameDataManager->getBoarsManager()->getSimulationId(objectId);
            simulationIds->add(simulationId);
          }
        }
      }
    }
  }
}

void updateBoars(gdc::GameDataManager* gameDataManager, gdv::ChunkGrid* chunkGrid, gdu::LinkedHashList<int>* boars)
{
  gdu::ConstLinkedHashListIterator<int> iterator(boars);
  while(iterator.isValid())
  {
    int objectId = iterator.value();

    gdco::Boar* boar = gameDataManager->getBoarsManager()->get(objectId);

    int bx;
    int by;
    int bz;
    gdv::toBlockCoords(boar->transformation.position.getX(), boar->transformation.position.getY(), boar->transformation.position.getZ(), &bx, &by, &bz);
    gdm::Vector3i newChunkPosition;
    gdv::blockCoordsToChunkCoords(bx, by, bz, &newChunkPosition.x, &newChunkPosition.y, &newChunkPosition.z);

    const gdm::Vector3i* chunkPosition = gameDataManager->getBoarsManager()->getChunkPosition(objectId);

    if(*chunkPosition != newChunkPosition)
    {
      chunkGrid->removeBoar(objectId, *chunkPosition);
      chunkGrid->addBoar(objectId, newChunkPosition);
      gameDataManager->getBoarsManager()->setChunkPosition(objectId, newChunkPosition);
    }


    iterator.next();
  }
}

void runClient(const char* ip)
{
  const unsigned int WINDOW_WIDTH = 1760;
  const unsigned int WINDOW_HEIGHT = 990;

  gdgui::WINDOW_WIDTH = WINDOW_WIDTH;
  gdgui::WINDOW_HEIGHT = WINDOW_HEIGHT;

  std::cout << "starting v2 of Client" << std::endl;

  std::cout << "initialising graphics..." << std::endl;

  gdg::initDisplay("Mine Fabrik", WINDOW_WIDTH, WINDOW_HEIGHT);

  std::cout << "Loading ressources..." << std::endl;

  gdt::loadFonts();
  gdd::loadConvexShapes();
  gdd::loadRessources();
  gdd::createItemAssets();


  gdi::createItemTypes();
  gde::createMainEventHandler();

  std::cout << "preparing variables..." << std::endl;

  gdg::Mesh* modelMesh = gdd::getMesh(gdd::PLAYER_H_CORE_MESH);
  gdg::Texture modelTexture(gdg::loadTexture("resources/stone_pickaxe.png"));
  gdg::TexturedMesh modelTexturedMesh(modelMesh, &modelTexture);
  gdga::Armature modelArmature = *gdd::getArmature(gdd::PLAYER_ARMATURE);

  gdga::Joint* bottomJoint = modelArmature.getJoint("Colonne_vertebrale_5");
  ArrayList<unsigned int> bottomJointIds;
  bottomJoint->getChildrenIds(&bottomJointIds);

  gdga::ArmatureAnimator animator(bottomJointIds, gdd::getAnimation(gdd::PLAYER_RUN_ANIMATION));


  gdga::Armature boarArmature = *gdd::getArmature(gdd::BOAR_ARMATURE);
  gdga::Joint* boarRootJoint = boarArmature.getJoint("Bone");
  ArrayList<unsigned int> boarJointIds;
  boarRootJoint->getChildrenIds(&boarJointIds);

  gdga::ArmatureAnimator boarAnimator(boarJointIds, gdd::getAnimation(gdd::BOAR_IDLE_ANIMATION));

  std::cout << "connecting..." << std::endl;

  gdc::Players players;

  gdg::Texture terrainAtlas(gdg::loadTexture("resources/terrain/atlas.png"));
  gdv::TerrainTexture terrainTexture(20, 20, &terrainAtlas);
  gdv::BlockBuilder blockBuilder(&terrainTexture);

  gdu::MemoryArray<gdp::ObjectSimulationData> simulationObjects;
  gdu::MemoryArray<gdmd::Tree> boundingTrees;
  gdu::MemoryArray<gdmg::AABB> aabbs;

  gdp::GridSpacePartition terrainSimulationGrid((float)gdv::CHUNK_SIZE, &boundingTrees, &aabbs);
  gdp::GridSpacePartition objectsSimulationGrid(8.0*(float)(gdv::CHUNK_SIZE), &boundingTrees, &aabbs);

  gdp::Simulation simulation(&simulationObjects, &boundingTrees, &aabbs, &terrainSimulationGrid, &objectsSimulationGrid);

  gdp::SimulationData simulationData;
  simulationData.simulation = &simulation;
  simulationData.objects = &simulationObjects;
  simulationData.aabbs = &aabbs;
  gdp::SimulationDataManager simulationDataManager(&simulationData);

  gdc::GameData gameData;
  gdc::GameDataManager gameDataManager(&gameData, &simulationDataManager);

  gdn::Client client(ip, 1235);

  gdv::ChunkGrid chunkGrid(&blockBuilder, &simulationDataManager, &terrainSimulationGrid, &client, &gameDataManager);

  gdm::Matrix4x4 projection(WINDOW_WIDTH, WINDOW_HEIGHT, 90, 90, 0.05, 5000);
  std::cout << "loading shaders:" << std::endl;
  Pointer<gdg::Shader> voxelShader = loadVoxelShader(projection);
  animationShader = loadAnimationShader(projection);
  basicShader = loadBasicShader(projection);

  Pointer<gdg::Shader> textShader = loadTextShader();
  Pointer<gdg::Shader> guiShader = loadGuiShader();

  gdt::TextRenderer textRenderer(textShader.value());
  gdgui::TEXT_RENDERER = &textRenderer;
  gdgui::GUI_SHADER = guiShader.value();

  gdg::Mesh blockMesh;
  blockBuilder.getBlock(0.114, 1, &blockMesh);
  gdg::TexturedMesh texturedBlockMesh(&blockMesh, &terrainAtlas);
  grassBlockMesh = &texturedBlockMesh;

  gdg::Camera camera(gdm::Vector3(160 ,63, 160));
  gdm::Vector3 sunDirection(2.0,-3.0,1.0);
  sunDirection.normalize();
  gdm::Vector3 sunColor(1.0, 1.0, 1.0);

  //fonts & text
  gdu::String string("Sample text! Lelz");

  gdt::Text text(gdt::getFont(gdt::DEFAULT_FONT), 1.0, 0.5, true);
  text.position.x = 0.5;
  text.position.y = 0.65;
  text.width = 0.5;
  text.borderWidth = 0.05;
  text.color = gdm::Vector3(0.51, 0.0, 0.51);
  text.setText(string);

  //gui
  gdgui::Frame frame(gdm::Vector2(0.2, 0.2), gdm::Vector2(0.3, 0.4));
  frame.setVisible(false);
  gdgui::Panel panel(gdm::Vector2(0.0, 0.1), gdm::Vector2(0.3, 0.3));
  frame.addComponent(&panel);

  gdgui::TextArea textArea(gdm::Vector2(), gdm::Vector2(0.3, 0.2), gdt::getFont(gdt::DEFAULT_FONT), 0.06, true);
  textArea.setText(gdu::String("Ceci est une zone de text! Qui ne depassera pas de ce cadre, enfin j'espere... Au pire on verra bien le rendu lelz, *dabing intensifies* Je peux meme centrer ce text avec le parametre true, ce pave parrait long pour un test mais il permet de verifier que le retour a la ligne se fait corectement! (il y a surement des fautes d'orthographe, mais osef)"));
  textArea.setTextColor(gdm::Vector3(1.0, 1.0, 1.0));
  panel.addComponent(&textArea);

  gdgui::Button button1(gdm::Vector2(0.1, 0.2), gdm::Vector2(0.1, 0.05));
  gdgui::Button button2(gdm::Vector2(0.1, 0.3), gdm::Vector2(0.1, 0.05));
  gdgui::Button button3(gdm::Vector2(0.1, 0.4), gdm::Vector2(0.1, 0.05));
  gdgui::Button button4(gdm::Vector2(0.1, 0.5), gdm::Vector2(0.1, 0.1));

  panel.addComponent(&button1);
  panel.addComponent(&button2);
  panel.addComponent(&button3);
  panel.addComponent(&button4);

  gdgui::addGuiComponent(&frame);

  gdi::InventoryFrame inventoryFrame;
  inventoryFrame.setVisible(false);
  gdgui::addGuiComponent(&inventoryFrame);

  gdi::PlayerInventoryFrame playerInventoryFrame;
  playerInventoryFrame.setVisible(false);
  gdgui::addGuiComponent(&playerInventoryFrame);

  gdgui::TabButton* activeTabButton = NULL;
  const float TAB_BUTTON_SIZE = 0.065;
  gdgui::VisibilityTabButton tabButton1(&playerInventoryFrame, gdd::INVENTORY_BUTTON_TEXTURE, gdm::Vector2(0.01, 0.01), gdm::Vector2(TAB_BUTTON_SIZE, TAB_BUTTON_SIZE*(16.0/9.0)), &activeTabButton);
  gdgui::VisibilityTabButton tabButton2(&playerInventoryFrame, gdd::CRAFTING_BUTTON_TEXTURE, gdm::Vector2(0.01, 0.12), gdm::Vector2(TAB_BUTTON_SIZE, TAB_BUTTON_SIZE*(16.0/9.0)), &activeTabButton);
  gdgui::VisibilityTabButton tabButton3(&frame, gdd::CRAFTING_BUTTON_TEXTURE, gdm::Vector2(0.01, 0.24), gdm::Vector2(TAB_BUTTON_SIZE, TAB_BUTTON_SIZE*(16.0/9.0)), &activeTabButton);
  gdgui::VisibilityTabButton tabButton4(&frame, gdd::CRAFTING_BUTTON_TEXTURE, gdm::Vector2(0.01, 0.24), gdm::Vector2(TAB_BUTTON_SIZE, TAB_BUTTON_SIZE*(16.0/9.0)), &activeTabButton);
  gdgui::VisibilityTabButton tabButton5(&frame, gdd::SKILLS_BUTTON_TEXTURE, gdm::Vector2(0.01, 0.24), gdm::Vector2(TAB_BUTTON_SIZE, TAB_BUTTON_SIZE*(16.0/9.0)), &activeTabButton);

  ArrayList<gdgui::GuiComponent*> gameTabsComponents;
  gameTabsComponents.add(&tabButton1);
  gameTabsComponents.add(&tabButton2);
  gameTabsComponents.add(&tabButton3);
  gameTabsComponents.add(&tabButton4);
  gameTabsComponents.add(&tabButton5);
  gdgui::GameTabs gameTabs(gdm::Vector2(0.0, 0.0), gdm::Vector2(0.15, 1.0));
  gameTabs.setComponents(gameTabsComponents);
  gdgui::addGuiComponent(&gameTabs);

  gdi::InventoryDisplayBelt inventoryDisplayBelt(gdm::Vector2(0.37, 0.8), gdm::Vector2(0.26, 0.2));
  gdgui::addGuiComponent(&inventoryDisplayBelt);

  gdi::addSelectedItemSlotDisplayToGui();

  std::cout << "registering listeners..." << std::endl;
  gdcl::LeftClickListener leftClickListener(&client, &players, &camera, &chunkGrid);
  gde::registerListener(&leftClickListener);

  gdcl::PacketListener packetListener(&client, &players, &chunkGrid, &gameDataManager);
  gde::registerListener(&packetListener);

  gdcl::ConnectionPacketListener connectionPacketListener(&client, &players);
  gde::registerListener(&connectionPacketListener);

  gdcl::MainPlayerSpawnListener mainPlayerSpawnListener(&players, &playerInventoryFrame, &inventoryDisplayBelt);
  gde::registerListener(&mainPlayerSpawnListener);

  gdcl::ChunkGeneratedListener chunkGeneratedListener(&chunkGrid);
  gde::registerListener(&chunkGeneratedListener);

  gdcl::PlayerSpawnListener playerSpawnListener(&players);
  gde::registerListener(&playerSpawnListener);

  gdcl::PlayerUpdatePacketListener playerUpdatePacketListener(&players);
  gde::registerListener(&playerUpdatePacketListener);

  gdcl::PlayerDespawnPacketListener playerDespawnPacketListener(&players);
  gde::registerListener(&playerDespawnPacketListener);

  gdcl::MainPlayerSetItemStackListener mainPlayerSetItemStackListener(&players);
  gde::registerListener(&mainPlayerSetItemStackListener);

  gdcl::MainPlayerSwapItemStacksListener mainPlayerSwapItemStacksListener(&client);
  gde::registerListener(&mainPlayerSwapItemStacksListener);

  //TESTS
  gdp::Object cube1(gdm::Vector3(160,14,160));
  cube1.physicalInformation.moveable = true;
  cube1.physicalInformation.mass = 100.0;
  cube1.physicalInformation.setBoxIntertiaMatrix(1.0, 1.0, 1.0);
  cube1.collider = gdd::getConvexShape(gdd::CUBE_SHAPE);

  gdp::Object cube2(gdm::Vector3(145, 14.7, 160.7));
  gdp::Object tree(gdm::Vector3(160, 9, 171));
  tree.physicalInformation.moveable = false;
  tree.collider = gdd::getConvexShape(gdd::BIRCH1_COLLIDER1_SHAPE);
  gdp::Object ramp(gdm::Vector3(140, 0, 171));
  ramp.physicalInformation.moveable = false;
  ramp.collider = gdd::getConvexShape(gdd::STRUCTURE_RAMP_SHAPE);
  ramp.calculateInformation();
  cube2.speed = gdm::Vector3(1,0,0);
  cube2.physicalInformation.mass = 0.5;
  cube2.physicalInformation.setBoxIntertiaMatrix(1.0, 1.0, 1.0);

  gdp::Object cube3(gdm::Vector3(164, 35, 160));
  cube3.physicalInformation.mass = 60.0;
  cube3.physicalInformation.setBoxIntertiaMatrix(1.0, 1.0, 1.0);
  cube3.physicalInformation.useGravity = true;
  cube3.collider = gdd::getConvexShape(gdd::CUBE_SHAPE);
  //gdp::Object cube2(gdm::Vector3(140, 14, 160));
  //cube2.speed = gdm::Vector3(1,0,0);

  gdm::Vector3 rotationDirection(1,1,0);
  rotationDirection.normalize();
  //cube1.transformation.rotation = gdm::Quaternion(131.0, rotationDirection);
  cube2.collider = gdd::getConvexShape(gdd::CUBE_SHAPE);

  cube1.calculateInformation();
  cube2.calculateInformation();

  gdp::Object spawnPlatform(gdm::Vector3(164, 25, 164));
  spawnPlatform.physicalInformation.moveable = false;
  spawnPlatform.collider = gdd::getConvexShape(gdd::PLATFORM1_SHAPE);

  int cube1SimulationId = simulationDataManager.createSimulationData(&cube1);
  simulation.add(cube1SimulationId);

  int cube2SimulationId = simulationDataManager.createSimulationData(&cube2);
  simulation.add(cube2SimulationId);

  int cube3SimulationId = simulationDataManager.createSimulationData(&cube3);
  simulation.add(cube3SimulationId);

  simulation.addStructure(simulationDataManager.createSimulationData(&ramp));
  simulation.addStructure(simulationDataManager.createSimulationData(&tree));
  simulation.addStructure(simulationDataManager.createSimulationData(&spawnPlatform));

  //unsigned int cube1ID = collisionManager.add(gdmg::Collider(&gdd::getConvexShape(gdd::CUBE_SHAPE), &cube1.transformation, &cube1.speed, &cube1.physicalInformation));
  //unsigned int cube2ID = collisionManager.add(gdmg::Collider(&gdd::getConvexShape(gdd::CUBE_SHAPE), &cube2.transformation, &cube2.speed, &cube2.physicalInformation));
  //unsigned int rampId = collisionManager.add(gdmg::Collider(&gdd::getConvexShape(gdd::STRUCTURE_RAMP_HITBOX), &ramp.transformation, &ramp.speed, &ramp.physicalInformation));
  unsigned int playerColliderId = -1;

  gdt::Text fpsText(gdt::getFont(gdt::DEFAULT_FONT), 0.20, 0.5, false);
  fpsText.position.x = 0.01;
  fpsText.color = gdm::Vector3(0.75, 0.9, 0.4);
  gdt::Text informationText(gdt::getFont(gdt::DEFAULT_FONT), 0.15, 0.5, false);
  informationText.position.x = 0.01;
  informationText.position.y+=(gdt::getFont(gdt::DEFAULT_FONT)->getLineHeight()*0.2);

  //END TESTS

  client.sendPacket(gdcp::ConnectionPacket()); //requesting connection!


  int FPS_TIME = 16666666;

  float secondsTimeCount = 0.0;
  int fps = 0;

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  while(client.isConnected() && !gdg::DISPLAY_WINDOW_CLOSED)
  {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int timePassedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    float timePassed = ((float)timePassedNs)/(1000000000.0);
    start = now;

    secondsTimeCount+=timePassed;
    fps++;
    if(secondsTimeCount >= 1.0)
    {
      std::cout << "--------" << std::endl;
      std::cout << "FPS: [" << fps << "]" << std::endl;
      std::cout << "--------" << std::endl;
      gdu::String fpsString = gdu::String("FPS: ") + gdu::String(fps, 10);
      std::cout << fpsString << std::endl;
      fpsText.setText(fpsString);
      secondsTimeCount = 0.0;
      fps = 0;

      chunkGrid.requestNextChunks();
    }

    gdgui::WINDOW_WIDTH = WINDOW_WIDTH;
    gdgui::WINDOW_HEIGHT = WINDOW_HEIGHT;

    gdgui::MOUSE_MOVE_X = gdgui::MOUSE_X;
    gdgui::MOUSE_MOVE_Y = gdgui::MOUSE_Y;
    gdgui::MOUSE_X = (float)(gdg::MOUSE_X)/(float)(WINDOW_WIDTH);
    gdgui::MOUSE_Y = (float)(gdg::MOUSE_Y)/(float)(WINDOW_HEIGHT);
    gdgui::MOUSE_MOVE_X = gdgui::MOUSE_X - gdgui::MOUSE_MOVE_X;
    gdgui::MOUSE_MOVE_Y = gdgui::MOUSE_Y - gdgui::MOUSE_MOVE_Y;

    gdgui::MOUSE_SCROLL_X = (float)(gdg::MOUSE_SCROLL_X)*0.03;
    gdgui::MOUSE_SCROLL_Y = (float)(gdg::MOUSE_SCROLL_Y)*0.03;

    if(gdg::mouseGrabed())
    {
      if(gdg::MOUSE_SCROLL_Y > 0)
      {
        inventoryDisplayBelt.previous();

        gdco::MainPlayer* player = players.getMainPlayer();
        if(player != NULL)
        {
          client.sendPacket(gdcp::SelectedInventorySlotPacket(inventoryDisplayBelt.getSelectedSlot()));
          player->setSelectedSlot(inventoryDisplayBelt.getSelectedSlot());
          player->onItemEquip();
        }

      }
      else if(gdg::MOUSE_SCROLL_Y < 0)
      {
        inventoryDisplayBelt.next();

        gdco::MainPlayer* player = players.getMainPlayer();
        if(player != NULL)
        {
          client.sendPacket(gdcp::SelectedInventorySlotPacket(inventoryDisplayBelt.getSelectedSlot()));
          player->setSelectedSlot(inventoryDisplayBelt.getSelectedSlot());
          player->onItemEquip();
        }

      }
    }

    gdgui::MOUSE_LEFT_BUTTON_PRESSED = gdg::isToggledMouseButton(SDL_BUTTON_LEFT);
    gdgui::MOUSE_RIGHT_BUTTON_PRESSED = gdg::isToggledMouseButton(SDL_BUTTON_RIGHT);


    //*****************************************************************************************
    //start [update]
    updateDebugKeys();

    updatePlayerData(timePassed, players.getMainPlayer(), camera);
    if(players.getMainPlayer() != NULL && playerColliderId ==  -1)
    {
      players.getMainPlayer()->collider = gdd::getConvexShape(gdd::PLAYER_H_ENIRONEMENT_HITBOX_SHAPE);
      playerColliderId = simulationDataManager.createSimulationData(players.getMainPlayer());
      simulation.add(playerColliderId);
    }


    client.update(timePassed);

    updatePlayers(timePassed, &players);


    if(players.getMainPlayer() != NULL)
    {
      updateChunkGridPosition(players.getMainPlayer()->transformation.position, &chunkGrid, &client);
    }
    //std::cout << "loading next grid collider" << std::endl;
    chunkGrid.loadNextCollider();
    //std::cout << "loading next grid mesh" << std::endl;
    chunkGrid.loadNextMesh();
    //std::cout << "loading next grid done!" << std::endl;

    gdu::LinkedHashList<int> objectsToUpdate;
    if(playerColliderId != -1)
    {
      objectsToUpdate.add(playerColliderId);
    }

    objectsToUpdate.add(cube1SimulationId);
    objectsToUpdate.add(cube2SimulationId);
    objectsToUpdate.add(cube3SimulationId);

    std::cout << "updating objects..." << std::endl;
    gdu::LinkedHashList<int> boarsToUpdate;

    std::cout << "getting objects..." << std::endl;
    getObjectsToUpdate(&chunkGrid, &objectsToUpdate, &boarsToUpdate, &gameDataManager);

    std::cout << "updating simulation..." << std::endl;
    simulation.update(timePassed, &objectsToUpdate);
    std::cout << "updating boars..." << std::endl;
    updateBoars(&gameDataManager, &chunkGrid, &boarsToUpdate);
    std::cout << "done updating objects..." << std::endl;

    updateCamera(players.getMainPlayer(), camera);

    updateMainPlayerModelInHand(players.getMainPlayer());

    sendPlayerData(players.getMainPlayer(), &client);

    testPathfinding(players.getMainPlayer(), &chunkGrid);

    std::chrono::system_clock::time_point endUpdateTime = std::chrono::system_clock::now();
    int updateTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endUpdateTime - start).count();
    //end [update]


    gdg::clearDisplay(0.498,0.87,1.0,0);
    //start [render]
    updateInformationText(&informationText, players.getMainPlayer());

    prepareVoxelShader(voxelShader, camera, sunDirection, sunColor, terrainAtlas);

    std::cout << "rendering grid..." << std::endl;
    renderChunkGrid(&chunkGrid);
    std::cout << "rendering grid done!" << std::endl;

    gdm::Matrix4x4 transformation;
    transformation.get(0,3) = 160;
    transformation.get(1,3) = 14;
    transformation.get(2,3) = 164;

    animator.update(timePassed);
    gdga::JointPose pose[modelArmature.getJointAmount()];
    animator.getPose(pose);
    modelArmature.applyPose(pose);

    prepareAnimationShader(camera, sunDirection, sunColor);

    renderBoars(&chunkGrid, &gameDataManager, timePassed);

    renderAnimatedModel(gdd::PLAYER_H_HEAD_MESH, gdd::PLAYER_H_HEAD_TEXTURE, &modelArmature, &transformation);
    renderAnimatedModel(gdd::PLAYER_H_CORE_MESH, gdd::PLAYER_H_CORE_TEXTURE, &modelArmature, &transformation);
    renderAnimatedModel(gdd::PLAYER_H_LEGS_MESH, gdd::PLAYER_H_LEGS_TEXTURE, &modelArmature, &transformation);
    renderAnimatedModel(gdd::PLAYER_H_FEET_MESH, gdd::PLAYER_H_FEET_TEXTURE, &modelArmature, &transformation);

    boarAnimator.update(timePassed);
    gdga::JointPose boarPose[boarArmature.getJointAmount()];
    boarAnimator.getPose(boarPose);
    boarArmature.applyPose(boarPose);

    transformation.get(0,3) = 160;
    transformation.get(1,3) = -12.0;
    transformation.get(2,3) = 164;

    transformation.get(0,0) = 0.3;
    transformation.get(1,1) = 0.3;
    transformation.get(2,2) = 0.3;

    renderAnimatedModel(gdd::BOAR_MESH, gdd::BOAR_TEXTURE, &boarArmature, &transformation);

    prepareBasicShader(camera, sunDirection, sunColor);
    renderPlayers(&players);

    transformation.get(0,3)+=4;

    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    renderModel(gdd::PLAYER_H_HEAD_MESH, gdd::PLAYER_H_HEAD_TEXTURE, &transformation);
    renderModel(gdd::PLAYER_H_CORE_MESH, gdd::PLAYER_H_CORE_TEXTURE, &transformation);
    renderModel(gdd::PLAYER_H_LEGS_MESH, gdd::PLAYER_H_LEGS_TEXTURE, &transformation);
    renderModel(gdd::PLAYER_H_FEET_MESH, gdd::PLAYER_H_FEET_TEXTURE, &transformation);

    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);



    if(RENDER_SIMULATION_UTILS)
    {
      //renderSimulationUtils(simulation.getMainTreeId(), &boundingTrees, &aabbs);
    }

    //gdm::Vector3 rotationDirection(1,1,0);
    //rotationDirection.normalize();
    //cube2.rotation = gdm::Quaternion(5.0*timePassed, rotationDirection)*cube2.rotation;



    const gdm::Matrix4x4* transformation1 = &cube1.transformation.toMatrix4x4();
    const gdm::Matrix4x4* iTransformation1 = &cube1.transformation.getILinearTransformation();
    const gdm::Matrix4x4* transformation2 = &cube2.transformation.toMatrix4x4();
    const gdm::Matrix4x4* iTransformation2 = &cube2.transformation.getILinearTransformation();
    gdmg::CollisionCalculator collisionCalculator(transformation1, iTransformation1, transformation2, iTransformation2, &cube1.speed, &cube2.speed);
    //gdm::Vector3 location(0,0,0);
    //gdmg::SupportVertex point = collisionCalculator.getDistance(&location, gdd::getConvexShape(gdd::CUBE_SHAPE), gdd::getConvexShape(gdd::CUBE_SHAPE));
    //float distance = (location - point.getMDifference()).getLength();
    //std::cout << "distance: " << distance << std::endl;


    renderModel(gdd::CRATE1_MESH, gdd::CRATE1_TEXTURE, transformation1);
    renderModel(gdd::CRATE1_MESH, gdd::CRATE1_TEXTURE, transformation2);
    renderModel(gdd::CRATE1_MESH, gdd::CRATE1_TEXTURE, &cube3.transformation.toMatrix4x4());

    disableFaceCulling();
    renderModel(gdd::BIRCH1_TREE_MESH, gdd::BIRCH1_TREE_TEXTURE, &tree.transformation.toMatrix4x4());
    renderModel(gdd::BIRCH1_LEAVES1_MESH, gdd::BIRCH1_LEAVES1_TEXTURE, &tree.transformation.toMatrix4x4());
    renderModel(gdd::BIRCH1_LEAVES2_MESH, gdd::BIRCH1_LEAVES2_TEXTURE, &tree.transformation.toMatrix4x4());
    renderModel(gdd::BIRCH1_LEAVES3_MESH, gdd::BIRCH1_LEAVES3_TEXTURE, &tree.transformation.toMatrix4x4());
    renderModel(gdd::BIRCH1_LEAVES4_MESH, gdd::BIRCH1_LEAVES4_TEXTURE, &tree.transformation.toMatrix4x4());
    enableFaceCulling();

    renderTrees(&chunkGrid, &gameDataManager, gdd::BIRCH2_TREE_MESH, gdd::BIRCH1_TREE_TEXTURE);
    disableFaceCulling();
    renderTrees(&chunkGrid, &gameDataManager, gdd::BIRCH2_LEAVES1_MESH, gdd::BIRCH1_LEAVES1_TEXTURE);
    renderTrees(&chunkGrid, &gameDataManager, gdd::BIRCH2_LEAVES2_MESH, gdd::BIRCH1_LEAVES2_TEXTURE);
    renderTrees(&chunkGrid, &gameDataManager, gdd::BIRCH2_LEAVES3_MESH, gdd::BIRCH1_LEAVES3_TEXTURE);
    renderTrees(&chunkGrid, &gameDataManager, gdd::BIRCH2_LEAVES4_MESH, gdd::BIRCH1_LEAVES4_TEXTURE);
    enableFaceCulling();


    renderModel(gdd::STRUCTURE_RAMP_MESH, gdd::TERRAIN_ATLAS_TEXTURE, &ramp.transformation.toMatrix4x4());

    renderModel(gdd::PLATFORM1_MESH, gdd::TERRAIN_ATLAS_TEXTURE, &spawnPlatform.transformation.toMatrix4x4());


    renderClient(players.getMainPlayer());

    glDisable(GL_DEPTH_TEST);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    glEnable(GL_SCISSOR_TEST);
    glScissor(0,0, WINDOW_WIDTH, WINDOW_HEIGHT);

    if(!gdg::mouseGrabed())
    {
      gdgui::updateGuiInput();
    }
    gdgui::updateGui(timePassed);
    gdgui::renderGui();

    glDisable(GL_SCISSOR_TEST);

    textRenderer.prepare(16.0/9.0);
    textRenderer.bindShader();
    textRenderer.render(fpsText);
    textRenderer.render(informationText);

    glDisable(GL_BLEND);
    glEnable(GL_DEPTH_TEST);

    //end [render]

    gdg::updateDisplay();

    std::chrono::system_clock::time_point endRenderTime = std::chrono::system_clock::now();
    int renderTime = std::chrono::duration_cast<std::chrono::nanoseconds>(endRenderTime - endUpdateTime).count();

    float updateTimeSec = (float)updateTime/1000000000.0;
    float renderTimeSec = (float)renderTime/1000000000.0;
    std::cout << "update time: " << updateTime << " : " << updateTimeSec << std::endl;
    std::cout << "render time: " << renderTime << " : " << renderTimeSec << std::endl;
    std::cout << "total time: " << updateTimeSec + renderTimeSec << " target: " << 1.0/60.0 << std::endl;

    //*****************************************************************************************
    now = std::chrono::system_clock::now();
    int processTime = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    int toWait = FPS_TIME - processTime;
    if(toWait < 0)
    {
      toWait = 0;
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(toWait));
  }

  //deleting game data
  gdi::deleteItemTypes();
  gde::deleteMainEventHandler();
  gdt::deleteFonts();

  gdd::deleteItemAssets();
  gdd::deleteRessources();
  gdd::deleteConvexShapes();

  gdg::cleanDisplay();

  std::cout << "after all" << std::endl;
}

void barycenterTest(const gdm::Vector3& OA, const gdm::Vector3& OB, const gdm::Vector3& OC, const gdm::Vector3& OD, float* u, float* v, float* w, float* k)
{
  gdm::Vector3 AB = OB - OA;
  gdm::Vector3 AC = OC - OA;
  gdm::Vector3 AD = OD - OA;
  gdm::Vector3 AO = -OA;

  float ABAB = AB.dot(AB);
  float ACAC = AC.dot(AC);
  float ADAD = AD.dot(AD);

  float ABAC = AB.dot(AC);
  float ABAD = AB.dot(AD);

  float ACAD = AC.dot(AD);

  float AOAB = AO.dot(AB);
  float AOAC = AO.dot(AC);
  float AOAD = AO.dot(AD);

  float detA  = - ABAB*(ACAC*ADAD - ACAD*ACAD)
                + ABAC*(ABAC*ADAD - ACAD*ABAD)
                - ABAD*(ABAC*ACAD - ACAC*ABAD);

  float detAv = - AOAB*(ACAC*ADAD - ACAD*ACAD)
                + AOAC*(ABAC*ADAD - ACAD*ABAD)
                - AOAD*(ABAC*ACAD - ACAC*ABAD);

  float detAw = - ABAB*(AOAC*ADAD - AOAD*ACAD)
                + ABAC*(AOAB*ADAD - AOAD*ABAD)
                - ABAD*(AOAB*ACAD - AOAC*ABAD);

  float detAk = - ABAB*(ACAC*AOAD - ACAD*AOAC)
                + ABAC*(ABAC*AOAD - ACAD*AOAB)
                - ABAD*(ABAC*AOAC - ACAC*AOAB);

  float denom = 1.0/detA;

  *v = detAv*denom;
  *w = detAw*denom;
  *k = detAk*denom;
  *u = 1.0 - *v - *w - *k;
}

void sendUpdatedObjects(gds::ServerManager* serverManager, gds::GameDataManager* gameDataManager, gds::ObjectsToUpdate* objectsToUpdate)
{
  for(int i=0;i<objectsToUpdate->boars.size();i++)
  {
    int objectId = objectsToUpdate->boars[i];
    serverManager->sendUpdateBoarPacket(gameDataManager, objectId);
  }
}

void updateBoars(gds::GameDataManager* gameDataManager, gdv::Terrain* terrain, ArrayList<int>* boars)
{
  for(int i=0;i<boars->size();i++)
  {
    int objectId = (*boars)[i];

    gdso::Boar* boar = gameDataManager->getBoar(objectId);

    int bx;
    int by;
    int bz;
    gdv::toBlockCoords(boar->transformation.position.getX(), boar->transformation.position.getY(), boar->transformation.position.getZ(), &bx, &by, &bz);
    gdm::Vector3i newChunkPosition;
    gdv::blockCoordsToChunkCoords(bx, by, bz, &newChunkPosition.x, &newChunkPosition.y, &newChunkPosition.z);

    const gdm::Vector3i* chunkPosition = gameDataManager->getBoarsManager()->getChunkPosition(objectId);
    if(newChunkPosition != *chunkPosition)
    {
      terrain->removeBoar(*chunkPosition, objectId);
      terrain->addBoar(newChunkPosition, objectId);
      gameDataManager->getBoarsManager()->setChunkPosition(objectId, newChunkPosition);
    }
  }
}

void runServer()
{
  const int SERVER_MAX_PLAYERS = 30;

  std::cout << "loading server ressources..." << std::endl;
  gdd::loadConvexShapes();

  gdi::createItemTypes();
  gde::createMainEventHandler();


  std::cout << "intitalising..." << std::endl;

  gdu::MemoryArray<gdp::ObjectSimulationData> simulationObjects;
  gdu::MemoryArray<gdmd::Tree> boundingTrees;
  gdu::MemoryArray<gdmg::AABB> aabbs;

  gdp::GridSpacePartition terrainSimulationGrid((float)gdv::CHUNK_SIZE, &boundingTrees, &aabbs);
  gdp::GridSpacePartition objectsSimulationGrid(8.0*(float)(gdv::CHUNK_SIZE), &boundingTrees, &aabbs);

  gdp::Simulation simulation(&simulationObjects, &boundingTrees, &aabbs, &terrainSimulationGrid, &objectsSimulationGrid);

  gdp::SimulationData simulationData;
  simulationData.simulation = &simulation;
  simulationData.objects = &simulationObjects;
  simulationData.aabbs = &aabbs;
  gdp::SimulationDataManager simulationDataManager(&simulationData);

  gds::GameData gameData;
  gds::GameDataManager gameDataManager(&gameData, &simulationDataManager);

  std::cout << "generating spawn..." << std::endl;
  gdv::ChunkGenerator chunkGenerator(&gameDataManager);
  gdv::Terrain terrain(&gameDataManager, &chunkGenerator);

  std::cout << "starting server..." << std::endl;

  SDL_Init(SDL_INIT_EVERYTHING);
  SDLNet_Init();

  bool running = true;
  SDL_Event event;

  gdg::initDisplay("server interface", 400, 400);

  gdu::Buffer buffer(10000000);
  gdn::Server server(SERVER_MAX_PLAYERS, 1235, &buffer);

  gds::ServerManager serverManager(&server, &buffer);
  gds::Players players(SERVER_MAX_PLAYERS);
  gdsv::TerrainSender terrainSender(SERVER_MAX_PLAYERS, &serverManager, &terrain, &gameDataManager);

  std::cout << "registering listeners..." << std::endl;
  gdsl::PacketListener packetListener(&serverManager, &players, &terrain, &terrainSender);
  gde::registerListener(&packetListener);

  gdsl::ConnectionPacketListener connectionPacketListener(&server, &players);
  gde::registerListener(&connectionPacketListener);

  gdsl::RequestSpawnPacketListener requestSpawnPacketListener(&server, &players);
  gde::registerListener(&requestSpawnPacketListener);

  gdsl::ClientDisconnectionListener clientDisconnectionListener(&server, &players);
  gde::registerListener(&clientDisconnectionListener);

  gdsl::ClientUpdatePacketListener clientUpdatePacketListener(&server, &players);
  gde::registerListener(&clientUpdatePacketListener);

  ArrayList<Pointer<gdp::Object>> objects;

  std::cout << "server running!" << std::endl;


  int UPS_TIME = 16666666;
  float upsTimeCount = 0.0;
  int ups = 0;

  std::chrono::system_clock::time_point start = std::chrono::system_clock::now();
  while(running)
  {
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();
    int timePassedNs = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    float timePassed = ((float)timePassedNs)/(1000000000.0);
    start = now;

    upsTimeCount+=timePassed;
    ups++;
    if(upsTimeCount >= 1.0)
    {
      std::cout << "UPS: " << ups << std::endl;
      upsTimeCount = 0.0;
      ups = 0;

      std::cout << "Regions loaded: " << terrain.loadedRegionsSize() << std::endl;
    }

    while(SDL_PollEvent(&event))
    {
      if(event.type == SDL_QUIT || (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE))
      {
        running = false;
      }
    }

    ArrayList<gdso::Player*> playersList;
    players.getPlayers(&playersList);
    //terrain.updateRegions(playersList); //todo
    terrain.update(playersList);

    gds::ObjectsToUpdate objectsToUpdate;
    terrain.getObjectsToUpdate(&playersList, &objectsToUpdate);
    std::cout << "objects to update: " << std::endl;
    std::cout << objectsToUpdate.boars << std::endl;
    simulation.update(timePassed, &objectsToUpdate.simulationIds);

    updateBoars(&gameDataManager, &terrain, &objectsToUpdate.boars);

    sendUpdatedObjects(&serverManager, &gameDataManager, &objectsToUpdate);

    server.update(timePassed);
    terrainSender.sendNextChunk();

    now = std::chrono::system_clock::now();
    int processTime = std::chrono::duration_cast<std::chrono::nanoseconds>(now - start).count();
    int toWait = UPS_TIME - processTime;
    if(toWait < 0)
    {
      toWait = 0;
    }
    std::this_thread::sleep_for(std::chrono::nanoseconds(toWait));
  }

  std::cout << "server stoping..." << std::endl;

  SDLNet_Quit();
  SDL_Quit();

  gdi::deleteItemTypes();
  gde::deleteMainEventHandler();

  gdd::deleteConvexShapes();
  std::cout << "server stoped" << std::endl;
}

void run()
{
  DEBUG << "(!) Debug mode is activated!";
  DEBUG.endl();
  //std::cout << std::endl;
  //"127.0.0.1"
  std::cout << "Launch client (1), server (2) or local client(3)?" << std::endl;
  std::cout << "choose: 1 / 2 / 3" << std::endl;
  std::cout << "All other numbers will close the program." << std::endl;
  int mode = 0;
  std::cin >> mode;
  if(mode == 1)
  {
    std::cout << "ip:" << std::endl;
    char ip[100];
    std::cin >> ip;
    std::cout << "starting game..." << std::endl;
    runClient(ip);
    std::cout << "ending game" << std::endl;
  }
  else if(mode == 2)
  {
    std::cout << "starting server..." << std::endl;
    runServer();
    std::cout << "server has stoped" << std::endl;
  }
  else if(mode == 3)
  {
    std::cout << "starting game..." << std::endl;
    runClient("127.0.0.1");
    std::cout << "ending game" << std::endl;
  }
}

void test()
{
  gdu::ListedArrays<int> list;
  for(int i=0;i<16;i++)
  {
    list.add(i);
  }

  gdu::ListedArrays<int> list2 = list;
  list2[6] = 4123;

  std::cout << list << std::endl;
  std::cout << std::endl;
  std::cout << list2 << std::endl;

  gdu::ListedArrays<int> list3;

  for(int i=0;i<16;i++)
  {
    list3.add(i + 60);
  }

  std::cout << list3 << std::endl;

  list3 = list2;
  list3.setSize(35);
  std::cout << list3 << std::endl;
}

int main()
{
  std::cout << "start" << std::endl;
  run();
  //test();
  std::cout << "stop" << std::endl;
  return 0;
}
