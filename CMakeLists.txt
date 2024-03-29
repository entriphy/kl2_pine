cmake_minimum_required(VERSION 3.17)
project(kl2_pine)
set(CMAKE_CXX_STANDARD 20)

# Global flags
add_compile_options(-m32)
add_link_options(-m32)

# SDL
set(SDL_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/SDL)
add_subdirectory(${SDL_DIR})

# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/imgui)
add_library(IMGUI STATIC)
target_sources(IMGUI 
    PRIVATE ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui.cpp
    PRIVATE ${IMGUI_DIR}/backends/imgui_impl_sdl3.cpp ${IMGUI_DIR}/backends/imgui_impl_sdlrenderer3.cpp
)
target_include_directories(IMGUI
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
    PUBLIC ${SDL_DIR}/include
)
target_link_libraries(IMGUI
    PUBLIC SDL3::SDL3 ${CMAKE_DL_LIBS}
)

# Klonoa 2 Decomp
set(KL2_DIR ${CMAKE_CURRENT_SOURCE_DIR}/lib/kl2)
set(KL2_INCLUDE_DIR ${KL2_DIR}/include)

# Klonoa 2 PINE
add_executable(${PROJECT_NAME}
    src/main.cpp
    src/window.cpp
    src/draw/hato_draw.cpp
    src/draw/nakano_draw.cpp
    src/draw/take_draw.cpp
)
target_link_libraries(${PROJECT_NAME} IMGUI SDL3::SDL3)
target_compile_options(${PROJECT_NAME} PUBLIC -DPS2_TYPE_STUBS)
if (WIN32)
    target_link_libraries(${PROJECT_NAME} wsock32 ws2_32)
    add_custom_command(
        TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND "${CMAKE_COMMAND}" -E copy_if_different "$<TARGET_FILE:SDL3::SDL3>" "$<TARGET_FILE_DIR:${PROJECT_NAME}>"
    )
else()
    target_compile_options(${PROJECT_NAME} PUBLIC -Wno-ignored-attributes)
endif()
target_include_directories(${PROJECT_NAME} PRIVATE
    include
    ${KL2_DIR}/include
    ${KL2_DIR}/src
)

