if (CMAKE_BUILD_TYPE STREQUAL "Release")
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/Doxyfile)
        message("-- Doxygen build documentation")
        add_custom_target(
                doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating documentation"
                VERBATIM
        )
    else ()
        message("-- Doxygen not found... skipped generating documentation")
    endif ()
else ()
    message("-- Skipped generating documentation")
endif ()