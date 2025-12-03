#ifndef _FFCC_PPP_USBSTREAMDATA_H_
#define _FFCC_PPP_USBSTREAMDATA_H_

class CUSBStreamData
{
public:
    CUSBStreamData();
    ~CUSBStreamData();

    void CreateBuffer();
    void DeleteBuffer();
    void SendMayamikaMessage();
    void IsUSBStreamDataDone();
    void SetUSBStreamDataDone();
};

#endif // _FFCC_PPP_USBSTREAMDATA_H_
