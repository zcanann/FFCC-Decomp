#ifndef _FFCC_P_MATERIALEDITOR_H_
#define _FFCC_P_MATERIALEDITOR_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/zlist.h"
#include <Dolphin/mtx.h>

struct Vec;
struct ZCANMGRP;

struct RSDITEM {
    u32 countA;
    u32 countB;
    u32 countC;
    void* ptrC;
    void* ptr10;
    void* ptr14;
    void* ptr18;
};

struct RSDLISTITEM {
    RSDITEM* rsdItem;
    ZCANMGRP* colAnmData;
    int colAnmCount;
    int flag;
};

extern unsigned int m_table_desc0__18CMaterialEditorPcs[];
extern unsigned int m_table_desc1__18CMaterialEditorPcs[];
extern unsigned int m_table_desc2__18CMaterialEditorPcs[];
extern unsigned int m_table_desc3__18CMaterialEditorPcs[];
extern unsigned int m_table__18CMaterialEditorPcs[];

struct pppFMATRIX {
    float value[3][4];
};

class CMaterialEditorPcs : public CProcess
{
public:
    CMaterialEditorPcs() {}
    ~CMaterialEditorPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void createViewer();
    void destroyViewer();

    void ClearTextureData();

    void calcViewer();
    void drawViewer();

    void CreateBoundaryBox(Vec&, Vec&, long, const Vec*);
#ifndef VERSION_GCCP01
    RSDITEM* GetReadRsd();
#endif
    void SetUSBData();
    void ResetRsdList(ZLIST*);
#ifndef VERSION_GCCP01
    void DeleteRsdItem(RSDLISTITEM*);
    void DeleteColAnmData(ZCANMGRP**, int);
#endif
    int AddRsdList(ZLIST*);
    int SetRsdFlag();
#ifndef VERSION_GCCP01
    RSDLISTITEM* GetRsdItemR();
#endif
    int SetRsdIndex();
    RSDLISTITEM* GetRsdItem();

    CMemory::CStage* m_stage; // 0x04
    unsigned char _pad08[0x7C];
    CUSBStreamData m_usbStream; // 0x84
    unsigned char _padB4[0x14];

    ZLIST m_zlist1; // 0xC8
    ZLIST m_zlist2; // 0xD8

    unsigned char _padE8[0x44];

    // Raw float words consumed by calcViewer (0x12C - 0x158)
    float field_0x12c;
    float field_0x130;
    float field_0x134;
    float field_0x138;
    float field_0x13c;
    float field_0x140;
    float field_0x144;
    float field_0x148;
    float field_0x14c;
    float field_0x150;
    float field_0x154;
    float field_0x158;

    Vec field268_0x15c; // 0x15C
    unsigned char _pad168[0xA4];
    pppFMATRIX m_unkMatrix; // 0x20C
    unsigned char _pad23C[0x3E0 - 0x23C];
};

extern CMaterialEditorPcs MaterialEditorPcs;

#endif // _FFCC_P_MATERIALEDITOR_H_
