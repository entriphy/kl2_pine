#include <imgui.h>
#include <format>
#include "klonoa_memory.h"
#include "stat.h"
#include "drawable.h"
#include "draws.h"

void NakanoDraw() {
    KlonoaMemory* memory = KlonoaMemory::Instance;

    if (ImGui::TreeNode("ObjWorkBuff")) {
        for (int i = 0; i < 128; i++) {
            u32 objworkAddress = OBJWORKBUFF_ADDRESS + i * sizeof(OBJWORK);
            s16 stat0 = memory->Read<s16>(objworkAddress + offsetof(OBJWORK, stat0));
            if (stat0 == 0) {
                continue;
            }

            s16 stat1 = memory->Read<s16>(objworkAddress + offsetof(OBJWORK, stat1));
            std::string name = std::format("ObjWorkBuff[{}] ({}: {}) @ 0x{:08X}", i, STAT0[stat0], getStat1(stat0, stat1), objworkAddress);
            if (ImGui::TreeNode(name.c_str())) {
                Drawable<OBJWORK>::Draw(objworkAddress);
                ImGui::TreePop();
            }
        }

        ImGui::TreePop();
    }

    if (ImGui::TreeNode("p1_packet")) {
        if (KlonoaMemory::Instance->ipc->Status() != PINE::PCSX2::EmuStatus::Paused) {
            ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
            ImGui::Text("PCSX2 must be paused first!");
            ImGui::PopStyleColor();
        } else {
            ImGui::Text("wip :)");
        }

        ImGui::TreePop();
    }
}