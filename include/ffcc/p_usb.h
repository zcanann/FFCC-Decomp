#ifndef _FFCC_P_USB_H_
#define _FFCC_P_USB_H_

#include "ffcc/memory.h"
#include "ffcc/p_sample.h"
#include "ffcc/usb.h"

struct CUSBPcsTable
{
    char* m_name;
    unsigned int m_words[0x46];
};

extern unsigned int m_table_desc0__7CUSBPcs[];
extern unsigned int m_table_desc1__7CUSBPcs[];
extern unsigned int m_table_desc2__7CUSBPcs[];
extern CUSBPcsTable m_table__7CUSBPcs;

class CUSBPcs : public CSamplePcs
{
public:
    CUSBPcs()
    {
        unsigned int* table = reinterpret_cast<unsigned int*>(&m_table__7CUSBPcs);

        table[1] = m_table_desc0__7CUSBPcs[0];
        table[2] = m_table_desc0__7CUSBPcs[1];
        table[3] = m_table_desc0__7CUSBPcs[2];
        table[4] = m_table_desc1__7CUSBPcs[0];
        table[5] = m_table_desc1__7CUSBPcs[1];
        table[6] = m_table_desc1__7CUSBPcs[2];
        table[7] = m_table_desc2__7CUSBPcs[0];
        table[8] = m_table_desc2__7CUSBPcs[1];
        table[9] = m_table_desc2__7CUSBPcs[2];
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
