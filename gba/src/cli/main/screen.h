#ifndef GUARD_SCREEN_H
#define GUARD_SCREEN_H

#include "global.h"

/* gMode, set by the GameCube with cmd 27 */
#define MODE_FIELD      0
#define MODE_CMAKE      1
#define MODE_SHOP       2
#define MODE_SMITH      3
#define MODE_CONTROLLER 4

/* gScreenPhase */
#define PHASE_INIT 0
#define PHASE_MAIN 1
#define PHASE_EXIT 2

/* Each screen of a mode has an init, main and exit function; each returns
   nonzero when its phase is finished. */
struct ScreenFuncs {
    s32 (*init)(void);
    s32 (*main)(void);
    s32 (*exit)(void);
};

extern u32 gMode;
extern s32 gScreen;
extern s32 gScreenPhase;
extern s32 gSavedScreen;
extern s32 gScreenInitDone;
extern s32 gSubState;
extern s32 gSubMode;
extern s8 gScreenStep;
extern s8 gOpenMenuReq;
extern s8 gMsgScreenId;
extern s8 gLetterAttachKind;
extern s8 gInfoWinReady;
extern s8 gShopMenuPos[2];

void Mode_Init(void);
s32 Mode_Update(void);
s32 FieldMode_Update(void);
s32 CMakeMode_Update(void);
s32 ShopMode_Update(void);
s32 SmithMode_Update(void);
s32 CtrlMode_Update(void);
void Mode_OnSet(u32 data);
void Menu_OnOpen(u32 data);
void Screen_Reset(void);
void Screen_Restart(void);
s32 Screen_Idle(void);

s32 MsgScreen_Init(void);
s32 MsgScreen_Main(void);
s32 RadarScreen_Init(void);
s32 RadarScreen_Main(void);
s32 RadarScreen_Exit(void);
s32 ScouterScreen_Init(void);
s32 ScouterScreen_Main(void);
s32 ScouterScreen_Exit(void);
void MenuScreen_SetReturn(s32 screen);

/* Screens that other modules refresh when new data arrives */
void ArtifactScreen_Refresh(void);
void CmdListScreen_BuildCandidates(void);
void CmdListScreen_PrintSlot(s32 row);
void CmdListScreen_AddSlot(void);
void ItemScreen_RefreshItem(s32 idx);
void ShopList_RefreshSellItem(s32 idx);
void Smith_SetResultSlot(s8 slot);
void Smith_ResetList(void);
/* Called with and without the row. */
void TmpArtifactScreen_PrintRow();
void TmpArtifactScreen_RefreshRow(s32 row);
void CMake_Reset(void);
void Letter_SetGilAttachment(s32 ok, u32 gil);
void Letter_SetItemAttachment(s32 ok, u32 item, s32 slot);

#endif
