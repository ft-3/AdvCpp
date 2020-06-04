#Change this if you need to target a specific CMake version
cmake_minimum_required(VERSION 3.10)
add_compile_options(-Wall -Wextra)

project(Blinker)

include_directories(include)

# Define sources and executable
set(EXECUTABLE_NAME "blinker")
#add_library(menu "src/menu.cpp")
add_executable(${EXECUTABLE_NAME} src/main.cpp)


# Detect and add SFML
#See the FindSFML.cmake file for additional details and instructions
# find_package(SFML 2.5 COMPONENTS system graphics window REQUIRED)
# if(SFML_FOUND)
# target_link_libraries(${EXECUTABLE_NAME} menu canvas sfml-graphics sfml-window sfml-system)
# endif()
