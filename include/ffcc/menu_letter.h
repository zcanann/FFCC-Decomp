#ifndef _FFCC_MENU_LETTER_H_
#define _FFCC_MENU_LETTER_H_

class CFont;

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
    void GetSingWinSize(int, short*, short*, int);
    void SetSingDynamicWinMessInfo(int, char*, char*, char*, char*, char*, char*, char*, char*);
    void SetSingWinScl(float);
    void SetMcWinInfo(int, int);
    void DrawSingleCrescent(float, float);
    void DrawSingleStat(float);
    void DrawSingleHelpWim(float);
    void DrawShadowFont(CFont*, char*, float, float, int, int);
    void DrawSingWin(short);
    void DrawSingWinMess(int, int, int);
    int SingWinMessHeight();
    void SingSetLetterAttachflg(int);
    int SingGetLetterAttachflg();

    void LetterInit();
    void LetterInit0();
    void LetterInit1();
    void LetterInit2();
    void LetterInit3();
    void LetterInit4();
    bool LetterOpen();
    int LetterCtrl();
    bool LetterClose();
    void LetterLstOpen();
    void LetterLstClose();
    void LetterMessOpen();
    int LetterMessClose();
    void LetterItemWinOpen();
    void LetterItemWinClose();
    bool LetterReplyWinOpen();
    void LetterReplyWinClose();
    void LetterAttachWinOpen();
    void LetterAttachWinClose();
    bool LetterConfirmOpen();
    void LetterConfirmClose();
    void LetterDraw();
    void LetterListDraw();
    void LetterMessDraw();
    int LetterCtrlCur();
    void LetterLstBaseDraw(float);
    void LetterSetAttachItem(unsigned int, int);
    char* GetMenuStr(int);
};

#endif // _FFCC_MENU_LETTER_H_
