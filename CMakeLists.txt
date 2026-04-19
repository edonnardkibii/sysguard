cmake_minimum_required(VERSION 3.16)

project(
    sysguard
    VERSION 0.1.0
    DESCRIPTION "Lightweight system health monitoring and early-warning tool"
    LANGUAGES CXX
)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(SYSGUARD_BUILD_TESTS "Build tests" ON)

add_executable(sysguard
    app/main.cpp
)

target_include_directories(sysguard
    PRIVATE
        ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if(SYSGUARD_BUILD_TESTS)
    enable_testing()
    add_subdirectory(tests)
endif()