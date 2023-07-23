#include "common.h"
#include "drawable.h"

template<> void Drawable<COORD>::DrawImpl(COORD *obj, const char *label, float min, float max) {
    Drawable<sceVu0FVECTOR>::Draw(&obj->Rot, "Rot", -3.14f, 3.14f);
    Drawable<sceVu0FVECTOR>::Draw(&obj->Trans, "Trans", -2000.0f, 2000.0f);

    Drawable<sceVu0FMATRIX>::DrawTree(&obj->Mtx, "Mtx", -10.0f, 10.0f);
    Drawable<sceVu0FMATRIX>::DrawTree(&obj->MtxSav, "MtxSav", -10.0f, 10.0f);
    Drawable<COORD>::DrawTree((u32)obj->Super, "Super");

    ImGui::Text("WipCnt: %f", obj->WipCnt);
    ImGui::Text("Flag: %d", obj->Flag);
}

template<> void Drawable<ACTTBL>::DrawImpl(ACTTBL *obj, const char *label, float min, float max) {
    ImGui::Text("mot: %d", obj->mot);
    ImGui::Text("stopflag: %d", obj->stopflag);
    ImGui::Text("sync: %d", obj->sync);
    ImGui::Text("incnt: %d", obj->incnt);
    ImGui::Text("outcnt: %d", obj->outcnt);
    ImGui::Text("inmode: %d", obj->inmode);
    ImGui::Text("outmode: %d", obj->outmode);
    ImGui::Text("onflag: %016jX", obj->onflag);
}

template<> void Drawable<PARTS>::DrawImpl(PARTS *obj, const char *label, float min, float max) {
    ImGui::Text("jblock_adrs: 0x%08X", (u32)obj->jblock_adrs);
    ImGui::Text("sfx_adrs: 0x%08X", (u32)obj->sfx_adrs);
    ImGui::Text("vert_adrs: 0x%08X", (u32)obj->vert_adrs);
    ImGui::Text("norm_adrs: 0x%08X", (u32)obj->norm_adrs);
    ImGui::Text("vert_adrs_mime0: 0x%08X", (u32)obj->vert_adrs_mime0);
    ImGui::Text("norm_adrs_mime0: 0x%08X", (u32)obj->norm_adrs_mime0);
    ImGui::Text("vert_adrs_mime1: 0x%08X", (u32)obj->vert_adrs_mime1);
    ImGui::Text("norm_adrs_mime1: 0x%08X", (u32)obj->norm_adrs_mime1);
    ImGui::Text("uv_adrs: 0x%08X", (u32)obj->uv_adrs);
    ImGui::Text("prim_adrs: 0x%08X", (u32)obj->prim_adrs);
    ImGui::Text("vert_wt_adrs: 0x%08X", (u32)obj->vert_wt_adrs);
    ImGui::Text("norm_wt_adrs: 0x%08X", (u32)obj->norm_wt_adrs);
    ImGui::Text("GmsAdr: 0x%08X", (u32)obj->GmsAdr);

    ImGui::Text("MimeWeight: %f", obj->MimeWeight);
    ImGui::Text("type: %d", obj->type);
    ImGui::Text("jblock_num: %d", obj->jblock_num);
    ImGui::Text("vert_num: %d", obj->vert_num);
    ImGui::Text("norm_num: %d", obj->norm_num);
    ImGui::Text("uv_num: %d", obj->uv_num);
    ImGui::Text("prim_num: %d", obj->prim_num);
    ImGui::Text("prim_blk: %d", obj->prim_blk);
    ImGui::Text("coord_id: %d", obj->coord_id);
    ImGui::Text("GsEnvInd: %d", obj->GsEnvInd);
    ImGui::Text("SpecType: %d", obj->SpecType);
    ImGui::Text("OutLine: %d", obj->OutLine);
}

template<> void Drawable<MBLOCK>::DrawImpl(MBLOCK *obj, const char *label, float min, float max) {
    ImGui::Text("pAct: 0x%08X", (u32)obj->pAct);

    ImGui::Text("MotionCnt: %f", obj->MotionCnt);
    ImGui::Text("MotionEndCnt: %f", obj->MotionEndCnt);
    ImGui::Text("CntSpeed: %f", obj->CntSpeed);
    ImGui::Text("Weight: %f", obj->Weight);
    ImGui::Text("TargetWeight: %f", obj->TargetWeight);
    ImGui::Text("InCnt: %f", obj->InCnt);
    ImGui::Text("OutCnt: %f", obj->OutCnt);
    ImGui::Text("OnFlag: %016jX", obj->OnFlag);
    ImGui::Text("StopFlag: %d", obj->StopFlag);
    ImGui::Text("Type: %d", obj->Type);
    ImGui::Text("SyncFlag: %d", obj->SyncFlag);
    ImGui::Text("InMode: %d", obj->InMode);
    ImGui::Text("OutMode: %d", obj->OutMode);
}

template<> void Drawable<MOTION>::DrawImpl(MOTION *obj, const char *label, float min, float max) {
    Drawable<COORD>::DrawTree((u32)obj->pBaseCoord, "pBaseCoord");
    Drawable<COORD>::DrawTree((u32)obj->pCoord, "pCoord");
    Drawable<ACTTBL>::DrawTree((u32)obj->pActtbl, "pActtbl");
    if (ImGui::TreeNode("Mb")) {
        for (int i = 0; i < 4; i++) {
            Drawable<MBLOCK>::DrawTree(&obj->Mb[i], std::format("Mb[{}]", i).c_str());
        }
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("IpWeight")) {
        for (int i = 0; i < 16; i++) {
            drawFloat4(std::format("IpWeight[{}]", i * 4).c_str(), &obj->IpWeight[i * 4], -1.0f, 1.0f);
        }
        ImGui::TreePop();
    }

    ImGui::Text("ActAdrs: 0x%08X", (u32)obj->ActAdrs);
    ImGui::Text("pInf: 0x%08X", (u32)obj->pInf);
    ImGui::Text("pItr: 0x%08X", (u32)obj->pItr);
    ImGui::Text("pItrW: 0x%08X", (u32)obj->pItrW);

    ImGui::Text("SubScale: %f", obj->SubScale);
    ImGui::Text("ActNum: %d", obj->ActNum);
    ImGui::Text("ActNumMax: %d", obj->ActNumMax);
    ImGui::Text("CoordNum: %d", obj->CoordNum);
    ImGui::Text("BaseIndex: %d", obj->BaseIndex);
    ImGui::Text("BaseMixIndex: %d", obj->BaseMixIndex);
    ImGui::Text("IpIndex: %d", obj->IpIndex);
    ImGui::Text("IpMixIndex: %d", obj->IpMixIndex);
    ImGui::Text("EndFlag: %d", obj->EndFlag);
}

template<> void Drawable<SFXOBJ>::DrawImpl(SFXOBJ* obj, const char* label, float min, float max) {
    Drawable<sceVu0FVECTOR>::Draw(&obj->ScaleVector, "ScaleVector", -5.0f, 5.0f);
    drawFloat("ShadowSize", &obj->ShadowSize, 0.0, 500.0);
    drawFloat("ShadowOffset", &obj->ShadowOffset, 0.0, 500.0);
    drawFloat("ShadowRange", &obj->ShadowRange, 0.0, 500.0);

    Drawable<MOTION>::DrawTree((u32)obj->pMot, "pMot");
    Drawable<SFXOBJ>::DrawTree((u32)obj->pObjSub, "pObjSub");
    Drawable<SFXOBJ>::DrawTree((u32)obj->pObjTop, "pObjTop");
    Drawable<sceVu0FMATRIX>::DrawTree((u32)obj->pLightColor, "pLightColor");
    Drawable<sceVu0FMATRIX>::DrawTree((u32)obj->pNormalLight, "pNormalLight");
    if (ImGui::TreeNode("pParts")) {
        for (int i = 0; i < obj->PartsNum; i++) {
            std::string name = "pParts[" + std::to_string(i) + "]";
            Drawable<PARTS>::DrawTree((u32)obj->pParts + sizeof(PARTS) * i, name.c_str());
        }

        ImGui::TreePop();
    }

    ImGui::Text("PartsNum: %d", obj->PartsNum);
    ImGui::Text("scale: %f", obj->scale);
    ImGui::Text("ObjNum: %d", obj->ObjNum);
}