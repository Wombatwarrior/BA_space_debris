set(BINARY ${PROJECT_BINARY})

file(GLOB_RECURSE SOURCES LIST_DIRECTORIES true *.h *.cpp)

set(SOURCES ${SOURCES})

add_executable(${BINARY} ${SOURCES})

target_link_libraries(${BINARY}
        # stuff that is used in headers and source files
        PRIVATE
        log4cxx)



add_library(${BINARY}_lib STATIC ${SOURCES})