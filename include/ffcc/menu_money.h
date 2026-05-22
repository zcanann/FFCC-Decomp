#ifndef _FFCC_MENU_MONEY_H_
#define _FFCC_MENU_MONEY_H_

class CFont;

struct MoneyMenuAnim
{
    short x;
    short y;
    short w;
    short h;
    float u;
    float v;
    float alpha;
    float uvScale;
    int unk18;
    int tex;
    int frame;
    int startFrame;
    int duration;
    unsigned int flags;
    float dx;
    float dy;
    float targetX;
    float targetY;
};

struct MoneyMenuAnimList
{
    short count;
    char pad_02[6];
    MoneyMenuAnim anims[64];
};

struct MoneyMenuState
{
    char pad_00[0x09];
    signed char messageMask;
    char pad_0a;
    char initialized;
    char pad_0c;
    char closeRequested;
    char pad_0e[0x2];
    short listState;
    short optionState;
    short optionIndex;
    char pad_16[0x8];
    short moveDirection;
    char pad_20[0x2];
    short frame;
    char pad_24[0x2];
    short selectedIndex;
    short subMenuIndex;
    char pad_2a[0x6];
    short mode;
    short prevMode;
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

    void DrawInit();
    void SetAttrFmt(FMT);
    void SetTexture(TEX);
    void DrawRect(unsigned long, float, float, float, float, float, float, float, float, float);
    void DrawSingWin(short);
    void DrawSingWinMess(int, int, int);
    int SingWinMessHeight();
    void DrawCursor(int, int, float);
    void GetSingWinSize(int, short*, short*, int);
    void SetSingWinInfo(int, int, int, int);

    bool MoneyOpen();
    int MoneyCtrl();
    int MoneyClose();
    void MoneyDraw();
    int MoneyCtrlCur();
    char* GetMenuStr(int);
    int SingGetLetterAttachflg();
    void LetterSetAttachItem(unsigned int, int);

    char pad_00[0x108];
    CFont* moneyFont;
    char pad_10c[0x720];
    MoneyMenuState* moneyState;
    char pad_830[0x18];
    short* singWindowInfo;
    int unk84c;
    MoneyMenuAnimList* moneyPanel;
    char pad_854[0x104];
};

extern CMenuPcs MenuPcs;

#endif // _FFCC_MENU_MONEY_H_
