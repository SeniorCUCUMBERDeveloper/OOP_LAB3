cmake_minimum_required(VERSION 3.10)

project(StorageManagement)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/libs)


file(GLOB_RECURSE SOURCES
    "main.cpp"
    "Storage/*.cpp"
)


file(GLOB_RECURSE CONTAINER_SRC "Container/*.cpp")
add_library(Container SHARED ${CONTAINER_SRC})
target_include_directories(Container PUBLIC "${PROJECT_SOURCE_DIR}/Container")


file(GLOB_RECURSE EXPLOSIVE_CONTAINER_SRC "ExplosiveContainer.cpp")
add_library(ExplosiveContainer SHARED ${EXPLOSIVE_CONTAINER_SRC} "${PROJECT_SOURCE_DIR}/Container/Container.cpp") # Соединяем с Container.cpp
target_include_directories(ExplosiveContainer PUBLIC
    "${PROJECT_SOURCE_DIR}/ExplosiveContainer"
    "${PROJECT_SOURCE_DIR}/Container"
)


file(GLOB_RECURSE FRAG_AND_REF_SRC "Frag_and_Ref.cpp")
add_library(FragAndRef SHARED ${FRAG_AND_REF_SRC})
target_include_directories(FragAndRef PUBLIC "${PROJECT_SOURCE_DIR}/Container")


file(GLOB_RECURSE FRAGILE_CONTAINER_SRC "FragileContainer.cpp")
add_library(FragileContainer SHARED ${FRAGILE_CONTAINER_SRC})
target_include_directories(FragileContainer PUBLIC "${PROJECT_SOURCE_DIR}/Container")


file(GLOB_RECURSE REFRAGED_CONTAINER_SRC "RefragedContainer.cpp")
add_library(RefragedContainer SHARED ${REFRAGED_CONTAINER_SRC})
target_include_directories(RefragedContainer PUBLIC "${PROJECT_SOURCE_DIR}/Container")


add_executable(StorageManagement ${SOURCES})


set_target_properties(StorageManagement PROPERTIES
    LINK_FLAGS "-Wl,-rpath,${CMAKE_LIBRARY_OUTPUT_DIRECTORY}"
)


include_directories(
    "${PROJECT_SOURCE_DIR}/MVC"
    "${PROJECT_SOURCE_DIR}/Storage"  
    "${PROJECT_SOURCE_DIR}/Container/I"
    "${PROJECT_SOURCE_DIR}/Octree"
)


link_directories(${CMAKE_LIBRARY_OUTPUT_DIRECTORY})