#ifndef _FFCC_P_FUNNYSHAPE_H_
#define _FFCC_P_FUNNYSHAPE_H_

#include "ffcc/memory.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/p_usb.h"
#include "ffcc/ptrarray_decl.h"
#include "ffcc/system.h"
#include "ffcc/FS_USB_Process.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct _GXTexObj;

struct CFunnyShapeViewerState {
    GXColor m_colors[4];
    Vec m_positions[3];
};

class CFunnyShapePcs : public CProcess
{
public:
    static CProcessCallbackTable m_table;

    /*
     * --INFO--
     * PAL Address: TODO
     * PAL Size: TODO
     * EN Address: 0x8005BF64
     * EN Size: 96b
     * JP Address: TODO
     * JP Size: TODO
     */
    CFunnyShapePcs() {}

    /*
     * --INFO--
     * PAL Address: 0x8004E964
     * PAL Size: 136b
     * EN Address: 0x8005BEDC
     * EN Size: 136b
     * JP Address: TODO
     * JP Size: TODO
     */
    ~CFunnyShapePcs() {}

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void createViewer();
    void destroyViewer();
    void calcViewer();
    void drawViewer();

    void SetUSBData();
    void USBDataCallback(CUSBPcs::CDataHeader*);

    CMemory::CStage* m_viewerStage;        // 0x04
    CFunnyShapeViewerState m_viewerState;  // 0x08
    CUSBStreamData m_usbStreamData;        // 0x3C
    CFunnyShape m_funnyShape;              // 0x50
    FS_DISPLAY_STATUS m_displayPending;    // 0x6178
    u32 m_displayTextureEnabled;           // 0x61B8
    CPtrArray<OSFS_TEXTURE_ST*> m_textureHeaders; // 0x61BC
    CPtrArray<_GXTexObj*> m_textureObjects;       // 0x61D8
};

extern CFunnyShapePcs FunnyShapePcs;

#endif // _FFCC_P_FUNNYSHAPE_H_
