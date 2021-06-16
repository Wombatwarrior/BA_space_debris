cmake_minimum_required(VERSION 3.10)

FIND_PACKAGE(LATEX)
IF(LATEX_FOUND)
    # Latex source file.
    SET( MAIN_TEX_BASE_FILENAME "OB_space_debris_trajectory_modelling")
    SET( MAIN_TEX "${CMAKE_SOURCE_DIR}/Thesis/${MAIN_TEX_BASE_FILENAME}.tex")
    SET( MATH_TEX_BASE_FILENAME "Math")
    SET( MATH_TEX "${CMAKE_SOURCE_DIR}/Thesis/${MAIN_TEX_BASE_FILENAME}.tex")
    SET( FIGURES_PATH ${CMAKE_SOURCE_DIR}/Thesis/figures)
    SET( TEMPLATE_STUFF_PATH ${CMAKE_SOURCE_DIR}/Thesis/templateStuff)


    # Directory where the source files are located.
    SET( WORKINGDIR "${CMAKE_CURRENT_BINARY_DIR}" )

    ADD_CUSTOM_TARGET( thesis_pdf ALL
            DEPENDS ${WORKINGDIR}/Thesis
            COMMAND latexmk -pdf ${MAIN_TEX_BASE_FILENAME}.tex
            COMMAND latexmk -pdf ${MATH_TEX_BASE_FILENAME}.tex
            )
    add_custom_command(
            OUTPUT ${WORKINGDIR}/Thesis
            COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${CMAKE_SOURCE_DIR}/Thesis
            ${WORKINGDIR}
    )
ELSE()
    MESSAGE(ERROR "No latex tools found!")
ENDIF()
