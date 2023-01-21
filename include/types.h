#ifndef TYPES_H
#define TYPES_H

#include "ps2_pointer.h"
#include "imgui.h"

typedef unsigned char u8;
typedef volatile u8 vu8;
typedef signed char s8;
typedef volatile s8 vs8;

typedef unsigned short u16;
typedef volatile u16 vu16;
typedef signed short s16;
typedef volatile s16 vs16;

typedef unsigned int u32;
typedef volatile u32 vu32;
typedef signed int s32;
typedef volatile s32 vs32;

typedef unsigned long long u64;
typedef volatile u64 vu64;
typedef signed long long s64;
typedef volatile s64 vs64;

typedef struct FVECTOR {
	float x;
	float y;
	float z;
	float w;

    void draw(KlonoaMemory* mem, const char* name, float min, float max) {
        if (ImGui::SliderFloat4(name, (float *)this, min, max)) {
            mem->WriteObj<FVECTOR>((char*)this - mem->ps2_ram);
        }
    }

    void drawColor(KlonoaMemory* mem, const char* name) {
        if (ImGui::ColorEdit3(name, (float *)this)) {
            mem->WriteObj<FVECTOR>((char*)this - mem->ps2_ram);
        }
    }
} FVECTOR __attribute__((aligned(16)));

typedef struct {
	int	x;
	int	y;
	int	z;
	int	w;
} IVECTOR __attribute__((aligned(16)));

typedef struct {
	short	x;
	short	y;
	short	z;
	short	w;
} SVECTOR __attribute__((aligned(16)));

typedef struct {
	FVECTOR m[4];
} FMATRIX __attribute__((aligned(16)));

typedef struct {
    void Draw(KlonoaMemory* mem) {
        ImGui::Text("none :(");
    }
} GeneralWork;
typedef struct {} Prim;

struct psSVECTOR
{
    short vx;
    short vy;
    short vz;
    short pad;
};

struct psVECTOR
{
    int vx;
    int vy;
    int vz;
    int pad;
};

void drawBool(KlonoaMemory* mem, const char* name, bool* ptr) {
    if (ImGui::Checkbox(name, ptr)) {
        mem->Write<char>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

void drawShort(KlonoaMemory* mem, const char* name, short* ptr, short min, short max) {
    if (ImGui::SliderScalar(name, ImGuiDataType_S16, ptr, &min, &max)) {
        mem->Write<short>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

void drawUShort(KlonoaMemory* mem, const char* name, ushort* ptr, ushort min, ushort max) {
    if (ImGui::SliderScalar(name, ImGuiDataType_U16, ptr, &min, &max)) {
        mem->Write<ushort>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

void drawInt(KlonoaMemory* mem, const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt(name, ptr, min, max)) {
        mem->Write<int>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

void drawInt3(KlonoaMemory* mem, const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt3(name, ptr, min, max)) {
        mem->WriteObj<IVECTOR>((char*)ptr - mem->ps2_ram);
    }
}

void drawFloat(KlonoaMemory* mem, const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat(name, ptr, min, max)) {
        mem->Write<float>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

void drawFloat2(KlonoaMemory* mem, const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat2(name, ptr, min, max)) {
        mem->Write<ulong>((char*)ptr - mem->ps2_ram, *(ulong *)ptr);
    }
}

void drawFloat3(KlonoaMemory* mem, const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat3(name, ptr, min, max)) {
        mem->WriteObj<IVECTOR>((char*)ptr - mem->ps2_ram);
    }
}

struct ROUTE
{
    psSVECTOR vec;
    psVECTOR posi;
    ushort co;
    ushort DUMMY;

    void draw(KlonoaMemory* mem, int cnt) {
        short num = (short)(cnt >> 12);
        ImGui::Text("vec:  %d %d %d", vec.vx, vec.vy, vec.vz);
        ImGui::Text("posi: %d %d %d", posi.vx, posi.vy, posi.vz);
        ImGui::Text("co: %d", co);
        ImGui::Text("posif: %d %d %d", (posi.vx + vec.vx * num) / 4096.0f, (posi.vy + vec.vy * num) / 4096.0f, (posi.vz + vec.vz * num) / 4096.0f);
    }
};

struct RT_WRK
{
    int cnt;
    PS2Pointer<ROUTE> rtp;
    short plc;
    short rtn;
    int mcn;

    void draw(KlonoaMemory* mem) {
        ImGui::Text("cnt: %d", cnt);
        ImGui::Text("plc: %d", plc);
        ImGui::Text("rtn: %d", rtn);
        ImGui::Text("mcn: %d", mcn);
        if (ImGui::TreeNode("rtp")) {
            ROUTE* route = rtp.Get(mem, plc * sizeof(ROUTE));
            route->draw(mem, cnt);
            ImGui::TreePop();
        }
    }
};

typedef struct HERO_WORK HERO_WORK;
void DrawHeroWork(KlonoaMemory* mem, HERO_WORK* work);

typedef struct ZAKO_WORK ZAKO_WORK;
void DrawZakoWork(KlonoaMemory* mem, ZAKO_WORK* work);

// Size: 0xF0
typedef struct _OBJWORK {
    u32 pers; // 0x00
    u32 draw; // 0x04
    u32 drmir; // 0x08
    u32 drmiref; // 0x0C
    u32 dreff; // 0x10
    PS2Pointer<Prim> prim; // 0x14, klMODEL, 
    PS2Pointer<GeneralWork> work; // 0x18
    s16 stat0; // 0x1C
    s16 stat1; // 0x1E
    s16 prty; // 0x20
    s16 hitram; // 0x22
    s16 bun0; // 0x24
    s16 bun1; // 0x26
    s16 pad0; // 0x28
    s16 pad1; // 0x2A
    s16 live; // 0x2C
    s16 stat; // 0x2E
    FVECTOR posi; // 0x30
    FVECTOR spd; // 0x40
    FVECTOR muki; // 0x50
    FVECTOR ang; // 0x60
    FVECTOR rot; // 0x70
    RT_WRK rtw; // 0x80
    s32 reg0; // 0x90
    s32 reg1; // 0x94
    s32 reg2; // 0x98
    s32 reg3; // 0x9C
    s32 reg4; // 0xA0
    s32 reg5; // 0xA4
    s32 reg6; // 0xA8
    s32 reg7; // 0xAC
    float freg0; // 0xB0
    float freg1; // 0xB4
    float freg2; // 0xB8
    float freg3; // 0xBC
    float freg4; // 0xC0
    float freg5; // 0xC4
    float freg6; // 0xC8
    float freg7; // 0xCC
    s64 htblid; // 0xD0
    s64 dummy; // 0xD8
    s16 option; // 0xE0
    s16 sflag; // 0xE2
    u32 hpo; // 0xE4
    u32 gimmick; // 0xE8
    u32 _hOp; // 0xEC

    void drawObj(KlonoaMemory* mem) {
        posi.draw(mem, "posi", -2000, 2000);
        spd.draw(mem, "spd", -1.0, 1.0);
        muki.draw(mem, "muki", -1.0, 1.0);
        ang.draw(mem, "ang", -1.0, 1.0);
        rot.draw(mem, "rot", -3.14, 3.14);
        if (ImGui::TreeNode("rtw")) {
            rtw.draw(mem);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("reg")) {
            ImGui::Text("reg0: %d", reg0);
            ImGui::Text("reg1: %d", reg1);
            ImGui::Text("reg2: %d", reg2);
            ImGui::Text("reg3: %d", reg3);
            ImGui::Text("reg4: %d", reg4);
            ImGui::Text("reg5: %d", reg5);
            ImGui::Text("reg6: %d", reg6);
            ImGui::Text("reg7: %d", reg7);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("freg")) {
            ImGui::Text("freg0: %f", freg0);
            ImGui::Text("freg1: %f", freg1);
            ImGui::Text("freg2: %f", freg2);
            ImGui::Text("freg3: %f", freg3);
            ImGui::Text("freg4: %f", freg4);
            ImGui::Text("freg5: %f", freg5);
            ImGui::Text("freg6: %f", freg6);
            ImGui::Text("freg7: %f", freg7);
            ImGui::TreePop();
        }

        if (ImGui::TreeNode("work")) {
            if (ImGui::TreeNode("HERO_WORK")) {
                DrawHeroWork(mem, work.Get<HERO_WORK>(mem));
                ImGui::TreePop();
            }
            if (ImGui::TreeNode("ZAKO_WORK")) {
                DrawZakoWork(mem, work.Get<ZAKO_WORK>(mem));
                ImGui::TreePop();
            }
            ImGui::TreePop();
        }
    }
} OBJWORK;

typedef struct PCOORD {
    FMATRIX Rot; // 0x00
    FMATRIX Trans; // 0x10
    FMATRIX Mtx; // 0x20
    FMATRIX MtxSav; // 0x60
    float WipCnt; // 0xA0
    PS2Pointer<struct PCOORD> Super; // 0xA4
    int Flag; // 0xA8
    float YokoSpd; // 0xAC
} PCOORD;

typedef struct {
    short mot;
    short stopflag;
    short sync;
    short incnt;
    short outcnt;
    short inmode;
    short outmode;
    ulong onflag;
} PACTTBL;

// Size: 0x38
typedef struct {
    float MotionCnt;
    float MotionEndCnt;
    float CntSpeed;
    float Weight;
    float TargetWeight;
    float InCnt;
    float OutCnt;
    float pad;
    ulong OnFlag;
    int pad2; // ??????
    short StopFlag;
    short Type;
    short SyncFlag;
    short InMode;
    short OutMode;
} PMBLOCK;

typedef struct {
    short ActNum;
    short ActNumMax;
    float SubScale; // 0x04
    short unk; // 0x08, or float?
    PS2Pointer<PCOORD> pBaseCoord; // 0x0C
    PS2Pointer<PCOORD> pCoord; // 0x10
    PS2Pointer<u8> pInf; // 0x14
    PS2Pointer<uint> pItr; // 0x18
    PS2Pointer<uint> pItrW; // 0x1C
    short CoordNum; // 0x20
    short BaseIndex; // 0x22
    short BaseMixIndex; // 0x24
    short IpIndex; // 0x26?
    short IpMixIndex; // 0x28?
    short spad;
    // int pad[3];
    float IpWeight[64]; // TODO: ????
    PS2Pointer<PACTTBL> pActtbl; // 0x12C
    PMBLOCK Mb[4];
    short EndFlag;
} PMOTION;

typedef struct {
    ulong IdFlag; // 0x00
    PS2Pointer<u8> pVmime; // 0x08
    short VmimeInd; // 0x0C
    float VmimeCnt; // 0x10
    float VmimeCntSpeed; // 0x14
} PMIME;

typedef struct {} PPARTS;

typedef struct PSFXOBJ {
    FVECTOR ScaleVector; // 0x00
    PS2Pointer<PMOTION> pMot; // 0x10
    PS2Pointer<FMATRIX> pLightColor; // 0x14
    PS2Pointer<FMATRIX> pNormalLight; // 0x18
    int PartsNum; // 0x1C
    int GmsNum; // 0x38, TODO: short or int?
    float scale;
    PS2Pointer<PPARTS> pParts;
    float pad[6];
    PS2Pointer<struct PSFXOBJ> pObjSub; // 0x44
    PS2Pointer<struct PSFXOBJ> pObjTop; // 0x48
    float ClutWeight; // 0x4C
    uint Flag; // 0x50
    uint Condition; // 0x54
    short Pause; // 0x58?
    short GmsTransType; // 0x5A?
    int pad2[2];
    PS2Pointer<PMIME> pMime; // 0x64
    short OutLineFlag; // 0x68
    float ClipOffset; // 0x6C
    float ClipZone; // 0x70
    short ClipFlag; // 0x74
    short Id; // 0x76
    ushort ClutNum0; // 0x78
    ushort ClutNum1; // 0x7A
    ushort Cbp; // 0x7C
    ushort NonActFlag; // 0x7E
    ushort MotionSyncFlag; // 0x80
    int ShadowType; // 0x84
    float ShadowSize; // 0x88
    float ShadowOffset; // 0x8C
    float ShadowRange; // 0x90
    short ObjNum;
    short DrawWorkCnt;
    int OutFlag;
    int actNum;
} PSFXOBJ;

typedef struct HERO_WORK : GeneralWork { 
    RT_WRK rtw;
    int idk;
    int miexspd; // 0x14
    int tumspd;
    int gimspd;
    uint bun_buf;
    uint Muki;
    uint buki_muki;
    uint timer;
    uint timer2;
    int yarare_bun;
    int tenmetu; // 0x38
    uint Muki_buf;
    uint door_muki;
    int total_rakka_time;
    int count;
    int muki2;
    int michinori;
    int michispd;
    int mispd_buf;
    int mispd; // 0x5C
    int spflag;
    int spflag2;
    int da_muteki; // 0x68
    int noyukatime;
    PS2Pointer<OBJWORK> mochifuku; // 0x70
    int jmp_cnt;
    float saka;
    float yarare_yposi;
    uint f_phcode;
    int lvl;
    int trg;
    int ex_lvl;
    int ex_trg;
    float sjump_flag;
    float sjump_yspd;
    float tenjo_hosei;
    int retflag;
    int left_move;
    int right_move;
    int up_move;
    int down_move;
    uint gimm_flag;
    PS2Pointer<OBJWORK> norigimm;
    PS2Pointer<OBJWORK> movebox;
    int yuka_hit;
    int yuka_hit_buf;
    int ottoto;
    int rakka_flag;
    int wahoo_cnt;
    int wahoo_timer;
    PS2Pointer<OBJWORK> okuyuka;
    int con;
    int b_action;
    int b_act_time;
    FVECTOR Scale;
    int se_id;
    int se_id2;
    int se_id3;
    int se_id4;
    int se_id5;
    int se_id6;
    int se_id7;
    int se_id8;
    int se_id9;
    int dai_se_cnt;
    int yuka_hit_old;
    int b_act_rflag;
    float b_act_rot;
    float motcnt;
    float motcnt_end;
    int motstop_flag;
    int mot_actno;
    int kasokuLvL; // 0x144
    float kasokuTime; // 0x148
    float kasokuMTime; // 0x14C
    float center_time;
    int rupu_cnt;
    int run_ef_cnt;
    int dead_cnt;
    int hima_cnt;
    int taiho_bun;
    int area_cnt;
    int kage_flag;
    float jumpspd_limit; // 0x16C
    int rakka_cnt;
    int pad;
    FVECTOR slant; // 0x180
    PS2Pointer<OBJWORK> effBoardFlear;
} HERO_WORK;

void DrawHeroWork(KlonoaMemory* mem, HERO_WORK* work) {
    ImGui::Text("jmp_cnt: %d", work->jmp_cnt);
    ImGui::Text("motcnt: %d", work->motcnt);
    ImGui::Text("motcnt_end: %d", work->motcnt_end);
    ImGui::Text("motstop_flag: %d", work->motstop_flag);
    ImGui::Text("mot_actno: %d", work->mot_actno);
    ImGui::Text("area_cnt: %d", work->area_cnt);
    if (ImGui::TreeNode("rtw")) {
        work->rtw.draw(mem);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("norigimm")) {
        work->norigimm.Get(mem)->drawObj(mem);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("movebox")) {
        work->movebox.Get(mem)->drawObj(mem);
        ImGui::TreePop();
    }
}

typedef struct {
    short dis;
    short ydis;
    signed char bake;
    signed char nbake;
    signed char look;
    signed char hoko;
    short turnint;
    short herootno;
    int heroot;

    void Draw(KlonoaMemory* mem) {
        drawShort(mem, "dis", &dis, 0, 1000);
        drawShort(mem, "ydis", &ydis, 0, 1000);
        drawShort(mem, "turnint", &turnint, 0, 1000);
        drawShort(mem, "herootno", &herootno, 0, 1000);
        drawInt(mem, "heroot", &heroot, 0, 1000);
    }
} ZAKO_BORN;

typedef struct {
    ZAKO_BORN zgene;

    void Draw(KlonoaMemory* mem) {
        zgene.Draw(mem);
    }
} ZAKO_MoveTbl;

typedef struct {
    signed char l0;
    signed char l1;
    short rno;
    float lip;
    float ypos;
    int mcn;
    int type;
    int pad[3];
    FVECTOR pos;
} LT_WORK;

typedef struct {
    PS2Pointer<PSFXOBJ> pSfx; // TODO: PSFXOBJ
    PS2Pointer<PSFXOBJ> pMir; // TODO: PSFXOBJ
    int pad0;
    int pad1;
} tOBJECT2;

typedef struct {
    int walkspd;
    short jumphigh;
    short jumptime;
    short mizo;
    short target0;
    short target1;
    short tachido;

    void Draw(KlonoaMemory* mem) {
        drawInt(mem, "walkspd", &walkspd, -1000, 1000);
        drawShort(mem, "jumphigh", &jumphigh, -1000, 1000);
        drawShort(mem, "jumptime", &jumptime, -1000, 1000);
    }
} WALK_COMMON;

typedef struct {
    float len;
    float yoff;
    float ysize;
    float dummy;
} HITTBL2;

typedef struct ZAKO_COMMON : GeneralWork {
    short xzdis; // 0x00
    short ydis; // 0x02
    ushort timer; // 0x04
    ushort count; // 0x06
    short flag; // 0x08
    short flag2; // 0x0A
    short flag3; // 0x0C
    short tekipic; // 0x0E
    PS2Pointer<ZAKO_MoveTbl> movetbl; // 0x10
    short look; // 0x14
    short bomtimer; // 0x16
    int motno; // 0x18
    PS2Pointer<OBJWORK> prt; // 0x1C
    int seno[4]; // 0x20
    short sedat0[4]; // 0x30
    short sedat1[4]; // 0x38
    PS2Pointer<OBJWORK> movebox; // 0x40
    float gspd; // 0x44
    PS2Pointer<OBJWORK> gmp; // 0x48
    int gimspd; // 0x4C
    LT_WORK ltw; // 0x50
    PS2Pointer<tOBJECT2> mp0; // 0x80
    PS2Pointer<tOBJECT2> mp1;
    short res0;
    short res1;
    float jumpspd;
    int pad0;
    float juryoku;
    long otoM;
    int pad1;
    short plc;
    short rtn;
    int mcn;
    int wspd; // 0xAC
    int michinori; // 0xB0
    int furimuki;
    PS2Pointer<WALK_COMMON> walkpa;
    int wsbuf;
    int test0;
    int test1;
    PS2Pointer<HITTBL2> hittbl2;

    void Draw(KlonoaMemory* mem) {
        drawShort(mem, "xzdis", &xzdis, -2000, 2000);
        drawShort(mem, "ydis", &ydis, -2000, 2000);
        drawUShort(mem, "timer", &timer, 0, 200);
        drawUShort(mem, "count", &count, 0, 200);
        drawFloat(mem, "jumpspd", &jumpspd, 0, 100);
        drawShort(mem, "plc", &plc, 0, 200);
        drawShort(mem, "rtn", &rtn, 0, 2000);
        drawInt(mem, "mcn", &mcn, 0, 2000);
        drawInt(mem, "wspd", &wspd, 0, 100);
        if (movetbl.IsValid() && ImGui::TreeNode("movetbl")) {
            ZAKO_MoveTbl* tbl = movetbl.Get(mem);
            tbl->Draw(mem);
            ImGui::TreePop();
        }
        if (prt.IsValid() && ImGui::TreeNode("prt")) {
            OBJWORK* objw = prt.Get(mem);
            objw->drawObj(mem);
            ImGui::TreePop();
        }
        if (movebox.IsValid() && ImGui::TreeNode("movebox")) {
            OBJWORK* objw = movebox.Get(mem);
            objw->drawObj(mem);
            ImGui::TreePop();
        }
        if (gmp.IsValid() && ImGui::TreeNode("gmp")) {
            OBJWORK* objw = gmp.Get(mem);
            objw->drawObj(mem);
            ImGui::TreePop();
        }
        if (mp0.IsValid() && ImGui::TreeNode("mp0")) {
            tOBJECT2* tobj = mp0.Get(mem);
            ImGui::TreePop();
        }
        if (mp1.IsValid() && ImGui::TreeNode("mp1")) {
            tOBJECT2* tobj = mp1.Get(mem);
            ImGui::TreePop();
        }
        if (walkpa.IsValid() && ImGui::TreeNode("walkpa")) {
            WALK_COMMON* walk = walkpa.Get(mem);
            walk->Draw(mem);
            ImGui::TreePop();
        }
    }
} ZAKO_COMMON;

typedef struct ZAKO_WORK : ZAKO_COMMON {
    float rt_ofs;
    float rt_spd;
    long test2;
    short tstatA;
    short tekipicA;
    int dum;
    int testA;
    int testB;
    long zchild;
    short timer2;
    int pad;
    FVECTOR vec1; // 0xC0
    FVECTOR vec2;
    FVECTOR vec3;
    FVECTOR tmp;
    float tenoff;
    float ang;
    int bnd[4];
    FVECTOR hitpos;
    FVECTOR bakpos;
    FVECTOR scale;
    FVECTOR norm;
    float yold;
    int nageint;
    float nagespd;
    float g;
    short idx[4];
    RT_WRK rtw;
} ZAKO_WORK;

void DrawZakoWork(KlonoaMemory* mem, ZAKO_WORK* work) {
    work->Draw(mem);
    work->vec1.draw(mem, "vec1", -100, 100);
    work->vec2.draw(mem, "vec2", -100, 100);
    work->vec3.draw(mem, "vec3", -100, 100);
}

typedef struct {
    FVECTOR Trans; // 0x00
    FVECTOR Rot; // 0x10
    FVECTOR Scale; // 0x20
    u32 pObj; // 0x30
    int ActNum; // 0x34
    int old_muki; // 0x38
    int wip_timer; // 0x3C
    int dummy[4]; // 0x40
} PsfxMODEL;

typedef struct : Prim {
    PsfxMODEL klm;
    PsfxMODEL ksm;
    PsfxMODEL kmm;
    PsfxMODEL shm;
    PsfxMODEL shm2;
} klMODEL;

typedef struct {
    FVECTOR trans;
    FVECTOR rot;
    FVECTOR light0;
    FVECTOR light1;
    FVECTOR light2;
    FVECTOR color0;
    FVECTOR color1;
    FVECTOR color2;
    FVECTOR ambient;
    FVECTOR fogcol;
    bool draw_enable;
    bool prim;
    bool lod;
    bool mmesh;
    bool basetex;
    bool fog;
    bool multitex;
    bool headtex;
    bool headtexval;
    bool heightajust;
    bool basetexarea;
    u8 pad;
    float planesizex;
    float planesizez;
    float meshsizex;
    float meshsizez;
    float height;
    float intervalx;
    float intervalz;
    float radiusx;
    float radiusz;
    float texajust;
    float speedx;
    float speedz;
    float shear;
    float basetexspeedx;
    float basetexspeedz;
    float multitexspeedx;
    float multitexspeedz;
    float random;
    float ajust_h_far;
    float ajust_h_near;
    float ajust_h_val;
    float alphablend;
    u8 padding[12];

    void draw(KlonoaMemory* mem) {
        trans.draw(mem, "trans", -2500, 2500);
        rot.draw(mem, "rot", -3.14, 3.14);
        light0.draw(mem, "light0", -2.0, 2.0);
        light1.draw(mem, "light1", -2.0, 2.0);
        light2.draw(mem, "light2", -2.0, 2.0);

        color0.drawColor(mem, "color0");
        color1.drawColor(mem, "color1");
        color2.drawColor(mem, "color2");
        ambient.drawColor(mem, "ambient");
        fogcol.drawColor(mem, "fogcol");

        drawFloat2(mem, "planesize", &planesizex, 0, 5000);
        drawFloat2(mem, "meshsize", &meshsizex, 0, 5000);
        drawFloat2(mem, "interval", &intervalx, 0, 1000);
        drawFloat2(mem, "radius", &radiusx, 0, 1000);
        drawFloat2(mem, "speed", &speedx, 0, 1000);
        drawFloat2(mem, "basetexspeed", &basetexspeedx, 0, 100);
        drawFloat2(mem, "multitexspeed", &multitexspeedx, 0, 100);

        drawFloat(mem, "height", &height, 0, 5);
        drawFloat(mem, "texajust", &texajust, 0, 10);
        drawFloat(mem, "shear", &shear, 0, 1);
        drawFloat(mem, "random", &random, 0, 1);
        drawFloat(mem, "ajust_h_far", &ajust_h_far, 0, 10000);
        drawFloat(mem, "ajust_h_near", &ajust_h_near, 0, 10000);
        drawFloat(mem, "ajust_h_val", &ajust_h_val, 0, 10000);
        drawFloat(mem, "alphablend", &alphablend, 0, 1);

        drawBool(mem, "draw_enable", &draw_enable);
        drawBool(mem, "prim", &prim);
        drawBool(mem, "lod", &lod);
        drawBool(mem, "mmesh", &mmesh);
        drawBool(mem, "basetex", &basetex);
        drawBool(mem, "fog", &fog);
        drawBool(mem, "multitex", &multitex);
        drawBool(mem, "headtex", &headtex);
        drawBool(mem, "headtexval", &headtexval);
        drawBool(mem, "heightajust", &heightajust);
        drawBool(mem, "basetexarea", &basetexarea);
    }
} kitWaveParam;

typedef struct {
    uint flag;
    int draw;
    int time;
    PS2Pointer<IVECTOR> dmatag;
    int code;
    int npos;
    int pos;
    int blk;
    float scalex;
    float scaley;
    float scalez;
    float scsx;
    float scsy;
    float scsz;
    float vcolr;
    float vcolg;
    float vcolb;
    float vcsr;
    float vcsg;
    float vcsb;
    int rotx;
    int rotsx;
    int rotax;
    int roty;
    int rotsy;
    int rotay;

    void drawInfo(KlonoaMemory* mem) {
        ImGui::Text("flag: %d", flag);
        ImGui::Text("draw: %d", draw);
        ImGui::Text("time: %d", time);
        ImGui::Text("code: %d", code);
        ImGui::Text("npos: %d", npos);
        ImGui::Text("pos: %d", pos);
        ImGui::Text("blk: %d", blk);
        ImGui::Text("scalex: %f", scalex);
        ImGui::Text("scaley: %f", scaley);
        ImGui::Text("scalez: %f", scalez);
        ImGui::Text("scsx: %f", scsx);
        ImGui::Text("scsy: %f", scsy);
        ImGui::Text("scsz: %f", scsz);
        ImGui::Text("vcolr: %f", vcolr);
        ImGui::Text("vcolg: %f", vcolg);
        ImGui::Text("vcolb: %f", vcolb);
        ImGui::Text("vcsr: %f", vcsr);
        ImGui::Text("vcsg: %f", vcsg);
        ImGui::Text("vcsb: %f", vcsb);
        ImGui::Text("rotx: %d", rotx);
        ImGui::Text("rotsx: %d", rotsx);
        ImGui::Text("rotax: %d", rotax);
        ImGui::Text("roty: %d", roty);
        ImGui::Text("rotsy: %d", rotsy);
        ImGui::Text("rotay: %d", rotay);
    }
} ANMINFO;

typedef struct {
    int posix;
    int posiy;
    int posiz;
    int angx;
    int angy;
    int angz;
    int proj;
    int time;
    int flg;

    void draw(KlonoaMemory* mem) {
        drawInt3(mem, "posi", &posix, -1000, 1000);
        drawInt3(mem, "ang", &angx, -1000, 1000);
        drawInt(mem, "proj", &proj, -1000, 1000);
        drawInt(mem, "time", &time, 0, 200);
        ImGui::Text("flg: %d", flg);
    }
} nkCamFIX;

typedef struct {
    uint cnt;
    uint status;
    uint lvl;
    u8 r3h;
    u8 r3v;
    u8 l3h;
    u8 l3v;
    uint lvl2;
    ushort trg;
    ushort trgbuf;
    ushort rep;
    ushort reptimer;
    uint looks;
} kPadDATA;

typedef struct {
    int outtime;
    int intime;
    int next_vision;
    int rtn;
    int mcn;
    int imuki;
    int omuki;
    int flag;
    int fdata;
} nkWIPE_WRK;

typedef struct {
    FVECTOR posi;
    FVECTOR ang;
    float scr_z;
    int mode;
    int pad[2];

    void draw(KlonoaMemory* mem) {
        posi.draw(mem, "posi", 0, 0);
        ang.draw(mem, "ang", -3.14, 3.14);
    }
} CAM_WORK;

typedef struct {
    int mode;
    int vision;
    int flag;
    uint fr;
    int db[204];
    int inter;
    int pause_flag;
    int non_pause_flag;
    int pause_flag2;
    int route_max;
    int init_vision;
    int st_rtn;
    int st_mcn;
    int st_muki;
    float st_height;
    int st_flag;
    int st_klomode;
    int Re_st_rtn;
    int Re_st_mcn;
    int Re_st_vision;
    int Re_st_klomode;
    int Re_st_muki;
    float Re_st_height;
    int Re_st_zanki_count;
    PS2Pointer<OBJWORK> klonoa;
    PS2Pointer<OBJWORK> kazd;
    int playdemo_time;
    int playdemo_flag;
    kPadDATA kpd[2];
    nkWIPE_WRK wipe;
    int kloLife[2];
    int kloZanki[2];
    float reverse_cnt;
    int stage_flag;
    int filter_type;
    float filter_cnt;
    int filter_prty;
    int area_max;
    float gus_timer;
    float gus_cnt;
    int popuka_flag;
    int time_atack_cnt;
    int vs_clear_cnt;
    int time_atack_best;
    float fcnt0;
    float fcnt1;
    float fcnt2;
    int area_cnt;
    float retry_posy;
    int retry_bun1;
    int retry_muki;
    int tokurom_cnt;
    FVECTOR pad;
    FMATRIX wsm;
    FMATRIX wvm;
    FMATRIX vsm;
    FMATRIX d_wsm;
    FMATRIX d_wvm;
    FMATRIX d_vsm;
    CAM_WORK cam;
    CAM_WORK d_cam;

    void draw(KlonoaMemory* mem) {
        ImGui::Text("vision: %x", vision);
        if (ImGui::TreeNode("cam")) {
            cam.draw(mem);
            ImGui::TreePop();
        }
        if (ImGui::TreeNode("d_cam")) {
            d_cam.draw(mem);
            ImGui::TreePop();
        }
    }
} GAME_WORK;

typedef struct {
    FVECTOR posi;
    FVECTOR ang;
} VIEWPOSI;

typedef struct {
    uint Ctbl;
    short Prio;
    short Zoom;
    short AngX;
    short AngY;
    short AngZ;
    short PosX;
    short PosY;
    short Time;
    short Mode;
    VIEWPOSI ViewPosi;
} VCONTBL;

typedef struct {
    int zoom;
    int angx;
    int angy;
    int angz;
    int trnsx;
    int trnsy;
    int proj;
    int flg;
} nkCamNOR;

typedef struct {
    float zoom;
    float angx;
    float angy;
    float angz;
    float wangx;
    float wangy;
    float posix;
    float posiy;
    FVECTOR adiv;
    float dtime;
    float dcnt;
    int mode;
    int release;
    float frtime;
    float fwtime;
    float offx;
    float offy;
    FVECTOR tposi;
    uint tblcnt;
    uint tblc_b;
    int old_type;
    int old_idx;
    int old_rtn;
    PS2Pointer<VCONTBL> tbl;
    PS2Pointer<nkCamNOR> nml;
    uint flg;
    uint flg2;
    int rtlen;

    void draw(KlonoaMemory* mem) {
        drawFloat(mem, "zoom", &zoom, -100, 100);
        drawFloat3(mem, "ang", &angx, -100, 100);
        tposi.draw(mem, "tposi", -1000, 1000);
        ImGui::Text("dcnt: %f", dcnt);
    }

} VWork;

#endif