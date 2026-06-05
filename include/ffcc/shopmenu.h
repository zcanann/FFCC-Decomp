#ifndef _FFCC_PPP_SHOPMENU_H_
#define _FFCC_PPP_SHOPMENU_H_

#include "ffcc/singmenu.h"

#include <dolphin/gx.h>

class CFont;
class CMaterialSet;
class CCaravanWork;
struct tagOAN3_SHAPE;

void _drawNoShadowFont(CFont*, char*, float, float, int, int);
void _drawShadowFont(CFont*, char*, float, float, int, int);
unsigned short getButtonRepeat(int, unsigned short);
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
    int getItemCnt();
    int calcGilRatio(int);
    int getItemNo(int);
    int getBuyGil(int);
    int getSellGil(int);
    int getMakeGil(int);
    int getBuySellGil(int);
    char* GetItemName(int);
    int GetMaxExchange();
    int GetTotalGil();
    int CanAddGil();
    int CheckSell(int);
    int getItemHaveCnt(int);
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

    void* m_unk00;
    int m_mode;
    int m_nextMode;
    int m_timer;
    int m_subMode;
    int m_listType;
    int m_pdtSlot;
    float m_fade;
    CCaravanWork* m_caravanWork;
    int m_listTop;
    int m_selectedIndex;
    int m_visibleRows;
    int m_canScrollUp;
    int m_canScrollDown;
    int m_figureMode;
    int m_yesNo;
    int m_faceAlpha;
    int m_quantity;
    unsigned char m_topChoice;
    unsigned char m_pad49[3];
    int m_itemCount;
    int m_itemTable[0x40];
    int m_resultItem;
    int m_resultParam;
};

#endif // _FFCC_PPP_SHOPMENU_H_
