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
static char s_FS_USB_Process_cpp[] = "FS_USB_Process.c";

static inline u8* Ptr(CFunnyShapePcs* self, u32 offset) {
    return reinterpret_cast<u8*>(self) + offset;
}

static inline const u8* PtrConst(const CFunnyShapePcs* self, u32 offset) {
    return reinterpret_cast<const u8*>(self) + offset;
}

static inline u16& U16At(CFunnyShapePcs* self, u32 offset) {
    return *reinterpret_cast<u16*>(Ptr(self, offset));
}

static inline s16& S16At(CFunnyShapePcs* self, u32 offset) {
    return *reinterpret_cast<s16*>(Ptr(self, offset));
}

static inline u32& U32At(CFunnyShapePcs* self, u32 offset) {
    return *reinterpret_cast<u32*>(Ptr(self, offset));
}

static inline void*& PtrAt(CFunnyShapePcs* self, u32 offset) {
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline CUSBStreamData* UsbStream(CFunnyShapePcs* self) {
    return reinterpret_cast<CUSBStreamData*>(Ptr(self, 0x8));
}

static inline CFunnyShape* FunnyShape(CFunnyShapePcs* self) {
    return reinterpret_cast<CFunnyShape*>(Ptr(self, 0x1C));
}
}

/*
 * --INFO--
 * PAL Address: 80052bc0
 * PAL Size: 3524b
 */
void CFunnyShapePcs::SetUSBData()
{
    CUSBStreamData* usb = UsbStream(this);
    CFunnyShape* funny = FunnyShape(this);
    CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(Ptr(this, 0x4));
    char index = *reinterpret_cast<char*>(Ptr(this, 0x6124));

    switch (*reinterpret_cast<u32*>(Ptr(this, 0x4C))) {
    case 4:
        U32At(this, 0x61B8) = 1;
        funny->ClearTextureData();
        break;
    case 5: {
        u16* tmp = static_cast<u16*>(__nwa__FUlPQ27CMemory6CStagePci(usb->m_sizeBytes, stage, s_FS_USB_Process_cpp, 0x55));
        void* hdr = __nw__FUlPQ27CMemory6CStagePci(0x30, stage, s_FS_USB_Process_cpp, 0x57);
        *reinterpret_cast<void**>(Ptr(this, 0x60A4) + index * 4) = hdr;

        memcpy(tmp, usb->m_data, usb->m_sizeBytes);
        for (int i = 0; i < 8; i++) {
            tmp[i] = BSWAP16(tmp[i]);
        }
        tmp[0x10] = BSWAP16(tmp[0x10]);
        tmp[0x11] = BSWAP16(tmp[0x11]);

        DCFlushRange(tmp, 0x30);
        memcpy(hdr, tmp, 0x30);

        void* texData = __nwa__FUlPQ27CMemory6CStagePci(usb->m_sizeBytes - 0x30, stage, s_FS_USB_Process_cpp, 0x6C);
        *reinterpret_cast<void**>(Ptr(this, 0x60E4) + index * 4) = texData;
        memcpy(texData, tmp + 0x18, usb->m_sizeBytes - 0x30);
        DCFlushRange(texData, usb->m_sizeBytes - 0x30);

        GXTexObj* texObj = static_cast<GXTexObj*>(__nw__FUlPQ27CMemory6CStagePci(0x20, stage, s_FS_USB_Process_cpp, 0x73));
        *reinterpret_cast<void**>(Ptr(this, 0x6064) + index * 4) = texObj;
        GXInitTexObj(texObj, texData, tmp[2], tmp[3], GX_TF_RGBA8, GX_CLAMP, GX_CLAMP, GX_FALSE);

        *Ptr(this, 0x6124) = index + 1;
        if (tmp != 0) {
            __dla__FPv(tmp);
        }
        break;
    }
    case 6:
        U32At(this, 0x61B8) = 0;
        break;
    case 10:
        funny->ClearAnmData();
        if (PtrAt(this, 0x6134) != 0) {
            __dla__FPv(PtrAt(this, 0x6134));
            PtrAt(this, 0x6134) = 0;
        }
        memset(funny, 0, 0x30);
        memcpy(Ptr(this, 0x6128), usb->m_data, 0x10);
        U32At(this, 0x6128) = BSWAP32(U32At(this, 0x6128));
        U16At(this, 0x612C) = BSWAP16(U16At(this, 0x612C));
        U16At(this, 0x612E) = BSWAP16(U16At(this, 0x612E));
        U16At(this, 0x6130) = BSWAP16(U16At(this, 0x6130));
        U16At(this, 0x6132) = BSWAP16(U16At(this, 0x6132));
        PtrAt(this, 0x6134) = 0;
        DCStoreRange(Ptr(this, 0x6128), usb->m_sizeBytes);
        break;
    case 11: {
        u8* animData = static_cast<u8*>(__nwa__FUlPQ27CMemory6CStagePci(usb->m_sizeBytes, stage, s_FS_USB_Process_cpp, 0x9C));
        PtrAt(this, 0x6134) = animData;

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
        memcpy(Ptr(this, 0x6178), usb->m_data, 0x40);
        U32At(this, 0x6178) = BSWAP32(U32At(this, 0x6178));
        U32At(this, 0x6180) = BSWAP32(U32At(this, 0x6180));
        U32At(this, 0x6184) = BSWAP32(U32At(this, 0x6184));
        U32At(this, 0x6188) = BSWAP32(U32At(this, 0x6188));
        U32At(this, 0x618C) = BSWAP32(U32At(this, 0x618C));
        U32At(this, 0x6190) = BSWAP32(U32At(this, 0x6190));
        U32At(this, 0x6194) = BSWAP32(U32At(this, 0x6194));
        U32At(this, 0x6198) = BSWAP32(U32At(this, 0x6198));
        U32At(this, 0x619C) = BSWAP32(U32At(this, 0x619C));
        U16At(this, 0x61A0) = BSWAP16(U16At(this, 0x61A0));
        U16At(this, 0x61A2) = BSWAP16(U16At(this, 0x61A2));
        U32At(this, 0x61A4) = BSWAP32(U32At(this, 0x61A4));
        U32At(this, 0x61A8) = BSWAP32(U32At(this, 0x61A8));
        DCStoreRange(Ptr(this, 0x6178), 0x40);

        GXColor clear = *reinterpret_cast<GXColor*>(Ptr(this, 0x617C));
        GXSetCopyClear(clear, 0xFFFFFF);

        U32At(this, 0x6138) = U32At(this, 0x6178);
        memcpy(Ptr(this, 0x613C), Ptr(this, 0x617C), 4);
        U32At(this, 0x6140) = U32At(this, 0x6180);
        U32At(this, 0x6144) = U32At(this, 0x6184);
        U32At(this, 0x6148) = U32At(this, 0x6188);
        U32At(this, 0x614C) = U32At(this, 0x618C);
        U32At(this, 0x6150) = U32At(this, 0x6190);
        U32At(this, 0x6154) = U32At(this, 0x6194);
        U32At(this, 0x6158) = U32At(this, 0x6198);
        U32At(this, 0x615C) = U32At(this, 0x619C);
        U16At(this, 0x6160) = *reinterpret_cast<u16*>(Ptr(this, 0x61A0));
        U16At(this, 0x6162) = *reinterpret_cast<u16*>(Ptr(this, 0x61A2));
        U32At(this, 0x6164) = U32At(this, 0x61A4);
        U32At(this, 0x6168) = U32At(this, 0x61A8);
        *Ptr(this, 0x616C) = *Ptr(this, 0x61AC);
        memcpy(Ptr(this, 0x616D), PtrConst(this, 0x61AD), 0x0B);
        break;
    }
    case 15: {
        u8 local[0x10];
        memcpy(local, usb->m_data, sizeof(local));

        U16At(this, 0x6050) = BSWAP16(*reinterpret_cast<u16*>(local + 0x0));
        U16At(this, 0x6052) = BSWAP16(*reinterpret_cast<u16*>(local + 0x2));
        U32At(this, 0x6054) = *reinterpret_cast<u32*>(local + 0x4);
        U16At(this, 0x6058) = BSWAP16(*reinterpret_cast<u16*>(local + 0x8));
        U32At(this, 0x605A) = *reinterpret_cast<u32*>(local + 0xA);
        U16At(this, 0x605E) = *reinterpret_cast<u16*>(local + 0xE);
        break;
    }
    case 16: {
        if (PtrAt(this, 0x6060) != 0) {
            __dla__FPv(PtrAt(this, 0x6060));
            PtrAt(this, 0x6060) = 0;
        }

        u8* meshData = static_cast<u8*>(__nwa__FUlPQ27CMemory6CStagePci(usb->m_sizeBytes, stage, s_FS_USB_Process_cpp, 0x106));
        memcpy(meshData, usb->m_data, usb->m_sizeBytes);
        *reinterpret_cast<u16*>(meshData + 0x0) = BSWAP16(*reinterpret_cast<u16*>(meshData + 0x0));
        *reinterpret_cast<u16*>(meshData + 0x2) = BSWAP16(*reinterpret_cast<u16*>(meshData + 0x2));

        int src2c = 0;
        int src24 = 0;
        int dst24 = 0;
        int dst2c = 0;
        for (int i = 0; i < S16At(this, 0x6052); i++) {
            if ((U16At(this, 0x6050) & 8) == 0) {
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

        PtrAt(this, 0x6060) = meshData;
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
