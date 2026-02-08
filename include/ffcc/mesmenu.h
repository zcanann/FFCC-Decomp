#ifndef _FFCC_MESMENU_H_
#define _FFCC_MESMENU_H_

class _GXColor;

class CMesMenu
{
public:
    CMesMenu();
    ~CMesMenu();

    void Create();
    void Destroy();
    void onCalc();
    void onDraw();
    void CalcHeart();
    void DrawHeart(float, float, float, float);
    void onScriptChanging(char*);
    void onScriptChanged(char*, int);
    void Open(char*, int, int, int, int, int, int);
    void CloseRequest(int);
    void close(int);
    void SetPos(float, float);
};

#endif // _FFCC_MESMENU_H_
