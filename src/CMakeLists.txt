add_executable(${PROJECT_NAME} 
    core/application.cpp
    core/input.cpp
    core/window.cpp

    renderer/camera.cpp
    renderer/shader.cpp
    renderer/texture.cpp
    renderer/vertex_array.cpp

    utils/files.cpp
    utils/log.cpp

    world/entity.cpp
    world/player.cpp

    main.cpp
)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_precompile_headers(${PROJECT_NAME} PRIVATE "ccph.h")

set_project_flags(${PROJECT_NAME})

message(STATUS ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${CONAN_LIBS})
target_link_libraries(${PROJECT_NAME} PRIVATE stdc++fs)

target_compile_definitions(${PROJECT_NAME} PRIVATE GLFW_INCLUDE_NONE)

target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:DEBUG>:CC_DEBUG>")
target_compile_definitions(${PROJECT_NAME} PRIVATE "$<$<CONFIG:RELEASE>:CC_RELEASE>")
