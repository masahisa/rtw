cmake_minimum_required(VERSION 2.8)

# lcov input directory
set(LCOV_INPUT_DIR ${CMAKE_SOURCE_DIR}/build/src/CMakeFiles/)

#lcov output directory
set(LCOV_OUTPUT_DIR ${CMAKE_SOURCE_DIR}/cov/lcov)

# add custom target
add_custom_target(
    cov
    COMMAND mkdir -p ${LCOV_OUTPUT_DIR}
    # make the coverage report from .gcda and .gcno
    COMMAND lcov --directory ${LCOV_INPUT_DIR} --capture --output-file ${LCOV_OUTPUT_DIR}/coverage.lcov
    COMMAND genhtml -o ${LCOV_OUTPUT_DIR} ${LCOV_OUTPUT_DIR}/coverage.lcov
    # after making the coverage report, zeroise the counters that means removing .gcda
    COMMAND lcov --directory ${LCOV_INPUT_DIR} --zerocounters
)