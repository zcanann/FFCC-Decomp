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
    int IsUSBStreamDataDone();
    void SetUSBStreamDataDone();

    unsigned char* m_data;             // 0x0
    int m_headerReady;                 // 0x4
    int m_dataReady;                   // 0x8
    unsigned int m_sizeBytes;          // 0xc
    int m_packetCode;                  // 0x10
};

struct CUSBStreamDataState
{
    CMemory::CStage* m_stageDefault;   // 0x00
    CMemory::CStage* m_stageLoad;      // 0x04
    CMemory::CStage* m_stageAmem;      // 0x08
    CMemory::CStage* m_stageExtra;     // 0x0C
    void* m_freePtr;                   // 0x10
    unsigned char m_fieldLoadReq;      // 0x14
    unsigned char m_printFreeOnNext;   // 0x15
    unsigned char m_blockOnFrame;      // 0x16
    unsigned char m_miruraEventActive; // 0x17
    unsigned char m_disableShokiDraw;  // 0x18
};

#endif // _FFCC_PPP_USBSTREAMDATA_H_
