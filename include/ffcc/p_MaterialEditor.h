#ifndef _FFCC_P_MATERIALEDITOR_H_
#define _FFCC_P_MATERIALEDITOR_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/zlist.h"
#include <Dolphin/mtx.h>

struct Vec;
struct RSDLISTITEM;
struct ZCANMGRP;

extern "C" void* __ct__14CUSBStreamDataFv(void*);
extern "C" void* __ct__5ZLISTFv(void*);
extern "C" CUSBStreamData* __dt__14CUSBStreamDataFv(CUSBStreamData*, short);

extern unsigned int m_table_desc0__18CMaterialEditorPcs[];
extern unsigned int m_table_desc1__18CMaterialEditorPcs[];
extern unsigned int m_table_desc2__18CMaterialEditorPcs[];
extern unsigned int m_table_desc3__18CMaterialEditorPcs[];
extern unsigned char m_table__18CMaterialEditorPcs[];

struct pppFMATRIX {
    float value[3][4];
};

class CMaterialEditorPcs : public CProcess
{
public:
    CMaterialEditorPcs()
    {
        __ct__14CUSBStreamDataFv(reinterpret_cast<unsigned char*>(this) + 0x84);
        __ct__5ZLISTFv(reinterpret_cast<unsigned char*>(this) + 0xC8);
        __ct__5ZLISTFv(reinterpret_cast<unsigned char*>(this) + 0xD8);

        unsigned int* dst = reinterpret_cast<unsigned int*>(m_table__18CMaterialEditorPcs);
        dst[1] = m_table_desc0__18CMaterialEditorPcs[0];
        dst[2] = m_table_desc0__18CMaterialEditorPcs[1];
        dst[3] = m_table_desc0__18CMaterialEditorPcs[2];
        dst[4] = m_table_desc1__18CMaterialEditorPcs[0];
        dst[5] = m_table_desc1__18CMaterialEditorPcs[1];
        dst[6] = m_table_desc1__18CMaterialEditorPcs[2];
        dst[7] = m_table_desc2__18CMaterialEditorPcs[0];
        dst[8] = m_table_desc2__18CMaterialEditorPcs[1];
        dst[9] = m_table_desc2__18CMaterialEditorPcs[2];
        dst[12] = m_table_desc3__18CMaterialEditorPcs[0];
        dst[13] = m_table_desc3__18CMaterialEditorPcs[1];
        dst[14] = m_table_desc3__18CMaterialEditorPcs[2];
    }
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
    void SetUSBData();
    void ResetRsdList(ZLIST*);
    void DeleteRsdItem(RSDLISTITEM*);
    void DeleteColAnmData(ZCANMGRP**, int);
    int AddRsdList(ZLIST*);
    int SetRsdFlag();
    void GetRsdItemR();
    int SetRsdIndex();
    void GetRsdItem();

    CUSBStreamData* UsbStream() { return reinterpret_cast<CUSBStreamData*>(reinterpret_cast<unsigned char*>(this) + 0x84); }
    const CUSBStreamData* UsbStream() const
    {
        return reinterpret_cast<const CUSBStreamData*>(reinterpret_cast<const unsigned char*>(this) + 0x84);
    }

    CMemory::CStage* m_stage; // 0x04
    unsigned char _pad08[0x7C];
    unsigned char m_usbStream[0x14]; // 0x84

    unsigned char _pad98[0x30];

    unsigned char m_zlist1[0x10]; // 0xC8
    unsigned char m_zlist2[0x10]; // 0xD8

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
};

extern CMaterialEditorPcs MaterialEditorPcs;

#endif // _FFCC_P_MATERIALEDITOR_H_
