#ifndef _FFCC_P_MATERIALEDITOR_H_
#define _FFCC_P_MATERIALEDITOR_H_

#include "ffcc/system.h"
#include "ffcc/memory.h"

struct Vec;

class CMaterialEditorPcs : public CProcess
{
public:
    CMaterialEditorPcs();
    ~CMaterialEditorPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);

    void createViewer();
    void destroyViewer();

    void ClearTextureData();

    void calcViewer();
    void drawViewer();

    void CreateBoundaryBox(Vec&, Vec&, long, const Vec*);

    CMemory::CStage* m_stage; // 0x04
};

extern __declspec(section ".data") CMaterialEditorPcs MaterialEditorPcs;

#endif // _FFCC_P_MATERIALEDITOR_H_
