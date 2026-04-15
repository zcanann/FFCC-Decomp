#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"
#include "types.h"

CUSBPcs USBPcs;
char s_usbReadPollInitialized;
int s_usbReadPollFrameCounter;
extern "C" void create__7CUSBPcsFv(CUSBPcs*);
extern "C" void destroy__7CUSBPcsFv(CUSBPcs*);
extern "C" void func__7CUSBPcsFv(CUSBPcs*);
u32 m_table_desc0__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(create__7CUSBPcsFv)};
u32 m_table_desc1__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(destroy__7CUSBPcsFv)};
u32 m_table_desc2__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<u32>(func__7CUSBPcsFv)};
char s_CUSBPcs_8032f810[] = "CUSBPcs";
u32 m_table__7CUSBPcs[0x15C / sizeof(u32)] = {
    reinterpret_cast<u32>(s_CUSBPcs_8032f810), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x12
};
static const char s_usbRootPath[] = "plot/kmitsuru/";
static const char s_p_usb_cpp_801D6D08[] = "p_usb.cpp";

extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CUSBPcs::CUSBPcs()
{
    m_table__7CUSBPcs[1] = m_table_desc0__7CUSBPcs[0];
    m_table__7CUSBPcs[2] = m_table_desc0__7CUSBPcs[1];
    m_table__7CUSBPcs[3] = m_table_desc0__7CUSBPcs[2];
    m_table__7CUSBPcs[4] = m_table_desc1__7CUSBPcs[0];
    m_table__7CUSBPcs[5] = m_table_desc1__7CUSBPcs[1];
    m_table__7CUSBPcs[6] = m_table_desc1__7CUSBPcs[2];
    m_table__7CUSBPcs[7] = m_table_desc2__7CUSBPcs[0];
    m_table__7CUSBPcs[8] = m_table_desc2__7CUSBPcs[1];
    m_table__7CUSBPcs[9] = m_table_desc2__7CUSBPcs[2];
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
 * Address:	TODO
 * Size:	TODO
 */
int CUSBPcs::GetTable(unsigned long param)
{
    return (int)((char*)m_table__7CUSBPcs + (param * 0x15c));
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
    unsigned int count;
    unsigned int* ptr;
    unsigned int* alloc;
    int connected;
    unsigned int* dstBuffer;
    CMemory::CStage* stage;
    int result;

    count = (unsigned int)(elemSize * elemCount);
    unsigned int value = (count + 0x5F) & ~0x1F;
    stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

    alloc = (unsigned int*)__nwa__FUlPQ27CMemory6CStagePci(value, stage, const_cast<char*>(s_p_usb_cpp_801D6D08), 0x1ca);
    alloc[1] = value;
    alloc[0] = 4;
    ptr = alloc;
    ptr[9] = Swap32((unsigned int)code);
    ptr[10] = Swap32((unsigned int)elemCount);
    ptr[12] = Swap32(count);
    ptr[11] = Swap32(0);
    ptr[8] = Swap32(count);
    memcpy(ptr + 0x10, src, count);

    connected = USB.IsConnected();
    if (connected == 0) {
        result = 0;
    } else {
        stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

        dstBuffer = (unsigned int*)__nwa__FUlPQ27CMemory6CStagePci(
            (ptr[1] + 0x1F) & ~0x1F, stage, const_cast<char*>(s_p_usb_cpp_801D6D08), 0x19e);
        memcpy(dstBuffer, ptr, (ptr[1] + 0x1F) & ~0x1F);

        dstBuffer[0] = Swap32(ptr[0]);
        dstBuffer[1] = Swap32(ptr[1]);

        DCFlushRange(dstBuffer, (ptr[1] + 0x1F) & ~0x1F);
        DCInvalidateRange(dstBuffer, (ptr[1] + 0x1F) & ~0x1F);

        if (USB.Write(dstBuffer, (ptr[1] + 0x1F) & ~0x1F) == 0) {
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

    if (ptr != (unsigned int*)nullptr) {
        delete[] ptr;
    }
    return result;
}
