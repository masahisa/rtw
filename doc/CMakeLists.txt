cmake_minimum_required(VERSION 2.8)

# doxygen main page
set(DOXYGEN_MAIN_PAGE ${CMAKE_SOURCE_DIR}/README.md)

# doxygen input directories
set(DOXYGEN_SOURCE_DIR ${CMAKE_SOURCE_DIR}/src/)
set(DOXYGEN_INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include/)
set(DOXYGEN_TEST_DIR ${CMAKE_SOURCE_DIR}/test/)

# doxygen output directory
set(DOXYGEN_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/doc/doxygen)

# configure file Doxyfile.in -> Doxyfile using CMake variables
set(DOXYGEN_IN ${CMAKE_SOURCE_DIR}/doc/Doxyfile.in)
set(DOXYGEN_OUT ${DOXYGEN_OUTPUT_DIR}/Doxyfile)
configure_file(${DOXYGEN_IN} ${DOXYGEN_OUT})

# add custom target
add_custom_target(
    doc
    COMMAND doxygen ${DOXYGEN_OUT}
    WORKING_DIRECTORY ${DOXYGEN_OUTPUT_DIR}
    )