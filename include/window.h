#include <iostream>
#include <GLFW/glfw3.h>
#include <imgui.h>

#define GLSL_VERSION "#version 330"

class Window {
public:
    GLFWwindow* window;
    ImGuiIO* io;
    void (*draw)();
    float fps;

    Window();
    ~Window();

    void loop();
};