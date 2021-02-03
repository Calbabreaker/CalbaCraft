add_library(SPDLOG 
    src/spdlog.cpp 
    src/stdout_sinks.cpp 
    src/color_sinks.cpp 
    src/file_sinks.cpp 
    src/async.cpp 
    src/cfg.cpp
    src/fmt.cpp
)

target_compile_definitions(SPDLOG PRIVATE SPDLOG_COMPILED_LIB)

target_include_directories(SPDLOG PUBLIC include/)