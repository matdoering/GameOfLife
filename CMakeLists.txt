cmake_minimum_required (VERSION 2.6)
cmake_policy(SET CMP0048 NEW)
project (GameOfLife VERSION 1.0)

# curses setup
find_package(Curses REQUIRED)
include_directories(${CURSES_INCLUDE_DIR})

execute_process(
COMMAND ${CMAKE_COMMAND} -E tar xzf ${CMAKE_CURRENT_SOURCE_DIR}/googletest-release-1.8.1.tar.gz
)

# Add test cpp file
add_executable(GameOfLife GameOfLife.cpp Board.cpp Cell.cpp)
add_executable(GameOfLifeTest GameOfLifeTest.cpp Board.cpp Cell.cpp)

################################
# GTest
################################



ADD_SUBDIRECTORY (${CMAKE_BINARY_DIR}/googletest-release-1.8.1)
include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})

enable_testing()
# link to curses
target_link_libraries(GameOfLife ${CURSES_LIBRARIES})

# Link test executable against gtest & gtest_main
target_link_libraries(GameOfLifeTest gtest gtest_main)
add_test( GameOfLifeTest GameOfLifeTest )
