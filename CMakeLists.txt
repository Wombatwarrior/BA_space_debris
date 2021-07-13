cmake_minimum_required(VERSION 3.10)

project(BA_space_debris)
set(CMAKE_CXX_STANDARD 17)

include_directories(src)

set_property(CACHE CMAKE_BUILD_TYPE PROPERTY STRINGS "Debug;Release")

enable_testing()

set (CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})
set (PROJECT_BINARY debris_sim)
add_subdirectory(src)
add_subdirectory(lib/googletest)
add_subdirectory(test)
add_subdirectory(Thesis)


list(APPEND CMAKE_MODULE_PATH ${PROJECT_SOURCE_DIR}/cmake)

include(doxygen)
