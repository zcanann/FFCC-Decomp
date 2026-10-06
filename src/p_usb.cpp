#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"
#include "types.h"

typedef int CUSBDataHeader_size_mismatch[(sizeof(CUSBPcs::CDataHeader) == 0x40) ? 1 : -1];
typedef int CUSBDataHeader_payload_size_offset_mismatch
    [(((u32)&((CUSBPcs::CDataHeader*)0)->m_payloadSize) == 0x20) ? 1 : -1];
typedef int CUSBDataHeader_packet_code_offset_mismatch
    [(((u32)&((CUSBPcs::CDataHeader*)0)->m_packetCode) == 0x24) ? 1 : -1];

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline CUSBPcs::CUSBPcs()
{
}

CUSBPcs USBPcs;

CProcessCallbackTable CUSBPcs::m_table = {
    "CUSBPcs",
    static_cast<CProcessCallback>(&CUSBPcs::create),
    static_cast<CProcessCallback>(&CUSBPcs::destroy),
    {
        {static_cast<CProcessCallback>(&CUSBPcs::func), 0x12, 0},
    },
};

static inline unsigned int Swap32(unsigned int x)
{
    return __lwbrx((void*)&x, 0);
}

/*
 * --INFO--
 * PAL Address: 0x80020370
 * PAL Size: 116b
 * EN Address: 0x80020164
 * EN Size: 116b
 * JP Address: 0x8001FBC4
 * JP Size: 116b
 */
void CUSBPcs::Init()
{
    CMemory* memory = &Memory;

	m_smallStage = memory->CreateStage(0x2000, "CUSBPcs", 0);
	m_bigStage = (CMemory::CStage*)nullptr;

	strcpy(m_rootPath, "plot/kmitsuru/");
	m_unk0x104 = 0;
	m_unk0x108 = 0;

	USB.Connect();
}

/*
 * --INFO--
 * PAL Address: 0x80020314
 * PAL Size: 92b
 * EN Address: 0x80020108
 * EN Size: 92b
 * JP Address: 0x8001FB68
 * JP Size: 92b
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
 * PAL Address: 0x80020300
 * PAL Size: 20b
 * EN Address: 0x800200F4
 * EN Size: 20b
 * JP Address: 0x8001FB54
 * JP Size: 20b
 */
int CUSBPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&m_table + index);
}

/*
 * --INFO--
 * PAL Address: 0x8002027c
 * PAL Size: 132b
 * EN Address: 0x80020070
 * EN Size: 132b
 * JP Address: 0x8001FAD0
 * JP Size: 132b
 */
void CUSBPcs::IsBigAlloc(int useBigStage)
{
    if ((useBigStage != 0) && (m_bigStage == (CMemory::CStage*)nullptr)) {
        m_bigStage = Memory.CreateStage(0x100000, "CUSBPcs", 0);
    } else if ((useBigStage == 0) && (m_bigStage != (CMemory::CStage*)nullptr)) {
        Memory.DestroyStage(m_bigStage);
        m_bigStage = (CMemory::CStage*)nullptr;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80020248
 * PAL Size: 52b
 * EN Address: 0x8002003C
 * EN Size: 52b
 * JP Address: 0x8001FA9C
 * JP Size: 52b
 */
void CUSBPcs::create()
{
	USB.AddMessageCallback(CUSBPcs::messageCallback, this);
}

/*
 * --INFO--
 * PAL Address: 0x80020218
 * PAL Size: 48b
 * EN Address: 0x8002000C
 * EN Size: 48b
 * JP Address: 0x8001FA6C
 * JP Size: 48b
 */
void CUSBPcs::destroy()
{
	USB.RemoveMessageCallback(CUSBPcs::messageCallback);
}

/*
 * --INFO--
 * PAL Address: 0x800201f0
 * PAL Size: 40b
 * EN Address: 0x8001FFE4
 * EN Size: 40b
 * JP Address: 0x8001FA44
 * JP Size: 40b
 */
void CUSBPcs::func()
{
	USB.Frame();
}

/*
 * --INFO--
 * PAL Address: 0x800201ec
 * PAL Size: 4b
 * EN Address: 0x8001FFE0
 * EN Size: 4b
 * JP Address: 0x8001FA40
 * JP Size: 4b
 */
void CUSBPcs::messageCallback(unsigned long, void*, MCCChannel)
{
    return;
}

/*
 * --INFO--
 * PAL Address: 0x80020180
 * PAL Size: 108b
 * EN Address: 0x8001FF74
 * EN Size: 108b
 * JP Address: 0x8001F9D0
 * JP Size: 112b
 */
void CUSBPcs::mccReadData()
{
    static int testloop = 0;

    testloop++;
    if (4 < testloop) {
        testloop = 0;
    } else {
        return;
    }

    if (USB.IsConnected() == 0) {
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8001ff6c
 * PAL Size: 532b
 * EN Address: 0x8001FD60
 * EN Size: 532b
 * JP Address: 0x8001F7BC
 * JP Size: 532b
 */
int CUSBPcs::SendDataCode(int code, void* src, int elemSize, int elemCount)
{
    unsigned int payloadSize;
    int result;
    int connected;
    CDataHeader* packet;
    CDataHeader* dstBuffer;
    CMemory::CStage* stage;
    unsigned int packetSize;

    payloadSize = elemSize * elemCount;
    packetSize = (payloadSize + 0x5F) & ~0x1F;
    stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

    unsigned char* raw = new (stage, "p_usb.cpp", 0x1ca) unsigned char[packetSize];
    packet = reinterpret_cast<CDataHeader*>(raw);
    packet->m_packetSize = packetSize;
    packet->m_packetType = 4;
    packet->m_packetCode = Swap32((unsigned int)code);
    packet->m_elementCount = Swap32((unsigned int)elemCount);
    packet->m_dataSize = Swap32(payloadSize);
    packet->m_reserved2C = Swap32(0);
    packet->m_payloadSize = Swap32(payloadSize);
    memcpy(packet + 1, src, payloadSize);

    connected = USB.IsConnected();
    if (connected == 0) {
        result = 0;
    } else {
        stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

        dstBuffer = reinterpret_cast<CDataHeader*>(new (stage, "p_usb.cpp", 0x19e)
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
