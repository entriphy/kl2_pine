#ifndef DRAWABLE_H
#define DRAWABLE_H

#include "klonoa_memory.h"
#include <imgui.h>
#include <format>

const ImVec4 COLOR_RED = ImVec4(1.0f, 0.0f, 0.0f, 1.0f);

template <class T>
class Drawable {
private:
    static void DrawImpl(T* obj, const char* label, float min, float max) {
        ImGui::Text("Unimplemented :(");
    }

public:
    static void Draw(u32 address, const char* label = "n/a", float min = -1.0f, float max = 1.0f) {
        if (address == 0) {
            ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
            ImGui::Text("NULL");
            ImGui::PopStyleColor();
            return;
        }

        T* obj = KlonoaMemory::Instance->ReadObj<T>(address);
        DrawImpl(obj, label, min, max);
    }

    static void Draw(T* obj, const char* label = "n/a", float min = -1.0f, float max = 1.0f) {
        DrawImpl(obj, label, min, max);
    }

    static void DrawTree(u32 address, const char* label = "n/a", float min = -1.0f, float max = 1.0f) {
        std::string newLabel = std::format("{} @ 0x{:08X}", label, address);
        if (ImGui::TreeNode(newLabel.c_str())) {
            Draw(address, newLabel.c_str(), min, max);
            ImGui::TreePop();
        }
    }

    static void DrawTree(T* obj, const char* label = "n/a", float min = -1.0f, float max = 1.0f) {
        std::string newLabel = std::format("{} @ 0x{:08X}", label, (char*)obj - KlonoaMemory::Instance->ps2_ram);
        if (ImGui::TreeNode(newLabel.c_str())) {
            Draw(obj, newLabel.c_str(), min, max);
            ImGui::TreePop();
        }
    }
};

inline void drawBool(const char* name, bool* ptr) {
    if (ImGui::Checkbox(name, ptr)) {
        KlonoaMemory::Instance->Write<char>((char*)ptr - KlonoaMemory::Instance->ps2_ram, *ptr);
    }
}

inline void drawShort(const char* name, short* ptr, short min, short max) {
    if (ImGui::SliderScalar(name, ImGuiDataType_S16, ptr, &min, &max)) {
        KlonoaMemory::Instance->Write<short>((char*)ptr - KlonoaMemory::Instance->ps2_ram, *ptr);
    }
}

inline void drawu16(const char* name, u16* ptr, u16 min, u16 max) {
    if (ImGui::SliderScalar(name, ImGuiDataType_U16, ptr, &min, &max)) {
        KlonoaMemory::Instance->Write<u16>((char*)ptr - KlonoaMemory::Instance->ps2_ram, *ptr);
    }
}

inline void drawInt(const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt(name, ptr, min, max)) {
        KlonoaMemory::Instance->Write<int>((char*)ptr - KlonoaMemory::Instance->ps2_ram, *ptr);
    }
}

inline void drawInt2(const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt2(name, ptr, min, max)) {
        KlonoaMemory::Instance->Write<long>((char*)ptr - KlonoaMemory::Instance->ps2_ram, *ptr);
    }
}

inline void drawInt3(const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt3(name, ptr, min, max)) {
        KlonoaMemory::Instance->WriteObj<IVECTOR>((char*)ptr - KlonoaMemory::Instance->ps2_ram);
    }
}

inline void drawFloat(const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat(name, ptr, min, max)) {
        KlonoaMemory::Instance->Write<float>((char*)ptr - KlonoaMemory::Instance->ps2_ram, *ptr);
    }
}

inline void drawFloat2(const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat2(name, ptr, min, max)) {
        KlonoaMemory::Instance->Write<u64>((char*)ptr - KlonoaMemory::Instance->ps2_ram, *(u64 *)ptr);
    }
}

inline void drawFloat3(const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat3(name, ptr, min, max)) {
        KlonoaMemory::Instance->WriteObj<IVECTOR>((char*)ptr - KlonoaMemory::Instance->ps2_ram);
    }
}

inline void drawFloat4(const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat4(name, ptr, min, max)) {
        KlonoaMemory::Instance->WriteObj<IVECTOR>((char*)ptr - KlonoaMemory::Instance->ps2_ram);
    }
}

#endif

