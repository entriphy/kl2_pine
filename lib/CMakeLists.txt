# Flags
add_compile_options(-m32)
add_link_options(-m32)

# GLFW
set(GLFW_DIR ${CMAKE_CURRENT_SOURCE_DIR}/glfw)
set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
add_subdirectory(${GLFW_DIR})

# ImGui
set(IMGUI_DIR ${CMAKE_CURRENT_SOURCE_DIR}/imgui)
add_library(IMGUI STATIC)
target_sources(IMGUI 
    PRIVATE ${IMGUI_DIR}/imgui_demo.cpp ${IMGUI_DIR}/imgui_draw.cpp ${IMGUI_DIR}/imgui_tables.cpp ${IMGUI_DIR}/imgui_widgets.cpp ${IMGUI_DIR}/imgui.cpp
    PRIVATE ${IMGUI_DIR}/backends/imgui_impl_opengl3.cpp ${IMGUI_DIR}/backends/imgui_impl_glfw.cpp
)
target_include_directories( IMGUI
    PUBLIC ${IMGUI_DIR}
    PUBLIC ${IMGUI_DIR}/backends
    PUBLIC ${SDL3_DIR}/include
)
target_link_libraries(IMGUI PUBLIC glfw ${CMAKE_DL_LIBS})

