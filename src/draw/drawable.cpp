#include "drawable.h"
#include <format>

template<> inline void Drawable<sceVu0FVECTOR>::DrawImpl(sceVu0FVECTOR* obj, const char* label, float min, float max) {
    if (ImGui::SliderFloat4(label, (float *)obj, min, max)) {
        KlonoaMemory::Instance->WriteObj<sceVu0FVECTOR>((char*)obj - KlonoaMemory::Instance->ps2_ram);
    }
}

template<> inline void Drawable<sceVu0FMATRIX>::DrawImpl(sceVu0FMATRIX* obj, const char* label, float min, float max) {
    if (ImGui::SliderFloat4(std::format("{}[0]", label).c_str(), (float *)(*obj)[0], min, max)) {
        KlonoaMemory::Instance->WriteObj<sceVu0FVECTOR>((char*)(*obj)[0] - KlonoaMemory::Instance->ps2_ram);
    }
    if (ImGui::SliderFloat4(std::format("{}[1]", label).c_str(), (float *)(*obj)[1], min, max)) {
        KlonoaMemory::Instance->WriteObj<sceVu0FVECTOR>((char*)(*obj)[1] - KlonoaMemory::Instance->ps2_ram);
    }
    if (ImGui::SliderFloat4(std::format("{}[2]", label).c_str(), (float *)(*obj)[2], min, max)) {
        KlonoaMemory::Instance->WriteObj<sceVu0FVECTOR>((char*)(*obj)[2] - KlonoaMemory::Instance->ps2_ram);
    }
    if (ImGui::SliderFloat4(std::format("{}[3]", label).c_str(), (float *)(*obj)[3], min, max)) {
        KlonoaMemory::Instance->WriteObj<sceVu0FVECTOR>((char*)(*obj)[3] - KlonoaMemory::Instance->ps2_ram);
    }
}