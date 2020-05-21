#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.10)
add_compile_options(-Wall -Wextra)

project(Game_of_life)
set(EXECUTABLE_NAME "gol")

# Boost stuff
find_package(Boost 1.67 COMPONENTS program_options REQUIRED)
include_directories(${Boost_INCLUDE_DIR})

# SFML package
find_package(SFML 2.5 COMPONENTS system graphics window REQUIRED)

# Define sources and executable
include_directories(include)
add_library(board "src/board.cpp")
add_executable(${EXECUTABLE_NAME} src/main.cpp)
if(SFML_FOUND)
    target_link_libraries(${EXECUTABLE_NAME} board ${Boost_LIBRARIES} menu sfml-graphics sfml-window sfml-system)
else()
    target_link_libraries(${EXECUTABLE_NAME} board ${Boost_LIBRARIES})
endif()
