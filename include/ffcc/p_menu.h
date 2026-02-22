#ifndef _FFCC_P_MENU_H_
#define _FFCC_P_MENU_H_

#include "ffcc/memorycard.h"
#include "ffcc/system.h"

#include <dolphin/gx.h>

class CColor;
class CFontMan;
class CFont;
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
    struct CTmp
	{
	};
    struct Sprt
    {
        void operator=(const Sprt&);
    };
    struct SPL
    {

    };
    struct FCV
    {

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

    CMenuPcs();
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

    void calc();
    void draw();

    void DrawInit();
    void DrawQuit();

    void SetAttrFmt(FMT);
    void SetTexture(TEX);
    void SetColor(CColor&);

    void GetButtonDown(int);
    void GetButtonRepeat(int);

    void onScriptChanging(char*);
    void onMapChanging(int, int);
    void onMapChanged(int, int, int);

    void DrawRect(unsigned long, float, float, float, float,
                  float, float, float, float, float);

    void DrawRect(unsigned long, float, float, float, float,
                  float, float, _GXColor*, float, float, float);

    void DrawBar(float, float, float, TEX, float);
    void DrawWindow(float, float, float, float, TEX, float);

    void LoadExtraFont(int, char*);
    void SetExtraFontTlut(int, _GXColor);

    void drawPause();

    void createBattle();
    void destroyBattle();
    void calcBattle();
    void drawBattle();

    void ChgPlayModeFromScript(bool);

    void GetTexture(TEX);

    void WmInit();
    void createWorld();
    void ChkNumItemAll();
    void loadData();
    void InitFrameInfo();
    void InitFrame0Info();
    void InitCharaInfo();
    void InitCharaSelectInfo();
    void InitCSelCurPos();
    void destroyWorld();
    void calcWorld();
    void CalcMainMenu();
    void CalcDiaryMenu();
    void CalcMCardMenu();
    void CalcCMakeMenu();
    void CalcMoveMenu();
    void InitSaveLoadMenu();
    void CalcLoadMenu();
    void CalcTitleMenu();
    void CalcGoOutCharaSelect(unsigned char);
    void CalcGoOutSelChar(unsigned char, unsigned char);
    void CalcGoOutSelCharInit();
    void SetMenuCharaAnim(int, int);
    unsigned int IsMenuCharaAnimIdle(int);
    void drawWorld();
    void DrawMainMenu();
    void DrawDiaryMenu();
    void DrawMCardMenu();
    void DrawCMakeMenu();
    void DrawMoveMenu();
    void DrawLoadMenu();
    void DrawTitleMenu();
    void SetWorldParam(int, int);
    void GetWorldParam(int);
    void CallWorldParam(int, int, int);
    void CalcSpl(SPL*, SPL*, float);
    void GetFcvValue(FCV, float);
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
    void GetModelNo(int, int, int);
    void CalcCharaSelect();
    void DrawCharaName();
    void DrawCMLife();
    void WMSubMenuInit();
    void WMChgMenu();
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
    void BindEffect(int, int, int);
    void SetLight(int);
    void DrawPageMark();
    void DrawRect2(unsigned long, float, float, float, float, float, float, float, float, float (*)[4]);
    void DrawRect3d(unsigned long, float, float, float, float, float, float, float, float, float);
    void SetMcWinInfo(int, int);
    void DrawMcWin(short, short);
    void DrawMcWinMess(int, int);
    void GetWinSize(int, short*, short*, int);
    void SetTextureLoc(int);
    void GetMaxAnimWait();
    void BindMcObj();
    void DrawFilter(unsigned char, unsigned char, unsigned char, unsigned char);
    CFont* GetFont22();
    void CopyNowCaravanDat(Mc::SaveDat*);
    void SetCaravanWork(Mc::SaveDat*);
    void GetSameCharaData(Mc::SaveDat*, Mc::SaveDat*, int, int);
    void CheckSameMcFormatID(Mc::SaveDat*, Mc::SaveDat*);
    void IsAsyncCharaLoadFinish();
    void AlphaNormal();
    void AlphaAdd();
    void GetFontWorld();
};


#endif // _FFCC_P_MENU_H_
