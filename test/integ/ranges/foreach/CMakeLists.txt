cmake_minimum_required(VERSION 3.22)

set(_INTEG_TEST_NAME integForeach)

project(${_INTEG_TEST_NAME} LANGUAGES CXX)

add_executable(${_INTEG_TEST_NAME})
target_sources(${_INTEG_TEST_NAME}
    PRIVATE
    main.cpp
)
target_link_libraries(${_INTEG_TEST_NAME}
    PRIVATE
    vikunjaTest
)

set_target_properties(${_INTEG_TEST_NAME} PROPERTIES FOLDER "test/integ")
add_test(NAME ${_INTEG_TEST_NAME} COMMAND ${_INTEG_TEST_NAME})
