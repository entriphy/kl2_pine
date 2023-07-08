#include <iostream>
#include <ostream>
#include <string>
#include <stdio.h>
#include <math.h>

#include <GLFW/glfw3.h>
#include <imgui.h>
#include "pine.h"
#include "types.h" // Modified to work on 64-bit (removes pointers)
#include "klonoa_memory.h"
#include "window.h"

#include "imgui_impl_glfw.h"
#include "imgui_impl_opengl3.h"

#define GLSL_VERSION "#version 330"

static const char* EmuStatuses[] = { "Running", "Paused", "Shutdown" };
static const ImVec4 EmuStatusColors[] = { ImVec4(0.0, 1.0, 0.0, 1.0), ImVec4(1.0, 1.0, 0.0, 1.0), ImVec4(1.0, 0.0, 0.0, 1.0) };
static const ImVec4 FpsColor = ImVec4(0.0, 0.75, 0.75, 1.0);

KlonoaMemory memory;
Window window;

void draw() {
    uint irqc = memory.Read<uint>(KlonoaMemory::IRQC_ADDRESS);
    uint vision = memory.Read<uint>(KlonoaMemory::GAMEGBL_VISION); // GameGbl.vision
    uint vtWaveAddr = memory.Read<uint>(KlonoaMemory::VT_WAVE_ADDRESS);
    uint camNorAddr = memory.Read<uint>(KlonoaMemory::CAMNOR_ADDRESS);
    uint camFixAddr = memory.Read<uint>(KlonoaMemory::CAMFIX_ADDRESS);

    uint pKlonoa = memory.Read<uint>(KlonoaMemory::GAMEGBL_KLONOA_ADDRESS); // GameGbl.klonoa
    uint hfmircnt = memory.Read<uint>(KlonoaMemory::HFMIRCNT_ADDRESS);
    
    ImGui::Begin("Window", nullptr, ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoMove | ImGuiWindowFlags_NoResize);
    {
        if (ImGui::BeginMenuBar()) {
            // Show PINE status
            ImGui::Text("PINE:");
            PINE::PCSX2::EmuStatus status;
            try {
                status = memory.ipc->Status();
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

            ImGui::EndMenuBar();
        }

        ImGui::Text("vision:        %04x", vision);
        ImGui::Text("");

        if (ImGui::TreeNode("Klonoa")) {
            OBJWORK* klonoa = memory.ReadObj<OBJWORK>(pKlonoa);
            klonoa->drawObj(&memory);

            uint pLevelPack = memory.Read<uint>(KlonoaMemory::LEVEL_PACK_PTR_ADDRESS);
            KlonoaMemory::FHM* levelPack = memory.ReadFHM(pLevelPack);
            KlonoaMemory::FHM* nakanoPack = levelPack->ReadFHM(&memory, 0);
            KlonoaMemory::FHM* chrPack = nakanoPack->ReadFHM(&memory, 1);
            KlonoaMemory::FHM* klonoaPack = chrPack->ReadFHM(&memory, 371);
            KlonoaMemory::FHM* klmPack = klonoaPack->ReadFHM(&memory, 0);
            KlonoaMemory::FHM* klonoaAnimationPack = klmPack->ReadFHM(&memory, 3);

            if (KlonoaMemory::IsValidPointer(klonoaAnimationPack->GetAddress(&memory))) {
                klMODEL* model = klonoa->prim.Get<klMODEL>(&memory);
                uint nameAddress = klonoaAnimationPack->GetFileAddress(&memory, model->klm.ActNum) + 8;
                if (!KlonoaMemory::IsValidPointer(nameAddress)) return;
                char* animation = (char *)(memory.ReadObj<ulong>(nameAddress));
                ImGui::Text("ActNum  %d (%s)", model->klm.ActNum, animation);
            }

            ImGui::TreePop();
        }

        if (ImGui::TreeNode("ObjWorkBuff")) {
            for (int i = 0; i < 128; i++) {
                uint objworkAddress = KlonoaMemory::OBJWORK_BUFF_ADDRESS + i * sizeof(OBJWORK);
                s16 stat0 = memory.Read<s16>(objworkAddress + offsetof(OBJWORK, stat0));
                s16 stat1 = memory.Read<s16>(objworkAddress + offsetof(OBJWORK, stat1));
                std::string name = "ObjWorkBuff[" + std::to_string(i) + "] " + stat0s[stat0] + ": " + getStat1(stat0, stat1);
                if (stat0 != 0 && ImGui::TreeNode(name.c_str())) {
                    OBJWORK* objwork = memory.ReadObj<OBJWORK>(objworkAddress);
                    objwork->drawObj(&memory);
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }

        if (KlonoaMemory::IsValidPointer(vtWaveAddr)) {
            uint waveCount = memory.Read<uint>(vtWaveAddr);
            for (int i = 0; i < waveCount; i++) {
                std::string name = "Wave_";
                name.push_back('0' + i);
                if (ImGui::TreeNode(name.c_str())) {
                    kitWaveParam* wave = memory.ReadObj<kitWaveParam>(vtWaveAddr + 0x10 + i * sizeof(kitWaveParam));
                    wave->draw(&memory);
                    ImGui::TreePop();
                }
            }
        }

        if (KlonoaMemory::IsValidPointer(camNorAddr) && ImGui::TreeNode("Normal Cameras")) {
            int i = 0;
            while ((memory.Read<int>(camNorAddr + i * sizeof(nkCamNOR) + offsetof(nkCamNOR, flg)) & 128) == 0) {
                std::string name = "camNor[" + std::to_string(i) + "]";
                if (ImGui::TreeNode(name.c_str())) {
                    nkCamNOR* cam = memory.ReadObj<nkCamNOR>(camNorAddr + i * sizeof(nkCamNOR));
                    cam->draw(&memory);
                    ImGui::TreePop();
                }
                i++;
            }
            ImGui::TreePop();
        }

        if (KlonoaMemory::IsValidPointer(camFixAddr) && ImGui::TreeNode("Fixed Cameras")) {
            uint count = 9;
            for (int i = 0; i < count; i++) {
                std::string name = "camFix[" + std::to_string(i) + "]";
                if (ImGui::TreeNode(name.c_str())) {
                    nkCamFIX* cam = memory.ReadObj<nkCamFIX>(camFixAddr + i * sizeof(nkCamFIX));
                    cam->draw(&memory);
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("GameGbl")) {
            GAME_WORK* GameGbl = memory.ReadObj<GAME_WORK>(KlonoaMemory::GAMEGBL_ADDRESS);
            GameGbl->draw(&memory);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("ViCon")) {
            VWork* ViCon = memory.ReadObj<VWork>(KlonoaMemory::VICON_ADDRESS);
            ViCon->draw(&memory);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("RpcArg")) {
            int* RpcArg = (int*)memory.Read(KlonoaMemory::RPCARG_ADDRESS, sizeof(int) * 16);
            for (int i = 0; i < 16; i++) {
                ImGui::Text("0x%x (%d)", RpcArg[i], RpcArg[i]);
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("RpcRecvBuff")) {
            int* RpcRecv = (int*)memory.Read(KlonoaMemory::RPCRECVBUF_ADDRESS, sizeof(int) * 32);
            for (int i = 0; i < 16; i++) {
                ImGui::Text("0x%x (%d)", RpcRecv[i], RpcRecv[i]);
            }
            ImGui::Text("---");
            for (int i = 0; i < 16; i++) {
                ImGui::Text("0x%x (%d)", RpcRecv[16 + i], RpcRecv[16 + i]);
            }
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("SndMainBuffer")) {
            int* SndMainBuffer = (int*)memory.Read(KlonoaMemory::SNDMAINBUFFER_ADDRESS, sizeof(int) * 16);
            for (int i = 0; i < 16; i++) {
                ImGui::Text("0x%x", SndMainBuffer[i]);
            }
            ImGui::TreePop();
        }

        if (hfmircnt > 0 && ImGui::TreeNode("hfmirbuf")) {
            HFMIR* hfmirbuf = (HFMIR*)memory.Read(KlonoaMemory::HFMIRBUF_ADDRESS, sizeof(HFMIR) * hfmircnt);
            for (int i = 0; i < hfmircnt; i++) {
                std::string name = "hfmirbuf[" + std::to_string(i) + "]";
                if (ImGui::TreeNode(name.c_str())) {
                    hfmirbuf[i].draw(&memory);
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        } 

        // gp_value: 0x3FE070
    }
}

int main() {
    window.draw = draw;
    window.loop();

    return 0;
}
