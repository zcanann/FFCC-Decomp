#ifndef _FFCC_P_MENU_H_
#define _FFCC_P_MENU_H_

struct _GXColor;
class CColor;
class CFontMan;
class CFont;
class CPad;
class CRingMenu;
class CMesMenu;

class McCtrl
{
public:
    McCtrl();
    ~McCtrl();

    void Init();
};

class CMenuPcs
{
public:
    struct CTmp
	{
	};
    enum MENUMODE
	{
		TODO,
	};
    enum FMT
	{
		TODO,
	};
    enum TEX
	{
		TODO,
	};

    CMenuPcs();
    ~CMenuPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);

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

    void GetButtonDown(int);
    void GetButtonRepeat(int);

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
};

#endif // _FFCC_P_MENU_H_
