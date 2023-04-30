cmake_minimum_required(VERSION 3.17)
project(memory_editor)
set(CMAKE_CXX_STANDARD 20)
add_subdirectory("lib")

find_package(IMGUI REQUIRED)
link_libraries(IMGUI)
include_directories(include)
add_compile_options(-O1 -m32)
add_link_options(-m32)

add_executable(${PROJECT_NAME}
        src/window.cpp
        src/main.cpp)
