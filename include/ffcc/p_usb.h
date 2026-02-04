#ifndef _FFCC_P_USB_H_
#define _FFCC_P_USB_H_

#include "ffcc/memory.h"
#include "ffcc/usb.h"
#include "ffcc/system.h"

class CUSBPcs : public CProcess
{
public:
    CUSBPcs();

    void Init();
    void Quit();
    void* GetTable(unsigned long);
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

#endif
