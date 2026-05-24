#ifndef _FFCC_P_MENU_H_
#define _FFCC_P_MENU_H_

#include "ffcc/memory.h"
#include "ffcc/memorycard.h"
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

struct McListInfo
{
    void operator=(const McListInfo&);
};

class CMenuPcs : public CProcess
{
public:
    static unsigned int m_table[0x57];

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
    struct Sprt
    {
        void operator=(const Sprt&);
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
        EffectInfo();
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

    CMenuPcs()
    {
        unsigned int* mcCtrl = reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x20);

        mcCtrl[0] = 0;
        mcCtrl[1] = 0;
        mcCtrl[3] = 0;
        mcCtrl[5] = 0;
        mcCtrl[7] = 0;
        mcCtrl[6] = 0;
        mcCtrl[2] = 0;
        mcCtrl[4] = 0;
    }
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
    double CalcListPos(int, int, int);
    void DrawListPosMark(float, float, float);
    float CalcCenteringPos(char*, CFont*);
    void DrawFont(int, int, _GXColor, int, char*, float, float);
    void DrawHelpMessage(int, CFont*, int, int, _GXColor, int, float, float);
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
    void DrawSelectWait();
    void CalcSelectCloseAnim();
    void DrawSelectCloseAnim();

    void DrawBonusCnt(CMenuPcs::Sprt2*, int);
    void DrawBonusFrame(float, float, float, float, float);
    void DrawArtiBase(CMenuPcs::Sprt2*, float);
    void DrawBonusChkMark(float);
    void ArtiBaseInfoInit(CMenuPcs::Sprt2*, CMenuPcs::Sprt2*);

    void GetAllPadOn();
    void ClrBattleItem();

    void ChgPlayModeFromScript(bool);

    CTexture* GetTexture(TEX);

    void WmInit();
    void createWorld();
    void createSingleMenu();
    void destroySingleMenu();
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
    void calcVillageMenu();
    void CalcMainMenu();
    void CalcDiaryMenu();
    void CalcMCardMenu();
    void CalcCMakeMenu();
    void CalcMoveMenu();
    void InitSaveLoadMenu();
    void CalcLoadMenu();
    void CalcTitleMenu();
    void CalcGoOutCharaSelect(unsigned char);
    int CalcGoOutSelChar(unsigned char, unsigned char);
    void CalcGoOutSelCharInit();
    void SetMenuCharaAnim(int, int);
    unsigned int IsMenuCharaAnimIdle(int);
    void drawWorld();
    void drawVillageMenu();
    void DrawMainMenu();
    void DrawDiaryMenu();
    void DrawMCardMenu();
    void DrawCMakeMenu();
    void DrawSingCMake();
    void DrawMoveMenu();
    void DrawLoadMenu();
    void DrawTitleMenu();
    void DrawOptionMenu();
    void SetWorldParam(int, int);
    void GetWorldParam(int);
    void CallWorldParam(int, int, int);
    void CalcSpl(SPL*, SPL*, float);
    double GetFcvValue(FCV, float);
    void SetProjection(int);
    void RestoreProjection();
    void DrawObj(int);
    void CalcPitcher();
    void CalcFukidashi();
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
    int GetItemType(int, int);
    unsigned char GetItemIcon(int);
    void ArtiInit();
    void ArtiInit1();
    int ArtiOpen();
    int ArtiCtrl();
    int ArtiClose();
    void ArtiDraw();
    int ArtiCtrlCur();
    void SetParty();
    void SetCMakeEnd(int);
    void ClrCMakeFlg(int);
    void ChgAllModel();
    void ChgAllModel2();
    void SetMakeChara(int);
    void ChgModel(int, int, int, int);
    void SetAnim(int);
    void DrawCursor(int, int, float);
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
    const char* const* GetMcWinMessBuff(int);
    int GetWinMess(int);
    int GetYesNoXPos(int);
    void SetTextureLoc(int);
    float GetMaxAnimWait();
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

    unsigned char m_pad04[0x48 - 0x04];
    BattleHudState m_battleHud;
    unsigned char m_pad70[0xEC - 0x70];
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
    unsigned char m_pad744[0x82C - 0x744];
    short* m_artiState;
    unsigned char m_pad830[0x850 - 0x830];
    short* m_artiList;
    unsigned char m_pad854[0x864 - 0x854];
    unsigned short m_battleStateFlag;
    unsigned char m_pad866[0x8A0 - 0x866];
};

extern "C" void create__8CMenuPcsFv(CMenuPcs*);
extern "C" void destroy__8CMenuPcsFv(CMenuPcs*);
extern "C" void calc__8CMenuPcsFv(CMenuPcs*);
extern "C" void draw__8CMenuPcsFv(CMenuPcs*);
extern "C" void loadTextureAsync__8CMenuPcsFPPciiPQ28CMenuPcs4CTmpiii(CMenuPcs*, char**, int, int, CMenuPcs::CTmp*, int, int, int);
extern "C" void drawSingleMenu__8CMenuPcsFv(CMenuPcs*);

extern CMenuPcs MenuPcs;
extern const char* sMenuTextureRegionNameTable[];
extern int sMenuTextureInfoTable[];

#endif // _FFCC_P_MENU_H_
