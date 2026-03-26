#include "ChunkMesh.h"

#include "VoxelData.h"

namespace gt
{
  namespace doubovik
  {
    namespace voxel
    {
      ChunkMesh::ChunkMesh()
      {
        loaded = false;
      }

      ChunkMesh::ChunkMesh(const ChunkMesh&)
      {
        loaded = false;
      }

      ChunkMesh& ChunkMesh::operator=(const ChunkMesh&)
      {
        loaded = false;
        return *this;
      }

      void ChunkMesh::deleteData()
      {
        mesh.deleteData();
        loaded = false;
      }

      void ChunkMesh::loadData(const ArrayList<float>& positions, const ArrayList<float>& uvs, const ArrayList<float>& normals, const ArrayList<unsigned int>& indices)
      {
        deleteData();
        if(positions.size() == 0)
        {
          return;
        }
        mesh.addVbo(0, 3, positions.getData(), positions.size());
        mesh.addVbo(1, 2, uvs.getData(), uvs.size());
        mesh.addVbo(2, 3, normals.getData(), normals.size());
        mesh.addIndices(indices.getData(), indices.size());
        loaded = true;
      }

      gdg::Mesh* ChunkMesh::getMesh()
      {
        return &mesh;
      }

      bool ChunkMesh::isLoaded() const
      {
        return loaded;
      }
    }
  }
}
