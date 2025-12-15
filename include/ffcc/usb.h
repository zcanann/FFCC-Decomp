#ifndef _FFCC_PPP_USB_H_
#define _FFCC_PPP_USB_H_

// TODO: Who owns?
enum MCCChannel
{

};

class CUSB
{
public:
    CUSB();

    void Init();
    void Quit();
    void Connect();
    void Disconnect();
    void Frame();
    bool Write(void*, int);
    bool SendMessage(unsigned long, MCCChannel);
    bool IsConnected();
    void AddMessageCallback(void (*)(unsigned long, void*, MCCChannel), void*);
    void RemoveMessageCallback(void (*)(unsigned long, void*, MCCChannel));
    void Printf(char*, ...);
};

CUSB USB;

#endif // _FFCC_PPP_USB_H_
