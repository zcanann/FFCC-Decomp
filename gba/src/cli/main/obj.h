#ifndef GUARD_OBJ_H
#define GUARD_OBJ_H

#include "global.h"

void Obj_Init(void);
void Oam_ClearBuffer(void);
void Obj_Draw(s32 x, s32 y, s32 cell, s32 frame, s32 pal, s32 prio, u32 flags);
void Obj_Nop(void);
void Oam_SortByPriority(void);
void Oam_UpdateAffine(void);
void Obj_SetAffine(s32 no, s32 angle, s32 sx, s32 sy);
void Oam_Commit(void);
void Oam_Reset(void);
u8 Obj_GetFrameCount(s32 cell);
s32 Obj_GetPalette(s32 cell, s32 frame);
void Obj_LoadToBg(s32 cell, s32 slot, s32 bg, s32 frame);
void Obj_AllocPalette(s32 cell, s32 frame);
void Obj_FreePalette(s32 cell);
void Obj_FreeAllPalettes(void);
void Oam_Transfer(void);
void Obj_ReloadPalettes(void);

#endif
