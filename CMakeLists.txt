cmake_minimum_required(VERSION 3.20)

project(Astrophysics-Engine VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Release CACHE STRING "Build type" FORCE)
endif()

add_compile_options(-Wall -Wextra -Wpedantic)

if(CMAKE_BUILD_TYPE STREQUAL "Debug")
    add_compile_options(-fsanitize=address,undefined)
    add_link_options(-fsanitize=address,undefined)
endif()

include(FetchContent)
FetchContent_Declare(
        googletest
        GIT_REPOSITORY https://github.com/google/googletest.git
        GIT_TAG        v1.14.0
)
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()
add_subdirectory(tests)

include_directories(${CMAKE_SOURCE_DIR}/include)
add_executable(Astrophysics-Engine
        src/main.cpp
        include/Orbit.h
        src/Orbit.cpp
        include/CelestialBody.h
        src/CelestialBody.cpp
        include/Spacecraft.h
        src/Spacecraft.cpp
        include/StateVector.h
        src/StateVector.cpp
)