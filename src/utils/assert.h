#pragma once

#include <filesystem>

#include "log.h"

#ifdef CC_DEBUG
    #if defined(__has_builtin) && !defined(__ibmxl__)
        #if __has_builtin(__builtin_debugtrap)
            #define CC_DEBUGBREAK() __builtin_debugtrap()
        #elif __has_builtin(__debugbreak)
            #define CC_DEBUGBREAK() __debugbreak()
        #endif
    #endif
    #if !defined(CC_DEBUGBREAK)
        #if defined(_MSC_VER) || defined(__INTEL_COMPILER)
            #define CC_DEBUGBREAK() __debugbreak()
        #elif defined(__ARMCC_VERSION)
            #define CC_DEBUGBREAK() __breakpoint(42)
        #elif defined(__ibmxl__) || defined(__xlC__)
            #include <builtins.h>
            #define CC_DEBUGBREAK() __trap(42)
        #elif defined(__DMC__) && defined(_M_IX86)
static inline void CC_DEBUGBREAK(void)
{
    __asm int 3h;
}
        #elif defined(__i386__) || defined(__x86_64__)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__("int3");
}
        #elif defined(__thumb__)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__(".inst 0xde01");
}
        #elif defined(__aarch64__)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__(".inst 0xd4200000");
}
        #elif defined(__arm__)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__(".inst 0xe7f001f0");
}
        #elif defined(__alpha__) && !defined(__osf__)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__("bpt");
}
        #elif defined(_54_)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__("ESTOP");
}
        #elif defined(_55_)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__(";\n .if (.MNEMONIC)\n ESTOP_1\n .else\n ESTOP_1()\n .endif\n NOP");
}
        #elif defined(_64P_)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__("SWBP 0");
}
        #elif defined(_6x_)
static inline void CC_DEBUGBREAK(void)
{
    __asm__ __volatile__("NOP\n .word 0x10000000");
}
        #elif defined(__STDC_HOSTED__) && (__STDC_HOSTED__ == 0) && defined(__GNUC__)
            #define CC_DEBUGBREAK() __builtin_trap()
        #else
            #include <signal.h>
            #if defined(SIGTRAP)
                #define CC_DEBUGBREAK() raise(SIGTRAP)
            #else
                #define CC_DEBUGBREAK() raise(SIGABRT)
            #endif
        #endif
    #endif

    // CC_ASSERT will only have the expression, while CC_ASSERT_MSG will have
    // both the expression and a message.
    #define CC_INTERNAL_ASSERT_IMPL(expr, ...)                                                     \
        if (!(expr))                                                                               \
        CC_LOG_ERROR(__VA_ARGS__), CC_DEBUGBREAK()

    #define CC_ASSERT_MSG(expr, msg, ...)                                                          \
        CC_INTERNAL_ASSERT_IMPL(expr, "Assertion failed: " msg, ##__VA_ARGS__)
    #define CC_ASSERT(expr)                                                                        \
        CC_INTERNAL_ASSERT_IMPL(expr, "Assertion '{0}' failed at: {1}:{2}", #expr,                 \
                                std::filesystem::path(__FILE__).filename().string(), __LINE__)

#else
    #define CC_ASSERT_MSG(expr, ...)
    #define CC_ASSERT(expr)
    #define CC_DEBUGBREAK()
#endif
