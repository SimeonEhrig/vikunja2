cmake_minimum_required(VERSION 3.19)

project(vikunja2 LANGUAGES CXX)

add_library(headers INTERFACE)
target_include_directories(headers INTERFACE include)
add_library(vikunja::vikunja ALIAS headers)

add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
    main.cpp
)
set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES
    CXX_STANDARD 20
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE vikunja::vikunja)
