#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.10)
add_compile_options(-Wall -Wextra)

project(Game_of_life)
set(EXECUTABLE_NAME "gol")

# Boost stuff
find_package(Boost 1.67 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# Define sources and executable
include_directories(include)
add_library(board "src/board.cpp")
add_executable(${EXECUTABLE_NAME} src/main.cpp)
target_link_libraries(${EXECUTABLE_NAME} board ${Boost_LIBRARIES})
