#ifndef _FFCC_P_USB_H_
#define _FFCC_P_USB_H_

#include "ffcc/memory.h"
#include "ffcc/usb.h"
#include "ffcc/system.h"

extern u32 m_table_desc0__7CUSBPcs[];
extern u32 m_table_desc1__7CUSBPcs[];
extern u32 m_table_desc2__7CUSBPcs[];
extern u32 m_table__7CUSBPcs[];

class CUSBPcs : public CProcess
{
public:
    CUSBPcs()
    {
        m_table__7CUSBPcs[1] = m_table_desc0__7CUSBPcs[0];
        m_table__7CUSBPcs[2] = m_table_desc0__7CUSBPcs[1];
        m_table__7CUSBPcs[3] = m_table_desc0__7CUSBPcs[2];
        m_table__7CUSBPcs[4] = m_table_desc1__7CUSBPcs[0];
        m_table__7CUSBPcs[5] = m_table_desc1__7CUSBPcs[1];
        m_table__7CUSBPcs[6] = m_table_desc1__7CUSBPcs[2];
        m_table__7CUSBPcs[7] = m_table_desc2__7CUSBPcs[0];
        m_table__7CUSBPcs[8] = m_table_desc2__7CUSBPcs[1];
        m_table__7CUSBPcs[9] = m_table_desc2__7CUSBPcs[2];
    }

    void Init();
    void Quit();
    int GetTable(unsigned long);
    void IsBigAlloc(int param_2);
    void create();
    void destroy();
    void func();
    static void messageCallback(unsigned long, void*, MCCChannel);
    void mccReadData();
    int SendDataCode(int code, void* src, int elemSize, int elemCount);

    // void* vtable;               // 0x0
    char m_rootPath[256];          // 0x4-0x103
    int m_unk0x104;                // 0x104
    int m_unk0x108;                // 0x108
    CMemory::CStage* m_bigStage;   // 0x10c
    CMemory::CStage* m_smallStage; // 0x110
};

extern CUSBPcs USBPcs;
extern int s_usbReadPollFrameCounter;
extern char s_usbReadPollInitialized;

#endif
