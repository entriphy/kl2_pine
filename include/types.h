#ifndef TYPES_H
#define TYPES_H

#include "ps2_pointer.h"
#include "imgui.h"
#include <map>

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

typedef float f32;

typedef union { // 0x10
    // u128 u_u128;
    u64  u_u64[2];
    s64  u_s64[2];
    u32  u_u32[4];
    s32  u_s32[4];
    u16  u_u16[8];
    s16  u_s16[8];
    u8   u_u8[16];
    s8   u_s8[16];
    f32  u_f32[4];
} qword_uni __attribute__((aligned(16)));

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

inline void drawUShort(KlonoaMemory* mem, const char* name, ushort* ptr, ushort min, ushort max) {
    if (ImGui::SliderScalar(name, ImGuiDataType_U16, ptr, &min, &max)) {
        mem->Write<ushort>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

inline void drawInt(KlonoaMemory* mem, const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt(name, ptr, min, max)) {
        mem->Write<int>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

inline void drawInt2(KlonoaMemory* mem, const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt2(name, ptr, min, max)) {
        mem->Write<long>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

inline void drawInt3(KlonoaMemory* mem, const char* name, int* ptr, int min, int max) {
    if (ImGui::SliderInt3(name, ptr, min, max)) {
        mem->WriteObj<IVECTOR>((char*)ptr - mem->ps2_ram);
    }
}

inline void drawFloat(KlonoaMemory* mem, const char* name, float* ptr, float min, float max) {
    if (ImGui::SliderFloat(name, ptr, min, max)) {
        mem->Write<float>((char*)ptr - mem->ps2_ram, *ptr);
    }
}

inline void drawFloat2(KlonoaMemory* mem, const char* name, float* ptr, float min, float max) {
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

typedef struct klMODEL klMODEL;
void DrawKlMODEL(KlonoaMemory* mem, klMODEL* work);

std::string stat0s[] = {
    "NULL",
    "nakano",
    "okanoTest",
    "okano",
    "NULL",
    "harada",
    "abe",
    "hato",
    "kazuya",
    "?"
};

std::string nakano_stat1[] = {
    "NULL",
    "ObjKlo",
    "ObjKazd",
    "ObjUnk",
    "NULL",
    "ObjGimTrain",
    "ObjGimViking",
    "ObjGimBridgeB7",
    "ObjGimS2Bridge",
    "ObjGimGpDoor0",
    "ObjGimGpDoor1",
    "ObjGimDoor04Pazzle",
    "ObjGimObjSpotlight",
    "ObjUnk",
    "ObjUnk",
    "nkPopuka",
    "nkFilterObj",
    "NULL",
    "ObjGimPendulum",
    "ObjGimBigRock",
    "ObjKuLight",
    "ObjGusSystem",
    "ObjEngSystem",
    "ObjGimRtDoor0",
    "ObjGimRtDoor1",
    "nkPopFlear",
    "nkYume150Flear"
};

std::map<s16, std::string> okanoTestObjMap = {
    { 0, "Z_Balloon00" },
    { 1, "Z_Balloon01" },
    { 2, "Z_BalloonXX" },
    { 3, "B_Man00" },
    { 4096, "I_Main" },
    { 13312, "D_Csr00" },
    { 16512, "M_Chip00" },
};

std::map<s16, std::string> okanoObjMap = {
    { 2048, "T_ZAKO_WALK00" },
    { 2049, "T_ZAKO_FLY00" },
    { 2050, "T_ZAKO_FLY01" },
    { 2051, "T_ZAKO_JALC00" },
    { 2052, "T_ZAKO_FALC00" },
    { 2053, "T_ZAKO_WALC00" },
    { 2054, "T_ZAKO_WALK02" },
    { 2055, "T_ZAKO_WALK01" },
    { 2056, "T_ZAKO_WALK04" },
    { 2057, "T_ZAKO_JUMP01" },
    { 2058, "T_ZAKO_FLIC00" },
    { 2059, "T_ZAKO_WALK10" },
    { 2060, "T_ZAKO_WALK05" },
    { 2061, "T_ZAKO_WALK06" },
    { 2062, "T_ZAKO_WALK07" },
    { 2063, "T_ZAKO_WALK08" },
    { 2064, "T_ZAKO_WALK03" },
    { 2065, "T_ZAKO_FLY02" },
    { 4096, "OK_ZAKO_GROUP1" },
    { 4096, "T_ZAKO_WALK34" },
    { 8192, "OK_ITEM_GROUP0" },
    { 8192, "T_ITEM_JUMP00" },
    { 8193, "T_GIMM_WND00" },
    { 8194, "T_GIMM_GUM00" },
    { 8195, "T_GIMM_GUN00" },
    { 8196, "T_GIMM_BASE00" },
    { 8197, "T_GIMM_BASE10" },
    { 8198, "T_GIMM_BASE11" },
    { 8199, "T_GIMM_BASE12" },
    { 8200, "T_GIMM_WND10" },
    { 8201, "T_GIMM_DOOR00" },
    { 8202, "T_GIMM_FIX00" },
    { 8203, "T_GIMM_BASE20" },
    { 8204, "T_GIMM_BASE14" },
    { 8206, "T_GIMM_BASE16" },
    { 8207, "T_GIMM_FIX01" },
    { 8208, "T_GIMM_BASE17" },
    { 8209, "T_GIMM_GRND00" },
    { 12288, "OK_MISC_GROUP0" },
    { 12288, "T_MISC_CAM00" },
    { 12289, "T_MISC_CAM01" },
    { 12290, "T_MISC_CAM02" },
    { 12295, "T_MISC_SND00" },
    { 14336, "T_MINI_MISL00" },
    { 14337, "T_MINI_MISL01" },
    { 16384, "T_EFCT_FIRE00" },
    { 16385, "T_EFCT_FIRE10" },
    { 16640, "T_ITEM_SUB00" },
    { 16641, "T_ITEM_SWIT00" },
    { 16642, "T_ITEM_SWIT01" },
    { 16512, "T_MISC_CHIP00" },
    { 13312, "T_D_CSR00" }
};

std::string harada_stat1[] = {
    "mapexpl",
    "switch_trg",
    "game_puppet",
    "ptefc_work",
    "game_puppet",
    "game_puppet",
    "obcex_work",
    "dummy_obcw"
};

std::map<s16, std::string> abeObjMap = {
    { 1, "abOBJTEST" },
    { 2, "abOBJ_FIRE_A" },
    { 3, "abOBJ_FIRE_B" },
    { 4, "abOBJ_SMOKE_A" },
    { 5, "abOBJ_SMOKE_B" },
    { 6, "abOBJ_SMOKE_C" },
    { 7, "abOBJ_SMOKE_D" },
    { 8, "abOBJ_SMOKE_E" },
    { 9, "abOBJ_EXPCNT_A" },
    { 10, "abOBJ_CORE_A" }, // 0x0000000A
    { 11, "abOBJ_SONIC_A" }, // 0x0000000B
    { 12, "abOBJ_SPARC_A" }, // 0x0000000C
    { 13, "abOBJ_EXP_00" }, // 0x0000000D
    { 14, "abOBJ_EXP_01" }, // 0x0000000E
    { 15, "abOBJ_EXP_02" }, // 0x0000000F
    { 16, "abOBJ_HAHEN_A" }, // 0x00000010
    { 17, "abOBJ_SHOUGRD_A" }, // 0x00000011
    { 18, "abOBJ_HAMON_A" }, // 0x00000012
    { 19, "abOBJ_KAZEDAMA_A" }, // 0x00000013
    { 20, "abOBJ_KAZEDAMA_B" }, // 0x00000014
    { 21, "abOBJ_DUMMY" }, // 0x00000015
    { 22, "abOBJ_HANABI_A" }, // 0x00000016
    { 23, "abOBJ_HANABITAMA_A" }, // 0x00000017
    { 24, "abOBJ_HANABICNT_A" }, // 0x00000018
    { 25, "abOBJ_EB_WAVE_A" }, // 0x00000019
    { 26, "abOBJ_EB_MONO_A" }, // 0x0000001A
    { 27, "abOBJ_EC_WAVE_A" }, // 0x0000001B
    { 28, "abOBJ_EC_MONO_A" }, // 0x0000001C
    { 29, "abOBJ_TSUMUJI_A" }, // 0x0000001D
    { 30, "abOBJ_KIRYU_A" }, // 0x0000001E
    { 31, "abOBJ_BOSSHIT_A" }, // 0x0000001F
    { 32, "abOBJ_SWITCH_A" }, // 0x00000020
    { 33, "abOBJ_ITEMPTCL_A" }, // 0x00000021
    { 34, "abOBJ_ITEMPTCL_B" }, // 0x00000022
    { 35, "abOBJ_ITEMPTCL_C" }, // 0x00000023
    { 36, "abOBJ_ELVIL_A" }, // 0x00000024
    { 37, "abOBJ_ELVIL_C" }, // 0x00000025
    { 38, "abOBJ_ELVIL_D" }, // 0x00000026
    { 39, "abOBJ_TAKI_A" }, // 0x00000027
    { 40, "abOBJ_SHIBUKI_A" }, // 0x00000028
    { 41, "abOBJ_SHIBUKI_B" }, // 0x00000029
    { 42, "abOBJ_SHIBUKI_C" }, // 0x0000002A
    { 43, "abOBJ_JETIMO_A" }, // 0x0000002B
    { 44, "abOBJ_HOUSHI_A" }, // 0x0000002C
    { 45, "abOBJ_RAIN_A" }, // 0x0000002D
    { 46, "abOBJ_LIGHTNING_A" }, // 0x0000002E
    { 47, "abOBJ_FLAER_A" }, // 0x0000002F
    { 48, "abOBJ_FIXEDMODEL" }, // 0x00000030
    { 49, "abOBJ_SCROLLMODEL" }, // 0x00000031
    { 50, "abOBJ_BUBBLE_A" }, // 0x00000032
    { 51, "abOBJ_KAZE_A" }, // 0x00000033
    { 52, "abOBJ_RIKRISTONE_A" }, // 0x00000034
    { 53, "abOBJ_AURA_A" }, // 0x00000035
    { 54, "abOBJ_OUGU_A" }, // 0x00000036
    { 55, "abOBJ_BUPPY_B" }, // 0x00000037
    { 56, "abOBJ_BUPPYSTONE_A" }, // 0x00000038
    { 57, "abOBJ_POOL_A" }, // 0x00000039
    { 58, "abOBJ_SHIZUKU_A" }, // 0x0000003A
    { 59, "abOBJ_HAMON_B" }, // 0x0000003B
    { 60, "abOBJ_TAKI_B" }, // 0x0000003C
    { 61, "abOBJ_ENERGYFORGE_A" }, // 0x0000003D
    { 62, "abOBJ_SHABON_A" }, // 0x0000003E
    { 63, "abOBJ_SPOTLIGHT_A" }, // 0x0000003F
    { 64, "abOBJ_FLAER_C" }, // 0x00000040
    { 65, "abOBJ_ENERGYFORGE_0706" }, // 0x00000041
    { 66, "abOBJ_LASER_1208" }, // 0x00000042
    { 67, "abOBJ_FLAER_2700" }, // 0x00000043
    { 68, "abOBJ_AURA_C" }, // 0x00000044
    { 69, "abOBJ_BOSSLIGHT_A" }, // 0x00000045
    { 70, "abOBJ_SMOKE_TK" }, // 0x00000046
    { 71, "abOBJ_KAZEDAMA_C" }, // 0x00000047
    { 72, "abOBJ_DISTORTIONCONTAINER" }, // 0x00000048
    { 73, "abOBJ_ITEMPTCL_B2" }, // 0x00000049
    { 74, "abOBJ_ITEMPTCL_C2" }, // 0x0000004A
    { 75, "abOBJ_ITEMPTCL_A2" }, // 0x0000004B
    { 76, "abOBJ_ITEMPTCL_A3" }, // 0x0000004C
    { 77, "abOBJ_ITEMPTCL_A4" }, // 0x0000004D
    { 78, "abOBJ_ITEMPTCL_A5" }, // 0x0000004E
    { 79, "abOBJ_ITEMPTCL_A6" }, // 0x0000004F
    { 80, "abOBJ_JIGEN_A" }, // 0x00000050
    { 81, "abOBJ_BUBBLE_B" }, // 0x00000051
    { 82, "abOBJ_PLASMA" }, // 0x00000052
    { 83, "abOBJ_SMOKE_BOSS1" }, // 0x00000053
    { 84, "abOBJ_SMOKE_ZIPPO" }, // 0x00000054
    { 85, "abOBJ_SCREENFLUSH" }, // 0x00000055
    { 86, "abOBJ_SMOKE_A2" }, // 0x00000056
    { 87, "abOBJ_PLASMA2" }, // 0x00000057
    { 88, "abOBJ_SMOKE_TK_RED" }, // 0x00000058
    { 89, "abOBJ_SMOKE_RUN" }, // 0x00000059
    { 90, "tkOBJ_BOSS2_QUAKE" }, // 0x0000005A
    { 91, "abOBJ_JIGEN_END_A" }, // 0x0000005B
    { 92, "abOBJ_SWITCH_A2" }, // 0x0000005C
    { 93, "abOBJ_SMOKE_DIGON" }, // 0x0000005D
    { 94, "abOBJ_HANABI_B" }, // 0x0000005E
    { 95, "abOBJ_HANABI_C" }, // 0x0000005F
    { 96, "abOBJ_SWITCH_B" }, // 0x00000060
    { 97, "abOBJ_SWITCH_B2" }, // 0x00000061
    { 98, "abOBJ_SWITCH_B3" }, // 0x00000062
    { 99, "abOBJ_JETIMO_A2" }, // 0x00000063
    { 100, "abOBJ_SMOKE_NOR_U" }, // 0x00000064
    { 101, "abOBJ_SMOKE_NOR_D" }, // 0x00000065
    { 102, "abOBJ_SMOKE_WATER" }, // 0x00000066
    { 103, "abOBJ_SMOKE_WATER_U" }, // 0x00000067
    { 104, "abOBJ_SMOKE_WATER_D" }, // 0x00000068
    { 105, "abOBJ_SMOKE_SNOW" }, // 0x00000069
    { 106, "abOBJ_SMOKE_SNOW_U" }, // 0x0000006A
    { 107, "abOBJ_SMOKE_SNOW_D" }, // 0x0000006B
    { 108, "abOBJ_SMOKE_SAND" }, // 0x0000006C
    { 109, "abOBJ_SMOKE_SAND_U" }, // 0x0000006D
    { 110, "abOBJ_SMOKE_SAND_D" }, // 0x0000006E
    { 111, "abOBJ_EXP_03" }, // 0x0000006F
    { 112, "abOBJ_SMOKE_MUWATER" }, // 0x00000070
    { 113, "abOBJ_SMOKE_MUSNOW" }, // 0x00000071
    { 114, "abOBJ_FIRE_B2" }, // 0x00000072
    { 115, "abOBJ_SPOTLIGHT_A2" }, // 0x00000073
    { 116, "abOBJ_FLAER_BOSS2" }, // 0x00000074
    { 117, "abOBJ_SMOKE_BOSS2_ROLLING" }, // 0x00000075
    { 118, "abOBJ_SMOKE_BOSS2_BUNSIN" }, // 0x00000076
    { 119, "abOBJ_EXP_BUPPY" }, // 0x00000077
    { 120, "abOBJ_FLAER_BUPPY" }, // 0x00000078
    { 121, "abOBJ_SWITCH_C" }, // 0x00000079
    { 122, "abOBJ_FLAER_SUPERTAT" }, // 0x0000007A
    { 123, "abOBJ_ELVIL_B" }, // 0x0000007B
    { 124, "abOBJ_FLAER_KLONOABOARD" }, // 0x0000007C
    { 125, "abOBJ_FIRE_ENEMY" }, // 0x0000007D
    { 126, "abOBJ_FLAER_BOSS3" }, // 0x0000007E
    { 127, "abOBJ_KAZE_B" }, // 0x0000007F
    { 128, "abOBJ_SMOKE_SL" }, // 0x00000080
    { 129, "abOBJ_LASER_BIS" }, // 0x00000081
    { 130, "abOBJ_LASER_ROOT" }, // 0x00000082
    { 131, "abOBJ_SMOKE_GRIDZP" }, // 0x00000083
    { 132, "abOBJ_SMOKE_GRIDZQ" }, // 0x00000084
    { 133, "abOBJ_FIRE_A2" }, // 0x00000085
    { 134, "abOBJ_TS_RADIOMAN" }, // 0x00000086
    { 135, "abOBJ_SMOKE_BOSS3_HOMING" }, // 0x00000087
    { 136, "abOBJ_SMOKE_BOSS3" }, // 0x00000088
    { 137, "abOBJ_SMOKE_BOSS4" }, // 0x00000089
    { 138, "abOBJ_SMOKE_BOSS4_NUTS" }, // 0x0000008A
    { 139, "abOBJ_LASER_ROTATING" }, // 0x0000008B
    { 140, "abOBJ_SWITCH_X" }, // 0x0000008C
    { 141, "abOBJ_HAMON_AP" }, // 0x0000008D
    { 142, "tkOBJ_BACHI" }, // 0x0000008E
    { 143, "abOBJ_SMOKE_GODDESS1" }, // 0x0000008F
    { 144, "abOBJ_SMOKE_GODDESS2" }, // 0x00000090
    { 145, "spOBJ_BERNY" }, // 0x00000091
    { 146, "abOBJ_FLAER_BOSS6_MIST" }, // 0x00000092
    { 147, "abOBJ_FLAER_BOSS6_SPHERE" }, // 0x00000093
    { 148, "abOBJ_BOSS6_RING" }, // 0x00000094
    { 149, "abOBJ_FLAER_NEMOMU_EYE" }, // 0x00000095
    { 150, "spOBJ_HOTARU" }, // 0x00000096
    { 151, "abOBJ_FRORO_DEL" }, // 0x00000097
    { 152, "abOBJ_FRORO_LIGHT" }, // 0x00000098
    { 153, "spOBJ_KUROSUKE" }, // 0x00000099
    { 154, "abOBJ_HAMON_A2" }, // 0x0000009A
    { 155, "abOBJ_PT0104_S1_00_01" }, // 0x0000009B
    { 156, "abOBJ_BOSS7_LASER" }, // 0x0000009C
    { 157, "abOBJ_BOSS7_LASER_ROOT" }, // 0x0000009D
    { 158, "abOBJ_BOSS7_PLASMA" }, // 0x0000009E
    { 159, "abOBJ_SMOKE_TK_MAP" }, // 0x0000009F
    { 160, "abOBJ_PT0207_0" }, // 0x000000A0
    { 161, "abOBJ_PT2100_ELEM" }, // 0x000000A1
    { 162, "abOBJ_PT2100_ELEMS" }, // 0x000000A2
    { 163, "abOBJ_PT2200_ELEM" }, // 0x000000A3
    { 164, "abOBJ_PT2200_ELEMS" }, // 0x000000A4
    { 165, "abOBJ_PT2300_BOSS0" }, // 0x000000A5
    { 166, "abOBJ_PT2301_REOSHOT" }, // 0x000000A6
    { 167, "abOBJ_PT2300_ELEM" }, // 0x000000A7
    { 168, "abOBJ_SMOKE_BIS" }, // 0x000000A8
    { 169, "abOBJ_FIRE_A3" }, // 0x000000A9
    { 170, "abOBJ_FIRE_A4" }, // 0x000000AA
    { 171, "abOBJ_FIRE_A_OFF" }, // 0x000000AB
    { 172, "abOBJ_FIRE_A3_OFF" }, // 0x000000AC
    { 173, "abOBJ_FIRE_A4_OFF" }, // 0x000000AD
    { 174, "abOBJ_SEA_SPRAY" }, // 0x000000AE
    { 175, "abOBJ_SMOKE_RSAND" }, // 0x000000AF
    { 176, "abOBJ_SMOKE_CLIFFROAD" }, // 0x000000B0
    { 177, "abOBJ_SMOKE_BOSS6_DASH" }, // 0x000000B1
    { 178, "abOBJ_SMOKE_BOSS6_DAMAGE" }, // 0x000000B2
    { 179, "abOBJ_FLAER_BOSS6" }, // 0x000000B3
    { 180, "abOBJ_FLAER_BOSS6_WHITE" }, // 0x000000B4
    { 181, "abOBJ_PT0100_S2_00_00" }, // 0x000000B5
    { 182, "abOBJ_PT0100_S2_00_01" }, // 0x000000B6
    { 183, "abOBJ_PT0100_S2_00_02" }, // 0x000000B7
    { 184, "abOBJ_REFLECT" }, // 0x000000B8
    { 185, "abOBJ_PT040a_s0_00_00" }, // 0x000000B9
    { 186, "abOBJ_PT0706_s0_00_00" }, // 0x000000BA
    { 187, "abOBJ_PT0706_s0_00_01" }, // 0x000000BB
    { 188, "abOBJ_PT1306_s0_00_00" }, // 0x000000BC
    { 189, "abOBJ_PT1306_s0_00_01" }, // 0x000000BD
    { 190, "abOBJ_PT1400_s0_00_00" }, // 0x000000BE
    { 191, "abOBJ_PT1502_s3_00_00" }, // 0x000000BF
    { 192, "abOBJ_PT1502_s1_00_00" }, // 0x000000C0
    { 193, "abOBJ_PT2100_s0_00_00" }, // 0x000000C1
    { 194, "abOBJ_PT2100_s0_00_01" }, // 0x000000C2
    { 195, "abOBJ_PT2301_s0_00_00" }, // 0x000000C3
    { 196, "abOBJ_PT2400_s0_00_00" }, // 0x000000C4
    { 197, "abOBJ_ENERGYFORGE_FIRE" }, // 0x000000C5
    { 198, "abOBJ_PTOP_00_00" }, // 0x000000C6
    { 199, "abOBJ_PT2600_s0_00_00" }, // 0x000000C7
    { 200, "abOBJ_PT2601_s0_00_00" }, // 0x000000C8
    { 201, "abOBJ_PT2700_s1_00_00" }, // 0x000000C9
    { 202, "abOBJ_PT2700_ELEM" }, // 0x000000CA
    { 203, "abOBJ_PT2700_ELEMS" }, // 0x000000CB
    { 204, "abOBJ_PT4001_s4_00_00" }, // 0x000000CC
    { 205, "abOBJ_PT4001_s4_00_01" }, // 0x000000CD
    { 206, "tkOBJ_HITBIT" }, // 0x000000CE
    { 207, "abOBJ_PTED_00_00" }, // 0x000000CF
    { 208, "abOBJ_PTED_00_01" }, // 0x000000D0
    { 209, "abOBJ_FLAER_BOSS6_EYE" }, // 0x000000D1
    { 210, "abOBJ_ANIME_CANDLE" }, // 0x000000D2
    { 211, "abOBJ_SHIBUKI_A2" }, // 0x000000D3
    { 212, "abOBJ_ANIME" }, // 0x000000D4
    { 213, "abOBJ_ANIME01" }, // 0x000000D5
    { 214, "abOBJ_ANIME02" }, // 0x000000D6
    { 215, "abOBJ_ANIME03" }, // 0x000000D7
    { 216, "abOBJ_ANIME04" }, // 0x000000D8
    { 217, "abOBJ_ANIME05" }, // 0x000000D9
    { 218, "abOBJ_ANIME06" }, // 0x000000DA
    { 219, "abOBJ_ANIME07" }, // 0x000000DB
    { 220, "abOBJ_ANIME08" }, // 0x000000DC
    { 221, "abOBJ_ANIME09" }, // 0x000000DD
    { 222, "abOBJ_ANIME10" }, // 0x000000DE
    { 223, "abOBJ_ANIME11" }, // 0x000000DF
    { 224, "abOBJ_ANIME12" }, // 0x000000E0
    { 225, "abOBJ_ANIME13" }, // 0x000000E1
    { 226, "abOBJ_ANIME14" }, // 0x000000E2
    { 227, "abOBJ_ANIME15" }, // 0x000000E3
    { 228, "abOBJ_ANIME16" }, // 0x000000E4
    { 229, "abOBJ_ANIME17" }, // 0x000000E5
    { 230, "abOBJ_ANIME18" }, // 0x000000E6
    { 231, "abOBJ_ANIME19" }, // 0x000000E7
    { 232, "abOBJ_ANIME20" }, // 0x000000E8
    { 233, "abOBJ_ANIME21" }, // 0x000000E9
    { 234, "abOBJ_POPEFF" }, // 0x000000EA
    { 235, "abOBJ_SPJUMP" }, // 0x000000EB
    { 236, "abOBJ_FIRE_FORGOTTEN_ROAD" }, // 0x000000EC
    { 237, "abOBJ_SHIBUKI_A_2" }, // 0x000000ED
    { 238, "abOBJ_SHIBUKI_A_3" }, // 0x000000EE
    { 239, "abOBJ_PTOP_00_01" }, // 0x000000EF
    { 240, "abOBJ_KAZEDAMA_SP" }, // 0x000000F0
    { 241, "abOBJ_HAMON17" }, // 0x000000F1
    { 242, "abOBJ_PT2700_s2_00_00" }, // 0x000000F2
    { 243, "abOBJ_SHIBUKI_D" }, // 0x000000F3
    { 244, "abOBJ_SLASHER" }, // 0x000000F4
    { 245, "abOBJ_SMOKE_TAT" }, // 0x000000F5
    { 246, "abOBJ_PTOP_RAKKA" }, // 0x000000F6
    { 247, "abOBJ_FXNUM" } // 0x000000F7
};

std::string kazuya_stat1[] = {
    "NULL",
    "kzOST",
    "kzOVO",
    "kzOWM",
    "kzOMD",
    "kzOKL"
};

inline const char* getStat1(s16 stat0, s16 stat1) {
    switch (stat0) {
        case 0:
            return "eh? (0)";
        case 1:
            return nakano_stat1[stat1].c_str();
        case 2:
            return okanoTestObjMap[stat1].c_str();
        case 3:
            return okanoObjMap[stat1].c_str();
        case 4:
            return "eh? (4)";
        case 5:
            return harada_stat1[stat1].c_str();
        case 6:
            return abeObjMap[stat1].c_str();
        case 8:
            return kazuya_stat1[stat1].c_str();
        case 9:
            return "??? (9)";
    }
    return nullptr;
}

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

        ImGui::Text("work_addr: %08x", work.ptr);
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

        if (ImGui::TreeNode("prim")) {
            DrawKlMODEL(mem, prim.Get<klMODEL>(mem));
            ImGui::TreePop();
        }

        ImGui::Text("stat: %d", stat);
        ImGui::Text("stat0: %d (%s)", stat0, stat0s[stat0].c_str());
        ImGui::Text("stat1: %d (%s)", stat1, getStat1(stat0, stat1));
    }
} OBJWORK;

// Size: 0xB0
typedef struct PCOORD {
    FVECTOR Rot; // 0x00
    FVECTOR Trans; // 0x10
    FMATRIX Mtx; // 0x20
    FMATRIX MtxSav; // 0x60
    f32 WipCnt; // 0xA0
    PS2Pointer<struct PCOORD> Super; // 0xA4
    s32 Flag; // 0xA8
    float YokoSpd; // 0xAC
} PCOORD;

// Size: 0x18
typedef struct {
    u64 IdFlag; // 0x00
    PS2Pointer<u8> pVmime; // 0x08
    s16 VmimeInd; // 0x0C
    float VmimeCnt; // 0x10
    float VmimeCntSpeed; // 0x14
} PMIME;

typedef struct {
    s16 mot;
    s16 stopflag;
    s16 sync;
    s16 incnt;
    s16 outcnt;
    s16 inmode;
    s16 outmode;
    u64 onflag;
} PACTTBL;

// Size: 0x38?
typedef struct {
    f32 MotionCnt;
    f32 MotionEndCnt;
    f32 CntSpeed;
    f32 Weight;
    f32 TargetWeight;
    f32 InCnt;
    f32 OutCnt;
    u64 OnFlag;
    s16 StopFlag;
    s16 Type;
    s16 SyncFlag;
    s16 InMode;
    s16 OutMode;
} PMBLOCK;

typedef struct {
    s16 ActNum;
    s16 ActNumMax;
    f32 SubScale; // 0x04
    f32 unk;
    PS2Pointer<PCOORD> pBaseCoord; // 0x0C
    PS2Pointer<PCOORD> pCoord; // 0x10
    u8* pInf; // 0x14
    u32 pItr; // 0x18, TODO: this should be a pointer
    u32 pItrW; // 0x1C, TODO: this should be a pointer
    s16 CoordNum; // 0x20
    s16 BaseIndex; // 0x22
    s16 BaseMixIndex; // 0x24
    s16 IpIndex; // 0x26?
    s16 IpMixIndex; // 0x28?
    s16 spad;
    s32 pad[10];
    // float IpWeight[64]; // TODO: ????
    PS2Pointer<PACTTBL> pActtbl; // 0x54
    PMBLOCK Mb[4];
    s16 EndFlag;
} PMOTION;

typedef struct {
    s16 joints[4];
    u16 vertex_count;
    u16 normal_count;
    u16 field_0xC;
    u16 field_0xE;
    u32 vertices_offset;
    u32 vertex_weights_offset;
    u32 normals_offset;
    u32 normals_weights_offset;
} PSPARTS;

typedef struct {
    long reg;
    long id;
} PGSREG;

typedef struct {
    s16 x;
    s16 y;
    s16 z;
} PVERTEX;

typedef struct {
    s32 u;
    s32 v;
} PUV;

typedef struct {
    u16 vertex;
    u16 uv;
    u16 normal;
    s16 flag;
} PINDEX;

// Size: 0x160
typedef struct { // 0x160
    /* 0x000 */ qword_uni GsEnv[16];
    /* 0x100 */ u64 gs_tex0;
    /* 0x108 */ PS2Pointer<s32> jblock_adrs;
    /* 0x10c */ PS2Pointer<s32> sfx_adrs;
    /* 0x110 */ PS2Pointer<s32> vert_adrs;
    /* 0x114 */ PS2Pointer<s32> norm_adrs;
    /* 0x118 */ PS2Pointer<s32> vert_adrs_mime0;
    /* 0x11c */ PS2Pointer<s32> norm_adrs_mime0;
    /* 0x120 */ PS2Pointer<s32> vert_adrs_mime1;
    /* 0x124 */ PS2Pointer<s32> norm_adrs_mime1;
    /* 0x128 */ PS2Pointer<s32> uv_adrs;
    /* 0x12c */ PS2Pointer<s32> prim_adrs;
    /* 0x130 */ PS2Pointer<s32> vert_wt_adrs;
    /* 0x134 */ PS2Pointer<s32> norm_wt_adrs;
    /* 0x138 */ f32 MimeWeight;
    /* 0x13c */ PS2Pointer<u32> GmsAdr;
    /* 0x140 */ u16 type;
    /* 0x142 */ u16 jblock_num;
    /* 0x144 */ u16 vert_num;
    /* 0x146 */ u16 norm_num;
    /* 0x148 */ u16 uv_num;
    /* 0x14a */ u16 prim_num;
    /* 0x14c */ u16 prim_blk;
    /* 0x14e */ u16 coord_id;
    /* 0x150 */ s16 GsEnvInd;
    /* 0x152 */ s16 SpecType;
    /* 0x154 */ s16 OutLine;

    void draw(KlonoaMemory* mem) {
        ImGui::Text("gs_tex0: %016lx", gs_tex0);
        ImGui::Text("jblock_adrs: %x", jblock_adrs.ptr);
        ImGui::Text("sfx_adrs: %x", sfx_adrs.ptr);
        ImGui::Text("vert_adrs: %x", vert_adrs.ptr);
        ImGui::Text("norm_adrs: %x", norm_adrs.ptr);
        ImGui::Text("type: %d", type);
        ImGui::Text("vert_num: %d", vert_num);
    }
} PPARTS;

typedef struct { // 0x8
    /* 0x0 */ u32 partsmax;
    /* 0x4 */ u8 *status;
} kitOutlineObjEnv;

typedef struct { // 0x90
    /* 0x00 */ s8 name[16];
    /* 0x10 */ s8 outline[64];
    /* 0x50 */ s8 spectype[64];
} SFXENV;

// Size: 0xA0
typedef struct PSFXOBJ {
    FVECTOR ScaleVector; // 0x00
    PS2Pointer<PMOTION> pMot; // 0x10
    PS2Pointer<FMATRIX> pLightColor; // 0x14
    PS2Pointer<FMATRIX> pNormalLight; // 0x18
    s32 PartsNum; // 0x1C
    PS2Pointer<u8> GmsAdrs; // 0x20
    PS2Pointer<u8> SubGmsAdrs; // 0x24
    PS2Pointer<u8> MimeAdrs; // 0x28
    PS2Pointer<u8> SvxAdrs; // 0x2C
    PS2Pointer<u8> SvxWorkAdrs; // 0x30
    PS2Pointer<SFXENV> EnvAdrs; // 0x34
    u16 GmsNum; // 0x38
    f32 scale; // 0x3C
    PS2Pointer<PPARTS> pParts;  // 0x40
    PS2Pointer<struct PSFXOBJ> pObjSub; // 0x44
    PS2Pointer<struct PSFXOBJ> pObjTop; // 0x48
    f32 ClutWeight; // 0x4C
    u32 Flag; // 0x50
    u32 Condition; // 0x54
    s16 Pause; // 0x58
    s16 GmsTransType; // 0x5A
    kitOutlineObjEnv LineEnv; // 0x5C
    PS2Pointer<PMIME> pMime; // 0x64
    s16 OutLineFlag; // 0x68
    f32 ClipOffset; // 0x6C
    f32 ClipZone; // 0x70
    s16 ClipFlag; // 0x74
    s16 Id; // 0x76
    u16 ClutNum0; // 0x78
    u16 ClutNum1; // 0x7A
    u16 Cbp; // 0x7C
    u16 NonActFlag; // 0x7E
    u16 MotionSyncFlag; // 0x80
    s32 ShadowType; // 0x84
    f32 ShadowSize; // 0x88
    f32 ShadowOffset; // 0x8C
    f32 ShadowRange; // 0x90
    s16 ObjNum; // 0x94
    s16 DrawWorkCnt; // 0x96
    s32 OutFlag; // 0x98
    s32 actNum; // 0x9C

    void Draw(KlonoaMemory* mem) {
        ScaleVector.draw(mem, "ScaleVector", -5.0, 5.0);
        drawFloat(mem, "ShadowSize", &ShadowSize, 0.0, 500.0);
        drawFloat(mem, "ShadowOffset", &ShadowOffset, 0.0, 500.0);
        drawFloat(mem, "ShadowRange", &ShadowRange, 0.0, 500.0);
        ImGui::Text("PartsNum: %d", PartsNum);
        ImGui::Text("scale: %f", scale);
        ImGui::Text("ObjNum: %d", ObjNum);

        if (ImGui::TreeNode("parts")) {
            for (int i = 0; i < PartsNum; i++) {
                std::string name = "parts[" + std::to_string(i) + "]";
                if (ImGui::TreeNode(name.c_str())) {
                    PPARTS* part = pParts.Get(mem, sizeof(PPARTS) * i);
                    part->draw(mem);
                    ImGui::TreePop();
                }
            }
            ImGui::TreePop();
        }

        if (pObjSub.IsValid() && ImGui::TreeNode("pObjSub")) {
            struct PSFXOBJ* sub = pObjSub.Get(mem);
            sub->Draw(mem);
            ImGui::TreePop();
        }

        if (pObjTop.IsValid() && ImGui::TreeNode("pObjTop")) {
            struct PSFXOBJ* top = pObjTop.Get(mem);
            top->Draw(mem);
            ImGui::TreePop();
        }
    }
} PSFXOBJ;

typedef struct PsfxMODEL {
    FVECTOR Trans; // 0x00
    FVECTOR Rot; // 0x10
    FVECTOR Scale; // 0x20
    PS2Pointer<PSFXOBJ> pObj; // 0x30
    int ActNum; // 0x34
    int old_muki; // 0x38
    int wip_timer; // 0x3C
    int dummy[4]; // 0x40

    void Draw(KlonoaMemory* mem) {
        Trans.draw(mem, "Trans", -2000, 2000);
        Rot.draw(mem, "Rot", -3.14, 3.14);
        Scale.draw(mem, "Scale", -5.0, 5.0);
        if (pObj.IsValid() && ImGui::TreeNode("pObj")) {
            pObj.Get(mem)->Draw(mem);
            ImGui::TreePop();
        }
        ImGui::Text("ActNum (0x%08x): %d", (char*)this + offsetof(PsfxMODEL, ActNum) - mem->ps2_ram, ActNum);
        if (ImGui::Button("Yeet")) {
            mem->Write<int>((char*)this + offsetof(PsfxMODEL, ActNum) - mem->ps2_ram, 1);
        }
    }
} PsfxMODEL;

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

typedef struct klMODEL : Prim {
    PsfxMODEL klm;
    PsfxMODEL ksm;
    PsfxMODEL kmm;
    PsfxMODEL shm;
    PsfxMODEL shm2;
} klMODEL;

void DrawKlMODEL(KlonoaMemory* mem, klMODEL* prim) {
    if (ImGui::TreeNode("klm")) {
        prim->klm.Draw(mem);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("ksm")) {
        prim->ksm.Draw(mem);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("kmm")) {
        prim->kmm.Draw(mem);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("shm")) {
        prim->shm.Draw(mem);
        ImGui::TreePop();
    }
    if (ImGui::TreeNode("shm2")) {
        prim->shm2.Draw(mem);
        ImGui::TreePop();
    }
}

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
        drawInt(mem, "proj", &proj, -4000, 4000);
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

    void draw(KlonoaMemory* mem) {
        drawInt(mem, "zoom", &zoom, -4000, 4000);
        drawInt3(mem, "ang", &angx, -1000, 1000);
        drawInt2(mem, "trns", &trnsx, -1000, 1000);
        drawInt(mem, "proj", &proj, -4000, 4000);
        ImGui::Text("flg: %d", flg);
    }
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

typedef struct {
    PS2Pointer<FVECTOR> norm;
    PS2Pointer<FVECTOR> center;
    PS2Pointer<FVECTOR> vert;
    float rx;
    float ry;
    float cx;
    float cy;
    float clen;
    uint count;

    void draw(KlonoaMemory* mem) {
        drawFloat2(mem, "rot", &rx, -M_PI, M_PI);
        drawFloat2(mem, "cam", &cx, -M_PI, M_PI);
        drawFloat(mem, "clen", &clen, 0.0f, 10.0f);
        ImGui::Text("count: %d", count);
    }
} HFMIR;

typedef struct {
    u32 type;
    u16 group_num;
    s16 minx;
    s16 miny;
    s16 minz;
    s16 maxx;
    s16 maxy;
    s16 maxz;
} CHeader;

typedef struct {
    u8 cache;
    u8 id;
    s16 x;
    s16 y;
    s16 z;
    s16 nx;
    s16 ny;
    s16 nz;
    s16 s;
    s16 t;
    u8 r;
    u8 g;
    u8 b;
    u8 a;
} CPacked;

#endif