cmake_minimum_required(VERSION 3.22)

project(vikunja2 LANGUAGES CXX)

set(_TARGET_NAME "example_iota")

add_executable(${_TARGET_NAME})
target_sources(${_TARGET_NAME}
    PRIVATE
    main.cpp
)
target_link_libraries(${_TARGET_NAME} PRIVATE vikunja::vikunja)
