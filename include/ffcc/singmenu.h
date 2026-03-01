#ifndef _FFCC_PPP_SINGMENU_H_
#define _FFCC_PPP_SINGMENU_H_

class CFont;
class CGraphic;

void CGraphic_GetTempStage();
void CFont_SetFixed(CFont*, int);

class CMenuPcs
{
public:
    class CTmp
	{
	};
    class MaterialInfo
	{
	};

    void createSingleMenu();
    void destroySingleMenu();
    void SingMenuInit();
    void SingMenuEnd();
    void calcSingleMenu();
    void drawSingleMenu();
    void loadTextureAsync(char **, int, int, CTmp*, int, int, int);
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
    void DrawSingleIcon(int, int, int, float, int, float);
    void DrawShadowFont(CFont*, char*, float, float, int, int);
    void DrawNoShadowFont(CFont*, char*, float, float, int, int);
    void GetItemType(int, int);
    void CalcListPos(int, int, int);
    void DrawListPosMark(float, float, float);
    void EquipChk(int);
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
    void GetSmithItem(int);
    void GetRecipeMaterial(int, MaterialInfo*);
    void GetRaceStr(int, char*);
    void DrawSingBar(int, int, int, float);
    void SingSetLetterAttachflg(int);
    void SingGetLetterAttachflg();
    void CalcSingLife();
    void DrawSingLife();
    void SingLifeInit(int);
    void SingLifeResetWait();
    char* GetTribeStr(int);
    char* GetJobStr(int);
    char* GetHairStr(int);
    char* GetMenuStr(int);
    char* GetAttrStr(int);
    unsigned char GetItemIcon(int);
};

#endif // _FFCC_PPP_SINGMENU_H_
