#include "ffcc/ME_USB_process.h"
#include "ffcc/p_MaterialEditor.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/memory.h"
#include "ffcc/zlist.h"
#include "ffcc/system.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

#define BSWAP32(val) ((u32)(((u32)(val) << 24) | (((u32)(val) & 0xff00) << 8) | (((u32)(val) & 0xff0000) >> 8) | ((u32)(val) >> 24)))

extern "C" void ClearTextureData__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void* GetRsdItem__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void __dla__FPv(void* ptr);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory* memory, unsigned long size, CMemory::CStage* stage, char* file, int line, int align);
extern "C" CMaterialEditorPcs* Free__7CMemoryFPv(CMemory* memory, void* ptr);
extern "C" void Printf__7CSystemFPce(CSystem* system, char* format, ...);
extern "C" void ResetRsdList__18CMaterialEditorPcsFP5ZLIST(CMaterialEditorPcs* materialEditorPcs, ZLIST* zlist);
extern "C" int AddRsdList__18CMaterialEditorPcsFP5ZLIST(CMaterialEditorPcs* materialEditorPcs, ZLIST* zlist);
extern "C" void SetRsdIndex__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void SetRsdFlag__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);

static char s_ME_USB_process_cpp_801d7d78[] = "ME_USB_process.cpp";
static char s_MemAlloc_Error____size__d_801d7d8c[] = "MemAlloc Error : size=%d";

namespace {
static inline u8* Ptr(CMaterialEditorPcs* self, u32 offset)
{
    return reinterpret_cast<u8*>(self) + offset;
}

static inline CUSBStreamData* UsbStream(CMaterialEditorPcs* self)
{
    return reinterpret_cast<CUSBStreamData*>(Ptr(self, 0x8));
}

static inline u32& U32At(CMaterialEditorPcs* self, u32 offset)
{
    return *reinterpret_cast<u32*>(Ptr(self, offset));
}

static inline CMemory::CStage* MaterialEditorStage()
{
    return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<u8*>(&MaterialEditorPcs) + 4);
}
}

/*
 * --INFO--
 * PAL Address: 80051d2c
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CMaterialEditorPcs* MemFree__18CMaterialEditorPcsFPv(CMaterialEditorPcs* materialEditorPcs, void* ptr)
{
    if (ptr == nullptr) {
        return materialEditorPcs;
    }

    return Free__7CMemoryFPv(&Memory, ptr);
}

/*
 * --INFO--
 * PAL Address: 80050a7c
 * PAL Size: 4784b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetUSBData__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs)
{
    CUSBStreamData* usb = UsbStream(materialEditorPcs);

    switch (usb->m_packetCode) {
    case 1:
        memcpy(Ptr(materialEditorPcs, 0xEC), usb->m_data, 0x120);
        for (int i = 0; i < 0x20; i++) {
            U32At(materialEditorPcs, 0xEC + i * 4) = BSWAP32(U32At(materialEditorPcs, 0xEC + i * 4));
        }
        memcpy(Ptr(materialEditorPcs, 0x16C), Ptr(materialEditorPcs, 0xEC), 0x30);
        DCStoreRange(Ptr(materialEditorPcs, 0xEC), 0x120);
        break;
    case 3:
        U32At(materialEditorPcs, 0x1C) = 1;
        break;
    case 4:
        U32At(materialEditorPcs, 0x1C) = 0;
        break;
    case 0x10: {
        u32** rsdItemRef = reinterpret_cast<u32**>(GetRsdItem__18CMaterialEditorPcsFv(materialEditorPcs));
        u32* rsdItem = *rsdItemRef;
        u32 size = usb->m_sizeBytes;
        u32 dataSize = size * 0xC;
        float* xyzData;

        if (rsdItem[4] != 0) {
            __dla__FPv(reinterpret_cast<void*>(rsdItem[4]));
            rsdItem[4] = 0;
        }

        rsdItem[0] = size;
        rsdItem[4] = reinterpret_cast<u32>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, dataSize, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0));
        if (rsdItem[4] == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, dataSize);
        }

        memcpy(reinterpret_cast<void*>(rsdItem[4]), usb->m_data, dataSize);

        xyzData = reinterpret_cast<float*>(rsdItem[4]);
        for (u32 i = 0; i < size; i++) {
            u32 id = BSWAP32(*reinterpret_cast<u32*>(xyzData + 0));
            float y = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 1)));
            float z = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 2)));

            *reinterpret_cast<u32*>(xyzData + 0) = id;
            xyzData[1] = y;
            xyzData[2] = z;
            xyzData += 3;
        }
        DCStoreRange(reinterpret_cast<void*>(rsdItem[4]), dataSize);
        break;
    }
    case 0x12: {
        u32** rsdItemRef = reinterpret_cast<u32**>(GetRsdItem__18CMaterialEditorPcsFv(materialEditorPcs));
        u32* rsdItem = *rsdItemRef;
        u32 size = usb->m_sizeBytes;
        u32 dataSize = size * 0xC;
        float* xyzData;

        if (rsdItem[5] != 0) {
            __dla__FPv(reinterpret_cast<void*>(rsdItem[5]));
            rsdItem[5] = 0;
        }

        rsdItem[1] = size;
        rsdItem[5] = reinterpret_cast<u32>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, dataSize, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0));
        if (rsdItem[5] == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, dataSize);
        }

        memcpy(reinterpret_cast<void*>(rsdItem[5]), usb->m_data, dataSize);

        xyzData = reinterpret_cast<float*>(rsdItem[5]);
        for (u32 i = 0; i < size; i++) {
            u32 id = BSWAP32(*reinterpret_cast<u32*>(xyzData + 0));
            float y = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 1)));
            float z = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 2)));

            *reinterpret_cast<u32*>(xyzData + 0) = id;
            xyzData[1] = y;
            xyzData[2] = z;
            xyzData += 3;
        }
        DCStoreRange(reinterpret_cast<void*>(rsdItem[5]), dataSize);
        break;
    }
    case 0x21:
        U32At(materialEditorPcs, 0xE8) = 1;
        ClearTextureData__18CMaterialEditorPcsFv(materialEditorPcs);
        break;
    case 0x22:
        U32At(materialEditorPcs, 0xE8) = 0;
        break;
    case 0x31: {
        u32 size = usb->m_sizeBytes;
        u8* dstBuffer = reinterpret_cast<u8*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, size, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0));
        u32** rsdItemRef;
        u8* target;

        if (dstBuffer == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, size);
        }

        rsdItemRef = reinterpret_cast<u32**>(GetRsdItem__18CMaterialEditorPcsFv(materialEditorPcs));
        target = reinterpret_cast<u8*>(*rsdItemRef ? reinterpret_cast<u8*>((*rsdItemRef)[6]) : 0);
        memcpy(dstBuffer, usb->m_data, size);

        if (target != 0) {
            for (u32 i = 0; i < size; i++) {
                target[i * 0x70 + 0x1A] = dstBuffer[i];
            }
        }

        if (dstBuffer != 0) {
            __dla__FPv(dstBuffer);
        }
        break;
    }
    case 0x40:
        ResetRsdList__18CMaterialEditorPcsFP5ZLIST(materialEditorPcs, reinterpret_cast<ZLIST*>(Ptr(materialEditorPcs, 0xC8)));
        break;
    case 0x41:
        AddRsdList__18CMaterialEditorPcsFP5ZLIST(materialEditorPcs, reinterpret_cast<ZLIST*>(Ptr(materialEditorPcs, 0xC8)));
        break;
    case 0x42:
        memcpy(Ptr(materialEditorPcs, 0x20), usb->m_data, 4);
        U32At(materialEditorPcs, 0x20) = BSWAP32(U32At(materialEditorPcs, 0x20));
        DCStoreRange(Ptr(materialEditorPcs, 0x20), 4);
        SetRsdIndex__18CMaterialEditorPcsFv(materialEditorPcs);
        break;
    case 0x43:
        memcpy(Ptr(materialEditorPcs, 0xC0), usb->m_data, 4);
        U32At(materialEditorPcs, 0xC0) = BSWAP32(U32At(materialEditorPcs, 0xC0));
        SetRsdFlag__18CMaterialEditorPcsFv(materialEditorPcs);
        DCStoreRange(Ptr(materialEditorPcs, 0xC0), 4);
        break;
    }
}
