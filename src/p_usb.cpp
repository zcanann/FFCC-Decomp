#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"
#include "types.h"

char s_usbReadPollInitialized;
int s_usbReadPollFrameCounter;
extern "C" void create__7CUSBPcsFv(CUSBPcs*);
extern "C" void destroy__7CUSBPcsFv(CUSBPcs*);
extern "C" void func__7CUSBPcsFv(CUSBPcs*);
u32 m_table_desc0__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(create__7CUSBPcsFv)};
u32 m_table_desc1__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(destroy__7CUSBPcsFv)};
u32 m_table_desc2__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(func__7CUSBPcsFv)};
char s_CUSBPcs_8032f810[] = "CUSBPcs";
u32 m_table__7CUSBPcs[0x11C / sizeof(u32)] = {
    reinterpret_cast<u32>(s_CUSBPcs_8032f810), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x12
};
static const char s_p_usb_cpp_801D6D08[] = "p_usb.cpp";
static const char s_usbRootPath[] = "plot/kmitsuru/";

extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CUSBPcs::CUSBPcs()
{
    u32* table = m_table__7CUSBPcs;
    const u32* desc0 = m_table_desc0__7CUSBPcs;
    const u32* desc1 = m_table_desc1__7CUSBPcs;
    const u32* desc2 = m_table_desc2__7CUSBPcs;

    table[1] = desc0[0];
    table[2] = desc0[1];
    table[3] = desc0[2];
    table[4] = desc1[0];
    table[5] = desc1[1];
    table[6] = desc1[2];
    table[7] = desc2[0];
    table[8] = desc2[1];
    table[9] = desc2[2];
}

static inline unsigned int Align32(unsigned int x)
{
    return (x + 0x1F) & ~0x1F;
}

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
    unsigned int allocSize;
    unsigned int byteCount;
    unsigned int swappedCode;
    unsigned int swappedElemCount;
    unsigned int swappedByteCount;
    unsigned int swappedZero;
    unsigned int repeatedByteCount;
    unsigned int* buffer;
    unsigned int* dstBuffer;
    CMemory::CStage* stage;
    int result;

    byteCount = (unsigned int)(elemSize * elemCount);
    allocSize = (byteCount + 0x5F) & ~0x1F;
    stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

    buffer = (unsigned int*)__nwa__FUlPQ27CMemory6CStagePci(
        allocSize, stage, const_cast<char*>(s_p_usb_cpp_801D6D08), 0x1ca);
    buffer[1] = allocSize;
    buffer[0] = 4;

    swappedCode = (unsigned int)code;
    buffer[9] = Swap32(swappedCode);
    swappedElemCount = (unsigned int)elemCount;
    buffer[10] = Swap32(swappedElemCount);
    swappedByteCount = byteCount;
    buffer[12] = Swap32(swappedByteCount);
    swappedZero = 0;
    buffer[11] = Swap32(swappedZero);
    repeatedByteCount = byteCount;
    buffer[8] = Swap32(repeatedByteCount);
    memcpy(buffer + 0x10, src, byteCount);

    if (USB.IsConnected() == 0) {
        result = 0;
    } else {
        stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

        dstBuffer = (unsigned int*)__nwa__FUlPQ27CMemory6CStagePci(
            (buffer[1] + 0x1F) & ~0x1F, stage, const_cast<char*>(s_p_usb_cpp_801D6D08), 0x19e);
        memcpy(dstBuffer, buffer, (buffer[1] + 0x1F) & ~0x1F);

        dstBuffer[0] = Swap32(buffer[0]);
        dstBuffer[1] = Swap32(buffer[1]);

        DCFlushRange(dstBuffer, (buffer[1] + 0x1F) & ~0x1F);
        DCInvalidateRange(dstBuffer, (buffer[1] + 0x1F) & ~0x1F);

        if (USB.Write(dstBuffer, (buffer[1] + 0x1F) & ~0x1F) == 0) {
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

    if (buffer != (unsigned int*)nullptr) {
        delete[] buffer;
    }
    return result;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CUSBPcs::mccReadData()
{ 
	if (s_usbReadPollInitialized == '\0')
	{
		s_usbReadPollFrameCounter = 0;
		s_usbReadPollInitialized = '\x01';
	}

	s_usbReadPollFrameCounter = s_usbReadPollFrameCounter + 1;

	if (4 < s_usbReadPollFrameCounter)
	{
		s_usbReadPollFrameCounter = 0;
		goto read_usb;
	end:
		return;
	read_usb:
		int connected = USB.IsConnected();
		if (connected != 0) {
			goto end;
		}
	}
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
void CUSBPcs::func()
{
	USB.Frame();
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
void CUSBPcs::create()
{
	USB.AddMessageCallback(CUSBPcs::messageCallback, this);
}

/*
 * --INFO--
 * PAL Address: 0x8002027c
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::IsBigAlloc(int param_2)
{
    if ((param_2 != 0) && (m_bigStage == (CMemory::CStage*)nullptr)) {
        m_bigStage = Memory.CreateStage(0x100000, s_CUSBPcs_8032f810, 0);
    } else if ((param_2 == 0) && (m_bigStage != (CMemory::CStage*)nullptr)) {
        Memory.DestroyStage(m_bigStage);
        m_bigStage = (CMemory::CStage*)nullptr;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CUSBPcs::GetTable(unsigned long param)
{
    return (int)((char*)m_table__7CUSBPcs + (param * 0x15c));
}

/*
 * --INFO--
 * PAL Address: 0x80020314
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
 * PAL Address: 0x80020370
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CUSBPcs::Init()
{ 
    CMemory* memory = &Memory;

	m_smallStage = memory->CreateStage(0x2000, s_CUSBPcs_8032f810, 0);
	m_bigStage = (CMemory::CStage*)nullptr;

	strcpy(m_rootPath, s_usbRootPath);
	m_unk0x104 = 0;
	m_unk0x108 = 0;

	USB.Connect();
}

CUSBPcs USBPcs;
