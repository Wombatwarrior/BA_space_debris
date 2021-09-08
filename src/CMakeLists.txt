set(CMAKE_CXX_STANDARD 17)

set(BINARY ${PROJECT_BINARY})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true
     satellitePropagator/*.h
     satellitePropagator/*.cpp
 )

set(SOURCES ${SOURCES})


add_library(${BINARY}_lib STATIC ${SOURCES})

target_include_directories(${BINARY}_lib
                           PUBLIC
                           .
)
target_compile_definitions(
        ${BINARY}_lib
        PUBLIC
        _USE_MATH_DEFINES
)


option(DebrisSim_Simulation "Build the simulation executable" ON)
if(DebrisSim_Simulation)

    add_executable(${BINARY} debris_sim.cpp)
    target_compile_definitions(
            ${BINARY}
            PUBLIC
            _USE_MATH_DEFINES
    )
    target_link_libraries(${BINARY}
            # stuff that is used in headers and source files
            PRIVATE
            ${BINARY}_lib
            log4cxx
    )
endif()