add_library(GLFW
    include/GLFW/glfw3.h
    include/GLFW/glfw3native.h
    src/internal.h 
    src/mappings.h 
    src/context.c 
    src/init.c 
    src/input.c 
    src/monitor.c
    src/vulkan.c 
    src/window.c
)

if (WIN32) 
    message(STATUS "Using Win32 for window creation")
    target_sources(GLFW PRIVATE
        src/win32_platform.h 
        src/win32_joystick.h 
        src/wgl_context.h
        src/egl_context.h 
        src/osmesa_context.h 
        src/win32_init.c
        src/win32_joystick.c 
        src/win32_monitor.c 
        src/win32_time.c
        src/win32_thread.c 
        src/win32_window.c 
        src/wgl_context.c
        src/egl_context.c 
        src/osmesa_context.c
    )

    target_compile_definitions(GLFW PRIVATE _GLFW_WIN32)
elseif(UNIX)
    message(STATUS "Using X11 for window creation")
    target_sources(GLFW PRIVATE
        src/x11_platform.h 
        src/xkb_unicode.h 
        src/posix_time.h
        src/posix_thread.h 
        src/glx_context.h 
        src/egl_context.h
        src/osmesa_context.h 
        src/x11_init.c 
        src/x11_monitor.c
        src/x11_window.c 
        src/xkb_unicode.c 
        src/posix_time.c
        src/posix_thread.c 
        src/glx_context.c 
        src/egl_context.c
        src/osmesa_context.c
    )

    target_compile_definitions(GLFW PRIVATE _GLFW_X11)
elseif(APPLE)
    message(STATUS "Using Cocoa for window creation")
    target_sources(GLFW PRIVATE
        src/cocoa_platform.h 
        src/cocoa_joystick.h
        src/posix_thread.h
        src/nsgl_context.h 
        src/egl_context.h 
        src/osmesa_context.h
        src/cocoa_init.m 
        src/cocoa_joystick.m 
        src/cocoa_monitor.m
        src/cocoa_window.m 
        src/cocoa_time.c 
        src/posix_thread.c
        src/nsgl_context.m 
        src/egl_context.c 
        src/osmesa_context.c
    )

    target_compile_definitions(GLFW PRIVATE _GLFW_COCOA)
else()
    message(FATAL_ERROR "No supported platform was detected")
endif()

target_include_directories(GLFW PRIVATE src/)

target_include_directories(GLFW INTERFACE include/)