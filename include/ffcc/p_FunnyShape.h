#ifndef _FFCC_P_FUNNYSHAPE_H_
#define _FFCC_P_FUNNYSHAPE_H_

#include "ffcc/memory.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/p_usb.h"
#include "ffcc/system.h"
#include "ffcc/FS_USB_Process.h"

class CFunnyShapePcs : public CProcess
{
public:
    static unsigned int m_table_desc0[3];
    static unsigned int m_table_desc1[3];
    static unsigned int m_table_desc2[3];
    static unsigned int m_table_desc3[3];
    static unsigned int m_table[0x15C / sizeof(unsigned int)];

    CFunnyShapePcs();
    ~CFunnyShapePcs();
	
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
    u8 m_viewerState[0x34];                // 0x08
    u8 m_usbStreamDataStorage[0x14];       // 0x3C
    CFunnyShape m_funnyShape;              // 0x50
    FS_DISPLAY_STATUS m_displayPending;    // 0x6178
    u32 m_displayTextureEnabled;           // 0x61B8
    u8 m_texturePtrArrayStorage[0x1C];     // 0x61BC
    u8 m_gxTexObjPtrArrayStorage[0x1C];    // 0x61D8
};

#ifdef FFCC_DEFINE_FUNNYSHAPEPCS_STORAGE
extern u8 FunnyShapePcs[sizeof(CFunnyShapePcs)];
#else
extern CFunnyShapePcs FunnyShapePcs;
#endif

#endif // _FFCC_P_FUNNYSHAPE_H_
