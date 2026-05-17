#ifndef _FFCC_MENU_TMPARTI_H_
#define _FFCC_MENU_TMPARTI_H_

class CFont;

struct TmpArtiState
{
    char pad_00[0x0B];
    char initialized;
    char pad_0c;
    char closeRequested;
    char pad_0e[0x10];
    short moveDirection;
    char pad_20[0x02];
    short frame;
    char pad_24[0x02];
    short unk_26;
    char pad_28[0x08];
    short prevSelection;
    short selection;
};

struct TmpArtiEntry
{
    short x;
    short y;
    short width;
    short height;
    float s;
    float t;
    float alpha;
    float z;
    int unk_18;
    int tex;
    int timer;
    int startFrame;
    int duration;
    char pad_2c[0x14];
};

struct TmpArtiList
{
    short count;
    short pad_02;
    int pad_04;
    TmpArtiEntry entries[64];
};

class CMenuPcs
{
public:
    unsigned int TmpArtiOpen();
    void TmpArtiCtrl();
    unsigned int TmpArtiClose();
    void TmpArtiDraw();

    char pad_0000[0x108];
    CFont* m_tmpArtiFont;
    char pad_010C[0x720];
    TmpArtiState* m_tmpArtiState;
    char pad_0830[0x20];
    TmpArtiList* m_tmpArtiList;
};

#endif // _FFCC_MENU_TMPARTI_H_
