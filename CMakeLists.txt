cmake_minimum_required(VERSION 3.15)
project(PlayerTracker CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

# ดึง Plugin-SDK มาเก็บไว้ใน FetchContent
include(FetchContent)
FetchContent_Declare(
    plugin-sdk
    GIT_REPOSITORY https://github.com/DK22Pac/plugin-sdk.git
    GIT_TAG master
)
FetchContent_MakeAvailable(plugin-sdk)

# กำหนด Target ASI
add_library(PlayerTracker SHARED src/main.cpp)

set_target_properties(PlayerTracker PROPERTIES 
    PREFIX ""
    SUFFIX ".asi"
)

# เพิ่ม Directory Header สำหรับ Plugin-SDK (SA-MP / GTASA)
target_include_directories(PlayerTracker PRIVATE 
    ${plugin-sdk_SOURCE_DIR}/plugin_sa
    ${plugin-sdk_SOURCE_DIR}/plugin_sa/game_sa
    ${plugin-sdk_SOURCE_DIR}/shared
    ${plugin-sdk_SOURCE_DIR}/shared/game
)

# Link Dynamic Library ของ Plugin-SDK
target_link_libraries(PlayerTracker PRIVATE plugin_sa)
