cmake_minimum_required(VERSION 3.22)

CPMAddPackage("gh:catchorg/Catch2@3.7.1")

add_library(vikunjaTest INTERFACE)
target_link_libraries(vikunjaTest 
    INTERFACE
    vikunja::vikunja
    Catch2::Catch2WithMain
)

add_subdirectory(unit)
add_subdirectory(integ)
