add_executable(${PROJECT_NAME} 
    core/application.cpp
    core/config.cpp
    core/input.cpp
    core/window.cpp

    renderer/gl/buffer.cpp
    renderer/gl/shader.cpp
    renderer/gl/texture.cpp
    renderer/gl/vertex_array.cpp
    renderer/camera.cpp

    utils/files.cpp
    utils/log.cpp

    world/block_data.cpp
    world/chunk_mesh.cpp
    world/chunk.cpp
    world/coordinates.cpp
    world/entity.cpp
    world/player.cpp
    world/world.cpp

    main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_precompile_headers(${PROJECT_NAME} PRIVATE "ccph.h")

set_project_flags(${PROJECT_NAME})

target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:CC_DEBUG>")
target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:CC_RELEASE>")
