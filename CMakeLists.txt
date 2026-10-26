cmake_minimum_required(VERSION 3.15)
project(PlayerTracker ASI)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_BUILD_TYPE Release)

set(CMAKE_SHARED_LIBRARY_SUFFIX ".asi")

include(FetchContent)
FetchContent_Declare(
    plugin-sdk
    GIT_REPOSITORY https://github.com/DK22Pac/plugin-sdk.git
    GIT_TAG master
)
FetchContent_MakeAvailable(plugin-sdk)

add_library(PlayerTracker SHARED src/main.cpp)
target_link_libraries(PlayerTracker PRIVATE plugin-sdk)
