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
};

#endif // _FFCC_PPP_USBSTREAMDATA_H_
