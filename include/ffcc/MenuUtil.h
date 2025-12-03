#ifndef _FFCC_MENU_UTIL_H_
#define _FFCC_MENU_UTIL_H_

class CFont;
struct _GXColor;

class CMenuPcs
{
public:
    void CalcHelpLine(int, int&, int&);
    void GetLongHelpString(CFont*, int, int);
    void CalcCenteringPos2(char*, float, float);
    void CalcCenteringPos(char*, CFont*);
    void DrawFont(int, int, _GXColor, int, char*, float, float);
    void GetFontWidth(char*, float, float);
    void DrawFont2(int, int, _GXColor, int, char*, float, float, float);
    void DrawHelpMessageUS(int, CFont*, int, int, _GXColor, int, float, float);
    void DrawHelpMessage(int, CFont*, int, int, _GXColor, int, float, float);
    void IsItemEquip(int);
    void SetCrystalCageAttr();
    void SetManaWaterEffect();
    void GetOptionData();
    void InitOptionMenuParam();
    void CalcOptionMenu();
    void DrawOptionMenu();
    void BindMcObj(int);
};

#endif // _FFCC_MENU_UTIL_H_
