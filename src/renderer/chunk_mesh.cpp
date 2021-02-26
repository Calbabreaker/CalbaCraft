#include "chunk_renderer.h"
#include "world/block_data.h"
#include "world/chunk.h"

#include "chunk_mesh.h"

// clang-format off
// uses a direction index to index CUBE_VERTICES
constexpr uint32_t CUBE_INDICES[] = {
    6, 7, 4, 5, // north
    3, 2, 1, 0, // south
    2, 6, 5, 1, // east
    7, 3, 0, 4, // west
    2, 3, 7, 6, // top
    0, 1, 5, 4, // bottom
};

constexpr glm::vec3 CUBE_VERTICES[] = {
    { 0.0f, 0.0f, 0.0f },
    { 1.0f, 0.0f, 0.0f },
    { 1.0f, 1.0f, 0.0f },
    { 0.0f, 1.0f, 0.0f },

    { 0.0f, 0.0f, 1.0f },
    { 1.0f, 0.0f, 1.0f },
    { 1.0f, 1.0f, 1.0f },
    { 0.0f, 1.0f, 1.0f }
};

constexpr glm::vec2 CUBE_UVS[] = {
    { 0.0f, 0.0f }, 
    { 1.0f, 0.0f }, 
    { 1.0f, 1.0f }, 
    { 1.0f, 0.0f }  
};
// clang-format on

ChunkMesh::ChunkMesh(ChunkRenderer* chunkRenderer)
    : m_vertexBuffer(MAX_VERTICES * sizeof(Vertex)), m_chunkRenderer(chunkRenderer)
{
    BufferElement layout[] = { { GL_FLOAT, 3 }, { GL_FLOAT, 2 } };
    m_vertexArray.addVertexBuffer(m_vertexBuffer, layout, 2);

    m_indexBuffer.setIndices(m_chunkRenderer->getMeshIndices(), MAX_INDICES_COUNT);
    m_vertexArray.setIndexBuffer(m_indexBuffer);

    m_vertexBufferBase = new Vertex[MAX_VERTICES];
}

void ChunkMesh::regenerateMesh(const std::shared_ptr<Chunk>& chunk)
{
    m_indicesCount = 0;
    m_vertexBufferPtr = m_vertexBufferBase;
    m_chunkPos = chunk->getChunkPos();

    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                FaceParams params;
                params.blockPos = { x, y, z };

                blockid_t id = chunk->getBlock(params.blockPos);
                const BlockData& data = BlockDatabase::getBlockData(id);

                if (id == 0)
                    continue;

                for (int dirIndex = 0; dirIndex < 6; dirIndex++)
                {
                    params.direction = static_cast<Direction>(dirIndex);
                    const glm::ivec3& dirVec = DIRECTION_TO_VECTOR[params.direction];
                    glm::ivec3 neighbourPos = params.blockPos + dirVec;

                    if (chunk->getBlock(neighbourPos, id) == 0)
                    {
                        m_chunkRenderer->getTexture().getSubTextureUVs(
                            data.texture, &params.uvMin, &params.uvMax);

                        addFace(params);
                    }
                }
            }
        }
    }

    if (m_indicesCount == 0)
        return;

    uint32_t size = static_cast<uint32_t>(
        reinterpret_cast<uint8_t*>(m_vertexBufferPtr) -
        reinterpret_cast<uint8_t*>(m_vertexBufferBase));

    m_vertexBuffer.setDynamicData(m_vertexBufferBase, size);
}

void ChunkMesh::addFace(const FaceParams& params)
{
    // gen vertices
    for (uint8_t i = 0; i < 4; i++)
    {
        const glm::ivec3& vertex = CUBE_VERTICES[CUBE_INDICES[(params.direction * 4) + i]];
        m_vertexBufferPtr->position = vertex + params.blockPos;
        m_vertexBufferPtr->texCoord.x = CUBE_UVS[i].x ? params.uvMax.x : params.uvMin.x;
        m_vertexBufferPtr->texCoord.y = CUBE_UVS[i].y ? params.uvMax.y : params.uvMin.y;
        m_vertexBufferPtr++;
    }

    m_indicesCount += 6;
}

void ChunkMesh::render()
{
    if (m_indicesCount == 0)
        return;

    m_vertexArray.draw(m_indicesCount);
}
