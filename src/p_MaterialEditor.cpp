#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_usb.h"
#include "ffcc/ME_USB_process.h"
#include "ffcc/p_camera.h"
#include "ffcc/graphic.h"
extern "C" {
extern const float kMaterialEditorControlMaxInit;
extern const float kMaterialEditorControlMinInit;
extern unsigned int kMaterialEditorDefaultColorRgba;
extern char sMaterialEditorSpinnerText[];
}
#include "ffcc/zlist.h"
#include <Dolphin/mtx.h>
#include <Dolphin/gx.h>
#include <dolphin/os/OSCache.h>
#include <string.h>

extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" void* __ct__14CUSBStreamDataFv(void* self);
extern "C" void* __ct__5ZLISTFv(void* self);
extern "C" ZLIST* __dt__5ZLISTFv(ZLIST* self, short shouldDelete);
extern "C" void createViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void destroyViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void calcViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void drawViewer__18CMaterialEditorPcsFv(CMaterialEditorPcs*);
extern "C" void __dt__18CMaterialEditorPcsFv(void* self);
extern "C" char __vt__8CManager[];
extern "C" char __vt_CProcess[];
extern char lbl_8032E648[];

static const char s_CMaterialEditorPcs_VIEWER_801D7D18[] = "CMaterialEditorPcs_VIEWER";
static const char s_CMaterialEditorPcs_801D7D34[] = "CMaterialEditorPcs";
extern "C" void* __vt__18CMaterialEditorPcs[];
unsigned int m_table_desc0__18CMaterialEditorPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__18CMaterialEditorPcsFv)};
unsigned int m_table_desc1__18CMaterialEditorPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__18CMaterialEditorPcsFv)};
unsigned int m_table_desc2__18CMaterialEditorPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__18CMaterialEditorPcsFv)};
unsigned int m_table_desc3__18CMaterialEditorPcs[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__18CMaterialEditorPcsFv)};
unsigned int m_table__18CMaterialEditorPcs[0x15C / sizeof(unsigned int)] = {
    reinterpret_cast<unsigned int>(const_cast<char*>(s_CMaterialEditorPcs_VIEWER_801D7D18)), 0, 0, 0, 0, 0, 0, 0, 0, 0, 0x20, 0, 0, 0, 0, 0x41, 1
};
unsigned int lbl_801EA624[3] = {reinterpret_cast<unsigned int>(lbl_8032E648), 0, 0};
unsigned int lbl_801EA630 = reinterpret_cast<unsigned int>(lbl_8032E648);
CMaterialEditorPcs MaterialEditorPcs;

struct MaterialEditorTableInit {
    MaterialEditorTableInit()
    {
        unsigned int* dst = reinterpret_cast<unsigned int*>(m_table__18CMaterialEditorPcs);

        dst[1] = m_table_desc0__18CMaterialEditorPcs[0];
        dst[2] = m_table_desc0__18CMaterialEditorPcs[1];
        dst[3] = m_table_desc0__18CMaterialEditorPcs[2];
        dst[4] = m_table_desc1__18CMaterialEditorPcs[0];
        dst[5] = m_table_desc1__18CMaterialEditorPcs[1];
        dst[6] = m_table_desc1__18CMaterialEditorPcs[2];
        dst[7] = m_table_desc2__18CMaterialEditorPcs[0];
        dst[8] = m_table_desc2__18CMaterialEditorPcs[1];
        dst[9] = m_table_desc2__18CMaterialEditorPcs[2];
        dst[12] = m_table_desc3__18CMaterialEditorPcs[0];
        dst[13] = m_table_desc3__18CMaterialEditorPcs[1];
        dst[14] = m_table_desc3__18CMaterialEditorPcs[2];
    }
};

static MaterialEditorTableInit sMaterialEditorTableInit;
static const char s_MaterialEditor[] = "MaterialEditor=%c";

extern "C" void Printf__8CGraphicFPce(void*, const char*, ...);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, unsigned char, int, int, unsigned char);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int, int, int, int, int);
extern "C" void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int, int, int, int, int);
extern "C" void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int,
                                                                                                        int, int, int);
extern "C" void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int,
                                                                                                        int, int, int);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
extern "C" void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
    int, int, int, int, int);
extern "C" float FLOAT_8032FCC8;
extern "C" float FLOAT_8032FCD8;
extern "C" float FLOAT_8032FCDC;
extern "C" double DOUBLE_8032FCC0;
extern "C" double DOUBLE_8032FCD0;

static void WriteU8(void* base, unsigned int offset, unsigned char value) {
    reinterpret_cast<unsigned char*>(base)[offset] = value;
}

static void WriteU32(void* base, unsigned int offset, unsigned int value) {
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(base) + offset) = value;
}

static void WriteF32(void* base, unsigned int offset, float value) {
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(base) + offset) = value;
}

/*
 * --INFO--
 * PAL Address: 0x8004c6a0
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialEditorPcs::~CMaterialEditorPcs()
{
}

/*
 * --INFO--
 * PAL Address: 0x8004c3c4
 * PAL Size: 452b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::Init()
{
    u32 clz0;
    u32 clz1;
    u8 level;
    unsigned char* self;
    int remaining;

    self = reinterpret_cast<unsigned char*>(this);
    self[0x8] = 0x7f;
    clz0 = static_cast<u32>(__cntlzw(0));
    self[0x9] = 0x7f;
    self[0xa] = 0x7f;
    clz1 = static_cast<u32>(__cntlzw(1));
    level = static_cast<u8>(-((u8)(clz0 >> 5) & 1)) & 0x3f;
    self[0xb] = 0xff;
    self[0xc] = level;
    clz0 = static_cast<u32>(__cntlzw(2));
    self[0xd] = level;
    self[0xe] = level;
    level = static_cast<u8>(-((u8)(clz1 >> 5) & 1)) & 0x3f;
    self[0xf] = 0xff;
    *reinterpret_cast<float*>(self + 0x18) = 0.0f;
    *reinterpret_cast<float*>(self + 0x1c) = 0.0f;
    *reinterpret_cast<float*>(self + 0x20) = -1.0f;
    self[0x10] = level;
    self[0x11] = level;
    self[0x12] = level;
    level = static_cast<u8>(-((u8)(clz0 >> 5) & 1)) & 0x3f;
    self[0x13] = 0xff;
    *reinterpret_cast<float*>(self + 0x24) = 0.0f;
    *reinterpret_cast<float*>(self + 0x28) = 0.0f;
    *reinterpret_cast<float*>(self + 0x2c) = -1.0f;
    self[0x14] = level;
    self[0x15] = level;
    self[0x16] = level;
    self[0x17] = 0xff;
    *reinterpret_cast<float*>(self + 0x30) = 0.0f;
    *reinterpret_cast<float*>(self + 0x34) = 0.0f;
    *reinterpret_cast<float*>(self + 0x38) = -1.0f;
    *reinterpret_cast<float*>(self + 0x44) = 0.0f;
    *reinterpret_cast<float*>(self + 0x40) = 0.0f;
    *reinterpret_cast<float*>(self + 0x3c) = 0.0f;
    *reinterpret_cast<float*>(self + 0x50) = 0.0f;
    *reinterpret_cast<float*>(self + 0x4c) = 0.0f;
    *reinterpret_cast<float*>(self + 0x48) = 0.0f;
    *reinterpret_cast<float*>(self + 0x5c) = 1.0f;
    *reinterpret_cast<float*>(self + 0x58) = 1.0f;
    *reinterpret_cast<float*>(self + 0x54) = 1.0f;
    *reinterpret_cast<u32*>(self + 0xbc) = 0;

    remaining = 2;
    do {
        *reinterpret_cast<u32*>(self + 0x2bc) = 0;
        *reinterpret_cast<u32*>(self + 0x2fc) = 0;
        *reinterpret_cast<u32*>(self + 0x23c) = 0;
        *reinterpret_cast<u32*>(self + 0x33c) = 0;
        *reinterpret_cast<u32*>(self + 0x37c) = 0;
        *reinterpret_cast<u32*>(self + 0x27c) = 0;
        *reinterpret_cast<u32*>(self + 0x2c0) = 0;
        *reinterpret_cast<u32*>(self + 0x300) = 0;
        *reinterpret_cast<u32*>(self + 0x240) = 0;
        *reinterpret_cast<u32*>(self + 0x340) = 0;
        *reinterpret_cast<u32*>(self + 0x380) = 0;
        *reinterpret_cast<u32*>(self + 0x280) = 0;
        *reinterpret_cast<u32*>(self + 0x2c4) = 0;
        *reinterpret_cast<u32*>(self + 0x304) = 0;
        *reinterpret_cast<u32*>(self + 0x244) = 0;
        *reinterpret_cast<u32*>(self + 0x344) = 0;
        *reinterpret_cast<u32*>(self + 0x384) = 0;
        *reinterpret_cast<u32*>(self + 0x284) = 0;
        *reinterpret_cast<u32*>(self + 0x2c8) = 0;
        *reinterpret_cast<u32*>(self + 0x308) = 0;
        *reinterpret_cast<u32*>(self + 0x248) = 0;
        *reinterpret_cast<u32*>(self + 0x348) = 0;
        *reinterpret_cast<u32*>(self + 0x388) = 0;
        *reinterpret_cast<u32*>(self + 0x288) = 0;
        *reinterpret_cast<u32*>(self + 0x2cc) = 0;
        *reinterpret_cast<u32*>(self + 0x30c) = 0;
        *reinterpret_cast<u32*>(self + 0x24c) = 0;
        *reinterpret_cast<u32*>(self + 0x34c) = 0;
        *reinterpret_cast<u32*>(self + 0x38c) = 0;
        *reinterpret_cast<u32*>(self + 0x28c) = 0;
        *reinterpret_cast<u32*>(self + 0x2d0) = 0;
        *reinterpret_cast<u32*>(self + 0x310) = 0;
        *reinterpret_cast<u32*>(self + 0x250) = 0;
        *reinterpret_cast<u32*>(self + 0x350) = 0;
        *reinterpret_cast<u32*>(self + 0x390) = 0;
        *reinterpret_cast<u32*>(self + 0x290) = 0;
        *reinterpret_cast<u32*>(self + 0x2d4) = 0;
        *reinterpret_cast<u32*>(self + 0x314) = 0;
        *reinterpret_cast<u32*>(self + 0x254) = 0;
        *reinterpret_cast<u32*>(self + 0x354) = 0;
        *reinterpret_cast<u32*>(self + 0x394) = 0;
        *reinterpret_cast<u32*>(self + 0x294) = 0;
        *reinterpret_cast<u32*>(self + 0x2d8) = 0;
        *reinterpret_cast<u32*>(self + 0x318) = 0;
        *reinterpret_cast<u32*>(self + 0x258) = 0;
        *reinterpret_cast<u32*>(self + 0x358) = 0;
        *reinterpret_cast<u32*>(self + 0x398) = 0;
        *reinterpret_cast<u32*>(self + 0x298) = 0;
        self += 0x20;
        remaining += -1;
    } while (remaining != 0);

    reinterpret_cast<unsigned char*>(this)[0x3bc] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8004c314
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::Quit()
{
    unsigned int i = 0;
    CMaterialEditorPcs* cursor = this;

    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x3BC) = 0;

    do {
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(
                                                   reinterpret_cast<unsigned char*>(cursor) + 0x2BC)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(
                                                   reinterpret_cast<unsigned char*>(cursor) + 0x2FC)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(
                                                   reinterpret_cast<unsigned char*>(cursor) + 0x23C)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(
                                                   reinterpret_cast<unsigned char*>(cursor) + 0x33C)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(
                                                   reinterpret_cast<unsigned char*>(cursor) + 0x37C)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(
                                                   reinterpret_cast<unsigned char*>(cursor) + 0x27C)));
        i += 1;
        cursor = reinterpret_cast<CMaterialEditorPcs*>(reinterpret_cast<unsigned char*>(cursor) + 4);
    } while (i < 0x10);

    unsigned int textureBlock = *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0xBC);
    if (textureBlock != 0) {
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(textureBlock));
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMaterialEditorPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(reinterpret_cast<unsigned char*>(m_table__18CMaterialEditorPcs) + index * 0x15C);
}

/*
 * --INFO--
 * PAL Address: 0x8004c234
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::createViewer()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CMemory::CStage* stage = reinterpret_cast<CMemory::CStage*>(
        Memory.CreateStage(0x200000, const_cast<char*>(s_CMaterialEditorPcs_801D7D34), 0));
    GXColor clear;
    float fVar1;

    WriteU32(self, 0x4, reinterpret_cast<unsigned int>(stage));
    USBPcs.IsBigAlloc(1);

    clear.r = 0x40;
    clear.g = 0x40;
    clear.b = 0x40;
    clear.a = 0xff;
    GXSetCopyClear(clear, 0xffffff);

    WriteU32(self, 0x98, 1);
    WriteU32(self, 0xe8, 0);
    memset(self + 0xec, 0, 0x120);

    fVar1 = FLOAT_8032FCC8;
    WriteF32(self, 0x128, fVar1);
    WriteF32(self, 0x114, fVar1);
    WriteF32(self, 0x100, fVar1);
    WriteF32(self, 0xec, fVar1);

    PSMTXIdentity(reinterpret_cast<MtxPtr>(self + 0x20C));
    m_usbStream.CreateBuffer();
}

/*
 * --INFO--
 * PAL Address: 0x8004c138
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::destroyViewer()
{
    GXColor clear;

    USBPcs.IsBigAlloc(0);

    clear.r = 0;
    clear.g = 0;
    clear.b = 0;
    clear.a = 0;
    GXSetCopyClear(clear, 0xffffff);

    reinterpret_cast<CUSBStreamData*>(reinterpret_cast<unsigned char*>(this) + 0x84)->DeleteBuffer();
    MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0xbc)));
    reinterpret_cast<unsigned char*>(this)[0x3bc] = 0;

    {
        unsigned int uVar2 = 0;
        CMaterialEditorPcs* pCVar1 = this;

        do {
            MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pCVar1) + 0x2bc)));
            MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pCVar1) + 0x2fc)));
            MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pCVar1) + 0x23c)));
            MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pCVar1) + 0x33c)));
            MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pCVar1) + 0x37c)));
            MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(pCVar1) + 0x27c)));
            uVar2 += 1;
            pCVar1 = reinterpret_cast<CMaterialEditorPcs*>(reinterpret_cast<unsigned char*>(pCVar1) + 4);
        } while (uVar2 < 0x10);
    }

    Memory.DestroyStage(reinterpret_cast<CMemory::CStage*>(*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(this) + 0x4)));
}

/*
 * --INFO--
 * PAL Address: 0x8004c098
 * PAL Size: 160b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::ClearTextureData()
{
    unsigned char* cursor = reinterpret_cast<unsigned char*>(this);
    unsigned int i = 0;

    *reinterpret_cast<volatile unsigned char*>(reinterpret_cast<unsigned char*>(this) + 0x3BC) = 0;

    do {
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x2BC)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x2FC)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x23C)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x33C)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x37C)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x27C)));
        i += 1;
        cursor += 4;
    } while (i < 0x10);
}

/*
 * --INFO--
 * PAL Address: 0x8004bec8
 * PAL Size: 464b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::calcViewer()
{
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

    Mtx cameraMatrix;
    ViewerSRT srt;
    Mtx scaleMatrix;
    float rotationValue;

    USBPcs.mccReadData();

    int usbDone = m_usbStream.IsUSBStreamDataDone();
    if (usbDone != 0) {
        SetUSBData();
        m_usbStream.SetUSBStreamDataDone();
    }

    rotationValue = FLOAT_8032FCC8;
    srt.transZ = FLOAT_8032FCD8;
    srt.transY = FLOAT_8032FCD8;
    srt.transX = FLOAT_8032FCD8;
    srt.rotZ = rotationValue;
    srt.rotY = rotationValue;
    srt.rotX = rotationValue;
    srt.scaleZ = FLOAT_8032FCD8;
    srt.scaleY = FLOAT_8032FCD8;
    srt.scaleX = FLOAT_8032FCD8;
    srt.transX = field268_0x15c.x;
    srt.transY = field268_0x15c.y;
    srt.transZ = -field268_0x15c.z;
    CameraPcs.SetViewerSRT(reinterpret_cast<const SRT*>(&srt));

    PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMatrix);

    m_unkMatrix.value[0][0] = field_0x12c;
    m_unkMatrix.value[0][1] = field_0x130;
    m_unkMatrix.value[0][2] = field_0x134;
    m_unkMatrix.value[0][3] = field_0x138;
    m_unkMatrix.value[1][0] = field_0x13c;
    m_unkMatrix.value[1][1] = field_0x140;
    m_unkMatrix.value[1][2] = field_0x144;
    m_unkMatrix.value[1][3] = field_0x148;
    m_unkMatrix.value[2][0] = field_0x14c;
    m_unkMatrix.value[2][1] = field_0x150;
    m_unkMatrix.value[2][2] = field_0x154;
    m_unkMatrix.value[2][3] = field_0x158;

    PSMTXTranspose(m_unkMatrix.value, m_unkMatrix.value);

    m_unkMatrix.value[0][1] = -m_unkMatrix.value[0][1];
    m_unkMatrix.value[1][1] = -m_unkMatrix.value[1][1];
    m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
    m_unkMatrix.value[2][0] = -m_unkMatrix.value[2][0];
    m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
    m_unkMatrix.value[2][2] = -m_unkMatrix.value[2][2];

    PSMTXIdentity(scaleMatrix);
    scaleMatrix[1][1] = FLOAT_8032FCDC;
    PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);

    PSMTXIdentity(scaleMatrix);
    scaleMatrix[2][2] = FLOAT_8032FCDC;
    PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);

    PSMTXConcat(cameraMatrix, m_unkMatrix.value, cameraMatrix);
    GXLoadPosMtxImm(cameraMatrix, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8004b2cc
 * PAL Size: 3068b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
struct MaterialEditorPolygon {
    u16 flags;
    u16 blendMode;
    u32 _04;
    u16 index0;
    u16 index1;
    u16 index2;
    u16 index3;
    u16 _10;
    u16 _12;
    u16 _14;
    u16 _16;
    u8 _18;
    char textureMarker;
    u8 _1a[4];
    s16 textureIndex;
    s16 u0;
    s16 v0;
    s16 u1;
    s16 v1;
    s16 u2;
    s16 v2;
    s16 u3;
    s16 v3;
    u8 _30[0x20];
    float texCoord[4][2];
};

void CMaterialEditorPcs::drawViewer()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    static char* pFan;
    static unsigned char init;
    static int alive;
    static unsigned char init_0;

    if (init == 0) {
        pFan = sMaterialEditorSpinnerText;
        init = 1;
    }
    if (init_0 == 0) {
        alive = 0;
        init_0 = 1;
    }

    alive = alive + 1;
    int sign = alive >> 31;
    int idx = (sign * 4 | (unsigned int)(((alive >> 4) * 0x40000000) + sign) >> 30) - sign;
    Printf__8CGraphicFPce(&Graphic, s_MaterialEditor, (int)(char)pFan[idx]);

    if (*reinterpret_cast<int*>(self + 0xE8) != 0) {
        return;
    }

    ZLIST* zlist = reinterpret_cast<ZLIST*>(self + 0xC8);
    _ZLISTITEM* it = zlist->m_root.m_previous;
    while (it != 0) {
        int* listData = reinterpret_cast<int*>(zlist->GetDataNext(&it));
        int model = *listData;

        GXSetArray(GX_VA_POS, *reinterpret_cast<void**>(model + 0x10), 0xC);
        GXSetArray(GX_VA_NRM, *reinterpret_cast<void**>(model + 0x14), 0xC);
        GXSetNumChans(1);
        GXClearVtxDesc();
        GXSetChanCtrl(GX_COLOR0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_ALPHA0, GX_FALSE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        GXSetNumTevStages(1);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
        _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 0, 7, 0);
        GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);

        GXColor matColor;
        matColor.r = static_cast<unsigned char>((kMaterialEditorDefaultColorRgba >> 24) & 0xFF);
        matColor.g = static_cast<unsigned char>((kMaterialEditorDefaultColorRgba >> 16) & 0xFF);
        matColor.b = static_cast<unsigned char>((kMaterialEditorDefaultColorRgba >> 8) & 0xFF);
        matColor.a = static_cast<unsigned char>(kMaterialEditorDefaultColorRgba & 0xFF);
        GXSetChanAmbColor(GX_COLOR0A0, matColor);
        GXSetChanMatColor(GX_COLOR0A0, matColor);

        GXSetVtxDesc(GX_VA_POS, GX_INDEX16);
        GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
        GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
        GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_NRM, GX_NRM_XYZ, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_F32, 0);
        GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_CLR0, GX_CLR_RGBA, GX_RGBA8, 0);
        GXSetNumTexGens(1);
        GXSetNumTevStages(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);

        for (int pass = 0; pass < 2; pass++) {
            MaterialEditorPolygon* polygon = reinterpret_cast<MaterialEditorPolygon*>(reinterpret_cast<RSDITEM*>(model)->ptr18);

            for (u32 polyIndex = 0; polyIndex < reinterpret_cast<RSDITEM*>(model)->countC; polyIndex++, polygon++) {
                if ((polygon->flags & 0x200) == 0) {
                    GXSetCullMode(GX_CULL_FRONT);
                } else {
                    GXSetCullMode(GX_CULL_NONE);
                }

                if (pass == 1) {
                    if ((polygon->flags & 0x400) == 0) {
                        continue;
                    }

                    u16 blendMode = polygon->blendMode;
                    int blend = 1;
                    int srcFactor = 1;
                    int dstFactor = 1;
                    int src = blendMode & 3;
                    int dst = (blendMode >> 2) & 3;

                    if ((src == 0) && (dst == 0)) {
                        srcFactor = 4;
                        dstFactor = 5;
                    } else if ((src == 0) && (dst == 2)) {
                        srcFactor = 4;
                    } else if ((src == 2) && (dst == 0)) {
                        blend = 3;
                    }

                    GXSetZCompLoc(GX_FALSE);
                    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(7, 0, 0, 7, 0);
                    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(blend, srcFactor, dstFactor, 3);
                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_FALSE);
                    GXSetCullMode(GX_CULL_NONE);
                } else {
                    if ((polygon->flags & 0x400) != 0) {
                        continue;
                    }

                    GXSetZMode(GX_TRUE, GX_LEQUAL, GX_TRUE);
                    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(0, 0, 0, 7);
                }

                if ((polygon->textureMarker == 'H') && (polygon->textureIndex < static_cast<s16>(m_loadedTextureCount))) {
                    s16* textureHeader = m_textureHeader[polygon->textureIndex];
                    float scaleU = static_cast<float>(DOUBLE_8032FCC0 / (static_cast<double>(textureHeader[2]) - DOUBLE_8032FCD0));
                    float scaleV = static_cast<float>(DOUBLE_8032FCC0 / (static_cast<double>(textureHeader[3]) - DOUBLE_8032FCD0));

                    polygon->texCoord[0][0] = scaleU * static_cast<float>(polygon->u0);
                    if (polygon->u0 < 0) {
                        polygon->texCoord[0][0] += FLOAT_8032FCC8;
                    }
                    polygon->texCoord[1][0] = scaleU * static_cast<float>(polygon->u1);
                    if (polygon->u1 < 0) {
                        polygon->texCoord[1][0] += FLOAT_8032FCC8;
                    }
                    polygon->texCoord[2][0] = scaleU * static_cast<float>(polygon->u2);
                    if (polygon->u2 < 0) {
                        polygon->texCoord[2][0] += FLOAT_8032FCC8;
                    }
                    polygon->texCoord[3][0] = scaleU * static_cast<float>(polygon->u3);
                    if (polygon->u3 < 0) {
                        polygon->texCoord[3][0] += FLOAT_8032FCC8;
                    }

                    if (polygon->v0 < 0) {
                        polygon->v0 = -polygon->v0;
                    }
                    if (polygon->v1 < 0) {
                        polygon->v1 = -polygon->v1;
                    }
                    if (polygon->v2 < 0) {
                        polygon->v2 = -polygon->v2;
                    }
                    if (polygon->v3 < 0) {
                        polygon->v3 = -polygon->v3;
                    }

                    polygon->texCoord[0][1] = -(scaleV * static_cast<float>(polygon->v0) - FLOAT_8032FCC8);
                    polygon->texCoord[1][1] = -(scaleV * static_cast<float>(polygon->v1) - FLOAT_8032FCC8);
                    polygon->texCoord[2][1] = -(scaleV * static_cast<float>(polygon->v2) - FLOAT_8032FCC8);
                    polygon->texCoord[3][1] = -(scaleV * static_cast<float>(polygon->v3) - FLOAT_8032FCC8);
                    DCStoreRange(polygon, sizeof(MaterialEditorPolygon));

                    if (textureHeader[1] == 0x20) {
                        GXSetNumTevStages(1);
                        GXSetNumTexGens(1);
                        GXLoadTexObj(m_texObj[polygon->textureIndex], GX_TEXMAP0);
                        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
                            0, 0xf, 8, 10, 0xf);
                        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 1, 0);
                        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
                            0, 7, 4, 5, 7);
                        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 1, 1, 0);
                    }

                    if ((textureHeader[1] == 4) || (textureHeader[1] == 8)) {
                        GXColor red = {0xff, 0xff, 0, 0};
                        GXColor blue = {0, 0, 0xff, 0xff};

                        GXSetNumTevStages(3);
                        GXSetNumTexGens(1);
                        GXSetTevColor(GX_TEVREG2, red);
                        GXSetTevColor(GX_TEVPREV, blue);
                        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_IDENTITY, GX_FALSE, GX_PTIDENTITY);
                        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
                            1, 0, 3, 3, 3);
                        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
                            2, 2, 2, 2, 3);
                        GXSetTevDirect(GX_TEVSTAGE0);
                        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
                            0, 0xf, 8, 4, 0xf);
                        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 0, 0);
                        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
                        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xff);
                        GXSetTevDirect(GX_TEVSTAGE1);
                        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
                            1, 0xf, 8, 6, 0);
                        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
                            1, 7, 6, 4, 7);
                        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
                        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
                        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 2);
                        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 0xff);
                        GXSetTevDirect(GX_TEVSTAGE2);
                        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
                            2, 0xf, 0, 10, 0xf);
                        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
                            2, 7, 0, 5, 7);
                        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 1, 1, 0);
                        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 2, 1, 0);
                        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
                        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0xff, 0xff, 4);
                        GXInitTexObjTlut(m_texObj[polygon->textureIndex], 0);
                        GXLoadTexObj(m_texObj[polygon->textureIndex], GX_TEXMAP0);
                        GXInitTexObjTlut(m_texObj[polygon->textureIndex], 1);
                        GXLoadTexObj(m_texObj[polygon->textureIndex], GX_TEXMAP1);
                        GXLoadTlut(m_tlutObj0[polygon->textureIndex], 0);
                        GXLoadTlut(m_tlutObj1[polygon->textureIndex], 1);
                    }
                }

                GXSetVtxDesc(GX_VA_NRM, GX_INDEX16);
                GXSetVtxDesc(GX_VA_CLR0, GX_INDEX16);
                GXSetArray(GX_VA_TEX0, polygon->texCoord, 4);
                GXSetArray(GX_VA_CLR0, polygon->texCoord, 8);

                u32 vertexIndex[8];
                u8 vertexCount = 3;
                vertexIndex[4] = polygon->index0;
                vertexIndex[5] = polygon->index1;
                vertexIndex[6] = polygon->index2;
                vertexIndex[0] = 0;
                vertexIndex[1] = 1;
                vertexIndex[2] = 2;

                if ((polygon->flags & 0xf) == 0) {
                    GXBegin(GX_TRIANGLES, GX_VTXFMT0, 3);
                }
                if ((polygon->flags & 0xf) == 1) {
                    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
                    vertexCount = 4;
                    vertexIndex[6] = polygon->index3;
                    vertexIndex[7] = polygon->index2;
                    vertexIndex[2] = 3;
                    vertexIndex[3] = 2;
                }

                for (u8 i = 0; i < vertexCount; i++) {
                    GXWGFifo.u16 = static_cast<u16>(vertexIndex[i + 4]);
                    GXWGFifo.u16 = static_cast<u16>(vertexIndex[i + 4]);
                    GXWGFifo.u8 = static_cast<u8>(vertexIndex[i]);
                    GXWGFifo.u16 = static_cast<u16>(vertexIndex[i]);
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8004b21c
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialEditorPcs::CreateBoundaryBox(Vec& minPos, Vec& maxPos, long count, const Vec* points)
{
    f32 maxInit = kMaterialEditorControlMaxInit;
    minPos.x = minPos.y = minPos.z = maxInit;
    f32 minInit = kMaterialEditorControlMinInit;
    maxPos.x = maxPos.y = maxPos.z = minInit;

    for (; count > 0; count--, points++) {
        const Vec& point = *points;
        if (minPos.x > point.x) {
            minPos.x = point.x;
        }
        if (minPos.y > point.y) {
            minPos.y = point.y;
        }
        if (minPos.z > point.z) {
            minPos.z = point.z;
        }
        if (maxPos.x < point.x) {
            maxPos.x = point.x;
        }
        if (maxPos.y < point.y) {
            maxPos.y = point.y;
        }
        if (maxPos.z < point.z) {
            maxPos.z = point.z;
        }
    }
}
