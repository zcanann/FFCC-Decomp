#ifndef _FFCC_MENU_TMPARTI_H_
#define _FFCC_MENU_TMPARTI_H_

class CFont;

class CMenuPcs
{
public:
    void TmpArtiInit();
    void TmpArtiInit0();
    unsigned int TmpArtiOpen();
    void TmpArtiCtrl();
    unsigned int TmpArtiClose();
    void TmpArtiDraw();
    void TmpArtiCtrlCur();

    char pad_0000[0x108];
    CFont* m_tmpArtiFont;
    char pad_010C[0x720];
    short* m_tmpArtiState;
    char pad_0830[0x20];
    short* m_tmpArtiList;
};

#endif // _FFCC_MENU_TMPARTI_H_
