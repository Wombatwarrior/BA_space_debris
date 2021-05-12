option(BUILD_DOC "Build documentation" OFF)

if (BUILD_DOC)
    find_package(Doxygen)
    if (DOXYGEN_FOUND)
        set(DOXYGEN_IN ${PROJECT_SOURCE_DIR}/Doxyfile)
        message("Doxygen build started")
        add_custom_target(
                doc_doxygen ALL
                COMMAND ${DOXYGEN_EXECUTABLE} ${DOXYGEN_IN}
                WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
                COMMENT "Generating documentation"
                VERBATIM
        )
    else (DOXYGEN_FOUND)
        message("Doxygen not found... skipped generating documentation")
    endif (DOXYGEN_FOUND)
    else (BUILD_DOC)
        message("Skipped generating documentation")
endif (BUILD_DOC)