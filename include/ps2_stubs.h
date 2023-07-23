#ifndef PS2_STUBS_H
#define PS2_STUBS_H

#include "types.h"

// libvu0.h
typedef s32	qword[4] __attribute__ ((aligned(16)));
typedef s32 sceVu0IVECTOR[4] __attribute__((aligned(16)));
typedef f32	sceVu0FVECTOR[4] __attribute__((aligned(16)));
typedef f32	sceVu0FMATRIX[4][4] __attribute__((aligned(16)));

// eestruct.h
typedef struct {
    u64 TBP0 : 14;
    u64 TBW  : 6;
    u64 PSM  : 6;
    u64 TW   : 4;
    u64 TH   : 4;
    u64 TCC  : 1;
    u64 TFX  : 2;
    u64 CBP  : 14;
    u64 CPSM : 4;
    u64 CSM  : 1;
    u64 CSA  : 5;
    u64 CLD  : 3;
} sceGsTex0;

// libgraph.h
typedef s32 sceGsDBuffDc[0xCC];

#endif
