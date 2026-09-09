#include "global.h"
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

STATIC_ASSERT(sizeof(CParModelSet) == 0x6C00);
STATIC_ASSERT(sizeof(CParShapeSet) == 0x2C00);
STATIC_ASSERT(sizeof(pppIVECTOR3) == 0xC);
STATIC_ASSERT(sizeof(pppIVECTOR4) == 0x10);
STATIC_ASSERT(offsetof(pppIVECTOR4, y) == 4);
STATIC_ASSERT(offsetof(pppIVECTOR4, z) == 8);
STATIC_ASSERT(offsetof(_pppMngSt, m_rotation) == 0x18);
STATIC_ASSERT(offsetof(_pppMngSt, m_lifeEnd) == 0x24);
STATIC_ASSERT(offsetof(_pppMngSt, m_scale) == 0x28);
STATIC_ASSERT(offsetof(_pppMngSt, m_matrix) == 0x78);
STATIC_ASSERT(sizeof(_pppMngSt) == 0x158);
STATIC_ASSERT(offsetof(_pppFieldParticleData, m_autoCreateMarker) == 0x2C);
STATIC_ASSERT(offsetof(_pppFieldParticleData, m_matrixMode) == 0x45);
STATIC_ASSERT(offsetof(_pppFieldParticleData, m_nodeName) == 0x50);
STATIC_ASSERT(offsetof(_pppMngSt, m_deltaTime) == 0xA8);
STATIC_ASSERT(offsetof(_pppMngSt, m_userPosition) == 0x48);
STATIC_ASSERT(offsetof(_pppMngSt, m_movementScale) == 0x54);
STATIC_ASSERT(offsetof(_pppMngSt, m_basePosition) == 0x58);
STATIC_ASSERT(offsetof(_pppMngSt, m_hitScale) == 0x64);

STATIC_ASSERT(sizeof(pppCacheChunk) == 0x8);
STATIC_ASSERT(offsetof(pppCacheChunk, m_pdt) == 0x4);
STATIC_ASSERT(sizeof(_pppEnvSt) == 0x14);
STATIC_ASSERT(sizeof(CPartMng::PppPdtSlot) == 0x38);
STATIC_ASSERT(offsetof(CPartMng::PppPdtSlot, m_env) == 0x4);
STATIC_ASSERT(offsetof(CPartMng::PppPdtSlot, m_name) == 0x18);
STATIC_ASSERT(sizeof(CPartMng) == 0x23FD8);
STATIC_ASSERT(offsetof(CPartMng, m_mngStCount) == 0x23550);
STATIC_ASSERT(offsetof(CPartMng, m_soundNearDistance) == 0x23568);
STATIC_ASSERT(offsetof(CPartMng, m_soundFarDistance) == 0x23588);
STATIC_ASSERT(offsetof(CPartMng, m_editParticleCount) == 0x4);
STATIC_ASSERT(offsetof(CPartMng, m_editReceiveCursor) == 0x1CC);
STATIC_ASSERT(offsetof(CPartMng, m_editShapeGroups) == 0x7FC);
STATIC_ASSERT(offsetof(CPartMng, m_cursorRequest) == 0x10);
STATIC_ASSERT(offsetof(CPartMng, m_editorCursorPosition) == 0x18);
STATIC_ASSERT(offsetof(CPartMng, m_editorCursorX) == 0x28);
STATIC_ASSERT(offsetof(CPartMng, m_editDataBuffers) == 0x1D4);
STATIC_ASSERT(offsetof(CPartMng, m_editTextBuffers) == 0x3D8);
STATIC_ASSERT(offsetof(CPartMng, m_editProgramData) == 0x5DC);
STATIC_ASSERT(offsetof(CPartMng, m_materialSet) == 0x7E4);
STATIC_ASSERT(offsetof(CPartMng, m_editorObject) == 0x80C);
STATIC_ASSERT(offsetof(CPartMng, m_pppMng) == 0x2A18);
STATIC_ASSERT(offsetof(CPartMng, m_pdtSlots) == 0x22E18);

extern "C" {
extern Mtx ppvCameraMatrix;
extern float ppvChrScl[3];
extern Mtx ppvUnitMatrix;
extern Vec ppvZeroVector;
}
extern char g_StrTmp[0x400];

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
static inline float LoadFloat(const float& value) { return value; }
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
static const char sPartMngDumpVectorFmt[] = "%s=(%f %f %f)\n";
static const char sPartMngDumpMatrixFmt[] =
    "%s=\n{ %f %f %f %f }\n{ %f %f %f %f }\n{ %f %f %f %f }\n\n";
static const char sPartMngDumpSeparator[] =
    "=====================================================\n"
    "=====================================================\n"
    "                      pppDumpMngSt\n"
    "=====================================================\n"
    "=====================================================\n";
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
void CPtrArray<CTexture*>::SetGrow(int growCapacity)
{
    m_growCapacity = growCapacity;
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
 * EN Address: 0x8006DCF8
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
inline pppShapeSt::~pppShapeSt()
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
 * EN Address: 0x8006E02C
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
inline pppModelSt::pppModelSt()
{
    m_refCount = 0;
    m_isUsed = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800595C8
 * PAL Size: 84b
 * EN Address: 0x8006DEAC
 * EN Size: 88b
 * JP Address: TODO
 * JP Size: TODO
 */
inline pppModelSt::~pppModelSt()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CPartMng::CPartMng()
{
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
    C_MTXPerspective(ppvScreenMatrix, kPartMngScreenFovY, kPartMngScreenAspect, kPartMngScreenNear, kPartMngPppFar);
    PSMTX44Copy(ppvScreenMatrix, ppvScreenMatrix0);

    memset(m_unk235A8, 0, 0x108);

    m_editorFlags[2] = 0;
    m_editorFlags[1] = 0;
    m_editorFlags[0] = 0;

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
    m_modelSet = 0;
    m_shapeSet = 0;

    for (int i = 0; i < 0x80; i++) {
        m_editDataBuffers[i] = 0;
    }
    for (int i = 0; i < 0x80; i++) {
        m_editTextBuffers[i] = 0;
    }
    for (int i = 0; i < 0x80; i++) {
        m_editProgramData[i] = 0;
    }

    for (int i = 0; i < 0x180; i++) {
        m_pppMng[i].m_baseTime = -0x1000;
        m_pppMng[i].m_soundEffectData.m_soundEffectHandle = -1;
        m_pppMng[i].m_soundEffectData.m_soundEffectSlot = -1;
        m_pppMng[i].m_soundEffectData.m_soundEffectStopFlag = 0;
        m_pppMng[i].m_soundEffectData.m_soundEffectKind = 1;
        m_pppMng[i].m_soundEffectData.m_soundEffectStartFrame = 0;
        m_pppMng[i].m_soundEffectData.m_soundEffectStartedOnce = 0;
        m_pppMng[i].m_soundEffectData.m_soundEffectFadeFrames = 30;
    }

    for (int i = 0; i < 0x20; i++) {
        m_pdtSlots[i].m_pppDataHead = 0;
    }

    m_editNodeNameBuffer = 0;
    m_editModelSlots = 0;
    m_editShapeSlots = 0;
    m_editShapeGroups = 0;

    m_envParam = kPartMngZero;
    m_mngStCount = 0x10;
    m_isEditMode = 1;

    m_editorObject = 0;

    memset(m_unk235A8, 0, 0x108);

    m_soundNearDistance[0] = kPartMngEnvBoxMinX;
    m_soundFarDistance[0] = kPartMngEnvBoxMaxXz;
    m_soundNearDistance[1] = kPartMngEnvBoxMinY;
    m_soundFarDistance[1] = kPartMngEnvBoxMaxY;
    m_soundNearDistance[2] = kPartMngEnvBoxMaxXz;
    m_soundFarDistance[2] = kPartMngEnvBoxMaxZ;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006DF04
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void pppModelSt::Release()
{
    if (--m_refCount <= 0) {
        if (m_cacheId != -1) {
            ppvAmemCacheSet.DestroyCache(m_cacheId);
            m_meshData = 0;
            m_displayListData = 0;
        }
        Destroy();
        m_refCount = 0;
        m_isUsed = 0;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006DD7C
 * EN Size: 136b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void pppShapeSt::Release()
{
    if (--m_refCount <= 0) {
        if (m_animData != 0) {
            delete reinterpret_cast<u8*>(m_animData);
            m_animData = 0;
        }
        if (m_displayListData != 0) {
            delete reinterpret_cast<u8*>(m_displayListData);
            m_displayListData = 0;
        }
        m_refCount = 0;
        m_inUse = 0;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006E240
 * EN Size: 128b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CParModelSet::CParModelSet()
{
    for (int i = 0; i < 0x100; i++) {
        m_models[i].m_isUsed = 0;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006DE04
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CParModelSet::~CParModelSet()
{
    for (unsigned int i = 0; i < 0x100; i++) {
        pppModelSt* model = &m_models[i];
        if (model->m_isUsed != 0) {
            model->Release();
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006E37C
 * EN Size: 128b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CParShapeSet::CParShapeSet()
{
    for (int i = 0; i < 0x100; i++) {
        m_shapes[i].m_inUse = 0;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006DC50
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CParShapeSet::~CParShapeSet()
{
    for (unsigned int i = 0; i < 0x100; i++) {
        pppShapeSt* shape = &m_shapes[i];
        if (shape->m_inUse != 0) {
            shape->Release();
        }
    }
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
    for (int i = 0; i < 0x20; i++) {
        pppReleasePdt(i);
    }

    if (m_modelSet != 0) {
        delete m_modelSet;
        m_modelSet = 0;
    }

    if (m_shapeSet != 0) {
        delete m_shapeSet;
        m_shapeSet = 0;
    }

    if (m_textureSet != 0) {
        CTextureSet* textureSet = m_textureSet;
        if (textureSet->DecRef() == 0) {
            delete textureSet;
        }
        m_textureSet = 0;
    }

    if (m_materialSet != 0) {
        CMaterialSet* materialSet = m_materialSet;
        if (materialSet->DecRef() == 0) {
            delete materialSet;
        }
        m_materialSet = 0;
    }

    if (m_editorObject != 0) {
        CCharaPcs::CHandle* handle = m_editorObject->m_charaModelHandle;
        if (handle != 0) {
            delete handle;
            m_editorObject->m_charaModelHandle = 0;
        }
        if (m_editorObject != 0) {
            operator delete(m_editorObject);
            m_editorObject = 0;
        }
    }

    pppDestroyHeap(&m_pppEnvSt);
}

/*
 * --INFO--
 * PAL Address: 0x8005ECFC
 * PAL Size: 384b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDumpMngSt()
{
    unsigned long heapTotal;
    unsigned long heapUse;
    unsigned long heapFree;

    if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
        System.Printf(const_cast<char*>(sPartMngDumpSeparator));
    }

    _pppMngSt* mngBase = PartMng.m_pppMng;
    int kind;
    int i = 0;
    _pppMngSt* mng;
    do {
        mng = &m_pppMng[i];
        if (mng->m_baseTime != -0x1000 && static_cast<unsigned int>(System.m_execParam) >= 1U) {
            kind = static_cast<int>(mng->m_kind);
            int heapGroup = mng - mngBase;
            int heapSize = ppvEnv->m_stagePtr->heapWalker(0, 0, static_cast<unsigned long>(heapGroup));

            System.Printf(
                const_cast<char*>(sPartMngDumpEntryFmt), mng->m_prioTime,
                mng->m_prio, heapSize, kind, static_cast<int>(mng->m_nodeIndex), heapGroup,
                m_pdtSlots[kind].m_name);
        }

        i++;
    } while (i < 0x180);

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
 * PAL Address: TODO
 * PAL Size: 180b
 * EN Address: 0x80066A58
 * EN Size: 196b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::pppReleasePmng(int pdtSlotIndex)
{
    PppPdtSlot* pdtSlot = &m_pdtSlots[pdtSlotIndex];
    ppvEnv = &pdtSlot->m_env;
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_pppResSet == pdtSlot) {
            _pppAllFreePObject(&m_pppMng[i]);
        }
    }
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
    PppPdtSlot* pdtSlot = m_pdtSlots + pdtSlotIndex;
    _pppDataHead* pdt = pdtSlot->m_pppDataHead;

    if (pdt == 0) {
        return;
    }

    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x158);
    m_materialSet->ReleaseTag(m_textureSet, pdtSlotIndex, &ppvAmemCacheSet);
    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x13a);

    pppReleasePmng(pdtSlotIndex);

    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x149);

    pdt = pdtSlot->m_pppDataHead;
    if (pdt != 0) {
        for (int i = 0; i < pdt->m_modelCount; i++) {
            pppModelSt* model = reinterpret_cast<pppModelSt**>(pdt->m_modelNames)[i];
            model->Release();
        }

        if (reinterpret_cast<pppModelSt**>(pdt->m_modelNames) != 0) {
            delete[] reinterpret_cast<pppModelSt**>(pdt->m_modelNames);
            pdt->m_modelNames = 0;
        }

        for (int i = 0; i < pdt->m_shapeCount; i++) {
            pppShapeSt* shape = reinterpret_cast<pppShapeSt**>(pdt->m_shapeNames)[i];
            shape->Release();
        }

        if (reinterpret_cast<pppShapeSt**>(pdt->m_shapeNames) != 0) {
            delete[] reinterpret_cast<pppShapeSt**>(pdt->m_shapeNames);
            pdt->m_shapeNames = 0;
        }

        for (int i = 0; i < pdt->m_shapeGroupCount; i++) {
            pppShapeGroupRaw* shapeGroup = &reinterpret_cast<pppShapeGroupRaw*>(pdt->m_shapeGroups)[i];
            if (shapeGroup->m_shapeList != 0) {
                delete shapeGroup->m_shapeList;
                shapeGroup->m_shapeList = 0;
            }
        }

        if (reinterpret_cast<pppShapeGroupRaw*>(pdt->m_shapeGroups) != 0) {
            delete[] reinterpret_cast<pppShapeGroupRaw*>(pdt->m_shapeGroups);
            pdt->m_shapeGroups = 0;
        }

        for (int i = 0; i < pdt->m_cacheChunkCount; i++) {
            ppvAmemCacheSet.DestroyCache(reinterpret_cast<pppCacheChunk*>(pdt->m_cacheChunks)[i].m_cacheIndex);
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
inline _pppMngSt* CPartMng::pppGetFreePppMngSt()
{
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_baseTime == -0x1000) {
            return &m_pppMng[i];
        }
    }
    return 0;
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
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_baseTime == -0x1000) {
            freeCount++;
        }
    }
    return freeCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CPartMng::PppPdtSlot* CPartMng::pppGetFreePppDataMngSt()
{
    for (int i = 8; i < 0x20; i++) {
        if (m_pdtSlots[i].m_pppDataHead == 0) {
            return &m_pdtSlots[i];
        }
    }
    return 0;
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
    if (m_editorCursorX == 0x7fff) {
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
    int cursorX = m_editorCursorX;
    int cursorY = m_editorCursorY;
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

    float x = m_editorCursorPosition.x;
    float y = m_editorCursorPosition.y;
    float z = m_editorCursorPosition.z;

    _GXColor color;
    color.r = 0xff;
    color.g = 0x80;
    color.b = 0x80;
    color.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x - LoadFloat(kPartMngCullRadius), y, z);
    GXPosition3f32(x + LoadFloat(kPartMngCullRadius), y, z);

    color.r = 0x80;
    color.g = 0xff;
    color.b = 0x80;
    color.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x, y - LoadFloat(kPartMngCullRadius), z);
    GXPosition3f32(x, y + LoadFloat(kPartMngCullRadius), z);

    color.r = 0xff;
    color.g = 0xff;
    color.b = 0x80;
    color.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, color);
    GXSetChanMatColor((GXChannelID)4, color);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x, y, z - LoadFloat(kPartMngCullRadius));
    GXPosition3f32(x, y, z + LoadFloat(kPartMngCullRadius));
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 152b
 * EN Address: 0x80067344
 * EN Size: 192b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void Screen2world(Vec& screenPos, Vec& worldPos)
{
    Mtx invCamera;
    Vec viewPos;
    float viewZ = ppvScreenMatrix0[2][3] / (screenPos.z + ppvScreenMatrix0[2][2]);
    viewPos.x = viewZ * (screenPos.x / ppvScreenMatrix0[0][0]);
    viewPos.y = viewZ * (screenPos.y / ppvScreenMatrix0[1][1]);
    viewPos.z = -viewZ;
    PSMTXInverse(ppvCameraMatrix0, invCamera);
    PSMTXMultVec(invCamera, &viewPos, &worldPos);
}

/*
 * --INFO--
 * PAL Address: 0x8005DEE8
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppGet2Dpos()
{
    u32 zAtPixel;
    Vec worldPos;
    Vec screenPos;

    if (m_cursorRequest != 0) {
        int x = m_editorCursorX + 0x140;
        int y = m_editorCursorY + 0xE0;
        if ((x >= 0) && (x < 0x27E) && (y >= 0) && (y < 0x1BE)) {
            Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x2A2);
            GXPeekZ(static_cast<u16>(x & 0xFFFF), static_cast<u16>(y & 0xFFFF), &zAtPixel);

            screenPos.x = (float)m_editorCursorX / kPartMngScreenHalfWidth;
            screenPos.y = -(float)m_editorCursorY / kPartMngScreenHalfHeight;
            screenPos.z = (float)((int)zAtPixel - 0xFFFFFF) / kPartMngDepthUnit;
            Screen2world(screenPos, worldPos);
            USBPcs.SendDataCode(0x60, &worldPos, 1, 0xC);
        }
        m_cursorRequest = 0;
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
    gPppHeapUseRateWords[0] = pppHeapUseRate(ppvEnv->m_stagePtr);
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
 * PAL Address: TODO
 * PAL Size: 164b
 * EN Address: 0x80067628
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::allFreeFPrim()
{
    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3A9);
    for (int i = 0; i < m_editParticleCount; i++) {
        if (m_pppMng[i].m_baseTime != -0x1000) {
            _pppAllFreePObject(&m_pppMng[i]);
        }
    }
    m_editParticleCount = 0;
    Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x3B3);
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
    int i;
    for (i = 0; i < m_editParticleCount; i++) {
        _pppFieldParticleData* fp = &reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer)[i];
        m_pppMng[i].m_pppResSet = m_unk23518;

        if (m_pppMng[i].m_baseTime < 0) {
            m_pppMng[i].m_baseTime = fp->m_autoCreateMarker;
        } else {
            m_pppMng[i].m_baseTime = fp->m_autoCreateMarker * 0x19 / 0x1E;
        }

        m_pppMng[i].m_cullRadiusSq = fp->m_cullDistance;
        if (m_pppMng[i].m_cullRadiusSq > 0.0) {
            m_pppMng[i].m_cullRadiusSq *= m_pppMng[i].m_cullRadiusSq;
        }
        m_pppMng[i].m_nodeIndex = static_cast<short>(i);
        m_pppMng[i].m_cullRadius = fp->m_cullRadius;
        m_pppMng[i].m_cullYOffset = fp->m_cullYOffset;
        m_pppMng[i].m_position.x = fp->m_position.x;
        m_pppMng[i].m_position.y = fp->m_position.y;
        m_pppMng[i].m_position.z = fp->m_position.z;
        m_pppMng[i].m_rotation.x = fp->m_rotation.x;
        m_pppMng[i].m_rotation.y = fp->m_rotation.y;
        m_pppMng[i].m_rotation.z = fp->m_rotation.z;
        m_pppMng[i].m_scale.x = fp->m_scale.x;
        m_pppMng[i].m_scale.y = fp->m_scale.y;
        m_pppMng[i].m_scale.z = fp->m_scale.z;
        m_pppMng[i].m_ownerScale = kPartMngOne;
        m_pppMng[i].m_scaleFactor = kPartMngOne;
        m_pppMng[i].m_userFloat1 = kPartMngOne;
        m_pppMng[i].m_userFloat0 = kPartMngOne;
        m_pppMng[i].m_useOwnerScaleSign = 0;
        m_pppMng[i].m_matrixMode = fp->m_matrixMode;
        m_pppMng[i].m_drawVariant = fp->m_drawVariant;
        m_pppMng[i].m_rotationOrder = fp->m_rotationOrder;
        m_pppMng[i].m_drawPass = fp->m_drawPass;
        m_pppMng[i].m_drawSubType = fp->m_drawSubType;
        m_pppMng[i].m_ownerFlagsInitialized = fp->m_ownerFlagsInitialized;
        m_pppMng[i].m_nodeScaleInitialized = fp->m_nodeScaleInitialized;
        m_pppMng[i].m_fieldF2 = 1;
        m_pppMng[i].m_fpBillboard = fp->m_fpBillboard;
        m_pppMng[i].m_prio = fp->m_prio;
        m_pppMng[i].m_mapObjIndex = fp->m_mapObjIndex;
        m_pppMng[i].m_bindNode = 0;
        m_pppMng[i].m_objHitMask = 0xFFFFFFFF;
        m_pppMng[i].m_cylinderAttribute = 0xFFFFFFFF;
        m_pppMng[i].m_paramA = 0;
        m_pppMng[i].m_hitBgFlag = 0;
        m_pppMng[i].m_slotVisible = 1;
        m_pppMng[i].m_ownerFacing = 1;
        m_pppMng[i].m_owner = 0;

        unsigned char mode = m_pppMng[i].m_matrixMode;
        switch (mode) {
        case 2:
        case 4:
            m_pppMng[i].m_mapObjIndex = static_cast<short>(MapMng.GetMapObjEffectIdx(fp->m_mapObjIndex));
            break;
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
            m_pppMng[i].m_ownerFacing = 0;
            m_pppMng[i].m_owner = m_editorObject;
            m_pppMng[i].m_lookTarget = m_editorObject;
            if (m_editorObject != 0) {
                int node = m_editorObject->m_charaModelHandle->m_model->SearchNodeSk(fp->m_nodeName);
                if (node >= 0) {
                    m_pppMng[i].m_bindNode = &m_editorObject->m_charaModelHandle->m_model->m_nodes[node];
                }
            }
            break;
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 64b
 * EN Address: 0x80067904
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::fpIDon(unsigned short selectedId)
{
    _pppMngSt* mng = m_pppMng;
    _pppFieldParticleData* fp = reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer);
    for (int i = m_editParticleCount; i != 0; i--) {
        if (fp->m_fieldId == selectedId) {
            mng->m_baseTime = 0;
        }
        fp++;
        mng++;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 64b
 * EN Address: 0x80067968
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::fpIDoff(unsigned short selectedId)
{
    _pppMngSt* mng = m_pppMng;
    _pppFieldParticleData* fp = reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer);
    for (int i = m_editParticleCount; i != 0; i--) {
        if (fp->m_fieldId == selectedId) {
            mng->m_particleEnded = 1;
        }
        fp++;
        mng++;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 376b
 * EN Address: 0x800679CC
 * EN Size: 344b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::InitMaterialSet()
{
    if (m_textureSet == 0) {
        m_textureSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x447) CTextureSet;
        CTextureSet* textureSet = m_textureSet;
        textureSet->m_textureArray.SetDefaultSize(0x180);
        textureSet->m_textureArray.SetGrow(0);
    }

    if (m_materialSet == 0) {
        m_materialSet = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x44B) CMaterialSet;
        CMaterialSet* materialSet = m_materialSet;
        materialSet->m_materials.SetDefaultSize(0x180);
        materialSet->m_materials.SetGrow(0);
        m_pppEnvSt.m_materialSetPtr = m_materialSet;

        CMaterial* defaultMaterial = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x44E) CMaterial;
        defaultMaterial->Create(0, static_cast<CMaterialMan::TEV_BIT>(0xFFF531F0));
        defaultMaterial->SetTevBit(static_cast<CMaterialMan::TEV_BIT>(1));
        m_materialSet->AddMaterial(defaultMaterial, 0);
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 456b
 * EN Address: 0x80067B24
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::ReadTex(CChunkFile& chunkFile)
{
    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 'TXID':
            InitMaterialSet();
            m_textureSet->Create(chunkFile, PartPcs.m_usbStreamState.m_stageLoad, 1, 0, 0, 0);
            m_materialSet->SetPartFromTextureSet(m_textureSet, 0);
            m_materialSet->SetTextureSet(m_textureSet);
            break;
        }
    }
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
    char* textureNames[0x100];
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
	char* textureNames[0x100];
	char** textureNameIt = textureNames;
	CChunkFile::CChunk chunk;

	while (chunkFile.GetNextChunk(chunk))
	{
		chunkFile.PushChunk();
		switch (chunk.m_id)
		{
		case 0x46534850: { // 'FSHP'
			char** textureNameWrite = textureNameIt;
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
 * PAL Address: 0x8005D660
 * PAL Size: 628b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditAllReleaseResource()
{
    if (m_materialSet != 0) {
        delete m_materialSet;
        m_materialSet = 0;
    }
    if (m_textureSet != 0) {
        delete m_textureSet;
        m_textureSet = 0;
    }

    for (int i = 0; i < 0x80; i++) {
        if (m_editDataBuffers[i] != 0) {
            operator delete(m_editDataBuffers[i]);
            m_editDataBuffers[i] = 0;
        }
    }

    for (int i = 0; i < 0x80; i++) {
        if (m_editTextBuffers[i] != 0) {
            operator delete(m_editTextBuffers[i]);
            m_editTextBuffers[i] = 0;
        }
    }

    for (int i = 0; i < 0x80; i++) {
        if (m_editProgramData[i] != 0) {
            operator delete(m_editProgramData[i]);
            m_editProgramData[i] = 0;
        }
    }

    if (m_editNodeNameBuffer != 0) {
        delete[] m_editNodeNameBuffer;
        m_editNodeNameBuffer = 0;
    }

    if (m_editModelSlots != 0) {
        for (int i = 0; i < 0x88; i++) {
            if (m_editModelSlots[i] != 0) {
                delete m_editModelSlots[i];
                m_editModelSlots[i] = 0;
            }
        }

        if (m_editModelSlots != 0) {
            operator delete(m_editModelSlots);
            m_editModelSlots = 0;
        }
    }

    if (m_editShapeSlots != 0) {
        for (int i = 0; i < 0x80; i++) {
            if (m_editShapeSlots[i] != 0) {
                delete m_editShapeSlots[i];
                m_editShapeSlots[i] = 0;
            }
        }

        if (m_editShapeSlots != 0) {
            operator delete(m_editShapeSlots);
            m_editShapeSlots = 0;
        }
    }

    for (int i = 0; i < 0x80; i++) {
        if (m_editTextBuffers[i] != 0) {
            operator delete(m_editTextBuffers[i]);
            m_editTextBuffers[i] = 0;
        }
    }

    if (m_editShapeGroups != 0) {
        operator delete(m_editShapeGroups);
        m_editShapeGroups = 0;
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 268b
 * EN Address: 0x800681F8
 * EN Size: 180b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void CheckSum(char* packet, unsigned long code, unsigned long packetSize)
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

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CheckSum(packet, code, packetSize);
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
        allFreeFPrim();
        pppEditAllReleaseResource();
        ppvSysStopPartF = 1;
        *reinterpret_cast<int*>(self + 0x800) = 0;
        *reinterpret_cast<int*>(self + 0x804) = -1;
        m_editParticleCount = 0;
        m_editProgramCount = 0;
        m_isEditMode = 0;

        InitMaterialSet();
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
        if (m_isEditMode != 0) {
            return;
        }

        m_pppMng[0].m_position.x = payloadFloats[0];
        m_pppMng[0].m_position.y = payloadFloats[1];
        m_pppMng[0].m_position.z = payloadFloats[2];
        m_pppMng[0].m_rotation.x = payloadWords[4];
        m_pppMng[0].m_rotation.y = payloadWords[5];
        m_pppMng[0].m_rotation.z = payloadWords[6];
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
        if (m_isEditMode != 0) {
            return;
        }

        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 1;
        m_pppEnvSt.m_mapMeshPtr = reinterpret_cast<CMapMesh**>(m_editModelSlots);
        m_pppEnvSt.m_shapeTablePtr = m_editShapeSlots;
        m_pppEnvSt.m_shapeGroupPtr = m_editShapeGroups;
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

        for (int i = 0; i < m_editParticleCount; i++) {
            m_pppMng[i].m_deltaTime = *reinterpret_cast<long*>(self + 0x168);
        }
        return;
    }
    case 2: {
        if (m_isEditMode != 0) {
            return;
        }

        *reinterpret_cast<int*>(self + kLastEnvCmdOffset) = 2;
        m_pppEnvSt.m_mapMeshPtr = reinterpret_cast<CMapMesh**>(m_editModelSlots);
        m_pppEnvSt.m_shapeTablePtr = m_editShapeSlots;
        m_pppEnvSt.m_shapeGroupPtr = m_editShapeGroups;
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

        for (int i = 0; i < m_editParticleCount; i++) {
            m_pppMng[i].m_deltaTime = *reinterpret_cast<long*>(self + 0x168);
        }
        return;
    }
    case 5:
    case 9:
        if (m_isEditMode != 0) {
            return;
        }
        {
            CChunkFile chunkFile;
            chunkFile.SetBuf(payloadWords + 8);

            if (m_editModelSlots == 0) {
                m_editModelSlots = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x5F8) pppModelSt*[0x88];
                for (int slot = 0; slot < 0x88; slot++) {
                    m_editModelSlots[slot] = 0;
                }
            }

            pppModelSt* modelSlot = m_editModelSlots[*reinterpret_cast<short*>(payload)];
            if (modelSlot != 0) {
                modelSlot->Release();
                m_editModelSlots[*reinterpret_cast<short*>(payload)] = 0;
            }

            modelSlot = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x5FC) pppModelSt;
            m_editModelSlots[*reinterpret_cast<short*>(payload)] = modelSlot;
            pppReadRsd(chunkFile, m_editModelSlots[*reinterpret_cast<short*>(payload)]);
            *reinterpret_cast<int*>(self + 0x804) = -1;
        }
        return;
    case 6:
    case 10:
        if (m_isEditMode != 0) {
            return;
        }
        {
            if (m_editShapeSlots == 0) {
                m_editShapeSlots = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x60A) pppShapeSt*[0x80];
                for (int slot = 0; slot < 0x80; slot++) {
                    m_editShapeSlots[slot] = 0;
                }
            }

            int slotIndex = payloadWords[0];
            pppShapeSt* shapeSlot = m_editShapeSlots[slotIndex];
            if (shapeSlot != 0) {
                shapeSlot->Release();
                m_editShapeSlots[slotIndex] = 0;
            }

            shapeSlot = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x610) pppShapeSt;
            m_editShapeSlots[slotIndex] = shapeSlot;
            CChunkFile chunkFile;
            chunkFile.SetBuf(payloadWords + 4);
            pppReadShp(chunkFile, m_editShapeSlots[slotIndex]);
        }
        return;
    case 8:
        if (m_isEditMode != 0) {
            return;
        }
        {
            if (m_editShapeGroups == 0) {
                m_editShapeGroups = new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x61F)
                    pppShapeGroupRaw[0x80];
            }

            int slotIndex = payloadWords[0];
            if (m_editTextBuffers[slotIndex] == 0) {
                m_editTextBuffers[slotIndex] = operator new[](
                    packetSize - 0x20, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x625);
            }

            memcpy(m_editTextBuffers[slotIndex], payload, packetSize - 0x20);
            int* groupData = reinterpret_cast<int*>(m_editTextBuffers[slotIndex]);
            pppShapeGroupRaw* group = &m_editShapeGroups[slotIndex];
            group->m_groupId = static_cast<short>(groupData[1]);
            group->m_shapeCount = static_cast<short>(groupData[2]);
            group->m_shapeList = reinterpret_cast<short*>(groupData + 3);
        }
        return;
    case 0x0B:
        if (m_isEditMode != 0) {
            return;
        }
        {
            CChunkFile chunkFile;
            chunkFile.SetBuf(payload);

            ReadTex(chunkFile);
        }
        return;
    case 0x0C:
        if (m_isEditMode != 0) {
            return;
        }
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x646);
        allFreeFPrim();
        {
            if (m_editProgramData[0] != 0) {
                delete reinterpret_cast<u8*>(m_editProgramData[0]);
                m_editProgramData[0] = 0;
            }
            if (m_editNodeNameBuffer != 0) {
                delete m_editNodeNameBuffer;
                m_editNodeNameBuffer = 0;
            }
            m_editProgramData[0] = reinterpret_cast<long*>(operator new[](
                packetSize - 0x20, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x64D));
            m_editNodeNameBuffer =
                new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x64E) u8[0x3000];
            memcpy(m_editProgramData[0], payload, packetSize - 0x20);
            pppInitPdt(m_editProgramData[0], pppGetSysProgTable());
        }

        reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer)->m_autoCreateMarker = 0;
        m_pppMng[0].m_baseTime = 0;
        reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer)->m_cullDistance = kPartMngCullRadiusSqMax;
        m_pppMng[0].m_cullRadiusSq = kPartMngCullRadiusSqMax;
        reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer)->m_cullYOffset = kPartMngCullRadius;
        reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer)->m_cullRadius = kPartMngCullRadius;
        m_pppMng[0].m_cullYOffset = kPartMngCullRadius;
        m_pppMng[0].m_cullRadius = kPartMngCullRadius;
        reinterpret_cast<_pppFieldParticleData*>(m_editNodeNameBuffer)->m_partIndex = 0;
        m_editParticleCount = 1;
        m_editProgramCount = 1;
        m_pppMng[0].m_objHitMask = 0xFFFFFFFF;
        m_pppMng[0].m_cylinderAttribute = 0xFFFFFFFF;
        m_pppMng[0].m_paramA = 0;
        m_pppMng[0].m_slotVisible = 1;
        m_pppMng[0].m_ownerFacing = 1;
        m_pppMng[0].m_pppResSet = self + 0x23518;
        m_pppMng[0].m_nodeIndex = 0;
        m_pppMng[0].m_fieldF2 = 1;
        m_pppEnvSt.m_mapMeshPtr = reinterpret_cast<CMapMesh**>(m_editModelSlots);
        m_pppEnvSt.m_shapeTablePtr = m_editShapeSlots;
        m_pppEnvSt.m_shapeGroupPtr = m_editShapeGroups;
        return;
    case 0x0D: {
        if (m_isEditMode != 0) {
            return;
        }
        Graphic._WaitDrawDone(const_cast<char*>(s_partMng_cpp), 0x673);
        if (m_editProgramData[m_editProgramCount] != 0) {
            delete reinterpret_cast<u8*>(m_editProgramData[m_editProgramCount]);
            m_editProgramData[m_editProgramCount] = 0;
        }
        if (m_editNodeNameBuffer != 0) {
            delete m_editNodeNameBuffer;
            m_editNodeNameBuffer = 0;
        }

        m_editProgramData[m_editProgramCount] = reinterpret_cast<long*>(operator new[](
            packetSize - 0x20, PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x678));
        m_editNodeNameBuffer =
            new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x679) u8[0x3000];
        memcpy(m_editProgramData[m_editProgramCount], payload, packetSize - 0x20);
        pppInitPdt(m_editProgramData[m_editProgramCount], pppGetSysProgTable());
        m_editProgramCount = m_editProgramCount + 1;
        return;
    }
    case 0x0F:
        if (m_isEditMode != 0) {
            return;
        }
        allFreeFPrim();
        ppvSysStopPartF = 1;
        return;
    case 0x0E:
        if (m_isEditMode != 0) {
            return;
        }
        if (m_editParticleCount == 0) {
            m_editReceiveCursor = m_editNodeNameBuffer;
        }
        memcpy(m_editReceiveCursor, payload, packetSize - 0x20);
        m_editReceiveCursor += sizeof(_pppFieldParticleData);
        m_editParticleCount += 1;
        return;
    case 0x10:
        if (m_isEditMode != 0) {
            return;
        }
        m_envParam = kPartMngZero;
        m_pppEnvSt.m_mapMeshPtr = reinterpret_cast<CMapMesh**>(m_editModelSlots);
        m_pppEnvSt.m_shapeTablePtr = m_editShapeSlots;
        m_pppEnvSt.m_shapeGroupPtr = m_editShapeGroups;
        SetFp();
        return;
    case 0x11:
        if (m_isEditMode != 0) {
            return;
        }
        m_pppMng[0].m_particleEnded = 1;
        return;
    case 0x12: {
        if (m_isEditMode != 0) {
            return;
        }
        fpIDon(static_cast<unsigned short>(*reinterpret_cast<unsigned int*>(self + 0x1C4)));
        return;
    }
    case 0x13: {
        if (m_isEditMode != 0) {
            return;
        }
        fpIDoff(static_cast<unsigned short>(*reinterpret_cast<unsigned int*>(self + 0x1C4)));
        return;
    }
    case 0x17:
        if (m_isEditMode != 0) {
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
 * PAL Address: TODO
 * PAL Size: 208b
 * EN Address: 0x80069094
 * EN Size: 308b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void pppSetFog(unsigned char fogEnable, unsigned char fogR, unsigned char fogG, unsigned char fogB,
                             float fogNear, float fogFar)
{
    _GXColor fogColor;
    if (fogEnable != 0) {
        fogColor.r = fogR;
        fogColor.g = fogG;
        fogColor.b = fogB;
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
}

/*
 * --INFO--
 * PAL Address: 0x8005BBC0
 * PAL Size: 1648b
 * EN Address: 0x800691C8
 * EN Size: 1452b
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

        unsigned char fogEnable = *reinterpret_cast<unsigned char*>(self + 0x15c);
        float fogNear;
        float fogFar = *reinterpret_cast<float*>(self + 0x164);
        fogNear = *reinterpret_cast<float*>(self + 0x160);
        unsigned char fogG;
        unsigned char fogB = *reinterpret_cast<unsigned char*>(self + 0x15f);
        fogG = *reinterpret_cast<unsigned char*>(self + 0x15e);
        unsigned char fogR = *reinterpret_cast<unsigned char*>(self + 0x15d);
        pppSetFog(fogEnable, fogR, fogG, fogB, fogNear, fogFar);

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

        unsigned char fogEnable = *reinterpret_cast<unsigned char*>(self + 0x15c);
        float fogNear;
        float fogFar = *reinterpret_cast<float*>(self + 0x164);
        fogNear = *reinterpret_cast<float*>(self + 0x160);
        unsigned char fogG;
        unsigned char fogB = *reinterpret_cast<unsigned char*>(self + 0x15f);
        fogG = *reinterpret_cast<unsigned char*>(self + 0x15e);
        unsigned char fogR = *reinterpret_cast<unsigned char*>(self + 0x15d);
        pppSetFog(fogEnable, fogR, fogG, fogB, fogNear, fogFar);

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
            CGObject* dyingObj = *reinterpret_cast<CGObject* volatile*>(editorObj);
            if (dyingObj != 0) {
                operator delete(dyingObj);
                *editorObj = 0;
            }
        }

        *editorObj =
            new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x7b5) CGObject;
        (*editorObj)->Create();

        (*editorObj)->m_charaModelHandle =
            new (PartPcs.m_usbStreamState.m_stageLoad, const_cast<char*>(s_partMng_cpp), 0x7b7) CCharaPcs::CHandle;
        (*editorObj)->m_charaModelHandle->Add();
        (*editorObj)->m_charaModelHandle->m_flags = 3;
        if ((*editorObj)->m_charaModelHandle->LoadModel(
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
            handle->LoadAnim(reinterpret_cast<char*>(self + 0x19c), gPppInConstructor, 0, -1, -1, -1, 0);
            handle->SetAnim(gPppInConstructor, -1, -1, -1, 0);
            gPppInConstructor++;
#undef handle
        }
        break;
    case 0x1b:
        *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MapPcs) + 0x180) =
            *reinterpret_cast<unsigned int*>(self + 0x1bc);
        break;
    case 0x1c:
        if (*editorObj != 0) {
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

    g_par_calc_prof.Stop();
    if (*reinterpret_cast<CGObject**>(self + 0x80c) != 0) {
        (*reinterpret_cast<CGObject**>(self + 0x80c))->m_charaModelHandle->m_model->CalcMatrix();
        (*reinterpret_cast<CGObject**>(self + 0x80c))->m_charaModelHandle->m_model->CalcSkin();
        (*reinterpret_cast<CGObject**>(self + 0x80c))->m_charaModelHandle->m_model->SetFrame(
            *reinterpret_cast<float*>(self + 0x23564));
        if (ppvUserStopPartF == 0) {
            *reinterpret_cast<float*>(self + 0x23564) += kPartMngOne;
        }
    }
    g_par_calc_prof.Start();

    if (usbEdit[0x18] != 0) {
        usbEdit[0x18] = 0;
        usbEdit[0x19] = 1;
        usbEdit[0x1A] = 0;

        allFreeFPrim();
        _pppMngSt* firstMng = m_pppMng;
        firstMng->m_particleEnded = 0;
        firstMng->m_deltaTime = *reinterpret_cast<int*>(self + 0x168);
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
            mng->m_deltaTime = *reinterpret_cast<int*>(self + 0x168);
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
            mng->m_deltaTime = *reinterpret_cast<int*>(self + 0x168);
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
 * EN Address: 0x8005AF54
 * EN Size: 488b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditDrawShadow()
{
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
                    CBound bound(&partPos, mng->m_cullRadius, mng->m_cullYOffset);
                    if (bound.CheckFrustum(
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
 * EN Address: 0x8005A820
 * EN Size: 1844b
 * JP Address: TODO
 * JP Size: TODO
 */
static inline void pppEditDrawPass(unsigned char* base, int drawPass, Vec& cameraPos)
{
    static const int kPppMngCount = 0x180;
    static const int kPppMngOffset = 0x2A18;
    static const int kPppMngStride = 0x158;
    Vec viewPos;
    Vec partPos;
    Vec cameraDelta;

    _pppMngSt* mng;
    int i;
    for (i = 0; i < kPppMngCount; i++, base += kPppMngStride) {
        mng = reinterpret_cast<_pppMngSt*>(base + kPppMngOffset);
        if (mng->m_hitBgFlag == 0 && mng->m_baseTime != -0x1000
            && (signed char)mng->m_drawPass == drawPass && mng->m_baseTime < 0
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
            {
                char* resSet = *reinterpret_cast<char**>(mng);
                ppvMng = mng;
                ppvEnv = reinterpret_cast<_pppEnvSt*>(resSet + 4);
            }
            pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));
            _pppDrawPart(reinterpret_cast<_pppMngSt*>(mng));
            continue;

        checkCull:
            PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
            if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                CBound bound(&partPos, mng->m_cullRadius, mng->m_cullYOffset);
                if (bound.CheckFrustum(
                        cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
                    goto drawPart;
                }
            }
        }
    }
}

void CPartMng::pppEditDraw()
{
    static const int kPppMngCount = 0x180;
    static const int kPppMngStride = 0x158;
    static const int kEditCountOffset = 0x4;
    static const int kEditDrawModeOffset = 0x23570;
    static const int kCursorEnableOffset = 0xC;
    static const int kBaseTimeOffset = 0x14;
    static const int kLifeEndOffset = 0x24;
    static const int kCurrentFrameOffset = 0x34;
    static const int kMatrixOffset = 0x78;
    static const int kEndRequestedOffset = 0xe8;
    static const int kDrawPassOffset = 0xed;
    static const int kStopAtLifeEndOffset = 0xe4;
    static const int kSlotVisibleOffset = 0xe9;
    static const int kOwnerVisibleOffset = 0xea;
    static const int kCullRadiusSqOffset = 0x108;
    static const int kCullRadiusOffset = 0x10c;
    static const int kCullYOffsetOffset = 0x110;
    static const int kSortDepthOffset = 0x114;

    if (ppvSysStopPartF != 0) {
        return;
    }

    m_debugCounter = 0;

    Vec partPos;
    Vec viewPos;
    if (*reinterpret_cast<long**>(reinterpret_cast<unsigned char*>(this) + 0x5dc) != 0) {
        if (*reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x174) <= 3) {
#define PPP_EDIT_DRAW_PASS(drawPass)                                                                       \
            {                                                                                              \
                Mtx invCamera;                                                                             \
                Vec cameraPos;                                                                             \
                PSMTXInverse(ppvCameraMatrix, invCamera);                                                  \
                cameraPos.x = invCamera[0][3];                                                             \
                cameraPos.y = invCamera[1][3];                                                             \
                cameraPos.z = invCamera[2][3];                                                             \
                pppEditDrawPass(reinterpret_cast<unsigned char*>(this), drawPass, cameraPos);                                            \
            }

            PPP_EDIT_DRAW_PASS(8)
            PPP_EDIT_DRAW_PASS(4)
            pppDraw();
            PPP_EDIT_DRAW_PASS(6)
            PPP_EDIT_DRAW_PASS(7)
#undef PPP_EDIT_DRAW_PASS
        } else {
            static const int kPppMngOffset = 0x2A18;
            char* base = reinterpret_cast<char*>(this);
            for (int i = 0; i < *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + kEditCountOffset); i++) {
                _pppMngSt* mng = reinterpret_cast<_pppMngSt*>(base + kPppMngOffset);
                ppvMng = mng;
                int baseTime = *reinterpret_cast<int*>(base + kPppMngOffset + kBaseTimeOffset);
                if (baseTime != -0x1000 && baseTime < 0) {
                    partPos.x = *reinterpret_cast<float*>(reinterpret_cast<char*>(mng) + kMatrixOffset + 0xc);
                    partPos.y = *reinterpret_cast<float*>(reinterpret_cast<char*>(mng) + kMatrixOffset + 0x1c);
                    partPos.z = *reinterpret_cast<float*>(reinterpret_cast<char*>(mng) + kMatrixOffset + 0x2c);
                    PSMTXMultVec(ppvCameraMatrix, &partPos, &viewPos);
                    *reinterpret_cast<float*>(reinterpret_cast<char*>(mng) + kSortDepthOffset) = viewPos.z;
                    ppvDrawMng.AddPrimOt(0x3ff, mng);
                    if (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(mng) + kStopAtLifeEndOffset) != 0
                        && *reinterpret_cast<int*>(reinterpret_cast<char*>(mng) + kCurrentFrameOffset) == *reinterpret_cast<int*>(reinterpret_cast<char*>(mng) + kLifeEndOffset)) {
                        gPppHeapUseRateWords[1] = 0;
                    }
                }
                base += kPppMngStride;
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
    if (ppvSysStopPartF == 0) {
        m_debugCounter = 0;
        if (*reinterpret_cast<long**>(reinterpret_cast<unsigned char*>(this) + 0x5dc) != 0
            && *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x174) <= 3) {
#define PPP_DRAW_AFTER_PASS(drawPass)                                                              \
            {                                                                                              \
                Mtx invCamera;                                                                             \
                Vec cameraPos;                                                                             \
                PSMTXInverse(ppvCameraMatrix, invCamera);                                                  \
                cameraPos.x = invCamera[0][3];                                                             \
                cameraPos.y = invCamera[1][3];                                                             \
                cameraPos.z = invCamera[2][3];                                                             \
                pppEditDrawPass(reinterpret_cast<unsigned char*>(this), drawPass, cameraPos);              \
            }

            PPP_DRAW_AFTER_PASS(5)
            PPP_DRAW_AFTER_PASS(6)
            PPP_DRAW_AFTER_PASS(7)
#undef PPP_DRAW_AFTER_PASS
        }
    }

    drawEnd();
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
void CPartMng::pppDumpCacheIdx()
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
 * PAL Address: 0x8005A6C0
 * PAL Size: 512b
 * EN Address: 0x80069F30
 * EN Size: 444b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppPartCalc()
{
    pppSetRendMatrix();

    int i;
    int gamePaused = Game.m_gameWork.m_gamePaused;
    for (i = 0; i < 0x180; i++) {
        _pppMngSt* mng = &m_pppMng[i];
        if ((gamePaused == 0 || (mng->m_drawPass >= 6 && mng->m_drawPass <= 7)) &&
            mng->m_baseTime != -0x1000) {
            ppvMng = mng;
            if (mng->m_hitBgFlag != 0) {
                continue;
            }
            ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);

            if (mng->m_baseTime >= 0) {
                goto decrementTimer;
            }

        runFrame:
            pppSetMatrix(mng);
            pppSetFpMatrix(mng);

            mng->m_spawnedCount += mng->m_deltaTime;
            ppvIs2ndCalc = 0;

            while (mng->m_spawnedCount >= 0x1000) {
                _pppCalcPart(mng);
                _pppDeadPart(mng);
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
                pppCacheChunk* partResource =
                    &reinterpret_cast<pppCacheChunk*>(pdtHead->m_cacheChunks)[mng->m_partIndex];

                if (ppvAmemCacheSet.IsEnable(partResource->m_cacheIndex) == 0) {
                    partResource->m_pdt = reinterpret_cast<long*>(
                        ppvAmemCacheSet.GetData(
                            partResource->m_cacheIndex, const_cast<char*>(s_partMng_cpp), 0x9A9));
                    pppInitPdt(partResource->m_pdt, pppGetSysProgTable());
                }

                ppvAmemCacheSet.AddRef(partResource->m_cacheIndex);
                mng->m_hasMapRef = 1;
                _pppStartPart(mng, partResource->m_pdt, 1);
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
 * EN Address: 0x80059E94
 * EN Size: 456b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDrawPrio(unsigned char drawMode)
{
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
                CBound bound(&partPos, mng->m_cullRadius, mng->m_cullYOffset);
                if (bound.CheckFrustum(
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
 * EN Address: 0x80059CA8
 * EN Size: 492b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDrawPrioPdtFpno(unsigned char drawMode, short kind, short nodeIndex)
{
    Mtx invCamera;
    Vec cameraPos;
    Vec cameraDelta;
    Vec partPos;
    Vec viewPos;
    _pppMngSt* mng;
    int i;

    PSMTXInverse(ppvCameraMatrix, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    for (i = 0; i < 0x180; i++) {
        mng = &m_pppMng[i];
        if (mng->m_nodeIndex == nodeIndex && mng->m_kind == kind && mng->m_hitBgFlag == 0
            && mng->m_baseTime != -0x1000 && (signed char)mng->m_drawPass == drawMode && mng->m_baseTime < 0) {
            if (mng->m_slotVisible == 0) {
                break;
            }

            ppvMng = mng;
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            {

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
                break;

            checkCull:
                PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                if (!(PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq)) {
                    break;
                }

                CBound bound(&partPos, mng->m_cullRadius, mng->m_cullYOffset);
                if (bound.CheckFrustum(
                        cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
                    goto drawPart;
                }
                break;
            }
        }
    }
    if (drawMode < 8) {
        return;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005a18c
 * PAL Size: 380b
 * EN Address: 0x80059B2C
 * EN Size: 380b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDrawIdx(int partIndex)
{
    Mtx invCamera;
    Vec cameraPos;
    Vec cameraDelta;
    Vec partPos;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    _pppMngSt* mng = &m_pppMng[partIndex];
    if (mng->m_hitBgFlag != 0) {
        return;
    }
    if (mng->m_baseTime == -0x1000) {
        return;
    }
    if (mng->m_baseTime >= 0) {
        return;
    }

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
    ppvEnv = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);
    ppvMng = mng;
    pppSetFpMatrix(mng);
    _pppDrawPart(mng);
    return;

checkCull:
    PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
    if (!(PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq)) {
        return;
    }

    {
        CBound bound(&partPos, mng->m_cullRadius, mng->m_cullYOffset);
        if (bound.CheckFrustum(cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
            goto drawPart;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80059f6c
 * PAL Size: 544b
 * EN Address: 0x8005990C
 * EN Size: 544b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppDraw()
{
    Mtx invCamera;
    Vec cameraPos;
    Vec viewPos;
    Vec partPos;
    Vec cameraDelta;

    m_debugCounter = 0;
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
                    CBound bound(&partPos, mng->m_cullRadius, mng->m_cullYOffset);
                    if (bound.CheckFrustum(cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) == 0) {
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
 * EN Address: 0x80059704
 * EN Size: 520b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppPartDrawAfter()
{
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
                CBound bound(&partPos, mng->m_cullRadius, mng->m_cullYOffset);
                if (bound.CheckFrustum(
                        cameraPos, ppvCameraMatrix, kPartMngFrustumCullLimit) != 0) {
                    goto drawPart;
                }
            }
        }
    }

    gPppHeapUseRateWords[0] = pppHeapUseRate(ppvEnv->m_stagePtr);
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
 * PAL Address: TODO
 * PAL Size: 116b
 * EN Address: 0x8006AC94
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::pppInitEnv(_pppEnvSt* env, _pppDataHead* dataHead, unsigned int heapSize)
{
    ppvEnv = env;
    env->m_materialSetPtr = m_materialSet;
    if (dataHead != 0) {
        env->m_mapMeshPtr = reinterpret_cast<CMapMesh**>(dataHead->m_modelNames);
        env->m_shapeTablePtr = reinterpret_cast<pppShapeSt**>(dataHead->m_shapeNames);
        env->m_shapeGroupPtr = reinterpret_cast<pppShapeGroupRaw*>(dataHead->m_shapeGroups);
    }
    if (heapSize != 0) {
        pppCreateHeap(env, heapSize);
    } else {
        env->m_stagePtr = PartMng.m_pppEnvSt.m_stagePtr;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80059A28
 * PAL Size: 540b
 * EN Address: 0x8006AD38
 * EN Size: 988b
 * JP Address: TODO
 * JP Size: TODO
 */
void* CPartMng::pppFileRead(char* filePath, unsigned long& fileSize, void* readBuffer, int readBufferSize)
{
    CFile::CHandle* fileHandle;

    if (m_partLoadMode == 1) {
        fileSize = m_partChunkSize[m_partChunkIndex];
        if (fileSize == 0) {
            return 0;
        }
        void* fileData = File.m_readBuffer;
        Memory.CopyFromAMemorySync(
            fileData, reinterpret_cast<void*>(m_partAMemCursor), (fileSize + 0x1f) & ~0x1f);
        m_partAMemCursor += fileSize;
        CheckSum(fileData, fileSize);
        m_partChunkIndex++;
        return fileData;
    } else if (readBuffer != 0 || (fileHandle = File.Open(filePath, 0, CFile::PRI_LOW)) != 0) {
        if (m_partLoadMode == 3) {
            File.ReadASync(fileHandle);
            m_partAsyncBusy[m_asyncHandleCount] = fileHandle;
            m_asyncHandleCount++;
            return reinterpret_cast<void*>(1);
        } else {
            void* fileData;
            if (readBuffer != 0) {
                fileSize = readBufferSize;
                fileData = readBuffer;
            } else {
                fileSize = File.GetLength(fileHandle);
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                fileData = File.m_readBuffer;
                File.Close(fileHandle);
            }
            if (m_partLoadMode == 2) {
                Memory.CopyToAMemorySync(fileData, reinterpret_cast<void*>(m_partAMemCursor), fileSize);
                m_partChunkSize[m_partChunkIndex] = fileSize;
                m_partChunkChecksum[m_partChunkIndex] = CheckSum(fileData, fileSize);
                m_partChunkIndex++;
                m_partAMemCursor += fileSize;
            }
            return fileData;
        }
    }

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
        m_materialSet->AddMaterial(defaultMaterial, 0);
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
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006E198
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
inline pppModelSt* CParModelSet::GetFree()
{
    for (int i = 0; i < GetNumModel(); i++) {
        if (m_models[i].m_isUsed == 0) {
            return &m_models[i];
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 508b
 * EN Address: 0x8006B5EC
 * EN Size: 420b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CParModelSet::Create(CChunkFile& chunkFile, int cachePriority, int addReference)
{
    pppModelSt* modelArray = m_models;
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
                    break;
                }
                i++;
                searchModel++;
                if (i >= 0x100) {
                    searchModel = 0;
                    break;
                }
            }

            if (searchModel != 0) {
                targetModel = 0;
                break;
            }

            targetModel = GetFree();
            targetModel->SetUse();
            strcpy(targetModel->m_name, name);
            break;
        }
        case kChunkRSDM:
            if (targetModel != 0) {
                CChunkFile rsdFile;
                rsdFile.SetBuf(chunkFile.GetAddress());
                unsigned int meshSize = PartMng.pppReadRsd(rsdFile, targetModel);
                targetModel->Ptr2Off();

                targetModel->m_cacheId = static_cast<short>(ppvAmemCacheSet.SetData(
                    targetModel->m_meshData, meshSize, static_cast<CAmemCache::TYPE>(1), cachePriority));

                if (targetModel->m_meshData != 0) {
                    operator delete(targetModel->m_meshData);
                    targetModel->m_meshData = 0;
                }

                if (addReference != 0) {
                    targetModel->AddRef();
                }
                targetModel = 0;
            }
            break;
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 556b
 * EN Address: 0x8006B790
 * EN Size: 136b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::pppLoadPmd(CChunkFile& chunkFile)
{
    CChunkFile::CChunk outerChunk;
    while (chunkFile.GetNextChunk(outerChunk)) {
        chunkFile.PushChunk();
        switch (outerChunk.m_id) {
        case kChunkRSET:
            m_modelSet->Create(chunkFile, 1, 1);
            break;
        }
        chunkFile.PopChunk();
    }
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

    if (m_modelSet == 0) {
        CMemory::CStage* stageLoad = PartPcs.m_usbStreamState.m_stageLoad;
        m_modelSet = new (stageLoad, const_cast<char*>(s_partMng_cpp), 0xca9) CParModelSet;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    pppLoadPmd(chunkFile);

    return 1;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: 0x8006E2D4
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
inline pppShapeSt* CParShapeSet::GetFree()
{
    for (int i = 0; i < GetNumShape(); i++) {
        if (m_shapes[i].m_inUse == 0) {
            return &m_shapes[i];
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 412b
 * EN Address: 0x8006B970
 * EN Size: 304b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CParShapeSet::Create(CChunkFile& chunkFile, int addReference)
{
    pppShapeSt* shapeArray = m_shapes;
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
                    break;
                }
                i++;
                searchShape++;
                if (i >= 0x100) {
                    searchShape = 0;
                    break;
                }
            }

            if (searchShape != 0) {
                targetShape = 0;
                break;
            }

            targetShape = GetFree();
            targetShape->SetUse();
            strcpy(targetShape->m_name, name);
            break;
        }
        case kChunkSHPM:
            if (targetShape != 0) {
                CChunkFile shpFile;
                shpFile.SetBuf(chunkFile.GetAddress());
                PartMng.pppReadShp(shpFile, targetShape);
                if (addReference != 0) {
                    targetShape->AddRef();
                }
                targetShape = 0;
            }
            break;
        }
    }
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: 464b
 * EN Address: 0x8006BAA0
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CPartMng::pppLoadPan(CChunkFile& chunkFile)
{
    CChunkFile::CChunk outerChunk;
    while (chunkFile.GetNextChunk(outerChunk)) {
        chunkFile.PushChunk();
        switch (outerChunk.m_id) {
        case kChunkSSET:
            m_shapeSet->Create(chunkFile, 1);
            break;
        }
        chunkFile.PopChunk();
    }
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

    if (m_shapeSet == 0) {
        CMemory::CStage* stageLoad = PartPcs.m_usbStreamState.m_stageLoad;
        m_shapeSet = new (stageLoad, const_cast<char*>(s_partMng_cpp), 0xd0b) CParShapeSet;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    pppLoadPan(chunkFile);

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
                case kChunkRSET:
                    m_modelSet->Create(pdtFile, cachePriority, 0);
                    break;
                case kChunkSSET:
                    m_shapeSet->Create(pdtFile, 0);
                    break;
                case kChunkPDTS: {
                    _pppDataHead* sourceHead = reinterpret_cast<_pppDataHead*>(pdtFile.GetAddress());
                    pppInitData(sourceHead, pppGetSysProgTable(), cachePriority);

                    pdtSlot->m_pppDataHead = static_cast<_pppDataHead*>(
                        operator new[](
                            sourceHead->m_partCount * sizeof(_pppFieldParticleData) + sizeof(_pppDataHead), PartPcs.m_usbStreamState.m_stageLoad,
                            const_cast<char*>(s_partMng_cpp), 0xd56));

                    memcpy(pdtSlot->m_pppDataHead, sourceHead, sourceHead->m_partCount * sizeof(_pppFieldParticleData) + sizeof(_pppDataHead));

                    pppInitEnv(&pdtSlot->m_env, pdtSlot->m_pppDataHead, 0);
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
    PppPdtSlot* freeSlot = pppGetFreePppDataMngSt();

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

struct PppHitIdBlock {
    int m_ids[8];
};

/*
 * --INFO--
 * PAL Address: 0x80058148
 * PAL Size: 1632b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppCreate0(int pdtSlotIndex, int fpNo, PPPCREATEPARAM* createParam, int allowFpOverride)
{
    PppPdtSlot* slot = &m_pdtSlots[pdtSlotIndex];
    if (slot == 0 || slot->m_pppDataHead == 0) {
        return -1;
    }
    _pppDataHead* pdt = slot->m_pppDataHead;

    _pppFieldParticleData* fp = reinterpret_cast<_pppFieldParticleData*>(
        reinterpret_cast<unsigned char*>(pdt) + sizeof(_pppDataHead) + fpNo * sizeof(_pppFieldParticleData));

    _pppMngSt* mng = pppGetFreePppMngSt();
    if (mng == 0) {
        return -1;
    }

    if (static_cast<unsigned int>(System.m_execParam) >= 1U) {
        System.Printf(const_cast<char*>(sPppCreateLogFmt), pdtSlotIndex, fpNo,
                      mng - m_pppMng,
                      m_pdtSlots[pdtSlotIndex].m_name);
    }

    mng->m_paramB = -1;
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
    mng->m_deltaTime = 0x1333;
    if (reinterpret_cast<unsigned char*>(&PartPcs)[0x2f] != 0 && pdtSlotIndex == 7 && fpNo == 0) {
        mng->m_deltaTime = 0x1000;
    }

    mng->m_soundEffectData = createParam->m_soundEffectParams;
    mng->m_soundEffectData.m_soundEffectStartFrame <<= 0xC;

    mng->m_isFinished = 0;
    mng->m_hitBgFlag = 0;
    mng->m_particleEnded = 0;
    mng->m_slotVisible = 1;
    mng->m_ownerFacing = 1;

    const int initialTime = fp->m_autoCreateMarker;
    if (initialTime == -0x1000) {
        mng->m_baseTime = 0;
    } else {
        mng->m_baseTime = initialTime * 0x19 / 0x1E;
    }

    mng->m_pppResSet = slot;
    mng->m_partIndex = fp->m_partIndex;
    mng->m_cullRadiusSq = fp->m_cullDistance;
    if (mng->m_cullRadiusSq > 0.0) {
        mng->m_cullRadiusSq *= mng->m_cullRadiusSq;
    }
    mng->m_cullRadius = fp->m_cullRadius;
    mng->m_cullYOffset = fp->m_cullYOffset;
    mng->m_pppPObjLinkHead.m_next = 0;
    mng->m_pppPDataVals = 0;

    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(mng) + 0xFC) =
        fp->m_fieldId;
    mng->m_field118 = fp->m_field118;
    mng->m_matrixMode = fp->m_matrixMode;
    mng->m_drawVariant = fp->m_drawVariant;
    mng->m_rotationOrder = fp->m_rotationOrder;
    mng->m_drawPass = fp->m_drawPass;
    mng->m_drawSubType = fp->m_drawSubType;
    mng->m_ownerFlagsInitialized = fp->m_ownerFlagsInitialized;
    mng->m_nodeScaleInitialized = fp->m_nodeScaleInitialized;
    mng->m_fieldF2 = 1;
    if (allowFpOverride != 0) {
        const int mode = fp->m_matrixMode;
        switch (mode) {
        case 3:
        case 5:
        case 6:
        case 7:
        case 8:
            break;
        default:
            mng->m_fieldF2 = fp->m_fieldF2;
            break;
        }
    }

    mng->m_fpBillboard = fp->m_fpBillboard;
    mng->m_prio = fp->m_prio;
    mng->m_mapObjIndex = fp->m_mapObjIndex;

    mng->m_bindNode = 0;
    mng->m_objHitMask = createParam->m_objectHitMask;
    mng->m_cylinderAttribute = createParam->m_cylinderAttribute;
    mng->m_paramA = createParam->m_paramA;
    mng->m_movementScale = createParam->m_paramC;
    mng->m_hitScale = createParam->m_paramD;

    {
        if (createParam->m_positionOffsetPtr == 0) {
            mng->m_position.x = fp->m_position.x;
            mng->m_position.y = fp->m_position.y;
            mng->m_position.z = fp->m_position.z;
            mng->m_basePosition.x = mng->m_position.x;
            mng->m_basePosition.y = mng->m_position.y;
            mng->m_basePosition.z = mng->m_position.z;
            mng->m_userPosition.x = mng->m_basePosition.x;
            mng->m_userPosition.y = mng->m_basePosition.y;
            mng->m_userPosition.z = mng->m_basePosition.z;
        } else {
            mng->m_position.x = createParam->m_positionOffsetPtr->x + fp->m_position.x;
            mng->m_position.y = createParam->m_positionOffsetPtr->y + fp->m_position.y;
            mng->m_position.z = createParam->m_positionOffsetPtr->z + fp->m_position.z;
            mng->m_basePosition.x = mng->m_position.x;
            mng->m_basePosition.y = mng->m_position.y;
            mng->m_basePosition.z = mng->m_position.z;
            mng->m_userPosition.x = mng->m_basePosition.x;
            mng->m_userPosition.y = mng->m_basePosition.y;
            mng->m_userPosition.z = mng->m_basePosition.z;
        }
    }

    Vec* extraPos = createParam->m_extraPositionPtr;
    if (extraPos != 0) {
        mng->m_paramVec0.x = extraPos->x;
        mng->m_paramVec0.y = extraPos->y;
        mng->m_paramVec0.z = extraPos->z;
        mng->m_paramVec0.x = mng->m_paramVec0.x + fp->m_position.x;
        mng->m_paramVec0.y = mng->m_paramVec0.y + fp->m_position.y;
        mng->m_paramVec0.z = mng->m_paramVec0.z + fp->m_position.z;
    }

    if (createParam->m_rotationPtr == 0) {
        mng->m_rotation.x = fp->m_rotation.x;
        mng->m_rotation.y = fp->m_rotation.y;
        mng->m_rotation.z = fp->m_rotation.z;
    } else {
        mng->m_rotation.x =
            static_cast<int>(32768.0f * createParam->m_rotationPtr->x / 180.0f);
        mng->m_rotation.y =
            static_cast<int>(32768.0f * createParam->m_rotationPtr->y / 180.0f);
        mng->m_rotation.z =
            static_cast<int>(32768.0f * createParam->m_rotationPtr->z / 180.0f);
    }

    if (createParam->m_scalePtr == 0) {
        mng->m_scale.x = fp->m_scale.x;
        mng->m_scale.y = fp->m_scale.y;
        mng->m_scale.z = fp->m_scale.z;
    } else {
        mng->m_scale.x = createParam->m_scalePtr->x * fp->m_scale.x;
        mng->m_scale.y = createParam->m_scalePtr->y * fp->m_scale.y;
        mng->m_scale.z = createParam->m_scalePtr->z * fp->m_scale.z;
    }

    mng->m_lookTarget = createParam->m_lookTargetPtr;
    mng->m_ownerScale = kPartMngOne;
    mng->m_scaleFactor = kPartMngOne;
    mng->m_userFloat1 = kPartMngOne;
    mng->m_userFloat0 = kPartMngOne;
    mng->m_useOwnerScaleSign = 0;
    mng->m_owner = 0;

    const unsigned char mode = fp->m_matrixMode;
    switch (mode) {
    case 2:
    case 4:
        mng->m_mapObjIndex = static_cast<short>(MapMng.GetMapObjEffectIdx(fp->m_mapObjIndex));
        break;
    case 3:
    case 5:
    case 6:
    case 7:
    case 8:
        mng->m_ownerFacing = 0;
        {
            mng->m_owner = reinterpret_cast<CGObject*>(createParam->m_paramB);
            mng->m_lookTarget = createParam->m_lookTargetPtr;
            if (reinterpret_cast<CGObject*>(createParam->m_paramB) != 0) {
                int node = reinterpret_cast<CGObject*>(createParam->m_paramB)->m_charaModelHandle->m_model->SearchNodeSk(
                    fp->m_nodeName);
                if (node >= 0) {
                    mng->m_bindNode =
                        &reinterpret_cast<CGObject*>(createParam->m_paramB)->m_charaModelHandle->m_model->m_nodes[node];
                }
            }
        }
        break;
    }

    return mng - m_pppMng;
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
    int slot = m_mngStCount;
    int nextSlot = slot + 1;
    m_mngStCount = nextSlot;

    if (nextSlot >= 0x7fffffff) {
        m_mngStCount = 0x10;
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
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = &m_pppMng[i];
        int baseTime = pppMngSt->m_baseTime;
        if (baseTime != -0x1000 && pppMngSt->m_paramA == slot) {
            if (checkHitFlags == 0 || (pppMngSt->m_hitParams.m_hitFlags & 1) == 0) {
                if (baseTime < 0) {
                    pppMngSt->m_hitBgFlag = 1;
                    pppStopSe(pppMngSt, &pppMngSt->m_soundEffectData);
                } else {
                    pppMngSt->m_baseTime = -0x1000;
                }
            }
        }
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
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = &m_pppMng[i];
        if (pppMngSt->m_baseTime != -0x1000
            && pppMngSt->m_paramA == slot) {
            if (checkHitFlags == 0 || (pppMngSt->m_hitParams.m_hitFlags & 1) == 0) {
                pppMngSt->m_particleEnded = 1;
                pppStopSe(pppMngSt, &pppMngSt->m_soundEffectData);
            }
        }
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
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_baseTime != -0x1000 && m_pppMng[i].m_paramA == slot) {
            m_pppMng[i].m_slotVisible = isVisible;
        }
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
    _pppMngSt* mng = &m_pppMng[index];
    int baseTime = mng->m_baseTime;

    if (baseTime < 0) {
        mng->m_hitBgFlag = 1;
        pppStopSe(mng, &mng->m_soundEffectData);
    } else {
        mng->m_baseTime = -0x1000;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057E58
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEndPart(int index)
{
    _pppMngSt* mng = &m_pppMng[index];

    mng->m_particleEnded = 1;
    pppStopSe(mng, &mng->m_soundEffectData);
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
    return &m_pppMng[index].m_hitParams;
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
	m_pppMng[index].m_slotVisible = visible;
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
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_baseTime != -0x1000 && m_pppMng[i].m_kind == 0 &&
            m_pppMng[i].m_nodeIndex == fieldNo) {
            m_pppMng[i].m_slotVisible = visible;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057CE0
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppFieldEndFpNo(short fieldNo)
{
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = &m_pppMng[i];
        int baseTime = pppMngSt->m_baseTime;
        if ((baseTime != -0x1000) && (pppMngSt->m_kind == 0) && (pppMngSt->m_nodeIndex == fieldNo)) {
            if (baseTime < 0) {
                pppMngSt->m_particleEnded = 1;
                pppStopSe(pppMngSt, &pppMngSt->m_soundEffectData);
            } else {
                pppMngSt->m_baseTime = -0x1000;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80057CCC
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppSetDeltaIdx(short index, long deltaTime)
{
    m_pppMng[index].m_deltaTime = deltaTime;
}

/*
 * --INFO--
 * PAL Address: 0x80057C08
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppSetDeltaSlot(int slot, long deltaTime)
{
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_baseTime != -0x1000 && m_pppMng[i].m_paramA == slot) {
            m_pppMng[i].m_deltaTime = deltaTime;
        }
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
    for (int i = 0; i < 0x180; i++) {
        if (m_pppMng[i].m_baseTime != -0x1000 && m_pppMng[i].m_paramA == slot) {
            m_pppMng[i].m_position = *position;
        }
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
    unsigned char mode;
    int baseTime;

    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = &m_pppMng[i];
        baseTime = pppMngSt->m_baseTime;
        if (baseTime != -0x1000) {
            mode = pppMngSt->m_matrixMode;
            if (mode == 3 || static_cast<unsigned char>(mode - 5) <= 2 || mode == 8) {
                CGObject* owner = pppMngSt->m_owner;
                if (owner != 0 &&
                    owner->m_charaModelHandle == handle) {
                    if (baseTime < 0) {
                        pppMngSt->m_hitBgFlag = 1;
                        pppStopSe(
                            pppMngSt,
                            &pppMngSt->m_soundEffectData);
                    } else {
                        pppMngSt->m_baseTime = -0x1000;
                    }
                }
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndCHandle(CCharaPcs::CHandle* handle)
{
    for (int i = 0; i < 0x180; i++) {
        _pppMngSt* pppMngSt = &m_pppMng[i];
        if (pppMngSt->m_baseTime != -0x1000) {
            unsigned char mode = pppMngSt->m_matrixMode;
            if (mode == 3 || static_cast<unsigned char>(mode - 5) <= 2 || mode == 8) {
                CGObject* owner = pppMngSt->m_owner;
                if (owner != 0 &&
                    owner->m_charaModelHandle == handle) {
                    pppMngSt->m_particleEnded = 1;
                    pppStopSe(
                        pppMngSt,
                        &pppMngSt->m_soundEffectData);
                }
            }
        }
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
    PPPSEST* soundEffectData = &m_soundEffectData;
    PPPIFPARAM* hitParams = &m_hitParams;

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
