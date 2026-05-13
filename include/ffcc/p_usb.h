#ifndef _FFCC_P_USB_H_
#define _FFCC_P_USB_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "ffcc/usb.h"

extern unsigned int m_table_desc0__7CUSBPcs[];
extern unsigned int m_table_desc1__7CUSBPcs[];
extern unsigned int m_table_desc2__7CUSBPcs[];
extern unsigned int m_table__7CUSBPcs[];

class CUSBPcs : public CProcess
{
public:
    class CDataHeader;

    CUSBPcs()
    {
        unsigned int* table = reinterpret_cast<unsigned int*>(m_table__7CUSBPcs);
        const unsigned int* desc0 = m_table_desc0__7CUSBPcs;
        const unsigned int* desc1 = m_table_desc1__7CUSBPcs;
        const unsigned int* desc2 = m_table_desc2__7CUSBPcs;

        table[1] = desc0[0];
        table[2] = desc0[1];
        table[3] = desc0[2];
        table[4] = desc1[0];
        table[5] = desc1[1];
        table[6] = desc1[2];
        table[7] = desc2[0];
        table[8] = desc2[1];
        table[9] = desc2[2];
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
