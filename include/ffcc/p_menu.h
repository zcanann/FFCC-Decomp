#ifndef _FFCC_P_MENU_H_
#define _FFCC_P_MENU_H_

#include "ffcc/memory.h"
#include "ffcc/math.h"
#include "ffcc/memorycard.h"
#include "ffcc/mcctrl.h"
#include "ffcc/gobject.h"
#include "ffcc/p_sample.h"
#include "ffcc/system.h"

#include <dolphin/gx.h>

class CColor;
class CFontMan;
class CFont;
class CTexture;
class CTextureSet;
class CPad;
class CRingMenu;
class CMesMenu;
class CShopMenu;
struct ArtiState;
struct ArtiOpenAnimList;
struct EquipMenuState;
struct EquipOpenAnimList;
struct MoneyMenuState;
struct MoneyMenuAnimList;
struct MenuLstState;
struct MenuLstList;
struct ItemMenuState;
struct ItemMenuAnimList;
struct CmakeMenuState;
struct GoOutMenuState;

struct MenuBoardEntry
{
    int m_modelHandle;
    int m_effectHandle;
    short m_centerX;
    short m_centerY;
    short m_width;
    short m_height;
    float m_posX;
    float m_posY;
    float m_depth;
    float m_rotX;
    float m_rotY;
    float m_rotZ;
    float m_scaleX;
    float m_scaleY;
    float m_scaleZ;
    float m_unk34;
    float m_unk38;
    float m_unk3c;
    int m_screenX;
    int m_screenY;
    int m_screenWidth;
    int m_screenHeight;
};

struct SingleFadeEntry
{
    short x;
    short y;
    short width;
    short height;
    float u;
    float v;
    float alpha;
    float uvScale;
    int unk18;
    int tex;
    int elapsed;
    int startFrame;
    int duration;
    unsigned int flags;
    float dx;
    float dy;
    float targetX;
    float targetY;
};

struct SingleFadeState
{
    short count;
    short pad_02;
    short active;
    short done;
    SingleFadeEntry entries[64];
};

struct WinMessEntry
{
    int m_lineCount;
    short m_messageIds[8];
};
STATIC_ASSERT(sizeof(WinMessEntry) == 0x14);
STATIC_ASSERT(offsetof(WinMessEntry, m_messageIds) == 0x04);

struct MenuWindowInfo
{
    short x;
    short y;
    short width;
    short height;
    short frame;
    short state;
};

struct WmCharaModelInfo
{
    int m_unknown00;
    int m_unknown04;
    int m_modelNo;
    unsigned char m_modelChanged;
    unsigned char m_pad0D[3];
    SRT m_transform;
};
STATIC_ASSERT(sizeof(WmCharaModelInfo) == 0x34);
STATIC_ASSERT(offsetof(WmCharaModelInfo, m_modelNo) == 0x08);
STATIC_ASSERT(offsetof(WmCharaModelInfo, m_modelChanged) == 0x0C);
STATIC_ASSERT(offsetof(WmCharaModelInfo, m_transform) == 0x10);

struct WmCharaSelectEntry
{
    int m_padType;                   // 0x00
    short m_currentSlot;             // 0x04
    short m_displaySlot;             // 0x06
    unsigned short m_disconnectTime; // 0x08
    unsigned char m_confirmed;       // 0x0A
    unsigned char m_cmakePending;    // 0x0B
    unsigned char m_cmakeReady;      // 0x0C
    unsigned char m_connected;       // 0x0D
    unsigned char m_cancelled;       // 0x0E
    unsigned char _pad0F;            // 0x0F
};

STATIC_ASSERT(sizeof(WmCharaSelectEntry) == 0x10);
STATIC_ASSERT(offsetof(WmCharaSelectEntry, m_currentSlot) == 0x04);
STATIC_ASSERT(offsetof(WmCharaSelectEntry, m_confirmed) == 0x0A);
STATIC_ASSERT(offsetof(WmCharaSelectEntry, m_cancelled) == 0x0E);

struct WmCharaAnimState
{
    int m_animIndex;
    int m_nextAnimIndex;
    int m_timer;
    float m_frame;
    float m_endFrame;
};
STATIC_ASSERT(sizeof(WmCharaAnimState) == 0x14);

struct WmWorldState
{
    float m_posX;
    float m_posY;
    char m_worldReady;
    char m_flag09;
    char m_flag0A;
    char m_flag0B;
    char m_modelFlagsInitialized;
    unsigned char m_pad0D;
    short m_state0E;
    short m_mainState;
    short m_state12;
    short m_state14;
    short m_subState;
    short m_delay;
    short m_counter1A;
    short m_menuMode;
    short m_nextMenuMode;
    short m_changeRequest;
    short m_frameCounter;
    short m_titleState;
    short m_cardChannel;
    unsigned char m_pad28[0x2E - 0x28];
    short m_mcResult;
    unsigned char m_pad30[0x36 - 0x30];
    short m_originalBackupParams[4];
    short m_backupParams[4];
    short m_pad46;
};

struct SingMenuState
{
    char pad_00[0x0B];
    char initialized;
    char pad_0C;
    char closeRequested;
    char pad_0E[0x10 - 0x0E];
    short stepState;
    short procState;
    short subState;
    char pad_16[0x1E - 0x16];
    short cursorMove;
    char pad_20[0x22 - 0x20];
    short frame;
    char pad_24[0x26 - 0x24];
    short selectedIndex;
    short scrollIndex;
    char pad_2A[0x2E - 0x2A];
    short result;
    short uniteState;
    char pad_32[0x34 - 0x32];
    short topIndex;
    char pad_36[0x48 - 0x36];
};

struct FavoListStorage;
struct CompaMenuState;
struct CompaOpenAnimList;
struct TmpArtiState;
struct TmpArtiList;

struct McListInfo
{
    void operator=(const McListInfo&);
};

class CMenuPcs : public CProcess
{
public:
    static CProcessCallbackTable m_table;

    struct BattleHudState
    {
        int m_visible;
        float m_worldPos[3];
        int m_fadeCounter;
        int m_gaugeCounter;
        int m_width;
        int m_gaugeMax;
        int m_gaugeTarget;
        int m_gaugeValue;
    };

    struct CTmp
    {
        int m_textureSetIndex;
        char* m_textureName;
    };
    struct MaterialInfo
    {
        short m_itemNo[3];
        short m_count[3];
    };
    struct GoOutResetFields
    {
        unsigned char m_resetFlag;
        unsigned char m_unknown879;
        unsigned char m_unknown87A;
        unsigned char m_unknown87B;
    };
    struct Sprt
    {
        short m_x;
        short m_y;
        short m_width;
        short m_height;
        float m_u;
        float m_v;
        float m_scaleX;
        float m_scaleY;
        unsigned int m_flags;
    };
    struct WmFrameInfo
    {
        int m_unknown;
        Sprt m_sprites[2];
    };
    struct Sprt2
    {
        void operator=(const Sprt2&);
    };
    struct SPL
    {

    };
    struct FCV
    {
        int keyCount;
        float* keys;
    };
    struct EffectInfo
    {
        int m_effectNo;
        int m_partNo;
        int m_slotNo;
        CGObject m_object;

        EffectInfo();
    };
    struct EffectEntry
    {
        unsigned char m_pad00[0x0C];
        int m_iconType;
        unsigned char m_pad10[0x28 - 0x10];
        unsigned int m_flags;
        unsigned char m_pad2C[0x48 - 0x2C];
    };
    enum MENUMODE
	{
		TODOA,
	};
    enum FMT
	{
		TODOB,
	};
    enum TEX
	{
		TODOC,
	};

    CMenuPcs() {}
    ~CMenuPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void loadFont(int, char*, int, int);
    void loadTexture(char**, int, int, CTmp*, int, int, int);
    void freeTexture(int, int, int, int);

    void changeMode(MENUMODE);
    int GetMenuMode();

    void calc();
    void draw();

    void DrawInit();
    void DrawQuit();

    void SetAttrFmt(FMT);
    void SetTexture(TEX);
    void SetColor(CColor&);

    unsigned short GetButtonDown(int);
    unsigned short GetButtonRepeat(int);

    void onScriptChanging(char*);
    void onMapChanging(int, int);
    void onMapChanged(int, int, int);

    void DrawRect(unsigned long, float, float, float, float,
                  float, float, float, float, float);

    void DrawRect(unsigned long, float, float, float, float,
                  float, float, _GXColor*, float, float, float);

    void DrawBar(float, float, float, TEX, float);
    void DrawWindow(float, float, float, float, TEX, float);
    void DrawSingleIcon(int, int, int, float, int, float);
    float CalcListPos(int, int, int);
    void DrawListPosMark(float, float, float);
    void DrawSingLife();
    float CalcCenteringPos(char*, CFont*);
    float CalcCenteringPos2(char*, float, float);
    void DrawFont(int, int, _GXColor, int, char*, float, float);
    void DrawFont2(int, int, _GXColor, int, char*, float, float, float);
    void DrawHelpMessageUS(int, CFont*, int, int, _GXColor, int, float, float);
    void DrawHelpMessage(int, CFont*, int, int, _GXColor, int, float, float);
    void DrawEquipMark(int, int, float);
    char* GetMenuStr(int);

    void LoadExtraFont(int, char*);
    void SetExtraFontTlut(int, _GXColor);

    void drawPause();

    void createBattle();
    void destroyBattle();
    void calcBattle();
    void drawBattle();

    void BonusInit();
    void createBonus();
    void destroyBonus();
    void calcBonus();
    void drawBonus();

    void CalcResultOpenAnim();
    void DrawResultOpenAnim();
    void CalcResultCountAnim();
    void DrawResultCountAnim();
    void CalcResultCloseAnim();
    void DrawResultCloseAnim();

    void CalcSelectOpenAnim();
    void DrawSelectOpenAnim();
    void CalcSelectWait();
    void CalcSelectCloseAnim();

    void DrawBonusFrame(float, float, float, float, float);
    void DrawArtiBase(CMenuPcs::Sprt2*, float);
    void ArtiBaseInfoInit(CMenuPcs::Sprt2*, CMenuPcs::Sprt2*);

    void ClrBattleItem();

    void ChgPlayModeFromScript(bool);

    CTexture* GetTexture(TEX);
    McCtrl* GetMcCtrl() { return &m_mcCtrl; }

    void WmInit();
    void createWorld();
    void createSingleMenu();
    void destroySingleMenu();
    void SingMenuInit();
    void CreateShopMenu();
    void CreateSmithMenu();
    void SingMenuEnd();
    void destroyVillageMenu();
    void ChkNumItemAll();
    void loadData();
    void InitFrameInfo();
    void InitFrame0Info();
    void InitCharaInfo();
    void InitCharaSelectInfo();
    void InitCSelCurPos();
    void destroyWorld();
    void calcWorld();
    void calcSingleMenu();
    void calcVillageMenu();
    void CalcMainMenu();
    void CalcDiaryMenu();
    void CalcMCardMenu();
    void CalcCMakeMenu();
    void CalcSingCMake();
    void CalcMoveMenu();
    void InitSaveLoadMenu();
    void CalcLoadMenu();
    void CalcTitleMenu();
    void CalcOptionMenu();
    void CalcGoOutCharaSelect(unsigned char);
    int CalcGoOutSelChar(unsigned char, unsigned char);
    void CalcGoOutSelCharInit();
    void SetMenuCharaAnim(int, int);
    unsigned int IsMenuCharaAnimIdle(int);
    void drawWorld();
    void drawSingleMenu();
    void drawVillageMenu();
    void DrawMainMenu();
    void DrawDiaryMenu();
    void DrawDiaryBase(int, float);
    void DrawMCardMenu();
    void DrawCMakeMenu();
    void DrawSingCMake();
    void DrawCmakeWin(float, float, float);
    void DrawCmakeTitle(int, float, float);
    void DrawCrystal(int, int, float);
    void DrawCmakeNameBase(int, float);
    void DrawCmakePageMark(float);
    void DrawCmakeDecision(int, float);
    void DrawCmakeBallCursor(int, int, float);
    void DrawCmakeCharaText(int, float);
    void DrawCmakeCrest(int, int, int, float);
    void DrawCmakeName(int, int, char*, float);
    void AddNameChara(int, int, int, int);
    void DrawCmakeYesNo(int, float);
    void DrawMoveMenu();
    void DrawLoadMenu();
    void DrawTitleMenu();
    void DrawOptionMenu();
    void SetWorldParam(int, int);
    unsigned int GetWorldParam(int);
    void CallWorldParam(int, int, int);
    void CalcSpl(SPL*, SPL*, float);
    float GetFcvValue(FCV, float);
    void SetProjection(int);
    void RestoreProjection();
    void DrawObj(int);
    void loadTextureAsync(char**, int, int, CTmp*, int, int, int);
    void CalcPitcher();
    void CalcFukidashi();
    void SetCrystalCageAttr();
    void SetManaWaterEffect();
    void DrawFukidashi();
    void ChkPlaceLength(char*);
    void SplitPlace(const char*, char*, char*);
    void SplitPlace2(const char*, char*, char*, CFont*, int);
    void CalcWMFrame();
    void DrawWMFrame();
    void CalcWMFrame0(int);
    void DrawWMFrame0(int, float);
    void DrawMainMenuBase(float);
    void CalcCharaBase();
    void DrawCharaBase();
    void CalcChara();
    void PCAnimCtrl();
    void GetAnimNo(int, int);
    void DrawChara();
    int GetModelNo(int, int, int);
    void CalcCharaSelect();
    void DrawCharaName();
    void DrawCMLife();
    void WMSubMenuInit();
    void WMChgMenu();
    void GetOptionData();
    const char* GetSkillStr(int);
    char* GetTribeStr(int);
    char* GetJobStr(int);
    char* GetHairStr(int);
    int GetItemType(int, int);
    int GetItemIcon(int);
    void ArtiInit();
    void ArtiInit1();
    int ArtiOpen();
    int ArtiCtrl();
    int ArtiClose();
    void ArtiDraw();
    int ArtiCtrlCur();
    void EquipInit1();
    int EquipOpen();
    int EquipCtrl();
    int EquipClose();
    void EquipDraw();
    int EquipCtrlCur();
    int EquipOpen0();
    int EquipClose0();
    int ChkEquipActive(int);
    int ChkEquipPossible(int);
    int GetEquipType(int);
    int EquipChk(int);
    void TmpArtiInit();
    void TmpArtiInit0();
    unsigned int TmpArtiOpen();
    int TmpArtiCtrl();
    unsigned int TmpArtiClose();
    void TmpArtiDraw();
    int TmpArtiCtrlCur();
    void ItemInit();
    void ItemInit1();
    int ItemOpen();
    int ItemCtrl();
    int ItemClose();
    void ItemDraw();
    int ItemCtrlCur();
    void SingLifeInit(int);
    int MoneyOpen();
    int MoneyCtrl();
    int MoneyClose();
    void MoneyDraw();
    int MoneyCtrlCur();
    inline void MoneySetPlace(int);
    void MLstInit();
    void MLstInit1();
    int MLstOpen();
    int MLstCtrl();
    int MLstClose();
    void MLstDraw();
    void MLstCtrlCur();
    void CmdInit();
    void CmdInit0();
    void CmdInit1();
    void CmdInit2();
    void CmdOpen();
    int CmdCtrl();
    int CmdClose();
    void CmdDraw();
    unsigned int CmdCtrlCur();
    unsigned int CmdOpen0();
    unsigned int CmdClose0();
    void GetCmdItem();
    void ChkCmdActive(int);
    int ChkUnite(int, int (*)[2]);
    void CmdUnite(int, int);
    void CmdDismantle(int);
    void DrawUniteList();
    int UniteOpenAnim(int);
    int UniteCloseAnim(int);
    unsigned int CmdOpen1();
    unsigned int CmdClose1();
    void CmdOpen2();
    unsigned int CmdClose2();
    void GetFontItem();
    char* GetAttrStr(int);
    void SetParty();
    void SetCMakeEnd(int);
    void ClrCMakeFlg(int);
    void CmakeOpen();
    void CmakeCtrl();
    void CmakeClose();
    void CmakeDraw();
    void CmakeNameOpen();
    int CmakeNameCtrl();
    void CmakeNameClose();
    void CmakeNameDraw();
    void CmakeSexOpen();
    void CmakeSexCtrl();
    void CmakeSexClose();
    void CmakeSexDraw();
    void CmakeTribeOpen();
    int CmakeTribeCtrl();
    void CmakeTribeClose();
    void CmakeTribeDraw();
    void CmakeJobOpen();
    int CmakeJobCtrl();
    void CmakeJobClose();
    void CmakeJobDraw();
    void CmakeResultOpen();
    void CmakeResultCtrl();
    void CmakeResultClose();
    void CmakeResultDraw();
    void CmakeResultOpen1();
    void CmakeResultCtrl1();
    void CmakeResultClose1();
    void CmakeResultDraw1();
    void CmakeVillageOpen();
    unsigned short CmakeVillageCtrl();
    void CmakeVillageClose();
    void CmakeVillageDraw();
    void SetSingMakeChara();
    void CalcSingleCMakeChara();
    void DrawSingleCMakeChara(float);
    void ChgAllModel();
    void ChgAllModel2();
    void SetMakeChara(int);
    void ChgModel(int, int, int, int);
    void SetAnim(int);
    void DrawCursor(int, int, float);
    void SingCalcChara(float);
    void DrawSingleBase(float);
    void DrawSingleCrescent(float, float);
    void DrawSingleStat(float);
    void DrawSingleHelpWim(float);
    void SingleCalcFadeIn();
    void SingleDrawFadeIn();
    void SingleCalcFadeOut();
    void SingleDrawFadeOut();
    void SingleCalcCtrl();
    void SingleDrawCtrl();
    void DrawShadowFont(CFont*, char*, float, float, int, int);
    void DrawNoShadowFont(CFont*, char*, float, float, int, int);
    void DrawSingWin(short);
    void DrawSingWinMess(int, int, int);
    int SingWinMessHeight();
    void GetSingWinSize(int, short*, short*, int);
    void SetSingDynamicWinMessInfo(int, char*, char*, char*, char*, char*, char*, char*, char*);
    void SetSingWinScl(float);
    float GetSingWinScl();
    void SetSingWinInfo(int, int, int, int);
    void SingSetLetterAttachflg(int);
    int SingGetLetterAttachflg();
    int GetSmithItem(int);
    void GetRecipeMaterial(int, MaterialInfo*);
    void GetRaceStr(int, char*);
    void CalcSingLife();
    void LetterSetAttachItem(unsigned int, int);
    inline void LetterInit();
    inline void LetterInit0();
    void LetterInit1();
    inline void LetterInit2();
    inline void LetterInit3();
    inline void LetterInit4();
    bool LetterOpen();
    int LetterCtrl();
    int LetterClose();
    inline void LetterLstOpen();
    inline void LetterLstClose();
    inline void LetterMessOpen();
    inline void LetterItemWinOpen();
    inline void LetterItemWinClose();
    int LetterReplyWinOpen();
    inline void LetterReplyWinClose();
    inline void LetterAttachWinOpen();
    inline void LetterAttachWinClose();
    int LetterConfirmOpen();
    inline void LetterConfirmClose();
    void LetterDraw();
    void LetterListDraw();
    void LetterMessDraw();
    int LetterCtrlCur();
    void LetterLstBaseDraw(float);
    void DrawSingBar(int, int, int, float);
    void SingLifeResetWait();
    void FavoInit();
    void FavoInit0();
    int FavoOpen();
    int FavoCtrl();
    int FavoClose();
    void FavoDraw();
    void CompaInit();
    void CompaInit0();
    int CompaOpen();
    void CompaCtrl();
    int CompaClose();
    void CompaDraw();
    void CalcMainMenuSub();
    void ChkSelectParty();
    void DrawMainMenuSub();
    void GetMcAccessPos(int*, int*);
    void GetMcOdekakePos(int*, int*);
    void ChkMcDataCnt();
    void DrawMCList();
    void DrawHelpBase(int, float);
    void CalcMcObj();
    void DrawMcObj();
    void SetMcList(int, struct McListInfo*);
    void ClrMcList();
    unsigned int BindEffect(int, int, int);
    void SetLight(int);
    void DrawPageMark();
    void DrawRect2(unsigned long, float, float, float, float, float, float, float, float, float (*)[4]);
    void DrawRect3d(unsigned long, float, float, float, float, float, float, float, float, float);
    void SetMcWinInfo(int, int);
    void DrawMcWin(short, short);
    void DrawMcWinMess(int, int);
    void GetWinSize(int, short*, short*, int);
    int GetSlotABXPos(int);
    const char* GetMcStr(int);
    const char* const* GetMcWinMessBuff(int);
    WinMessEntry* GetWinMess(int);
    int GetYesNoXPos(int);
    void SetTextureLoc(int);
    float GetMaxAnimWait();
    void BindMcObj(int);
    void BindMcObj();
    void DrawFilter(unsigned char, unsigned char, unsigned char, unsigned char);
    CFont* GetFont22();
    CMesMenu* GetMesMenu(int);
    void CopyNowCaravanDat(Mc::SaveDat*);
    void SetCaravanWork(Mc::SaveDat*);
    int GetSameCharaData(Mc::SaveDat*, Mc::SaveDat*, int, int);
    int CheckSameMcFormatID(Mc::SaveDat*, Mc::SaveDat*);
    void IsAsyncCharaLoadFinish();
    void AlphaNormal();
    void AlphaAdd();
    void GetFontWorld();

    struct BonusStorage
    {
        unsigned char m_pad744[0x814 - 0x744];
        int m_bonusBoardPtr;
        unsigned char m_pad818[0x82C - 0x818];
    };

    struct WmStorage
    {
        Mtx m_savedCameraMatrix;
        CCharaPcs::CHandle* m_handles[0x28];
        unsigned char* m_worldObjData;
        unsigned char* m_bubbleData;
        unsigned char* m_frameData;
        WmFrameInfo* m_frameInfo;
        WmCharaModelInfo* m_charaModelData;
        WmCharaSelectEntry* m_charaSelectData;
    };

    unsigned char m_pad04[0x14 - 0x04];
    unsigned char m_mcRequestLocked;
    unsigned char m_pad15[0x18 - 0x15];
    signed char m_mcRequest;
    unsigned char m_pad19[0x20 - 0x19];
    McCtrl m_mcCtrl;
    BattleHudState m_battleHud;
    int m_manaWaterTimerA;
    unsigned char m_pad74[0x80 - 0x74];
    unsigned char m_effectTimer;
    unsigned char m_pad81[0x84 - 0x81];
    int m_crystalElem;
    short m_crystalPart;
    short m_crystalAttr;
    unsigned char m_bonusAlpha;
    unsigned char m_bonusCursorFlag;
    signed char m_optionIndex;
    signed char m_gameInitMode;
    signed char m_stereoMode;
    signed char m_bgmVolume;
    signed char m_seVolume;
    signed char m_leftHintTimer;
    signed char m_rightHintTimer;
    unsigned char m_pad95[0x98 - 0x95];
    float m_optionOpenAnim;
    signed char m_optionMenuState;
    unsigned char m_pad9D[0xA0 - 0x9D];
    float m_optionRowAnim;
    signed char m_optionAnimPhase;
    unsigned char m_padA5[0xA8 - 0xA5];
    float m_optionColumnAnim;
    signed char m_optionAnimCounter;
    unsigned char m_padAD[0xB0 - 0xAD];
    int m_specialModeEdit;
    signed char m_specialModeCursor;
    signed char m_specialModeFlags[4];
    unsigned char m_padB9[0xBC - 0xB9];
    int m_specialModeWorkHead;
    int m_specialModeWork[11];
    CMemory::CStage* m_menuStage;
    CMemory::CStage* m_stageF0;
    CMemory::CStage* m_stageF4;
    CFont* m_fonts[5];
    CMesMenu* m_battleMesMenus[12];
    CRingMenu* m_battleRingMenus[4];
    CTextureSet* m_textureSets[16];
    CTexture* m_textures[105];
    unsigned char m_pad330[0x340 - 0x330];
    unsigned char m_externalFontTlut[0x740 - 0x340];
    int m_mode;
    union {
        BonusStorage m_bonus;
        WmStorage m_wm;
    };
    union {
        ArtiState* m_artiState;
        EquipMenuState* m_equipState;
        MoneyMenuState* m_moneyState;
        MenuLstState* m_menuLstState;
        ItemMenuState* m_itemMenuState;
        SingMenuState* m_singMenuState;
        CompaMenuState* m_compaMenuState;
        TmpArtiState* m_tmpArtiState;
        CmakeMenuState* m_cmakeState;
        short* m_cmdState;
        WmWorldState* m_wmWorldState;
        GoOutMenuState* m_goOutState;
        int m_bonusStatePtr;
    };
    union {
        unsigned char m_pad830[0x838 - 0x830];
        void* m_cmakeVillageWork;
    };
    union {
        EffectEntry* m_effectEntries;
        unsigned char* m_wmCharaState;
    };
    unsigned char* m_wmWorldParams;
    union {
        EffectInfo* m_effectWork;
        int m_bonusListPtr;
    };
    union {
        unsigned char m_pad844[0x848 - 0x844];
        WmCharaAnimState* m_wmCharaAnimState;
    };
    MenuWindowInfo* m_menuWindowInfo;
    union {
        int m_pad84C;
        int m_bonusAnimPtr;
    };
    union {
        ArtiOpenAnimList* m_artiList;
        EquipOpenAnimList* m_equipList;
        MoneyMenuAnimList* m_moneyPanel;
        MenuLstList* m_menuLstList;
        ItemMenuAnimList* m_itemList;
        FavoListStorage* m_favoList;
        CompaOpenAnimList* m_compaList;
        TmpArtiList* m_tmpArtiList;
        short* m_cmdList;
        SingleFadeState* m_singleFadeState;
    };
    unsigned char* m_wmWorkBuffer;
    unsigned char m_wmThpActive;
    signed char m_singleMenuStageActive;
    signed char m_singleMenuInitialized;
    unsigned char m_pad85B[0x85C - 0x85B];
    int m_singleMenuTextureLoadIndex;
    int m_singleMenuTextureLoadState;
    union {
        short m_battleStateFlag;
        short m_cmdLayoutFlag;
        short m_singleMenuMode;
    };
    short m_singleMenuPhase;
    short m_singleCmakeMode;
    short m_singleCmakeSlot;
    short m_menuResultCode;
    union {
        unsigned char m_textureLocIndex;
        unsigned char m_goOutLoadFinished;
    };
    unsigned char m_pad86F;
    union {
        short m_wmTransitionCode;
        signed short m_goOutLoadResult;
    };
    signed char m_singleMenuCtrlResetFlag;
    unsigned char m_pad873;
    int m_singleLifeTimer;
    CShopMenu* m_shopMenu;
    union {
        unsigned char m_pad87C;
        GoOutResetFields m_goOutReset;
    };
    union {
        int m_pad880;
        Mc::SaveDat* m_goOutTransferSaveData;
    };
    union {
        int m_pad884;
        void* m_goOutTransferWork;
    };
    union {
        unsigned char m_cmakeWorkActive;
        unsigned char m_goOutUnknown888;
    };
    union {
        unsigned char m_cmakeWorkCardChannel;
        unsigned char m_goOutSaveLoadMode;
    };
    union {
        unsigned char m_pad88A;
        unsigned char m_goOutUnknown88A;
    };
    union {
        unsigned char m_pad88B;
        unsigned char m_goOutUnknown88B;
    };
    union {
        unsigned char* m_cmakeWork;
        void* m_goOutTransferWorkActive;
    };
    unsigned char m_pad890[0x8A0 - 0x890];
};

extern CMenuPcs MenuPcs;
extern const char* sMenuTextureRegionNameTable[];
extern int sMenuTextureInfoTable[];

STATIC_ASSERT(sizeof(MenuBoardEntry) == 0x50);
STATIC_ASSERT(sizeof(CMenuPcs::BattleHudState) == 0x28);
STATIC_ASSERT(sizeof(MenuWindowInfo) == 0x0C);
STATIC_ASSERT(sizeof(CMenuPcs::EffectInfo) == 0x524);
STATIC_ASSERT(sizeof(CMenuPcs::EffectEntry) == 0x48);
STATIC_ASSERT(sizeof(CMenuPcs::MaterialInfo) == 0x0C);
STATIC_ASSERT(offsetof(CMenuPcs, m_mcCtrl) == 0x20);
STATIC_ASSERT(offsetof(CMenuPcs, m_manaWaterTimerA) == 0x70);
STATIC_ASSERT(offsetof(CMenuPcs, m_effectTimer) == 0x80);
STATIC_ASSERT(offsetof(CMenuPcs, m_crystalElem) == 0x84);
STATIC_ASSERT(offsetof(CMenuPcs, m_crystalPart) == 0x88);
STATIC_ASSERT(offsetof(CMenuPcs, m_crystalAttr) == 0x8A);
STATIC_ASSERT(offsetof(CMenuPcs, m_battleHud) == 0x48);
STATIC_ASSERT(offsetof(CMenuPcs, m_optionIndex) == 0x8E);
STATIC_ASSERT(offsetof(CMenuPcs, m_bonusAlpha) == 0x8C);
STATIC_ASSERT(offsetof(CMenuPcs, m_bonusCursorFlag) == 0x8D);
STATIC_ASSERT(offsetof(CMenuPcs, m_optionOpenAnim) == 0x98);
STATIC_ASSERT(offsetof(CMenuPcs, m_optionRowAnim) == 0xA0);
STATIC_ASSERT(offsetof(CMenuPcs, m_optionColumnAnim) == 0xA8);
STATIC_ASSERT(offsetof(CMenuPcs, m_specialModeFlags) == 0xB5);
STATIC_ASSERT(offsetof(CMenuPcs, m_specialModeWorkHead) == 0xBC);
STATIC_ASSERT(offsetof(CMenuPcs, m_specialModeWork) == 0xC0);
STATIC_ASSERT(offsetof(CMenuPcs, m_fonts) == 0xF8);
STATIC_ASSERT(offsetof(CMenuPcs, m_bonus) == 0x744);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm) == 0x744);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm.m_savedCameraMatrix) == 0x744);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm.m_worldObjData) == 0x814);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm.m_bubbleData) == 0x818);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm.m_frameData) == 0x81C);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm.m_frameInfo) == 0x820);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm.m_charaModelData) == 0x824);
STATIC_ASSERT(offsetof(CMenuPcs, m_wm.m_charaSelectData) == 0x828);
STATIC_ASSERT(offsetof(CMenuPcs, m_moneyState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuLstState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_itemMenuState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_singMenuState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_compaMenuState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_tmpArtiState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmakeState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmdState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_wmWorldState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutState) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_bonusStatePtr) == 0x82C);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmakeVillageWork) == 0x830);
STATIC_ASSERT(offsetof(CMenuPcs, m_wmCharaState) == 0x838);
STATIC_ASSERT(offsetof(CMenuPcs, m_wmWorldParams) == 0x83C);
STATIC_ASSERT(offsetof(CMenuPcs, m_effectWork) == 0x840);
STATIC_ASSERT(offsetof(CMenuPcs, m_bonusListPtr) == 0x840);
STATIC_ASSERT(offsetof(CMenuPcs, m_wmCharaAnimState) == 0x844);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuWindowInfo) == 0x848);
STATIC_ASSERT(offsetof(CMenuPcs, m_bonusAnimPtr) == 0x84C);
STATIC_ASSERT(offsetof(CMenuPcs, m_moneyPanel) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuLstList) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_itemList) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_favoList) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_compaList) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_tmpArtiList) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmdList) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleFadeState) == 0x850);
STATIC_ASSERT(offsetof(CMenuPcs, m_wmWorkBuffer) == 0x854);
STATIC_ASSERT(offsetof(CMenuPcs, m_wmThpActive) == 0x858);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmdLayoutFlag) == 0x864);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuMode) == 0x864);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuPhase) == 0x866);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleCmakeMode) == 0x868);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleCmakeSlot) == 0x86A);
STATIC_ASSERT(offsetof(CMenuPcs, m_menuResultCode) == 0x86C);
STATIC_ASSERT(offsetof(CMenuPcs, m_textureLocIndex) == 0x86E);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutLoadFinished) == 0x86E);
STATIC_ASSERT(offsetof(CMenuPcs, m_wmTransitionCode) == 0x870);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutLoadResult) == 0x870);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleMenuCtrlResetFlag) == 0x872);
STATIC_ASSERT(offsetof(CMenuPcs, m_singleLifeTimer) == 0x874);
STATIC_ASSERT(offsetof(CMenuPcs, m_shopMenu) == 0x878);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutReset) == 0x87C);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutReset.m_resetFlag) == 0x87C);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutTransferSaveData) == 0x880);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutTransferWork) == 0x884);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmakeWorkActive) == 0x888);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutUnknown888) == 0x888);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmakeWorkCardChannel) == 0x889);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutSaveLoadMode) == 0x889);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutUnknown88A) == 0x88A);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutUnknown88B) == 0x88B);
STATIC_ASSERT(offsetof(CMenuPcs, m_cmakeWork) == 0x88C);
STATIC_ASSERT(offsetof(CMenuPcs, m_goOutTransferWorkActive) == 0x88C);
STATIC_ASSERT(sizeof(SingleFadeEntry) == 0x40);
STATIC_ASSERT(offsetof(SingleFadeEntry, uvScale) == 0x14);
STATIC_ASSERT(offsetof(SingleFadeEntry, tex) == 0x1C);
STATIC_ASSERT(offsetof(SingleFadeEntry, flags) == 0x2C);
STATIC_ASSERT(offsetof(SingleFadeEntry, dx) == 0x30);
STATIC_ASSERT(offsetof(SingleFadeEntry, targetX) == 0x38);
STATIC_ASSERT(sizeof(SingleFadeState) == 0x1008);
STATIC_ASSERT(sizeof(WmWorldState) == 0x48);
STATIC_ASSERT(offsetof(WmWorldState, m_originalBackupParams) == 0x36);
STATIC_ASSERT(offsetof(WmWorldState, m_backupParams) == 0x3E);
STATIC_ASSERT(sizeof(SingMenuState) == 0x48);
STATIC_ASSERT(offsetof(SingMenuState, initialized) == 0x0B);
STATIC_ASSERT(offsetof(SingMenuState, closeRequested) == 0x0D);
STATIC_ASSERT(offsetof(SingMenuState, stepState) == 0x10);
STATIC_ASSERT(offsetof(SingMenuState, cursorMove) == 0x1E);
STATIC_ASSERT(offsetof(SingMenuState, frame) == 0x22);
STATIC_ASSERT(offsetof(SingMenuState, selectedIndex) == 0x26);
STATIC_ASSERT(offsetof(SingMenuState, result) == 0x2E);
STATIC_ASSERT(offsetof(SingMenuState, uniteState) == 0x30);
STATIC_ASSERT(offsetof(SingMenuState, topIndex) == 0x34);

STATIC_ASSERT(sizeof(CMenuPcs::Sprt) == 0x1C);
STATIC_ASSERT(sizeof(CMenuPcs::WmFrameInfo) == 0x3C);
STATIC_ASSERT(offsetof(CMenuPcs::WmFrameInfo, m_sprites) == 0x4);

#endif // _FFCC_P_MENU_H_
