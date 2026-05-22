#include "ffcc/ME_USB_process.h"
#include "ffcc/p_camera.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/memory.h"
#include "ffcc/zlist.h"
#include "ffcc/system.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

extern "C" const char s_ME_USB_process_cpp_801d7d78[] = "ME_USB_process.cpp";
extern "C" const char s_MemAlloc_Error____size__d_801d7d8c[] = "MemAlloc Error!!! size=%d\n";

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

static inline char& S8At(CMaterialEditorPcs* self, u32 offset)
{
    return *reinterpret_cast<char*>(Ptr(self, offset));
}

static inline CMemory::CStage* MaterialEditorStage()
{
    return MaterialEditorPcs.m_stage;
}

static inline u32 LoadSwap32(u32 value)
{
    return __lwbrx(&value, 0);
}

static inline void StoreSwap32(u32* value)
{
    u32 raw = *value;

    *value = __lwbrx(&raw, 0);
}

static inline void StoreSwapNegFloat(f32* value)
{
    f32 raw = *value;
    u32 swapped = __lwbrx(&raw, 0);

    *value = -*reinterpret_cast<f32*>(&swapped);
}

static inline u16 LoadSwapU16(u16 value)
{
    return __lhbrx(&value, 0);
}

}

/*
 * --INFO--
 * PAL Address: 0x8004CA08
 * PAL Size: 4784b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::SetUSBData()
{
    CUSBStreamData& usb = m_usbStream;

    switch (usb.m_packetCode) {
    case 0x21:
        m_displayTextureEnabled = 1;
        ClearTextureData();
        break;
    case 0x22:
        m_displayTextureEnabled = 0;
        break;
    case 3:
        usb.m_stageDefault = reinterpret_cast<CMemory::CStage*>(1);
        break;
    case 4:
        usb.m_stageDefault = 0;
        break;
    case 0x40:
        ResetRsdList(&m_zlist1);
        break;
    case 0x41:
        AddRsdList(&m_zlist1);
        break;
    case 0x10: {
        ViewerSRT srt;
        Vec minPos;
        Vec maxPos;
        RSDITEM* rsdItem = GetRsdItem()->rsdItem;
        u32* xyzData;

        if (rsdItem->ptr10 != 0) {
            delete[] static_cast<u8*>(rsdItem->ptr10);
            rsdItem->ptr10 = 0;
        }

        rsdItem->countA = usb.m_sizeBytes;
        void* allocData = Memory._Alloc(
            usb.m_sizeBytes * 0xC, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
        if (allocData == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), usb.m_sizeBytes * 0xC);
        }
        rsdItem->ptr10 = allocData;

        memcpy(rsdItem->ptr10, usb.m_data, usb.m_sizeBytes * 0xC);

        xyzData = reinterpret_cast<u32*>(rsdItem->ptr10);
        for (u32 i = 0, offset = 0; i < usb.m_sizeBytes; i++, offset += 0xC) {
            u32* item = reinterpret_cast<u32*>(reinterpret_cast<u8*>(xyzData) + offset);
            StoreSwap32(item + 0);
            StoreSwapNegFloat(reinterpret_cast<f32*>(item + 1));
            StoreSwapNegFloat(reinterpret_cast<f32*>(item + 2));
        }
        DCStoreRange(rsdItem->ptr10, usb.m_sizeBytes * 0xC);

        CreateBoundaryBox(minPos, maxPos, rsdItem->countA, reinterpret_cast<const Vec*>(rsdItem->ptr10));

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
    case 0x13: {
        RSDITEM* rsdItem = GetRsdItem()->rsdItem;

        if (rsdItem->ptr18 != 0) {
            delete[] static_cast<u8*>(rsdItem->ptr18);
            rsdItem->ptr18 = 0;
        }

        rsdItem->countC = usb.m_sizeBytes;
        void* allocData = Memory._Alloc(
            usb.m_sizeBytes * 0x70, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
        if (allocData == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), usb.m_sizeBytes * 0x70);
        }
        rsdItem->ptr18 = allocData;

        memset(rsdItem->ptr18, 0, usb.m_sizeBytes * 0x70);
        memcpy(rsdItem->ptr18, usb.m_data, usb.m_sizeBytes * 0x70);

        for (u32 i = 0; i < usb.m_sizeBytes; i++) {
            u8* data = reinterpret_cast<u8*>(rsdItem->ptr18) + i * 0x70;

            *reinterpret_cast<u16*>(data + 0x00) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x00));
            *reinterpret_cast<u16*>(data + 0x02) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x02));
            StoreSwap32(reinterpret_cast<u32*>(data + 0x04));
            *reinterpret_cast<u16*>(data + 0x08) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x08));
            *reinterpret_cast<u16*>(data + 0x0A) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x0A));
            *reinterpret_cast<u16*>(data + 0x0C) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x0C));
            *reinterpret_cast<u16*>(data + 0x0E) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x0E));
            *reinterpret_cast<u16*>(data + 0x10) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x10));
            *reinterpret_cast<u16*>(data + 0x12) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x12));
            *reinterpret_cast<u16*>(data + 0x14) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x14));
            *reinterpret_cast<u16*>(data + 0x16) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x16));
            *reinterpret_cast<u16*>(data + 0x1C) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x1C));
            *reinterpret_cast<u16*>(data + 0x1E) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x1E));
            *reinterpret_cast<u16*>(data + 0x20) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x20));
            *reinterpret_cast<u16*>(data + 0x22) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x22));
            *reinterpret_cast<u16*>(data + 0x24) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x24));
            *reinterpret_cast<u16*>(data + 0x26) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x26));
            *reinterpret_cast<u16*>(data + 0x28) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x28));
            *reinterpret_cast<u16*>(data + 0x2A) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x2A));
            *reinterpret_cast<u16*>(data + 0x2C) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x2C));
            *reinterpret_cast<u16*>(data + 0x2E) = LoadSwapU16(*reinterpret_cast<u16*>(data + 0x2E));
        }
        DCStoreRange(rsdItem->ptr18, usb.m_sizeBytes * 0x70);
        break;
    }
    case 0x42:
        memcpy(&usb.m_stageLoad, usb.m_data, 4);
        usb.m_stageLoad = reinterpret_cast<CMemory::CStage*>(LoadSwap32(reinterpret_cast<u32>(usb.m_stageLoad)));
        DCStoreRange(&usb.m_stageLoad, 4);
        SetRsdIndex();
        break;
    case 0x43:
        memcpy(&m_rsdFlag, usb.m_data, 4);
        m_rsdFlag = LoadSwap32(m_rsdFlag);
        SetRsdFlag();
        DCStoreRange(&m_rsdFlag, 4);
        break;
    case 0x12: {
        RSDITEM* rsdItem = GetRsdItem()->rsdItem;
        u32* xyzData;

        if (rsdItem->ptr14 != 0) {
            delete[] static_cast<u8*>(rsdItem->ptr14);
            rsdItem->ptr14 = 0;
        }

        rsdItem->countB = usb.m_sizeBytes;
        void* allocData = Memory._Alloc(
            usb.m_sizeBytes * 0xC, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
        if (allocData == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), usb.m_sizeBytes * 0xC);
        }
        rsdItem->ptr14 = allocData;

        memcpy(rsdItem->ptr14, usb.m_data, usb.m_sizeBytes * 0xC);

        xyzData = reinterpret_cast<u32*>(rsdItem->ptr14);
        for (u32 i = 0, offset = 0; i < usb.m_sizeBytes; i++, offset += 0xC) {
            u32* item = reinterpret_cast<u32*>(reinterpret_cast<u8*>(xyzData) + offset);
            StoreSwap32(item + 0);
            StoreSwapNegFloat(reinterpret_cast<f32*>(item + 1));
            StoreSwapNegFloat(reinterpret_cast<f32*>(item + 2));
        }
        DCStoreRange(rsdItem->ptr14, usb.m_sizeBytes * 0xC);
        break;
    }
    case 1: {
        memcpy(Ptr(this, 0xEC), usb.m_data, 0x120);
        StoreSwap32(&U32At(this, 0xEC));
        StoreSwap32(&U32At(this, 0xF0));
        StoreSwap32(&U32At(this, 0xF4));
        StoreSwap32(&U32At(this, 0xF8));
        StoreSwap32(&U32At(this, 0xFC));
        StoreSwap32(&U32At(this, 0x100));
        StoreSwap32(&U32At(this, 0x104));
        StoreSwap32(&U32At(this, 0x108));
        StoreSwap32(&U32At(this, 0x10C));
        StoreSwap32(&U32At(this, 0x110));
        StoreSwap32(&U32At(this, 0x114));
        StoreSwap32(&U32At(this, 0x118));
        StoreSwap32(&U32At(this, 0x11C));
        StoreSwap32(&U32At(this, 0x120));
        StoreSwap32(&U32At(this, 0x124));
        StoreSwap32(&U32At(this, 0x128));
        StoreSwap32(&U32At(this, 0x12C));
        StoreSwap32(&U32At(this, 0x130));
        StoreSwap32(&U32At(this, 0x134));
        StoreSwap32(&U32At(this, 0x138));
        StoreSwap32(&U32At(this, 0x13C));
        StoreSwap32(&U32At(this, 0x140));
        StoreSwap32(&U32At(this, 0x144));
        StoreSwap32(&U32At(this, 0x148));
        StoreSwap32(&U32At(this, 0x14C));
        StoreSwap32(&U32At(this, 0x150));
        StoreSwap32(&U32At(this, 0x154));
        StoreSwap32(&U32At(this, 0x158));
        StoreSwap32(&U32At(this, 0x15C));
        StoreSwap32(&U32At(this, 0x160));
        StoreSwap32(&U32At(this, 0x164));
        StoreSwap32(&this->field_0x168);
        memcpy(Ptr(this, 0x20C), Ptr(this, 0xEC), 0x30);
        DCStoreRange(Ptr(this, 0xEC), 0x120);
        break;
    }
    case 0x31: {
        u8* dstBuffer = static_cast<u8*>(
            Memory._Alloc(usb.m_sizeBytes, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0));

        if (dstBuffer == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), usb.m_sizeBytes);
        }

        RSDITEM* rsdItem = this->GetRsdItem()->rsdItem;
        memcpy(dstBuffer, usb.m_data, usb.m_sizeBytes);

        u8* target = reinterpret_cast<u8*>(rsdItem->ptr18);
        for (u32 i = 0; i < usb.m_sizeBytes; i++) {
            target[i * 0x70 + 0x1A] = dstBuffer[i];
        }

        if (dstBuffer != 0) {
            delete[] dstBuffer;
        }
        break;
    }
    case 0x20: {
        u32 size = usb.m_sizeBytes;
        s16* headerBuffer = static_cast<s16*>(
            Memory._Alloc(size, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0));

        if (headerBuffer == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), size);
        }

        void* headerDst =
            Memory._Alloc(0x10, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
        if (headerDst == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), 0x10);
        }

        this->m_textureHeader[this->m_loadedTextureCount] = static_cast<s16*>(headerDst);
        memcpy(headerBuffer, usb.m_data, size);
        headerBuffer[0] = LoadSwapU16(headerBuffer[0]);
        headerBuffer[1] = LoadSwapU16(headerBuffer[1]);
        headerBuffer[2] = LoadSwapU16(headerBuffer[2]);
        headerBuffer[3] = LoadSwapU16(headerBuffer[3]);
        headerBuffer[4] = LoadSwapU16(headerBuffer[4]);
        headerBuffer[5] = LoadSwapU16(headerBuffer[5]);
        headerBuffer[6] = LoadSwapU16(headerBuffer[6]);
        headerBuffer[7] = LoadSwapU16(headerBuffer[7]);
        DCFlushRange(headerBuffer, 0x10);
        memcpy(this->m_textureHeader[this->m_loadedTextureCount], headerBuffer, 0x10);

        s16 format = headerBuffer[1];
        if (format == 0x20) {
            void* texData = Memory._Alloc(
                size - 0x10, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
            if (texData == 0) {
                System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), size - 0x10);
            }
            this->m_textureData[this->m_loadedTextureCount] = texData;
            memcpy(texData, headerBuffer + 8, size - 0x10);
            DCFlushRange(texData, size - 0x10);
        } else if ((format == 4) || (format == 8)) {
            int tlutEntries = format == 4 ? 0x10 : 0x100;
            int tlutDataSize = tlutEntries * 4;
            int imageDataSize = static_cast<int>(size) - 0x10 - tlutDataSize;
            void* texData = Memory._Alloc(
                imageDataSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);

            if (texData == 0) {
                System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), imageDataSize);
            }
            this->m_textureData[this->m_loadedTextureCount] = texData;
            memcpy(texData, headerBuffer + 8, imageDataSize);
            DCFlushRange(texData, imageDataSize);

            void* tlutData = Memory._Alloc(
                tlutDataSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
            if (tlutData == 0) {
                System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), tlutDataSize);
            }
            this->m_tlutData[this->m_loadedTextureCount] = tlutData;

            int tlutOffset = format == 4 ? (headerBuffer[2] * headerBuffer[3]) / 2 : headerBuffer[2] * headerBuffer[3];
            memcpy(tlutData, reinterpret_cast<u8*>(headerBuffer) + tlutOffset + 0x10, tlutDataSize);
            DCFlushRange(tlutData, tlutDataSize);
        }

        void* texObj =
            Memory._Alloc(0x20, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
        if (texObj == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), 0x20);
        }
        this->m_texObj[this->m_loadedTextureCount] = static_cast<GXTexObj*>(texObj);

        void* tlutObj0 =
            Memory._Alloc(0xC, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
        if (tlutObj0 == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), 0xC);
        }
        this->m_tlutObj0[this->m_loadedTextureCount] = static_cast<GXTlutObj*>(tlutObj0);

        void* tlutObj1 =
            Memory._Alloc(0xC, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp_801d7d78), 0x31, 0);
        if (tlutObj1 == 0) {
            System.Printf(const_cast<char*>(s_MemAlloc_Error____size__d_801d7d8c), 0xC);
        }
        this->m_tlutObj1[this->m_loadedTextureCount] = static_cast<GXTlutObj*>(tlutObj1);

        u32 widthFactor = static_cast<u32>(headerBuffer[2]);
        u32 heightFactor = static_cast<u32>(headerBuffer[3]);
        GXBool isPowerOfTwo = GX_TRUE;

        while ((widthFactor & 1) == 0) {
            widthFactor >>= 1;
        }
        while ((heightFactor & 1) == 0) {
            heightFactor >>= 1;
        }
        if ((heightFactor != 1) || (heightFactor != 1)) {
            isPowerOfTwo = GX_FALSE;
        }

        if (format == 0x20) {
            GXInitTexObj(this->m_texObj[this->m_loadedTextureCount],
                this->m_textureData[this->m_loadedTextureCount], headerBuffer[2], headerBuffer[3],
                GX_TF_RGBA8, static_cast<GXTexWrapMode>(isPowerOfTwo), static_cast<GXTexWrapMode>(isPowerOfTwo), GX_FALSE);
        } else if ((format == 4) || (format == 8)) {
            int tlutEntries = format == 4 ? 0x10 : 0x100;

            GXInitTlutObj(this->m_tlutObj0[this->m_loadedTextureCount],
                this->m_tlutData[this->m_loadedTextureCount], GX_TL_IA8, tlutEntries);
            GXInitTlutObj(this->m_tlutObj1[this->m_loadedTextureCount],
                reinterpret_cast<u8*>(this->m_tlutData[this->m_loadedTextureCount]) + tlutEntries * 2, GX_TL_IA8, tlutEntries);
            GXLoadTlut(this->m_tlutObj0[this->m_loadedTextureCount], GX_TLUT0);
            GXLoadTlut(this->m_tlutObj1[this->m_loadedTextureCount], GX_TLUT1);
            GXInitTexObjCI(this->m_texObj[this->m_loadedTextureCount],
                this->m_textureData[this->m_loadedTextureCount], headerBuffer[2], headerBuffer[3],
                static_cast<GXCITexFmt>(format == 4 ? GX_TF_C4 : GX_TF_C8),
                static_cast<GXTexWrapMode>(isPowerOfTwo), static_cast<GXTexWrapMode>(isPowerOfTwo),
                GX_FALSE, static_cast<u32>(GX_TLUT0));
        }

        if (headerBuffer != 0) {
            delete[] reinterpret_cast<u8*>(headerBuffer);
        }
        S8At(this, 0x3BC) = S8At(this, 0x3BC) + 1;
        break;
    }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004DCB8
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::MemFree(void* ptr)
{
    if (ptr != nullptr) {
        Memory.Free(ptr);
    }
}
