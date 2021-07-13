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

add_executable(${BINARY} debris_sim.cpp)

target_link_libraries(${BINARY}
        # stuff that is used in headers and source files
        PRIVATE
        ${BINARY}_lib
        log4cxx
)
