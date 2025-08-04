cmake_minimum_required(VERSION 3.10)
project(modularity_and_efficiency)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(SRC main.cpp)

# Optimized target
add_executable(fused_opt ${SRC})
target_compile_definitions(fused_opt PRIVATE FUSED_VERSION_OPT)
if (MSVC)
    target_compile_options(fused_opt PRIVATE /O2 /arch:AVX2)
else()
    target_compile_options(fused_opt PRIVATE -O3 -march=native -ffast-math -funroll-loops)
endif()

# Unoptimized target
add_executable(fused_debug ${SRC})
target_compile_definitions(fused_debug PRIVATE FUSED_VERSION_DEBUG)
if (MSVC)
    target_compile_options(fused_debug PRIVATE /Od)
else()
    target_compile_options(fused_debug PRIVATE -O0)
endif()

add_custom_target(run_both
    COMMAND $<TARGET_FILE:fused_debug>
    COMMAND $<TARGET_FILE:fused_opt>
    DEPENDS fused_debug fused_opt
)