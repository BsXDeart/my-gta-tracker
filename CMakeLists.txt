cmake_minimum_required(VERSION 3.15)
project(PlayerTracker CXX)

# ปรับเป็น C++20 เพื่อให้รองรับ safetyhook ของ Plugin-SDK
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_BUILD_TYPE Release)

include(FetchContent)

# ดึง Plugin-SDK
FetchContent_Declare(
    plugin-sdk
    GIT_REPOSITORY https://github.com/DK22Pac/plugin-sdk.git
    GIT_TAG master
)
FetchContent_MakeAvailable(plugin-sdk)

add_library(PlayerTracker SHARED src/main.cpp)

set_target_properties(PlayerTracker PROPERTIES 
    PREFIX ""
    SUFFIX ".asi"
)

# เพิ่ม Directory Header สำหรับ Plugin-SDK
target_include_directories(PlayerTracker PRIVATE 
    ${plugin-sdk_SOURCE_DIR}/plugin_sa
    ${plugin-sdk_SOURCE_DIR}/plugin_sa/game_sa
    ${plugin-sdk_SOURCE_DIR}/shared
    ${plugin-sdk_SOURCE_DIR}/shared/game
)

# ป้องกันปัญหา UTF-8 / NOMINMAX ใน MSVC
target_compile_definitions(PlayerTracker PRIVATE 
    NOMINMAX 
    WIN32_LEAN_AND_MEAN
)

target_link_libraries(PlayerTracker PRIVATE plugin_sa)
