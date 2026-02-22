#include "ffcc/p_usb.h"

#include "ffcc/usb.h"

#include <dolphin/os.h>
#include "string.h"
#include "types.h"

char DAT_8032ec6c;
int DAT_8032ec68;

extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);

extern "C" char __vt__8CManager[];
extern "C" char lbl_801E8668[];
extern "C" char lbl_801E8830[];
extern u32 lbl_801E8690[];
extern u32 lbl_801E869C[];
extern u32 lbl_801E86A8[];
extern u32 lbl_801E86B4[];
extern char lbl_8032F810[];
extern CUSBPcs USBPcs;


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
	m_smallStage = Memory.CreateStage(0x2000, lbl_8032F810, 0);
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
    if ((param_2 != 0) && (m_bigStage == (CMemory::CStage*)nullptr)) {
        m_bigStage = Memory.CreateStage(0x100000, lbl_8032F810, 0);
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
    unsigned int* ptr;
    unsigned int* dstBuffer;
    unsigned int value;
    unsigned int count;
    CMemory::CStage* stage;
    int result;

    count = (unsigned int)(elemSize * elemCount);
    value = (count + 0x5F) & ~0x1F;
    stage = m_bigStage;
    if (stage == (CMemory::CStage*)nullptr) {
        stage = m_smallStage;
    }

    ptr = (unsigned int*)__nwa__FUlPQ27CMemory6CStagePci(value, stage, "p_usb.cpp", 0x1ca);
    ptr[1] = value;
    ptr[0] = 4;
    ptr[9] = Swap32((unsigned int)code);
    ptr[10] = Swap32((unsigned int)elemCount);
    ptr[12] = Swap32(count);
    ptr[11] = 0;
    ptr[8] = Swap32(count);
    memcpy(ptr + 0x10, src, count);

    if (USB.IsConnected() == 0) {
        result = 0;
    } else {
        stage = m_bigStage;
        if (stage == (CMemory::CStage*)nullptr) {
            stage = m_smallStage;
        }

        dstBuffer = (unsigned int*)__nwa__FUlPQ27CMemory6CStagePci((ptr[1] + 0x1F) & ~0x1F, stage, "p_usb.cpp", 0x19e);
        memcpy(dstBuffer, ptr, (ptr[1] + 0x1F) & ~0x1F);

        value = ptr[0];
        dstBuffer[0] = Swap32(value);
        value = ptr[1];
        dstBuffer[1] = Swap32(value);

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
 * PAL Address: 0x800203e4
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_usb_cpp()
{
    void* vtbl = __vt__8CManager;
    *reinterpret_cast<void**>(&USBPcs) = vtbl;
    *reinterpret_cast<void**>(&USBPcs) = lbl_801E8668;
    *reinterpret_cast<void**>(&USBPcs) = lbl_801E8830;

    u32* dst = lbl_801E86B4;
    u32* src0 = lbl_801E8690;
    u32* src1 = lbl_801E869C;
    u32* src2 = lbl_801E86A8;

    dst[1] = src0[0];
    dst[2] = src0[1];
    dst[3] = src0[2];
    dst[4] = src1[0];
    dst[5] = src1[1];
    dst[6] = src1[2];
    dst[7] = src2[0];
    dst[8] = src2[1];
    dst[9] = src2[2];
}
