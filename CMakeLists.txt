cmake_minimum_required(VERSION 3.22)

project(vikunja2 LANGUAGES CXX)

# TODO: fix me, when alpaka is integrated
set(CMAKE_CXX_STANDARD 20)

option(BUILD_TESTING "Build the testing tree." OFF)
option(vikunja_EXAMPLES "Build the vikunja examples." OFF)

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

if(vikunja_EXAMPLES)
    message(STATUS "enable examples")
    add_subdirectory(examples)
endif()

if(BUILD_TESTING)
    message(STATUS "enable testing")
    enable_testing()
    add_subdirectory(test)
endif()
