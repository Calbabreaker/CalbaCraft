#pragma once

#include <string_view>

#include "rapidjson/document.h"

std::string loadFileContents(const std::string_view filepath);
rapidjson::Document loadJSONFile(const std::string_view filepath);
