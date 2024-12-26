cmake_minimum_required(VERSION 3.10)


project(StorageManagement)


set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)


set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)


file(GLOB_RECURSE SOURCES
    "main.cpp"
    "Storage/*.cpp"
)


add_executable(StorageManagement ${SOURCES})


include_directories(
    "${PROJECT_SOURCE_DIR}/MVC"
    "${PROJECT_SOURCE_DIR}/Storage"
    "${PROJECT_SOURCE_DIR}/Container"
    "${PROJECT_SOURCE_DIR}/Checker"
    "${PROJECT_SOURCE_DIR}/Octree"
)