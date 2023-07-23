#ifndef WINDOW_H
#define WINDOW_H

#include <iostream>
#include <imgui.h>
#include <SDL.h>

#define GLSL_VERSION "#version 330"

class Window {
public:
    SDL_Window* window;
    SDL_Renderer* renderer;
    ImGuiIO* io;
    void (*draw)();
    float fps;
    bool should_close;

    Window();
    ~Window();

    void loop();
    [[nodiscard]] float getScale() const;
};

#endif