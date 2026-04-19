#ifndef _FFCC_P_FUNNYSHAPE_H_
#define _FFCC_P_FUNNYSHAPE_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/FS_USB_Process.h"

class CDataHeader;

extern "C" void* __ct__14CUSBStreamDataFv(void*);
extern "C" void* __ct__11CFunnyShapeFv(void*);
extern "C" void __ct__22CPtrArray_P9_GXTexObj_Fv(void*);
extern "C" void __ct__29CPtrArray_P15OSFS_TEXTURE_ST_Fv(void*);
extern unsigned int m_table_desc0__14CFunnyShapePcs[];
extern unsigned int m_table_desc1__14CFunnyShapePcs[];
extern unsigned int m_table_desc2__14CFunnyShapePcs[];
extern unsigned int m_table_desc3__14CFunnyShapePcs[];
extern unsigned int m_table__14CFunnyShapePcs[];

class CFunnyShapePcs : public CProcess
{
public:
    CFunnyShapePcs();
    ~CFunnyShapePcs();
	
    void Init();
    void Quit();
    int GetTable(unsigned long);

    void createViewer();
    void destroyViewer();
    void calcViewer();
    void drawViewer();

    void SetDisplay(FS_DISPLAY_STATUS);
    void SetUSBData();
    void USBDataCallback(CDataHeader*);

    CMemory::CStage* m_viewerStage;        // 0x04
    u8 m_viewerState[0x34];                // 0x08
    u8 m_usbStreamDataStorage[0x14];       // 0x3C
    u8 m_funnyShapeStorage[0x6000];        // 0x50
    OSFS_SHAPE_ST m_shape;                 // 0x6050
    void* m_meshData;                      // 0x6060
    void* m_texObjData[0x10];              // 0x6064
    void* m_textureHeaders[0x10];          // 0x60A4
    void* m_textureData[0x10];             // 0x60E4
    s8 m_textureCount;                     // 0x6124
    u8 m_textureCountPad[3];               // 0x6125
    OSFS_ANM_ST m_anm;                     // 0x6128
    FS_DISPLAY_STATUS m_displayCurrent;    // 0x6138
    FS_DISPLAY_STATUS m_displayPending;    // 0x6178
    u32 m_displayTextureEnabled;           // 0x61B8
    u8 m_texturePtrArrayStorage[0x1C];     // 0x61BC
    u8 m_gxTexObjPtrArrayStorage[0x1C];    // 0x61D8
};

extern CFunnyShapePcs FunnyShapePcs;

#endif // _FFCC_P_FUNNYSHAPE_H_
