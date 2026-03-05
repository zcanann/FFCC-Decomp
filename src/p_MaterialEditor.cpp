#include "ffcc/p_MaterialEditor.h"
#include "ffcc/p_usb.h"
#include "ffcc/ME_USB_process.h"
#include "ffcc/graphic.h"
#include "ffcc/zlist.h"
#include <Dolphin/mtx.h>
#include <Dolphin/gx.h>
#include <string.h>

extern "C" int __cntlzw(unsigned int);
extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" void* __ct__14CUSBStreamDataFv(void* self);
extern "C" void* __ct__5ZLISTFv(void* self);
extern "C" void __dt__18CMaterialEditorPcsFv(void* self);

extern CUSBPcs USBPcs;
extern CGraphic Graphic;
extern unsigned char m_table__18CMaterialEditorPcs[];
static char s_CMaterialEditorPcs[] = "CMaterialEditorPcs";
extern void* __vt__8CManager;
extern void* lbl_801E8668;
extern void* lbl_801EA644;
extern unsigned char lbl_8026D338[];
extern unsigned int lbl_801EA498[];
extern unsigned int lbl_801EA4A4[];
extern unsigned int lbl_801EA4B0[];
extern unsigned int lbl_801EA4BC[];
extern unsigned int lbl_801EA4C8[];
extern float lbl_8032FCAC;
extern float lbl_8032FCB0;
extern unsigned char DAT_8032ed1c;
extern char* DAT_8032ed18;
extern char DAT_8032fcb4[];
extern unsigned char DAT_8032ed24;
extern int DAT_8032ed20;
extern unsigned int DAT_8032fca8;
static char s_MaterialEditor[] = "MaterialEditor=%c";
extern class CCameraPcs {
public:
    Mtx m_cameraMatrix;
} CameraPcs;
extern CMemory Memory;

extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void Printf__8CGraphicFPce(void*, const char*, ...);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, unsigned char, int, int, unsigned char);

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
 * PAL Address: 0x8004c588
 * PAL Size: 280b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_MaterialEditor_cpp(void)
{
    volatile void** base = reinterpret_cast<volatile void**>(&MaterialEditorPcs);
    *base = &__vt__8CManager;
    *base = &lbl_801E8668;
    *base = &lbl_801EA644;

    unsigned char* self = reinterpret_cast<unsigned char*>(&MaterialEditorPcs);
    __ct__14CUSBStreamDataFv(self + 0x84);
    __ct__5ZLISTFv(self + 0xC8);
    __ct__5ZLISTFv(self + 0xD8);
    __register_global_object(&MaterialEditorPcs, reinterpret_cast<void*>(__dt__18CMaterialEditorPcsFv), lbl_8026D338);

    unsigned int* dst = lbl_801EA4C8;
    dst[1] = lbl_801EA498[0];
    dst[2] = lbl_801EA498[1];
    dst[3] = lbl_801EA498[2];
    dst[4] = lbl_801EA4A4[0];
    dst[5] = lbl_801EA4A4[1];
    dst[6] = lbl_801EA4A4[2];
    dst[7] = lbl_801EA4B0[0];
    dst[8] = lbl_801EA4B0[1];
    dst[9] = lbl_801EA4B0[2];
    dst[12] = lbl_801EA4BC[0];
    dst[13] = lbl_801EA4BC[1];
    dst[14] = lbl_801EA4BC[2];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterialEditorPcs::CMaterialEditorPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterialEditorPcs::~CMaterialEditorPcs()
{
	// TODO
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    const float kZero = 0.0f;
    const float kOne = 1.0f;
    const float kNegOne = -1.0f;

    const unsigned int clz0 = static_cast<unsigned int>(__cntlzw(0));
    const unsigned int clz1 = static_cast<unsigned int>(__cntlzw(1));
    const unsigned int clz2 = static_cast<unsigned int>(__cntlzw(2));

    WriteU8(self, 0x8, 0x7f);
    WriteU8(self, 0x9, 0x7f);
    WriteU8(self, 0xA, 0x7f);
    WriteU8(self, 0xB, 0xff);

    unsigned char level = static_cast<unsigned char>(-static_cast<int>((clz0 >> 5) & 1)) & 0x3f;
    WriteU8(self, 0xC, level);
    WriteU8(self, 0xD, level);
    WriteU8(self, 0xE, level);
    WriteU8(self, 0xF, 0xff);

    WriteF32(self, 0x18, kZero);
    WriteF32(self, 0x1C, kZero);
    WriteF32(self, 0x20, kNegOne);

    level = static_cast<unsigned char>(-static_cast<int>((clz1 >> 5) & 1)) & 0x3f;
    WriteU8(self, 0x10, level);
    WriteU8(self, 0x11, level);
    WriteU8(self, 0x12, level);
    WriteU8(self, 0x13, 0xff);

    WriteF32(self, 0x24, kZero);
    WriteF32(self, 0x28, kZero);
    WriteF32(self, 0x2C, kNegOne);

    level = static_cast<unsigned char>(-static_cast<int>((clz2 >> 5) & 1)) & 0x3f;
    WriteU8(self, 0x14, level);
    WriteU8(self, 0x15, level);
    WriteU8(self, 0x16, level);
    WriteU8(self, 0x17, 0xff);

    WriteF32(self, 0x30, kZero);
    WriteF32(self, 0x34, kZero);
    WriteF32(self, 0x38, kNegOne);
    WriteF32(self, 0x3C, kZero);
    WriteF32(self, 0x40, kZero);
    WriteF32(self, 0x44, kZero);
    WriteF32(self, 0x48, kZero);
    WriteF32(self, 0x4C, kZero);
    WriteF32(self, 0x50, kZero);
    WriteF32(self, 0x54, kOne);
    WriteF32(self, 0x58, kOne);
    WriteF32(self, 0x5C, kOne);

    WriteU32(self, 0xBC, 0);

    int remaining = 2;
    CMaterialEditorPcs* cursor = this;
    do {
        unsigned char* block = reinterpret_cast<unsigned char*>(cursor);

        *reinterpret_cast<unsigned int*>(block + 0x2BC) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2FC) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x23C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x33C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x37C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x27C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2C0) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x300) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x240) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x340) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x380) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x280) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2C4) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x304) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x244) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x344) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x384) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x284) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2C8) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x308) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x248) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x348) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x388) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x288) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2CC) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x30C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x24C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x34C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x38C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x28C) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2D0) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x310) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x250) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x350) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x390) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x290) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2D4) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x314) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x254) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x354) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x394) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x294) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x2D8) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x318) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x258) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x358) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x398) = 0;
        *reinterpret_cast<unsigned int*>(block + 0x298) = 0;

        cursor = reinterpret_cast<CMaterialEditorPcs*>(block + 0x20);
        remaining -= 1;
    } while (remaining != 0);

    WriteU32(self, 0x3BC, 0);
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned char* cursor = self;
    unsigned int i = 0;

    WriteU32(self, 0x3BC, 0);

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

    unsigned int textureBlock = *reinterpret_cast<unsigned int*>(self + 0xBC);
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
    return reinterpret_cast<int>(m_table__18CMaterialEditorPcs + index * 0x15C);
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
        CreateStage__7CMemoryFUlPci(&Memory, 0x200000, s_CMaterialEditorPcs, 0));
    GXColor clear;
    const float kZero = 0.0f;

    WriteU32(self, 0x4, reinterpret_cast<unsigned int>(stage));
    USBPcs.IsBigAlloc(1);

    clear.r = 0x40;
    clear.g = 0x40;
    clear.b = 0x40;
    clear.a = 0xff;
    GXSetCopyClear(clear, 0xffffff);

    WriteU32(self, 0x1c, 1);
    WriteU32(self, 0xe8, 0);
    memset(self + 0xec, 0, 0x120);

    WriteF32(self, 0xec, kZero);
    WriteF32(self, 0x100, kZero);
    WriteF32(self, 0x114, kZero);
    WriteF32(self, 0x128, kZero);

    PSMTXIdentity(m_unkMatrix.value);
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned char* cursor = self;
    GXColor clear;
    unsigned int i = 0;

    USBPcs.IsBigAlloc(0);

    clear.r = 0;
    clear.g = 0;
    clear.b = 0;
    clear.a = 0;
    GXSetCopyClear(clear, 0xffffff);

    m_usbStream.DeleteBuffer();
    MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(self + 0xbc)));
    WriteU32(self, 0x3bc, 0);

    do {
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x2bc)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x2fc)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x23c)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x33c)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x37c)));
        MemFree__18CMaterialEditorPcsFPv(this, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(cursor + 0x27c)));
        i += 1;
        cursor += 4;
    } while (i < 0x10);

    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, reinterpret_cast<void*>(*reinterpret_cast<unsigned int*>(self + 0x4)));
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned char* cursor = self;
    unsigned int i = 0;

    WriteU32(self, 0x3BC, 0);

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
	USBPcs.mccReadData();
	
	if (m_usbStream.IsUSBStreamDataDone()) {
		SetUSBData();
		m_usbStream.SetUSBStreamDataDone();
	}
	
	// Set up scaling and translation vectors
	float scaleX = 4.0f;
	float scaleY = 4.0f; 
	float scaleZ = 4.0f;
	float transX = 1.0f;
	float transY = 1.0f;
	float transZ = 1.0f;
	
	// Set viewer position
	float posX = field268_0x15c.x;
	float posY = field268_0x15c.y;
	float posZ = -field268_0x15c.z;
	
	// Call SetViewerSRT with SRT structure
	struct SRT {
		float x, y, z;
	} srtPos = { posX, posY, posZ };
	// CameraPcs.SetViewerSRT(&srtPos);
	
	Mtx cameraMatrix;
	PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMatrix);
	
	// Copy matrix data from fields to m_unkMatrix
	m_unkMatrix.value[0][0] = *(float*)&field_0x12c;
	m_unkMatrix.value[0][1] = *(float*)&field_0x130;
	m_unkMatrix.value[0][2] = *(float*)&field_0x134;
	m_unkMatrix.value[0][3] = *(float*)&field_0x138;
	m_unkMatrix.value[1][0] = *(float*)&field_0x13c;
	m_unkMatrix.value[1][1] = *(float*)&field_0x140;
	m_unkMatrix.value[1][2] = *(float*)&field_0x144;
	m_unkMatrix.value[1][3] = *(float*)&field_0x148;
	m_unkMatrix.value[2][0] = *(float*)&field_0x14c;
	m_unkMatrix.value[2][1] = *(float*)&field_0x150;
	m_unkMatrix.value[2][2] = *(float*)&field_0x154;
	m_unkMatrix.value[2][3] = *(float*)&field_0x158;
	
	PSMTXTranspose(m_unkMatrix.value, m_unkMatrix.value);
	
	// Negate specific matrix elements
	m_unkMatrix.value[0][1] = -m_unkMatrix.value[0][1];
	m_unkMatrix.value[1][1] = -m_unkMatrix.value[1][1]; 
	m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
	m_unkMatrix.value[2][0] = -m_unkMatrix.value[2][0];
	m_unkMatrix.value[2][1] = -m_unkMatrix.value[2][1];
	m_unkMatrix.value[2][2] = -m_unkMatrix.value[2][2];
	
	// Apply scaling transformations
	Mtx scaleMatrix;
	PSMTXIdentity(scaleMatrix);
	scaleMatrix[1][1] = -1.0f;
	PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);
	
	PSMTXIdentity(scaleMatrix);
	scaleMatrix[2][2] = -1.0f;
	PSMTXConcat(m_unkMatrix.value, scaleMatrix, m_unkMatrix.value);
	
	PSMTXConcat(cameraMatrix, m_unkMatrix.value, cameraMatrix);
	GXLoadPosMtxImm(cameraMatrix, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialEditorPcs::drawViewer()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (DAT_8032ed1c == 0) {
        DAT_8032ed18 = DAT_8032fcb4;
        DAT_8032ed1c = 1;
    }
    if (DAT_8032ed24 == 0) {
        DAT_8032ed20 = 0;
        DAT_8032ed24 = 1;
    }

    DAT_8032ed20 = DAT_8032ed20 + 1;
    int sign = DAT_8032ed20 >> 31;
    int idx = (sign * 4 | (unsigned int)(((DAT_8032ed20 >> 4) * 0x40000000) + sign) >> 30) - sign;
    Printf__8CGraphicFPce(&Graphic, s_MaterialEditor, (int)(char)DAT_8032ed18[idx]);

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
        matColor.r = static_cast<unsigned char>((DAT_8032fca8 >> 24) & 0xFF);
        matColor.g = static_cast<unsigned char>((DAT_8032fca8 >> 16) & 0xFF);
        matColor.b = static_cast<unsigned char>((DAT_8032fca8 >> 8) & 0xFF);
        matColor.a = static_cast<unsigned char>(DAT_8032fca8 & 0xFF);
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
    f32 maxInit = lbl_8032FCAC;
    f32 minInit = lbl_8032FCB0;
    minPos.x = maxInit;
    minPos.y = maxInit;
    minPos.z = maxInit;
    maxPos.x = minInit;
    maxPos.y = minInit;
    maxPos.z = minInit;

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
