#ifndef _FFCC_PPP_SINGMENU_H_
#define _FFCC_PPP_SINGMENU_H_

class CFont;
class CGraphic;

void CGraphic_GetTempStage();
void CFont_SetFixed(CFont*, int);

class CMenuPcs
{
public:
    enum FMT
    {
        TODO_FMT
    };

    enum TEX
    {
        TODO_TEX
    };

    class CTmp
	{
	};
    struct MaterialInfo
	{
        short m_itemNo[3];
        short m_count[3];
	};

    void createSingleMenu();
    void destroySingleMenu();
    void SingMenuInit();
    void CreateShopMenu();
    void CreateSmithMenu();
    void SingMenuEnd();
    void calcSingleMenu();
    void drawSingleMenu();
    void loadTextureAsync(char **, int, int, CTmp*, int, int, int);
    void loadFont(int, char*, int, int);
    void loadTexture(char**, int, int, CTmp*, int, int, int);
    void freeTexture(int, int, int, int);
    void SetAttrFmt(FMT);
    void SetTexture(TEX);
    void DrawInit();
    void DrawRect(unsigned long, float, float, float, float, float, float, float, float, float);
    void SetProjection(int);
    void SetLight(int);
    void RestoreProjection();
    void DrawFilter(unsigned char, unsigned char, unsigned char, unsigned char);
    void SingCalcChara(float);
    void DrawSingleBase(float);
    void DrawSingleStat(float);
    void DrawSingleHelpWim(float);
    void DrawSingleCrescent(float, float);
    void SingleCalcFadeIn();
    void SingleDrawFadeIn();
    void SingleCalcFadeOut();
    void SingleDrawFadeOut();
    void SingleCalcCtrl();
    void SingleDrawCtrl();
    void CmdDraw();
    void ItemDraw();
    void EquipDraw();
    void ArtiDraw();
    void TmpArtiDraw();
    void MoneyDraw();
    void FavoDraw();
    void CompaDraw();
    void LetterDraw();
    void MLstDraw();
    void DrawCursor(int, int, float);
    void DrawSingleIcon(int, int, int, float, int, float);
    void DrawShadowFont(CFont*, char*, float, float, int, int);
    void DrawNoShadowFont(CFont*, char*, float, float, int, int);
    int GetItemType(int, int);
    double CalcListPos(int, int, int);
    void DrawListPosMark(float, float, float);
    int EquipChk(int);
    void DrawEquipMark(int, int, float);
    void DrawSingWin(short);
    void DrawSingWinMess(int, int, int);
    void GetSingWinSize(int, short*, short*, int);
    void SetSingWinInfo(int, int, int, int);
    void SetSingDynamicWinMessInfo(int, char*, char*, char*, char*, char*, char*, char*, char*);
    void SetSingWinScl(float);
    float GetSingWinScl();
    int SingWinMessHeight();
    int ChkEquipPossible(int);
    int GetEquipType(int);
    int GetSmithItem(int);
    void GetRecipeMaterial(int, MaterialInfo*);
    void GetRaceStr(int, char*);
    void DrawSingBar(int, int, int, float);
    void SingSetLetterAttachflg(int);
    int SingGetLetterAttachflg();
    void CalcSingLife();
    void DrawSingLife();
    void SingLifeInit(int);
    void SingLifeResetWait();
    char* GetTribeStr(int);
    char* GetJobStr(int);
    char* GetHairStr(int);
    char* GetMenuStr(int);
    char* GetAttrStr(int);
    int GetModelNo(int, int, int);
    unsigned char GetItemIcon(int);
};

extern CMenuPcs MenuPcs;

#endif // _FFCC_PPP_SINGMENU_H_
