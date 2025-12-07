#ifndef _FFCC_PPP_SHOPMENU_H_
#define _FFCC_PPP_SHOPMENU_H_

#include <dolphin/gx.h>

class CFont;
class CMaterialSet;
class CCaravanWork;
struct tagOAN3_SHAPE;

void _drawNoShadowFont(CFont*, char*, float, float, int, int);
void _drawShadowFont(CFont*, char*, float, float, int, int);
void getButtonRepeat(int, unsigned short);
void bButtonNoRepeat(unsigned short);
void setOrtho(int, int, float, float, float);
void drawShp(tagOAN3_SHAPE*, CMaterialSet*, unsigned char);
void drawShapeSeq0(int, int, unsigned char, unsigned char);
void drawShapeSeq(int, int, int, int, unsigned char, unsigned char, unsigned char, float, unsigned char);
void drawShapeSeqScale(int, int, int, int, float, float, unsigned char);
void drawShapeSeqGrouad(int, int, int, int, float, float, _GXColor, _GXColor, _GXColor, _GXColor);
void drawGrouadQuad(int, int, int, int, _GXColor, _GXColor, _GXColor, _GXColor);

class CShopMenu
{
public:
    void SetMode(int);
    void getItemCnt();
    void calcGilRatio(int);
    void getItemNo(int);
    void getBuyGil(int);
    void getSellGil(int);
    void getMakeGil(int);
    void getBuySellGil(int);
    void GetItemName(int);
    void GetMaxExchange();
    void GetTotalGil();
    void CanAddGil();
    void CheckSell(int);
    void getItemHaveCnt(int);
    void Init(int);
    void Destroy();
    void Calc();
    void SelectItemIdx();
    void SelectFigure();
    void SelectYesNo();
    void SelectMake();
    void SelectSOUBI();
    void DrawShop0();
    void DrawBuy();
    void DrawSell();
    void DrawSmith0();
    void DrawMake();
    void DrawSoubi();
    void Draw();
    void InitDrawEnvShape();
    void DrawShopBase();
    void DrawMakeBase();
    void DrawSoubiBase();
    void DrawObi(int);
    void DrawItemList();
    void DrawBuySellInfo();
    void DrawItemInfo0();
    void DrawItemInfo(int, int, int, int, int, int, int, int);
    void DrawItemHelp(int, int, int);
    void DrawDec(int, int, int, float, float, int, int, int);
    void DrawDecScale(int, int, int, float, float, float, int, int, int);
    void setFaceAlpha(int, int);
};

#endif // _FFCC_PPP_SHOPMENU_H_
