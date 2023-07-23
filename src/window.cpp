#include <imgui.h>
#include <stdexcept>
#include <backends/imgui_impl_sdl3.h>
#include <backends/imgui_impl_sdlrenderer3.h>

#include "window.h"

#define GLSL_VERSION "#version 330"

Window::Window() {
    // Initialize SDL
    if (SDL_Init(0) != 0) {
        throw std::runtime_error("Failed to initialize SDL");
    }
    window = SDL_CreateWindow("Klonoa 2 PINE", 720, 720, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    if (window == nullptr) {
        throw std::runtime_error("Could not create window");
    }
    SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);

    renderer = SDL_CreateRenderer(window, nullptr, SDL_RENDERER_PRESENTVSYNC | SDL_RENDERER_ACCELERATED);
    if (renderer == nullptr) {
        throw std::runtime_error("Could not create renderer");
    }

    const float scale{getScale()};
    SDL_SetRenderScale(renderer, scale, scale);
    should_close = false;

    // Initialize ImGui
    ImGui::CreateContext();
    ImGui::GetStyle().WindowRounding = 0.0f;

    io = &ImGui::GetIO();
    io->IniFilename = nullptr;
    io->ConfigWindowsMoveFromTitleBarOnly = true;

    ImGuiViewport *viewport = ImGui::GetMainViewport();
    ImGui_ImplSDL3_InitForSDLRenderer(window, renderer);
    ImGui_ImplSDLRenderer3_Init(renderer);
}

void Window::loop() {
    while (!should_close) {
        SDL_Event event{};
        while (SDL_PollEvent(&event) == 1) {
            ImGui_ImplSDL3_ProcessEvent(&event);
            if (event.type == SDL_EVENT_QUIT) {
                should_close = true;
            }
        }

        ImGui_ImplSDLRenderer3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(0, 0));
        ImGui::SetNextWindowSize(ImVec2(720, 720));

        draw();

        ImGui::End();
        ImGui::Render();

        SDL_SetRenderDrawColor(renderer, 100, 100, 100, 255);
        SDL_RenderClear(renderer);
        ImGui_ImplSDLRenderer3_RenderDrawData(ImGui::GetDrawData());
        SDL_RenderPresent(renderer);
    }
}

Window::~Window() {
    ImGui_ImplSDLRenderer3_Shutdown();
    ImGui_ImplSDL3_Shutdown();
    ImGui::DestroyContext();

    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

float Window::getScale() const {
    int window_width{0};
    int window_height{0};
    SDL_GetWindowSize(window, &window_width, &window_height);

    int render_output_width{0};
    int render_output_height{0};
    SDL_GetCurrentRenderOutputSize(renderer, &render_output_width, &render_output_height);

    const float scale_x{static_cast<float>(render_output_width) / static_cast<float>(window_width)};

    return scale_x;
}