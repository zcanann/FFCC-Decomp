#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/file.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/math.h"
#include "ffcc/p_game.h"

#include <string.h>

extern "C" void __dl__FPv(void* ptr);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void pppPartInit__8CPartMngFv2(CPartMng* partMng);
extern "C" void pppCreateHeap__FP9_pppEnvStUl(_pppEnvSt*, unsigned long);
extern "C" unsigned int CheckSum__FPvi(void*, int);
extern "C" void pppStopSe__FP9_pppMngStP7PPPSEST(_pppMngSt*, PPPSEST*);
extern "C" float ppvScreenMatrix[4][4];
extern "C" float ppvScreenMatrix0[4][4];
extern "C" float ppvCameraMatrix02[3][4];
extern "C" Mtx ppvUnitMatrix;
extern "C" Vec ppvZeroVector;
extern "C" float FLOAT_8032fe5c;
extern "C" float FLOAT_8032fe60;
extern "C" float FLOAT_8032fe64;
extern "C" float FLOAT_8032fe68;
extern "C" float FLOAT_8032fe8c;
extern "C" float FLOAT_8032fe90;
extern "C" float FLOAT_8032fe94;
extern "C" float FLOAT_8032fe98;
extern "C" float FLOAT_8032fe9c;
extern "C" float FLOAT_8032fea0;
extern "C" float FLOAT_8032fea4;
extern "C" float FLOAT_8032fea8;
extern "C" float FLOAT_8032fe4c;
extern "C" float FLOAT_8032fe50;
extern "C" float FLOAT_8032fe54;
extern "C" float FLOAT_8032fe58;
extern "C" float FLOAT_8032ed58;
extern "C" float FLOAT_8032ed5c;
extern "C" float FLOAT_8032ed60;
extern "C" float FLOAT_8032fe18;
extern "C" unsigned char DAT_8032ed68;
extern "C" int DAT_8032ed6c;
extern "C" int DAT_8032ed74;
extern "C" unsigned char DAT_8032ed78;
extern "C" unsigned char DAT_8032ed79;
extern "C" int DAT_8032ed7c;
extern "C" unsigned char DAT_8032ed90;
extern "C" unsigned char DAT_8032ed91;
extern unsigned char CameraPcs[];
extern "C" void __ct__9_pppMngStFv(_pppMngSt* pppMngSt);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void pppSetBlendMode__FUc(unsigned char);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void pppSetFpMatrix__FP9_pppMngSt(_pppMngSt*);
extern "C" void _pppDrawPart__FP9_pppMngSt(_pppMngSt*);
extern "C" void Create__9CGBaseObjFv(CGBaseObj*);
extern "C" void LoadMap__7CMapPcsFiiPvUlUc(void*, int, int, void*, unsigned long, unsigned char);
extern int DAT_8032ed70;
extern unsigned char PartPcs[];
extern unsigned char MapPcs[];
extern CPartMng PartMng;
extern PPPCREATEPARAM g_dcp;
static char s_partMng_cpp_801d8230[] = "partMng.cpp";
static char s_pppGetFreePppDataMngSt_CAN_NOT_ALLOC[] = "pppGetFreePppDataMngSt CAN NOT ALLOC!!\n";
static char s_CheckSum_ERROR_code_0x_x____801d82f0[] = "CheckSum ERROR code[0x%x]!!!";

struct CPtrArrayBare {
    unsigned long m_size;
    unsigned long m_numItems;
    unsigned long m_defaultSize;
    void* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};

/*
 * --INFO--
 * PAL Address: 0x8005f61c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetGrow__21CPtrArray(CPtrArrayBare* ptrArray, int growCapacity)
{
    ptrArray->m_growCapacity = growCapacity;
}

/*
 * --INFO--
 * PAL Address: 0x8005f618
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::CObject::onNewFinished()
{
}

/*
 * --INFO--
 * PAL Address: 0x80059220
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppShapeSt::pppShapeSt()
{
    m_refCount = 0;
    m_inUse = 0;
    m_animData = 0;
    m_displayListData = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800591A4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppShapeSt::~pppShapeSt()
{
    if (m_animData != 0) {
        __dl__FPv(m_animData);
        m_animData = 0;
    }

    if (m_displayListData != 0) {
        __dl__FPv(m_displayListData);
        m_displayListData = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005961C
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppModelSt::pppModelSt()
{
    m_refCount = 0;
    m_isUsed = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800595C8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppModelSt::~pppModelSt()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CPartMng::CPartMng()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005f0fc
 * PAL Size: 1308b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::Create()
{
    static const int kEnvOffset = 0x2351c;
    static const int kPppMngCount = 0x180;
    static const int kPppMngStride = 0x158;

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    _pppEnvSt* env = reinterpret_cast<_pppEnvSt*>(self + kEnvOffset);

    C_MTXPerspective(ppvScreenMatrix, FLOAT_8032fe8c, FLOAT_8032fe90, FLOAT_8032fe94, FLOAT_8032fe58);
    PSMTX44Copy(ppvScreenMatrix, ppvScreenMatrix0);

    memset(self + 0x10, 0, 0x108);

    DAT_8032ed68 = 1;
    DAT_8032ed6c = 0;
    DAT_8032ed70 = 0;
    DAT_8032ed74 = 0;

    if (Game.game.m_currentSceneId == 7) {
        pppCreateHeap__FP9_pppEnvStUl(env, 0x100000);
    } else {
        pppCreateHeap__FP9_pppEnvStUl(env, 0xC0000);
    }

    pppEnvStPtr = env;
    DAT_8032ed7c = 0;

    PSMTXIdentity(ppvUnitMatrix);
    ppvZeroVector.x = FLOAT_8032fe5c;
    ppvZeroVector.y = FLOAT_8032fe5c;
    ppvZeroVector.z = FLOAT_8032fe5c;

    DAT_8032ed78 = 0;
    DAT_8032ed79 = 0;

    PSMTXIdentity(ppvWorldMatrix);
    PSMTXIdentity(ppvWorldMatrix);
    PSMTXIdentity(ppvCameraMatrix0);
    PSMTXCopy(ppvCameraMatrix0, ppvCameraMatrix0);

    memset(self + 0x1d4, 0, 0x600);

    for (int i = 0; i < kPppMngCount; i++) {
        unsigned char* mng = self + (i * kPppMngStride);
        *reinterpret_cast<int*>(mng + 0x14) = -0x1000;
        *reinterpret_cast<int*>(mng + 0x12c) = -1;
        *reinterpret_cast<int*>(mng + 0x11c) = -1;
        *reinterpret_cast<unsigned char*>(mng + 0x120) = 0;
        *reinterpret_cast<unsigned char*>(mng + 0x121) = 1;
        *reinterpret_cast<int*>(mng + 0x124) = 0;
        *reinterpret_cast<unsigned char*>(mng + 0x122) = 0;
        *reinterpret_cast<int*>(mng + 0x128) = 0x1e;
    }

    env->m_envParam = FLOAT_8032fe5c;
    env->m_mngStCount = 0x10;
    env->m_isEditMode = 1;

    memset(self + 0x10, 0, 0x108);

    env->m_boxMinX = FLOAT_8032fe98;
    env->m_boxMaxX = FLOAT_8032fe9c;
    env->m_boxMinY = FLOAT_8032fea0;
    env->m_boxMaxY = FLOAT_8032fea4;
    env->m_boxMinZ = FLOAT_8032fe9c;
    env->m_boxMaxZ = FLOAT_8032fea8;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDumpMngSt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppAmemCacheClear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppAmemCacheCountStart()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppAmemCacheCountEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReleasePmng(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReleasePdt(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGetFreePppMngSt()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005e97c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppGetNumFreePppMngSt()
{
    int freeCount = 0;
    char* pppMngSt = reinterpret_cast<char*>(this);

    int i = 0x30;
    do {
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 4)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 5)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 6)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 7)) == -0x1000) {
            freeCount++;
        }
        pppMngSt += 0xAC0;
        i--;
    } while (i != 0);

    return freeCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGetFreePppDataMngSt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawLine(int, int, int, int, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawLine3D(Vec*, Vec*, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005e388
 * PAL Size: 1524b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::drawCursor()
{
    int cursorX = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x28);
    if (cursorX == 0x7fff) {
        return;
    }

    int cursorY = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2c);

    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)2);
    GXSetChanCtrl((GXChannelID)2, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)2);

    Mtx44 orthoProjection;
    C_MTXOrtho(orthoProjection, FLOAT_8032fe5c, FLOAT_8032fe60, FLOAT_8032fe5c, FLOAT_8032fe64, FLOAT_8032fe5c,
               FLOAT_8032fe68);
    GXSetProjection(orthoProjection, GX_ORTHOGRAPHIC);

    Mtx identity;
    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetZCompLoc(0);
    GXSetCurrentMtx(0);
    _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(1, 4, 5, 1);
    GXSetZMode(0, GX_ALWAYS, 0);
    _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(6, 1, 0, 7, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xff, 0xff, 4);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    pppSetBlendMode__FUc(3);

    _GXColor white;
    white.r = 0xff;
    white.g = 0xff;
    white.b = 0xff;
    white.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x140), (float)(cursorY + 0xd6), FLOAT_8032fe5c);
    GXPosition3f32((float)(cursorX + 0x140), (float)(cursorY + 0xea), FLOAT_8032fe5c);

    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x13f), (float)(cursorY + 0xd6), FLOAT_8032fe5c);
    GXPosition3f32((float)(cursorX + 0x13f), (float)(cursorY + 0xea), FLOAT_8032fe5c);

    _GXColor yellow;
    yellow.r = 0x00;
    yellow.g = 0x00;
    yellow.b = 0x00;
    yellow.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, yellow);
    GXSetChanMatColor((GXChannelID)4, yellow);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x12c), (float)(cursorY + 0xe0), FLOAT_8032fe5c);
    GXPosition3f32((float)(cursorX + 0x154), (float)(cursorY + 0xe0), FLOAT_8032fe5c);

    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x141), (float)(cursorY + 0xd7), FLOAT_8032fe5c);
    GXPosition3f32((float)(cursorX + 0x141), (float)(cursorY + 0xeb), FLOAT_8032fe5c);

    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x142), (float)(cursorY + 0xd7), FLOAT_8032fe5c);
    GXPosition3f32((float)(cursorX + 0x142), (float)(cursorY + 0xeb), FLOAT_8032fe5c);

    GXSetChanAmbColor((GXChannelID)4, white);
    GXSetChanMatColor((GXChannelID)4, white);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x12d), (float)(cursorY + 0xe1), FLOAT_8032fe5c);
    GXPosition3f32((float)(cursorX + 0x155), (float)(cursorY + 0xe1), FLOAT_8032fe5c);

    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::render3Dcursor()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Screen2world(Vec&, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGet2Dpos()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawStart()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::setProcSpeed(ProcSpdSt*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::initGraphicSystem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::allFreeFPrim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::SetFp()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::fpIDon(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::fpIDoff(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::InitMaterialSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::ReadTex(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReadRsd(CChunkFile&, pppModelSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReadShp(CChunkFile&, pppShapeSt*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005d92c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppEditGetViewPos(Vec* viewPos)
{
	viewPos->x = ppvCameraMatrix0[0][3];
	viewPos->y = ppvCameraMatrix0[1][3];
	viewPos->z = ppvCameraMatrix0[2][3];
}

/*
 * --INFO--
 * PAL Address: 0x8005d900
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppEditGetViewMatrix(float (*viewMatrix)[4])
{
	PSMTXCopy(ppvCameraMatrix0, viewMatrix);
}

/*
 * --INFO--
 * PAL Address: 0x8005d8d4
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppEditGetProjectionMatrix(float (*projectionMatrix)[4])
{
	PSMTX44Copy(ppvScreenMatrix0, projectionMatrix);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditAllReleaseResource()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005c1c4
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CheckSum(char* packet, unsigned long code, unsigned long packetSize)
{
    if (packet == 0 || packetSize <= 0x20) {
        return;
    }

    int checkSum = 0x12345678;
    char* cursor = packet + 0x20;
    unsigned long remaining = packetSize - 0x20;

    while (remaining > 0) {
        checkSum += *cursor++;
        remaining--;
    }

    if (checkSum != *reinterpret_cast<int*>(packet)) {
        Graphic.Printf(s_CheckSum_ERROR_code_0x_x____801d82f0, code);
        Graphic.DrawDebugString();
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005c230
 * PAL Size: 5168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDataRcv(unsigned long code, char* packet, unsigned long packetSize)
{
    if (packet == 0 || packetSize <= 0x20) {
        return;
    }

    CheckSum(packet, code, packetSize);

    switch (code) {
    case 0x14:
        DAT_8032ed70 = 0;
        return;
    case 0x15:
        DAT_8032ed70 = 1;
        return;
    case 0x1f:
    case 0xfe:
    case 0xff:
    default:
        return;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppEditSetProjection2D()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetFog(unsigned char, unsigned char, unsigned char, unsigned char, float, float)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005bbc0
 * PAL Size: 1648b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditBeforeCalc()
{
    char* self = reinterpret_cast<char*>(this);
    int* lastEnvCmd = reinterpret_cast<int*>(self + 0x23560);
    CGObject** editorObj = reinterpret_cast<CGObject**>(self + 0x80c);

    switch (*lastEnvCmd) {
    case 1:
    case 2: {
        // Camera matrix handed over from editor uses opposite handedness on these axes.
        *reinterpret_cast<float*>(self + 0x60) = -*reinterpret_cast<float*>(self + 0x60);
        *reinterpret_cast<float*>(self + 0x68) = -*reinterpret_cast<float*>(self + 0x68);
        *reinterpret_cast<float*>(self + 0x44) = -*reinterpret_cast<float*>(self + 0x44);
        *reinterpret_cast<float*>(self + 0x54) = -*reinterpret_cast<float*>(self + 0x54);
        *reinterpret_cast<float*>(self + 0x6c) = -*reinterpret_cast<float*>(self + 0x6c);
        *reinterpret_cast<float*>(self + 0x6c) *= *reinterpret_cast<float*>(self + 0x70);

        PSMTXCopy(reinterpret_cast<float(*)[4]>(self + 0x40), ppvCameraMatrix02);
        C_MTXPerspective(ppvScreenMatrix, FLOAT_8032fe4c, FLOAT_8032fe50, FLOAT_8032fe54, FLOAT_8032fe58);
        FLOAT_8032ed58 = ppvScreenMatrix[2][0];
        FLOAT_8032ed5c = ppvScreenMatrix[2][1];
        FLOAT_8032ed60 = ppvScreenMatrix[2][3];
        PSMTXCopy(ppvCameraMatrix02, ppvCameraMatrix0);
        PSMTX44Copy(ppvScreenMatrix, ppvScreenMatrix0);

        _GXColor clearColor;
        clearColor.r = *reinterpret_cast<unsigned char*>(self + 0x158);
        clearColor.g = *reinterpret_cast<unsigned char*>(self + 0x159);
        clearColor.b = *reinterpret_cast<unsigned char*>(self + 0x15a);
        clearColor.a = 0xFF;
        GXSetCopyClear(clearColor, 0x00FFFFFF);

        unsigned char useFog = *reinterpret_cast<unsigned char*>(self + 0x15c);
        _GXColor fogColor;
        fogColor.r = *reinterpret_cast<unsigned char*>(self + 0x15d);
        fogColor.g = *reinterpret_cast<unsigned char*>(self + 0x15e);
        fogColor.b = *reinterpret_cast<unsigned char*>(self + 0x15f);
        fogColor.a = 0;

        if (useFog != 0) {
            Graphic.SetFogColor(fogColor);
            if (*lastEnvCmd == 1) {
                Graphic.SetFogParam(*reinterpret_cast<float*>(self + 0x160), *reinterpret_cast<float*>(self + 0x164));
            } else {
                Graphic.SetFogParam(*reinterpret_cast<float*>(self + 0x164), *reinterpret_cast<float*>(self + 0x160));
            }
        } else {
            fogColor.r = 0;
            fogColor.g = 0;
            fogColor.b = 0;
            fogColor.a = 0;
            Graphic.SetFogColor(fogColor);
            Graphic.SetFogParam(FLOAT_8032fe5c, FLOAT_8032fe5c);
        }

        DAT_8032ed6c = 1;
        break;
    }
    case 0x18:
        Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0x7a4);
        LoadMap__7CMapPcsFiiPvUlUc(
            MapPcs,
            *reinterpret_cast<int*>(self + 0x188),
            *reinterpret_cast<int*>(self + 0x18c),
            0,
            0,
            0
        );
        *reinterpret_cast<unsigned int*>(MapPcs + 0x180) = 1;
        break;
    case 0x19: {
        Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0x7ad);

        if (*editorObj != 0) {
            if ((*editorObj)->m_charaModelHandle != 0) {
                delete (*editorObj)->m_charaModelHandle;
                (*editorObj)->m_charaModelHandle = 0;
            }
            __dl__FPv(*editorObj);
            *editorObj = 0;
        }

        CMemory::CStage* stageLoad = *reinterpret_cast<CMemory::CStage**>(PartPcs + 0x1c);
        *editorObj = static_cast<CGObject*>(__nw__FUlPQ27CMemory6CStagePci(0x518, stageLoad, s_partMng_cpp_801d8230, 0x7b5));
        if (*editorObj != 0) {
            Create__9CGBaseObjFv(*editorObj);

            CCharaPcs::CHandle* handle = new (stageLoad, s_partMng_cpp_801d8230, 0x7b7) CCharaPcs::CHandle;
            (*editorObj)->m_charaModelHandle = handle;
            if (handle != 0) {
                handle->Add();
                handle->m_charaNo = 3;
                handle->LoadModel(
                    *reinterpret_cast<int*>(self + 0x190),
                    *reinterpret_cast<unsigned long*>(self + 0x194),
                    *reinterpret_cast<unsigned long*>(self + 0x198),
                    0,
                    -1,
                    0,
                    0
                );

                if (handle == (*editorObj)->m_charaModelHandle && !handle->IsModelLoaded(1)) {
                    delete handle;
                    (*editorObj)->m_charaModelHandle = 0;
                }
            }
        }
        break;
    }
    case 0x1a:
        if (*editorObj != 0) {
            Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0x7ce);
            if (DAT_8032ed91 == 0) {
                DAT_8032ed90 = 0;
                DAT_8032ed91 = 1;
            }

            CCharaPcs::CHandle* handle = (*editorObj)->m_charaModelHandle;
            if (handle != 0) {
                handle->LoadAnim(reinterpret_cast<char*>(self + 0x19c), DAT_8032ed90, 0, -1, -1, -1, 0);
                handle->SetAnim(DAT_8032ed90, -1, -1, -1, 0);
                DAT_8032ed90++;
            }
        }
        break;
    case 0x1b:
        *reinterpret_cast<unsigned int*>(MapPcs + 0x180) = *reinterpret_cast<unsigned int*>(self + 0x1bc);
        break;
    case 0x1c:
        if (*editorObj != 0 && (*editorObj)->m_charaModelHandle != 0) {
            if (*reinterpret_cast<int*>(self + 0x1c0) != 0) {
                (*editorObj)->m_charaModelHandle->m_flags |= 1;
            } else {
                (*editorObj)->m_charaModelHandle->m_flags &= ~1;
            }
        }
        break;
    default:
        break;
    }

    *lastEnvCmd = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditPartCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditDrawShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditDraw()
{
    static const int kPppMngCount = 0x180;
    static const int kPppMngStride = 0x158;
    static const int kBaseTimeOffset = 0x14;
    static const int kMatrixOffset = 0x78;
    static const int kEndRequestedOffset = 0xe5;
    static const int kDrawPassOffset = 0xed;
    static const int kSlotVisibleOffset = 0xe9;
    static const int kOwnerVisibleOffset = 0xf0;
    static const int kCullRadiusSqOffset = 0x108;
    static const int kCullRadiusOffset = 0x10c;
    static const int kCullYOffsetOffset = 0x110;
    static const int kSortDepthOffset = 0x114;

    if (DAT_8032ed68 != 0) {
        return;
    }

    Mtx invCamera;
    Vec cameraPos;
    Vec partPos;
    Vec cameraDelta;
    Vec viewPos;

    for (int passIndex = 0; passIndex < 4; passIndex++) {
        unsigned char drawPass = 0;
        if (passIndex == 0) {
            drawPass = 8;
        } else if (passIndex == 1) {
            drawPass = 4;
        } else if (passIndex == 2) {
            pppDraw();
            drawPass = 6;
        } else {
            drawPass = 7;
        }

        PSMTXInverse(ppvCameraMatrix0, invCamera);
        cameraPos.x = invCamera[0][3];
        cameraPos.y = invCamera[1][3];
        cameraPos.z = invCamera[2][3];

        char* mng = reinterpret_cast<char*>(this);
        for (int i = 0; i < kPppMngCount; i++) {
            int baseTime = *reinterpret_cast<int*>(mng + kBaseTimeOffset);
            unsigned char endRequested = *reinterpret_cast<unsigned char*>(mng + kEndRequestedOffset);
            unsigned char partDrawPass = *reinterpret_cast<unsigned char*>(mng + kDrawPassOffset);
            unsigned char slotVisible = *reinterpret_cast<unsigned char*>(mng + kSlotVisibleOffset);
            unsigned char ownerVisible = *reinterpret_cast<unsigned char*>(mng + kOwnerVisibleOffset);

            if (endRequested == 0 && baseTime != -0x1000 && partDrawPass == drawPass && baseTime < 0 && slotVisible != 0
                && ownerVisible != 0) {
                partPos.x = *reinterpret_cast<float*>(mng + kMatrixOffset + 0xc);
                partPos.y = *reinterpret_cast<float*>(mng + kMatrixOffset + 0x1c);
                partPos.z = *reinterpret_cast<float*>(mng + kMatrixOffset + 0x2c);

                float cullRadiusSq = *reinterpret_cast<float*>(mng + kCullRadiusSqOffset);
                bool shouldDraw = (cullRadiusSq == 0.0f);
                if (!shouldDraw) {
                    PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                    if (PSVECSquareMag(&cameraDelta) < cullRadiusSq) {
                        CBound bound;
                        float cullRadius = *reinterpret_cast<float*>(mng + kCullRadiusOffset);
                        float cullYOffset = *reinterpret_cast<float*>(mng + kCullYOffsetOffset);
                        Vec min;
                        min.x = partPos.x - cullRadius;
                        min.y = partPos.y;
                        min.z = partPos.z - cullRadius;
                        shouldDraw = (bound.CheckFrustum(min, ppvCameraMatrix0, partPos.y + cullYOffset) != 0);
                    }
                }

                if (shouldDraw) {
                    PSMTXMultVec(ppvCameraMatrix0, &partPos, &viewPos);
                    *reinterpret_cast<float*>(mng + kSortDepthOffset) = viewPos.z;

                    pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
                    pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(*reinterpret_cast<char**>(mng) + 4);
                    pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
                    _pppDrawPart__FP9_pppMngSt(pppMngStPtr);
                }
            }

            mng += kPppMngStride;
        }
    }

    ppvScreenMatrix[2][3] = FLOAT_8032ed60;
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * PAL Address: 0x8005a958
 * PAL Size: 1320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditPartDrawAfter()
{
    static const int kPppMngCount = 0x180;
    static const int kPppMngStride = 0x158;
    static const int kBaseTimeOffset = 0x14;
    static const int kMatrixOffset = 0x78;
    static const int kEndRequestedOffset = 0xe5;
    static const int kDrawPassOffset = 0xed;
    static const int kSlotVisibleOffset = 0xe9;
    static const int kOwnerVisibleOffset = 0xf0;
    static const int kCullRadiusSqOffset = 0x108;
    static const int kCullRadiusOffset = 0x10c;
    static const int kCullYOffsetOffset = 0x110;
    static const int kSortDepthOffset = 0x114;

    if (DAT_8032ed68 != 0) {
        return;
    }

    Mtx invCamera;
    Vec cameraPos;
    Vec partPos;
    Vec cameraDelta;
    Vec viewPos;

    for (int passIndex = 0; passIndex < 3; passIndex++) {
        unsigned char drawPass = static_cast<unsigned char>(passIndex + 5);

        PSMTXInverse(ppvCameraMatrix0, invCamera);
        cameraPos.x = invCamera[0][3];
        cameraPos.y = invCamera[1][3];
        cameraPos.z = invCamera[2][3];

        char* mng = reinterpret_cast<char*>(this);
        for (int i = 0; i < kPppMngCount; i++) {
            int baseTime = *reinterpret_cast<int*>(mng + kBaseTimeOffset);
            unsigned char endRequested = *reinterpret_cast<unsigned char*>(mng + kEndRequestedOffset);
            unsigned char partDrawPass = *reinterpret_cast<unsigned char*>(mng + kDrawPassOffset);
            unsigned char slotVisible = *reinterpret_cast<unsigned char*>(mng + kSlotVisibleOffset);
            unsigned char ownerVisible = *reinterpret_cast<unsigned char*>(mng + kOwnerVisibleOffset);

            if (endRequested == 0 && baseTime != -0x1000 && partDrawPass == drawPass && baseTime < 0 && slotVisible != 0
                && ownerVisible != 0) {
                partPos.x = *reinterpret_cast<float*>(mng + kMatrixOffset + 0xc);
                partPos.y = *reinterpret_cast<float*>(mng + kMatrixOffset + 0x1c);
                partPos.z = *reinterpret_cast<float*>(mng + kMatrixOffset + 0x2c);

                float cullRadiusSq = *reinterpret_cast<float*>(mng + kCullRadiusSqOffset);
                bool shouldDraw = (cullRadiusSq == 0.0f);
                if (!shouldDraw) {
                    PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                    if (PSVECSquareMag(&cameraDelta) < cullRadiusSq) {
                        CBound bound;
                        float cullRadius = *reinterpret_cast<float*>(mng + kCullRadiusOffset);
                        float cullYOffset = *reinterpret_cast<float*>(mng + kCullYOffsetOffset);
                        Vec min;
                        min.x = partPos.x - cullRadius;
                        min.y = partPos.y;
                        min.z = partPos.z - cullRadius;
                        shouldDraw = (bound.CheckFrustum(min, ppvCameraMatrix0, partPos.y + cullYOffset) != 0);
                    }
                }

                if (shouldDraw) {
                    PSMTXMultVec(ppvCameraMatrix0, &partPos, &viewPos);
                    *reinterpret_cast<float*>(mng + kSortDepthOffset) = viewPos.z;

                    pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
                    pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(*reinterpret_cast<char**>(mng) + 4);
                    pppSetFpMatrix__FP9_pppMngSt(pppMngStPtr);
                    _pppDrawPart__FP9_pppMngSt(pppMngStPtr);
                }
            }

            mng += kPppMngStride;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005a92c
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSetProjection()
{
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * PAL Address: 0x8005a8c0
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppSetRendMatrix()
{
    PSMTX44Copy(*reinterpret_cast<Mtx44*>(CameraPcs + 0x48), ppvScreenMatrix);
    PSMTXCopy(*reinterpret_cast<Mtx*>(CameraPcs + 4), ppvCameraMatrix0);
    FLOAT_8032ed58 = ppvScreenMatrix[2][0];
    FLOAT_8032ed5c = ppvScreenMatrix[2][1];
    FLOAT_8032ed60 = ppvScreenMatrix[2][3];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppPartCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppRefCnt0Up()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDumpCacheIdx()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawPppMngSt(Vec&, _pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawPrio(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawPrioPdtFpno(unsigned char, short, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawIdx(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppPartDrawAfter()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80059cac
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppPartDead()
{
    Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0xb3d);

    char* pppMngSt = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if (baseTime != -0x1000 && baseTime < 0) {
            unsigned char isFinished = *reinterpret_cast<unsigned char*>(pppMngSt + 0xe6);
            unsigned char endRequested = *reinterpret_cast<unsigned char*>(pppMngSt + 0xe5);
            if (isFinished != 0 || endRequested != 0) {
                pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(*reinterpret_cast<char**>(pppMngSt) + 4);
                pppMngStPtr = reinterpret_cast<_pppMngSt*>(pppMngSt);
                _pppAllFreePObject(reinterpret_cast<_pppMngSt*>(pppMngSt));
            }
        }
        pppMngSt += 0x158;
    }

    Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0xb5d);
}

/*
 * --INFO--
 * PAL Address: 0x8005992c
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void fn_8005992C(CPartMng* partMng)
{
    char* base = reinterpret_cast<char*>(partMng);
    for (int i = 0; i < 0x10; i++) {
        CFile::CHandle** handleSlot = reinterpret_cast<CFile::CHandle**>(base + 0x2378c + (i * 4));
        CFile::CHandle* handle = *handleSlot;
        if (handle != 0 && File.IsCompleted(handle)) {
            int len = File.GetLength(handle);
            void* readBuffer = File.m_readBuffer;
            void* amemCursor = *reinterpret_cast<void**>(base + 0x236f8);

            Memory.CopyToAMemorySync(readBuffer, amemCursor, (len + 0x1f) & ~0x1f);
            *reinterpret_cast<int*>(base + 0x2370c + (i * 4)) = len;
            *reinterpret_cast<unsigned int*>(base + 0x2374c + (i * 4)) = CheckSum__FPvi(readBuffer, len);
            (*reinterpret_cast<int*>(base + 0x23700))++;
            *reinterpret_cast<char**>(base + 0x236f8) += len;

            File.Close(handle);
            *handleSlot = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80059c44
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppPartInit__8CPartMngFv2(CPartMng* partMng)
{
	char* pppMngSt = reinterpret_cast<char*>(partMng);
	int i = 0;

	*reinterpret_cast<int*>(reinterpret_cast<char*>(partMng) + 0x8) = 0;
	do {
		int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
		if (baseTime != -0x1000 && baseTime < 0) {
			_pppInitPart(reinterpret_cast<_pppMngSt*>(pppMngSt));
		}
		pppMngSt += 0x158;
		i++;
	} while (i < 0x180);
}

void CPartMng::pppPartInit()
{
    pppPartInit__8CPartMngFv2(this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppInitEnv(_pppEnvSt*, _pppDataHead*, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppFileRead(char*, unsigned long&, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::LoadPartNoSyncCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPtx(const char*, int, int, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPmd(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPmd(const char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPan(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPan(const char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPdt(const char*, int, int, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CPartMng::pppGetFreeDataMng()
{
    char* self = reinterpret_cast<char*>(this);
    char* pdtSlot = self + 0x22FD8;
    char* freeSlot = 0;

    for (int i = 0; i < 0x18; i++) {
        if (*reinterpret_cast<_pppDataHead**>(pdtSlot) == 0) {
            freeSlot = pdtSlot;
            break;
        }
        pdtSlot += 0x38;
    }

    if (freeSlot == 0) {
        if (System.m_execParam != 0) {
            System.Printf(s_pppGetFreePppDataMngSt_CAN_NOT_ALLOC);
        }
        OSPanic(s_partMng_cpp_801d8230, 0xD74, "");
        return -1;
    }

    int index = freeSlot - (self + 0x22E18);
    index = index / 0x38 + (index >> 0x1f);
    return index - (index >> 0x1f);
}

/*
 * --INFO--
 * PAL Address: 0x800587a8
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppGetDefaultCreateParam()
{
    g_dcp.m_positionOffsetPtr = 0;
    g_dcp.m_rotationPtr = 0;
    g_dcp.m_scalePtr = 0;
    g_dcp.m_extraPositionPtr = 0;
    g_dcp.m_paramA = 0;
    g_dcp.m_paramB = 0;
    g_dcp.m_lookTargetPtr = 0;
    g_dcp.m_objectHitMask = 0;
    g_dcp.m_cylinderAttribute = 0;
    g_dcp.m_paramC = FLOAT_8032fe18;
    g_dcp.m_paramD = FLOAT_8032fe18;
    g_dcp.m_owner = 0;
    g_dcp.m_soundEffectParams.m_soundEffectHandle = -1;
    g_dcp.m_soundEffectParams.m_soundEffectSlot = -1;
    g_dcp.m_soundEffectParams.m_soundEffectStopFlag = 0;
    g_dcp.m_soundEffectParams.m_soundEffectKind = 1;
    g_dcp.m_soundEffectParams.m_soundEffectStartFrame = 0;
    g_dcp.m_soundEffectParams.m_soundEffectStartedOnce = 0;
    g_dcp.m_soundEffectParams.m_soundEffectFadeFrames = 0x1e;
}

/*
 * --INFO--
 * PAL Address: 0x80058148
 * PAL Size: 1632b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppCreate0(int, int, PPPCREATEPARAM*, int)
{
    // TODO
    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8005810c
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppCreate(int pdtSlotIndex, int fpNo, PPPCREATEPARAM* createParam, int allowFpOverride)
{
    if (DAT_8032ed68 == 0) {
        return pppCreate0(pdtSlotIndex, fpNo, createParam, allowFpOverride);
    }
    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x800580e0
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppGetFreeSlot()
{
    char* self = reinterpret_cast<char*>(this);
    unsigned long slot = *reinterpret_cast<unsigned long*>(self + 0x34);
    slot++;
    *reinterpret_cast<unsigned long*>(self + 0x34) = slot;

    if ((long)slot >= 0x7fffffff) {
        *reinterpret_cast<unsigned long*>(self + 0x34) = 0x10;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80058030
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDeleteSlot(int slot, int checkHitFlags)
{
    char* pppMngSt = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if (baseTime != -0x1000 && *reinterpret_cast<int*>(pppMngSt + 0x100) == slot) {
            if (checkHitFlags == 0 || (*reinterpret_cast<unsigned char*>(pppMngSt + 0x137) & 1) == 0) {
                if (baseTime < 0) {
                    *reinterpret_cast<unsigned char*>(pppMngSt + 0xe5) = 1;
                    pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                                     reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
                } else {
                    *reinterpret_cast<int*>(pppMngSt + 0x14) = -0x1000;
                }
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057fac
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEndSlot(int slot, int checkHitFlags)
{
    char* pppMngSt = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        if (*reinterpret_cast<int*>(pppMngSt + 0x14) != -0x1000
            && *reinterpret_cast<int*>(pppMngSt + 0x100) == slot) {
            if (checkHitFlags == 0 || (*reinterpret_cast<unsigned char*>(pppMngSt + 0x137) & 1) == 0) {
                *reinterpret_cast<unsigned char*>(pppMngSt + 0xe4) = 1;
                pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                                 reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057ee8
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppShowSlot(int slot, unsigned char isVisible)
{
    char* pppMngSt = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        if (*reinterpret_cast<int*>(pppMngSt + 0x14) != -0x1000
            && *reinterpret_cast<int*>(pppMngSt + 0x100) == slot) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9) = isVisible;
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeletePart(int index)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    pppMngSt += 0x158 * index;

    int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
    if (baseTime < 0) {
        *reinterpret_cast<unsigned char*>(pppMngSt + 0xe5) = 1;
        pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                         reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
    } else {
        *reinterpret_cast<int*>(pppMngSt + 0x14) = -0x1000;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndPart(int index)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    pppMngSt += 0x158 * index;

    *reinterpret_cast<unsigned char*>(pppMngSt + 0xe4) = 1;
    pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                     reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
}

/*
 * --INFO--
 * PAL Address: 0x80057e40
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
PPPIFPARAM* CPartMng::pppGetIfDt(short index)
{
	return reinterpret_cast<PPPIFPARAM*>(reinterpret_cast<char*>(this) + (index * 0x158) + 0x130);
}

/*
 * --INFO--
 * PAL Address: 0x80057e2c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppShowIdx(short index, unsigned char visible)
{
	reinterpret_cast<unsigned char*>(this)[(index * 0x158) + 0xe9] = visible;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppFieldShowFpNo(short fieldNo, unsigned char visible)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    int i = 0x60;

    do {
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 0)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 0)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 0)) = visible;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 1)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 1)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 1)) = visible;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 2)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 2)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 2)) = visible;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 3)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 3)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 3)) = visible;
        }

        pppMngSt += 0x560;
        i--;
    } while (i != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppFieldEndFpNo(short fieldNo)
{
    char* pppMngSt = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if ((baseTime != -0x1000) && (*reinterpret_cast<short*>(pppMngSt + 0x74) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76) == fieldNo)) {
            if (baseTime < 0) {
                *reinterpret_cast<unsigned char*>(pppMngSt + 0xe4) = 1;
                pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                                 reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
            } else {
                *reinterpret_cast<int*>(pppMngSt + 0x14) = -0x1000;
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetDeltaIdx(short index, long color)
{
    *reinterpret_cast<long*>(reinterpret_cast<char*>(this) + (index * 0x158) + 0x2ac0) = color;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetDeltaSlot(int slot, long color)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    int i = 0x40;

    do {
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 0)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 0)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 0)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 0)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 0)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 1)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 1)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 1)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 1)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 1)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 2)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 2)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 2)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 2)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 2)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 3)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 3)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 3)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 3)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 3)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 4)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 4)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 4)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 4)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 4)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 4)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 5)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 5)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 5)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 5)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 5)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 5)) = static_cast<unsigned char>(color & 0xff);
        }

        pppMngSt += 0x810;
        i--;
    } while (i != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetLocSlot(int slot, Vec* position)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    int i = 0x60;

    do {
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 0)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 0)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 0)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 0)) = position->z;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 1)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 1)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 1)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 1)) = position->z;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 2)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 2)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 2)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 2)) = position->z;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 3)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 3)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 3)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 3)) = position->z;
        }

        pppMngSt += 0x560;
        i--;
    } while (i != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeleteCHandle(CCharaPcs::CHandle* handle)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if (baseTime != -0x1000) {
            unsigned char mode = *reinterpret_cast<unsigned char*>(pppMngSt + 0xe7);
            if (mode == 3 || (mode >= 5 && mode <= 7) || mode == 8) {
                void* owner = *reinterpret_cast<void**>(pppMngSt + 0xd8);
                if (owner != 0 &&
                    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<char*>(owner) + 0xf8) == handle) {
                    if (baseTime < 0) {
                        *reinterpret_cast<unsigned char*>(pppMngSt + 0xe5) = 1;
                        pppStopSe__FP9_pppMngStP7PPPSEST(
                            reinterpret_cast<_pppMngSt*>(pppMngSt),
                            reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
                    } else {
                        *reinterpret_cast<int*>(pppMngSt + 0x14) = -0x1000;
                    }
                }
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndCHandle(CCharaPcs::CHandle* handle)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        if (*reinterpret_cast<int*>(pppMngSt + 0x14) != -0x1000) {
            unsigned char mode = *reinterpret_cast<unsigned char*>(pppMngSt + 0xe7);
            if (mode == 3 || (mode >= 5 && mode <= 7) || mode == 8) {
                void* owner = *reinterpret_cast<void**>(pppMngSt + 0xd8);
                if (owner != 0 &&
                    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<char*>(owner) + 0xf8) == handle) {
                    *reinterpret_cast<unsigned char*>(pppMngSt + 0xe4) = 1;
                    pppStopSe__FP9_pppMngStP7PPPSEST(
                        reinterpret_cast<_pppMngSt*>(pppMngSt),
                        reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
                }
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppIsDeadCHandle(CCharaPcs::CHandle* handle)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        if (*reinterpret_cast<int*>(pppMngSt + 0x14) != -0x1000) {
            unsigned char mode = *reinterpret_cast<unsigned char*>(pppMngSt + 0xe7);
            if (mode == 3 || (mode >= 5 && mode <= 7) || mode == 8) {
                void* owner = *reinterpret_cast<void**>(pppMngSt + 0xd8);
                if (owner != 0 &&
                    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<char*>(owner) + 0xf8) == handle) {
                    return;
                }
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeleteAll()
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if (baseTime != -0x1000) {
            if (baseTime < 0) {
                *reinterpret_cast<unsigned char*>(pppMngSt + 0xe5) = 1;
                pppStopSe__FP9_pppMngStP7PPPSEST(
                    reinterpret_cast<_pppMngSt*>(pppMngSt),
                    reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
            } else {
                *reinterpret_cast<int*>(pppMngSt + 0x14) = -0x1000;
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDestroyAll()
{
    Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0x116f);

    char* pppMngSt = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        if (*reinterpret_cast<int*>(pppMngSt + 0x14) != -0x1000 && *reinterpret_cast<void**>(pppMngSt) != 0) {
            _pppAllFreePObject(reinterpret_cast<_pppMngSt*>(pppMngSt));
        }
        pppMngSt += 0x158;
    }

    Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0x117b);
}

/*
 * --INFO--
 * PAL Address: 0x8005f624
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_partMng_cpp(void)
{
    __construct_array(reinterpret_cast<unsigned char*>(&PartMng) + 0x2A18, (void (*)(void*))__ct__9_pppMngStFv, 0,
                      sizeof(_pppMngSt), 0x180);

    g_dcp.m_soundEffectParams.m_soundEffectHandle = -1;
    g_dcp.m_soundEffectParams.m_soundEffectSlot = -1;
    g_dcp.m_soundEffectParams.m_soundEffectStopFlag = 0;
    g_dcp.m_soundEffectParams.m_soundEffectKind = 1;
    g_dcp.m_soundEffectParams.m_soundEffectStartFrame = 0;
    g_dcp.m_soundEffectParams.m_soundEffectStartedOnce = 0;
    g_dcp.m_soundEffectParams.m_soundEffectFadeFrames = 30;
    g_dcp.m_hitParamA = 0;
    g_dcp.m_hitParamB = 0;
    g_dcp.m_hitObjectCount = 0;
    g_dcp.m_hitFlags = 0;
    g_dcp.m_positionOffsetPtr = 0;
    g_dcp.m_rotationPtr = 0;
    g_dcp.m_scalePtr = 0;
    g_dcp.m_extraPositionPtr = 0;
    g_dcp.m_paramA = 0;
    g_dcp.m_paramB = 0;
    g_dcp.m_lookTargetPtr = 0;
    g_dcp.m_objectHitMask = 0;
    g_dcp.m_cylinderAttribute = 0;
    g_dcp.m_paramC = 1.0f;
    g_dcp.m_paramD = 1.0f;
    g_dcp.m_owner = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005f6dc
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__9_pppMngStFv(_pppMngSt* pppMngSt)
{
    char* base = reinterpret_cast<char*>(pppMngSt);
    PPPSEST* soundEffectData = reinterpret_cast<PPPSEST*>(base + 0x11c);
    PPPIFPARAM* hitParams = reinterpret_cast<PPPIFPARAM*>(base + 0x130);

    soundEffectData->m_soundEffectHandle = -1;
    soundEffectData->m_soundEffectSlot = -1;
    soundEffectData->m_soundEffectStopFlag = 0;
    soundEffectData->m_soundEffectKind = 1;
    soundEffectData->m_soundEffectStartFrame = 0;
    soundEffectData->m_soundEffectStartedOnce = 0;
    soundEffectData->m_soundEffectFadeFrames = 30;

    hitParams->m_particleIndex = 0;
    hitParams->m_classId = 0;
    hitParams->m_hitObjectCount = 0;
    hitParams->m_hitFlags = 0;
}
