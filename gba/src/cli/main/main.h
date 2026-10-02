#ifndef GUARD_MAIN_H
#define GUARD_MAIN_H

#include "global.h"

/* Pad state, updated once per frame by Input_Update. */
extern u16 gKeysHeld;
extern u16 gKeysPrev;
extern u16 gKeysNew;      /* pressed this frame */
extern u16 gKeysRepeat;   /* pressed this frame, or held with auto-repeat */
extern u16 gKeysReleased;
extern u16 gKeysToggled;
extern u16 gKeysCurrent;

extern u32 gFrameCount;
extern u8 gWasConnected;
extern u8 gReconnectPending;
extern u8 gInputLockFrames;
extern u8 gSpMode;

extern const s16 gSinTable[];

void AgbMain(void);
void IntrDummy(void);
void VBlankIntr(void);
void SoundIntr(void);
void Input_Init(void);
void Input_Update(void);

void Header_Init(void);
void Header_Clear(void);
void Header_Print(const char *str);
void Header_DrawBar(void);

/* Called with and without an argument (the look screen passes none). */
void Bg_LoadBackdrop();
void Bg_CopyBackdropToRadar(void);
void Bg_ClearMaps(void);
void Bg_LoadPlayerPalette(void);
u16 *Bg_GetMapPtr(s32 bg, s32 x, s32 y);
void Bg_SetScroll(u8 mask, u16 x, u16 y);
void Bg_ApplyScroll(void);

void Shake_Reset(void);
void Shake_Start(void);
void Shake_Update(void);
void Shake_GetOffset(s8 *x, s8 *y);

void Text_PrintNumber(s32 value, s32 x, s32 digits);
void IntToStr(char *buf, s32 value);
s16 FixMul(s16 a, s16 b);
s16 FixDiv(s16 a, s16 b);
s16 FixInverse(s16 a);
void Str_GetChar(const char *str, s32 n, char *out);
/* Called with an extra argument by the name entry screen. */
s32 Str_IsWideChar();
s32 Str_Length(const char *str);

void Alarm_Update(void);
void Alarm_Reset(void);
void SpMode_Apply(void);

#endif
