cmake_minimum_required(VERSION 3.10)

project(StorageSimulation)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(SOURCES
    Simulation.cpp
    ../Storage/Storage.cpp
    ../Container/Container.cpp 
    ../Container/Frag_and_Ref.cpp 
    ../Container/RefragedContainer.cpp 
    ../Container/FragileContainer.cpp
)

set(HEADERS
    ../Octree/Octree.hpp
    ../Storage/Storage.hpp
    ../Container/Container.hpp
    ../Terminal/Terminal.hpp
    ../Container/FragileContainer.hpp
    ../Container/RefragedContainer.hpp
    ../Request/Request.hpp
)

add_executable(StorageSimulation ${SOURCES} ${HEADERS})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}")
set(CMAKE_LINK_FLAGS "${CMAKE_LINK_FLAGS}")

include_directories(
    ../Octree
    ../Storage
    ../Container
    ../Terminal
    ../Request
)