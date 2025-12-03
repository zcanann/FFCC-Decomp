#ifndef _FFCC_PPP_USB_H_
#define _FFCC_PPP_USB_H_

enum MCCChannel;

class CUSB
{
public:
    CUSB();

    void Init();
    void Quit();
    void Connect();
    void Disconnect();
    void Frame();
    void Write(void *, int);
    void SendMessage(unsigned long, MCCChannel);
    void IsConnected();
    void AddMessageCallback(void (*)(unsigned long, void *, MCCChannel), void *);
    void RemoveMessageCallback(void (*)(unsigned long, void *, MCCChannel));
    void Printf(char *, ...);
};

#endif // _FFCC_PPP_USB_H_
