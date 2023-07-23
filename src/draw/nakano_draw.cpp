#include <imgui.h>
#include <format>
#include "klonoa_memory.h"
#include "stat.h"
#include "drawable.h"

// hato
#include "hato/ht_boss00.h"

#define OBJWORKBUFF_ADDRESS 0x00366BB0


template<> void Drawable<ROUTE>::DrawImpl(ROUTE *obj, const char *label, float min, float max) {
    ImGui::Text("vec:  %d %d %d", obj->vec.x, obj->vec.y, obj->vec.z);
    ImGui::Text("posi: %d %d %d", obj->posi.x, obj->posi.y, obj->posi.z);
    ImGui::Text("co:   %d", obj->co);
//    ImGui::Text("posif: %d %d %d", (obj.vx + vec.vx * num) / 4096.0f, (posi.vy + vec.vy * num) / 4096.0f, (posi.vz + vec.vz * num) / 4096.0f);
}

template<> void Drawable<RT_WRK>::DrawImpl(RT_WRK *obj, const char *label, float min, float max) {
    ImGui::Text("cnt: %d", obj->cnt);
    ImGui::Text("plc: %d", obj->plc);
    ImGui::Text("rtn: %d", obj->rtn);
    ImGui::Text("mcn: %d", obj->mcn);
    Drawable<ROUTE>::DrawTree((u32)obj->rtp, "rtn");
}

template<> void Drawable<OBJWORK>::DrawImpl(OBJWORK* obj, const char* label, float min, float max) {
    ImGui::Text("stat: %d", obj->stat);
    ImGui::Text("stat0: %d (%s)", obj->stat0, STAT0[obj->stat0].c_str());
    ImGui::Text("stat1: %d (%s)", obj->stat1, getStat1(obj->stat0, obj->stat1));

    Drawable<sceVu0FVECTOR>::Draw(&obj->posi, "posi", -2000.0f, 2000.0f);
    Drawable<sceVu0FVECTOR>::Draw(&obj->spd, "spd", -1.0f, 1.0f);
    Drawable<sceVu0FVECTOR>::Draw(&obj->muki, "muki", -1.0f, 1.0f);
    Drawable<sceVu0FVECTOR>::Draw(&obj->ang, "ang", -1.0f, 1.0f);
    Drawable<sceVu0FVECTOR>::Draw(&obj->rot, "rot", -3.14f, 3.14f);
    Drawable<RT_WRK>::DrawTree(&obj->rtw, "rtw");

    if (ImGui::TreeNode("reg")) {
        ImGui::Text("reg0: %d", obj->reg0);
        ImGui::Text("reg1: %d", obj->reg1);
        ImGui::Text("reg2: %d", obj->reg2);
        ImGui::Text("reg3: %d", obj->reg3);
        ImGui::Text("reg4: %d", obj->reg4);
        ImGui::Text("reg5: %d", obj->reg5);
        ImGui::Text("reg6: %d", obj->reg6);
        ImGui::Text("reg7: %d", obj->reg7);
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("freg")) {
        ImGui::Text("freg0: %f", obj->freg0);
        ImGui::Text("freg1: %f", obj->freg1);
        ImGui::Text("freg2: %f", obj->freg2);
        ImGui::Text("freg3: %f", obj->freg3);
        ImGui::Text("freg4: %f", obj->freg4);
        ImGui::Text("freg5: %f", obj->freg5);
        ImGui::Text("freg6: %f", obj->freg6);
        ImGui::Text("freg7: %f", obj->freg7);
        ImGui::TreePop();
    }

    std::string workLabel = std::format("work @ 0x{:08X}", (u32)obj->work);
    if (ImGui::TreeNode(workLabel.c_str())) {
        if (obj->work == nullptr) {
            ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
            ImGui::Text("NULL");
            ImGui::PopStyleColor();
        } else {
            switch (obj->stat0) {
                case 0:
                    ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
                    ImGui::Text("this should not happen lol");
                    ImGui::PopStyleColor();
                    break;
                case 7: // Hato
                    switch (obj->stat1) {
                        case 0:
                            ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
                            ImGui::Text("NULL");
                            ImGui::PopStyleColor();
                            break;
                        case 1: // htBOSS_02
                            break;
                        case 35: // htBOSS_00
                            Drawable<htBoss00Data>::Draw((u32)obj->work);
                            break;
                        case 36:
                            Drawable<htBoss00HandData>::Draw((u32)obj->work);
                            break;
                        default:
                            ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
                            ImGui::Text("Unknown work type for specified stat1");
                            ImGui::PopStyleColor();
                            break;
                    }
                    break;
                default:
                    ImGui::PushStyleColor(ImGuiCol_Text, COLOR_RED);
                    ImGui::Text("Unknown work type for specified stat0");
                    ImGui::PopStyleColor();
                    break;
            }
        }
        ImGui::TreePop();
    }
}

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