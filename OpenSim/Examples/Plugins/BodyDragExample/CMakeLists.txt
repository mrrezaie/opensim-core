project(BodyDragForce)

cmake_minimum_required(VERSION 3.2)

file(GLOB SOURCE_FILES *.cpp)
file(GLOB INCLUDE_FILES *.h)

set(PLUGIN_NAME "BodyDragForce" CACHE STRING "Name of shared library to create")

# OpenSim uses C++17 language features.
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(OpenSim REQUIRED PATHS "${OPENSIM_INSTALL_DIR}")

add_library(${PLUGIN_NAME} SHARED ${SOURCE_FILES} ${INCLUDE_FILES})

target_link_libraries(${PLUGIN_NAME} ${OpenSim_LIBRARIES})

set_target_properties(
    ${PLUGIN_NAME} PROPERTIES
    DEFINE_SYMBOL OSIMPLUGIN_EXPORTS
    PROJECT_LABEL "Libraries - ${PLUGIN_NAME}")

install_targets(/plugins RUNTIME_DIRECTORY /plugins  ${PLUGIN_NAME})

