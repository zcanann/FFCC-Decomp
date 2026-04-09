#include "ffcc/ME_USB_process.h"
#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_camera.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/memory.h"
#include "ffcc/zlist.h"
#include "ffcc/system.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

#define BSWAP16(val) ((u16)(((u16)(val) << 8) | ((u16)(val) >> 8)))
#define BSWAP32(val) ((u32)(((u32)(val) << 24) | (((u32)(val) & 0xff00) << 8) | (((u32)(val) & 0xff0000) >> 8) | ((u32)(val) >> 24)))

extern "C" void ClearTextureData__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void* GetRsdItem__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void __dla__FPv(void* ptr);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory* memory, unsigned long size, CMemory::CStage* stage, char* file, int line, int align);
extern "C" void Printf__7CSystemFPce(CSystem* system, char* format, ...);
extern "C" void ResetRsdList__18CMaterialEditorPcsFP5ZLIST(CMaterialEditorPcs* materialEditorPcs, ZLIST* zlist);
extern "C" int AddRsdList__18CMaterialEditorPcsFP5ZLIST(CMaterialEditorPcs* materialEditorPcs, ZLIST* zlist);
extern "C" void SetRsdIndex__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);
extern "C" void SetRsdFlag__18CMaterialEditorPcsFv(CMaterialEditorPcs* materialEditorPcs);

static char s_ME_USB_process_cpp_801d7d78[] = "ME_USB_process.cpp";
static char s_MemAlloc_Error____size__d_801d7d8c[] = "MemAlloc Error : size=%d";

namespace {
struct ViewerSRT {
    float transX;
    float transY;
    float transZ;
    float rotX;
    float rotY;
    float rotZ;
    float scaleX;
    float scaleY;
    float scaleZ;
};

struct RSDITEM {
    u32 countA;
    u32 countB;
    u32 countC;
    void* ptrC;
    void* ptr10;
    void* ptr14;
    void* ptr18;
};

static inline u8* Ptr(CMaterialEditorPcs* self, u32 offset)
{
    return reinterpret_cast<u8*>(self) + offset;
}

static inline u32& U32At(CMaterialEditorPcs* self, u32 offset)
{
    return *reinterpret_cast<u32*>(Ptr(self, offset));
}

static inline u16& U16At(CMaterialEditorPcs* self, u32 offset)
{
    return *reinterpret_cast<u16*>(Ptr(self, offset));
}

static inline s16& S16At(CMaterialEditorPcs* self, u32 offset)
{
    return *reinterpret_cast<s16*>(Ptr(self, offset));
}

static inline void*& PtrAt(CMaterialEditorPcs* self, u32 offset)
{
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline char& S8At(CMaterialEditorPcs* self, u32 offset)
{
    return *reinterpret_cast<char*>(Ptr(self, offset));
}

static inline CMemory::CStage* MaterialEditorStage()
{
    return MaterialEditorPcs.m_stage;
}

static inline RSDITEM* GetRsdItem(CMaterialEditorPcs* self)
{
    return *reinterpret_cast<RSDITEM**>(GetRsdItem__18CMaterialEditorPcsFv(self));
}

static inline u32 TextureIndex(CMaterialEditorPcs* self)
{
    return static_cast<u32>(static_cast<unsigned char>(S8At(self, 0x3BC)));
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
extern "C" void MemFree__18CMaterialEditorPcsFPv(CMaterialEditorPcs* materialEditorPcs, void* ptr)
{
    if (ptr != nullptr) {
        Memory.Free(ptr);
    }
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
    CUSBStreamData& usb = materialEditorPcs->m_usbStream;

    switch (usb.m_packetCode) {
    case 1: {
        memcpy(Ptr(materialEditorPcs, 0xEC), usb.m_data, 0x120);
        for (int i = 0; i < 0x20; i++) {
            U32At(materialEditorPcs, 0xEC + i * 4) = BSWAP32(U32At(materialEditorPcs, 0xEC + i * 4));
        }
        memcpy(Ptr(materialEditorPcs, 0x20C), Ptr(materialEditorPcs, 0xEC), 0x30);
        DCStoreRange(Ptr(materialEditorPcs, 0xEC), 0x120);
        break;
    }
    case 3:
        usb.m_stageDefault = reinterpret_cast<CMemory::CStage*>(1);
        break;
    case 4:
        usb.m_stageDefault = 0;
        break;
    case 0x10: {
        ViewerSRT srt;
        Vec minPos;
        Vec maxPos;
        RSDITEM* rsdItem = GetRsdItem(materialEditorPcs);
        u32 size = usb.m_sizeBytes;
        u32 dataSize = size * 0xC;
        float* xyzData;

        if (rsdItem->ptr10 != 0) {
            __dla__FPv(rsdItem->ptr10);
            rsdItem->ptr10 = 0;
        }

        rsdItem->countA = size;
        rsdItem->ptr10 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, dataSize, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
        if (rsdItem->ptr10 == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, dataSize);
        }

        memcpy(rsdItem->ptr10, usb.m_data, dataSize);

        xyzData = reinterpret_cast<float*>(rsdItem->ptr10);
        for (u32 i = 0; i < size; i++) {
            u32 id = BSWAP32(*reinterpret_cast<u32*>(xyzData + 0));
            float y = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 1)));
            float z = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 2)));

            *reinterpret_cast<u32*>(xyzData + 0) = id;
            xyzData[1] = y;
            xyzData[2] = z;
            xyzData += 3;
        }
        DCStoreRange(rsdItem->ptr10, dataSize);

        materialEditorPcs->CreateBoundaryBox(minPos, maxPos, rsdItem->countA, reinterpret_cast<const Vec*>(rsdItem->ptr10));

        srt.transX = 0.0f;
        srt.transY = static_cast<float>(-static_cast<int>(maxPos.x - minPos.x) / 2);
        srt.transZ = static_cast<float>(-static_cast<int>(maxPos.y - minPos.y) * (static_cast<int>(maxPos.x - minPos.x) / 0x14) - 10);
        srt.rotX = 0.0f;
        srt.rotY = 0.0f;
        srt.rotZ = 0.0f;
        srt.scaleX = 1.0f;
        srt.scaleY = 1.0f;
        srt.scaleZ = 1.0f;
        CameraPcs.SetViewerSRT(reinterpret_cast<const SRT*>(&srt));
        break;
    }
    case 0x12: {
        RSDITEM* rsdItem = GetRsdItem(materialEditorPcs);
        u32 size = usb.m_sizeBytes;
        u32 dataSize = size * 0xC;
        float* xyzData;

        if (rsdItem->ptr14 != 0) {
            __dla__FPv(rsdItem->ptr14);
            rsdItem->ptr14 = 0;
        }

        rsdItem->countB = size;
        rsdItem->ptr14 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, dataSize, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
        if (rsdItem->ptr14 == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, dataSize);
        }

        memcpy(rsdItem->ptr14, usb.m_data, dataSize);

        xyzData = reinterpret_cast<float*>(rsdItem->ptr14);
        for (u32 i = 0; i < size; i++) {
            u32 id = BSWAP32(*reinterpret_cast<u32*>(xyzData + 0));
            float y = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 1)));
            float z = -static_cast<float>(BSWAP32(*reinterpret_cast<u32*>(xyzData + 2)));

            *reinterpret_cast<u32*>(xyzData + 0) = id;
            xyzData[1] = y;
            xyzData[2] = z;
            xyzData += 3;
        }
        DCStoreRange(rsdItem->ptr14, dataSize);
        break;
    }
    case 0x13: {
        RSDITEM* rsdItem = GetRsdItem(materialEditorPcs);
        u32 size = usb.m_sizeBytes;
        u32 dataSize = size * 0x70;

        if (rsdItem->ptr18 != 0) {
            __dla__FPv(rsdItem->ptr18);
            rsdItem->ptr18 = 0;
        }

        rsdItem->countC = size;
        rsdItem->ptr18 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, dataSize, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
        if (rsdItem->ptr18 == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, dataSize);
        }

        memset(rsdItem->ptr18, 0, dataSize);
        memcpy(rsdItem->ptr18, usb.m_data, dataSize);

        for (u32 i = 0; i < size; i++) {
            u8* data = reinterpret_cast<u8*>(rsdItem->ptr18) + i * 0x70;

            *reinterpret_cast<u16*>(data + 0x00) = BSWAP16(*reinterpret_cast<u16*>(data + 0x00));
            *reinterpret_cast<u16*>(data + 0x02) = BSWAP16(*reinterpret_cast<u16*>(data + 0x02));
            *reinterpret_cast<u32*>(data + 0x04) = BSWAP32(*reinterpret_cast<u32*>(data + 0x04));
            *reinterpret_cast<u16*>(data + 0x08) = BSWAP16(*reinterpret_cast<u16*>(data + 0x08));
            *reinterpret_cast<u16*>(data + 0x0A) = BSWAP16(*reinterpret_cast<u16*>(data + 0x0A));
            *reinterpret_cast<u16*>(data + 0x0C) = BSWAP16(*reinterpret_cast<u16*>(data + 0x0C));
            *reinterpret_cast<u16*>(data + 0x0E) = BSWAP16(*reinterpret_cast<u16*>(data + 0x0E));
            *reinterpret_cast<u16*>(data + 0x10) = BSWAP16(*reinterpret_cast<u16*>(data + 0x10));
            *reinterpret_cast<u16*>(data + 0x12) = BSWAP16(*reinterpret_cast<u16*>(data + 0x12));
            *reinterpret_cast<u16*>(data + 0x14) = BSWAP16(*reinterpret_cast<u16*>(data + 0x14));
            *reinterpret_cast<u16*>(data + 0x16) = BSWAP16(*reinterpret_cast<u16*>(data + 0x16));
            *reinterpret_cast<u16*>(data + 0x1C) = BSWAP16(*reinterpret_cast<u16*>(data + 0x1C));
            *reinterpret_cast<u16*>(data + 0x1E) = BSWAP16(*reinterpret_cast<u16*>(data + 0x1E));
            *reinterpret_cast<u16*>(data + 0x20) = BSWAP16(*reinterpret_cast<u16*>(data + 0x20));
            *reinterpret_cast<u16*>(data + 0x22) = BSWAP16(*reinterpret_cast<u16*>(data + 0x22));
            *reinterpret_cast<u16*>(data + 0x24) = BSWAP16(*reinterpret_cast<u16*>(data + 0x24));
            *reinterpret_cast<u16*>(data + 0x26) = BSWAP16(*reinterpret_cast<u16*>(data + 0x26));
            *reinterpret_cast<u16*>(data + 0x28) = BSWAP16(*reinterpret_cast<u16*>(data + 0x28));
            *reinterpret_cast<u16*>(data + 0x2A) = BSWAP16(*reinterpret_cast<u16*>(data + 0x2A));
            *reinterpret_cast<u16*>(data + 0x2C) = BSWAP16(*reinterpret_cast<u16*>(data + 0x2C));
            *reinterpret_cast<u16*>(data + 0x2E) = BSWAP16(*reinterpret_cast<u16*>(data + 0x2E));
        }
        DCStoreRange(rsdItem->ptr18, dataSize);
        break;
    }
    case 0x20: {
        u32 textureIndex = TextureIndex(materialEditorPcs);
        u32 size = usb.m_sizeBytes;
        s16* headerBuffer = static_cast<s16*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, size, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0));
        void* headerDst = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, 0x10, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);

        if (headerBuffer == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, size);
        }
        if (headerDst == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, 0x10);
        }

        PtrAt(materialEditorPcs, 0x27C + textureIndex * 4) = headerDst;
        memcpy(headerBuffer, usb.m_data, size);
        for (int i = 0; i < 8; i++) {
            headerBuffer[i] = BSWAP16(headerBuffer[i]);
        }
        DCFlushRange(headerBuffer, 0x10);
        memcpy(headerDst, headerBuffer, 0x10);

        s16 format = headerBuffer[1];
        if (format == 0x20) {
            void* texData = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                &Memory, size - 0x10, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
            if (texData == 0) {
                Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, size - 0x10);
            }
            PtrAt(materialEditorPcs, 0x2BC + textureIndex * 4) = texData;
            memcpy(texData, headerBuffer + 8, size - 0x10);
            DCFlushRange(texData, size - 0x10);
        } else if ((format == 4) || (format == 8)) {
            int tlutEntries = format == 4 ? 0x10 : 0x100;
            int imageDataSize = static_cast<int>(size) - 0x10 - tlutEntries * 4;
            void* texData = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                &Memory, imageDataSize, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
            void* tlutData = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                &Memory, tlutEntries * 4, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
            int tlutOffset = format == 4 ? (headerBuffer[2] * headerBuffer[3]) / 2 : headerBuffer[2] * headerBuffer[3];

            if (texData == 0) {
                Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, imageDataSize);
            }
            if (tlutData == 0) {
                Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, tlutEntries * 4);
            }

            PtrAt(materialEditorPcs, 0x2BC + textureIndex * 4) = texData;
            PtrAt(materialEditorPcs, 0x2FC + textureIndex * 4) = tlutData;
            memcpy(texData, headerBuffer + 8, imageDataSize);
            memcpy(tlutData, reinterpret_cast<u8*>(headerBuffer) + tlutOffset + 0x10, tlutEntries * 4);
            DCFlushRange(texData, imageDataSize);
            DCFlushRange(tlutData, tlutEntries * 4);
        }

        void* texObj = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, 0x20, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
        if (texObj == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, 0x20);
        }
        PtrAt(materialEditorPcs, 0x23C + textureIndex * 4) = texObj;

        void* tlutObj0 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, 0xC, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
        if (tlutObj0 == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, 0xC);
        }
        PtrAt(materialEditorPcs, 0x33C + textureIndex * 4) = tlutObj0;

        void* tlutObj1 = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, 0xC, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0);
        if (tlutObj1 == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, 0xC);
        }
        PtrAt(materialEditorPcs, 0x37C + textureIndex * 4) = tlutObj1;

        u32 widthFactor = static_cast<u32>(headerBuffer[2]);
        u32 heightFactor = static_cast<u32>(headerBuffer[3]);
        GXBool isPowerOfTwo = GX_TRUE;

        while ((widthFactor & 1) == 0) {
            widthFactor >>= 1;
        }
        while ((heightFactor & 1) == 0) {
            heightFactor >>= 1;
        }
        if ((widthFactor != 1) || (heightFactor != 1)) {
            isPowerOfTwo = GX_FALSE;
        }

        if (format == 0x20) {
            GXInitTexObj(static_cast<GXTexObj*>(PtrAt(materialEditorPcs, 0x23C + textureIndex * 4)),
                PtrAt(materialEditorPcs, 0x2BC + textureIndex * 4), headerBuffer[2], headerBuffer[3],
                GX_TF_RGBA8, static_cast<GXTexWrapMode>(isPowerOfTwo), static_cast<GXTexWrapMode>(isPowerOfTwo), GX_FALSE);
        } else if ((format == 4) || (format == 8)) {
            int tlutEntries = format == 4 ? 0x10 : 0x100;

            GXInitTlutObj(static_cast<GXTlutObj*>(PtrAt(materialEditorPcs, 0x33C + textureIndex * 4)),
                PtrAt(materialEditorPcs, 0x2FC + textureIndex * 4), GX_TL_IA8, tlutEntries);
            GXInitTlutObj(static_cast<GXTlutObj*>(PtrAt(materialEditorPcs, 0x37C + textureIndex * 4)),
                reinterpret_cast<u8*>(PtrAt(materialEditorPcs, 0x2FC + textureIndex * 4)) + tlutEntries * 2, GX_TL_IA8, tlutEntries);
            GXLoadTlut(static_cast<GXTlutObj*>(PtrAt(materialEditorPcs, 0x33C + textureIndex * 4)), GX_TLUT0);
            GXLoadTlut(static_cast<GXTlutObj*>(PtrAt(materialEditorPcs, 0x37C + textureIndex * 4)), GX_TLUT1);
            GXInitTexObjCI(static_cast<GXTexObj*>(PtrAt(materialEditorPcs, 0x23C + textureIndex * 4)),
                PtrAt(materialEditorPcs, 0x2BC + textureIndex * 4), headerBuffer[2], headerBuffer[3],
                static_cast<GXCITexFmt>(format == 4 ? GX_CTF_R4 : GX_CTF_RA4),
                static_cast<GXTexWrapMode>(isPowerOfTwo), static_cast<GXTexWrapMode>(isPowerOfTwo),
                GX_FALSE, static_cast<u32>(GX_TLUT0));
        }

        if (headerBuffer != 0) {
            __dla__FPv(headerBuffer);
        }
        S8At(materialEditorPcs, 0x3BC) = S8At(materialEditorPcs, 0x3BC) + 1;
        break;
    }
    case 0x31: {
        RSDITEM* rsdItem = GetRsdItem(materialEditorPcs);
        u32 size = usb.m_sizeBytes;
        u8* dstBuffer = reinterpret_cast<u8*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, size, MaterialEditorStage(), s_ME_USB_process_cpp_801d7d78, 0x31, 0));

        if (dstBuffer == 0) {
            Printf__7CSystemFPce(&System, s_MemAlloc_Error____size__d_801d7d8c, size);
        }

        memcpy(dstBuffer, usb.m_data, size);

        u8* target = reinterpret_cast<u8*>(rsdItem->ptr18);
        for (u32 i = 0; i < size; i++) {
            target[i * 0x70 + 0x1A] = dstBuffer[i];
        }

        if (dstBuffer != 0) {
            __dla__FPv(dstBuffer);
        }
        break;
    }
    case 0x21:
        U32At(materialEditorPcs, 0xE8) = 1;
        ClearTextureData__18CMaterialEditorPcsFv(materialEditorPcs);
        break;
    case 0x22:
        U32At(materialEditorPcs, 0xE8) = 0;
        break;
    case 0x40:
        ResetRsdList__18CMaterialEditorPcsFP5ZLIST(materialEditorPcs, reinterpret_cast<ZLIST*>(Ptr(materialEditorPcs, 0xC8)));
        break;
    case 0x41:
        AddRsdList__18CMaterialEditorPcsFP5ZLIST(materialEditorPcs, reinterpret_cast<ZLIST*>(Ptr(materialEditorPcs, 0xC8)));
        break;
    case 0x42:
        memcpy(&usb.m_stageLoad, usb.m_data, 4);
        usb.m_stageLoad = reinterpret_cast<CMemory::CStage*>(BSWAP32(reinterpret_cast<u32>(usb.m_stageLoad)));
        DCStoreRange(&usb.m_stageLoad, 4);
        SetRsdIndex__18CMaterialEditorPcsFv(materialEditorPcs);
        break;
    case 0x43:
        memcpy(Ptr(materialEditorPcs, 0xC0), usb.m_data, 4);
        U32At(materialEditorPcs, 0xC0) = BSWAP32(U32At(materialEditorPcs, 0xC0));
        SetRsdFlag__18CMaterialEditorPcsFv(materialEditorPcs);
        DCStoreRange(Ptr(materialEditorPcs, 0xC0), 4);
        break;
    }
}
