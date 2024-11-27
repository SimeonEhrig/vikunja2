cmake_minimum_required(VERSION 3.22)

project(vikunja2 LANGUAGES CXX)

# TODO: fix me, when alpaka is integrated
set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTING "Build the testing tree." OFF)

include(cmake/CPM.cmake)
CPMAddPackage("gh:kokkos/mdspan#mdspan-0.6.0")

add_library(headers INTERFACE)
target_include_directories(headers INTERFACE include)

add_library(vikunja INTERFACE)
target_link_libraries(vikunja 
    INTERFACE 
    headers
    std::mdspan
)
add_library(vikunja::vikunja ALIAS vikunja)

add_executable(${CMAKE_PROJECT_NAME})
target_sources(${CMAKE_PROJECT_NAME}
    PRIVATE
    main.cpp
)
target_link_libraries(${CMAKE_PROJECT_NAME} PRIVATE vikunja::vikunja)

# TODO set as option
if(BUILD_TESTING)
    message(STATUS "enable testing")
    enable_testing()
    add_subdirectory(test)
endif()
