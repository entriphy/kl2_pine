#include <format>
#include "window.h"
#include "klonoa_memory.h"
#include "common.h"
#include "draw.h"

KlonoaMemory* KlonoaMemory::Instance = nullptr;
Window window;

static const char* EmuStatuses[] = {
    "Running",
    "Paused",
    "Shutdown"
};

static const ImVec4 EmuStatusColors[] = {
    ImVec4(0.0, 1.0, 0.0, 1.0),
    ImVec4(1.0, 1.0, 0.0, 1.0),
    ImVec4(1.0, 0.0, 0.0, 1.0)
};

static const ImVec4 FpsColor = ImVec4(0.0, 0.75, 0.75, 1.0);

void draw() {
    u32 irqc = KlonoaMemory::Instance->Read<u32>(KlonoaMemory::IRQC_ADDRESS);
    u32 vision = KlonoaMemory::Instance->Read<u32>(KlonoaMemory::GAMEGBL_VISION); // GameGbl.vision

    ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    {
        if (ImGui::BeginMenuBar()) {
            // Show PINE status
            ImGui::Text("PCSX2:");
            PINE::PCSX2::EmuStatus status;
            try {
                status = KlonoaMemory::Instance->ipc->Status();
            } catch (PINE::Shared::IPCStatus ex) {
                status = PINE::PCSX2::EmuStatus::Shutdown;
            }
            ImGui::PushStyleColor(ImGuiCol_Text, EmuStatusColors[status]);
            ImGui::Text("%s", EmuStatuses[status]);
            ImGui::PopStyleColor();

            // Window FPS counter
            ImGui::Text("FPS:");
            ImGui::PushStyleColor(ImGuiCol_Text, FpsColor);
            ImGui::Text("%.0f", window.io->Framerate);
            ImGui::PopStyleColor();

            // IRQC (in-game frame) count
            ImGui::Text("IRQC:");
            ImGui::PushStyleColor(ImGuiCol_Text, FpsColor);
            ImGui::Text("%d", irqc);
            ImGui::PopStyleColor();

            // Current vision
            ImGui::Text("Vision:");
            ImGui::PushStyleColor(ImGuiCol_Text, FpsColor);
            ImGui::Text("%x", vision);
            ImGui::PopStyleColor();

            ImGui::EndMenuBar();
        }
    }

    if (ImGui::TreeNode("Nakano")) {
        NakanoDraw();
        ImGui::TreePop();
    }
}

int main(int argc, char* argv[]) {
    KlonoaMemory::Instance = new KlonoaMemory();

    if (KlonoaMemory::Instance->ipc == nullptr) {
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            "Failed to connect to PCSX2. Ensure PINE is enabled and PCSX2 is running Klonoa 2.",
            nullptr);
        return 1;
    }

    char* gameId = KlonoaMemory::Instance->ipc->GetGameID();
    if (strcmp(gameId, "SLUS-20151") != 0) {
        std::string message = std::format("PCSX2 is not running Klonoa 2 NTSC (SLUS-20151), got {}.", gameId);
        SDL_ShowSimpleMessageBox(
            SDL_MESSAGEBOX_ERROR,
            "Error",
            message.c_str(),
            nullptr);
        return 2;
    }

    window.draw = draw;
    window.loop();
    return 0;
}