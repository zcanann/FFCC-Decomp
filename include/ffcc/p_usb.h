#ifndef _FFCC_P_USB_H_
#define _FFCC_P_USB_H_

#include "ffcc/usb.h"
#include "ffcc/system.h"

class CUSBPcs : public CProcess
{
public:
    struct CDataHeader
	{
	};

    CUSBPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);

    void IsBigAlloc(int);

    void create();
    void destroy();

    void func();

    void messageCallback(unsigned long, void*, MCCChannel);
    void mccReadData();
    void USBDataCallback(unsigned long, MCCChannel);

    void WriteMessage(CDataHeader*, MCCChannel);
    void SendDataCode(int, void*, int, int);

    void GetPath();
};

#endif
