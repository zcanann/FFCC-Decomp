#include "ffcc/ME_USB_process.h"
#include "ffcc/p_camera.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/memory.h"
#include "ffcc/zlist.h"
#include "ffcc/system.h"
#include "dolphin/gx/GXTexture.h"
#include "dolphin/os/OSCache.h"

#include <string.h>

static const char s_ME_USB_process_cpp[] = "ME_USB_process.cpp";
extern "C" const char sMemAllocErrorSizeFmt[] = "MemAlloc Error!!! size=%d\n";

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

static inline void StoreSwapFloat(f32* value)
{
    f32 raw = *value;
    u32 swapped = __lwbrx(&raw, 0);

    *value = *reinterpret_cast<f32*>(&swapped);
}

static inline void StoreSwapNegFloat(f32* value)
{
    f32 raw = *value;
    u32 swapped = __lwbrx(&raw, 0);

    *value = -*reinterpret_cast<f32*>(&swapped);
}

static inline void StoreSwapU16(u16* value)
{
    u16 raw = *value;

    *value = __lhbrx(&raw, 0);
}

static inline void StoreSwapS16(s16* value)
{
    s16 raw = *value;

    *value = __lhbrx(&raw, 0);
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
    CUSBStreamDataState& usbState = m_usbStreamState;

    switch (usb.m_packetCode) {
    case 0x21:
        m_displayTextureEnabled = 1;
        ClearTextureData();
        break;
    case 0x22:
        m_displayTextureEnabled = 0;
        break;
    case 3:
        usbState.m_stageDefault = reinterpret_cast<CMemory::CStage*>(1);
        break;
    case 4:
        usbState.m_stageDefault = 0;
        break;
    case 0x40:
        ResetRsdList(&m_zlist1);
        break;
    case 0x41:
        AddRsdList(&m_zlist1);
        break;
    case 0x10: {
        extern const float kMapEditorZero;
        extern const float kMapEditorOne;
        ViewerSRT srt;
        Vec minPos;
        Vec maxPos;
        RSDITEM* rsdItem = GetRsdItem()->rsdItem;

        if (rsdItem->ptr10 != 0) {
            delete[] static_cast<u8*>(rsdItem->ptr10);
            rsdItem->ptr10 = 0;
        }

        rsdItem->countA = usb.m_sizeBytes;
        u32 allocSize = usb.m_sizeBytes * 0xC;
        void* allocData = Memory._Alloc(
            allocSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
        if (allocData == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), allocSize);
        }
        rsdItem->ptr10 = allocData;

        memcpy(rsdItem->ptr10, usb.m_data, usb.m_sizeBytes * 0xC);

        for (u32 offset = 0, i = 0; i < usb.m_sizeBytes; offset += 0xC, i++) {
            StoreSwapFloat(reinterpret_cast<f32*>(reinterpret_cast<u8*>(rsdItem->ptr10) + offset + 0x0));
            StoreSwapNegFloat(reinterpret_cast<f32*>(reinterpret_cast<u8*>(rsdItem->ptr10) + offset + 0x4));
            StoreSwapNegFloat(reinterpret_cast<f32*>(reinterpret_cast<u8*>(rsdItem->ptr10) + offset + 0x8));
        }
        DCStoreRange(rsdItem->ptr10, usb.m_sizeBytes * 0xC);

        CreateBoundaryBox(minPos, maxPos, rsdItem->countA, reinterpret_cast<const Vec*>(rsdItem->ptr10));

        s32 xDiff = static_cast<s32>(maxPos.y - minPos.y);
        s32 yDiff = static_cast<s32>(maxPos.z - minPos.z);

        srt.transX = kMapEditorZero;
        srt.transZ = kMapEditorZero;
        srt.transY = kMapEditorZero;
        srt.rotZ = kMapEditorZero;
        srt.rotY = kMapEditorZero;
        srt.rotX = kMapEditorZero;
        srt.scaleZ = kMapEditorOne;
        srt.scaleY = kMapEditorOne;
        srt.scaleX = kMapEditorOne;
        srt.transX = kMapEditorZero;
        srt.transY = static_cast<f32>(-xDiff / 2);
        srt.transZ = static_cast<f32>(-yDiff * (xDiff / 0x14) - 10);
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
        u32 allocSize = usb.m_sizeBytes * 0x70;
        void* allocData = Memory._Alloc(
            allocSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
        if (allocData == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), allocSize);
        }
        rsdItem->ptr18 = allocData;

        memset(rsdItem->ptr18, 0, usb.m_sizeBytes * 0x70);
        memcpy(rsdItem->ptr18, usb.m_data, usb.m_sizeBytes * 0x70);

        for (u32 offset = 0, i = 0; i < usb.m_sizeBytes; offset += 0x70, i++) {
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x00));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x02));
            StoreSwap32(reinterpret_cast<u32*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x04));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x08));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x0A));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x0C));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x0E));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x10));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x12));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x14));
            StoreSwapU16(reinterpret_cast<u16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x16));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x1C));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x1E));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x20));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x22));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x24));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x26));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x28));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x2A));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x2C));
            StoreSwapS16(reinterpret_cast<s16*>(reinterpret_cast<u8*>(rsdItem->ptr18) + offset + 0x2E));
        }
        DCStoreRange(rsdItem->ptr18, usb.m_sizeBytes * 0x70);
        break;
    }
    case 0x42:
        memcpy(&usbState.m_stageLoad, usb.m_data, 4);
        usbState.m_stageLoad = reinterpret_cast<CMemory::CStage*>(LoadSwap32(reinterpret_cast<u32>(usbState.m_stageLoad)));
        DCStoreRange(&usbState.m_stageLoad, 4);
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

        if (rsdItem->ptr14 != 0) {
            delete[] static_cast<u8*>(rsdItem->ptr14);
            rsdItem->ptr14 = 0;
        }

        rsdItem->countB = usb.m_sizeBytes;
        u32 allocSize = usb.m_sizeBytes * 0xC;
        void* allocData = Memory._Alloc(
            allocSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
        if (allocData == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), allocSize);
        }
        rsdItem->ptr14 = allocData;

        memcpy(rsdItem->ptr14, usb.m_data, usb.m_sizeBytes * 0xC);

        for (u32 offset = 0, i = 0; i < usb.m_sizeBytes; offset += 0xC, i++) {
            StoreSwapFloat(reinterpret_cast<f32*>(reinterpret_cast<u8*>(rsdItem->ptr14) + offset + 0x0));
            StoreSwapNegFloat(reinterpret_cast<f32*>(reinterpret_cast<u8*>(rsdItem->ptr14) + offset + 0x4));
            StoreSwapNegFloat(reinterpret_cast<f32*>(reinterpret_cast<u8*>(rsdItem->ptr14) + offset + 0x8));
        }
        DCStoreRange(rsdItem->ptr14, usb.m_sizeBytes * 0xC);
        break;
    }
    case 1: {
        memcpy(&m_usbTransform, usb.m_data, sizeof(m_usbTransform));
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[0][0]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[0][1]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[0][2]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[0][3]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[1][0]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[1][1]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[1][2]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[1][3]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[2][0]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[2][1]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[2][2]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[2][3]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[3][0]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[3][1]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[3][2]);
        StoreSwapFloat(&m_usbTransform.m_modelMatrix[3][3]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[0][0]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[0][1]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[0][2]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[0][3]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[1][0]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[1][1]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[1][2]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[1][3]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[2][0]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[2][1]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[2][2]);
        StoreSwapFloat(&m_usbTransform.m_viewMatrix[2][3]);
        StoreSwapFloat(&m_usbTransform.m_cameraPosition.x);
        StoreSwapFloat(&m_usbTransform.m_cameraPosition.y);
        StoreSwapFloat(&m_usbTransform.m_cameraPosition.z);
        StoreSwapFloat(&m_usbTransform.m_cameraDistance);
        memcpy(&m_unkMatrix, m_usbTransform.m_modelMatrix, 0x30);
        DCStoreRange(&m_usbTransform, sizeof(m_usbTransform));
        break;
    }
    case 0x31: {
        u32 allocSize = usb.m_sizeBytes;
        u8* dstBuffer = static_cast<u8*>(
            Memory._Alloc(allocSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0));

        if (dstBuffer == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), allocSize);
        }

        u8* src = dstBuffer;
        RSDITEM* rsdItem = this->GetRsdItem()->rsdItem;
        memcpy(dstBuffer, usb.m_data, usb.m_sizeBytes);

        u32 dstOffset = 0;
        for (u32 i = 0; i < usb.m_sizeBytes; i++) {
            u8 value = *dstBuffer;
            u32 writeOffset = dstOffset + 0x1A;
            dstOffset += 0x70;
            dstBuffer++;
            static_cast<u8*>(rsdItem->ptr18)[writeOffset] = value;
        }

        if (src != 0) {
            delete[] src;
        }
        break;
    }
    case 0x20: {
        u32 allocSize = usb.m_sizeBytes;
        void* mem = Memory._Alloc(allocSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);

        if (mem == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), allocSize);
        }

        s16* headerBuffer = static_cast<s16*>(mem);
        void* headerDst =
            Memory._Alloc(0x10, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
        if (headerDst == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), 0x10);
        }

        this->m_textureHeader[this->m_loadedTextureCount] = static_cast<s16*>(headerDst);
        memcpy(headerBuffer, usb.m_data, usb.m_sizeBytes);
        StoreSwapS16(&headerBuffer[0]);
        StoreSwapS16(&headerBuffer[1]);
        StoreSwapS16(&headerBuffer[2]);
        StoreSwapS16(&headerBuffer[3]);
        StoreSwapS16(&headerBuffer[4]);
        StoreSwapS16(&headerBuffer[5]);
        StoreSwapS16(&headerBuffer[6]);
        StoreSwapS16(&headerBuffer[7]);
        DCFlushRange(headerBuffer, 0x10);
        memcpy(this->m_textureHeader[this->m_loadedTextureCount], headerBuffer, 0x10);

        if (headerBuffer[1] == 0x20) {
            u32 dataBytes = usb.m_sizeBytes;
            void* texData = Memory._Alloc(
                dataBytes - 0x10, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
            if (texData == 0) {
                System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), dataBytes - 0x10);
            }
            this->m_textureData[this->m_loadedTextureCount] = texData;
            memcpy(this->m_textureData[this->m_loadedTextureCount], headerBuffer + 8, usb.m_sizeBytes - 0x10);
            DCFlushRange(this->m_textureData[this->m_loadedTextureCount], usb.m_sizeBytes - 0x10);
        } else if ((headerBuffer[1] == 4) || (headerBuffer[1] == 8)) {
            int tlutEntries = headerBuffer[1] == 4 ? 0x10 : 0x100;
            int tlutDataSize = tlutEntries * 4;
            int imageDataSize = static_cast<int>(usb.m_sizeBytes) - 0x10 - tlutDataSize;
            void* texData = Memory._Alloc(
                imageDataSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);

            if (texData == 0) {
                System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), imageDataSize);
            }
            this->m_textureData[this->m_loadedTextureCount] = texData;
            memcpy(this->m_textureData[this->m_loadedTextureCount], headerBuffer + 8,
                static_cast<int>(usb.m_sizeBytes) - 0x10 - tlutDataSize);
            DCFlushRange(this->m_textureData[this->m_loadedTextureCount],
                static_cast<int>(usb.m_sizeBytes) - 0x10 - tlutDataSize);

            void* tlutData = Memory._Alloc(
                tlutDataSize, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
            if (tlutData == 0) {
                System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), tlutDataSize);
            }
            this->m_tlutData[this->m_loadedTextureCount] = tlutData;

            u8* tlutSrc;
            if (headerBuffer[1] == 4) {
                tlutSrc = reinterpret_cast<u8*>(headerBuffer) + (headerBuffer[2] * headerBuffer[3]) / 2;
            } else {
                tlutSrc = reinterpret_cast<u8*>(headerBuffer) + headerBuffer[2] * headerBuffer[3];
            }
            memcpy(this->m_tlutData[this->m_loadedTextureCount], tlutSrc + 0x10, tlutDataSize);
            DCFlushRange(this->m_tlutData[this->m_loadedTextureCount], tlutDataSize);
        }

        void* texObj =
            Memory._Alloc(0x20, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
        if (texObj == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), 0x20);
        }
        this->m_texObj[this->m_loadedTextureCount] = static_cast<GXTexObj*>(texObj);

        void* tlutObj0 =
            Memory._Alloc(0xC, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
        if (tlutObj0 == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), 0xC);
        }
        this->m_tlutObj0[this->m_loadedTextureCount] = static_cast<GXTlutObj*>(tlutObj0);

        void* tlutObj1 =
            Memory._Alloc(0xC, MaterialEditorStage(), const_cast<char*>(s_ME_USB_process_cpp), 0x31, 0);
        if (tlutObj1 == 0) {
            System.Printf(const_cast<char*>(sMemAllocErrorSizeFmt), 0xC);
        }
        this->m_tlutObj1[this->m_loadedTextureCount] = static_cast<GXTlutObj*>(tlutObj1);

        u32 widthFactor = static_cast<u32>(headerBuffer[2]);
        u32 heightFactor = static_cast<u32>(headerBuffer[3]);
        int isPowerOfTwo = 1;

        for (;;) {
            if ((widthFactor & 1) != 0) {
                break;
            }
            widthFactor >>= 1;
        }
        for (;;) {
            if ((heightFactor & 1) != 0) {
                break;
            }
            heightFactor >>= 1;
        }
        if ((heightFactor != 1) || (widthFactor != 1)) {
            isPowerOfTwo = 0;
        }

        if (headerBuffer[1] == 0x20) {
            GXInitTexObj(this->m_texObj[this->m_loadedTextureCount],
                this->m_textureData[this->m_loadedTextureCount], headerBuffer[2], headerBuffer[3],
                GX_TF_RGBA8, static_cast<GXTexWrapMode>(isPowerOfTwo), static_cast<GXTexWrapMode>(isPowerOfTwo), GX_FALSE);
        } else if ((headerBuffer[1] == 4) || (headerBuffer[1] == 8)) {
            int tlutEntries = headerBuffer[1] == 4 ? 0x10 : 0x100;

            GXInitTlutObj(this->m_tlutObj0[this->m_loadedTextureCount],
                this->m_tlutData[this->m_loadedTextureCount], GX_TL_IA8, tlutEntries);
            GXInitTlutObj(this->m_tlutObj1[this->m_loadedTextureCount],
                reinterpret_cast<u8*>(this->m_tlutData[this->m_loadedTextureCount]) + tlutEntries * 2, GX_TL_IA8, tlutEntries);
            GXLoadTlut(this->m_tlutObj0[this->m_loadedTextureCount], GX_TLUT0);
            GXLoadTlut(this->m_tlutObj1[this->m_loadedTextureCount], GX_TLUT1);
            GXInitTexObjCI(this->m_texObj[this->m_loadedTextureCount],
                this->m_textureData[this->m_loadedTextureCount], headerBuffer[2], headerBuffer[3],
                static_cast<GXCITexFmt>(headerBuffer[1] == 4 ? GX_TF_C4 : GX_TF_C8),
                static_cast<GXTexWrapMode>(isPowerOfTwo), static_cast<GXTexWrapMode>(isPowerOfTwo),
                GX_FALSE, static_cast<u32>(GX_TLUT0));
        }

        if (headerBuffer != 0) {
            delete[] reinterpret_cast<u8*>(headerBuffer);
        }
        m_loadedTextureCount++;
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

extern const float kMapEditorZero = 0.0f;
extern const float kMapEditorOne = 1.0f;
