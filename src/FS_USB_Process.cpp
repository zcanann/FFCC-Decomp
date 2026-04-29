#include "ffcc/FS_USB_Process.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/p_FunnyShape.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/p_usb.h"
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

extern "C" void* __nw__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);
extern "C" void __dla__FPv(void* ptr);

extern "C" const char s_FS_USB_Process_cpp_801D7E80[] = "FS_USB_Process.cpp";

namespace {

struct CUSBStreamDataHeader {
    u8* m_data;
    int m_headerReady;
    int m_dataReady;
    u32 m_sizeBytes;
    u32 m_packetCode;
};

struct DisplayTail {
    u8 m_bytes[0xB];
};

static inline CUSBStreamDataHeader* UsbStream(CFunnyShapePcs* self) {
    return reinterpret_cast<CUSBStreamDataHeader*>(self->m_usbStreamDataStorage);
}

static inline CFunnyShape* FunnyShape(CFunnyShapePcs* self) {
    return reinterpret_cast<CFunnyShape*>(self->m_funnyShapeStorage);
}

static inline u8* AnmData(CFunnyShapePcs* self) {
    return static_cast<u8*>(self->m_anm.anmData);
}

static inline u32 LoadSwap32(u32 value) {
    return __lwbrx(&value, 0);
}

static inline void StoreSwap32(u32* value) {
    *value = LoadSwap32(*value);
}

static inline void StoreSwap32(f32* value) {
    f32 raw = *value;
    u32 swapped = __lwbrx(&raw, 0);
    *value = *reinterpret_cast<f32*>(&swapped);
}

static inline s16 LoadSwap16(s16 value) {
    return __lhbrx(&value, 0);
}

static inline u16 LoadSwapU16(u16 value) {
    return __lhbrx(&value, 0);
}
}

/*
 * --INFO--
 * PAL Address: 80052bc0
 * PAL Size: 3524b
 */
void CFunnyShapePcs::SetUSBData()
{
    CUSBStreamDataHeader* usb = UsbStream(this);

    switch (usb->m_packetCode) {
    case 4:
        m_displayTextureEnabled = 1;
        FunnyShape(this)->ClearTextureData();
        break;
    case 6:
        m_displayTextureEnabled = 0;
        break;
    case 12: {
        memcpy(&m_displayPending, usb->m_data, 0x40);
        StoreSwap32(&m_displayPending.flags);
        StoreSwap32(&m_displayPending.unk08);
        StoreSwap32(&m_displayPending.unk0C);
        StoreSwap32(&m_displayPending.unk10);
        StoreSwap32(&m_displayPending.unk14);
        StoreSwap32(&m_displayPending.unk18);
        StoreSwap32(&m_displayPending.unk1C);
        StoreSwap32(&m_displayPending.unk20);
        StoreSwap32(&m_displayPending.unk24);
        m_displayPending.unk28 = LoadSwap16(m_displayPending.unk28);
        m_displayPending.unk2A = LoadSwap16(m_displayPending.unk2A);
        StoreSwap32(&m_displayPending.unk2C);
        StoreSwap32(&m_displayPending.unk30);
        DCStoreRange(&m_displayPending, 0x40);

        GXColor clear;
        clear.r = m_displayPending.clear.r;
        clear.g = m_displayPending.clear.g;
        clear.b = m_displayPending.clear.b;
        clear.a = m_displayPending.clear.a;
        GXSetCopyClear(clear, 0xFFFFFF);
        FS_DISPLAY_STATUS display = m_displayPending;
        m_displayCurrent.flags = display.flags;
        m_displayCurrent.clear.r = display.clear.r;
        m_displayCurrent.clear.g = display.clear.g;
        m_displayCurrent.clear.b = display.clear.b;
        m_displayCurrent.clear.a = display.clear.a;
        m_displayCurrent.unk08 = display.unk08;
        m_displayCurrent.unk0C = display.unk0C;
        m_displayCurrent.unk10 = display.unk10;
        m_displayCurrent.unk14 = display.unk14;
        m_displayCurrent.unk18 = display.unk18;
        m_displayCurrent.unk1C = display.unk1C;
        m_displayCurrent.unk20 = display.unk20;
        m_displayCurrent.unk24 = display.unk24;
        m_displayCurrent.unk28 = display.unk28;
        m_displayCurrent.unk2A = display.unk2A;
        m_displayCurrent.unk2C = display.unk2C;
        m_displayCurrent.unk30 = display.unk30;
        m_displayCurrent.unk34[0] = display.unk34[0];
        *reinterpret_cast<DisplayTail*>(&m_displayCurrent.unk34[1]) =
            *reinterpret_cast<DisplayTail*>(&display.unk34[1]);
        break;
    }
    case 5: {
        s16* tmp = static_cast<s16*>(__nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes, FunnyShapePcs.m_viewerStage, const_cast<char*>(s_FS_USB_Process_cpp_801D7E80), 0x55));
        void* textureHeader = __nw__FUlPQ27CMemory6CStagePci(
            0x30, FunnyShapePcs.m_viewerStage, const_cast<char*>(s_FS_USB_Process_cpp_801D7E80), 0x57);
        m_textureHeaders[m_textureCount] = textureHeader;

        memcpy(tmp, usb->m_data, usb->m_sizeBytes);
        s16 header0 = tmp[0];
        tmp[0] = LoadSwap16(header0);
        s16 header1 = tmp[1];
        tmp[1] = LoadSwap16(header1);
        s16 header2 = tmp[2];
        tmp[2] = LoadSwap16(header2);
        s16 header3 = tmp[3];
        tmp[3] = LoadSwap16(header3);
        s16 header4 = tmp[4];
        tmp[4] = LoadSwap16(header4);
        s16 header5 = tmp[5];
        tmp[5] = LoadSwap16(header5);
        s16 header6 = tmp[6];
        tmp[6] = LoadSwap16(header6);
        s16 header7 = tmp[7];
        tmp[7] = LoadSwap16(header7);
        u16 header10 = reinterpret_cast<u16*>(tmp)[0x10];
        reinterpret_cast<u16*>(tmp)[0x10] = LoadSwapU16(header10);
        u16 header11 = reinterpret_cast<u16*>(tmp)[0x11];
        reinterpret_cast<u16*>(tmp)[0x11] = LoadSwapU16(header11);

        DCFlushRange(tmp, 0x30);
        memcpy(m_textureHeaders[m_textureCount], tmp, 0x30);

        m_textureData[m_textureCount] = __nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes - 0x30, FunnyShapePcs.m_viewerStage, const_cast<char*>(s_FS_USB_Process_cpp_801D7E80), 0x6C);
        memcpy(m_textureData[m_textureCount], tmp + 0x18, usb->m_sizeBytes - 0x30);
        DCFlushRange(m_textureData[m_textureCount], usb->m_sizeBytes - 0x30);

        m_texObjData[m_textureCount] = __nw__FUlPQ27CMemory6CStagePci(
            0x20, FunnyShapePcs.m_viewerStage, const_cast<char*>(s_FS_USB_Process_cpp_801D7E80), 0x73);
        GXInitTexObj(static_cast<GXTexObj*>(m_texObjData[m_textureCount]), m_textureData[m_textureCount], tmp[2], tmp[3], GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

        m_textureCount++;
        if (tmp != 0) {
            __dla__FPv(tmp);
        }
        break;
    }
    case 10:
        FunnyShape(this)->ClearAnmData();
        if (m_anm.anmData != 0) {
            __dla__FPv(m_anm.anmData);
            m_anm.anmData = 0;
        }
        memset(FunnyShape(this), 0, 0x30);
        memcpy(&m_anm, usb->m_data, 0x10);
        StoreSwap32(&m_anm.unk00);
        m_anm.unk04 = LoadSwap16(m_anm.unk04);
        m_anm.unk06 = LoadSwap16(m_anm.unk06);
        m_anm.unk08 = LoadSwap16(m_anm.unk08);
        m_anm.unk0A = LoadSwap16(m_anm.unk0A);
        m_anm.anmData = 0;
        DCStoreRange(&m_anm, usb->m_sizeBytes);
        break;
    case 11: {
        m_anm.anmData = __nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes, FunnyShapePcs.m_viewerStage, const_cast<char*>(s_FS_USB_Process_cpp_801D7E80), 0x9C);

        memcpy(AnmData(this), usb->m_data, usb->m_sizeBytes);
        *reinterpret_cast<s16*>(AnmData(this) + 2) = LoadSwap16(*reinterpret_cast<s16*>(AnmData(this) + 2));
        *reinterpret_cast<s16*>(AnmData(this) + 4) = LoadSwap16(*reinterpret_cast<s16*>(AnmData(this) + 4));
        *reinterpret_cast<s16*>(AnmData(this) + 6) = LoadSwap16(*reinterpret_cast<s16*>(AnmData(this) + 6));
        *reinterpret_cast<s16*>(AnmData(this) + 8) = LoadSwap16(*reinterpret_cast<s16*>(AnmData(this) + 8));
        *reinterpret_cast<s16*>(AnmData(this) + 10) = LoadSwap16(*reinterpret_cast<s16*>(AnmData(this) + 10));
        *reinterpret_cast<u16*>(AnmData(this) + 14) = LoadSwapU16(*reinterpret_cast<u16*>(AnmData(this) + 14));
        *reinterpret_cast<s16*>(AnmData(this) + 16) = LoadSwap16(*reinterpret_cast<s16*>(AnmData(this) + 16));
        *reinterpret_cast<s16*>(AnmData(this) + 18) = LoadSwap16(*reinterpret_cast<s16*>(AnmData(this) + 18));

        int groupOffset = 0;
        for (int i = 0; i < *reinterpret_cast<s16*>(AnmData(this) + 6); i++) {
            u8* group = AnmData(this) + groupOffset;
            if (i != 0) {
                *reinterpret_cast<s16*>(group + 0x10) = LoadSwap16(*reinterpret_cast<s16*>(group + 0x10));
                *reinterpret_cast<s16*>(group + 0x12) = LoadSwap16(*reinterpret_cast<s16*>(group + 0x12));
            }

            s16* list = reinterpret_cast<s16*>(AnmData(this) + *reinterpret_cast<s16*>(group + 0x10));
            list[0] = LoadSwap16(list[0]);
            list[1] = LoadSwap16(list[1]);

            int src24 = 0;
            int src2c = 0;
            int dst24 = 0;
            int dst2c = 0;
            for (int j = 0; j < static_cast<s16>(list[1]); j++) {
                if ((list[0] & 8) != 0) {
                    u8* src = reinterpret_cast<u8*>(list) + 0x10 + src2c;
                    u32* p32 = reinterpret_cast<u32*>(src);
                    StoreSwap32(&p32[0]);
                    StoreSwap32(&p32[1]);
                    *reinterpret_cast<s16*>(src + 0x10) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x10));
                    *reinterpret_cast<s16*>(src + 0x12) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x12));
                    *reinterpret_cast<s16*>(src + 0x14) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x14));
                    *reinterpret_cast<s16*>(src + 0x16) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x16));
                    *reinterpret_cast<s16*>(src + 0x18) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x18));
                    *reinterpret_cast<s16*>(src + 0x1A) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1A));
                    *reinterpret_cast<s16*>(src + 0x1C) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1C));
                    *reinterpret_cast<s16*>(src + 0x1E) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1E));
                    *reinterpret_cast<s16*>(src + 0x20) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x20));
                    *reinterpret_cast<s16*>(src + 0x22) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x22));
                    *reinterpret_cast<s16*>(src + 0x24) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x24));
                    *reinterpret_cast<s16*>(src + 0x26) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x26));

                    u8* dst = reinterpret_cast<u8*>(list) + 0x10 + dst2c;
                    memcpy(dst, src, 0x2C);
                    DCStoreRange(dst, 0x2C);
                } else {
                    u8* src = reinterpret_cast<u8*>(list) + 0x10 + src24;
                    u32* p32 = reinterpret_cast<u32*>(src);
                    StoreSwap32(&p32[0]);
                    StoreSwap32(&p32[1]);
                    *reinterpret_cast<s16*>(src + 0x10) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x10));
                    *reinterpret_cast<s16*>(src + 0x12) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x12));
                    *reinterpret_cast<s16*>(src + 0x14) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x14));
                    *reinterpret_cast<s16*>(src + 0x16) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x16));
                    *reinterpret_cast<s16*>(src + 0x18) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x18));
                    *reinterpret_cast<s16*>(src + 0x1A) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1A));
                    *reinterpret_cast<s16*>(src + 0x1C) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1C));
                    *reinterpret_cast<s16*>(src + 0x1E) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1E));

                    u8* dst = reinterpret_cast<u8*>(list) + 0x10 + dst24;
                    memcpy(dst, src, 0x24);
                    DCStoreRange(dst, 0x24);
                }

                src2c += 0x2C;
                src24 += 0x24;
                dst24 += 0x24;
                dst2c += 0x2C;
            }
            groupOffset += 8;
        }
        DCStoreRange(m_anm.anmData, usb->m_sizeBytes);
        FunnyShape(this)->InitAnmWork();
        break;
    }
    case 15: {
        OSFS_SHAPE_ST shape;
        memcpy(&shape, usb->m_data, sizeof(shape));

        shape.flags = LoadSwap16(shape.flags);
        shape.count = LoadSwap16(shape.count);
        shape.unk08 = LoadSwap16(shape.unk08);
        m_shape = shape;
        break;
    }
    case 16: {
        if (m_meshData != 0) {
            __dla__FPv(m_meshData);
            m_meshData = 0;
        }

        u8* meshData = static_cast<u8*>(__nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes, FunnyShapePcs.m_viewerStage, const_cast<char*>(s_FS_USB_Process_cpp_801D7E80), 0x106));
        memcpy(meshData, usb->m_data, usb->m_sizeBytes);
        *reinterpret_cast<s16*>(meshData + 0x0) = LoadSwap16(*reinterpret_cast<s16*>(meshData + 0x0));
        *reinterpret_cast<s16*>(meshData + 0x2) = LoadSwap16(*reinterpret_cast<s16*>(meshData + 0x2));

        int src2c = 0;
        int src24 = 0;
        int dst24 = 0;
        int dst2c = 0;
        for (int i = 0; i < m_shape.count; i++) {
            if ((m_shape.flags & 8) != 0) {
                u8* src = meshData + 0x10 + src2c;
                u32* p32 = reinterpret_cast<u32*>(src);
                StoreSwap32(&p32[0]);
                StoreSwap32(&p32[1]);
                *reinterpret_cast<s16*>(src + 0x10) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x10));
                *reinterpret_cast<s16*>(src + 0x12) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x12));
                *reinterpret_cast<s16*>(src + 0x14) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x14));
                *reinterpret_cast<s16*>(src + 0x16) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x16));
                *reinterpret_cast<s16*>(src + 0x18) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x18));
                *reinterpret_cast<s16*>(src + 0x1A) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1A));
                *reinterpret_cast<s16*>(src + 0x1C) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1C));
                *reinterpret_cast<s16*>(src + 0x1E) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1E));
                *reinterpret_cast<s16*>(src + 0x20) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x20));
                *reinterpret_cast<s16*>(src + 0x22) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x22));
                *reinterpret_cast<s16*>(src + 0x24) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x24));
                *reinterpret_cast<s16*>(src + 0x26) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x26));

                u8* dst = meshData + 0x10 + dst2c;
                memcpy(dst, src, 0x2C);
                DCStoreRange(dst, 0x2C);
            } else {
                u8* src = meshData + 0x10 + src24;
                u32* p32 = reinterpret_cast<u32*>(src);
                StoreSwap32(&p32[0]);
                StoreSwap32(&p32[1]);
                *reinterpret_cast<s16*>(src + 0x10) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x10));
                *reinterpret_cast<s16*>(src + 0x12) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x12));
                *reinterpret_cast<s16*>(src + 0x14) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x14));
                *reinterpret_cast<s16*>(src + 0x16) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x16));
                *reinterpret_cast<s16*>(src + 0x18) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x18));
                *reinterpret_cast<s16*>(src + 0x1A) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1A));
                *reinterpret_cast<s16*>(src + 0x1C) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1C));
                *reinterpret_cast<s16*>(src + 0x1E) = LoadSwap16(*reinterpret_cast<s16*>(src + 0x1E));

                u8* dst = meshData + 0x10 + dst24;
                memcpy(dst, src, 0x24);
                DCStoreRange(dst, 0x24);
            }

            src2c += 0x2C;
            src24 += 0x24;
            dst24 += 0x24;
            dst2c += 0x2C;
        }

        m_meshData = meshData;
        DCStoreRange(m_meshData, usb->m_sizeBytes);
        break;
    }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED  
 * PAL Size: 52b
 */
void CFunnyShapePcs::USBDataCallback(CUSBPcs::CDataHeader* dataHeader)
{
    (void)dataHeader;
}
