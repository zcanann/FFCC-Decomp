#ifndef GUARD_TEXT_H
#define GUARD_TEXT_H

#include "global.h"

/* Text_Print modes */
#define TEXT_DRAW     0
#define TEXT_DRAW_FIX 1 /* centre narrow glyphs in a fixed 9-pixel cell */
#define TEXT_WIDTH    2 /* return the width without drawing */
#define TEXT_CHAR     3 /* return the width of the first character */

extern u8 gLanguage;

void Text_Init(void);
void Text_SetFill(s32 on, s32 no);
void Text_Clear(void);
s32 Text_Print(const char *str, s32 mode);
void Text_CopyToVram(u32 dst, s32 n);
void Text_LoadPalette(s32 no, s32 id, s32 base);
void Font_LoadPalette(u32 dst, s32 no);
void Text_CopyFill(u32 dst);
void Text_SetX(s32 x);
void Text_AddX(s32 dx);
u32 Text_GetX(void);
void Text_CopyToObj(s32 which, s32 n, s32 color);
void Text_ClearObj(s32 which);
void Text_SwapFill(void);

/* Localised text tables, indexed by gLanguage & 0xF */
#if defined(VERSION_GCCJGC)
extern char *gTribeNames_Jp[];
extern char *gSystemText_Jp[];
extern char *gJobNames_Jp[];
extern char *gStatNames_Jp[];
extern char *gNoticeText_Jp[];
extern char *gTraitNames_Jp[];
extern char *gItemNames_Jp[];
extern char *gMonsterNames_Jp[];
extern char *gItemDescs_Jp[];
extern char *gCMakeText_Jp[];
extern char *gLookNames_Jp[];
extern const u8 gItemIcons[];

#define Msg_GetTribe(idx) (gTribeNames_Jp[(idx)])
#define Msg_GetSystem(idx) (gSystemText_Jp[(idx)])
#define Msg_GetJob(idx) (gJobNames_Jp[(idx)])
#define Msg_GetStat(idx) (gStatNames_Jp[(idx)])
#define Msg_GetNotice(idx) (gNoticeText_Jp[(idx)])
#define Msg_GetTrait(idx) (gTraitNames_Jp[(idx)])
#define Msg_GetItemName(idx) (gItemNames_Jp[(idx)])
#define Msg_GetMonsterName(idx) (gMonsterNames_Jp[(idx)])
#define Item_GetIcon(idx) (gItemIcons[(idx)])
#define Msg_GetCMake(idx) (gCMakeText_Jp[(idx)])
#define Msg_GetLook(idx) (gLookNames_Jp[(idx)])
#else
char *Msg_GetTribe(s32 idx);
char *Msg_GetSystem(s32 idx);
char *Msg_GetJob(s32 idx);
char *Msg_GetStat(s32 idx);
char *Msg_GetNotice(s32 idx);
char *Msg_GetTrait(s32 idx);
#endif
#if !defined(VERSION_GCCJGC)
char *Msg_GetLook(s32 idx);
char *Msg_GetCMake(s32 idx);
#endif
char *Msg_GetLetter(s32 idx);
#if !defined(VERSION_GCCJGC)
char *Msg_GetItemName(s32 idx);
s32 Item_GetIcon(s32 idx);
char *Msg_GetMonsterName(s32 idx);
void Msg_GetItemDesc(s32 idx, char *buf);
#endif

#endif
