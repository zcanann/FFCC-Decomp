#ifndef _FFCC_PPP_USBSTREAMDATA_H_
#define _FFCC_PPP_USBSTREAMDATA_H_

#include "ffcc/memory.h"

class CUSBStreamData
{
public:
    CUSBStreamData();
    ~CUSBStreamData();

    void CreateBuffer();
    void DeleteBuffer();
    bool IsUSBStreamDataDone();
    void SetUSBStreamDataDone();

    unsigned char* m_data;             // 0x0
    int m_headerReady;                 // 0x4
    int m_dataReady;                   // 0x8
    unsigned int m_sizeBytes;          // 0xc
    unsigned int m_packetCode;         // 0x10
    CMemory::CStage m_stageDefault;    // 0x14
    CMemory::CStage m_stageLoad;       // 0x18
    CMemory::CStage m_stageAmem;       // 0x1c
    CMemory::CStage m_stageExtra;      // 0x20
    void* m_freePtr;                   // 0x24
    unsigned char m_fieldLoadReq;      // 0x28
    unsigned char m_printFreeOnNext;   // 0x29
    unsigned char m_blockOnFrame;      // 0x2a
    unsigned char m_miruraEventActive; // 0x2b
    unsigned char m_disableShokiDraw;  // 0x2c
};

#endif // _FFCC_PPP_USBSTREAMDATA_H_
