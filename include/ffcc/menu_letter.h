#ifndef _FFCC_MENU_LETTER_H_
#define _FFCC_MENU_LETTER_H_

class CMenuPcs
{
public:
    void LetterInit();
    void LetterInit0();
    void LetterInit1();
    void LetterInit2();
    void LetterInit3();
    void LetterInit4();
    void LetterOpen();
    void LetterCtrl();
    void LetterClose();
    void LetterLstOpen();
    void LetterLstClose();
    void LetterMessOpen();
    void LetterMessClose();
    void LetterItemWinOpen();
    void LetterItemWinClose();
    void LetterReplyWinOpen();
    void LetterReplyWinClose();
    void LetterAttachWinOpen();
    void LetterAttachWinClose();
    void LetterConfirmOpen();
    void LetterConfirmClose();
    void LetterDraw();
    void LetterListDraw();
    void LetterMessDraw();
    void LetterCtrlCur();
    void LetterLstBaseDraw(float);
    void LetterDrawPageMark(int);
    void LetterSetAttachItem(unsigned int, int);
};

#endif // _FFCC_MENU_LETTER_H_
