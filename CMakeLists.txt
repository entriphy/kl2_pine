cmake_minimum_required(VERSION 3.17)
project(kl2_pine)
set(CMAKE_CXX_STANDARD 20)

# Global flags
add_compile_options(-O0 -m32 -DPS2_TYPE_STUBS)
add_link_options(-m32)

# GLFW
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})

# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui)
add_library(IMGUI STATIC)
target_sources(IMGUI 
    PRIVATE ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui.cpp
    PRIVATE ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)
target_include_directories(IMGUI
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
    PUBLIC ${SDL3_DIR}/include
)
target_link_libraries(IMGUI
    PUBLIC glfw ${CMAKE_DL_LIBS}
)

# Klonoa 2 Decomp
set(KL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/kl2)
set(KL2_INCLUDE_DIR ${KL2_DIR}/include)

# Klonoa 2 PINE
find_package(IMGUI REQUIRED)
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/window.cpp
    src/draw/drawable.cpp
    src/draw/hato_draw.cpp
    src/draw/nakano_draw.cpp
    src/draw/take_draw.cpp
)
target_link_libraries(${PROJECT_NAME} IMGUI)
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    ${KL2_DIR}/include
    ${KL2_DIR}/src
)

