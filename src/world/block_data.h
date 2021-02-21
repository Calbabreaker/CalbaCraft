#pragma once

#include <glm/glm.hpp>
#include <string_view>
#include <vector>

using blockid_t = uint8_t;

struct BlockData
{
    blockid_t id;
    std::string_view name;
    glm::vec2 texture;
};

class BlockDatabase
{
public:
    static void loadData(const std::string_view filepath);
    static const BlockData& getBlockData(blockid_t id);

private:
    static std::vector<BlockData> s_blockDatas;
};
