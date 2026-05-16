#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"
#include "types.h"

extern const char lbl_801DA074[];
int s_usbReadPollFrameCounter;
char s_usbReadPollInitialized;
extern "C" void create__7CUSBPcsFv(CUSBPcs*);
extern "C" void destroy__7CUSBPcsFv(CUSBPcs*);
extern "C" void func__7CUSBPcsFv(CUSBPcs*);

extern const char s_CUSBPcs_8032f810[] = "CUSBPcs";
extern "C" unsigned int m_table_desc0__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__7CUSBPcsFv)};
extern "C" unsigned int m_table_desc1__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__7CUSBPcsFv)};
extern "C" unsigned int m_table_desc2__7CUSBPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(func__7CUSBPcsFv)};
unsigned int m_table__7CUSBPcs[0x11C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(s_CUSBPcs_8032f810)),
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
};
unsigned int s_CUSBPcsTablePad0[3] = {0, 0, 0};
unsigned int s_CUSBPcsTablePad1[5] = {0, 0, 0, 0, 0};
const char* DAT_8032E838[2] = {lbl_801DA074, 0};
extern const char s_p_usb_cpp_801D6D08[] = "p_usb.cpp";
extern const char s_usbRootPath[16] = "plot/kmitsuru/";
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);

inline CUSBPcs::CUSBPcs()
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
    unsigned int* dstBuffer;
    CMemory::CStage* stage;
    unsigned int value;

    count = elemSize * elemCount;
    value = (count + 0x5F) & ~0x1F;
    stage = (m_bigStage != (CMemory::CStage*)nullptr) ? m_bigStage : m_smallStage;

    void* packet = __nwa__FUlPQ27CMemory6CStagePci(
        value, stage, const_cast<char*>(s_p_usb_cpp_801D6D08), 0x1ca);
    unsigned int* header = (unsigned int*)packet;
    header[1] = value;
    *header = 4;
    unsigned int* ptr = header;
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
        m_bigStage = Memory.CreateStage(0x100000, const_cast<char*>(s_CUSBPcs_8032f810), 0);
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
    return reinterpret_cast<int>(reinterpret_cast<char*>(m_table__7CUSBPcs) + (param * 0x15c));
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

	m_smallStage = memory->CreateStage(0x2000, const_cast<char*>(s_CUSBPcs_8032f810), 0);
	m_bigStage = (CMemory::CStage*)nullptr;

	strcpy(m_rootPath, s_usbRootPath);
	m_unk0x104 = 0;
	m_unk0x108 = 0;

	USB.Connect();
}
