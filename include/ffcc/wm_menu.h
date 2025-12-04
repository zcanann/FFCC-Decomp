#ifndef _FFCC_PPP_WM_MENU_H_
#define _FFCC_PPP_WM_MENU_H_

#include "ffcc/memorycard.h"

class CFont;
class CGraphic;
class CCameraPcs;

struct McListInfo
{
    void operator=(const McListInfo &);
};

class McCtrl
{
public:
    McCtrl();
    ~McCtrl();

    void Init();
    void LoadMcList();
    void SetListDat(int, int);
    void SetBrokenFile(int);
    void SaveDat();
    void LoadDat();
    void Format(int);
    void ChkEmpty(int);
    void ChkConnect(int);
    void ChkNowData();
    void SaveDataBuffer(char *);
    void ChkParty(char *);
    void EraseDat();
    void GetDno();
    void GetSerial();
    void SetDataBuff(char *);
    void GetSlot();
    void SetDno(int);
    void SetSlot(int);
};


class CMenuPcs
{
public:
    struct Sprt
    {
        void operator=(const Sprt &);
    };

    struct SPL;
    struct FCV;
    struct EffectInfo
    {
        EffectInfo();
    };

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
    void IsMenuCharaAnimIdle(int);
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
    void CalcSpl(SPL *, SPL *, float);
    void GetFcvValue(FCV, float);
    void SetProjection(int);
    void RestoreProjection();
    void DrawObj(int);
    void CalcPitcher();
    void CalcFukidashi();
    void DrawFukidashi();
    void ChkPlaceLength(char *);
    void SplitPlace(const char *, char *, char *);
    void SplitPlace2(const char *, char *, char *, CFont *, int);
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
    void GetMcAccessPos(int *, int *);
    void GetMcOdekakePos(int *, int *);
    void ChkMcDataCnt();
    void DrawMCList();
    void DrawHelpBase(int, float);
    void CalcMcObj();
    void DrawMcObj();
    void SetMcList(int, struct McListInfo *);
    void ClrMcList();
    void BindEffect(int, int, int);
    void SetLight(int);
    void DrawPageMark();
    void DrawRect2(unsigned long, float, float, float, float, float, float, float, float, float (*)[4]);
    void DrawRect3d(unsigned long, float, float, float, float, float, float, float, float, float);
    void SetMcWinInfo(int, int);
    void DrawMcWin(short, short);
    void DrawMcWinMess(int, int);
    void GetWinSize(int, short *, short *, int);
    void SetTextureLoc(int);
    void GetMaxAnimWait();
    void BindMcObj();
    void DrawFilter(unsigned char, unsigned char, unsigned char, unsigned char);
    void CopyNowCaravanDat(Mc::SaveDat *);
    void SetCaravanWork(Mc::SaveDat *);
    void GetSameCharaData(Mc::SaveDat *, Mc::SaveDat *, int, int);
    void CheckSameMcFormatID(Mc::SaveDat *, Mc::SaveDat *);
    void IsAsyncCharaLoadFinish();
    void AlphaNormal();
    void AlphaAdd();
    void GetFontWorld();
};

#endif // _FFCC_PPP_WM_MENU_H_
