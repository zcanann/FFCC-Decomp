#include "ffcc/ME_USB_process.h"
#include "ffcc/p_MaterialEditor.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/memory.h"
#include "ffcc/system.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

#define BSWAP32(val) ((u32)(((u32)(val) << 24) | (((u32)(val) & 0xff00) << 8) | (((u32)(val) & 0xff0000) >> 8) | ((u32)(val) >> 24)))

extern "C" void ClearTextureData__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void SetRsdIndex__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void SetRsdFlag__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);

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
    if (ptr != 0) {
        Memory.Free(ptr);
    }
    return materialEditorPcs;
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
    case 0x21:
        U32At(materialEditorPcs, 0xE8) = 1;
        ClearTextureData__18CMaterialEditorPcsFv(materialEditorPcs);
        break;
    case 0x22:
        U32At(materialEditorPcs, 0xE8) = 0;
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
