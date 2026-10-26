cmake_minimum_required(VERSION 3.15)
project(PlayerTracker CXX)

set(CMAKE_CXX_STANDARD 17)
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

target_link_libraries(PlayerTracker PRIVATE plugin-sdk)
