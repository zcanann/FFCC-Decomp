#ifndef _FFCC_P_MATERIALEDITOR_H_
#define _FFCC_P_MATERIALEDITOR_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"
#include "ffcc/pppTypes.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/zlist.h"
#include <Dolphin/mtx.h>
#include <Dolphin/gx.h>

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

struct MaterialEditorPolygon {
    u16 flags;
    u16 blendMode;
    u32 _04;
    u16 index0;
    u16 index1;
    u16 index2;
    u16 index3;
    u16 _10;
    u16 _12;
    u16 _14;
    u16 _16;
    u8 _18;
    char textureMarker;
    u8 _1a[2];
    s16 _1c;
    s16 textureIndex;
    s16 u0;
    s16 v0;
    s16 u1;
    s16 v1;
    s16 u2;
    s16 v2;
    s16 u3;
    s16 v3;
    u8 _30[0x20];
    float texCoord[4][2];
};
typedef int MaterialEditorPolygon_size_mismatch[(sizeof(MaterialEditorPolygon) == 0x70) ? 1 : -1];

struct RSDLISTITEM {
    RSDITEM* rsdItem;
    ZCANMGRP* colAnmData;
    int colAnmCount;
    int flag;
};

class CMaterialEditorPcs : public CProcess
{
public:
    static CProcessTableCallback m_table_desc0;
    static CProcessTableCallback m_table_desc1;
    static CProcessTableCallback m_table_desc2;
    static CProcessTableCallback m_table_desc3;
    static CProcessTable m_table;

    CMaterialEditorPcs() {}
    ~CMaterialEditorPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void createViewer();
    void destroyViewer();

    void ClearTextureData();
    void MemFree(void*);

    void calcViewer();
    void drawViewer();

    void CreateBoundaryBox(Vec&, Vec&, long, const Vec*);
    RSDITEM* GetReadRsd();
    void SetUSBData();
    void ResetRsdList(ZLIST*);
    void DeleteRsdItem(RSDLISTITEM*);
    void DeleteColAnmData(ZCANMGRP**, int);
    int AddRsdList(ZLIST*);
    int SetRsdFlag();
    RSDLISTITEM* GetRsdItemR();
    int SetRsdIndex();
    RSDLISTITEM* GetRsdItem();

    CMemory::CStage* m_stage; // 0x04
    GXColor m_viewerLightColors[4]; // 0x08
    Vec m_viewerLightDirs[3]; // 0x18
    Vec m_viewerSrtPosition; // 0x3C
    Vec m_viewerSrtRotation; // 0x48
    Vec m_viewerSrtScale; // 0x54
    unsigned char _pad60[0x24];
    CUSBStreamData m_usbStream; // 0x84
    unsigned char _padB4[0x8];
    u32 m_rsdIndex; // 0xBC
    int m_rsdFlag; // 0xC0
    int m_rsdListIndex; // 0xC4

    ZLIST m_zlist1; // 0xC8
    ZLIST m_zlist2; // 0xD8

    u32 m_displayTextureEnabled; // 0xE8
    float field_0xec; // 0xEC
    float field_0xf0;
    float field_0xf4;
    float field_0xf8;
    float field_0xfc;
    float field_0x100;
    float field_0x104;
    float field_0x108;
    float field_0x10c;
    float field_0x110;
    float field_0x114;
    float field_0x118;
    float field_0x11c;
    float field_0x120;
    float field_0x124;
    float field_0x128;

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
    float field_0x168; // 0x168
    unsigned char _pad16C[0xA0];
    pppFMATRIX m_unkMatrix; // 0x20C
    GXTexObj* m_texObj[16]; // 0x23C
    s16* m_textureHeader[16]; // 0x27C
    void* m_textureData[16]; // 0x2BC
    void* m_tlutData[16]; // 0x2FC
    GXTlutObj* m_tlutObj0[16]; // 0x33C
    GXTlutObj* m_tlutObj1[16]; // 0x37C
    s8 m_loadedTextureCount; // 0x3BC
    unsigned char _pad3BD[0x3E0 - 0x3BD];
};

extern CMaterialEditorPcs MaterialEditorPcs;

#endif // _FFCC_P_MATERIALEDITOR_H_
