#include "chunk_renderer.h"

ChunkRenderer::ChunkRenderer()
    : m_chunkShader("shaders/chunk_vert.glsl", "shaders/chunk_frag.glsl"),
      m_chunkTexture("textures/block_textures.png", { 16, 16 })
{
    m_chunkShader.bind();
    m_chunkShader.setInt1("u_texture", 0);

    m_meshIndices = new uint32_t[ChunkMesh::MAX_INDICES_COUNT];
    uint32_t offset = 0;

    for (uint32_t i = 0; i < ChunkMesh::MAX_INDICES_COUNT; i += 6)
    {
        m_meshIndices[i + 0] = offset;
        m_meshIndices[i + 1] = offset + 1;
        m_meshIndices[i + 2] = offset + 2;

        m_meshIndices[i + 3] = offset + 2;
        m_meshIndices[i + 4] = offset + 3;
        m_meshIndices[i + 5] = offset + 0;

        offset += 4;
    }
}

ChunkRenderer::~ChunkRenderer()
{
    delete[] m_meshIndices;
}

void ChunkRenderer::render(const Camera& camera)
{
    m_chunkShader.bind();
    m_chunkShader.setMat4("u_viewProjection", camera.getViewProjection());
    m_chunkTexture.bind();

    for (const std::shared_ptr<ChunkMesh>& mesh : m_chunkMeshes)
    {
        m_chunkShader.setFloat3("u_chunkPosition", mesh->getChunkPos());
        mesh->render();
    }
}

std::shared_ptr<ChunkMesh> ChunkRenderer::newChunkMesh()
{
    std::shared_ptr<ChunkMesh> mesh = std::make_shared<ChunkMesh>(this);
    m_chunkMeshes.push_back(mesh);
    return mesh;
}
