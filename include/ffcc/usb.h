#ifndef _FFCC_PPP_USB_H_
#define _FFCC_PPP_USB_H_

enum MCCChannel
{
    Channel0,
    Channel1,
    Channel2,
    Channel3,
    Channel4,
    Channel5,
    Channel6,
    Channel7,
};

typedef void (*MessageCallback)(unsigned long, void*, MCCChannel);

struct CUSBCallbackEntry
{
    int m_inUse;           // 0x0
    void* m_callback;      // 0x4
    void* m_callerContext; // 0x8
};

class CUSB
{
public:
    void Init();
    void Quit();
    void Connect();
    void Disconnect();
    void Frame();
    bool Write(void*, int);
    bool SendMessage(unsigned long, MCCChannel);
    bool IsConnected();
    void AddMessageCallback(MessageCallback, void*);
    void RemoveMessageCallback(MessageCallback);
    void Printf(char*, ...);
    
    void* m_managerStringTable;       // 0x0
    unsigned int m_unk_0x4;           // 0x4
    unsigned int m_unk_0x8;           // 0x8
    unsigned int m_unk_0xc;           // 0xc
    CUSBCallbackEntry m_callbacks[8]; // 0x10
    unsigned int m_unk0x70;           // 0x70
    unsigned int m_connectionState;   // 0x74
    unsigned int m_unk0x78;           // 0x78
    unsigned int m_unk0x7c;           // 0x7c
};

extern CUSB USB;

extern void* PTR_PTR_DAT_801e88a4;

#endif // _FFCC_PPP_USB_H_
