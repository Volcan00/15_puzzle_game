cmake_minimum_required(VERSION 3.10)

project(15_Puzzle_Game)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Include directories
include_directories(include)

# Main executable
add_executable(main 
    src/main.cpp
    src/Board.cpp
    src/Direction.cpp
    src/Point.cpp
    src/Tile.cpp
    src/UserInput.cpp)

# Google Test setup
enable_testing()

# Find Google Test package
find_package(GTest REQUIRED)
include_directories(${GTEST_INCLUDE_DIRS})

# Add test executable (do not include main.cpp here)
add_executable(main_tests 
    tests/main_tests.cpp
    src/Board.cpp
    src/Direction.cpp
    src/Point.cpp
    src/Tile.cpp
    src/UserInput.cpp)

# Link test executable against Google Test libraries
target_link_libraries(main_tests ${GTEST_LIBRARIES} pthread)

# Add tests
add_test(NAME main_tests COMMAND main_tests)
