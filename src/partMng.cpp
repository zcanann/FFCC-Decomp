#include "ffcc/ptrarray.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/chunkfile.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/file.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/map.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/p_map.h"
#include "ffcc/p_usb.h"
#include "ffcc/p_tina.h"
#include "ffcc/textureman.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/pppfunctbl.h"
#include "ffcc/ppp_linkage.h"
#include "ffcc/pppShape.h"
#include "ffcc/linkage.h"
extern "C" {
extern float ppvScreenMatrixXbuff;
extern float ppvScreenMatrixYbuff;
extern float ppvScreenMatrixZbuff;
}
#include "ffcc/stopwatch.h"

#include <string.h>
#include <dolphin/gx/GXCpu2Efb.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <PowerPC_EABI_Support/Runtime/New.h>

extern "C" {
extern Mtx ppvCameraMatrix;
extern float ppvChrScl[3];
extern Mtx ppvUnitMatrix;
extern Vec ppvZeroVector;
}
extern char g_StrTmp[0x400];
extern "C" int LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii(
    void* self, int, unsigned long, unsigned long, unsigned long, int, int, int);
static inline int pppLoadModelRet(
    CCharaPcs::CHandle* h, int a, unsigned long b, unsigned long c,
    unsigned long d, int e, int f, int g) {
    return LoadModel__Q29CCharaPcs7CHandleFiUlUlUliii(h, a, b, c, d, e, f, g);
}

inline CGBaseObj::CGBaseObj()
{
}

inline CGObject::CGObject()
{
}
extern "C" const double kPartMngZeroDouble = 0.0;
extern "C" const float kPartMngAngleHalfUnit = 32768.0f;
extern "C" const float kPartMngHalfTurnDegrees = 180.0f;
extern "C" const float kPartMngOne = 1.0f;
extern "C" const char sPartMngEmptyString[4] = "";
extern "C" const char sPdtPathFmt[] = "%s.pdt";
extern "C" const char sPanPathFmt[] = "%s.pan";
extern "C" const char sPmdPathFmt[] = "%s.pmd";
extern "C" const char sPtxPathFmt[] = "%s.ptx";
extern "C" const double kPartMngMinusOneDouble = -1.0;
extern "C" const float kPartMngFrustumCullLimit = -100000000.0f;
extern "C" const float kPartMngPppFovY = 25.0f;
extern "C" const float kPartMngPppAspect = 1.3333334f;
extern "C" const float kPartMngPppNear = 10.0f;
extern "C" const float kPartMngPppFar = 10000.0f;
extern "C" const float kPartMngZero = 0.0f;
extern "C" const float kPartMngOrthoHeight = 448.0f;
extern "C" const float kPartMngOrthoWidth = 640.0f;
extern "C" const float kPartMngOrthoFar = -100.0f;
extern "C" const float kPartMngCullRadiusSqMax = 3.4028235e38f;
extern "C" const float kPartMngCullRadius = 100.0f;
extern "C" const float kPartMngScreenHalfHeight = 224.0f;
extern "C" const float kPartMngDepthUnit = 16777216.0f;
extern "C" const float kPartMngScreenHalfWidth = 320.0f;
extern "C" const double kPartMngS32ToDoubleBias = 4503601774854144.0;
extern "C" const char sPartMngTripleNewline[] = "\n\n\n";
extern "C" const float kPartMngScreenFovY = 33.3f;
extern "C" const float kPartMngScreenAspect = 0.93333334f;
extern "C" const float kPartMngScreenNear = 0.125f;
extern "C" const float kPartMngEnvBoxMinX = 200.0f;
extern "C" const float kPartMngEnvBoxMaxXz = 400.0f;
extern "C" const float kPartMngEnvBoxMinY = 300.0f;
extern "C" const float kPartMngEnvBoxMaxY = 600.0f;
extern "C" const float kPartMngEnvBoxMaxZ = 800.0f;
extern "C" {
extern int ppvSysStopPartF;
extern int ppvSysGoPartF;
extern void* ppvHookFuncTbl;
unsigned char gPppDefaultValueBuffer[0x40] = {0};
int gPppHeapUseRateWords[3] = {0, 0, 0};
unsigned char gPppInConstructor = 0;
signed char gPppInSubFrameCalc = 0;
extern int ppvEmptyLoop;
unsigned char gPppEditorAnimIndex = 0;
unsigned char gPppEditorAnimIndexInitialized = 0;
int gPppCalcDisabled = 0;
}
CPartMng PartMng;
static PPPCREATEPARAM g_dcp;
static const char s_partMng_cpp[] = "partMng.cpp";
static const char sPppCreateLogFmt[] =
    "pppCreate0 pdtID=%d fpno=%d mngNo=%d name=%s\n";
static const char sPppFreeDataMngAllocError[] = "pppGetFreePppDataMngSt CAN NOT ALLOC !!!\n";
static const char s_ReadPdtLogFormat[] = "ReadPdt fn=%s\n";
static const char s_CanNotReadFormat[] = "CAN NOT READ %s !!!!!!\n";
static const char s_ReadPanLogFormat[] = "ReadPan fn=%s\n";
static const char s_ReadPmdLogFormat[] = "ReadPmd fn=%s\n";
static const char s_ReadPtxLogFormat[] = "ReadPtx fn=%s\n";
static const char sPartMngChecksumErrorFmt[] = "CheckSum ERROR code=0x%x!!!\n";
static const char sPartMngDumpSeparator[] = "----------------------------------\n";
static const char sPartMngDumpEntryFmt[] =
    "  prioTime=%d  prio=%d  heapSize=%d  pdtID=%2d  fpno=%3d   mngNo=%d  %s\n";
static const char sPartMngHeapSummaryFmt[] =
    "HEAP TOTAL=%dKbyte  USE=%dKbyte  FREE=%dKbyte\n";

enum PppChunkId {
    kChunkNAME = 0x4E414D45,
    kChunkPDT = 0x50445420,
    kChunkPDTS = 0x50445453,
    kChunkRSDM = 0x5253444D,
    kChunkRSET = 0x52534554,
    kChunkSHPM = 0x5348504D,
    kChunkSSET = 0x53534554,
    kChunkTSET = 0x54534554,
};

struct CPartMngLoadState {
    unsigned char m_unk0[0x236F4];
    unsigned int m_partAMemBase;
    unsigned int m_partAMemCursor;
    unsigned int m_partLoadCacheParam;
    unsigned int m_partChunkIndex;
    unsigned int m_asyncHandleCount;
    int m_partLoadMode;
    unsigned int m_partChunkSize[16];
    unsigned int m_partChunkChecksum[16];
    CFile::CHandle* m_partAsyncBusy[16];
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
template <>
#pragma dont_inline on
void CPtrArray<CTexture*>::SetGrow(int growCapacity)
{
    m_growCapacity = growCapacity;
}
#pragma dont_inline reset

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
        delete reinterpret_cast<u8*>(m_animData);
        m_animData = 0;
    }

    if (m_displayListData != 0) {
        delete reinterpret_cast<u8*>(m_displayListData);
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
    static const int kPppMngCount = 0x180;
    static const int kPppMngStride = 0x158;

    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    C_MTXPerspective(ppvScreenMatrix, kPartMngScreenFovY, kPartMngScreenAspect, kPartMngScreenNear, kPartMngPppFar);
    PSMTX44Copy(ppvScreenMatrix, ppvScreenMatrix0);

    memset(self + 0x235a8, 0, 0x108);

    self[0x80a] = 0;
    self[0x809] = 0;
    self[0x808] = 0;

    ppvSysStopPartF = 1;
    ppvSysGoPartF = 0;
    ppvUserStopPartF = 0;
    ppvEmptyLoop = 0;

    if (Game.m_currentSceneId == 7) {
        pppCreateHeap(&m_pppEnvSt, 0x100000);
    } else {
        pppCreateHeap(&m_pppEnvSt, 0xC0000);
    }

    ppvEnv = &m_pppEnvSt;
    ppvHookFuncTbl = 0;

    PSMTXIdentity(ppvUnitMatrix);
    ppvZeroVector.z = kPartMngZero;
    ppvZeroVector.y = kPartMngZero;
    ppvZeroVector.x = kPartMngZero;

    ppvIsLoopCalc = 0;
    ppvIs2ndCalc = 0;

    PSMTXIdentity(ppvWorldMatrix);
    PSMTXIdentity(ppvWorldMatrix);
    PSMTXIdentity(ppvCameraMatrix);
    PSMTXCopy(ppvCameraMatrix, ppvCameraMatrix0);

    m_materialSet = 0;
    m_textureSet = 0;
    m_pppModelStArr = 0;
    m_pppShapeStArr = 0;

    {
        int* zero = reinterpret_cast<int*>(self);
        for (int i = 0; i < 0x80; i++) {
            zero[0x75 + i] = 0;
        }
    }
    {
        int* zero = reinterpret_cast<int*>(self);
        for (int i = 0; i < 0x80; i++) {
            zero[0xf6 + i] = 0;
        }
    }
    {
        int* zero = reinterpret_cast<int*>(self);
        for (int i = 0; i < 0x80; i++) {
            zero[0x177 + i] = 0;
        }
    }

    {
        unsigned char* mng = self;
        for (int i = 0; i < kPppMngCount / 6; i++) {
            for (int k = 0; k < 6; k++) {
                unsigned char* e = mng + (k * kPppMngStride);
                *reinterpret_cast<int*>(e + 0x2A18 + 0x14) = -0x1000;
                *reinterpret_cast<int*>(e + 0x2A18 + 0x12c) = -1;
                *reinterpret_cast<int*>(e + 0x2A18 + 0x11c) = -1;
                *reinterpret_cast<unsigned char*>(e + 0x2A18 + 0x120) = 0;
                *reinterpret_cast<unsigned char*>(e + 0x2A18 + 0x121) = 1;
                *reinterpret_cast<int*>(e + 0x2A18 + 0x124) = 0;
                *reinterpret_cast<unsigned char*>(e + 0x2A18 + 0x122) = 0;
                *reinterpret_cast<int*>(e + 0x2A18 + 0x128) = 0x1e;
            }
            mng += 6 * kPppMngStride;
        }
    }

    {
        unsigned char* walk = self;
        for (int k = 0; k < 4; k++) {
            int* e = reinterpret_cast<int*>(walk + 0x22e18);
            e[0x00 / 4] = 0;
            e[0x38 / 4] = 0;
            e[0x70 / 4] = 0;
            e[0xa8 / 4] = 0;
            e[0xe0 / 4] = 0;
            e[0x118 / 4] = 0;
            e[0x150 / 4] = 0;
            e[0x188 / 4] = 0;
            walk += 0x1c0;
        }
    }

    *reinterpret_cast<void**>(self + 0x1c8) = 0;
    *reinterpret_cast<int*>(self + 0x7f4) = 0;
    *reinterpret_cast<int*>(self + 0x7f8) = 0;
    *reinterpret_cast<int*>(self + 0x7fc) = 0;

    m_pppEnvSt.m_envParam = kPartMngZero;
    m_pppEnvSt.m_mngStCount = 0x10;
    m_pppEnvSt.m_isEditMode = 1;

    *reinterpret_cast<int*>(self + 0x80c) = 0;

    memset(self + 0x235a8, 0, 0x108);

    m_pppEnvSt.m_boxMinX = kPartMngEnvBoxMinX;
    m_pppEnvSt.m_boxMaxX = kPartMngEnvBoxMaxXz;
    m_pppEnvSt.m_boxMinY = kPartMngEnvBoxMinY;
    m_pppEnvSt.m_boxMaxY = kPartMngEnvBoxMaxY;
    m_pppEnvSt.m_boxMinZ = kPartMngEnvBoxMaxXz;
    m_pppEnvSt.m_boxMaxZ = kPartMngEnvBoxMaxZ;
}

/*
 * --INFO--
 * PAL Address: 0x8005ee7c
 * PAL Size: 640b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::Destroy()
{
    struct PartMngResRaw {
        unsigned char m_unk0[0x7e4];
        CMaterialSet* m_materialSet;
        CTextureSet* m_textureSet;
        pppModelSt* m_pppModelStArr;
        pppShapeSt* m_pppShapeStArr;
        unsigned char m_unk7f4[0x18];
        void* m_editorObj;
    };

    struct CRefRaw {
        void** m_vtable;
        int m_refCount;
    };

    struct PartMngModelStBlock {
        pppModelSt m_entries[0x100];
    };

    struct PartMngShapeStBlock {
        pppShapeSt m_entries[0x100];
    };

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    PartMngResRaw* res = reinterpret_cast<PartMngResRaw*>(self);

    for (int i = 0; i < 0x20; i++) {
        pppReleasePdt(i);
    }

    if (res->m_pppModelStArr != 0) {
        pppModelSt* modelArr = res->m_pppModelStArr;
        if (modelArr != 0) {
            for (unsigned int i = 0; i < 0x100; i++) {
                pppModelSt* model = &modelArr[i];
                if (model->m_isUsed != 0) {
                    if (--model->m_refCount <= 0) {
                        if (model->m_cacheId != -1) {
                            ppvAmemCacheSet.DestroyCache(model->m_cacheId);
                            *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(model) + 0x24) = 0;
                            *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(model) + 0x28) = 0;
                        }
                        model->Destroy();
                        model->m_refCount = 0;
                        model->m_isUsed = 0;
                    }
                }
            }
            delete reinterpret_cast<PartMngModelStBlock*>(modelArr);
        }
        res->m_pppModelStArr = 0;
    }

    if (res->m_pppShapeStArr != 0) {
        pppShapeSt* shapeArr = res->m_pppShapeStArr;
        if (shapeArr != 0) {
            for (unsigned int i = 0; i < 0x100; i++) {
                pppShapeSt* shape = &shapeArr[i];
                if (shape->m_inUse != 0) {
                    if (--shape->m_refCount <= 0) {
                        if (shape->m_animData != 0) {
                            delete reinterpret_cast<u8*>(shape->m_animData);
                            shape->m_animData = 0;
                        }
                        if (shape->m_displayListData != 0) {
                            delete reinterpret_cast<u8*>(shape->m_displayListData);
                            shape->m_displayListData = 0;
                        }
                        shape->m_refCount = 0;
                        shape->m_inUse = 0;
                    }
                }
            }
            delete reinterpret_cast<PartMngShapeStBlock*>(shapeArr);
        }
        res->m_pppShapeStArr = 0;
    }

    if (res->m_textureSet != 0) {
        CTextureSet* textureSet = res->m_textureSet;
        if (--reinterpret_cast<CRefRaw*>(textureSet)->m_refCount == 0) {
            delete textureSet;
        }
        res->m_textureSet = 0;
    }

    if (res->m_materialSet != 0) {
        CMaterialSet* materialSet = res->m_materialSet;
        if (--reinterpret_cast<CRefRaw*>(materialSet)->m_refCount == 0) {
            delete materialSet;
        }
        res->m_materialSet = 0;
    }

    if (res->m_editorObj != 0) {
        CCharaPcs::CHandle* handle =
            *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<unsigned char*>(res->m_editorObj) + 0xf8);
        if (handle != 0) {
            delete handle;
            *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(res->m_editorObj) + 0xf8) = 0;
        }
        if (res->m_editorObj != 0) {
            operator delete(res->m_editorObj);
            res->m_editorObj = 0;
        }
    }

    pppDestroyHeap(&m_pppEnvSt);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma optimization_level 2
void CPartMng::pppDumpMngSt()
{
    struct PppMngStDumpRaw {
        void* m_pppResSet;                 // 0x00
        unsigned char m_pad04[0x14 - 0x4];
        int m_baseTime;                    // 0x14
        unsigned char m_pad18[0x74 - 0x18];
        short m_kind;                      // 0x74
        short m_nodeIndex;                 // 0x76
        unsigned char m_pad78[0xF8 - 0x78];
        unsigned char m_prio;              // 0xF8
        unsigned char m_padF9[0xFA - 0xF9];
        unsigned short m_prioTime;         // 0xFA
        unsigned char m_padFC[0x12C - 0xFC];
        int m_heapGroupRef;                // 0x12C
    };

    unsigned long heapTotal;
    unsigned long heapUse;
    unsigned long heapFree;
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
        System.Printf(const_cast<char*>(sPartMngDumpSeparator));
    }

    unsigned char* base = self;
    PppMngStDumpRaw* mngBase = reinterpret_cast<PppMngStDumpRaw*>(reinterpret_cast<unsigned char*>(&PartMng) + 0x2A18);
    for (int i = 0; i < 0x180; i++) {
        PppMngStDumpRaw* mng = reinterpret_cast<PppMngStDumpRaw*>(base + 0x2A18);
        if (mng->m_baseTime != -0x1000 && static_cast<unsigned int>(System.m_execParam) >= 1U) {
            int kind = static_cast<int>(mng->m_kind);
            int heapGroup = static_cast<int>(reinterpret_cast<char*>(mng) - reinterpret_cast<char*>(mngBase)) / 0x158;
            int heapSize = ppvEnv->m_stagePtr->heapWalker(0, 0, static_cast<unsigned long>(heapGroup));

            System.Printf(
                const_cast<char*>(sPartMngDumpEntryFmt), mng->m_prioTime,
                mng->m_prio, heapSize, kind, static_cast<int>(mng->m_nodeIndex), heapGroup,
                m_pdtSlots[kind].m_name);
        }

        base += 0x158;
    }

    ppvEnv->m_stagePtr->heapInfo(heapTotal, heapUse, heapFree);

    if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
        System.Printf(
            const_cast<char*>(sPartMngHeapSummaryFmt),
            static_cast<int>(heapTotal >> 10), static_cast<int>(heapUse >> 10),
            static_cast<int>(heapFree >> 10));
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
        System.Printf(const_cast<char*>(sPartMngTripleNewline));
    }
}
#pragma optimization_level 4

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
 * PAL Address: 0x8005ea20
 * PAL Size: 732b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppReleasePdt(int pdtSlotIndex)
{
    struct PppMngStRaw {
        void* m_pppResSet;
        char m_unused[0x154];
    };

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    PppPdtSlot* pdtSlot = m_pdtSlots + pdtSlotIndex;
    _pppDataHead* pdt = pdtSlot->m_pppDataHead;

    if (pdt == 0) {
        return;
    }

    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x158);
    m_materialSet->ReleaseTag(m_textureSet, pdtSlotIndex, &ppvAmemCacheSet);
    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x13a);

    ppvEnv = reinterpret_cast<_pppEnvSt*>(pdtSlot->m_envFields);
    unsigned char* mngWalk = self;
    for (int i = 0; i < 0x180; i++) {
        PppMngStRaw* pppMngSt = reinterpret_cast<PppMngStRaw*>(mngWalk + 0x2A18);
        if (pppMngSt->m_pppResSet == pdtSlot) {
            _pppAllFreePObject(reinterpret_cast<_pppMngSt*>(pppMngSt));
        }
        mngWalk += 0x158;
    }

    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x149);

    pdt = pdtSlot->m_pppDataHead;
    if (pdt != 0) {
        for (int i = 0; i < pdt->m_modelCount; i++) {
            pppModelSt* model = reinterpret_cast<pppModelSt**>(pdt->m_modelNames)[i];
            if (--model->m_refCount <= 0) {
                if (model->m_cacheId != -1) {
                    ppvAmemCacheSet.DestroyCache(model->m_cacheId);
                    *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(model) + 0x24) = 0;
                    *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(model) + 0x28) = 0;
                }
                model->Destroy();
                model->m_refCount = 0;
                model->m_isUsed = 0;
            }
        }

        if (reinterpret_cast<pppModelSt**>(pdt->m_modelNames) != 0) {
            delete[] reinterpret_cast<pppModelSt**>(pdt->m_modelNames);
            pdt->m_modelNames = 0;
        }

        for (int i = 0; i < pdt->m_shapeCount; i++) {
            pppShapeSt* shape = reinterpret_cast<pppShapeSt**>(pdt->m_shapeNames)[i];
            if (--shape->m_refCount <= 0) {
                if (shape->m_animData != 0) {
                    delete reinterpret_cast<u8*>(shape->m_animData);
                    shape->m_animData = 0;
                }
                if (shape->m_displayListData != 0) {
                    delete reinterpret_cast<u8*>(shape->m_displayListData);
                    shape->m_displayListData = 0;
                }
                shape->m_refCount = 0;
                shape->m_inUse = 0;
            }
        }

        if (reinterpret_cast<pppShapeSt**>(pdt->m_shapeNames) != 0) {
            delete[] reinterpret_cast<pppShapeSt**>(pdt->m_shapeNames);
            pdt->m_shapeNames = 0;
        }

        int shapeGroupByteOffset = 0;
        for (int i = 0; i < pdt->m_shapeGroupCount; i++) {
            unsigned char* shapeGroup = reinterpret_cast<unsigned char*>(pdt->m_shapeGroups) + shapeGroupByteOffset;
            if (*reinterpret_cast<void**>(shapeGroup + 4) != 0) {
                operator delete(*reinterpret_cast<void**>(shapeGroup + 4));
                *reinterpret_cast<void**>(shapeGroup + 4) = 0;
            }
            shapeGroupByteOffset += 8;
        }

        if (reinterpret_cast<pppShapeGroupRaw*>(pdt->m_shapeGroups) != 0) {
            delete[] reinterpret_cast<pppShapeGroupRaw*>(pdt->m_shapeGroups);
            pdt->m_shapeGroups = 0;
        }

        for (int i = 0; i < pdt->m_cacheChunkCount; i++) {
            ppvAmemCacheSet.DestroyCache(reinterpret_cast<s16*>(pdt->m_cacheChunks)[i * 4]);
        }

        if (pdt->m_cacheChunks != 0) {
            operator delete(reinterpret_cast<void*>(pdt->m_cacheChunks));
            pdt->m_cacheChunks = 0;
        }

        if (pdtSlot->m_pppDataHead != 0) {
            operator delete(pdtSlot->m_pppDataHead);
            pdtSlot->m_pppDataHead = 0;
        }
    }

    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x182);
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
#pragma opt_propagation off
int CPartMng::pppGetNumFreePppMngSt()
{
    int freeCount = 0;
    int mngIndex = 0;

    int i = 0x30;
    do {
        if (m_pppMng[mngIndex + 0].m_baseTime == -0x1000) {
            freeCount++;
        }
        if (m_pppMng[mngIndex + 1].m_baseTime == -0x1000) {
            freeCount++;
        }
        if (m_pppMng[mngIndex + 2].m_baseTime == -0x1000) {
            freeCount++;
        }
        if (m_pppMng[mngIndex + 3].m_baseTime == -0x1000) {
            freeCount++;
        }
        if (m_pppMng[mngIndex + 4].m_baseTime == -0x1000) {
            freeCount++;
        }
        if (m_pppMng[mngIndex + 5].m_baseTime == -0x1000) {
            freeCount++;
        }
        if (m_pppMng[mngIndex + 6].m_baseTime == -0x1000) {
            freeCount++;
        }
        if (m_pppMng[mngIndex + 7].m_baseTime == -0x1000) {
            freeCount++;
        }
        mngIndex += 8;
        i--;
    } while (i != 0);

    return freeCount;
}
#pragma opt_propagation reset

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
    if (*reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x28) == 0x7fff) {
        return;
    }

    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)2);
    GXSetChanCtrl((GXChannelID)2, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)2);

    Mtx identity;
    Mtx44 orthoProjection;
    C_MTXOrtho(orthoProjection, kPartMngZero, kPartMngOrthoHeight, kPartMngZero, kPartMngOrthoWidth, kPartMngZero,
               kPartMngOrthoFar);
    GXSetProjection(orthoProjection, GX_ORTHOGRAPHIC);

    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetZCompLoc(0);
    GXSetCurrentMtx(0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetZMode(0, GX_ALWAYS, 0);
    _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    pppSetBlendMode(3);

    _GXColor color;
    color.r = 0xff;
    color.g = 0xff;
    color.b = 0xff;
    color.a = 0xff;
    int cursorX = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x28);
    int cursorY = *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x2c);
    float zero = kPartMngZero;

    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x140), (float)(cursorY + 0xd6), zero);
    GXPosition3f32((float)(cursorX + 0x140), (float)(cursorY + 0xea), zero);

    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x13f), (float)(cursorY + 0xd6), zero);
    GXPosition3f32((float)(cursorX + 0x13f), (float)(cursorY + 0xea), zero);

    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x12c), (float)(cursorY + 0xe0), zero);
    GXPosition3f32((float)(cursorX + 0x154), (float)(cursorY + 0xe0), zero);

    color.r = 0x00;
    color.g = 0x00;
    color.b = 0x00;
    color.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x141), (float)(cursorY + 0xd7), zero);
    GXPosition3f32((float)(cursorX + 0x141), (float)(cursorY + 0xeb), zero);

    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x142), (float)(cursorY + 0xd7), zero);
    GXPosition3f32((float)(cursorX + 0x142), (float)(cursorY + 0xeb), zero);

    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32((float)(cursorX + 0x12d), (float)(cursorY + 0xe1), zero);
    GXPosition3f32((float)(cursorX + 0x155), (float)(cursorY + 0xe1), zero);

    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * PAL Address: 0x8005e078
 * PAL Size: 784b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::render3Dcursor()
{
    GXSetNumChans(1);
    GXSetChanCtrl((GXChannelID)0, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)2);
    GXSetChanCtrl((GXChannelID)2, 0, (GXColorSrc)0, (GXColorSrc)0, 0, (GXDiffuseFn)2, (GXAttnFn)2);

    Mtx identity;
    Mtx44 orthoProjection;
    C_MTXOrtho(orthoProjection, kPartMngZero, kPartMngOrthoHeight, kPartMngZero, kPartMngOrthoWidth, kPartMngZero,
               kPartMngOrthoFar);
    GXSetProjection(orthoProjection, GX_ORTHOGRAPHIC);

    PSMTXIdentity(identity);
    GXLoadPosMtxImm(identity, 0);
    GXSetZCompLoc(0);
    GXSetCurrentMtx(0);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXSetZMode(0, GX_ALWAYS, 0);
    _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
    GXSetCullMode(GX_CULL_NONE);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    GXSetNumTexGens(0);
    GXSetNumTevStages(1);
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
    GXLoadPosMtxImm(ppvCameraMatrix, 0);
    pppSetBlendMode(3);

    float* cursorPos = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x18);
    float x = cursorPos[0];
    float y = cursorPos[1];
    float z = cursorPos[2];

    _GXColor color;
    color.r = 0xff;
    color.g = 0x80;
    color.b = 0x80;
    color.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x - kPartMngCullRadius, y, z);
    GXPosition3f32(x + kPartMngCullRadius, y, z);

    color.r = 0x80;
    color.g = 0xff;
    color.b = 0x80;
    color.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x, y - kPartMngCullRadius, z);
    GXPosition3f32(x, y + kPartMngCullRadius, z);

    color.r = 0xff;
    color.g = 0xff;
    color.b = 0x80;
    color.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x, y, z - kPartMngCullRadius);
    GXPosition3f32(x, y, z + kPartMngCullRadius);
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
    struct PartMngMouseRaw {
        unsigned char pad00[0x10];
        int requestFlag;
        unsigned char pad14[0x14];
        unsigned int cursorX;
        unsigned int cursorY;
    };

    int zAtPixel;
    Vec worldPos;
    Vec viewPos;
    Mtx invCamera;
    PartMngMouseRaw* raw = reinterpret_cast<PartMngMouseRaw*>(this);

    if (raw->requestFlag != 0) {
        int x = raw->cursorX + 0x140;
        int y = raw->cursorY + 0xE0;
        if ((x >= 0) && (x < 0x27E) && (y >= 0) && (y < 0x1BE)) {
            Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x2A2);
            GXPeekZ(static_cast<u16>(x & 0xFFFF), static_cast<u16>(y & 0xFFFF), reinterpret_cast<u32*>(&zAtPixel));

            float normY = -(float)(int)raw->cursorY / kPartMngScreenHalfHeight / ppvScreenMatrix0[1][1];
            float viewZ = ppvScreenMatrix0[2][3]
                          / ((float)(zAtPixel - 0xFFFFFF) / kPartMngDepthUnit + ppvScreenMatrix0[2][2]);
            float normX = (float)(int)raw->cursorX / kPartMngScreenHalfWidth / ppvScreenMatrix0[0][0];
            viewPos.x = viewZ * normX;
            viewPos.y = viewZ * normY;
            viewPos.z = -viewZ;

            PSMTXInverse(ppvCameraMatrix0, invCamera);
            PSMTXMultVec(invCamera, &viewPos, &worldPos);
            USBPcs.SendDataCode(0x60, &worldPos, 1, 0xC);
        }
        raw->requestFlag = 0;
    }
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
 * PAL Address: 0x8005DE70
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::drawEnd()
{
    gPppHeapUseRateWords[0] = pppHeapCheckLeak__FPQ27CMemory6CStage2(ppvEnv->m_stagePtr);
    int heapCheckCount = gPppHeapUseRateWords[2];
    gPppHeapUseRateWords[2] = heapCheckCount - 1;
    if ((heapCheckCount == 0) || (gPppHeapUseRateWords[0] > gPppHeapUseRateWords[1])) {
        gPppHeapUseRateWords[1] = gPppHeapUseRateWords[0];
        gPppHeapUseRateWords[2] = *(int*)((char*)this + 0x16C) << 1;
    }
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
 * PAL Address: 0x8005dbf8
 * PAL Size: 632b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::SetFp()
{
    struct PppMngSetFpRaw {
        void* m_pppResSet;                   // 0x00
        unsigned char m_pad04[0x08 - 0x04];
        Vec m_position;                      // 0x08
        int m_baseTime;                      // 0x14
        float m_rotationX;                   // 0x18
        float m_rotationZ;                   // 0x1C
        int m_rotationSpeed;                 // 0x20
        unsigned char m_pad24[0x28 - 0x24];
        Vec m_scale;                         // 0x28
        unsigned char m_pad34[0x38 - 0x34];
        float m_userFloat0;                  // 0x38
        float m_userFloat1;                  // 0x3C
        float m_scaleFactor;                 // 0x40
        float m_ownerScale;                  // 0x44
        unsigned char m_pad48[0x76 - 0x48];
        short m_nodeIndex;                   // 0x76
        unsigned char m_pad78[0xBC - 0x78];
        unsigned int m_objHitMask;           // 0xBC
        unsigned int m_cylinderAttribute;    // 0xC0
        unsigned char m_padC4[0xD8 - 0xC4];
        CGObject* m_owner;                   // 0xD8
        CGObject* m_lookTarget;              // 0xDC
        void* m_bindNode;                    // 0xE0
        unsigned char m_padE4[0xE7 - 0xE4];
        unsigned char m_matrixMode;          // 0xE7
        unsigned char m_fieldE8;             // 0xE8
        unsigned char m_ownerFlagsInitialized; // 0xE9
        unsigned char m_ownerFlagA;          // 0xEA
        unsigned char m_drawVariant;         // 0xEB
        unsigned char m_rotationOrder;       // 0xEC
        unsigned char m_drawPass;            // 0xED
        unsigned char m_drawSubType;         // 0xEE
        unsigned char m_useOwnerScaleSign;   // 0xEF
        unsigned char m_ownerFlagB;          // 0xF0
        unsigned char m_ownerFlagC;          // 0xF1
        unsigned char m_fieldF2;             // 0xF2
        unsigned char m_padF3[0xF7 - 0xF3];
        unsigned char m_fpBillboard;         // 0xF7
        unsigned char m_prio;                // 0xF8
        unsigned char m_padF9[0x100 - 0xF9];
        int m_paramA;                        // 0x100
        unsigned int m_paramB;               // 0x104
        float m_cullRadiusSq;                // 0x108
        float m_cullRadius;                  // 0x10C
        float m_cullYOffset;                 // 0x110
        unsigned char m_pad114[0x11A - 0x114];
        short m_mapObjIndex;                 // 0x11A
    };

    // Overlay view: pins the element fields at baked 0x2A18+field displacements
    // off a base register that starts at `this` and walks by sizeof(_pppMngSt).
    struct PppMngSetFpView {
        unsigned char m_head[0x2A18];
        PppMngSetFpRaw m_mng;                // 0x2A18
    };

    static const int kUsbEditOffset = 0x7F0;
    static const int kResSetOffset = 0x23518;
    static const int kRecvBuffOffset = 0x1C8;
    static const int kEditCountOffset = 0x4;
    static const int kPacketStride = 0x60;

    PppMngSetFpView* view = reinterpret_cast<PppMngSetFpView*>(this);
    int i;
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
#define mng (&view->m_mng)
    for (i = 0; i < *reinterpret_cast<int*>(self + kEditCountOffset); i++) {
        unsigned char* fpBytes = *reinterpret_cast<unsigned char**>(self + kRecvBuffOffset) + i * kPacketStride;
        float* recvBuff = reinterpret_cast<float*>(fpBytes);
        mng->m_pppResSet = self + kResSetOffset;

        if (mng->m_baseTime < 0) {
            mng->m_baseTime = reinterpret_cast<int*>(recvBuff)[0x0B];
        } else {
            mng->m_baseTime = reinterpret_cast<int*>(recvBuff)[0x0B] * 0x19 / 0x1E;
        }

        mng->m_cullRadiusSq = recvBuff[0x0D];
        if (mng->m_cullRadiusSq > 0.0) {
            mng->m_cullRadiusSq *= mng->m_cullRadiusSq;
        }
        mng->m_nodeIndex = static_cast<short>(i);
        mng->m_cullRadius = recvBuff[0x0E];
        mng->m_cullYOffset = recvBuff[0x0F];
        mng->m_position.x = recvBuff[0];
        mng->m_position.y = recvBuff[1];
        mng->m_position.z = recvBuff[2];
        *reinterpret_cast<int*>(&mng->m_rotationX) = reinterpret_cast<int*>(recvBuff)[4];
        *reinterpret_cast<int*>(&mng->m_rotationZ) = reinterpret_cast<int*>(recvBuff)[5];
        mng->m_rotationSpeed = reinterpret_cast<int*>(recvBuff)[6];
        mng->m_scale.x = recvBuff[8];
        mng->m_scale.y = recvBuff[9];
        mng->m_scale.z = recvBuff[0x0A];
        mng->m_ownerScale = kPartMngOne;
        mng->m_scaleFactor = kPartMngOne;
        mng->m_userFloat1 = kPartMngOne;
        mng->m_userFloat0 = kPartMngOne;
        mng->m_useOwnerScaleSign = 0;
        mng->m_matrixMode = *reinterpret_cast<unsigned char*>(fpBytes + 0x45);
        mng->m_drawVariant = *reinterpret_cast<unsigned char*>(fpBytes + 0x46);
        mng->m_rotationOrder = *reinterpret_cast<unsigned char*>(fpBytes + 0x47);
        mng->m_drawPass = *reinterpret_cast<unsigned char*>(fpBytes + 0x44);
        mng->m_drawSubType = *reinterpret_cast<unsigned char*>(fpBytes + 0x4C);
        mng->m_ownerFlagB = *reinterpret_cast<unsigned char*>(fpBytes + 0x4D);
        mng->m_ownerFlagC = *reinterpret_cast<unsigned char*>(fpBytes + 0x4E);
        mng->m_fieldF2 = 1;
        mng->m_fpBillboard = *reinterpret_cast<unsigned char*>(fpBytes + 0x4A);
        mng->m_prio = *reinterpret_cast<unsigned char*>(fpBytes + 0x4B);
        mng->m_mapObjIndex = *reinterpret_cast<short*>(fpBytes + 0x48);
        mng->m_bindNode = 0;
        mng->m_objHitMask = 0xFFFFFFFF;
        mng->m_cylinderAttribute = 0xFFFFFFFF;
        mng->m_paramA = 0;
        mng->m_fieldE8 = 0;
        mng->m_ownerFlagsInitialized = 1;
        mng->m_ownerFlagA = 1;
        mng->m_owner = 0;

        unsigned char mode = mng->m_matrixMode;
        switch (mode) {
        case 2:
        case 4:
            mng->m_mapObjIndex = static_cast<short>(MapMng.GetMapObjEffectIdx(*reinterpret_cast<short*>(fpBytes + 0x48)));
            break;
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
#define owner (*reinterpret_cast<CGObject**>(self + kUsbEditOffset + 0x1C))
            mng->m_ownerFlagA = 0;
            mng->m_owner = owner;
            mng->m_lookTarget = owner;
            if (owner != 0) {
                int node = owner->m_charaModelHandle->m_model->SearchNodeSk(reinterpret_cast<char*>(fpBytes + 0x50));
                if (node >= 0) {
                    mng->m_bindNode = reinterpret_cast<void*>(
                        *reinterpret_cast<int*>(
                            reinterpret_cast<unsigned char*>(owner->m_charaModelHandle->m_model) + 0xA8) +
                        node * 0xC0);
                }
            }
#undef owner
            break;
        }

        view = reinterpret_cast<PppMngSetFpView*>(reinterpret_cast<unsigned char*>(view) + sizeof(_pppMngSt));
    }
#undef mng
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
 * PAL Address: 0x8005dad0
 * PAL Size: 296b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CPartMng::pppReadRsd(CChunkFile& chunkFile, pppModelSt* modelSt)
{
    char* textureNames[0x101];
    CChunkFile::CChunk chunk;

    unsigned int meshSize = 0;

    while (chunkFile.GetNextChunk(chunk)) {
        chunkFile.PushChunk();
        switch (chunk.m_id) {
        case 'RSD ':
            while (chunkFile.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 'TXNM':
                    for (unsigned int i = 0; i < chunk.m_arg0; i++) {
                        textureNames[i] = chunkFile.GetString();
                    }
                    break;
                case 'MESH':
                    meshSize = modelSt->ReadOtmMesh(chunkFile, PartPcs.m_usbStreamState.m_stageLoad, 0, 0);
                    modelSt->SetDisplayListMaterial(m_materialSet, textureNames, &ppvAmemCacheSet);
                    break;
                }
            }
            break;
        }
        chunkFile.PopChunk();
    }

    return meshSize;
}

/*
 * --INFO--
 * PAL Address: 0x8005d950
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppReadShp(CChunkFile& chunkFile, pppShapeSt* shapeSt)
{
	char* textureNames[0x101];
	char** textureNameIt = textureNames;
	CChunkFile::CChunk chunk;

	while (chunkFile.GetNextChunk(chunk))
	{
		chunkFile.PushChunk();
		char** textureNameWrite = textureNameIt;
		switch (chunk.m_id)
		{
		case 0x46534850: // 'FSHP'
			while (chunkFile.GetNextChunk(chunk))
			{
				switch (chunk.m_id)
				{
				case 0x54584E4D: // 'TXNM'
					chunkFile.PushChunk();
					*textureNameWrite = chunkFile.GetString();
					chunkFile.PopChunk();
					textureNameIt++;
					textureNameWrite++;
					break;
				case 0x444C5354: // 'DLST'
					shapeSt->m_displayListData =
						operator new[](
						    chunk.m_size, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x4B3);
					chunkFile.Get(shapeSt->m_displayListData, chunk.m_size);
					DCFlushRange(shapeSt->m_displayListData, (chunk.m_size + 0x1F) & 0xFFFFFFE0);
					break;
				case 0x414E494D: // 'ANIM'
					shapeSt->m_animData =
						operator new[](
						    chunk.m_size, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x4B9);
					chunkFile.Get(shapeSt->m_animData, chunk.m_size);
					pppSetShapeMaterial(shapeSt, m_materialSet, textureNames);
					break;
				}
			}
			break;
		}
		chunkFile.PopChunk();
	}
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
#pragma opt_lifetimes off
#pragma opt_strength_reduction off
void CPartMng::pppEditAllReleaseResource()
{
    static const int kUsbMapMeshTableOffset = 0x7F4;
    static const int kUsbShapeSlotTableOffset = 0x7F8;
    static const int kRecvBuffOffset = 0x1C8;

#define self (reinterpret_cast<unsigned char*>(this))
    int iVar3;
    unsigned char* iter;

    if (m_materialSet != 0) {
        delete m_materialSet;
        m_materialSet = 0;
    }
    if (m_textureSet != 0) {
        delete m_textureSet;
        m_textureSet = 0;
    }

    iter = self;
    iVar3 = 0;
    do {
        if (*reinterpret_cast<void**>(iter + 0x1D4) != 0) {
            operator delete(*reinterpret_cast<void**>(iter + 0x1D4));
            *reinterpret_cast<void**>(iter + 0x1D4) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0x4;
    } while (iVar3 < 0x80);

    iter = self;
    iVar3 = 0;
    do {
        if (*reinterpret_cast<void**>(iter + 0x3D8) != 0) {
            operator delete(*reinterpret_cast<void**>(iter + 0x3D8));
            *reinterpret_cast<void**>(iter + 0x3D8) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0x4;
    } while (iVar3 < 0x80);

    iter = self;
    iVar3 = 0;
    do {
        if (*reinterpret_cast<long**>(iter + 0x5DC) != 0) {
            operator delete(*reinterpret_cast<long**>(iter + 0x5DC));
            *reinterpret_cast<long**>(iter + 0x5DC) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0x4;
    } while (iVar3 < 0x80);

    u8*& recvBuffer = *reinterpret_cast<u8**>(self + kRecvBuffOffset);
    if (recvBuffer != 0) {
        delete[] recvBuffer;
        recvBuffer = 0;
    }

    pppModelSt**& modelSlots = *reinterpret_cast<pppModelSt***>(self + kUsbMapMeshTableOffset);
    if (modelSlots != 0) {
        for (int i = 0; i < 0x88; i++) {
            pppModelSt* model = modelSlots[i];
            if (model != 0) {
                delete model;
                modelSlots[i] = 0;
            }
        }

        if (modelSlots != 0) {
            operator delete(modelSlots);
            modelSlots = 0;
        }
    }

    pppShapeSt**& shapeSlots = *reinterpret_cast<pppShapeSt***>(self + kUsbShapeSlotTableOffset);
    if (shapeSlots != 0) {
        for (int i = 0; i < 0x80; i++) {
            pppShapeSt* shape = shapeSlots[i];
            if (shape != 0) {
                delete shape;
                shapeSlots[i] = 0;
            }
        }

        if (shapeSlots != 0) {
            operator delete(shapeSlots);
            shapeSlots = 0;
        }
    }

    iVar3 = 0;
    iter = self;
    do {
        if (*reinterpret_cast<void**>(iter + 0x3D8) != 0) {
            operator delete(*reinterpret_cast<void**>(iter + 0x3D8));
            *reinterpret_cast<void**>(iter + 0x3D8) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0x4;
    } while (iVar3 < 0x80);

    if (*reinterpret_cast<void**>(self + 0x7FC) != 0) {
        operator delete(*reinterpret_cast<void**>(self + 0x7FC));
        *reinterpret_cast<int*>(self + 0x7FC) = 0;
    }
#undef self
}
#pragma opt_lifetimes reset
#pragma opt_strength_reduction reset

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
    int checkSum = 0x12345678;
    char* cursor = packet + 0x20;
    unsigned long remaining = packetSize - 0x20;

    while (remaining > 0) {
        checkSum += *cursor++;
        remaining--;
    }

    if (static_cast<unsigned int>(checkSum) != *reinterpret_cast<unsigned int*>(packet)) {
        Graphic.Printf(const_cast<char*>(sPartMngChecksumErrorFmt), code);
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
    struct PartMngResRaw {
        unsigned char m_unk0[0x7E4];
        CMaterialSet* m_materialSet;
        CTextureSet* m_textureSet;
    };

    static const int kUsbMapMeshTableOffset = 0x7F4;
    static const int kUsbShapeSlotTableOffset = 0x7F8;
    static const int kUsbTextTableOffset = 0x7FC;
    static const int kStreamTextRawOffset = 0x3D8;
    static const int kRecvWriteOffset = 0x1CC;
    static const int kRecvBuffOffset = 0x1C8;
    static const int kPdtCountOffset = 0x0;
    static const int kEditCountOffset = 0x4;
    static const int kPppDataHeadTableOffset = 0x5DC;
    static const int kLastEnvCmdOffset = 0x23560;
    static const int kEditFrameOffset = 0xC;
    static const int kEditDrawModeOffset = 0x23570;
    static const int kCursorRequestOffset = 0x10;
    static const int kCursorXOffset = 0x178;
    static const int kCursorYOffset = 0x17A;
    static const int kCursorPacketOffset = 0x17C;
    static const int kCursorPacket42Offset = 0x18;
    static const int kEditCameraMatrixOffset = 0x40;
    static const int kEditCameraExtraOffset = 0x70;
    static const int kCmd16PayloadOffset = 0x180;
    static const int kLoadMapArgsOffset = 0x188;
    static const int kLoadModelArgsOffset = 0x190;
    static const int kLoadAnimNameOffset = 0x19C;
    static const int kMapPcsFlagOffset = 0x1BC;
    static const int kCharaVisToggleOffset = 0x1C0;

    CheckSum(packet, code, packetSize);

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    PartMngResRaw* res = reinterpret_cast<PartMngResRaw*>(self);
    char* payload = packet + 0x20;
    float* payloadFloats = reinterpret_cast<float*>(payload);
    int* payloadWords = reinterpret_cast<int*>(payload);
    if (payload == 0) {
        return;
    }

    struct EditCameraMatrix {
        int m_words[12];
    };
    struct EditEnvBlock {
        int m_words[0x38];
    };

    switch (code) {
    case 4:
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x554);
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3A9);
        {
            for (int i = 0; i < *reinterpret_cast<int*>(self + kEditCountOffset); i++) {
                _pppMngSt* mng = reinterpret_cast<_pppMngSt*>(self + i * 0x158 + 0x2A18);
                if (mng->m_baseTime != -0x1000) {
                    _pppAllFreePObject(mng);
                }
            }
        }
        *reinterpret_cast<int*>(self + kEditCountOffset) = 0;
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3B3);
        pppEditAllReleaseResource();
        ppvSysStopPartF = 1;
        *reinterpret_cast<int*>(self + 0x800) = 0;
        *reinterpret_cast<int*>(self + 0x804) = -1;
        *reinterpret_cast<int*>(self + kEditCountOffset) = 0;
        *reinterpret_cast<int*>(self + kPdtCountOffset) = 0;
        m_pppEnvSt.m_isEditMode = 0;

        if (res->m_textureSet == 0) {
            res->m_textureSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x447) CTextureSet;
            CTextureSet* textureSet = res->m_textureSet;
            textureSet->m_textureArray.SetDefaultSize(0x180);
            textureSet->m_textureArray.SetGrow(0);
        }

        if (res->m_materialSet == 0) {
            res->m_materialSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x44B) CMaterialSet;
            CMaterialSet* materialSet = res->m_materialSet;
            materialSet->m_materials.SetDefaultSize(0x180);
            materialSet->m_materials.SetGrow(0);
            m_pppEnvSt.m_materialSetPtr = res->m_materialSet;

            CMaterial* defaultMaterial = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x44E) CMaterial;
            defaultMaterial->Create(0, static_cast<CMaterialMan::TEV_BIT>(0xFFF531F0));
            *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(defaultMaterial) + 0x24) |= 1;
            if (static_cast<unsigned int>(res->m_materialSet->m_materials.GetSize()) == 0U) {
                materialSet->m_materials.Add(defaultMaterial);
            } else {
                materialSet->m_materials.SetAt(0, defaultMaterial);
            }
        }
        return;
    case 0x14:
        ppvUserStopPartF = 0;
        return;
    case 0x15:
        ppvUserStopPartF = 1;
        return;
    case 0x16:
        memcpy(self + kCmd16PayloadOffset, payload, 8);
        return;
    case 0x18:
        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 0x18;
        memcpy(self + kLoadMapArgsOffset, payload, 8);
        return;
    case 0x19:
        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 0x19;
        memcpy(self + kLoadModelArgsOffset, payload, 0xC);
        return;
    case 0x1A:
        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 0x1A;
        memcpy(self + kLoadAnimNameOffset, payload, 0x20);
        return;
    case 3:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }

        m_pppMng[0].m_position.x = payloadFloats[0];
        m_pppMng[0].m_position.y = payloadFloats[1];
        m_pppMng[0].m_position.z = payloadFloats[2];
        *reinterpret_cast<int*>(&m_pppMng[0].m_rotation.x) = payloadWords[4];
        *reinterpret_cast<int*>(&m_pppMng[0].m_rotation.z) = payloadWords[5];
        m_pppMng[0].m_rotationSpeed = payloadWords[6];
        m_pppMng[0].m_scale.x = payloadFloats[8];
        m_pppMng[0].m_scale.y = payloadFloats[9];
        m_pppMng[0].m_scale.z = payloadFloats[0xA];
        {
            float* mngF = reinterpret_cast<float*>(m_pppMng);
            mngF[0x58 / 4] = payloadFloats[0x10];
            mngF[0x5C / 4] = payloadFloats[0x11];
            mngF[0x60 / 4] = payloadFloats[0x12];
            mngF[0x68 / 4] = payloadFloats[0x14];
            mngF[0x6C / 4] = payloadFloats[0x15];
            mngF[0x70 / 4] = payloadFloats[0x16];
            ppvChrScl[0] = payloadFloats[0xC];
            ppvChrScl[1] = payloadFloats[0xD];
            ppvChrScl[2] = payloadFloats[0xE];
            mngF[0x54 / 4] = payloadFloats[0x17];
            mngF[0x64 / 4] = payloadFloats[0x18];
        }
        m_pppMng[0].m_hitBgFlag = 0;
        return;
    case 0x1B:
        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 0x1B;
        memcpy(self + kMapPcsFlagOffset, payload, 4);
        return;
    case 0x1C:
        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 0x1C;
        memcpy(self + kCharaVisToggleOffset, payload, 4);
        return;
    case 1: {
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }

        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 1;
        m_pppEnvSt.m_mapMeshPtr = *reinterpret_cast<CMapMesh***>(self + kUsbMapMeshTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[0]) =
            *reinterpret_cast<unsigned int*>(self + kUsbShapeSlotTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[1]) =
            *reinterpret_cast<unsigned int*>(self + kUsbTextTableOffset);
        *reinterpret_cast<EditCameraMatrix*>(self + kEditCameraMatrixOffset) =
            *reinterpret_cast<EditCameraMatrix*>(payload);
        *reinterpret_cast<float*>(self + kEditCameraExtraOffset) = payloadFloats[0xC];
        *reinterpret_cast<float*>(self + kEditCameraExtraOffset + 4) = payloadFloats[0xD];
        *reinterpret_cast<EditEnvBlock*>(self + kEditCameraExtraOffset + 8) =
            *reinterpret_cast<EditEnvBlock*>(payload + 0x38);
        *reinterpret_cast<unsigned char*>(self + 0x158) = payload[0x118];
        *reinterpret_cast<unsigned char*>(self + 0x159) = payload[0x119];
        *reinterpret_cast<unsigned char*>(self + 0x15A) = payload[0x11A];
        *reinterpret_cast<unsigned char*>(self + 0x15B) = payload[0x11B];
        *reinterpret_cast<unsigned char*>(self + 0x15C) = payload[0x11C];
        *reinterpret_cast<unsigned char*>(self + 0x15D) = payload[0x11D];
        *reinterpret_cast<unsigned char*>(self + 0x15E) = payload[0x11E];
        *reinterpret_cast<unsigned char*>(self + 0x15F) = payload[0x11F];
        *reinterpret_cast<float*>(self + 0x160) = *reinterpret_cast<float*>(payload + 0x120);
        *reinterpret_cast<float*>(self + 0x164) = *reinterpret_cast<float*>(payload + 0x124);
        *reinterpret_cast<int*>(self + 0x168) = *reinterpret_cast<int*>(payload + 0x128);
        *reinterpret_cast<int*>(self + 0x16C) = *reinterpret_cast<int*>(payload + 0x12C);
        *reinterpret_cast<int*>(self + 0x170) = *reinterpret_cast<int*>(payload + 0x130);
        *reinterpret_cast<int*>(self + 0x174) = *reinterpret_cast<int*>(payload + 0x134);

        m_pppMng[0].m_ownerScale = kPartMngOne;
        m_pppMng[0].m_scaleFactor = kPartMngOne;
        m_pppMng[0].m_userFloat1 = kPartMngOne;
        m_pppMng[0].m_userFloat0 = kPartMngOne;
        m_pppMng[0].m_useOwnerScaleSign = 0;
        m_pppMng[0].m_matrixMode = 0;

        for (int i = 0; i < *reinterpret_cast<int*>(self + 0x4); i++) {
            *reinterpret_cast<unsigned int*>(self + i * 0x158 + 0x2ac0) =
                *reinterpret_cast<unsigned int*>(self + 0x168);
        }
        return;
    }
    case 2: {
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }

        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 2;
        m_pppEnvSt.m_mapMeshPtr = *reinterpret_cast<CMapMesh***>(self + kUsbMapMeshTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[0]) =
            *reinterpret_cast<unsigned int*>(self + kUsbShapeSlotTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[1]) =
            *reinterpret_cast<unsigned int*>(self + kUsbTextTableOffset);
        *reinterpret_cast<EditCameraMatrix*>(self + kEditCameraMatrixOffset) =
            *reinterpret_cast<EditCameraMatrix*>(payload);
        *reinterpret_cast<float*>(self + kEditCameraExtraOffset) = payloadFloats[0xC];
        *reinterpret_cast<float*>(self + kEditCameraExtraOffset + 4) = payloadFloats[0xD];
        *reinterpret_cast<EditEnvBlock*>(self + kEditCameraExtraOffset + 8) =
            *reinterpret_cast<EditEnvBlock*>(payload + 0x38);
        *reinterpret_cast<unsigned char*>(self + 0x158) = payload[0x118];
        *reinterpret_cast<unsigned char*>(self + 0x159) = payload[0x119];
        *reinterpret_cast<unsigned char*>(self + 0x15A) = payload[0x11A];
        *reinterpret_cast<unsigned char*>(self + 0x15B) = payload[0x11B];
        *reinterpret_cast<unsigned char*>(self + 0x15C) = payload[0x11C];
        *reinterpret_cast<unsigned char*>(self + 0x15D) = payload[0x11D];
        *reinterpret_cast<unsigned char*>(self + 0x15E) = payload[0x11E];
        *reinterpret_cast<unsigned char*>(self + 0x15F) = payload[0x11F];
        *reinterpret_cast<float*>(self + 0x160) = *reinterpret_cast<float*>(payload + 0x120);
        *reinterpret_cast<float*>(self + 0x164) = *reinterpret_cast<float*>(payload + 0x124);
        *reinterpret_cast<int*>(self + 0x168) = *reinterpret_cast<int*>(payload + 0x128);
        *reinterpret_cast<int*>(self + 0x16C) = *reinterpret_cast<int*>(payload + 0x12C);
        *reinterpret_cast<int*>(self + 0x170) = *reinterpret_cast<int*>(payload + 0x130);
        *reinterpret_cast<int*>(self + 0x174) = *reinterpret_cast<int*>(payload + 0x134);

        ppvChrScl[2] = kPartMngOne;
        ppvChrScl[1] = kPartMngOne;
        ppvChrScl[0] = kPartMngOne;

        for (int i = 0; i < *reinterpret_cast<int*>(self + 0x4); i++) {
            *reinterpret_cast<unsigned int*>(self + i * 0x158 + 0x2ac0) =
                *reinterpret_cast<unsigned int*>(self + 0x168);
        }
        return;
    }
    case 5:
    case 9:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        {
            CChunkFile chunkFile;
            chunkFile.SetBuf(payloadWords + 8);

            pppModelSt*** modelTablePtr = reinterpret_cast<pppModelSt***>(self + kUsbMapMeshTableOffset);
            if (*modelTablePtr == 0) {
                *modelTablePtr = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x5F8) pppModelSt*[0x88];
                for (int slot = 0; slot < 0x88; slot++) {
                    (*modelTablePtr)[slot] = 0;
                }
            }

#define slotIndex (static_cast<int>(*reinterpret_cast<short*>(payload)))
            pppModelSt* modelSlot = (*modelTablePtr)[slotIndex];
            if (modelSlot != 0) {
                if (--modelSlot->m_refCount <= 0) {
                    if (modelSlot->m_cacheId != -1) {
                        ppvAmemCacheSet.DestroyCache(modelSlot->m_cacheId);
                        modelSlot->m_meshData = 0;
                        modelSlot->m_displayListData = 0;
                    }
                    modelSlot->Destroy();
                    modelSlot->m_refCount = 0;
                    modelSlot->m_isUsed = 0;
                }
                (*modelTablePtr)[slotIndex] = 0;
            }

            modelSlot = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x5FC) pppModelSt;
            (*modelTablePtr)[slotIndex] = modelSlot;
            pppReadRsd(chunkFile, (*modelTablePtr)[slotIndex]);
#undef slotIndex
            *reinterpret_cast<int*>(self + 0x804) = -1;
        }
        return;
    case 6:
    case 10:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        {
            pppShapeSt*** shapeSlotTablePtr = reinterpret_cast<pppShapeSt***>(self + kUsbShapeSlotTableOffset);
            if (*shapeSlotTablePtr == 0) {
                *shapeSlotTablePtr = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x60A) pppShapeSt*[0x80];
                for (int slot = 0; slot < 0x80; slot++) {
                    (*shapeSlotTablePtr)[slot] = 0;
                }
            }

            int slotIndex = payloadWords[0];
            pppShapeSt* shapeSlot = (*shapeSlotTablePtr)[slotIndex];
            if (shapeSlot != 0) {
                if (--shapeSlot->m_refCount <= 0) {
                    if (shapeSlot->m_animData != 0) {
                        delete reinterpret_cast<u8*>(shapeSlot->m_animData);
                        shapeSlot->m_animData = 0;
                    }
                    if (shapeSlot->m_displayListData != 0) {
                        delete reinterpret_cast<u8*>(shapeSlot->m_displayListData);
                        shapeSlot->m_displayListData = 0;
                    }
                    shapeSlot->m_refCount = 0;
                    shapeSlot->m_inUse = 0;
                }
                (*shapeSlotTablePtr)[slotIndex] = 0;
            }

            shapeSlot = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x610) pppShapeSt;
            (*shapeSlotTablePtr)[slotIndex] = shapeSlot;
            CChunkFile chunkFile;
            chunkFile.SetBuf(payloadWords + 4);
            pppReadShp(chunkFile, (*shapeSlotTablePtr)[slotIndex]);
        }
        return;
    case 8:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        {
            void**& textTable = *reinterpret_cast<void***>(self + kUsbTextTableOffset);
            if (textTable == 0) {
                textTable = reinterpret_cast<void**>(
                    operator new[](0x400, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x61F));
            }

            int slotIndex = payloadWords[0];
            unsigned char* slotBase = self + slotIndex * 4;
#define textRaw (*reinterpret_cast<void**>(slotBase + kStreamTextRawOffset))
            if (textRaw == 0) {
                textRaw = operator new[](packetSize - 0x20, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x625);
            }

            memcpy(textRaw, payload, packetSize - 0x20);

            unsigned short* textEntry = reinterpret_cast<unsigned short*>(
                reinterpret_cast<unsigned char*>(textTable) + slotIndex * 8);
            textEntry[0] = static_cast<unsigned short>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(textRaw) + 4));
            textEntry[1] = static_cast<unsigned short>(*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(textRaw) + 8));
            *reinterpret_cast<void**>(textEntry + 2) = reinterpret_cast<unsigned char*>(textRaw) + 0xC;
#undef textRaw
        }
        return;
    case 0x0B:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        {
            CChunkFile chunkFile;
            chunkFile.SetBuf(payload);

            CChunkFile::CChunk chunk;
            while (chunkFile.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 'DIXT': {

                if (res->m_textureSet == 0) {
                    res->m_textureSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x447) CTextureSet;
                    CTextureSet* textureSet = res->m_textureSet;
                    textureSet->m_textureArray.SetDefaultSize(0x180);
                    textureSet->m_textureArray.SetGrow(0);
                }

                if (res->m_materialSet == 0) {
                    res->m_materialSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x44B) CMaterialSet;
                    CMaterialSet* materialSet = res->m_materialSet;
                    materialSet->m_materials.SetDefaultSize(0x180);
                    materialSet->m_materials.SetGrow(0);
                    m_pppEnvSt.m_materialSetPtr = res->m_materialSet;

                    CMaterial* defaultMaterial = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x44E) CMaterial;
                    defaultMaterial->Create(0, static_cast<CMaterialMan::TEV_BIT>(0xFFF531F0));
                    *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(defaultMaterial) + 0x24) |= 1;
                    if (static_cast<unsigned int>(res->m_materialSet->m_materials.GetSize()) == 0U) {
                        materialSet->m_materials.Add(defaultMaterial);
                    } else {
                        materialSet->m_materials.SetAt(0, defaultMaterial);
                    }
                }

                res->m_textureSet->Create(chunkFile, PartPcs.m_usbStreamState.m_stageLoad, 1, 0, 0, 0);
                res->m_materialSet->SetPartFromTextureSet(res->m_textureSet, 0);
                res->m_materialSet->SetTextureSet(res->m_textureSet);
                } break;
                }
            }
        }
        return;
    case 0x0C:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x646);
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3A9);
        {
            for (int i = 0; i < *reinterpret_cast<int*>(self + kEditCountOffset); i++) {
                _pppMngSt* mng = reinterpret_cast<_pppMngSt*>(self + i * 0x158 + 0x2A18);
                if (mng->m_baseTime != -0x1000) {
                    _pppAllFreePObject(mng);
                }
            }
        }
        *reinterpret_cast<int*>(self + kEditCountOffset) = 0;
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3B3);
        {
            void*& pppDataHead0 = *reinterpret_cast<void**>(self + kPppDataHeadTableOffset);
            if (pppDataHead0 != 0) {
                delete reinterpret_cast<u8*>(pppDataHead0);
                pppDataHead0 = 0;
            }
            if (*reinterpret_cast<void**>(self + kRecvBuffOffset) != 0) {
                delete *reinterpret_cast<u8**>(self + kRecvBuffOffset);
                *reinterpret_cast<void**>(self + kRecvBuffOffset) = 0;
            }
            pppDataHead0 = operator new[](
                packetSize - 0x20, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x64D);
            *reinterpret_cast<u8**>(self + kRecvBuffOffset) =
                new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x64E) u8[0x3000];
            memcpy(pppDataHead0, payload, packetSize - 0x20);
            pppInitPdt(reinterpret_cast<long*>(pppDataHead0), pppGetSysProgTable());
        }

        *reinterpret_cast<int*>(*reinterpret_cast<unsigned char**>(self + kRecvBuffOffset) + 0x2C) = 0;
        m_pppMng[0].m_baseTime = 0;
        *reinterpret_cast<float*>(*reinterpret_cast<unsigned char**>(self + kRecvBuffOffset) + 0x34) = kPartMngCullRadiusSqMax;
        m_pppMng[0].m_cullRadiusSq = kPartMngCullRadiusSqMax;
        *reinterpret_cast<float*>(*reinterpret_cast<unsigned char**>(self + kRecvBuffOffset) + 0x3C) = kPartMngCullRadius;
        *reinterpret_cast<float*>(*reinterpret_cast<unsigned char**>(self + kRecvBuffOffset) + 0x38) = kPartMngCullRadius;
        m_pppMng[0].m_cullYOffset = kPartMngCullRadius;
        m_pppMng[0].m_cullRadius = kPartMngCullRadius;
        *reinterpret_cast<int*>(*reinterpret_cast<unsigned char**>(self + kRecvBuffOffset) + 0x30) = 0;
        *reinterpret_cast<int*>(self + kEditCountOffset) = 1;
        *reinterpret_cast<int*>(self + kPdtCountOffset) = 1;
        m_pppMng[0].m_objHitMask = 0xFFFFFFFF;
        m_pppMng[0].m_cylinderAttribute = 0xFFFFFFFF;
        m_pppMng[0].m_paramA = 0;
        m_pppMng[0].m_slotVisible = 1;
        m_pppMng[0].m_ownerFacing = 1;
        m_pppMng[0].m_pppResSet = self + 0x23518;
        m_pppMng[0].m_nodeIndex = 0;
        m_pppMng[0].m_fieldF2 = 1;
        m_pppEnvSt.m_mapMeshPtr = *reinterpret_cast<CMapMesh***>(self + kUsbMapMeshTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[0]) =
            *reinterpret_cast<unsigned int*>(self + kUsbShapeSlotTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[1]) =
            *reinterpret_cast<unsigned int*>(self + kUsbTextTableOffset);
        return;
    case 0x0D: {
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x673);
#define pppDataHead (*reinterpret_cast<void**>(self + kPppDataHeadTableOffset + (*reinterpret_cast<int*>(self + kPdtCountOffset)) * 4))
        if (pppDataHead != 0) {
            delete reinterpret_cast<u8*>(pppDataHead);
            pppDataHead = 0;
        }
        if (*reinterpret_cast<void**>(self + kRecvBuffOffset) != 0) {
            delete *reinterpret_cast<u8**>(self + kRecvBuffOffset);
            *reinterpret_cast<void**>(self + kRecvBuffOffset) = 0;
        }

        pppDataHead = operator new[](
            packetSize - 0x20, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x678);
        *reinterpret_cast<u8**>(self + kRecvBuffOffset) =
            new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x679) u8[0x3000];
        memcpy(pppDataHead, payload, packetSize - 0x20);
        pppInitPdt(reinterpret_cast<long*>(pppDataHead), pppGetSysProgTable());
        *reinterpret_cast<int*>(self + kPdtCountOffset) = *reinterpret_cast<int*>(self + kPdtCountOffset) + 1;
#undef pppDataHead
        return;
    }
    case 0x0F:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3A9);
        {
            for (int i = 0; i < *reinterpret_cast<int*>(self + kEditCountOffset); i++) {
                _pppMngSt* mng = reinterpret_cast<_pppMngSt*>(self + i * 0x158 + 0x2A18);
                if (mng->m_baseTime != -0x1000) {
                    _pppAllFreePObject(mng);
                }
            }
        }
        *reinterpret_cast<int*>(self + kEditCountOffset) = 0;
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3B3);
        ppvSysStopPartF = 1;
        return;
    case 0x0E:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        if (*reinterpret_cast<int*>(self + kEditCountOffset) == 0) {
            *reinterpret_cast<void**>(self + kRecvWriteOffset) = *reinterpret_cast<void**>(self + kRecvBuffOffset);
        }
        memcpy(*reinterpret_cast<void**>(self + kRecvWriteOffset), payload, packetSize - 0x20);
        *reinterpret_cast<unsigned char**>(self + kRecvWriteOffset) += 0x60;
        *reinterpret_cast<int*>(self + kEditCountOffset) += 1;
        return;
    case 0x10:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        m_pppEnvSt.m_envParam = kPartMngZero;
        m_pppEnvSt.m_mapMeshPtr = *reinterpret_cast<CMapMesh***>(self + kUsbMapMeshTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[0]) =
            *reinterpret_cast<unsigned int*>(self + kUsbShapeSlotTableOffset);
        *reinterpret_cast<unsigned int*>(&m_pppEnvSt.m_particleColors[1]) =
            *reinterpret_cast<unsigned int*>(self + kUsbTextTableOffset);
        SetFp();
        return;
    case 0x11:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        m_pppMng[0].m_particleEnded = 1;
        return;
    case 0x12: {
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        unsigned int selectedId = *reinterpret_cast<unsigned int*>(self + 0x1C4) & 0xFFFF;
        _pppMngSt* mng = m_pppMng;
        unsigned char* recvBytes = *reinterpret_cast<unsigned char**>(self + 0x1C8);
        for (int i = *reinterpret_cast<int*>(self + 0x4); i != 0; i--) {
            if (static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(recvBytes + 0x40)) == selectedId) {
                mng->m_baseTime = 0;
            }
            recvBytes += 0x60;
            mng++;
        }
        return;
    }
    case 0x13: {
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        unsigned int selectedId = *reinterpret_cast<unsigned int*>(self + 0x1C4) & 0xFFFF;
        _pppMngSt* mng = m_pppMng;
        unsigned char* recvBytes = *reinterpret_cast<unsigned char**>(self + 0x1C8);
        for (int i = *reinterpret_cast<int*>(self + 0x4); i != 0; i--) {
            if (static_cast<unsigned int>(*reinterpret_cast<unsigned short*>(recvBytes + 0x40)) == selectedId) {
                mng->m_particleEnded = 1;
            }
            recvBytes += 0x60;
            mng++;
        }
        return;
    }
    case 0x17:
        if (m_pppEnvSt.m_isEditMode != 0) {
            return;
        }
        *reinterpret_cast<short*>(self + kCursorPacketOffset) = *reinterpret_cast<short*>(self + kCursorXOffset);
        *reinterpret_cast<short*>(self + kCursorPacketOffset + 2) = *reinterpret_cast<short*>(self + kCursorYOffset);
        self[0x808] = 1;
        return;
    case 0x1E:
        *reinterpret_cast<int*>(self + kCursorRequestOffset) = 1;
        return;
    case 0x41:
        *reinterpret_cast<int*>(self + kEditFrameOffset) = 0;
        return;
    case 0x40:
        *reinterpret_cast<int*>(self + kEditFrameOffset) = 1;
        return;
    case 0x42:
        memcpy(self + kCursorPacket42Offset, payload, 0x28);
        *reinterpret_cast<int*>(self + kEditFrameOffset) = 1;
        return;
    case 0x20:
        MapMng.ShowMapObjID(payloadWords[1], payloadWords[0]);
        return;
    case 0x21:
        MapMng.ShowMapMeshID(payloadWords[1], payloadWords[0]);
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
    CGObject** editorObj = reinterpret_cast<CGObject**>(self + 0x80c);

    switch (*reinterpret_cast<int*>(self + 0x23560)) {
    case 1: {
        // Camera matrix handed over from editor uses opposite handedness on these axes.
        *reinterpret_cast<float*>(self + 0x60) = -*reinterpret_cast<float*>(self + 0x60);
        *reinterpret_cast<float*>(self + 0x68) = -*reinterpret_cast<float*>(self + 0x68);
        *reinterpret_cast<float*>(self + 0x44) = -*reinterpret_cast<float*>(self + 0x44);
        *reinterpret_cast<float*>(self + 0x54) = -*reinterpret_cast<float*>(self + 0x54);
        *reinterpret_cast<float*>(self + 0x6c) = -*reinterpret_cast<float*>(self + 0x6c);
        *reinterpret_cast<float*>(self + 0x6c) *= *reinterpret_cast<float*>(self + 0x70);

        PSMTXCopy(reinterpret_cast<float(*)[4]>(self + 0x40), ppvCameraMatrix);
        C_MTXPerspective(ppvScreenMatrix, kPartMngPppFovY, kPartMngPppAspect, kPartMngPppNear, kPartMngPppFar);
        ppvScreenMatrixXbuff = ppvScreenMatrix[2][0];
        ppvScreenMatrixYbuff = ppvScreenMatrix[2][1];
        ppvScreenMatrixZbuff = ppvScreenMatrix[2][3];
        PSMTXCopy(ppvCameraMatrix, ppvCameraMatrix0);
        PSMTX44Copy(ppvScreenMatrix, ppvScreenMatrix0);

        _GXColor clearColor;
        clearColor.r = *reinterpret_cast<unsigned char*>(self + 0x158);
        clearColor.g = *reinterpret_cast<unsigned char*>(self + 0x159);
        clearColor.b = *reinterpret_cast<unsigned char*>(self + 0x15a);
        clearColor.a = 0xFF;
        GXSetCopyClear(clearColor, 0x00FFFFFF);

        float fogNear = *reinterpret_cast<float*>(self + 0x160);
        float fogFar = *reinterpret_cast<float*>(self + 0x164);
        _GXColor fogColor;
        if (*reinterpret_cast<unsigned char*>(self + 0x15c) != 0) {
            fogColor.b = *reinterpret_cast<unsigned char*>(self + 0x15f);
            fogColor.g = *reinterpret_cast<unsigned char*>(self + 0x15e);
            fogColor.r = *reinterpret_cast<unsigned char*>(self + 0x15d);
            fogColor.a = 0;
            Graphic.SetFogColor(fogColor);
            Graphic.SetFogParam(fogNear, fogFar);
        } else {
            fogColor.r = 0;
            fogColor.g = 0;
            fogColor.b = 0;
            fogColor.a = 0;
            Graphic.SetFogColor(fogColor);
            Graphic.SetFogParam(kPartMngZero, kPartMngZero);
        }

        ppvSysGoPartF = 1;
        break;
    }
    case 2: {
        *reinterpret_cast<float*>(self + 0x60) = -*reinterpret_cast<float*>(self + 0x60);
        *reinterpret_cast<float*>(self + 0x68) = -*reinterpret_cast<float*>(self + 0x68);
        *reinterpret_cast<float*>(self + 0x44) = -*reinterpret_cast<float*>(self + 0x44);
        *reinterpret_cast<float*>(self + 0x54) = -*reinterpret_cast<float*>(self + 0x54);
        *reinterpret_cast<float*>(self + 0x6c) = -*reinterpret_cast<float*>(self + 0x6c);
        *reinterpret_cast<float*>(self + 0x6c) *= *reinterpret_cast<float*>(self + 0x70);

        PSMTXCopy(reinterpret_cast<float(*)[4]>(self + 0x40), ppvCameraMatrix);
        C_MTXPerspective(ppvScreenMatrix, kPartMngPppFovY, kPartMngPppAspect, kPartMngPppNear, kPartMngPppFar);
        ppvScreenMatrixXbuff = ppvScreenMatrix[2][0];
        ppvScreenMatrixYbuff = ppvScreenMatrix[2][1];
        ppvScreenMatrixZbuff = ppvScreenMatrix[2][3];
        PSMTXCopy(ppvCameraMatrix, ppvCameraMatrix0);
        PSMTX44Copy(ppvScreenMatrix, ppvScreenMatrix0);

        _GXColor clearColor;
        clearColor.r = *reinterpret_cast<unsigned char*>(self + 0x158);
        clearColor.g = *reinterpret_cast<unsigned char*>(self + 0x159);
        clearColor.b = *reinterpret_cast<unsigned char*>(self + 0x15a);
        clearColor.a = 0xFF;
        GXSetCopyClear(clearColor, 0x00FFFFFF);

        float fogNear = *reinterpret_cast<float*>(self + 0x160);
        float fogFar = *reinterpret_cast<float*>(self + 0x164);
        _GXColor fogColor;
        if (*reinterpret_cast<unsigned char*>(self + 0x15c) != 0) {
            fogColor.b = *reinterpret_cast<unsigned char*>(self + 0x15f);
            fogColor.g = *reinterpret_cast<unsigned char*>(self + 0x15e);
            fogColor.r = *reinterpret_cast<unsigned char*>(self + 0x15d);
            fogColor.a = 0;
            Graphic.SetFogColor(fogColor);
            Graphic.SetFogParam(fogNear, fogFar);
        } else {
            fogColor.r = 0;
            fogColor.g = 0;
            fogColor.b = 0;
            fogColor.a = 0;
            Graphic.SetFogColor(fogColor);
            Graphic.SetFogParam(kPartMngZero, kPartMngZero);
        }

        ppvSysGoPartF = 1;
        break;
    }
    case 0x18:
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x7a4);
        MapPcs.LoadMap(*reinterpret_cast<int*>(self + 0x188), *reinterpret_cast<int*>(self + 0x18c), 0, 0, 0);
        *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MapPcs) + 0x180) = 1;
        break;
    case 0x19: {
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x7ad);

        if (*editorObj != 0) {
            if ((*editorObj)->m_charaModelHandle != 0) {
                delete (*editorObj)->m_charaModelHandle;
                (*editorObj)->m_charaModelHandle = 0;
            }
            operator delete(*editorObj);
            *editorObj = 0;
        }

        *editorObj =
            new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x7b5) CGObject;
        (*editorObj)->Create();

        (*editorObj)->m_charaModelHandle =
            new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x7b7) CCharaPcs::CHandle;
        (*editorObj)->m_charaModelHandle->Add();
        (*editorObj)->m_charaModelHandle->m_charaNo = 3;
        if (pppLoadModelRet(
                (*editorObj)->m_charaModelHandle,
                *reinterpret_cast<int*>(self + 0x190),
                *reinterpret_cast<unsigned long*>(self + 0x194),
                *reinterpret_cast<unsigned long*>(self + 0x198),
                0,
                -1,
                0,
                0
            ) == 0 &&
            (*editorObj)->m_charaModelHandle != 0) {
            delete (*editorObj)->m_charaModelHandle;
            (*editorObj)->m_charaModelHandle = 0;
        }
        break;
    }
    case 0x1a:
        if (*editorObj != 0) {
            Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x7ce);
            if (gPppInSubFrameCalc == 0) {
                gPppInConstructor = 0;
                gPppInSubFrameCalc = 1;
            }

#define handle ((*editorObj)->m_charaModelHandle)
            if (handle != 0) {
                handle->LoadAnim(reinterpret_cast<char*>(self + 0x19c), gPppInConstructor, 0, -1, -1, -1, 0);
                handle->SetAnim(gPppInConstructor, -1, -1, -1, 0);
                gPppInConstructor++;
            }
#undef handle
        }
        break;
    case 0x1b:
        *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MapPcs) + 0x180) =
            *reinterpret_cast<unsigned int*>(self + 0x1bc);
        break;
    case 0x1c:
        if (*editorObj != 0 && (*editorObj)->m_charaModelHandle != 0) {
            if (*reinterpret_cast<unsigned int*>(self + 0x1c0) != 0) {
                (*editorObj)->m_charaModelHandle->m_flags |= 1;
            } else {
                (*editorObj)->m_charaModelHandle->m_flags &= ~1;
            }
        }
        break;
    default:
        break;
    }

    *reinterpret_cast<int*>(self + 0x23560) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005b79c
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditPartCalc()
{
    static const int kUsbEditOffset = 0x7F0;
    static const int kPppMngCount = 0x180;

    char* self = reinterpret_cast<char*>(this);
    char* usbEdit = reinterpret_cast<char*>(self + kUsbEditOffset);
    PppPdtSlot* pdtSlots = m_pdtSlots;

    if (ppvSysGoPartF != 0) {
        ppvSysGoPartF = 0;
        ppvSysStopPartF = 0;
    }

    reinterpret_cast<CStopWatch&>(g_par_calc_prof).Stop();
    if (*reinterpret_cast<CGObject**>(self + 0x80c) != 0) {
        (*reinterpret_cast<CGObject**>(self + 0x80c))->m_charaModelHandle->m_model->CalcMatrix();
        (*reinterpret_cast<CGObject**>(self + 0x80c))->m_charaModelHandle->m_model->CalcSkin();
        (*reinterpret_cast<CGObject**>(self + 0x80c))->m_charaModelHandle->m_model->SetFrame(
            *reinterpret_cast<float*>(self + 0x23564));
        if (ppvUserStopPartF == 0) {
            *reinterpret_cast<float*>(self + 0x23564) += kPartMngOne;
        }
    }
    reinterpret_cast<CStopWatch&>(g_par_calc_prof).Start();

    if (usbEdit[0x18] != 0) {
        usbEdit[0x18] = 0;
        usbEdit[0x19] = 1;
        usbEdit[0x1A] = 0;

        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3a9);
        for (int i = 0; i < *reinterpret_cast<int*>(self + 0x4); i++) {
            if (m_pppMng[i].m_baseTime != -0x1000) {
                _pppAllFreePObject(&m_pppMng[i]);
            }
        }

        *reinterpret_cast<int*>(self + 0x4) = 0;

        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3b3);
        _pppMngSt* firstMng = m_pppMng;
        firstMng->m_particleEnded = 0;
        *reinterpret_cast<int*>(&firstMng->m_envColorR) = *reinterpret_cast<int*>(self + 0x168);
        _pppStartPart(firstMng, *reinterpret_cast<long**>(self + 0x5dc), 1);
    }

    if (ppvSysStopPartF != 0) {
        return;
    }
    if (*reinterpret_cast<long**>(self + 0x5dc) == 0) {
        return;
    }

    if (*reinterpret_cast<int*>(self + 0x174) <= 3) {
        for (int i = 0; i < *reinterpret_cast<int*>(self + 0x4); i++) {
            _pppMngSt* mng = &m_pppMng[i];
            ppvMng = mng;
            int baseTime = mng->m_baseTime;
            if (baseTime == -0x1000) {
                continue;
            }
            if (baseTime >= 0) {
                goto decrementTimerA;
            }

        runFrameA:
            pppSetMatrix(mng);
            pppSetFpMatrix(mng);
            _pppCalcPart(mng);
            _pppDeadPart(mng);

            if (mng->m_isFinished != 0 || mng->m_hitBgFlag != 0) {
                Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x827);
                _pppAllFreePObject(mng);
                Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x82b);
                if (*reinterpret_cast<int*>(self + 0x174) > 3) {
                    pppHeapCheckLeak(ppvEnv->m_stagePtr);
                }
                if (i == 0) {
                    usbEdit[0x1A] = 1;
                }
                gPppHeapUseRateWords[1] = 0;
            }
            continue;

        decrementTimerA:
            {
                int newBaseTime = baseTime - 1;
                mng->m_baseTime = newBaseTime;
                if (newBaseTime >= 0) {
                    continue;
                }
            }
            mng->m_particleEnded = 0;
            *reinterpret_cast<int*>(&mng->m_envColorR) = *reinterpret_cast<int*>(self + 0x168);
            _pppStartPart(mng, reinterpret_cast<long*>(*reinterpret_cast<long*>(self + 0x5dc +
                                   (*reinterpret_cast<int**>(self + 0x1C8))[i * 0x18 + 0xC] * 4)), 1);
            goto runFrameA;
        }
    } else {
        for (int i = 0; i < *reinterpret_cast<int*>(self + 0x4); i++) {
            _pppMngSt* mng = &m_pppMng[i];
            ppvMng = mng;
            if (mng->m_baseTime == -0x1000) {
                mng->m_baseTime = 0;
            }
            if (mng->m_baseTime >= 0) {
                goto decrementTimerB;
            }

        runFrameB:
            pppSetMatrix(mng);
            pppSetFpMatrix(mng);
            _pppCalcPart(mng);
            if (mng->m_mode != 0 && mng->m_currentFrame == mng->m_lifeEnd) {
                gPppHeapUseRateWords[1] = 0;
            }
            _pppDeadPart(mng);
            if (mng->m_isFinished != 0 || mng->m_hitBgFlag != 0) {
                Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x861);
                _pppAllFreePObject(mng);
                Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x865);
                if (*reinterpret_cast<int*>(self + 0x174) > 3) {
                    pppHeapCheckLeak(ppvEnv->m_stagePtr);
                }
                if (i == 0) {
                    usbEdit[0x1A] = 1;
                }
                gPppHeapUseRateWords[1] = 0;
            }
            continue;

        decrementTimerB:
            {
                int newBaseTime = mng->m_baseTime - 1;
                mng->m_baseTime = newBaseTime;
                if (newBaseTime >= 0) {
                    continue;
                }
            }
            mng->m_particleEnded = 0;
            *reinterpret_cast<int*>(&mng->m_envColorR) = *reinterpret_cast<int*>(self + 0x168);
            _pppStartPart(mng, reinterpret_cast<long*>(*reinterpret_cast<long*>(self + 0x5dc +
                                   (*reinterpret_cast<int**>(self + 0x1C8))[i * 0x18 + 0xC] * 4)), 1);
            goto runFrameB;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005b5b4
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditDrawShadow()
{
    struct PppCullBound {
        Vec m_min;
        Vec m_max;
    };

    if (ppvSysStopPartF != 0) {
        return;
    }

    char* self = reinterpret_cast<char*>(this);
    if (*reinterpret_cast<long**>(self + 0x5dc) != 0 && *reinterpret_cast<int*>(self + 0x174) <= 3) {
        Mtx invCamera;
        Vec cameraPos;
        Vec cameraDelta;
        Vec partPos;
        Vec viewPos;

        PSMTXInverse(ppvCameraMatrix, invCamera);
        cameraPos.x = invCamera[0][3];
        cameraPos.y = invCamera[1][3];
        cameraPos.z = invCamera[2][3];

        for (int i = 0; i < 0x180; i++) {
            _pppMngSt* mng = &m_pppMng[i];
            if (mng->m_hitBgFlag == 0 && mng->m_baseTime != -0x1000 && (signed char)mng->m_drawPass == 3
                && mng->m_baseTime < 0 && mng->m_slotVisible != 0 && mng->m_ownerFacing != 0) {
                ppvMng = mng;
                partPos.x = mng->m_matrix.value[0][3];
                partPos.y = mng->m_matrix.value[1][3];
                partPos.z = mng->m_matrix.value[2][3];

                if ((double)mng->m_cullRadiusSq != -1.0) {
                    goto checkCull;
                }

            drawPart:
                PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
                mng->m_sortDepth = viewPos.z;
                ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<char*>(mng->m_pppResSet) + 4);
                ppvMng = mng;
                pppSetFpMatrix(mng);
                _pppDrawPart(mng);
                continue;

            checkCull:
                PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                    PppCullBound bound;
                    float yOffset = mng->m_cullYOffset;
                    float radius = mng->m_cullRadius;
                    bound.m_min.x = partPos.x - radius;
                    bound.m_max.x = partPos.x + radius;
                    bound.m_min.z = partPos.z - radius;
                    bound.m_min.y = partPos.y;
                    bound.m_max.z = partPos.z + radius;
                    bound.m_max.y = partPos.y + yOffset;
                    if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(
                            cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
                        goto drawPart;
                    }
                }
            }
        }
    }

    ppvScreenMatrix[2][3] = ppvScreenMatrixZbuff;
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * PAL Address: 0x8005ae80
 * PAL Size: 1844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditDraw()
{
    static const int kPppMngCount = 0x180;
    static const int kPppMngStride = 0x158;
    static const int kEditCountOffset = 0x2355C;
    static const int kEditDrawModeOffset = 0x23570;
    static const int kCursorEnableOffset = 0xC;
    static const int kBaseTimeOffset = 0x14;
    static const int kLifeEndOffset = 0x24;
    static const int kCurrentFrameOffset = 0x34;
    static const int kMatrixOffset = 0x78;
    static const int kEndRequestedOffset = 0xe8;
    static const int kDrawPassOffset = 0xed;
    static const int kStopAtLifeEndOffset = 0xef;
    static const int kSlotVisibleOffset = 0xe9;
    static const int kOwnerVisibleOffset = 0xea;
    static const int kCullRadiusSqOffset = 0x108;
    static const int kCullRadiusOffset = 0x10c;
    static const int kCullYOffsetOffset = 0x110;
    static const int kSortDepthOffset = 0x114;

    if (ppvSysStopPartF != 0) {
        return;
    }

    m_pppEnvSt.m_debugCounter = 0;

    if (*reinterpret_cast<long**>(reinterpret_cast<unsigned char*>(this) + 0x5dc) != 0) {
        if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x174) <= 3) {
#define PPP_EDIT_DRAW_PASS(drawPass)                                                                       \
            {                                                                                              \
                struct PppCullBound { Vec m_min; Vec m_max; };                                             \
                Mtx invCamera;                                                                             \
                Vec cameraPos;                                                                             \
                Vec cameraDelta;                                                                           \
                Vec partPos;                                                                               \
                Vec viewPos;                                                                               \
                PSMTXInverse(ppvCameraMatrix, invCamera);                                                  \
                cameraPos.x = invCamera[0][3];                                                             \
                cameraPos.y = invCamera[1][3];                                                             \
                cameraPos.z = invCamera[2][3];                                                             \
                                                                                                           \
                for (int i = 0; i < kPppMngCount; i++) {                                                   \
                    _pppMngSt* mng = &m_pppMng[i];                                                         \
                    if (mng->m_hitBgFlag == 0 && mng->m_baseTime != -0x1000                                \
                        && (signed char)mng->m_drawPass == (drawPass) && mng->m_baseTime < 0               \
                        && mng->m_slotVisible != 0 && mng->m_ownerFacing != 0) {                           \
                        ppvMng = mng;                                                                      \
                        partPos.x = mng->m_matrix.value[0][3];                                             \
                        partPos.y = mng->m_matrix.value[1][3];                                             \
                        partPos.z = mng->m_matrix.value[2][3];                                             \
                                                                                                           \
                        if ((double)mng->m_cullRadiusSq != -1.0) {                                          \
                            goto checkCull##drawPass;                                                      \
                        }                                                                                  \
                                                                                                           \
                    drawPart##drawPass:                                                                    \
                        PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);                                 \
                        mng->m_sortDepth = viewPos.z;                                                      \
                        ppvMng = mng;                                                                      \
                        ppvEnv = reinterpret_cast<_pppEnvSt*>(*reinterpret_cast<char**>(mng) + 4);         \
                        pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));                                  \
                        _pppDrawPart(reinterpret_cast<_pppMngSt*>(mng));                                    \
                        continue;                                                                          \
                                                                                                           \
                    checkCull##drawPass:                                                                   \
                        PSVECSubtract(&cameraPos, &partPos, &cameraDelta);                                 \
                        if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {                          \
                            PppCullBound bound;                                                            \
                            float radius = mng->m_cullRadius;                                              \
                            bound.m_min.x = partPos.x - radius;                                            \
                            bound.m_max.x = partPos.x + radius;                                            \
                            bound.m_min.z = partPos.z - radius;                                            \
                            bound.m_min.y = partPos.y;                                                     \
                            bound.m_max.z = partPos.z + radius;                                            \
                            bound.m_max.y = partPos.y + mng->m_cullYOffset;                                \
                            if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(                           \
                                    cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {                    \
                                goto drawPart##drawPass;                                                   \
                            }                                                                              \
                        }                                                                                  \
                    }                                                                                      \
                }                                                                                          \
            }

            PPP_EDIT_DRAW_PASS(8)
            PPP_EDIT_DRAW_PASS(4)
            pppDraw();
            PPP_EDIT_DRAW_PASS(6)
            PPP_EDIT_DRAW_PASS(7)
#undef PPP_EDIT_DRAW_PASS
        } else {
            Vec partPos;
            Vec viewPos;
            char* mng = reinterpret_cast<char*>(m_pppMng);
            int editCount = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + kEditCountOffset);
            for (int i = 0; i < editCount; i++) {
                int baseTime = *reinterpret_cast<int*>(mng + kBaseTimeOffset);
                ppvMng = reinterpret_cast<_pppMngSt*>(mng);
                if (baseTime != -0x1000 && baseTime < 0) {
                    partPos.x = *reinterpret_cast<float*>(mng + kMatrixOffset + 0xc);
                    partPos.y = *reinterpret_cast<float*>(mng + kMatrixOffset + 0x1c);
                    partPos.z = *reinterpret_cast<float*>(mng + kMatrixOffset + 0x2c);
                    PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
                    *reinterpret_cast<float*>(mng + kSortDepthOffset) = viewPos.z;
                    ppvDrawMng.AddPrimOt(0x3ff, reinterpret_cast<_pppMngSt*>(mng));
                    if (*reinterpret_cast<unsigned char*>(mng + kStopAtLifeEndOffset) != 0
                        && *reinterpret_cast<int*>(mng + kCurrentFrameOffset) == *reinterpret_cast<int*>(mng + kLifeEndOffset)) {
                        gPppHeapUseRateWords[1] = 0;
                    }
                }
                mng += kPppMngStride;
            }
            ppvDrawMng.DrawOt();
        }
    }

    if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + kCursorEnableOffset) != 0) {
        drawCursor();
        render3Dcursor();
    }

    ppvScreenMatrix[2][3] = ppvScreenMatrixZbuff;
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
    static const int kEditDrawModeOffset = 0x23570;
    static const int kHeapCheckIntervalOffset = 0x16C;

    if (ppvSysStopPartF == 0) {
        m_pppEnvSt.m_debugCounter = 0;
        if (*reinterpret_cast<long**>(reinterpret_cast<unsigned char*>(this) + 0x5dc) != 0
            && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x174) <= 3) {
#define PPP_DRAW_AFTER_PASS(drawPass)                                                              \
            {                                                                                              \
                struct PppCullBound { Vec m_min; Vec m_max; };                                             \
                Mtx invCamera;                                                                             \
                Vec cameraPos;                                                                             \
                Vec cameraDelta;                                                                           \
                Vec partPos;                                                                               \
                Vec viewPos;                                                                               \
                PSMTXInverse(ppvCameraMatrix, invCamera);                                                  \
                cameraPos.x = invCamera[0][3];                                                             \
                cameraPos.y = invCamera[1][3];                                                             \
                cameraPos.z = invCamera[2][3];                                                             \
                                                                                                           \
                for (int i = 0; i < kPppMngCount; i++) {                                                   \
                    _pppMngSt* mng = &m_pppMng[i];                                                         \
                    if (mng->m_hitBgFlag == 0 && mng->m_baseTime != -0x1000                                \
                        && (signed char)mng->m_drawPass == (drawPass) && mng->m_baseTime < 0               \
                        && mng->m_slotVisible != 0 && mng->m_ownerFacing != 0) {                           \
                        ppvMng = mng;                                                                      \
                        partPos.x = mng->m_matrix.value[0][3];                                             \
                        partPos.y = mng->m_matrix.value[1][3];                                             \
                        partPos.z = mng->m_matrix.value[2][3];                                             \
                                                                                                           \
                        if ((double)mng->m_cullRadiusSq != -1.0) {                                          \
                            goto checkCull##drawPass;                                                      \
                        }                                                                                  \
                                                                                                           \
                    drawPart##drawPass:                                                                    \
                        PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);                                 \
                        mng->m_sortDepth = viewPos.z;                                                      \
                        ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<char*>(mng->m_pppResSet) + 4); \
                        ppvMng = mng;                                                                      \
                        pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));                                  \
                        _pppDrawPart(reinterpret_cast<_pppMngSt*>(mng));                                    \
                        continue;                                                                          \
                                                                                                           \
                    checkCull##drawPass:                                                                   \
                        PSVECSubtract(&cameraPos, &partPos, &cameraDelta);                                 \
                        if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {                          \
                            PppCullBound bound;                                                            \
                            float radius = mng->m_cullRadius;                                              \
                            bound.m_min.x = partPos.x - radius;                                               \
                            bound.m_max.x = partPos.x + radius;                                               \
                            bound.m_min.z = partPos.z - radius;                                               \
                            bound.m_min.y = partPos.y;                                                        \
                            bound.m_max.z = partPos.z + radius;                                               \
                            bound.m_max.y = partPos.y + mng->m_cullYOffset;                                   \
                            if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(                           \
                                    cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {                    \
                                goto drawPart##drawPass;                                                   \
                            }                                                                              \
                        }                                                                                  \
                    }                                                                                      \
                }                                                                                          \
            }

            PPP_DRAW_AFTER_PASS(5)
            PPP_DRAW_AFTER_PASS(6)
            PPP_DRAW_AFTER_PASS(7)
#undef PPP_DRAW_AFTER_PASS
        }
    }

    gPppHeapUseRateWords[0] = pppHeapCheckLeak__FPQ27CMemory6CStage2(ppvEnv->m_stagePtr);
    {
        int prevInterval = gPppHeapUseRateWords[2];
        gPppHeapUseRateWords[2] = prevInterval - 1;
        if (prevInterval == 0 || gPppHeapUseRateWords[0] > gPppHeapUseRateWords[1]) {
            gPppHeapUseRateWords[1] = gPppHeapUseRateWords[0];
            gPppHeapUseRateWords[2] = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + kHeapCheckIntervalOffset) << 1;
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
    PSMTX44Copy(CameraPcs.m_screenMatrix, ppvScreenMatrix);
    PSMTXCopy(CameraPcs.m_cameraMatrix, ppvCameraMatrix);
    ppvScreenMatrixXbuff = ppvScreenMatrix[2][0];
    ppvScreenMatrixYbuff = ppvScreenMatrix[2][1];
    ppvScreenMatrixZbuff = ppvScreenMatrix[2][3];
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
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDumpCacheIdx()
{
    struct PppPartResourceRaw {
        short m_cacheIndex;
        short m_pad;
        long* m_pdt;
    };

    struct PppMngStDumpRaw {
        void* m_pppResSet;              // 0x00
        int m_partIndex;                // 0x04
        unsigned char m_pad08[0x14 - 8];
        int m_baseTime;                 // 0x14
        unsigned char m_pad18[0xA8 - 0x18];
        unsigned char m_envColorR;      // 0xA8
        unsigned char m_envColorG;      // 0xA9
        unsigned char m_envColorB;      // 0xAA
        unsigned char m_envColorA;      // 0xAB
        int m_spawnedCount;             // 0xAC
        unsigned char m_padB0[0xE4 - 0xB0];
        unsigned char m_endRequested;   // 0xE4
        unsigned char m_stopRequested;  // 0xE5
        unsigned char m_isFinished;     // 0xE6
        unsigned char m_matrixMode;     // 0xE7
        unsigned char m_hitBgFlag;      // 0xE8
        unsigned char m_slotVisible;    // 0xE9
        unsigned char m_ownerFacing;    // 0xEA
        unsigned char m_drawVariant;    // 0xEB
        unsigned char m_rotationOrder;  // 0xEC
        signed char m_drawPass;         // 0xED
        signed char m_drawSubType;      // 0xEE
        unsigned char m_useOwnerScaleSign; // 0xEF
        unsigned char m_ownerFlagsInitialized; // 0xF0
        unsigned char m_nodeScaleInitialized;  // 0xF1
        unsigned char m_fieldF2;        // 0xF2
        unsigned char m_padF3[0xF6 - 0xF3];
        unsigned char m_hasMapRef;      // 0xF6
    };

    pppSetRendMatrix();

    int i;
    int gamePaused = Game.m_gameWork.m_gamePaused;
    for (i = 0; i < 0x180; i++) {
        PppMngStDumpRaw* mng = reinterpret_cast<PppMngStDumpRaw*>(
            reinterpret_cast<unsigned char*>(this) + 0x2A18 + i * 0x158);
        if ((gamePaused == 0 || (mng->m_drawPass >= 6 && mng->m_drawPass <= 7)) &&
            mng->m_baseTime != -0x1000) {
            ppvMng = reinterpret_cast<_pppMngSt*>(mng);
            if (mng->m_hitBgFlag != 0) {
                continue;
            }
            ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);

            if (mng->m_baseTime >= 0) {
                goto decrementTimer;
            }

        runFrame:
            pppSetMatrix(reinterpret_cast<_pppMngSt*>(mng));
            pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));

            mng->m_spawnedCount += *reinterpret_cast<int*>(&mng->m_envColorR);
            ppvIs2ndCalc = 0;

            while (mng->m_spawnedCount >= 0x1000) {
                _pppCalcPart(reinterpret_cast<_pppMngSt*>(mng));
                _pppDeadPart(reinterpret_cast<_pppMngSt*>(mng));
                if (mng->m_isFinished != 0) {
                    break;
                }

                ppvIs2ndCalc = 1;
                mng->m_spawnedCount -= 0x1000;
            }

            ppvIs2ndCalc = 0;
            continue;

        decrementTimer:
            {
                int newBaseTime = mng->m_baseTime - 1;
                mng->m_baseTime = newBaseTime;
                if (newBaseTime >= 0) {
                    continue;
                }
            }

            {
                _pppDataHead* pdtHead = *reinterpret_cast<_pppDataHead**>(mng->m_pppResSet);
                PppPartResourceRaw* partResource =
                    reinterpret_cast<PppPartResourceRaw*>(reinterpret_cast<unsigned char*>(pdtHead->m_cacheChunks) +
                                                          mng->m_partIndex * sizeof(PppPartResourceRaw));

                if (ppvAmemCacheSet.IsEnable(partResource->m_cacheIndex) == 0) {
                    partResource->m_pdt = reinterpret_cast<long*>(
                        ppvAmemCacheSet.GetData(
                            partResource->m_cacheIndex, const_cast<char*>(s_partMng_cpp), 0x9A9));
                    pppInitPdt(partResource->m_pdt, pppGetSysProgTable());
                }

                ppvAmemCacheSet.AddRef(partResource->m_cacheIndex);
                mng->m_hasMapRef = 1;
                _pppStartPart(reinterpret_cast<_pppMngSt*>(mng), partResource->m_pdt, 1);
            }
            goto runFrame;
        }
    }
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
 * PAL Address: 0x8005a4f4
 * PAL Size: 456b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDrawPrio(unsigned char drawMode)
{
    struct PppCullBound {
        Vec m_min;
        Vec m_max;
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec cameraDelta;
    Vec partPos;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* mng = &m_pppMng[i];
        if (mng->m_hitBgFlag == 0 && mng->m_baseTime != -0x1000
            && (signed char)mng->m_drawPass == drawMode && mng->m_baseTime < 0
            && mng->m_slotVisible != 0 && mng->m_ownerFacing != 0) {
            ppvMng = mng;
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            if ((double)mng->m_cullRadiusSq != -1.0) {
                goto checkCull;
            }

        drawPart:
            PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
            mng->m_sortDepth = viewPos.z;
            ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<char*>(mng->m_pppResSet) + 4);
            ppvMng = mng;
            pppSetFpMatrix(mng);
            _pppDrawPart(mng);
            continue;

        checkCull:
            PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
            if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                PppCullBound bound;
                float yOffset = mng->m_cullYOffset;
                float radius = mng->m_cullRadius;
                bound.m_min.x = partPos.x - radius;
                bound.m_max.x = partPos.x + radius;
                bound.m_min.z = partPos.z - radius;
                bound.m_min.y = partPos.y;
                bound.m_max.z = partPos.z + radius;
                bound.m_max.y = partPos.y + yOffset;
                if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(
                        cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
                    goto drawPart;
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005a308
 * PAL Size: 492b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDrawPrioPdtFpno(unsigned char drawMode, short kind, short nodeIndex)
{
    struct PppMngStDrawPdtRaw {
        void* m_pppResSet;                   // 0x00
        int m_partIndex;                     // 0x04
        Vec m_position;                      // 0x08
        int m_baseTime;                      // 0x14
        unsigned char m_pad18[0x74 - 0x18]; // 0x18
        short m_kind;                        // 0x74
        short m_nodeIndex;                   // 0x76
        pppFMATRIX m_matrix;                 // 0x78
        unsigned char m_padA8[0xE4 - 0xA8]; // 0xA8
        unsigned char m_mode;                // 0xE4
        unsigned char m_stopRequested;       // 0xE5
        unsigned char m_isFinished;          // 0xE6
        unsigned char m_matrixMode;          // 0xE7
        unsigned char m_endRequested;        // 0xE8
        unsigned char m_slotVisible;         // 0xE9
        unsigned char m_ownerFacing;         // 0xEA
        unsigned char m_drawVariant;         // 0xEB
        unsigned char m_rotationOrder;       // 0xEC
        signed char m_drawMode;            // 0xED
        signed char m_drawSubType;           // 0xEE
        unsigned char m_useOwnerScaleSign;   // 0xEF
        unsigned char m_ownerVisible;        // 0xF0
        unsigned char m_nodeScaleInitialized; // 0xF1
        unsigned char m_fieldF2;             // 0xF2
        unsigned char m_padF3[0x108 - 0xF3]; // 0xF3
        float m_cullRadiusSq;                // 0x108
        float m_cullRadius;                  // 0x10C
        float m_cullYOffset;                 // 0x110
        float m_sortDepth;                   // 0x114
        unsigned char m_pad118[0x158 - 0x118]; // 0x118
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec cameraDelta;
    Vec partPos;
    Vec viewPos;
    PppMngStDrawPdtRaw* mng;
    int remaining;

    PSMTXInverse(ppvCameraMatrix, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    unsigned char* base = reinterpret_cast<unsigned char*>(this);
    for (remaining = 0x180; remaining != 0; remaining--) {
        mng = reinterpret_cast<PppMngStDrawPdtRaw*>(base + 0x2A18);
        if (mng->m_nodeIndex == nodeIndex && mng->m_kind == kind && mng->m_endRequested == 0
            && mng->m_baseTime != -0x1000 && mng->m_drawMode == drawMode && mng->m_baseTime < 0) {
            if (mng->m_slotVisible == 0) {
                break;
            }

            ppvMng = reinterpret_cast<_pppMngSt*>(mng);
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            {
                struct PppCullBound { Vec m_min; Vec m_max; };

                if ((double)mng->m_cullRadiusSq != -1.0) {
                    goto checkCull;
                }

            drawPart:
                PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
                mng->m_sortDepth = viewPos.z;
                ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<char*>(mng->m_pppResSet) + 4);
                ppvMng = reinterpret_cast<_pppMngSt*>(mng);
                pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));
                _pppDrawPart(reinterpret_cast<_pppMngSt*>(mng));
                break;

            checkCull:
                PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                if (!(PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq)) {
                    break;
                }

                PppCullBound bound;
                float yOffset = mng->m_cullYOffset;
                float radius = mng->m_cullRadius;
                bound.m_min.y = partPos.y;
                bound.m_max.y = partPos.y + yOffset;
                bound.m_min.x = partPos.x - radius;
                bound.m_max.x = partPos.x + radius;
                bound.m_min.z = partPos.z - radius;
                bound.m_max.z = partPos.z + radius;
                if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(
                        cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
                    goto drawPart;
                }
                break;
            }
        }
        base += 0x158;
    }
    if (drawMode < 8) {
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005a18c
 * PAL Size: 380b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDrawIdx(int partIndex)
{
    struct PppCullBound {
        Vec m_min;
        Vec m_max;
    };

    struct PppMngStDrawIdxRaw {
        void* m_pppResSet;                   // 0x00
        unsigned char m_pad04[0x14 - 0x4];
        int m_baseTime;                      // 0x14
        unsigned char m_pad18[0x78 - 0x18];
        pppFMATRIX m_matrix;                 // 0x78
        unsigned char m_padA8[0xE8 - 0xA8];
        unsigned char m_deleteRequested;     // 0xE8
        unsigned char m_padE9[0x108 - 0xE9];
        float m_cullRadiusSq;                // 0x108
        float m_cullRadius;                  // 0x10C
        float m_cullYOffset;                 // 0x110
        float m_sortDepth;                   // 0x114
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec cameraDelta;
    Vec partPos;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    PppMngStDrawIdxRaw* mng =
        reinterpret_cast<PppMngStDrawIdxRaw*>(reinterpret_cast<unsigned char*>(this) + 0x2A18 + partIndex * 0x158);
    if (mng->m_deleteRequested != 0) {
        return;
    }
    if (mng->m_baseTime == -0x1000) {
        return;
    }
    if (mng->m_baseTime >= 0) {
        return;
    }

    ppvMng = reinterpret_cast<_pppMngSt*>(mng);
    partPos.x = mng->m_matrix.value[0][3];
    partPos.y = mng->m_matrix.value[1][3];
    partPos.z = mng->m_matrix.value[2][3];

    if ((double)mng->m_cullRadiusSq != -1.0) {
        goto checkCull;
    }

drawPart:
    PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
    mng->m_sortDepth = viewPos.z;
    ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);
    ppvMng = reinterpret_cast<_pppMngSt*>(mng);
    pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));
    _pppDrawPart(reinterpret_cast<_pppMngSt*>(mng));
    return;

checkCull:
    PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
    if (!(PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq)) {
        return;
    }

    {
        PppCullBound bound;
        float yOffset = mng->m_cullYOffset;
        float radius = mng->m_cullRadius;
        bound.m_min.y = partPos.y;
        bound.m_max.y = partPos.y + yOffset;
        bound.m_min.x = partPos.x - radius;
        bound.m_max.x = partPos.x + radius;
        bound.m_min.z = partPos.z - radius;
        bound.m_max.z = partPos.z + radius;
        if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
            goto drawPart;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80059f6c
 * PAL Size: 544b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDraw()
{
    struct PppCullBound {
        Vec m_min;
        Vec m_max;
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec viewPos;
    Vec partPos;
    Vec cameraDelta;

    m_pppEnvSt.m_debugCounter = 0;
    PSMTXInverse(ppvCameraMatrix, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* mng = &m_pppMng[i];
        if (mng->m_hitBgFlag == 0 && mng->m_baseTime != -0x1000 && (signed char)mng->m_drawPass <= 2 && mng->m_baseTime < 0
            && mng->m_slotVisible != 0 && mng->m_ownerFacing != 0) {
            ppvMng = mng;
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            if ((double)mng->m_cullRadiusSq != -1.0) {
                goto checkCull;
            }

        drawPart:
            PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
            mng->m_sortDepth = viewPos.z;

            switch ((signed char)mng->m_drawPass) {
            case 0:
                ppvDrawMng.AddPrim(viewPos.z, reinterpret_cast<_pppMngSt*>(mng), mng->m_drawSubType);
                break;
            case 1:
                ppvDrawMng.AddPrimOt(0x3FF, reinterpret_cast<_pppMngSt*>(mng));
                break;
            case 2:
                ppvDrawMng.AddPrimOt(0, reinterpret_cast<_pppMngSt*>(mng));
                break;
            }
            goto nextPart;

        checkCull:
            {
                PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                    PppCullBound bound;
                    float yOffset = mng->m_cullYOffset;
                    float radius = mng->m_cullRadius;
                    bound.m_min.x = partPos.x - radius;
                    bound.m_max.x = partPos.x + radius;
                    bound.m_min.z = partPos.z - radius;
                    bound.m_min.y = partPos.y;
                    bound.m_max.z = partPos.z + radius;
                    bound.m_max.y = partPos.y + yOffset;
                    if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) == 0) {
                        goto nextPart;
                    }
                    goto drawPart;
                }
                goto nextPart;
            }
        }
    nextPart:
        ;
    }

    ppvDrawMng.DrawOt();
}

/*
 * --INFO--
 * PAL Address: 0x80059d64
 * PAL Size: 520b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppPartDrawAfter()
{
    struct PppCullBound {
        Vec m_min;
        Vec m_max;
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec cameraDelta;
    Vec partPos;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* mng = &m_pppMng[i];
        if (mng->m_hitBgFlag == 0 && mng->m_baseTime != -0x1000 && (signed char)mng->m_drawPass == 5
            && mng->m_baseTime < 0 && mng->m_slotVisible != 0 && mng->m_ownerFacing != 0) {
            ppvMng = mng;
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            if ((double)mng->m_cullRadiusSq != -1.0) {
                goto checkCull;
            }

        drawPart:
            PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
            mng->m_sortDepth = viewPos.z;
            ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<char*>(mng->m_pppResSet) + 4);
            ppvMng = mng;
            pppSetFpMatrix(mng);
            _pppDrawPart(mng);
            continue;

        checkCull:
            PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
            if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                PppCullBound bound;
                float yOffset = mng->m_cullYOffset;
                float radius = mng->m_cullRadius;
                bound.m_min.x = partPos.x - radius;
                bound.m_max.x = partPos.x + radius;
                bound.m_min.z = partPos.z - radius;
                bound.m_min.y = partPos.y;
                bound.m_max.z = partPos.z + radius;
                bound.m_max.y = partPos.y + yOffset;
                if (reinterpret_cast<CBound*>(&bound)->CheckFrustum(
                        cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
                    goto drawPart;
                }
            }
        }
    }

    gPppHeapUseRateWords[0] = pppHeapCheckLeak__FPQ27CMemory6CStage2(ppvEnv->m_stagePtr);
    {
        int prevInterval = gPppHeapUseRateWords[2];
        gPppHeapUseRateWords[2] = prevInterval - 1;
        if (prevInterval == 0 || gPppHeapUseRateWords[0] > gPppHeapUseRateWords[1]) {
            gPppHeapUseRateWords[1] = gPppHeapUseRateWords[0];
            gPppHeapUseRateWords[2] = *(int*)((char*)this + 0x16C) << 1;
        }
    }
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
    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0xb3d);

#define base (reinterpret_cast<char*>(this))
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + i * 0x158 + 0x2A18);
        int baseTime = pppMngSt->m_baseTime;
        if (baseTime != -0x1000 && baseTime < 0) {
            unsigned char isFinished = *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE6);
            if (isFinished != 0 || *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE8) != 0) {
                ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<char*>(pppMngSt->m_pppResSet) + 4);
                ppvMng = pppMngSt;
                _pppAllFreePObject(pppMngSt);
            }
        }
    }
#undef base

    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0xb5d);
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
/*
 * --INFO--
 * PAL Address: 0x80059c44
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppPartInit()
{
    char* base = reinterpret_cast<char*>(this);
    int i = 0;

    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x8) = 0;
    do {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + 0x2A18);
        int baseTime = pppMngSt->m_baseTime;
        if (baseTime != -0x1000 && baseTime < 0) {
            _pppInitPart(pppMngSt);
        }
        base += 0x158;
        i++;
    } while (i < 0x180);
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
void* CPartMng::pppFileRead(char* filePath, unsigned long& fileSize, void* readBuffer, int readBufferSize)
{
    CPartMngLoadState* loadState = reinterpret_cast<CPartMngLoadState*>(this);
    CFile::CHandle* fileHandle;

    if (loadState->m_partLoadMode == 1) {
        fileSize = loadState->m_partChunkSize[loadState->m_partChunkIndex];
        if (fileSize == 0) {
            return 0;
        }
        readBuffer = File.m_readBuffer;
        Memory.CopyFromAMemorySync(
            readBuffer, reinterpret_cast<void*>(loadState->m_partAMemCursor), (fileSize + 0x1f) & ~0x1f);
        loadState->m_partAMemCursor += fileSize;
        CheckSum(readBuffer, fileSize);
        loadState->m_partChunkIndex++;
    } else if (readBuffer == 0 && (fileHandle = File.Open(filePath, 0, CFile::PRI_LOW), fileHandle == 0)) {
        goto failReturn;
    } else if (loadState->m_partLoadMode == 3) {
        File.ReadASync(fileHandle);
        readBuffer = reinterpret_cast<void*>(1);
        loadState->m_partAsyncBusy[loadState->m_asyncHandleCount] = fileHandle;
        loadState->m_asyncHandleCount++;
    } else {
        if (readBuffer != 0) {
            fileSize = readBufferSize;
        } else {
            fileSize = File.GetLength(fileHandle);
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);
            readBuffer = File.m_readBuffer;
            File.Close(fileHandle);
        }
        if (loadState->m_partLoadMode == 2) {
            Memory.CopyToAMemorySync(readBuffer, reinterpret_cast<void*>(loadState->m_partAMemCursor), fileSize);
            loadState->m_partChunkSize[loadState->m_partChunkIndex] = fileSize;
            loadState->m_partChunkChecksum[loadState->m_partChunkIndex] = CheckSum(readBuffer, fileSize);
            loadState->m_partChunkIndex++;
            loadState->m_partAMemCursor += fileSize;
        }
    }

    return readBuffer;

failReturn:
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::LoadPartNoSyncCalc()
{
    for (int i = 0; i < 0x10; i++) {
        if (m_partAsyncBusy[i] != 0) {
            if (File.IsCompleted(m_partAsyncBusy[i])) {
                int len;
                void* readBuffer = File.m_readBuffer;
                len = File.GetLength(m_partAsyncBusy[i]);
                void* amemCursor = reinterpret_cast<void*>(m_partAMemCursor);

                Memory.CopyToAMemorySync(readBuffer, amemCursor, (len + 0x1f) & ~0x1f);
                m_partChunkSize[i] = len;
                m_partChunkChecksum[i] = CheckSum(readBuffer, len);
                m_partChunkIndex++;
                m_partAMemCursor += len;

                File.Close(m_partAsyncBusy[i]);
                m_partAsyncBusy[i] = 0;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80059658
 * PAL Size: 724b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppLoadPtx(const char* baseName, int pdtSlotIndex, int appendMode, void* readBuffer, int readBufferSize)
{
    ppvAmemCacheSet.CacheClear();
    PartPcs.m_usbStreamState.m_stageLoad->setDefaultParam(pdtSlotIndex);

    char* path = g_StrTmp;
    sprintf(path, sPtxPathFmt, baseName);
    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_ReadPtxLogFormat), path);
    }

    unsigned long fileSize;
    void* fileData = pppFileRead(path, fileSize, readBuffer, readBufferSize);
    if (fileData == 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
            System.Printf(const_cast<char*>(s_CanNotReadFormat), path);
        }
        PartPcs.m_usbStreamState.m_stageLoad->resDefaultParam();
        return 0;
    }

    if (m_partLoadMode == 2) {
        return 1;
    }
    if (m_partLoadMode == 3) {
        return 1;
    }

    if (m_textureSet == 0) {
        m_textureSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0xC10) CTextureSet;
        CTextureSet* textureSet = m_textureSet;
        textureSet->m_textureArray.SetDefaultSize(0x180);
        textureSet->m_textureArray.SetGrow(0);
    }

    if (m_materialSet == 0) {
        m_materialSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0xC14) CMaterialSet;
        CMaterialSet* materialSet = m_materialSet;
        materialSet->m_materials.SetDefaultSize(0x180);
        materialSet->m_materials.SetGrow(0);
        m_pppEnvSt.m_materialSetPtr = m_materialSet;

        CMaterial* defaultMaterial = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0xC17) CMaterial;
        defaultMaterial->Create(0, static_cast<CMaterialMan::TEV_BIT>(0xFFF531F0));
        if (static_cast<unsigned int>(m_materialSet->m_materials.GetSize()) == 0U) {
            materialSet->m_materials.Add(defaultMaterial);
        } else {
            materialSet->m_materials.SetAt(0, defaultMaterial);
        }
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case kChunkTSET:
            m_textureSet->Create(chunkFile, PartPcs.m_usbStreamState.m_stageLoad, 1, &ppvAmemCacheSet, appendMode, 0);
            break;
        }
    }

    m_materialSet->SetPartFromTextureSet(m_textureSet, pdtSlotIndex);
    m_materialSet->SetTextureSet(m_textureSet);
    PartPcs.m_usbStreamState.m_stageLoad->resDefaultParam();
    return 1;
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
 * PAL Address: 0x80059238
 * PAL Size: 912b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppLoadPmd(const char* baseName)
{
    char* path = g_StrTmp;
    unsigned long fileSize;

    sprintf(path, sPmdPathFmt, baseName);
    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_ReadPmdLogFormat), path);
    }

    void* fileData = pppFileRead(path, fileSize, 0, 0);
    if (fileData == 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
            System.Printf(const_cast<char*>(s_CanNotReadFormat), path);
        }
        return 0;
    }

    if (m_pppModelStArr == 0) {
        CMemory::CStage* stageLoad = PartPcs.m_usbStreamState.m_stageLoad;
        struct PartMngModelStBlock {
            pppModelSt m_entries[0x100];
        };
        pppModelSt* modelArray = reinterpret_cast<pppModelSt*>(new (stageLoad, const_cast<char*>(s_partMng_cpp), 0xca9) PartMngModelStBlock);
        for (int i = 0; i < 0x100; i++) {
            modelArray[i].m_isUsed = 0;
        }
        m_pppModelStArr = modelArray;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    CChunkFile::CChunk outerChunk;
    while (chunkFile.GetNextChunk(outerChunk)) {
        chunkFile.PushChunk();
        switch (outerChunk.m_id) {
        case kChunkRSET: {
            pppModelSt* modelArray = m_pppModelStArr;
            pppModelSt* targetModel = 0;

            CChunkFile::CChunk innerChunk;
            while (chunkFile.GetNextChunk(innerChunk)) {
                switch (innerChunk.m_id) {
                case kChunkNAME: {
                    char* name = chunkFile.GetString();

                    pppModelSt* searchModel = modelArray;
                    unsigned int i = 0;
                    for (;;) {
                        if (searchModel->m_isUsed != 0 && strcmp(searchModel->m_name, name) == 0) {
                            goto pmdNameSearchDone;
                        }
                        i++;
                        searchModel++;
                        if (i >= 0x100) {
                            searchModel = 0;
                            goto pmdNameSearchDone;
                        }
                    }
                pmdNameSearchDone:

                    if (searchModel == 0) {
                        pppModelSt* freeModel = modelArray;
                        for (int freeIndex = 0; freeIndex < 0x100; freeIndex++) {
                            if (freeModel->m_isUsed == 0) {
                                targetModel = modelArray + freeIndex;
                                goto foundFreeModel;
                            }
                            freeModel++;
                        }
                        targetModel = 0;
                    foundFreeModel:

                        targetModel->m_refCount = 0;
                        targetModel->m_isUsed = 1;
                        strcpy(targetModel->m_name, name);
                    } else {
                        targetModel = 0;
                    }
                    break;
                }
                case kChunkRSDM:
                    if (targetModel != 0) {
                        CChunkFile rsdFile;
                        rsdFile.SetBuf(chunkFile.GetAddress());
                        unsigned int meshSize = pppReadRsd(rsdFile, targetModel);
                        targetModel->Ptr2Off();

                        void** meshDataPtr =
                            reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(targetModel) + 0x24);
                        targetModel->m_cacheId = static_cast<short>(ppvAmemCacheSet.SetData(
                            *meshDataPtr, meshSize, static_cast<CAmemCache::TYPE>(1), 1));

                        if (*meshDataPtr != 0) {
                            operator delete(*meshDataPtr);
                            *meshDataPtr = 0;
                        }

                        targetModel->m_refCount++;
                        targetModel = 0;
                    }
                    break;
                }
            }
            break;
        }
        }
        chunkFile.PopChunk();
    }

    return 1;
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
 * PAL Address: 0x80058e58
 * PAL Size: 844b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppLoadPan(const char* baseName)
{
    char* path = g_StrTmp;
    unsigned long fileSize;

    sprintf(path, sPanPathFmt, baseName);
    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_ReadPanLogFormat), path);
    }

    void* fileData = pppFileRead(path, fileSize, 0, 0);
    if (fileData == 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
            System.Printf(const_cast<char*>(s_CanNotReadFormat), path);
        }
        return 0;
    }

    if (m_pppShapeStArr == 0) {
        CMemory::CStage* stageLoad = PartPcs.m_usbStreamState.m_stageLoad;
        struct PartMngShapeStBlock {
            pppShapeSt m_entries[0x100];
        };
        pppShapeSt* shapeArray = reinterpret_cast<pppShapeSt*>(new (stageLoad, const_cast<char*>(s_partMng_cpp), 0xd0b) PartMngShapeStBlock);
        for (int i = 0; i < 0x100; i++) {
            shapeArray[i].m_inUse = 0;
        }
        m_pppShapeStArr = shapeArray;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    CChunkFile::CChunk outerChunk;
    while (chunkFile.GetNextChunk(outerChunk)) {
        chunkFile.PushChunk();
        switch (outerChunk.m_id) {
        case kChunkSSET: {
            pppShapeSt* shapeArray = m_pppShapeStArr;
            pppShapeSt* targetShape = 0;

            CChunkFile::CChunk innerChunk;
            while (chunkFile.GetNextChunk(innerChunk)) {
                switch (innerChunk.m_id) {
                case kChunkNAME: {
                    char* name = chunkFile.GetString();

                    pppShapeSt* searchShape = shapeArray;
                    unsigned int i = 0;
                    for (;;) {
                        if (searchShape->m_inUse != 0 && strcmp(searchShape->m_name, name) == 0) {
                            goto panNameSearchDone;
                        }
                        i++;
                        searchShape = reinterpret_cast<pppShapeSt*>(
                            reinterpret_cast<unsigned char*>(searchShape) + 0x2c);
                        if (i >= 0x100) {
                            searchShape = 0;
                            goto panNameSearchDone;
                        }
                    }
                panNameSearchDone:

                    if (searchShape == 0) {
                        pppShapeSt* freeShape = shapeArray;
                        for (int freeIndex = 0; freeIndex < 0x100; freeIndex++) {
                            if (freeShape->m_inUse == 0) {
                                targetShape = reinterpret_cast<pppShapeSt*>(
                                    reinterpret_cast<unsigned char*>(shapeArray) + freeIndex * 0x2c);
                                goto foundFree;
                            }
                            freeShape = reinterpret_cast<pppShapeSt*>(
                                reinterpret_cast<unsigned char*>(freeShape) + 0x2c);
                        }
                        targetShape = 0;
                    foundFree:

                        targetShape->m_refCount = 0;
                        targetShape->m_inUse = 1;
                        strcpy(targetShape->m_name, name);
                    } else {
                        targetShape = 0;
                    }
                    break;
                }
                case kChunkSHPM:
                    if (targetShape != 0) {
                        CChunkFile shpFile;
                        shpFile.SetBuf(chunkFile.GetAddress());
                        pppReadShp(shpFile, targetShape);
                        targetShape->m_refCount++;
                        targetShape = 0;
                    }
                    break;
                }
            }
            break;
        }
        }
        chunkFile.PopChunk();
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800588e0
 * PAL Size: 1400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppLoadPdt(const char* baseName, int pdtSlotIndex, int cachePriority, void* readBuffer, int readBufferSize)
{
    ppvAmemCacheSet.CacheClear();
    PartPcs.m_usbStreamState.m_stageLoad->setDefaultParam(pdtSlotIndex);

    char* pdtPath = g_StrTmp;
    sprintf(pdtPath, sPdtPathFmt, baseName);
    PppPdtSlot* pdtSlot = &m_pdtSlots[pdtSlotIndex];
    strncpy(pdtSlot->m_name, baseName, sizeof(pdtSlot->m_name));

    if (static_cast<unsigned int>(System.m_execParam) >= 3U) {
        System.Printf(const_cast<char*>(s_ReadPdtLogFormat), pdtPath);
    }

    unsigned long pdtSize;
    void* pdtData = pppFileRead(pdtPath, pdtSize, readBuffer, readBufferSize);
    if (pdtData == 0) {
        pdtSlot->m_pppDataHead = 0;
        if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
            System.Printf(const_cast<char*>(s_CanNotReadFormat), pdtPath);
        }
        PartPcs.m_usbStreamState.m_stageLoad->resDefaultParam();
        return 0;
    }

    if (m_partLoadMode == 2) {
        return 1;
    }
    if (m_partLoadMode == 3) {
        return 1;
    }

    CChunkFile pdtFile;
    pdtFile.SetBuf(pdtData);

    CChunkFile::CChunk parentChunk;
    while (pdtFile.GetNextChunk(parentChunk)) {
        pdtFile.PushChunk();
        switch (parentChunk.m_id) {
        case kChunkPDT: {
            while (pdtFile.GetNextChunk(parentChunk)) {
                pdtFile.PushChunk();
                switch (parentChunk.m_id) {
                case kChunkRSET: {
                    pppModelSt* modelArray = m_pppModelStArr;
                    pppModelSt* targetModel = 0;

                    CChunkFile::CChunk resourceChunk;
                    while (pdtFile.GetNextChunk(resourceChunk)) {
                        switch (resourceChunk.m_id) {
                        case kChunkNAME: {
                            char* name = pdtFile.GetString();

                            pppModelSt* searchModel = modelArray;
                            unsigned int i = 0;
                            for (;;) {
                                if (searchModel->m_isUsed != 0 && strcmp(searchModel->m_name, name) == 0) {
                                    goto nameSearchDone;
                                }
                                i++;
                                searchModel++;
                                if (i >= 0x100) {
                                    searchModel = 0;
                                    goto nameSearchDone;
                                }
                            }
                        nameSearchDone:

                            if (searchModel == 0) {
                                pppModelSt* freeModel = modelArray;
                                for (int freeIndex = 0; freeIndex < 0x100; freeIndex++) {
                                    if (freeModel->m_isUsed == 0) {
                                        targetModel = modelArray + freeIndex;
                                        goto foundFreeModel;
                                    }
                                    freeModel++;
                                }
                                targetModel = 0;
                            foundFreeModel:

                                targetModel->m_refCount = 0;
                                targetModel->m_isUsed = 1;
                                strcpy(targetModel->m_name, name);
                            } else {
                                targetModel = 0;
                            }
                            break;
                        }
                        case kChunkRSDM:
                            if (targetModel != 0) {
                                CChunkFile rsdFile;
                                rsdFile.SetBuf(pdtFile.GetAddress());
                                unsigned int meshSize = pppReadRsd(rsdFile, targetModel);
                                targetModel->Ptr2Off();

                                void** meshDataPtr =
                                    reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(targetModel) + 0x24);
                                targetModel->m_cacheId = static_cast<short>(ppvAmemCacheSet.SetData(
                                    *meshDataPtr, meshSize, static_cast<CAmemCache::TYPE>(1), cachePriority));

                                if (*meshDataPtr != 0) {
                                    operator delete(*meshDataPtr);
                                    *meshDataPtr = 0;
                                }
                                targetModel = 0;
                            }
                            break;
                        }
                    }
                    break;
                }
                case kChunkSSET: {
                    pppShapeSt* shapeArray = m_pppShapeStArr;
                    pppShapeSt* targetShape = 0;

                    CChunkFile::CChunk shapeChunk;
                    while (pdtFile.GetNextChunk(shapeChunk)) {
                        switch (shapeChunk.m_id) {
                        case kChunkNAME: {
                            char* name = pdtFile.GetString();

                            pppShapeSt* searchShape = shapeArray;
                            unsigned int i = 0;
                            do {
                                if (searchShape->m_inUse != 0 && strcmp(searchShape->m_name, name) == 0) {
                                    break;
                                }
                                i++;
                                searchShape++;
                            } while (i < 0x100);
                            if (i >= 0x100) {
                                searchShape = 0;
                            }

                            if (searchShape == 0) {
                                pppShapeSt* freeShape = shapeArray;
                                for (int freeIndex = 0; freeIndex < 0x100; freeIndex++) {
                                    if (freeShape->m_inUse == 0) {
                                        targetShape = shapeArray + freeIndex;
                                        goto foundFreeShape;
                                    }
                                    freeShape++;
                                }
                                targetShape = 0;
                            foundFreeShape:

                                targetShape->m_refCount = 0;
                                targetShape->m_inUse = 1;
                                strcpy(targetShape->m_name, name);
                            } else {
                                targetShape = 0;
                            }
                            break;
                        }
                        case kChunkSHPM:
                            if (targetShape != 0) {
                                CChunkFile shpFile;
                                shpFile.SetBuf(pdtFile.GetAddress());
                                pppReadShp(shpFile, targetShape);
                                targetShape = 0;
                            }
                            break;
                        }
                    }
                    break;
                }
                case kChunkPDTS: {
                    _pppDataHead* sourceHead = reinterpret_cast<_pppDataHead*>(pdtFile.GetAddress());
                    pppInitData(sourceHead, pppGetSysProgTable(), cachePriority);

                    unsigned long copySize = sourceHead->m_partCount * 0x60 + 0x20;
                    _pppDataHead* copiedHead = static_cast<_pppDataHead*>(
                        operator new[](
                            copySize, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0xd56));
                    pdtSlot->m_pppDataHead = copiedHead;

                    memcpy(copiedHead, sourceHead, copySize);

                    ppvEnv = reinterpret_cast<_pppEnvSt*>(pdtSlot->m_envFields);
                    pdtSlot->m_envFields[1] = reinterpret_cast<unsigned int>(m_materialSet);

                    if (copiedHead != 0) {
                        pdtSlot->m_envFields[2] = copiedHead->m_modelNames;
                        pdtSlot->m_envFields[3] = copiedHead->m_shapeNames;
                        pdtSlot->m_envFields[4] = copiedHead->m_shapeGroups;
                    }
                    pdtSlot->m_envFields[0] = reinterpret_cast<unsigned int>(PartMng.m_pppEnvSt.m_stagePtr);
                    break;
                }
                }
                pdtFile.PopChunk();
            }
                } break;
        }
        pdtFile.PopChunk();
    }

    PartPcs.m_usbStreamState.m_stageLoad->resDefaultParam();
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8005880c
 * PAL Size: 212b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppGetFreeDataMng()
{
    PppPdtSlot* freeSlot;
    int slotIndex = 8;
    for (int count = 0x18; count != 0; count--) {
        if (m_pdtSlots[slotIndex].m_pppDataHead == 0) {
            freeSlot = &m_pdtSlots[slotIndex];
            goto found;
        }
        slotIndex++;
    }
    freeSlot = 0;
found:

    if (freeSlot == 0) {
        if ((unsigned int)System.m_execParam >= 1) {
            System.Printf(const_cast<char*>(sPppFreeDataMngAllocError));
        }
        OSPanic(const_cast<char*>(s_partMng_cpp), 0xD74, const_cast<char*>(sPartMngEmptyString));
        return -1;
    }

    return freeSlot - m_pdtSlots;
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
PPPCREATEPARAM* CPartMng::pppGetDefaultCreateParam()
{
    g_dcp.m_positionOffsetPtr = 0;
    g_dcp.m_rotationPtr = 0;
    g_dcp.m_scalePtr = 0;
    g_dcp.m_extraPositionPtr = 0;
    g_dcp.m_paramA = 0;
    g_dcp.m_paramB = 0;
    g_dcp.m_objectHitMask = 0;
    g_dcp.m_cylinderAttribute = 0;
    g_dcp.m_paramC = kPartMngOne;
    g_dcp.m_paramD = kPartMngOne;
    *reinterpret_cast<unsigned char*>(&g_dcp.m_owner) = 0;
    g_dcp.m_soundEffectParams.m_soundEffectHandle = -1;
    g_dcp.m_soundEffectParams.m_soundEffectSlot = -1;
    g_dcp.m_soundEffectParams.m_soundEffectStopFlag = 0;
    g_dcp.m_soundEffectParams.m_soundEffectKind = 1;
    g_dcp.m_soundEffectParams.m_soundEffectStartFrame = 0;
    g_dcp.m_soundEffectParams.m_soundEffectStartedOnce = 0;
    g_dcp.m_soundEffectParams.m_soundEffectFadeFrames = 0x1e;
    return &g_dcp;
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
struct PppHitIdBlock {
    int m_ids[8];
};

int CPartMng::pppCreate0(int pdtSlotIndex, int fpNo, PPPCREATEPARAM* createParam, int allowFpOverride)
{
    struct PppMngStCreateRaw {
        void* m_pppResSet;           // 0x00
        int m_partIndex;             // 0x04
        Vec m_position;              // 0x08
        int m_baseTime;              // 0x14
        pppIVECTOR4 m_rotation;      // 0x18
        int m_rotationSpeed;         // 0x20
        int m_lifeEnd;               // 0x24
        Vec m_scale;                 // 0x28
        int m_currentFrame;          // 0x34
        int m_previousFrame;         // 0x38
        int m_numControlPrograms;    // 0x3C
        float m_scaleFactor;         // 0x40
        float m_ownerScale;          // 0x44
        float m_userFloat0;          // 0x48
        float m_userFloat1;          // 0x4C
        Vec m_savedPosition;         // 0x50
        Vec m_previousPosition;      // 0x5C
        Vec m_paramVec0;             // 0x68
        short m_kind;                // 0x74
        short m_nodeIndex;           // 0x76
        pppFMATRIX m_matrix;         // 0x78
        unsigned char m_envColorR;   // 0xA8
        unsigned char m_envColorG;   // 0xA9
        unsigned char m_envColorB;   // 0xAA
        unsigned char m_envColorA;   // 0xAB
        int m_spawnedCount;          // 0xAC
        int m_previousFrame2;        // 0xB0
        int m_numControlPrograms2;   // 0xB4
        int m_numPrograms2;          // 0xB8
        unsigned int m_objHitMask;   // 0xBC
        unsigned int m_cylinderAttribute; // 0xC0
        _pppPObjLink m_pppPObjLinkHead;   // 0xC4 (size 0xC)
        void* m_programTable;        // 0xD0
        void* m_pppPDataVals;        // 0xD4
        void* m_owner;               // 0xD8
        void* m_lookTarget;          // 0xDC
        void* m_bindNode;            // 0xE0
        unsigned char m_endRequested;     // 0xE4
        unsigned char m_stopRequested;    // 0xE5
        unsigned char m_isFinished;       // 0xE6
        unsigned char m_matrixMode;       // 0xE7
        unsigned char m_hitBgFlag;        // 0xE8
        unsigned char m_slotVisible;      // 0xE9
        unsigned char m_ownerFacing;      // 0xEA
        unsigned char m_drawVariant;      // 0xEB
        unsigned char m_rotationOrder;    // 0xEC
        unsigned char m_drawPass;         // 0xED
        signed char m_drawSubType;        // 0xEE
        unsigned char m_useOwnerScaleSign; // 0xEF
        unsigned char m_ownerFlagsInitialized; // 0xF0
        unsigned char m_nodeScaleInitialized;   // 0xF1
        unsigned char m_fieldF2;          // 0xF2
        unsigned char m_padF3[0xF5 - 0xF3];
        unsigned char m_mapTexLoaded;     // 0xF5
        unsigned char m_hasMapRef;        // 0xF6
        unsigned char m_fpBillboard;      // 0xF7
        unsigned char m_prio;             // 0xF8
        unsigned char m_padF9;            // 0xF9
        unsigned short m_prioTime;        // 0xFA
        unsigned char m_padFC[0x100 - 0xFC];
        int m_paramA;                     // 0x100
        unsigned int m_paramB;            // 0x104
        float m_cullRadiusSq;             // 0x108
        float m_cullRadius;               // 0x10C
        float m_cullYOffset;              // 0x110
        float m_sortDepth;                // 0x114
        unsigned short m_field118;        // 0x118
        short m_mapObjIndex;              // 0x11A
        PPPSEST m_soundEffectData;        // 0x11C
        PPPIFPARAM m_hitParams;           // 0x130
        int m_hitObjectIds[8];            // 0x138
    };

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    PppPdtSlot* slot = &m_pdtSlots[pdtSlotIndex];
    _pppDataHead* pdt = slot->m_pppDataHead;
    if (pdt == 0) {
        return -1;
    }

    unsigned char* fpData = reinterpret_cast<unsigned char*>(pdt) + 0x20 + fpNo * 0x60;

    PppMngStCreateRaw* mng;
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_baseTime == -0x1000) {
            mng = reinterpret_cast<PppMngStCreateRaw*>(self + 0x2A18 + i * 0x158);
            goto foundMng;
        }
    }
    mng = 0;
foundMng:
    if (mng == 0) {
        return -1;
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
        System.Printf(const_cast<char*>(sPppCreateLogFmt), pdtSlotIndex, fpNo,
                      mng - reinterpret_cast<PppMngStCreateRaw*>(self + 0x2A18),
                      slot->m_name);
    }

    unsigned char* fpData1 = fpData + 0x20;
    unsigned char* fpData2 = fpData + 0x40;

    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(mng) + 0x104) = -1;
    mng->m_prioTime = 0;
    mng->m_kind = static_cast<short>(pdtSlotIndex);
    mng->m_nodeIndex = static_cast<short>(fpNo);

    mng->m_hitParams.m_particleIndex = createParam->m_hitParamA;
    mng->m_hitParams.m_classId = createParam->m_hitParamB;
    mng->m_hitParams.m_hitObjectCount = createParam->m_hitObjectCount;
    mng->m_hitParams.m_hitFlags = createParam->m_hitFlags;
    *reinterpret_cast<PppHitIdBlock*>(mng->m_hitObjectIds) =
        *reinterpret_cast<const PppHitIdBlock*>(createParam->m_hitObjectIds);

    mng->m_mapTexLoaded = 0;
    mng->m_hasMapRef = 0;
    *reinterpret_cast<unsigned int*>(&mng->m_envColorR) = 0x1333;
    if (reinterpret_cast<unsigned char*>(&PartPcs)[0x2f] != 0 && pdtSlotIndex == 7 && fpNo == 0) {
        *reinterpret_cast<unsigned int*>(&mng->m_envColorR) = 0x1000;
    }

    mng->m_soundEffectData = createParam->m_soundEffectParams;
    mng->m_soundEffectData.m_soundEffectStartFrame <<= 0xC;

    mng->m_isFinished = 0;
    mng->m_hitBgFlag = 0;
    mng->m_stopRequested = 0;
    mng->m_slotVisible = 1;
    mng->m_ownerFacing = 1;

    const int initialTime = *reinterpret_cast<int*>(fpData1 + 0x0C);
    if (initialTime == -0x1000) {
        mng->m_baseTime = 0;
    } else {
        mng->m_baseTime = initialTime * 0x19 / 0x1E;
    }

    mng->m_pppResSet = slot;
    mng->m_partIndex = *reinterpret_cast<int*>(fpData1 + 0x10);
    mng->m_cullRadiusSq = *reinterpret_cast<float*>(fpData1 + 0x14);
    if (mng->m_cullRadiusSq > 0.0) {
        mng->m_cullRadiusSq *= mng->m_cullRadiusSq;
    }
    mng->m_cullRadius = *reinterpret_cast<float*>(fpData1 + 0x18);
    mng->m_cullYOffset = *reinterpret_cast<float*>(fpData1 + 0x1C);
    mng->m_pppPObjLinkHead.m_next = 0;
    mng->m_pppPDataVals = 0;

    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(mng) + 0xFC) =
        *reinterpret_cast<unsigned short*>(fpData2 + 0x0);
    mng->m_field118 = *reinterpret_cast<unsigned short*>(fpData2 + 0x2);
    mng->m_matrixMode = *reinterpret_cast<unsigned char*>(fpData2 + 0x5);
    mng->m_drawVariant = *reinterpret_cast<unsigned char*>(fpData2 + 0x6);
    mng->m_rotationOrder = *reinterpret_cast<unsigned char*>(fpData2 + 0x7);
    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(mng) + 0xED) =
        *reinterpret_cast<unsigned char*>(fpData2 + 0x4);
    mng->m_drawSubType = *reinterpret_cast<signed char*>(fpData2 + 0x0C);
    mng->m_ownerFlagsInitialized = *reinterpret_cast<unsigned char*>(fpData2 + 0x0D);
    mng->m_nodeScaleInitialized = *reinterpret_cast<unsigned char*>(fpData2 + 0x0E);
    mng->m_fieldF2 = 1;
    if (allowFpOverride != 0) {
        const int mode = *reinterpret_cast<unsigned char*>(fpData2 + 0x05);
        switch (mode) {
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        default:
            mng->m_fieldF2 = *reinterpret_cast<unsigned char*>(fpData2 + 0x0F);
            break;
        }
    }

    mng->m_fpBillboard = *reinterpret_cast<unsigned char*>(fpData2 + 0x0A);
    mng->m_prio = *reinterpret_cast<unsigned char*>(fpData2 + 0x0B);
    mng->m_mapObjIndex = *reinterpret_cast<short*>(fpData2 + 0x08);

    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(mng) + 0xE0) = 0;
    mng->m_objHitMask = createParam->m_objectHitMask;
    mng->m_cylinderAttribute = createParam->m_cylinderAttribute;
    mng->m_paramA = createParam->m_paramA;
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(mng) + 0x54) = createParam->m_paramC;
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(mng) + 0x64) = createParam->m_paramD;

    {
        unsigned char* mngBytes = reinterpret_cast<unsigned char*>(mng);
        if (createParam->m_positionOffsetPtr == 0) {
            mng->m_position.x = *reinterpret_cast<float*>(fpData + 0x00);
            mng->m_position.y = *reinterpret_cast<float*>(fpData + 0x04);
            mng->m_position.z = *reinterpret_cast<float*>(fpData + 0x08);
            *reinterpret_cast<float*>(mngBytes + 0x58) = mng->m_position.x;
            *reinterpret_cast<float*>(mngBytes + 0x5c) = mng->m_position.y;
            *reinterpret_cast<float*>(mngBytes + 0x60) = mng->m_position.z;
            *reinterpret_cast<float*>(mngBytes + 0x48) = *reinterpret_cast<float*>(mngBytes + 0x58);
            *reinterpret_cast<float*>(mngBytes + 0x4c) = *reinterpret_cast<float*>(mngBytes + 0x5c);
            *reinterpret_cast<float*>(mngBytes + 0x50) = *reinterpret_cast<float*>(mngBytes + 0x60);
        } else {
            mng->m_position.x = createParam->m_positionOffsetPtr->x + *reinterpret_cast<float*>(fpData + 0x00);
            mng->m_position.y = createParam->m_positionOffsetPtr->y + *reinterpret_cast<float*>(fpData + 0x04);
            mng->m_position.z = createParam->m_positionOffsetPtr->z + *reinterpret_cast<float*>(fpData + 0x08);
            *reinterpret_cast<float*>(mngBytes + 0x58) = mng->m_position.x;
            *reinterpret_cast<float*>(mngBytes + 0x5c) = mng->m_position.y;
            *reinterpret_cast<float*>(mngBytes + 0x60) = mng->m_position.z;
            *reinterpret_cast<float*>(mngBytes + 0x48) = *reinterpret_cast<float*>(mngBytes + 0x58);
            *reinterpret_cast<float*>(mngBytes + 0x4c) = *reinterpret_cast<float*>(mngBytes + 0x5c);
            *reinterpret_cast<float*>(mngBytes + 0x50) = *reinterpret_cast<float*>(mngBytes + 0x60);
        }
    }

    Vec* extraPos = createParam->m_extraPositionPtr;
    if (extraPos != 0) {
        mng->m_paramVec0.x = extraPos->x;
        mng->m_paramVec0.y = extraPos->y;
        mng->m_paramVec0.z = extraPos->z;
        mng->m_paramVec0.x = mng->m_paramVec0.x + *reinterpret_cast<float*>(fpData + 0x00);
        mng->m_paramVec0.y = mng->m_paramVec0.y + *reinterpret_cast<float*>(fpData + 0x04);
        mng->m_paramVec0.z = mng->m_paramVec0.z + *reinterpret_cast<float*>(fpData + 0x08);
    }

    if (createParam->m_rotationPtr == 0) {
        *reinterpret_cast<int*>(&mng->m_rotation.x) = *reinterpret_cast<int*>(fpData + 0x10);
        *reinterpret_cast<int*>(&mng->m_rotation.z) = *reinterpret_cast<int*>(fpData + 0x14);
        mng->m_rotationSpeed = *reinterpret_cast<int*>(fpData + 0x18);
    } else {
        unsigned char* mngB = reinterpret_cast<unsigned char*>(mng);
        *reinterpret_cast<int*>(mngB + 0x18) =
            static_cast<int>(32768.0f * createParam->m_rotationPtr->x / 180.0f);
        *reinterpret_cast<int*>(mngB + 0x1C) =
            static_cast<int>(32768.0f * createParam->m_rotationPtr->y / 180.0f);
        *reinterpret_cast<int*>(mngB + 0x20) =
            static_cast<int>(32768.0f * createParam->m_rotationPtr->z / 180.0f);
    }

    if (createParam->m_scalePtr == 0) {
        mng->m_scale.x = *reinterpret_cast<float*>(fpData1 + 0x00);
        mng->m_scale.y = *reinterpret_cast<float*>(fpData1 + 0x04);
        mng->m_scale.z = *reinterpret_cast<float*>(fpData1 + 0x08);
    } else {
        mng->m_scale.x = createParam->m_scalePtr->x * *reinterpret_cast<float*>(fpData1 + 0x00);
        mng->m_scale.y = createParam->m_scalePtr->y * *reinterpret_cast<float*>(fpData1 + 0x04);
        mng->m_scale.z = createParam->m_scalePtr->z * *reinterpret_cast<float*>(fpData1 + 0x08);
    }

    reinterpret_cast<_pppMngSt*>(mng)->m_lookTarget = createParam->m_lookTargetPtr;
    mng->m_ownerScale = kPartMngOne;
    mng->m_scaleFactor = kPartMngOne;
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(mng) + 0x3C) = kPartMngOne;
    *reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(mng) + 0x38) = kPartMngOne;
    mng->m_useOwnerScaleSign = 0;
    reinterpret_cast<_pppMngSt*>(mng)->m_owner = 0;

    const unsigned char mode = *reinterpret_cast<unsigned char*>(fpData2 + 0x05);
    switch (mode) {
    case 2:
    case 4:
        mng->m_mapObjIndex = static_cast<short>(MapMng.GetMapObjEffectIdx(*reinterpret_cast<short*>(fpData2 + 0x08)));
        break;
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
        mng->m_ownerFacing = 0;
        {
#define owner (reinterpret_cast<CGObject*>(createParam->m_paramB))
            reinterpret_cast<_pppMngSt*>(mng)->m_owner = owner;
            reinterpret_cast<_pppMngSt*>(mng)->m_lookTarget = createParam->m_lookTargetPtr;
            if (owner != 0) {
                int node = owner->m_charaModelHandle->m_model->SearchNodeSk(reinterpret_cast<char*>(fpData2 + 0x10));
                if (node >= 0) {
                    *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(mng) + 0xE0) =
                        *reinterpret_cast<int*>(
                            reinterpret_cast<unsigned char*>(owner->m_charaModelHandle->m_model) + 0xA8) +
                        node * 0xC0;
                }
            }
#undef owner
        }
        break;
    }

    return mng - reinterpret_cast<PppMngStCreateRaw*>(self + 0x2A18);
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
    if (PartPcs.m_usbStreamState.m_disableShokiDraw != 0) {
        return -1;
    }
    return pppCreate0(pdtSlotIndex, fpNo, createParam, allowFpOverride);
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
int CPartMng::pppGetFreeSlot()
{
    int slot = m_pppEnvSt.m_mngStCount;
    int nextSlot = slot + 1;
    m_pppEnvSt.m_mngStCount = nextSlot;

    if (nextSlot >= 0x7fffffff) {
        m_pppEnvSt.m_mngStCount = 0x10;
    }

    return slot;
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
    char* base = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + 0x2A18);
        int baseTime = pppMngSt->m_baseTime;
        if (baseTime != -0x1000 && pppMngSt->m_paramA == slot) {
            if (checkHitFlags == 0 || (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0x137) & 1) == 0) {
                if (baseTime < 0) {
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE8) = 1;
                    pppStopSe(pppMngSt, &pppMngSt->m_soundEffectData);
                } else {
                    pppMngSt->m_baseTime = -0x1000;
                }
            }
        }
        base += 0x158;
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
    char* base = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + 0x2A18);
        if (pppMngSt->m_baseTime != -0x1000
            && pppMngSt->m_paramA == slot) {
            if (checkHitFlags == 0 || (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0x137) & 1) == 0) {
                *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE5) = 1;
                pppStopSe(pppMngSt, &pppMngSt->m_soundEffectData);
            }
        }
        base += 0x158;
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
        if (*reinterpret_cast<int*>(pppMngSt + 0x2A2C) != -0x1000
            && *reinterpret_cast<int*>(pppMngSt + 0x2B18) == slot) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0x2B01) = isVisible;
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057E94
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDeletePart(int index)
{
    struct PppMngLifecycleState {
        void* m_pppResSet;                   // 0x00
        unsigned char m_pad04[0x14 - 0x4];
        int m_baseTime;                      // 0x14
        unsigned char m_pad18[0xE8 - 0x18];
        unsigned char m_deleteRequested;     // 0xE8
        unsigned char m_padE9[0x11C - 0xE9];
        PPPSEST m_soundEffectData;           // 0x11C
    };

    PppMngLifecycleState* mng = reinterpret_cast<PppMngLifecycleState*>(
        reinterpret_cast<unsigned char*>(this) + 0x2A18 + index * 0x158);
    int baseTime = mng->m_baseTime;

    if (baseTime < 0) {
        mng->m_deleteRequested = 1;
        pppStopSe(reinterpret_cast<_pppMngSt*>(mng), &mng->m_soundEffectData);
    } else {
        mng->m_baseTime = -0x1000;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndPart(int index)
{
    struct PppMngLifecycleState {
        unsigned char m_pad00[0xE5];
        unsigned char m_stopRequested;       // 0xE5
        unsigned char m_padE6[0x11C - 0xE6];
        PPPSEST m_soundEffectData;           // 0x11C
    };

    PppMngLifecycleState* mng = reinterpret_cast<PppMngLifecycleState*>(
        reinterpret_cast<unsigned char*>(this) + 0x2A18 + index * 0x158);

    mng->m_stopRequested = 1;
    pppStopSe(reinterpret_cast<_pppMngSt*>(mng), &mng->m_soundEffectData);
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
    int offset = index * 0x158;
    return reinterpret_cast<PPPIFPARAM*>(reinterpret_cast<char*>(this) + offset + 0x2B48);
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
	reinterpret_cast<unsigned char*>(this)[(index * 0x158) + 0x2b01] = visible;
}

/*
 * --INFO--
 * PAL Address: 0x80057D6C
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppFieldShowFpNo(short fieldNo, unsigned char visible)
{
    CPartMng* partMng = this;
    int fieldNoInt = fieldNo;

    int i;
    for (i = 0; i < 0x120; i += 3) {
        if ((partMng->m_pppMng[0].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[0].m_kind == 0) &&
            (partMng->m_pppMng[0].m_nodeIndex == fieldNoInt)) {
            partMng->m_pppMng[0].m_slotVisible = visible;
        }
        if ((partMng->m_pppMng[1].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[1].m_kind == 0) &&
            (partMng->m_pppMng[1].m_nodeIndex == fieldNoInt)) {
            partMng->m_pppMng[1].m_slotVisible = visible;
        }
        if ((partMng->m_pppMng[2].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[2].m_kind == 0) &&
            (partMng->m_pppMng[2].m_nodeIndex == fieldNoInt)) {
            partMng->m_pppMng[2].m_slotVisible = visible;
        }
        if ((partMng->m_pppMng[3].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[3].m_kind == 0) &&
            (partMng->m_pppMng[3].m_nodeIndex == fieldNoInt)) {
            partMng->m_pppMng[3].m_slotVisible = visible;
        }

        partMng = reinterpret_cast<CPartMng*>(reinterpret_cast<char*>(partMng) + 0x560);
    }
    if (i < 0x120) {
        return;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppFieldEndFpNo(short fieldNo)
{
    char* base = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + 0x2A18);
        int baseTime = pppMngSt->m_baseTime;
        if ((baseTime != -0x1000) && (pppMngSt->m_kind == 0) && (pppMngSt->m_nodeIndex == fieldNo)) {
            if (baseTime < 0) {
                pppMngSt->m_particleEnded = 1;
                pppStopSe(pppMngSt, &pppMngSt->m_soundEffectData);
            } else {
                pppMngSt->m_baseTime = -0x1000;
            }
        }
        base += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetDeltaIdx(short index, long color)
{
    char* delta = reinterpret_cast<char*>(this);
    delta += index * 0x158;
    *reinterpret_cast<long*>(delta + 0x2ac0) = color;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetDeltaSlot(int slot, long color)
{
    CPartMng* partMng = this;

    int i;
    for (i = 0; i < 0x140; i += 5) {
        if ((partMng->m_pppMng[0].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[0].m_paramA == slot)) {
            *reinterpret_cast<long*>(&partMng->m_pppMng[0].m_envColorR) = color;
        }
        if ((partMng->m_pppMng[1].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[1].m_paramA == slot)) {
            *reinterpret_cast<long*>(&partMng->m_pppMng[1].m_envColorR) = color;
        }
        if ((partMng->m_pppMng[2].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[2].m_paramA == slot)) {
            *reinterpret_cast<long*>(&partMng->m_pppMng[2].m_envColorR) = color;
        }
        if ((partMng->m_pppMng[3].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[3].m_paramA == slot)) {
            *reinterpret_cast<long*>(&partMng->m_pppMng[3].m_envColorR) = color;
        }
        if ((partMng->m_pppMng[4].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[4].m_paramA == slot)) {
            *reinterpret_cast<long*>(&partMng->m_pppMng[4].m_envColorR) = color;
        }
        if ((partMng->m_pppMng[5].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[5].m_paramA == slot)) {
            *reinterpret_cast<long*>(&partMng->m_pppMng[5].m_envColorR) = color;
        }

        partMng = reinterpret_cast<CPartMng*>(reinterpret_cast<char*>(partMng) + 0x810);
    }
    if (i < 0x140) {
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057B2C
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppSetLocSlot(int slot, Vec* position)
{
    CPartMng* partMng = this;

    int i;
    for (i = 0; i < 0x120; i += 3) {
        if ((partMng->m_pppMng[0].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[0].m_paramA == slot)) {
            partMng->m_pppMng[0].m_position.x = position->x;
            partMng->m_pppMng[0].m_position.y = position->y;
            partMng->m_pppMng[0].m_position.z = position->z;
        }
        if ((partMng->m_pppMng[1].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[1].m_paramA == slot)) {
            partMng->m_pppMng[1].m_position.x = position->x;
            partMng->m_pppMng[1].m_position.y = position->y;
            partMng->m_pppMng[1].m_position.z = position->z;
        }
        if ((partMng->m_pppMng[2].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[2].m_paramA == slot)) {
            partMng->m_pppMng[2].m_position.x = position->x;
            partMng->m_pppMng[2].m_position.y = position->y;
            partMng->m_pppMng[2].m_position.z = position->z;
        }
        if ((partMng->m_pppMng[3].m_baseTime != -0x1000) &&
            (partMng->m_pppMng[3].m_paramA == slot)) {
            partMng->m_pppMng[3].m_position.x = position->x;
            partMng->m_pppMng[3].m_position.y = position->y;
            partMng->m_pppMng[3].m_position.z = position->z;
        }

        partMng = reinterpret_cast<CPartMng*>(reinterpret_cast<char*>(partMng) + 0x560);
    }
    if (i < 0x120) {
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057a6c
 * PAL Size: 192b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDeleteCHandle(CCharaPcs::CHandle* handle)
{
    char* base = reinterpret_cast<char*>(this);
    unsigned char mode;
    int baseTime;

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + 0x2A18);
        baseTime = pppMngSt->m_baseTime;
        if (baseTime != -0x1000) {
            mode = *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE7);
            if (mode == 3 || static_cast<unsigned char>(mode - 5) <= 2 || mode == 8) {
                void* owner = pppMngSt->m_owner;
                if (owner != 0 &&
                    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<char*>(owner) + 0xf8) == handle) {
                    if (baseTime < 0) {
                        *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE8) = 1;
                        pppStopSe(
                            pppMngSt,
                            &pppMngSt->m_soundEffectData);
                    } else {
                        pppMngSt->m_baseTime = -0x1000;
                    }
                }
            }
        }
        base += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndCHandle(CCharaPcs::CHandle* handle)
{
    char* base = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + 0x2A18);
        if (pppMngSt->m_baseTime != -0x1000) {
            unsigned char mode = *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE7);
            if (mode == 3 || static_cast<unsigned char>(mode - 5) <= 2 || mode == 8) {
                void* owner = pppMngSt->m_owner;
                if (owner != 0 &&
                    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<char*>(owner) + 0xf8) == handle) {
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE5) = 1;
                    pppStopSe(
                        pppMngSt,
                        &pppMngSt->m_soundEffectData);
                }
            }
        }
        base += 0x158;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800578b0
 * PAL Size: 272b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppIsDeadCHandle(CCharaPcs::CHandle* handle)
{
    unsigned char mode;
    void* owner;
    int mngIndex = 0;

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = &m_pppMng[mngIndex];
        if (m_pppMng[mngIndex].m_baseTime != -0x1000) {
            mode = m_pppMng[mngIndex].m_matrixMode;
            if (mode == 3 || static_cast<unsigned char>(mode - 5) <= 2 || mode == 8) {
                owner = pppMngSt->m_owner;
                if (owner != 0 &&
                    *reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<char*>(owner) + 0xf8) == handle) {
                    return 0;
                }
            }
        }
        mngIndex++;
    }
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeleteAll()
{
    char* base = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(base + 0x2A18);
        int baseTime = pppMngSt->m_baseTime;
        if (baseTime != -0x1000) {
            if (baseTime < 0) {
                *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0xE8) = 1;
                pppStopSe(
                    pppMngSt,
                    &pppMngSt->m_soundEffectData);
            } else {
                pppMngSt->m_baseTime = -0x1000;
            }
        }
        base += 0x158;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057794
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDestroyAll()
{
    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x116f);

    int mngIndex = 0;
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = &m_pppMng[mngIndex];
        if (pppMngSt->m_baseTime != -0x1000 && pppMngSt->m_pppResSet != 0) {
            _pppAllFreePObject(pppMngSt);
        }
        mngIndex++;
    }

    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x117b);
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
_pppMngSt::_pppMngSt()
{
    char* base = reinterpret_cast<char*>(this);
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
