#include <filesystem>

#include "files.h"

std::string loadFileContents(const std::string_view filepath)
{
    std::ifstream inFile(filepath.data(), std::ios::in | std::ios::binary | std::ios::ate);
    CC_ASSERT_RELEASE(inFile.is_open(), "Could not open file {0}!", filepath);

    std::string contents;
    inFile.seekg(0, std::ios::end);
    contents.reserve(static_cast<size_t>(inFile.tellg()));
    inFile.seekg(0, std::ios::beg);

    contents.assign(std::istreambuf_iterator<char>(inFile), std::istreambuf_iterator<char>());
    return contents;
}

rapidjson::Document loadJSONFile(const std::string_view filepath)
{
    std::string contents = loadFileContents(filepath);
    rapidjson::Document doc;
    doc.Parse(contents.c_str());
    return doc;
}
