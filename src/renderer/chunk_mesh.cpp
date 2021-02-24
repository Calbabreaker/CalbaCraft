#include "chunk_renderer.h"
#include "world/block_data.h"

#include "chunk_mesh.h"

ChunkMesh::ChunkMesh(ChunkRenderer* chunkRenderer)
    : m_vertexBuffer(MAX_VERTICES), m_chunkRenderer(chunkRenderer)
{
    BufferElement layout[] = { { GL_FLOAT, 3 }, { GL_FLOAT, 2 } };
    m_vertexArray.addVertexBuffer(m_vertexBuffer, layout, 2);

    m_indexBuffer.setIndices(m_chunkRenderer->getMeshIndices(), MAX_INDICES_COUNT);
    m_vertexArray.setIndexBuffer(m_indexBuffer);
}

void ChunkMesh::rengenerateMesh(const std::shared_ptr<Chunk>& chunk)
{
    for (int x = 0; x < CHUNK_SIZE; x++)
    {
        for (int y = 0; y < CHUNK_SIZE; y++)
        {
            for (int z = 0; z < CHUNK_SIZE; z++)
            {
                // glm::ivec3 blockPos = { x, y, z };
                // blockid_t id = blocks[localBlockPosToIndex(blockPos)];

                // if (id != 0)
                // {
                // }
            }
        }
    }
}

void ChunkMesh::render()
{
    m_vertexArray.draw();
}
