#include <glm/gtc/type_ptr.hpp>

#include "block_data.h"
#include "utils/files.h"

static constexpr glm::ivec2 getVector(const rapidjson::Value::Array& vector)
{
    return { vector[0], vector[1] };
}

std::vector<BlockData> BlockDatabase::s_blockDatas;

void BlockDatabase::loadData(const std::string_view filepath)
{
    rapidjson::Document array = loadJSONFile(filepath);
    s_blockDatas.reserve(array.Size());

    for (rapidjson::SizeType i = 0; i < array.Size(); i++)
    {
        rapidjson::Value jsonBlock = array[i].GetObject();
        BlockData blockData;

        blockData.id = static_cast<blockid_t>(i);
        blockData.name = jsonBlock["name"].GetString();

        blockData.texture = getVector(jsonBlock["texture"].GetArray());
    }
}

const BlockData& BlockDatabase::getBlockData(blockid_t id)
{
    return s_blockDatas[id];
}
