#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"
#include "types.h"

int s_usbReadPollFrameCounter;
char s_usbReadPollInitialized;

static const char sUsbPcsClassName[] = "CUSBPcs";

typedef int CUSBDataHeader_size_mismatch[(sizeof(CUSBPcs::CDataHeader) == 0x40) ? 1 : -1];
typedef int CUSBDataHeader_payload_size_offset_mismatch
    [(((u32)&((CUSBPcs::CDataHeader*)0)->m_payloadSize) == 0x20) ? 1 : -1];
typedef int CUSBDataHeader_packet_code_offset_mismatch
    [(((u32)&((CUSBPcs::CDataHeader*)0)->m_packetCode) == 0x24) ? 1 : -1];

extern "C" {
void create__7CUSBPcsFv(CUSBPcs*);
void destroy__7CUSBPcsFv(CUSBPcs*);
void func__7CUSBPcsFv(CUSBPcs*);
}

inline CUSBPcs::CUSBPcs()
{
    static CProcessTableCallback desc0 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__7CUSBPcsFv)};
    static CProcessTableCallback desc1 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CUSBPcsFv)};
    static CProcessTableCallback desc2 = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(func__7CUSBPcsFv)};

    CUSBProcessTable* table = &m_table;

    table->m_fields.m_create = desc0;
    table->m_fields.m_destroy = desc1;
    table->m_fields.m_entries[0].m_callback = desc2;
}

CUSBProcessTable CUSBPcs::m_table = {
    const_cast<char*>(sUsbPcsClassName),
    {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0x12,
        0,
        0,
        0,
        0,
        0,
        0,
    },
};
static const char sUsbManagerClassName[] = "CManager";
static const char sUsbProcessClassName[] = "CProcess";
static const char s_p_usb_cpp[] = "p_usb.cpp";
static const char s_usbRootPath[16] = "plot/kmitsuru/";

CUSBPcs USBPcs;

static inline unsigned int Swap32(unsigned int x)
{
    return __lwbrx((void*)&x, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8001ff6c
 * PAL Size: 532b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUSBPcs::SendDataCode(int code, void* src, int elemSize, int elemCount)
{
    unsigned int count;
    int result;
    int connected;
    CDataHeader* packet;
    CDataHeader* dstBuffer;
    CMemory::CStage* stage;
    unsigned int value;

    count = elemSize * elemCount;
    value = (count + 0x5F) & ~0x1F;
    stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

    packet = reinterpret_cast<CDataHeader*>(new (stage, const_cast<char*>(s_p_usb_cpp), 0x1ca) unsigned char[value]);
    packet->m_packetSize = value;
    packet->m_packetType = 4;
    packet->m_packetCode = Swap32((unsigned int)code);
    packet->m_payloadSize = Swap32(count);
    packet->m_elementCount = Swap32((unsigned int)elemCount);
    packet->m_reserved2C = Swap32(0);
    packet->m_dataSize = Swap32(count);
    memcpy(packet + 1, src, count);

    connected = USB.IsConnected();
    if (connected == 0) {
        result = 0;
    } else {
        stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

        dstBuffer = reinterpret_cast<CDataHeader*>(new (stage, const_cast<char*>(s_p_usb_cpp), 0x19e)
            unsigned char[(packet->m_packetSize + 0x1F) & ~0x1F]);
        memcpy(dstBuffer, packet, (packet->m_packetSize + 0x1F) & ~0x1F);

        dstBuffer->m_packetType = Swap32(packet->m_packetType);
        dstBuffer->m_packetSize = Swap32(packet->m_packetSize);

        DCFlushRange(dstBuffer, (packet->m_packetSize + 0x1F) & ~0x1F);
        DCInvalidateRange(dstBuffer, (packet->m_packetSize + 0x1F) & ~0x1F);

        if (USB.Write(dstBuffer, (packet->m_packetSize + 0x1F) & ~0x1F) == 0) {
            delete[] dstBuffer;
            result = 0;
        } else if (USB.SendMessage(0, (MCCChannel)9) == 0) {
            delete[] dstBuffer;
            result = 0;
        } else {
            delete[] dstBuffer;
            result = 1;
        }
    }

    if (packet != (CDataHeader*)nullptr) {
        delete[] packet;
    }
    return result;
}

/*
 * --INFO--
 * PAL Address: 0x80021db8
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::mccReadData()
{
    if (s_usbReadPollInitialized == '\0') {
        s_usbReadPollFrameCounter = 0;
        s_usbReadPollInitialized = '\x01';
    }

    s_usbReadPollFrameCounter++;
    if (4 < s_usbReadPollFrameCounter) {
        s_usbReadPollFrameCounter = 0;
    } else {
        return;
    }

    if (USB.IsConnected() == 0) {
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80021e24
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::messageCallback(unsigned long, void*, MCCChannel)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80021e28
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::func()
{
	USB.Frame();
}

/*
 * --INFO--
 * PAL Address: 0x80021e50
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::destroy()
{
	USB.RemoveMessageCallback(CUSBPcs::messageCallback);
}

/*
 * --INFO--
 * PAL Address: 0x80021e80
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::create()
{
	USB.AddMessageCallback(CUSBPcs::messageCallback, this);
}

/*
 * --INFO--
 * PAL Address: 0x80021eb4
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::IsBigAlloc(int param_2)
{
    if ((param_2 != 0) && (m_bigStage == (CMemory::CStage*)nullptr)) {
        m_bigStage = Memory.CreateStage(0x100000, const_cast<char*>(sUsbPcsClassName), 0);
    } else if ((param_2 == 0) && (m_bigStage != (CMemory::CStage*)nullptr)) {
        Memory.DestroyStage(m_bigStage);
        m_bigStage = (CMemory::CStage*)nullptr;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80021f38
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CUSBPcs::GetTable(unsigned long param)
{
    return reinterpret_cast<int>(reinterpret_cast<char*>(&m_table) + param * sizeof(CProcessTable));
}

/*
 * --INFO--
 * PAL Address: 0x80021f4c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
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
 * PAL Address: 0x80021fa8
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::Init()
{
    CMemory* memory = &Memory;

	m_smallStage = memory->CreateStage(0x2000, const_cast<char*>(sUsbPcsClassName), 0);
	m_bigStage = (CMemory::CStage*)nullptr;

	strcpy(m_rootPath, s_usbRootPath);
	m_unk0x104 = 0;
	m_unk0x108 = 0;

	USB.Connect();
}
