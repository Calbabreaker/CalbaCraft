file(GLOB_RECURSE SOURCES *.cpp *.h)
add_executable(${PROJECT_NAME} ${SOURCES})
target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

set_project_options(${PROJECT_NAME})
set_project_warnings(${PROJECT_NAME})

target_precompile_headers(${PROJECT_NAME} PRIVATE
    <algorithm>
    <chrono>
    <functional>
    <iostream>
    <memory>
    <utility>

    # -- Data Structures --
    <array>
    <sstream>
    <string>
    <string_view>
    <unordered_map>
    <unordered_set>
    <variant>
    <vector>
)

target_link_libraries(${PROJECT_NAME} PRIVATE GLFW)
target_link_libraries(${PROJECT_NAME} PRIVATE SPDLOG)

target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)

target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:CC_DEBUG>")
target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:CC_RELEASE>")
