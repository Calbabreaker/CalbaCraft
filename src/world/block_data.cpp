#include "block_data.h"
#include "utils/files.h"

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

        if (jsonBlock.HasMember("texture"))
            blockData.texture = { jsonBlock["texture"][0].GetUint(),
                                  jsonBlock["texture"][1].GetUint() };
        else
            blockData.texture = { 0, 0 };
    }
}

const BlockData& BlockDatabase::getBlockData(blockid_t id)
{
    return s_blockDatas[id];
}
