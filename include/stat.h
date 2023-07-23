#ifndef STAT_H
#define STAT_H

#include <string>
#include <map>
#include "types.h"

inline std::string STAT0[] = {
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

inline std::string NK_STAT1[] = {
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

inline std::map<s16, std::string> OK_TEST_STAT1 = {
    { 0, "Z_Balloon00" },
    { 1, "Z_Balloon01" },
    { 2, "Z_BalloonXX" },
    { 3, "B_Man00" },
    { 4096, "I_Main" },
    { 13312, "D_Csr00" },
    { 16512, "M_Chip00" },
};

inline std::map<s16, std::string> OK_STAT1 = {
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

std::string HR_STAT1[] = {
    "mapexpl",
    "switch_trg",
    "game_puppet",
    "ptefc_work",
    "game_puppet",
    "game_puppet",
    "obcex_work",
    "dummy_obcw"
};

inline std::map<s16, std::string> AB_STAT1 = {
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

inline std::string HT_STAT1[] = {
    "htBOSS_NULL",
    "htBOSS_02",
    "htBOSS_02_BUNSIN",
    "htBOSS_03",
    "htBOSS_06",
    "htBOSS_06_MIST_BALL",
    "htB2_EFF",
    "htBOSS_GIMM",
    "htBOSS_01",
    "htBOSS_01_ATK_TOP",
    "htBOSS_04",
    "htBOOST_RING",
    "htATTACK_NUT",
    "htBOARD_MYU",
    "htBMYU_PA",
    "htATTACK_ICE",
    "htBOSS_07",
    "htB7_BIT",
    "htZAKO_BALLOON",
    "htBOSS_08",
    "htITEM",
    "htZAKO_TAT",
    "htZAKO_TAT2",
    "htZAKO_TAT2_PA",
    "htSOUND",
    "htZAKO_OBAKE",
    "htTAKA_EFFECT",
    "htB71_BG",
    "htNEMO_MYU",
    "htB7_BIT2",
    "htB8_ATK_PA",
    "htB71_BG_OBJ",
    "htPT_BOSS",
    "htTAT_BOMB",
    "htBOOST_RING_1702",
    "htBOSS_00",
    "htBOSS_00_HAND",
    "htZAKO_TAT2_BOMB",
    "htMETA_ENMY",
    "htEV_JORA",
    "htEV_JORA2",
    "htAREA2702",
    "htKING_ATTACK"
};

inline std::string KZ_STAT1[] = {
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
            return NK_STAT1[stat1].c_str();
        case 2:
            return OK_TEST_STAT1[stat1].c_str();
        case 3:
            return OK_STAT1[stat1].c_str();
        case 4:
            return "eh? (4)";
        case 5:
            return HR_STAT1[stat1].c_str();
        case 6:
            return AB_STAT1[stat1].c_str();
        case 7:
            return HT_STAT1[stat1].c_str();
        case 8:
            return KZ_STAT1[stat1].c_str();
        case 9:
            return "??? (9)";
        default:
            return "bruh";
    }
}

#endif
