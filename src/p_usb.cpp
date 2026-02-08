#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"
#include "types.h"

char DAT_8032ec6c;
int DAT_8032ec68;

extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801E8830;
extern u32 lbl_801E8690[];
extern u32 lbl_801E869C[];
extern u32 lbl_801E86A8[];
extern u32 lbl_801E86B4[];
extern CUSBPcs USBPcs;
void* operator new[](unsigned long, CMemory::CStage*, char*, int);


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
    return (void*)((char*)lbl_801E86B4 + (param * 0x15c));
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

int CUSBPcs::SendDataCode(int code, void* src, int elemSize, int elemCount)
{
    unsigned int count      = (unsigned int)(elemSize * elemCount);
    unsigned int packetSize = Align32(count + 0x40);

    CMemory::CStage* stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

    unsigned int* packet  = new (stage, (char*)"p_usb.cpp", 0x1ca) unsigned int[packetSize >> 2];
    unsigned int* sendBuf = (unsigned int*)nullptr;

    int result = 0;

    packet[1]  = packetSize;
    packet[0]  = 4;
    packet[8]  = (count << 24) | ((count >> 8) & 0xFF) << 16 | ((count >> 16) & 0xFF) << 8 | (count >> 24);
    packet[9]  = ((unsigned int)code << 24) | ((((unsigned int)code >> 8) & 0xFF) << 16) |
                ((((unsigned int)code >> 16) & 0xFF) << 8) | ((unsigned int)code >> 24);
    packet[10] = ((unsigned int)elemCount << 24) | ((((unsigned int)elemCount >> 8) & 0xFF) << 16) |
                ((((unsigned int)elemCount >> 16) & 0xFF) << 8) | ((unsigned int)elemCount >> 24);
    packet[11] = 0;
    packet[12] = (count << 24) | ((count >> 8) & 0xFF) << 16 | ((count >> 16) & 0xFF) << 8 | (count >> 24);

    memcpy((unsigned char*)packet + 0x40, src, count);

    do
    {
        if (!USB.IsConnected())
            break;

        stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

        unsigned int sendSize = Align32(packet[1]);

        sendBuf = new (stage, (char*)"p_usb.cpp", 0x19e) unsigned int[sendSize >> 2];
        memcpy(sendBuf, packet, sendSize);

        unsigned int tmp = packet[0];
        sendBuf[0] = (tmp << 24) | ((tmp >> 8) & 0xFF) << 16 | ((tmp >> 16) & 0xFF) << 8 | (tmp >> 24);

        tmp = packet[1];
        sendBuf[1] = (tmp << 24) | ((tmp >> 8) & 0xFF) << 16 | ((tmp >> 16) & 0xFF) << 8 | (tmp >> 24);

        DCFlushRange(sendBuf, sendSize);
        DCInvalidateRange(sendBuf, sendSize);

        if (!USB.Write(sendBuf, (int)sendSize))
        {
            operator delete(sendBuf);
            sendBuf = (unsigned int*)nullptr;
            break;
        }

        if (!USB.SendMessage(0, (MCCChannel)9))
        {
            operator delete(sendBuf);
            sendBuf = (unsigned int*)nullptr;
            break;
        }

        operator delete(sendBuf);
        sendBuf = (unsigned int*)nullptr;

        result = 1;
    } while (0);

    if (packet != (unsigned int*)nullptr)
        operator delete(packet);

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
    *(void**)&USBPcs = &__vt__8CManager;
    *(void**)&USBPcs = &lbl_801E8668;

    u32 a0 = lbl_801E8690[0];
    u32 a1 = lbl_801E8690[1];
    u32 a2 = lbl_801E8690[2];
    u32 b0 = lbl_801E869C[0];
    u32 b1 = lbl_801E869C[1];
    u32 b2 = lbl_801E869C[2];
    u32 c0 = lbl_801E86A8[0];
    u32 c1 = lbl_801E86A8[1];
    u32 c2 = lbl_801E86A8[2];

    *(void**)&USBPcs = &lbl_801E8830;
    lbl_801E86B4[1] = a0;
    lbl_801E86B4[2] = a1;
    lbl_801E86B4[3] = a2;
    lbl_801E86B4[4] = b0;
    lbl_801E86B4[5] = b1;
    lbl_801E86B4[6] = b2;
    lbl_801E86B4[7] = c0;
    lbl_801E86B4[8] = c1;
    lbl_801E86B4[9] = c2;
}
