#ifndef _FFCC_P_MENU_H_
#define _FFCC_P_MENU_H_

#include "ffcc/memory.h"
#include "ffcc/memorycard.h"
#include "ffcc/system.h"

#include <dolphin/gx.h>

class CColor;
class CFontMan;
class CFont;
class CPad;
class CRingMenu;
class CMesMenu;

extern unsigned int m_table_desc0__8CMenuPcs[];
extern unsigned int m_table_desc1__8CMenuPcs[];
extern unsigned int m_table_desc2__8CMenuPcs[];
extern unsigned int m_table_desc3__8CMenuPcs[];
extern unsigned int m_table_desc4__8CMenuPcs[];
extern unsigned int m_table_desc5__8CMenuPcs[];
extern unsigned int m_table__8CMenuPcs[];

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

    CMenuPcs()
    {
        unsigned int* mcCtrl = reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x20);
        unsigned int* table = m_table__8CMenuPcs;

        mcCtrl[0] = 0;
        mcCtrl[1] = 0;
        mcCtrl[2] = 0;
        mcCtrl[3] = 0;
        mcCtrl[4] = 0;
        mcCtrl[5] = 0;
        mcCtrl[6] = 0;
        mcCtrl[7] = 0;

        table[1] = m_table_desc0__8CMenuPcs[0];
        table[2] = m_table_desc0__8CMenuPcs[1];
        table[3] = m_table_desc0__8CMenuPcs[2];
        table[4] = m_table_desc1__8CMenuPcs[0];
        table[5] = m_table_desc1__8CMenuPcs[1];
        table[6] = m_table_desc1__8CMenuPcs[2];
        table[7] = m_table_desc2__8CMenuPcs[0];
        table[8] = m_table_desc2__8CMenuPcs[1];
        table[9] = m_table_desc2__8CMenuPcs[2];
        table[12] = m_table_desc3__8CMenuPcs[0];
        table[13] = m_table_desc3__8CMenuPcs[1];
        table[14] = m_table_desc3__8CMenuPcs[2];
        table[17] = m_table_desc4__8CMenuPcs[0];
        table[18] = m_table_desc4__8CMenuPcs[1];
        table[19] = m_table_desc4__8CMenuPcs[2];
        table[22] = m_table_desc5__8CMenuPcs[0];
        table[23] = m_table_desc5__8CMenuPcs[1];
        table[24] = m_table_desc5__8CMenuPcs[2];
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
    int GetModelNo(int, int, int);
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
    unsigned int BindEffect(int, int, int);
    void SetLight(int);
    void DrawPageMark();
    void DrawRect2(unsigned long, float, float, float, float, float, float, float, float, float (*)[4]);
    void DrawRect3d(unsigned long, float, float, float, float, float, float, float, float, float);
    void SetMcWinInfo(int, int);
    void DrawMcWin(short, short);
    void DrawMcWinMess(int, int);
    void GetWinSize(int, short*, short*, int);
    void SetTextureLoc(int);
    float GetMaxAnimWait();
    void BindMcObj();
    void DrawFilter(unsigned char, unsigned char, unsigned char, unsigned char);
    CFont* GetFont22();
    void CopyNowCaravanDat(Mc::SaveDat*);
    void SetCaravanWork(Mc::SaveDat*);
    void GetSameCharaData(Mc::SaveDat*, Mc::SaveDat*, int, int);
    int CheckSameMcFormatID(Mc::SaveDat*, Mc::SaveDat*);
    void IsAsyncCharaLoadFinish();
    void AlphaNormal();
    void AlphaAdd();
    void GetFontWorld();

    unsigned char m_pad04[0xEC - 0x04];
    CMemory::CStage* m_menuStage;
    CMemory::CStage* m_stageF0;
    CMemory::CStage* m_stageF4;
    CFont* m_fonts[5];
    unsigned char m_pad10C[0x8A0 - 0x10C];
};

extern CMenuPcs MenuPcs;
extern const char* sMenuTextureRegionNameTable[];
extern int sMenuTextureInfoTable[];

#endif // _FFCC_P_MENU_H_
