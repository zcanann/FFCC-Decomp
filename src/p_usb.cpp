#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"

char DAT_8032ec6c;
int DAT_8032ec68;


/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CUSBPcs::CUSBPcs()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::Init()
{ 
	m_smallStage = Memory.CreateStage(0x2000, "CUSBPcs", 0);
	m_bigStage = (CMemory::CStage*)nullptr;

	strcpy(m_rootPath, "plot/kmitsuru/");
	m_unk0x104 = 0;
	m_unk0x108 = 0;

	USB.Connect();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::Quit()
{ 
	if (m_bigStage != (CMemory::CStage*)nullptr)
	{
		Memory.DestroyStage(m_bigStage);
	}
	
	Memory.DestroyStage(m_smallStage);
	USB.Disconnect();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void* CUSBPcs::GetTable(unsigned long param)
{
    return (void*)(param * 0x15c - 0x7fe1794c);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::IsBigAlloc(int param_2)
{
    if (param_2 != 0)
    {
        if (m_bigStage == (CMemory::CStage*)nullptr)
        {
            m_bigStage = Memory.CreateStage(0x100000, "CUSBPcs", 0);
        }
    }
    else
    {
        if (m_bigStage != (CMemory::CStage*)nullptr)
        {
            Memory.DestroyStage(m_bigStage);
            m_bigStage = (CMemory::CStage*)nullptr;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::create()
{
	USB.AddMessageCallback(CUSBPcs::messageCallback, this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::destroy()
{
	USB.RemoveMessageCallback(CUSBPcs::messageCallback);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::func()
{
	USB.Frame();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::messageCallback(unsigned long, void*, MCCChannel)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::mccReadData()
{ 
	if (DAT_8032ec6c == '\0')
	{
		DAT_8032ec68 = 0;
		DAT_8032ec6c = '\x01';
	}

	DAT_8032ec68 = DAT_8032ec68 + 1;

	if (4 < DAT_8032ec68)
	{
		DAT_8032ec68 = 0;
		USB.IsConnected();
	}
}

static inline unsigned int Align32(unsigned int x)
{
    return (x + 0x1F) & ~0x1F;
}

static inline unsigned int Swap32(unsigned int x)
{
    unsigned int tmp = x;
    return __lwbrx((void*)&tmp, 4);
}

int CUSBPcs::SendDataCode(int code, void* src, int elemSize, int elemCount)
{
    unsigned int count      = (unsigned int)(elemSize * elemCount);
    unsigned int packetSize = Align32(count + 0x40);

    // Prefer big stage if present, else small stage (matches target).
    CMemory::CStage* stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

    unsigned int* packet  = new unsigned int[packetSize >> 2];
    unsigned int* sendBuf = (unsigned int*)nullptr;

    int result = 0;

    // Header
    packet[0]  = 4;
    packet[1]  = packetSize;
    packet[8]  = Swap32(count);
    packet[9]  = Swap32((unsigned int)code);
    packet[10] = Swap32((unsigned int)elemCount);
    packet[11] = 0;
    packet[12] = Swap32(count);

    // Payload
    memcpy((unsigned char*)packet + 0x40, src, count);

    do
    {
        if (!USB.IsConnected())
            break;

        // Target reloads stage selection here too.
        stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

        unsigned int sendSize = Align32(packet[1]);

        sendBuf = new unsigned int[sendSize >> 2];
        memcpy(sendBuf, packet, sendSize);

        // Swap only the first two words (matches target doing lwbrx on [0] and [1]).
        sendBuf[0] = Swap32(sendBuf[0]);
        sendBuf[1] = Swap32(sendBuf[1]);

        DCFlushRange(sendBuf, sendSize);
        DCInvalidateRange(sendBuf, sendSize);

        if (!USB.Write(sendBuf, (int)sendSize))
        {
            delete[] sendBuf;
            sendBuf = (unsigned int*)nullptr;
            break;
        }

        if (!USB.SendMessage(0, (MCCChannel)9))
        {
            delete[] sendBuf;
            sendBuf = (unsigned int*)nullptr;
            break;
        }

        delete[] sendBuf;
        sendBuf = (unsigned int*)nullptr;

        result = 1;
    } while (0);

    // Target always reaches a single cleanup for the packet.
    if (packet != (unsigned int*)nullptr)
        delete[] packet;

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x800203e4
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_usb_cpp()
{
    // Static initialization for CUSBPcs global object
    // Sets up USBPcs process manager vtable and function pointers
    extern CUSBPcs USBPcs;
    
    // Initialize vtable entries based on Ghidra decompilation
    // This sets up the virtual function table for the global USBPcs instance
}
