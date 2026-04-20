#include "ffcc/FS_USB_Process.h"
#include "ffcc/FunnyShape.h"
#include "ffcc/p_FunnyShape.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/p_usb.h"
#include "dolphin/gx/GXFrameBuffer.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

// Byte swap macros
#define BSWAP16(val) ((u16)(((u16)(val) << 8) | ((u16)(val) >> 8)))
#define BSWAP32(val) ((u32)(((u32)(val) << 24) | (((u32)(val) & 0xff00) << 8) | (((u32)(val) & 0xff0000) >> 8) | ((u32)(val) >> 24)))

extern "C" void* __nw__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(u32 size, CMemory::CStage* stage, char* file, int line);
extern "C" void __dla__FPv(void* ptr);

namespace {
static const char s_FS_USB_Process_cpp_801d7e80[] = "FS_USB_Process.cpp";

struct CUSBStreamDataHeader {
    u8* m_data;
    int m_headerReady;
    int m_dataReady;
    u32 m_sizeBytes;
    u32 m_packetCode;
};

static inline CUSBStreamDataHeader* UsbStream(CFunnyShapePcs* self) {
    return reinterpret_cast<CUSBStreamDataHeader*>(self->m_usbStreamDataStorage);
}

static inline CFunnyShape* FunnyShape(CFunnyShapePcs* self) {
    return reinterpret_cast<CFunnyShape*>(self->m_funnyShapeStorage);
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
    CFunnyShape* funny = FunnyShape(this);
    CMemory::CStage* stage = m_viewerStage;

    switch (usb->m_packetCode) {
    case 4:
        m_displayTextureEnabled = 1;
        funny->ClearTextureData();
        break;
    case 5: {
        char textureIndex;
        u16* tmp = static_cast<u16*>(__nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes, stage, const_cast<char*>(s_FS_USB_Process_cpp_801d7e80), 0x55));
        textureIndex = m_textureCount;
        m_textureHeaders[textureIndex] = __nw__FUlPQ27CMemory6CStagePci(
            0x30, stage, const_cast<char*>(s_FS_USB_Process_cpp_801d7e80), 0x57);

        memcpy(tmp, usb->m_data, usb->m_sizeBytes);
        for (int i = 0; i < 8; i++) {
            tmp[i] = BSWAP16(tmp[i]);
        }
        tmp[0x10] = BSWAP16(tmp[0x10]);
        tmp[0x11] = BSWAP16(tmp[0x11]);

        DCFlushRange(tmp, 0x30);
        memcpy(m_textureHeaders[textureIndex], tmp, 0x30);

        m_textureData[textureIndex] = __nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes - 0x30, stage, const_cast<char*>(s_FS_USB_Process_cpp_801d7e80), 0x6C);
        memcpy(m_textureData[textureIndex], tmp + 0x18, usb->m_sizeBytes - 0x30);
        DCFlushRange(m_textureData[textureIndex], usb->m_sizeBytes - 0x30);

        m_texObjData[textureIndex] = __nw__FUlPQ27CMemory6CStagePci(
            0x20, stage, const_cast<char*>(s_FS_USB_Process_cpp_801d7e80), 0x73);
        GXInitTexObj(static_cast<GXTexObj*>(m_texObjData[textureIndex]), m_textureData[textureIndex], tmp[2], tmp[3], GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

        m_textureCount++;
        if (tmp != 0) {
            __dla__FPv(tmp);
        }
        break;
    }
    case 6:
        m_displayTextureEnabled = 0;
        break;
    case 10:
        funny->ClearAnmData();
        if (m_anm.anmData != 0) {
            __dla__FPv(m_anm.anmData);
            m_anm.anmData = 0;
        }
        memset(funny, 0, 0x30);
        memcpy(&m_anm, usb->m_data, 0x10);
        m_anm.unk00 = BSWAP32(m_anm.unk00);
        m_anm.unk04 = BSWAP16(m_anm.unk04);
        m_anm.unk06 = BSWAP16(m_anm.unk06);
        m_anm.unk08 = BSWAP16(m_anm.unk08);
        m_anm.unk0A = BSWAP16(m_anm.unk0A);
        m_anm.anmData = 0;
        DCStoreRange(&m_anm, usb->m_sizeBytes);
        break;
    case 11: {
        u8* animData = static_cast<u8*>(__nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes, stage, const_cast<char*>(s_FS_USB_Process_cpp_801d7e80), 0x9C));
        m_anm.anmData = animData;

        memcpy(animData, usb->m_data, usb->m_sizeBytes);
        *reinterpret_cast<u16*>(animData + 2) = BSWAP16(*reinterpret_cast<u16*>(animData + 2));
        *reinterpret_cast<u16*>(animData + 4) = BSWAP16(*reinterpret_cast<u16*>(animData + 4));
        *reinterpret_cast<u16*>(animData + 6) = BSWAP16(*reinterpret_cast<u16*>(animData + 6));
        *reinterpret_cast<u16*>(animData + 8) = BSWAP16(*reinterpret_cast<u16*>(animData + 8));
        *reinterpret_cast<u16*>(animData + 10) = BSWAP16(*reinterpret_cast<u16*>(animData + 10));
        *reinterpret_cast<u16*>(animData + 14) = BSWAP16(*reinterpret_cast<u16*>(animData + 14));
        *reinterpret_cast<u16*>(animData + 16) = BSWAP16(*reinterpret_cast<u16*>(animData + 16));
        *reinterpret_cast<u16*>(animData + 18) = BSWAP16(*reinterpret_cast<u16*>(animData + 18));

        int groupOffset = 0;
        for (int i = 0; i < *reinterpret_cast<s16*>(animData + 6); i++) {
            u8* group = animData + groupOffset;
            if (i != 0) {
                *reinterpret_cast<u16*>(group + 0x10) = BSWAP16(*reinterpret_cast<u16*>(group + 0x10));
                *reinterpret_cast<u16*>(group + 0x12) = BSWAP16(*reinterpret_cast<u16*>(group + 0x12));
            }

            u16* list = reinterpret_cast<u16*>(animData + *reinterpret_cast<s16*>(group + 0x10));
            list[0] = BSWAP16(list[0]);
            list[1] = BSWAP16(list[1]);

            int src24 = 0;
            int src2c = 0;
            int dst24 = 0;
            int dst2c = 0;
            for (int j = 0; j < static_cast<s16>(list[1]); j++) {
                if ((list[0] & 8) == 0) {
                    u8* src = reinterpret_cast<u8*>(list) + 0x10 + src24;
                    u32* p32 = reinterpret_cast<u32*>(src);
                    p32[0] = BSWAP32(p32[0]);
                    p32[1] = BSWAP32(p32[1]);
                    *reinterpret_cast<u16*>(src + 0x10) = BSWAP16(*reinterpret_cast<u16*>(src + 0x10));
                    *reinterpret_cast<u16*>(src + 0x12) = BSWAP16(*reinterpret_cast<u16*>(src + 0x12));
                    *reinterpret_cast<u16*>(src + 0x14) = BSWAP16(*reinterpret_cast<u16*>(src + 0x14));
                    *reinterpret_cast<u16*>(src + 0x16) = BSWAP16(*reinterpret_cast<u16*>(src + 0x16));
                    *reinterpret_cast<u16*>(src + 0x18) = BSWAP16(*reinterpret_cast<u16*>(src + 0x18));
                    *reinterpret_cast<u16*>(src + 0x1A) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1A));
                    *reinterpret_cast<u16*>(src + 0x1C) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1C));
                    *reinterpret_cast<u16*>(src + 0x1E) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1E));

                    u8* dst = reinterpret_cast<u8*>(list) + 0x10 + dst24;
                    memcpy(dst, src, 0x24);
                    DCStoreRange(dst, 0x24);
                } else {
                    u8* src = reinterpret_cast<u8*>(list) + 0x10 + src2c;
                    u32* p32 = reinterpret_cast<u32*>(src);
                    p32[0] = BSWAP32(p32[0]);
                    p32[1] = BSWAP32(p32[1]);
                    *reinterpret_cast<u16*>(src + 0x10) = BSWAP16(*reinterpret_cast<u16*>(src + 0x10));
                    *reinterpret_cast<u16*>(src + 0x12) = BSWAP16(*reinterpret_cast<u16*>(src + 0x12));
                    *reinterpret_cast<u16*>(src + 0x14) = BSWAP16(*reinterpret_cast<u16*>(src + 0x14));
                    *reinterpret_cast<u16*>(src + 0x16) = BSWAP16(*reinterpret_cast<u16*>(src + 0x16));
                    *reinterpret_cast<u16*>(src + 0x18) = BSWAP16(*reinterpret_cast<u16*>(src + 0x18));
                    *reinterpret_cast<u16*>(src + 0x1A) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1A));
                    *reinterpret_cast<u16*>(src + 0x1C) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1C));
                    *reinterpret_cast<u16*>(src + 0x1E) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1E));
                    *reinterpret_cast<u16*>(src + 0x20) = BSWAP16(*reinterpret_cast<u16*>(src + 0x20));
                    *reinterpret_cast<u16*>(src + 0x22) = BSWAP16(*reinterpret_cast<u16*>(src + 0x22));
                    *reinterpret_cast<u16*>(src + 0x24) = BSWAP16(*reinterpret_cast<u16*>(src + 0x24));
                    *reinterpret_cast<u16*>(src + 0x26) = BSWAP16(*reinterpret_cast<u16*>(src + 0x26));

                    u8* dst = reinterpret_cast<u8*>(list) + 0x10 + dst2c;
                    memcpy(dst, src, 0x2C);
                    DCStoreRange(dst, 0x2C);
                }

                src2c += 0x2C;
                src24 += 0x24;
                dst24 += 0x24;
                dst2c += 0x2C;
            }
            groupOffset += 8;
        }
        DCStoreRange(animData, usb->m_sizeBytes);
        funny->InitAnmWork();
        break;
    }
    case 12: {
        memcpy(&m_displayPending, usb->m_data, 0x40);
        m_displayPending.flags = BSWAP32(m_displayPending.flags);
        m_displayPending.unk08 = BSWAP32(m_displayPending.unk08);
        m_displayPending.unk0C = BSWAP32(m_displayPending.unk0C);
        m_displayPending.unk10 = BSWAP32(m_displayPending.unk10);
        m_displayPending.unk14 = BSWAP32(m_displayPending.unk14);
        m_displayPending.unk18 = BSWAP32(m_displayPending.unk18);
        m_displayPending.unk1C = BSWAP32(m_displayPending.unk1C);
        m_displayPending.unk20 = BSWAP32(m_displayPending.unk20);
        m_displayPending.unk24 = BSWAP32(m_displayPending.unk24);
        m_displayPending.unk28 = BSWAP16(m_displayPending.unk28);
        m_displayPending.unk2A = BSWAP16(m_displayPending.unk2A);
        m_displayPending.unk2C = BSWAP32(m_displayPending.unk2C);
        m_displayPending.unk30 = BSWAP32(m_displayPending.unk30);
        DCStoreRange(&m_displayPending, 0x40);

        GXColor clear = m_displayPending.clear;
        GXSetCopyClear(clear, 0xFFFFFF);

        m_displayCurrent.flags = m_displayPending.flags;
        memcpy(&m_displayCurrent.clear, &m_displayPending.clear, sizeof(GXColor));
        m_displayCurrent.unk08 = m_displayPending.unk08;
        m_displayCurrent.unk0C = m_displayPending.unk0C;
        m_displayCurrent.unk10 = m_displayPending.unk10;
        m_displayCurrent.unk14 = m_displayPending.unk14;
        m_displayCurrent.unk18 = m_displayPending.unk18;
        m_displayCurrent.unk1C = m_displayPending.unk1C;
        m_displayCurrent.unk20 = m_displayPending.unk20;
        m_displayCurrent.unk24 = m_displayPending.unk24;
        m_displayCurrent.unk28 = m_displayPending.unk28;
        m_displayCurrent.unk2A = m_displayPending.unk2A;
        m_displayCurrent.unk2C = m_displayPending.unk2C;
        m_displayCurrent.unk30 = m_displayPending.unk30;
        m_displayCurrent.unk34[0] = m_displayPending.unk34[0];
        memcpy(&m_displayCurrent.unk34[1], &m_displayPending.unk34[1], 0x0B);
        break;
    }
    case 15: {
        u8 local[0x10];
        memcpy(local, usb->m_data, sizeof(local));

        m_shape.flags = BSWAP16(*reinterpret_cast<u16*>(local + 0x0));
        m_shape.count = BSWAP16(*reinterpret_cast<u16*>(local + 0x2));
        m_shape.unk04 = *reinterpret_cast<u32*>(local + 0x4);
        m_shape.unk08 = BSWAP16(*reinterpret_cast<u16*>(local + 0x8));
        memcpy(m_shape.unk0A, local + 0xA, 4);
        m_shape.unk0E = *reinterpret_cast<u16*>(local + 0xE);
        break;
    }
    case 16: {
        if (m_meshData != 0) {
            __dla__FPv(m_meshData);
            m_meshData = 0;
        }

        u8* meshData = static_cast<u8*>(__nwa__FUlPQ27CMemory6CStagePci(
            usb->m_sizeBytes, stage, const_cast<char*>(s_FS_USB_Process_cpp_801d7e80), 0x106));
        memcpy(meshData, usb->m_data, usb->m_sizeBytes);
        *reinterpret_cast<u16*>(meshData + 0x0) = BSWAP16(*reinterpret_cast<u16*>(meshData + 0x0));
        *reinterpret_cast<u16*>(meshData + 0x2) = BSWAP16(*reinterpret_cast<u16*>(meshData + 0x2));

        int src2c = 0;
        int src24 = 0;
        int dst24 = 0;
        int dst2c = 0;
        for (int i = 0; i < m_shape.count; i++) {
            if ((m_shape.flags & 8) == 0) {
                u8* src = meshData + 0x10 + src24;
                u32* p32 = reinterpret_cast<u32*>(src);
                p32[0] = BSWAP32(p32[0]);
                p32[1] = BSWAP32(p32[1]);
                *reinterpret_cast<u16*>(src + 0x10) = BSWAP16(*reinterpret_cast<u16*>(src + 0x10));
                *reinterpret_cast<u16*>(src + 0x12) = BSWAP16(*reinterpret_cast<u16*>(src + 0x12));
                *reinterpret_cast<u16*>(src + 0x14) = BSWAP16(*reinterpret_cast<u16*>(src + 0x14));
                *reinterpret_cast<u16*>(src + 0x16) = BSWAP16(*reinterpret_cast<u16*>(src + 0x16));
                *reinterpret_cast<u16*>(src + 0x18) = BSWAP16(*reinterpret_cast<u16*>(src + 0x18));
                *reinterpret_cast<u16*>(src + 0x1A) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1A));
                *reinterpret_cast<u16*>(src + 0x1C) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1C));
                *reinterpret_cast<u16*>(src + 0x1E) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1E));

                u8* dst = meshData + 0x10 + dst24;
                memcpy(dst, src, 0x24);
                DCStoreRange(dst, 0x24);
            } else {
                u8* src = meshData + 0x10 + src2c;
                u32* p32 = reinterpret_cast<u32*>(src);
                p32[0] = BSWAP32(p32[0]);
                p32[1] = BSWAP32(p32[1]);
                *reinterpret_cast<u16*>(src + 0x10) = BSWAP16(*reinterpret_cast<u16*>(src + 0x10));
                *reinterpret_cast<u16*>(src + 0x12) = BSWAP16(*reinterpret_cast<u16*>(src + 0x12));
                *reinterpret_cast<u16*>(src + 0x14) = BSWAP16(*reinterpret_cast<u16*>(src + 0x14));
                *reinterpret_cast<u16*>(src + 0x16) = BSWAP16(*reinterpret_cast<u16*>(src + 0x16));
                *reinterpret_cast<u16*>(src + 0x18) = BSWAP16(*reinterpret_cast<u16*>(src + 0x18));
                *reinterpret_cast<u16*>(src + 0x1A) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1A));
                *reinterpret_cast<u16*>(src + 0x1C) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1C));
                *reinterpret_cast<u16*>(src + 0x1E) = BSWAP16(*reinterpret_cast<u16*>(src + 0x1E));
                *reinterpret_cast<u16*>(src + 0x20) = BSWAP16(*reinterpret_cast<u16*>(src + 0x20));
                *reinterpret_cast<u16*>(src + 0x22) = BSWAP16(*reinterpret_cast<u16*>(src + 0x22));
                *reinterpret_cast<u16*>(src + 0x24) = BSWAP16(*reinterpret_cast<u16*>(src + 0x24));
                *reinterpret_cast<u16*>(src + 0x26) = BSWAP16(*reinterpret_cast<u16*>(src + 0x26));

                u8* dst = meshData + 0x10 + dst2c;
                memcpy(dst, src, 0x2C);
                DCStoreRange(dst, 0x2C);
            }

            src2c += 0x2C;
            src24 += 0x24;
            dst24 += 0x24;
            dst2c += 0x2C;
        }

        m_meshData = meshData;
        DCStoreRange(meshData, usb->m_sizeBytes);
        break;
    }
    }
}

/*
 * --INFO--
 * PAL Address: UNUSED  
 * PAL Size: 52b
 */
void CFunnyShapePcs::USBDataCallback(CDataHeader* dataHeader)
{
    (void)dataHeader;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CFunnyShapePcs::SetDisplay(FS_DISPLAY_STATUS)
{
}
