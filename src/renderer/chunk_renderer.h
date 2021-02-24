#pragma once

#include <memory>
#include <vector>

#include "camera.h"
#include "chunk_mesh.h"
#include "gl/shader.h"
#include "gl/texture.h"

class ChunkRenderer
{
public:
    ChunkRenderer();
    ~ChunkRenderer();

    void render(const Camera& camera);

    std::shared_ptr<ChunkMesh> newChunkMesh();

    const TextureAtlas& getTexture() const { return m_chunkTexture; }
    const uint32_t* getMeshIndices() const { return m_meshIndices; }

private:
    std::vector<std::shared_ptr<ChunkMesh>> m_chunkMeshes;

    Shader m_chunkShader;
    TextureAtlas m_chunkTexture;
    uint32_t* m_meshIndices;
};
