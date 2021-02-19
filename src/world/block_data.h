#pragma once

#include <glm/glm.hpp>
#include <string_view>

using blockid_t = uint8_t;

struct BlockData
{
    blockid_t id;
    std::string_view name;
    glm::vec2 textureTop;
    glm::vec2 textureSide;
    glm::vec2 textureBottom;
};

class BlockDatabase
{
public:
    static void loadData(const std::string_view fileCBD);
    static void getBlockData(blockid_t id);

private:
};
