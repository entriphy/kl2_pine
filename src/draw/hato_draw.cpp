#include "drawable.h"
#include "hato/ht_boss00.h"

template<> void Drawable<htBoss00Data>::DrawImpl(htBoss00Data *obj, const char *label, float min, float max) {
    Drawable<sceVu0FVECTOR>::Draw(&obj->weak_offset, "weak_offset");
    Drawable<sceVu0FVECTOR>::Draw(&obj->weak_pos, "weak_pos");
    Drawable<sceVu0FVECTOR>::Draw(&obj->ref_offset, "ref_offset");
    Drawable<sceVu0FVECTOR>::Draw(&obj->ref_pos, "ref_pos");
    Drawable<sceVu0FVECTOR>::Draw(&obj->ref_vp, "ref_vp");
    Drawable<sceVu0FVECTOR>::Draw(&obj->hand_offset[0], "hand_offset[0]");
    Drawable<sceVu0FVECTOR>::Draw(&obj->hand_offset[1], "hand_offset[1]");
    Drawable<sceVu0FVECTOR>::Draw(&obj->hand_offset[2], "hand_offset[2]");
    Drawable<sceVu0FVECTOR>::Draw(&obj->hand_offset[3], "hand_offset[3]");
    Drawable<sceVu0FVECTOR>::Draw(&obj->ref_move_vec, "ref_move_vec");

    Drawable<SFXOBJ>::DrawTree((u32)obj->sfx_boss, "sfx_boss");
}

template<> void Drawable<htBoss00HandData>::DrawImpl(htBoss00HandData *obj, const char *label, float min, float max) {
    Drawable<SFXOBJ>::DrawTree((u32)obj->sfx_hand, "sfx_hand");
}