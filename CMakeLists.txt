cmake_minimum_required(VERSION 3.28)

project(SIMPLE-2D-ENGINE LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

include(FetchContent)

enable_testing()

FetchContent_Declare(
    SFML
    GIT_REPOSITORY https://github.com/SFML/SFML.git
    GIT_TAG 3.1.0
    GIT_SHALLOW ON
    EXCLUDE_FROM_ALL
    SYSTEM
)

FetchContent_MakeAvailable(SFML)

add_library(Physics
    src/Vec2.cpp
    src/CircleShape.cpp
    src/BoxShape.cpp
    src/RigidBody.cpp
    src/World.cpp
)

target_include_directories(Physics
    PUBLIC
        include
)

add_executable(Sandbox
    sandbox/main.cpp
)

target_link_libraries(Sandbox
    PRIVATE
        Physics
        SFML::Graphics
)

add_executable(Tests
    tests/world_tests.cpp
)

target_link_libraries(Tests
    PRIVATE
        Physics
)
