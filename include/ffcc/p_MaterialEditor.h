#ifndef _FFCC_P_MATERIALEDITOR_H_
#define _FFCC_P_MATERIALEDITOR_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"
#include "ffcc/USBStreamData.h"
#include <Dolphin/mtx.h>

struct Vec;

struct pppFMATRIX {
    float value[3][4];
};

class CMaterialEditorPcs : public CProcess
{
public:
    CMaterialEditorPcs();
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

    CMemory::CStage* m_stage; // 0x04
    CUSBStreamData m_usbStream; // USB stream data for processing
    
    // Additional fields based on Ghidra decomp
    Vec field268_0x15c; // Position vector
    pppFMATRIX m_unkMatrix; // Matrix for transformations
    
    // Fields for matrix data (0x12c - 0x158 range)
    char field_0x12c[4];
    char field_0x130[4]; 
    char field_0x134[4];
    char field_0x138[4];
    char field_0x13c[4];
    char field_0x140[4];
    char field_0x144[4];
    char field_0x148[4];
    char field_0x14c[4];
    char field_0x150[4];
    char field_0x154[4];
    char field_0x158[4];
};

extern __declspec(section ".data") CMaterialEditorPcs MaterialEditorPcs;

#endif // _FFCC_P_MATERIALEDITOR_H_
