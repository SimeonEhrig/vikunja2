cmake_minimum_required(VERSION 3.22)

set(_UNIT_TEST_NAME unitRanges)

project(${_UNIT_TEST_NAME} LANGUAGES CXX)

add_executable(${_UNIT_TEST_NAME})
target_sources(${_UNIT_TEST_NAME}
    PRIVATE
    foreach.cpp
    io_input_concept.cpp
    proxyRange.cpp
)
target_link_libraries(${_UNIT_TEST_NAME}
    PRIVATE
    vikunjaTest
)

set_target_properties(${_UNIT_TEST_NAME} PROPERTIES FOLDER "test/unit")
add_test(NAME ${_UNIT_TEST_NAME} COMMAND ${_UNIT_TEST_NAME})
