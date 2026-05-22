#ifndef _FFCC_MENU_ITEM_H_
#define _FFCC_MENU_ITEM_H_

class CFont;
struct ItemMenuAnimList;
struct _GXColor;

struct ItemMenuState
{
    char pad_00[0x09];
    char optionFlags;
    char pad_0a;
    char initialized;
    char pad_0c;
    char closeRequested;
    char pad_0e[0x2];
    short listState;
    short optionFrame;
    short optionIndex;
    char pad_16[0x8];
    short cursorMove;
    char pad_20[0x2];
    short frame;
    char pad_24[0x2];
    short selectedIndex;
    short subMenuIndex;
    char pad_2a[0x6];
    short mode;
    short prevMode;
    short scroll;
};

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

    void SetAttrFmt(FMT);
    void SetTexture(TEX);
    void DrawInit();
    void DrawRect(unsigned long, float, float, float, float, float, float, float, float, float);
    void DrawRect(unsigned long, float, float, float, float, float, float, _GXColor*, float, float, float);
    void DrawSingleIcon(int, int, int, float, int, float);
    double CalcListPos(int, int, int);
    void DrawListPosMark(float, float, float);
    void DrawSingWin(short);
    void DrawSingWinMess(int, int, int);
    int SingWinMessHeight();
    void DrawCursor(int, int, float);
    void DrawSingLife();
    void DrawHelpMessage(int, CFont*, int, int, _GXColor, int, float, float);

    void ItemInit();
    void ItemInit1();
    bool ItemOpen();
    int ItemCtrl();
    bool ItemClose();
    void ItemDraw();
    int ItemCtrlCur();
    void SingLifeInit(int);
    int SingGetLetterAttachflg();
    void LetterSetAttachItem(unsigned int, int);
    int EquipChk(int);
    int GetItemType(int, int);
    void GetSingWinSize(int, short*, short*, int);
    void SetSingWinInfo(int, int, int, int);
    void DrawEquipMark(int, int, float);

    char pad_00[0xF8];
    CFont* helpFont;
    char pad_fc[0xC];
    CFont* listFont;
    char pad_10c[0x720];
    ItemMenuState* itemMenuState;
    char pad_830[0x18];
    short* singWindowInfo;
    int unk84c;
    ItemMenuAnimList* itemList;
    char pad_854[0x104];
};

extern CMenuPcs MenuPcs;

#endif // _FFCC_MENU_ITEM_H_
