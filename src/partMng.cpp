#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/chunkfile.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/file.h"
#include "ffcc/gobject.h"
#include "ffcc/graphic.h"
#include "ffcc/map.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/p_map.h"
#include "ffcc/p_usb.h"
#include "ffcc/p_tina.h"
#include "ffcc/USBStreamData.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/pppfunctbl.h"
#include "ffcc/pppShape.h"
#include "ffcc/linkage.h"
extern "C" {
extern int gPppCalcDisabled;
extern unsigned char gPppInConstructor;
extern float gPartScreenMatrixRow2X;
extern float gPartScreenMatrixRow2Y;
extern float gPartScreenMatrixRow2W;
extern int gPppHeapUseRateWords[3];
}
#include "ffcc/stopwatch.h"

#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" void Printf__7CSystemFPce(CSystem*, const char*, ...);
extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void _WaitDrawDone__8CGraphicFPci(CGraphic*, const char*, int);
extern "C" void pppCreateHeap__FP9_pppEnvStUl(_pppEnvSt*, unsigned long);
extern "C" unsigned int CheckSum__FPvi(void*, int);
extern "C" void pppStopSe__FP9_pppMngStP7PPPSEST(_pppMngSt*, PPPSEST*);
extern "C" void _pppAllFreePObject__FP9_pppMngSt(_pppMngSt*);
extern "C" unsigned long pppHeapCheckLeak__FPQ27CMemory6CStage2(CMemory::CStage*);
extern "C" {
float ppvScreenMatrix[10][4];
float ppvScreenMatrix0[4][4];
float ppvCameraMatrix02[3][4];
float ppvChrScl[4];
Mtx ppvUnitMatrix;
Vec ppvZeroVector;
}
CAmemCacheSet ppvAmemCacheSet;
extern "C" float FLOAT_8032fe5c;
extern "C" float FLOAT_8032fe60;
extern "C" float FLOAT_8032fe64;
extern "C" float FLOAT_8032fe68;
extern "C" float FLOAT_8032fe70;
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
extern "C" float FLOAT_8032fe18;
extern "C" float FLOAT_8032fe74;
extern "C" float FLOAT_8032fe78;
extern "C" float FLOAT_8032fe7c;
extern "C" double DOUBLE_8032fe80;
extern "C" void SendDataCode__7CUSBPcsFiPvii(CUSBPcs*, int, void*, int, int);
extern "C" void GXPeekZ(u16, u16, u32*);
extern "C" void __ct__9_pppMngStFv(_pppMngSt* pppMngSt);
extern "C" void __ct__10pppShapeStFv(pppShapeSt* shapeSt);
extern "C" void __dt__10pppShapeStFv(pppShapeSt* shapeSt, int);
extern "C" void __ct__10pppModelStFv(pppModelSt* modelSt);
extern "C" void __dt__10pppModelStFv(pppModelSt* modelSt, int);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void __destroy_arr(void*, void*, unsigned long, unsigned long);
extern "C" void pppDestroyHeap__FP9_pppEnvSt(_pppEnvSt*);
extern "C" void __dt__Q29CCharaPcs7CHandleFv(void*, int);
extern "C" void _GXSetBlendMode__F12_GXBlendMode14_GXBlendFactor14_GXBlendFactor10_GXLogicOp(int, int, int, int);
extern "C" void _GXSetAlphaCompare__F10_GXCompareUc10_GXAlphaOp10_GXCompareUc(int, int, int, int, int);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _pppDrawPart__FP9_pppMngSt(_pppMngSt*);
extern "C" void Create__9CGBaseObjFv(CGBaseObj*);
extern "C" void LoadMap__7CMapPcsFiiPvUlUc(void*, int, int, void*, unsigned long, unsigned char);
extern "C" int SearchNodeSk__Q26CChara6CModelFPc(CChara::CModel*, char*);
extern "C" void SetFrame__Q26CChara6CModelFf(float, CChara::CModel*);
extern "C" void CalcMatrix__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void CalcSkin__Q26CChara6CModelFv(CChara::CModel*);
extern "C" void* __nw__11CTextureSetFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" CTextureSet* __ct__11CTextureSetFv(CTextureSet*);
extern "C" void Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(
    CTextureSet*, void*, CMemory::CStage*, int, CAmemCacheSet*, int, int);
extern "C" void* __nw__12CMaterialSetFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" CMaterialSet* __ct__12CMaterialSetFv(CMaterialSet*);
extern "C" void SetPartFromTextureSet__12CMaterialSetFP11CTextureSeti(CMaterialSet*, CTextureSet*, int);
extern "C" void SetTextureSet__12CMaterialSetFP11CTextureSet(CMaterialSet*, CTextureSet*);
extern "C" void* __nw__9CMaterialFUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" CMaterial* __ct__9CMaterialFv(CMaterial*);
extern "C" void Create__9CMaterialFUlQ212CMaterialMan7TEV_BIT(CMaterial*, unsigned long, unsigned long);
extern "C" void AddMaterial__12CMaterialSetFP9CMateriali(CMaterialSet*, CMaterial*, int);
CProfile g_par_calc_prof(0);
CProfile g_par_draw_prof(0);
PPPCREATEPARAM g_dcp;
extern "C" {
unsigned char DAT_8032ed68 = 0;
int DAT_8032ed6c = 0;
int DAT_8032ed74 = 0;
float gPartScreenMatrixRow2X = 0.0f;
float gPartScreenMatrixRow2Y = 0.0f;
float gPartScreenMatrixRow2W = 0.0f;
unsigned char gPppInConstructor = 0;
unsigned char gPppInSubFrameCalc = 0;
int DAT_8032ed7c = 0;
unsigned char DAT_8032ed90 = 0;
unsigned char DAT_8032ed91 = 0;
int gPppCalcDisabled = 0;
}
CPartMng PartMng;
static char s_partMng_cpp_801d8230[] = "partMng.cpp";
static char s_pppGetFreePppDataMngSt_CAN_NOT_ALLOC[] = "pppGetFreePppDataMngSt CAN NOT ALLOC!!\n";
static char s_CheckSum_ERROR_code_0x_x____801d82f0[] = "CheckSum ERROR code[0x%x]!!!";
static char s__________________________________801d8358[] = "----------------------------------\n";
static char s_prioTime__d_prio__d_heapSize__d_p_801d8454[] =
    "  prioTime=%d  prio=%d  heapSize=%d  pdtID=%2d  fpno=%3d   mngNo=%d  %s\n";
static char s_HEAP_TOTAL__dKbyte_USE__dKbyte_F_801d84a0[] =
    "HEAP TOTAL=%dKbyte  USE=%dKbyte  FREE=%dKbyte\n";

struct CPtrArrayBare {
    void* m_vtable;
    unsigned long m_size;
    unsigned long m_numItems;
    unsigned long m_defaultSize;
    void* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
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
    *(short*)((char*)this + 0x64) = 0;
    *(unsigned char*)((char*)this + 0x68) = 0;
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
    gPppCalcDisabled = 0;
    DAT_8032ed74 = 0;

    if (Game.m_currentSceneId == 7) {
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

    gPppInConstructor = 0;
    gPppInSubFrameCalc = 0;

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

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    PartMngResRaw* res = reinterpret_cast<PartMngResRaw*>(self);

    for (int i = 0; i < 0x20; i++) {
        pppReleasePdt(i);
    }

    if (res->m_pppModelStArr != 0) {
        for (unsigned int i = 0; i < 0x100; i++) {
            pppModelSt* model = &res->m_pppModelStArr[i];
            if (model->m_isUsed != 0) {
                model->m_refCount--;
                if (model->m_refCount < 1) {
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
        __destroy_arr(res->m_pppModelStArr, reinterpret_cast<void*>(__dt__10pppModelStFv), 0x6c, 0x100);
        __dl__FPv(res->m_pppModelStArr);
        res->m_pppModelStArr = 0;
    }

    if (res->m_pppShapeStArr != 0) {
        for (unsigned int i = 0; i < 0x100; i++) {
            pppShapeSt* shape = &res->m_pppShapeStArr[i];
            if (shape->m_inUse != 0) {
                shape->m_refCount--;
                if (shape->m_refCount < 1) {
                    if (shape->m_animData != 0) {
                        __dl__FPv(shape->m_animData);
                        shape->m_animData = 0;
                    }
                    if (shape->m_displayListData != 0) {
                        __dl__FPv(shape->m_displayListData);
                        shape->m_displayListData = 0;
                    }
                    shape->m_refCount = 0;
                    shape->m_inUse = 0;
                }
            }
        }
        __destroy_arr(res->m_pppShapeStArr, reinterpret_cast<void*>(__dt__10pppShapeStFv), 0x2c, 0x100);
        __dl__FPv(res->m_pppShapeStArr);
        res->m_pppShapeStArr = 0;
    }

    if (res->m_textureSet != 0) {
        CRefRaw* textureSet = reinterpret_cast<CRefRaw*>(res->m_textureSet);
        textureSet->m_refCount--;
        if (textureSet->m_refCount == 0) {
            reinterpret_cast<void (*)(void*, int)>(textureSet->m_vtable[2])(textureSet, 1);
        }
        res->m_textureSet = 0;
    }

    if (res->m_materialSet != 0) {
        CRefRaw* materialSet = reinterpret_cast<CRefRaw*>(res->m_materialSet);
        materialSet->m_refCount--;
        if (materialSet->m_refCount == 0) {
            reinterpret_cast<void (*)(void*, int)>(materialSet->m_vtable[2])(materialSet, 1);
        }
        res->m_materialSet = 0;
    }

    if (res->m_editorObj != 0) {
        void* handle = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(res->m_editorObj) + 0xf8);
        if (handle != 0) {
            __dt__Q29CCharaPcs7CHandleFv(handle, 1);
            *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(res->m_editorObj) + 0xf8) = 0;
        }
        __dl__FPv(res->m_editorObj);
        res->m_editorObj = 0;
    }

    pppDestroyHeap__FP9_pppEnvSt(reinterpret_cast<_pppEnvSt*>(self + 0x2351c));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDumpMngSt()
{
    struct PppPdtSlotRaw {
        _pppDataHead* m_pdt;
        unsigned int m_envFields[5];
        char m_name[0x20];
    };

    struct PppMngStDumpRaw {
        void* m_pppResSet;                 // 0x00
        unsigned char m_pad04[0x74 - 0x4];
        short m_kind;                      // 0x74
        short m_nodeIndex;                 // 0x76
        unsigned char m_pad78[0xAC - 0x78];
        int m_prioTime;                    // 0xAC
        unsigned char m_padB0[0xF8 - 0xB0];
        unsigned char m_prio;              // 0xF8
        unsigned char m_padF9[0x12C - 0xF9];
        int m_heapGroupRef;                // 0x12C
    };

    unsigned long heapTotal;
    unsigned long heapUse;
    unsigned long heapFree;
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    PppPdtSlotRaw* pdtSlots = reinterpret_cast<PppPdtSlotRaw*>(self + 0x22E18);

    if (System.m_execParam != 0) {
        Printf__7CSystemFPce(&System, s__________________________________801d8358);
    }

    PppMngStDumpRaw* mng = reinterpret_cast<PppMngStDumpRaw*>(self + 0x1D4);
    for (int i = 0; i < 0x180; i++) {
        if (mng->m_prioTime != -0x1000 && System.m_execParam != 0) {
            int kind = static_cast<int>(mng->m_kind);
            int heapGroup = (mng->m_heapGroupRef + 0x2D) / 0x158;
            int heapSize = pppEnvStPtr->m_stagePtr->heapWalker(0, 0, static_cast<unsigned long>(heapGroup));

            Printf__7CSystemFPce(
                &System, s_prioTime__d_prio__d_heapSize__d_p_801d8454, mng->m_prioTime,
                mng->m_prio, heapSize, kind, static_cast<int>(mng->m_nodeIndex), heapGroup,
                pdtSlots[kind].m_name);
        }

        mng = reinterpret_cast<PppMngStDumpRaw*>(reinterpret_cast<unsigned char*>(mng) + 0x158);
    }

    pppEnvStPtr->m_stagePtr->heapInfo(heapTotal, heapUse, heapFree);

    if (System.m_execParam != 0) {
        Printf__7CSystemFPce(
            &System, s_HEAP_TOTAL__dKbyte_USE__dKbyte_F_801d84a0,
            static_cast<int>(heapTotal >> 10), static_cast<int>(heapUse >> 10),
            static_cast<int>(heapFree >> 10));
        Printf__7CSystemFPce(&System, s__________________________________801d8358);
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
    struct PppPdtSlotRaw {
        _pppDataHead* m_pppDataHead;
        unsigned int m_envFields[5];
        char m_name[0x20];
    };

    struct PppMngStRaw {
        void* m_pppResSet;
        char m_unused[0x154];
    };

    struct PartMngResRaw {
        char m_unused[0x7e4];
        CMaterialSet* m_materialSet;
        CTextureSet* m_textureSet;
    };

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    PppPdtSlotRaw* pdtSlots = reinterpret_cast<PppPdtSlotRaw*>(self + 0x22e18);
    PppPdtSlotRaw* pdtSlot = &pdtSlots[pdtSlotIndex];
    _pppDataHead* pdt = pdtSlot->m_pppDataHead;

    if (pdt == 0) {
        return;
    }

    PartMngResRaw* res = reinterpret_cast<PartMngResRaw*>(self);
    _WaitDrawDone__8CGraphicFPci(&Graphic, s_partMng_cpp_801d8230, 0x158);
    res->m_materialSet->ReleaseTag(res->m_textureSet, pdtSlotIndex, &ppvAmemCacheSet);
    _WaitDrawDone__8CGraphicFPci(&Graphic, s_partMng_cpp_801d8230, 0x13a);

    pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(pdtSlot->m_envFields);
    PppMngStRaw* pppMngSt = reinterpret_cast<PppMngStRaw*>(self + 0x1d4);
    for (int i = 0; i < 0x180; i++) {
        if (pppMngSt[i].m_pppResSet == pdtSlot) {
            _pppAllFreePObject__FP9_pppMngSt(reinterpret_cast<_pppMngSt*>(&pppMngSt[i]));
        }
    }

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_partMng_cpp_801d8230, 0x149);

    pppModelSt** modelNames = reinterpret_cast<pppModelSt**>(pdt->m_modelNames);
    for (int i = 0; i < pdt->m_modelCount; i++) {
        pppModelSt* model = modelNames[i];
        model->m_refCount--;
        if (model->m_refCount < 1) {
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

    if (modelNames != 0) {
        __dla__FPv(modelNames);
        pdt->m_modelNames = 0;
    }

    pppShapeSt** shapeNames = reinterpret_cast<pppShapeSt**>(pdt->m_shapeNames);
    for (int i = 0; i < pdt->m_shapeCount; i++) {
        pppShapeSt* shape = shapeNames[i];
        shape->m_refCount--;
        if (shape->m_refCount < 1) {
            if (shape->m_animData != 0) {
                __dl__FPv(shape->m_animData);
                shape->m_animData = 0;
            }
            if (shape->m_displayListData != 0) {
                __dl__FPv(shape->m_displayListData);
                shape->m_displayListData = 0;
            }
            shape->m_refCount = 0;
            shape->m_inUse = 0;
        }
    }

    if (shapeNames != 0) {
        __dla__FPv(shapeNames);
        pdt->m_shapeNames = 0;
    }

    unsigned char* shapeGroups = reinterpret_cast<unsigned char*>(pdt->m_shapeGroups);
    for (int i = 0; i < pdt->m_shapeGroupCount; i++) {
        void** groupData = reinterpret_cast<void**>(shapeGroups + i * 8 + 4);
        if (*groupData != 0) {
            __dl__FPv(*groupData);
            *groupData = 0;
        }
    }

    if (shapeGroups != 0) {
        __dla__FPv(shapeGroups);
        pdt->m_shapeGroups = 0;
    }

    unsigned char* cacheChunks = reinterpret_cast<unsigned char*>(pdt->m_cacheChunks);
    for (int i = 0; i < pdt->m_cacheChunkCount; i++) {
        short cacheId = *reinterpret_cast<short*>(cacheChunks + i * 8);
        ppvAmemCacheSet.DestroyCache(cacheId);
    }

    if (cacheChunks != 0) {
        __dl__FPv(cacheChunks);
        pdt->m_cacheChunks = 0;
    }

    __dl__FPv(pdtSlot->m_pppDataHead);
    pdtSlot->m_pppDataHead = 0;

    _WaitDrawDone__8CGraphicFPci(&Graphic, s_partMng_cpp_801d8230, 0x182);
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
    pppSetBlendMode(3);

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
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
    GXLoadPosMtxImm(ppvCameraMatrix0, 0);
    pppSetBlendMode(3);

    float* cursorPos = reinterpret_cast<float*>(reinterpret_cast<unsigned char*>(this) + 0x23780);
    float x = cursorPos[0];
    float y = cursorPos[1];
    float z = cursorPos[2];

    _GXColor colorX;
    colorX.r = 0xff;
    colorX.g = 0x80;
    colorX.b = 0x80;
    colorX.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, colorX);
    GXSetChanMatColor((GXChannelID)4, colorX);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x - FLOAT_8032fe70, y, z);
    GXPosition3f32(x + FLOAT_8032fe70, y, z);

    _GXColor colorY;
    colorY.r = 0x80;
    colorY.g = 0xff;
    colorY.b = 0x80;
    colorY.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, colorY);
    GXSetChanMatColor((GXChannelID)4, colorY);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x, y - FLOAT_8032fe70, z);
    GXPosition3f32(x, y + FLOAT_8032fe70, z);

    _GXColor colorZ;
    colorZ.r = 0xff;
    colorZ.g = 0xff;
    colorZ.b = 0x80;
    colorZ.a = 0xff;
    GXSetChanAmbColor((GXChannelID)4, colorZ);
    GXSetChanMatColor((GXChannelID)4, colorZ);
    GXBegin(GX_LINES, GX_VTXFMT5, 2);
    GXPosition3f32(x, y, z - FLOAT_8032fe70);
    GXPosition3f32(x, y, z + FLOAT_8032fe70);
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
        int cursorX;
        int cursorY;
    };

    int zAtPixel;
    Vec viewPos;
    Vec worldPos;
    Mtx invCamera;
    PartMngMouseRaw* raw = reinterpret_cast<PartMngMouseRaw*>(this);

    if (raw->requestFlag != 0) {
        unsigned int x = raw->cursorX + 0x140;
        unsigned int y = raw->cursorY + 0xE0;
        if ((-1 < (int)x) && ((int)x < 0x27E) && (-1 < (int)y) && ((int)y < 0x1BE)) {
            _WaitDrawDone__8CGraphicFPci(&Graphic, s_partMng_cpp_801d8230, 0x2A2);
            GXPeekZ(static_cast<u16>(x & 0xFFFF), static_cast<u16>(y & 0xFFFF), reinterpret_cast<u32*>(&zAtPixel));

            viewPos.z = ppvScreenMatrix0[2][3]
                        / ((float)((double)(zAtPixel - 0xFFFFFF) / FLOAT_8032fe78) + ppvScreenMatrix0[2][2]);
            viewPos.x = viewPos.z * (((float)((double)raw->cursorX / FLOAT_8032fe7c)) / ppvScreenMatrix0[0][0]);
            viewPos.y = viewPos.z * ((-(float)((double)raw->cursorY / FLOAT_8032fe74)) / ppvScreenMatrix0[1][1]);
            viewPos.z = -viewPos.z;

            PSMTXInverse(ppvCameraMatrix0, invCamera);
            PSMTXMultVec(invCamera, &viewPos, &worldPos);
            SendDataCode__7CUSBPcsFiPvii(&USBPcs, 0x60, &worldPos, 1, 0xC);
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
    gPppHeapUseRateWords[0] = pppHeapCheckLeak__FPQ27CMemory6CStage2(pppEnvStPtr->m_stagePtr);
    if ((gPppHeapUseRateWords[2] == 0)
        || ((gPppHeapUseRateWords[2] = gPppHeapUseRateWords[2] - 1), gPppHeapUseRateWords[1] < gPppHeapUseRateWords[0])) {
        gPppHeapUseRateWords[2] = *(int*)((char*)this + 0x16C) << 1;
        gPppHeapUseRateWords[1] = gPppHeapUseRateWords[0];
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
        unsigned char m_pad04[0x14 - 0x04];
        int m_baseTime;                      // 0x14
        float m_rotationX;                   // 0x18
        float m_rotationZ;                   // 0x1C
        int m_rotationSpeed;                 // 0x20
        unsigned char m_pad24[0x28 - 0x24];
        Vec m_scale;                         // 0x28
        unsigned char m_pad34[0x40 - 0x34];
        float m_scaleFactor;                 // 0x40
        float m_ownerScale;                  // 0x44
        float m_userFloat0;                  // 0x48
        float m_userFloat1;                  // 0x4C
        unsigned char m_pad50[0x76 - 0x50];
        short m_nodeIndex;                   // 0x76
        unsigned char m_pad78[0xBC - 0x78];
        unsigned int m_objHitMask;           // 0xBC
        unsigned int m_cylinderAttribute;    // 0xC0
        unsigned char m_padC4[0xD8 - 0xC4];
        void* m_owner;                       // 0xD8
        void* m_lookTarget;                  // 0xDC
        void* m_bindNode;                    // 0xE0
        unsigned char m_padE4[0xEB - 0xE4];
        unsigned char m_matrixMode;          // 0xEB
        unsigned char m_drawPass;            // 0xED
        signed char m_drawSubType;           // 0xEE
        unsigned char m_drawVariant;         // 0xEF
        unsigned char m_rotationOrder;       // 0xF0
        unsigned char m_ownerFlagsInitialized; // 0xF1
        unsigned char m_fieldF2;             // 0xF2
        unsigned char m_useOwnerScaleSign;   // 0xF3
        unsigned char m_ownerFlagA;          // 0xF4
        unsigned char m_ownerFlagB;          // 0xF5
        unsigned char m_padF6[0xF9 - 0xF6];
        unsigned char m_fpBillboard;         // 0xF9
        unsigned char m_prio;                // 0xFA
        unsigned char m_padFB[0x100 - 0xFB];
        unsigned int m_paramA;               // 0x100
        unsigned int m_paramB;               // 0x104
        float m_cullRadiusSq;                // 0x108
        float m_cullRadius;                  // 0x10C
        float m_cullYOffset;                 // 0x110
        unsigned char m_pad114[0x11A - 0x114];
        short m_mapObjIndex;                 // 0x11A
    };

    static const int kUsbEditOffset = 0x7F0;
    static const int kResSetOffset = 0x23518;
    static const int kRecvBuffOffset = 0x23554;
    static const int kEditCountOffset = 0x2355C;
    static const int kPppMngOffset = 0x2A18;
    static const int kPacketStride = 0x60;

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    int editCount = *reinterpret_cast<int*>(self + kEditCountOffset);
    float* recvBuff = *reinterpret_cast<float**>(self + kRecvBuffOffset);
    PppMngSetFpRaw* mng = reinterpret_cast<PppMngSetFpRaw*>(self + kPppMngOffset);
    for (int i = 0; i < editCount; i++) {
        unsigned char* fpBytes = reinterpret_cast<unsigned char*>(recvBuff);
        mng->m_pppResSet = self + kResSetOffset;

        int fpTime = static_cast<int>(recvBuff[0x0B]);
        if (mng->m_baseTime < 0) {
            mng->m_baseTime = fpTime;
        } else {
            int scaled = (fpTime * 0x19) / 0x1E + ((fpTime * 0x19) >> 0x1F);
            mng->m_baseTime = scaled - (scaled >> 0x1F);
        }

        mng->m_cullRadiusSq = recvBuff[0x0D];
        if (mng->m_cullRadiusSq > 0.0f) {
            mng->m_cullRadiusSq *= mng->m_cullRadiusSq;
        }
        mng->m_nodeIndex = static_cast<short>(i);
        mng->m_cullRadius = recvBuff[0x0E];
        mng->m_cullYOffset = recvBuff[0x0F];
        mng->m_rotationX = recvBuff[4];
        mng->m_rotationZ = recvBuff[5];
        mng->m_rotationSpeed = static_cast<int>(recvBuff[6]);
        mng->m_scale.x = recvBuff[8];
        mng->m_scale.y = recvBuff[9];
        mng->m_scale.z = recvBuff[0x0A];
        mng->m_ownerScale = FLOAT_8032fe18;
        mng->m_scaleFactor = FLOAT_8032fe18;
        mng->m_userFloat1 = FLOAT_8032fe18;
        mng->m_userFloat0 = FLOAT_8032fe18;
        mng->m_useOwnerScaleSign = 0;
        mng->m_matrixMode = *reinterpret_cast<unsigned char*>(fpBytes + 0x45);
        mng->m_drawVariant = *reinterpret_cast<unsigned char*>(fpBytes + 0x46);
        mng->m_rotationOrder = *reinterpret_cast<unsigned char*>(fpBytes + 0x47);
        mng->m_drawPass = *reinterpret_cast<unsigned char*>(fpBytes + 0x44);
        mng->m_drawSubType = *reinterpret_cast<signed char*>(fpBytes + 0x4C);
        mng->m_ownerFlagA = *reinterpret_cast<unsigned char*>(fpBytes + 0x4D);
        mng->m_ownerFlagB = *reinterpret_cast<unsigned char*>(fpBytes + 0x4E);
        mng->m_fieldF2 = 1;
        mng->m_fpBillboard = *reinterpret_cast<unsigned char*>(fpBytes + 0x4A);
        mng->m_prio = *reinterpret_cast<unsigned char*>(fpBytes + 0x4B);
        mng->m_mapObjIndex = *reinterpret_cast<short*>(fpBytes + 0x48);
        mng->m_owner = 0;
        mng->m_objHitMask = 0xFFFFFFFF;
        mng->m_cylinderAttribute = 0xFFFFFFFF;
        mng->m_paramA = 0;
        mng->m_ownerFlagsInitialized = 1;
        mng->m_ownerFlagA = 1;

        unsigned char mode = mng->m_matrixMode;
        if (mode == 2 || mode == 4) {
            mng->m_mapObjIndex = static_cast<short>(MapMng.GetMapObjEffectIdx(*reinterpret_cast<unsigned short*>(fpBytes + 0x48)));
        } else if (mode >= 3 && mode <= 8) {
            CGObject* owner = *reinterpret_cast<CGObject**>(self + kUsbEditOffset + 0x1C);
            mng->m_ownerFlagA = 0;
            mng->m_owner = owner;
            mng->m_lookTarget = owner;
            if (owner != 0 && owner->m_charaModelHandle != 0 && owner->m_charaModelHandle->m_model != 0) {
                int node = SearchNodeSk__Q26CChara6CModelFPc(owner->m_charaModelHandle->m_model,
                                                             reinterpret_cast<char*>(fpBytes + 0x50));
                if (node >= 0) {
                    mng->m_bindNode = reinterpret_cast<void*>(
                        *reinterpret_cast<int*>(*reinterpret_cast<int*>(
                            reinterpret_cast<unsigned char*>(owner->m_charaModelHandle->m_model) + 0xA8) +
                                                node * 0xC0));
                }
            }
        }

        recvBuff = reinterpret_cast<float*>(fpBytes + kPacketStride);
        mng = reinterpret_cast<PppMngSetFpRaw*>(reinterpret_cast<unsigned char*>(mng) + sizeof(_pppMngSt));
    }
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
void CPartMng::pppReadRsd(CChunkFile& chunkFile, pppModelSt* modelSt)
{
    struct PartMngResRaw {
        unsigned char m_unk0[0x7e4];
        CMaterialSet* m_materialSet;
    };

    struct PartPcsRaw {
        unsigned char m_unk0[4];
        CUSBStreamData m_usbStreamData;
    };

    char* textureNames[0x101];
    CChunkFile::CChunk chunk;
    PartMngResRaw* res = reinterpret_cast<PartMngResRaw*>(this);
    PartPcsRaw* partPcs = reinterpret_cast<PartPcsRaw*>(&PartPcs);

    while (chunkFile.GetNextChunk(chunk)) {
        chunkFile.PushChunk();
        if (chunk.m_id == 'RSD ') {
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 'TXNM') {
                    for (unsigned int i = 0; i < chunk.m_arg0; i++) {
                        textureNames[i] = chunkFile.GetString();
                    }
                } else if (chunk.m_id == 'MESH') {
                    modelSt->ReadOtmMesh(chunkFile, partPcs->m_usbStreamData.m_stageLoad, 0, 0);
                    modelSt->SetDisplayListMaterial(res->m_materialSet, textureNames, 0);
                }
            }
        }
        chunkFile.PopChunk();
    }
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
	char* textureNames[20];
	char** textureNameIt = textureNames;
	CChunkFile::CChunk chunk;
	CMemory::CStage* stageLoad =
		*reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartPcs) + 0x1C);

	while (chunkFile.GetNextChunk(chunk))
	{
		chunkFile.PushChunk();
		if (chunk.m_id == 0x46534850) // 'FSHP'
		{
			while (chunkFile.GetNextChunk(chunk))
			{
				if (chunk.m_id == 0x444C5354) // 'DLST'
				{
					shapeSt->m_displayListData =
						__nwa__FUlPQ27CMemory6CStagePci(chunk.m_arg0, stageLoad, s_partMng_cpp_801d8230, 0x4B3);
					chunkFile.Get(shapeSt->m_displayListData, chunk.m_arg0);
					DCFlushRange(shapeSt->m_displayListData, (chunk.m_arg0 + 0x1F) & 0xFFFFFFE0);
				}
				else if ((int)chunk.m_id < 0x444C5354)
				{
					if (chunk.m_id == 0x414E494D) // 'ANIM'
					{
						shapeSt->m_animData =
							__nwa__FUlPQ27CMemory6CStagePci(chunk.m_arg0, stageLoad, s_partMng_cpp_801d8230, 0x4B9);
						chunkFile.Get(shapeSt->m_animData, chunk.m_arg0);
						pppSetShapeMaterial(shapeSt,
						                    *reinterpret_cast<CMaterialSet**>(reinterpret_cast<unsigned char*>(this) + 0x7E4),
						                    textureNames);
					}
				}
				else if (chunk.m_id == 0x54584E4D) // 'TXNM'
				{
					chunkFile.PushChunk();
					*textureNameIt = chunkFile.GetString();
					chunkFile.PopChunk();
					textureNameIt++;
				}
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
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditAllReleaseResource()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CMaterialSet* materialSet = *reinterpret_cast<CMaterialSet**>(self + 0x7E4);
    CTextureSet* textureSet = *reinterpret_cast<CTextureSet**>(self + 0x7E8);
    int iVar3;
    CMapMesh* mapMesh;
    int* piVar4;
    int iVar5;
    unsigned char* iter;

    if (materialSet != 0) {
        if (materialSet != 0) {
            reinterpret_cast<void (*)(void*, int)>((*reinterpret_cast<void***>(materialSet))[2])(materialSet, 1);
        }
        *reinterpret_cast<CMaterialSet**>(self + 0x7E4) = 0;
    }
    if (textureSet != 0) {
        if (textureSet != 0) {
            reinterpret_cast<void (*)(void*, int)>((*reinterpret_cast<void***>(textureSet))[2])(textureSet, 1);
        }
        *reinterpret_cast<CTextureSet**>(self + 0x7E8) = 0;
    }

    iVar3 = 0;
    iter = self;
    do {
        if (*reinterpret_cast<void**>(iter + 0x1D4) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(iter + 0x1D4));
            *reinterpret_cast<void**>(iter + 0x1D4) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0xC;
    } while (iVar3 < 0x80);

    iVar3 = 0;
    iter = self;
    do {
        if (*reinterpret_cast<void**>(iter + 0x1D8) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(iter + 0x1D8));
            *reinterpret_cast<void**>(iter + 0x1D8) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0xC;
    } while (iVar3 < 0x80);

    iVar3 = 0;
    iter = self;
    do {
        if (*reinterpret_cast<long**>(iter + 0x1DC) != 0) {
            __dl__FPv(*reinterpret_cast<long**>(iter + 0x1DC));
            *reinterpret_cast<long**>(iter + 0x1DC) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0xC;
    } while (iVar3 < 0x80);

    if (*reinterpret_cast<void**>(self + 0x23554) != 0) {
        __dla__FPv(*reinterpret_cast<void**>(self + 0x23554));
        *reinterpret_cast<void**>(self + 0x23554) = 0;
    }

    if (*reinterpret_cast<int*>(self + 0x7F4) != 0) {
        iVar5 = 0;
        iVar3 = 0;
        do {
            mapMesh = *reinterpret_cast<CMapMesh**>(*reinterpret_cast<int*>(self + 0x7F4) + iVar5);
            if (mapMesh != 0) {
                mapMesh->~CMapMesh();
                __dl__FPv(mapMesh);
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x7F4) + iVar5) = 0;
            }
            iVar3 = iVar3 + 1;
            iVar5 = iVar5 + 4;
        } while (iVar3 < 0x88);

        if (*reinterpret_cast<int*>(self + 0x7F4) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(self + 0x7F4));
            *reinterpret_cast<int*>(self + 0x7F4) = 0;
        }
    }

    if (*reinterpret_cast<int*>(self + 0x7F8) != 0) {
        iVar3 = 0;
        iVar5 = 0;
        do {
            piVar4 = *reinterpret_cast<int**>(*reinterpret_cast<int*>(self + 0x7F8) + iVar5);
            if (piVar4 != 0) {
                if (piVar4 != 0) {
                    if (*piVar4 != 0) {
                        __dl__FPv(reinterpret_cast<void*>(*piVar4));
                        *piVar4 = 0;
                    }
                    if (piVar4[1] != 0) {
                        __dl__FPv(reinterpret_cast<void*>(piVar4[1]));
                        piVar4[1] = 0;
                    }
                    __dl__FPv(piVar4);
                }
                *reinterpret_cast<int*>(*reinterpret_cast<int*>(self + 0x7F8) + iVar5) = 0;
            }
            iVar3 = iVar3 + 1;
            iVar5 = iVar5 + 4;
        } while (iVar3 < 0x80);

        if (*reinterpret_cast<int*>(self + 0x7F8) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(self + 0x7F8));
            *reinterpret_cast<int*>(self + 0x7F8) = 0;
        }
    }

    iVar3 = 0;
    iter = self;
    do {
        if (*reinterpret_cast<void**>(iter + 0x1D8) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(iter + 0x1D8));
            *reinterpret_cast<void**>(iter + 0x1D8) = 0;
        }
        iVar3 = iVar3 + 1;
        iter = iter + 0xC;
    } while (iVar3 < 0x80);

    if (*reinterpret_cast<int*>(self + 0x7FC) != 0) {
        __dl__FPv(*reinterpret_cast<void**>(self + 0x7FC));
        *reinterpret_cast<int*>(self + 0x7FC) = 0;
    }
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
        gPppCalcDisabled = 0;
        return;
    case 0x15:
        gPppCalcDisabled = 1;
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
        gPartScreenMatrixRow2X = ppvScreenMatrix[2][0];
        gPartScreenMatrixRow2Y = ppvScreenMatrix[2][1];
        gPartScreenMatrixRow2W = ppvScreenMatrix[2][3];
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
            &MapPcs,
            *reinterpret_cast<int*>(self + 0x188),
            *reinterpret_cast<int*>(self + 0x18c),
            0,
            0,
            0
        );
        *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MapPcs) + 0x180) = 1;
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

        CMemory::CStage* stageLoad =
            *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartPcs) + 0x1c);
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
        *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&MapPcs) + 0x180) =
            *reinterpret_cast<unsigned int*>(self + 0x1bc);
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
 * PAL Address: 0x8005b79c
 * PAL Size: 1060b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppEditPartCalc()
{
    struct PppPdtSlotRaw {
        _pppDataHead* m_pdt;
        int m_refCount;
        char m_name[0x30];
    };

    static const int kUsbEditOffset = 0x7F0;
    static const int kPppMngOffset = 0x2A18;
    static const int kPppMngCount = 0x180;
    static const int kPppMngStride = 0x158;
    static const int kPdtSlotsOffset = 0x22E18;

    char* self = reinterpret_cast<char*>(this);
    unsigned char* usbEdit = reinterpret_cast<unsigned char*>(self + kUsbEditOffset);
    CGObject* editorObj = *reinterpret_cast<CGObject**>(usbEdit + 0x1C);
    unsigned char* mng = reinterpret_cast<unsigned char*>(self + kPppMngOffset);
    PppPdtSlotRaw* pdtSlots = reinterpret_cast<PppPdtSlotRaw*>(self + kPdtSlotsOffset);

    OSStopStopwatch(&g_par_calc_prof);
    if (editorObj != 0 && editorObj->m_charaModelHandle != 0 && editorObj->m_charaModelHandle->m_model != 0) {
        CChara::CModel* model = editorObj->m_charaModelHandle->m_model;
        CalcMatrix__Q26CChara6CModelFv(model);
        CalcSkin__Q26CChara6CModelFv(model);
        SetFrame__Q26CChara6CModelFf(*reinterpret_cast<float*>(self + 0x23564), model);
        if (gPppCalcDisabled == 0) {
            *reinterpret_cast<float*>(self + 0x23564) += FLOAT_8032fe18;
        }
    }
    OSStartStopwatch(&g_par_calc_prof);

    if (usbEdit[0x18] != 0) {
        usbEdit[0x18] = 0;
        usbEdit[0x19] = 1;
        usbEdit[0x1A] = 0;

        Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0x3a9);
        for (int i = 0; i < kPppMngCount; i++) {
            if (*reinterpret_cast<int*>(mng + 0x14) != -0x1000) {
                _pppAllFreePObject(reinterpret_cast<_pppMngSt*>(mng));
            }
            mng += kPppMngStride;
        }

        *reinterpret_cast<int*>(self + 0x2355C) = 0;

        Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0x3b3);
        if (pdtSlots[0].m_pdt != 0) {
            unsigned char* firstMng = reinterpret_cast<unsigned char*>(self + kPppMngOffset);
            firstMng[0xE5] = 0;
            firstMng[0xA8] = *reinterpret_cast<unsigned char*>(self + 0x158);
            firstMng[0xA9] = *reinterpret_cast<unsigned char*>(self + 0x159);
            firstMng[0xAA] = *reinterpret_cast<unsigned char*>(self + 0x15A);
            firstMng[0xAB] = *reinterpret_cast<unsigned char*>(self + 0x15B);
            _pppStartPart(reinterpret_cast<_pppMngSt*>(firstMng), reinterpret_cast<long*>(pdtSlots[0].m_pdt), 1);
        }
    }

    if (DAT_8032ed68 != 0 || pdtSlots[0].m_pdt == 0) {
        return;
    }

    int editDrawMode = *reinterpret_cast<int*>(self + 0x23570);
    int loopCount = *reinterpret_cast<int*>(self + 0x2355C);
    if (loopCount > kPppMngCount) {
        loopCount = kPppMngCount;
    }

    mng = reinterpret_cast<unsigned char*>(self + kPppMngOffset);
    for (int i = 0; i < loopCount; i++) {
        int baseTime = *reinterpret_cast<int*>(mng + 0x14);
        pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
        if (baseTime == -0x1000) {
            mng += kPppMngStride;
            continue;
        }

        if (editDrawMode >= 4 && baseTime == -0x1000) {
            *reinterpret_cast<int*>(mng + 0x14) = 0;
            baseTime = 0;
        }

        if (baseTime >= 0) {
            baseTime -= 1;
            *reinterpret_cast<int*>(mng + 0x14) = baseTime;
            if (baseTime < 0) {
                mng[0xE5] = 0;
                mng[0xA8] = *reinterpret_cast<unsigned char*>(self + 0x158);
                mng[0xA9] = *reinterpret_cast<unsigned char*>(self + 0x159);
                mng[0xAA] = *reinterpret_cast<unsigned char*>(self + 0x15A);
                mng[0xAB] = *reinterpret_cast<unsigned char*>(self + 0x15B);
                _pppStartPart(reinterpret_cast<_pppMngSt*>(mng), reinterpret_cast<long*>(pdtSlots[0].m_pdt), 1);
            }
        }

        pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(*reinterpret_cast<char**>(mng) + 4);
        pppSetMatrix(reinterpret_cast<_pppMngSt*>(mng));
        pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));
        _pppCalcPart(reinterpret_cast<_pppMngSt*>(mng));
        _pppDeadPart(reinterpret_cast<_pppMngSt*>(mng));

        if (mng[0xE6] != 0 || mng[0xE4] != 0) {
            Graphic._WaitDrawDone(s_partMng_cpp_801d8230, (editDrawMode < 4) ? 0x827 : 0x861);
            _pppAllFreePObject(reinterpret_cast<_pppMngSt*>(mng));
            Graphic._WaitDrawDone(s_partMng_cpp_801d8230, (editDrawMode < 4) ? 0x82b : 0x865);
            if (editDrawMode > 3) {
                pppHeapCheckLeak(pppEnvStPtr->m_stagePtr);
            }
            if (i == 0) {
                usbEdit[0x1A] = 1;
            }
        }

        mng += kPppMngStride;
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
    struct PppPdtSlotRaw {
        _pppDataHead* m_pdt;
        int m_refCount;
        char m_name[0x30];
    };

    struct PppMngStDrawRaw {
        void* m_pppResSet;                   // 0x00
        int m_partIndex;                     // 0x04
        Vec m_position;                      // 0x08
        int m_baseTime;                      // 0x14
        unsigned char m_pad18[0x78 - 0x18]; // 0x18
        pppFMATRIX m_matrix;                 // 0x78
        unsigned char m_padA8[0xE4 - 0xA8]; // 0xA8
        unsigned char m_endRequested;        // 0xE4
        unsigned char m_stopRequested;       // 0xE5
        unsigned char m_isFinished;          // 0xE6
        unsigned char m_matrixMode;          // 0xE7
        unsigned char m_hitBgFlag;           // 0xE8
        unsigned char m_slotVisible;         // 0xE9
        unsigned char m_ownerFacing;         // 0xEA
        unsigned char m_drawVariant;         // 0xEB
        unsigned char m_rotationOrder;       // 0xEC
        unsigned char m_drawMode;            // 0xED
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
    };

    if (DAT_8032ed68 != 0) {
        return;
    }

    char* self = reinterpret_cast<char*>(this);
    PppPdtSlotRaw* pdtSlots = reinterpret_cast<PppPdtSlotRaw*>(self + 0x22E18);
    if (pdtSlots[0].m_pdt != 0 && *reinterpret_cast<int*>(self + 0x23570) < 4) {
        Mtx invCamera;
        Vec cameraPos;
        Vec partPos;
        Vec cameraDelta;
        Vec viewPos;

        PSMTXInverse(ppvCameraMatrix0, invCamera);
        cameraPos.x = invCamera[0][3];
        cameraPos.y = invCamera[1][3];
        cameraPos.z = invCamera[2][3];

        PppMngStDrawRaw* mng = reinterpret_cast<PppMngStDrawRaw*>(self + 0x2A18);
        for (int i = 0; i < 0x180; i++) {
            if (mng->m_endRequested == 0 && mng->m_baseTime != -0x1000 && mng->m_drawMode == 3 && mng->m_baseTime < 0
                && mng->m_slotVisible != 0 && mng->m_ownerVisible != 0) {
                partPos.x = mng->m_matrix.value[0][3];
                partPos.y = mng->m_matrix.value[1][3];
                partPos.z = mng->m_matrix.value[2][3];

                bool shouldDraw = (mng->m_cullRadiusSq == 0.0f);
                if (!shouldDraw) {
                    PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                    if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                        CBound bound;
                        Vec min;
                        min.x = partPos.x - mng->m_cullRadius;
                        min.y = partPos.y;
                        min.z = partPos.z - mng->m_cullRadius;
                        shouldDraw = (bound.CheckFrustum(min, ppvCameraMatrix0, partPos.y + mng->m_cullYOffset) != 0);
                    }
                }

                if (shouldDraw) {
                    PSMTXMultVec(ppvCameraMatrix0, &partPos, &viewPos);
                    mng->m_sortDepth = viewPos.z;
                    pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);
                    pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
                    pppSetFpMatrix(pppMngStPtr);
                    _pppDrawPart__FP9_pppMngSt(pppMngStPtr);
                }
            }
            mng++;
        }
    }

    ppvScreenMatrix[2][3] = gPartScreenMatrixRow2W;
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
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
                    pppSetFpMatrix(pppMngStPtr);
                    _pppDrawPart__FP9_pppMngSt(pppMngStPtr);
                }
            }

            mng += kPppMngStride;
        }
    }

    ppvScreenMatrix[2][3] = gPartScreenMatrixRow2W;
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
                    pppSetFpMatrix(pppMngStPtr);
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
    PSMTX44Copy(*reinterpret_cast<Mtx44*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x94), ppvScreenMatrix);
    PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 4), ppvCameraMatrix02);
    gPartScreenMatrixRow2X = ppvScreenMatrix[2][0];
    gPartScreenMatrixRow2Y = ppvScreenMatrix[2][1];
    gPartScreenMatrixRow2W = ppvScreenMatrix[2][3];
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
        unsigned char m_drawPass;       // 0xED
        signed char m_drawSubType;      // 0xEE
        unsigned char m_useOwnerScaleSign; // 0xEF
        unsigned char m_ownerFlagsInitialized; // 0xF0
        unsigned char m_nodeScaleInitialized;  // 0xF1
        unsigned char m_fieldF2;        // 0xF2
        unsigned char m_padF3[0xF6 - 0xF3];
        unsigned char m_hasMapRef;      // 0xF6
    };

    pppSetRendMatrix();

    PppMngStDumpRaw* mng = reinterpret_cast<PppMngStDumpRaw*>(reinterpret_cast<unsigned char*>(this) + 0x1D4);
    for (int i = 0; i < 0x180; i++) {
        if ((Game.m_gameWork.m_gamePaused == 0 || (mng->m_drawVariant > 5 && mng->m_drawVariant < 8)) &&
            mng->m_baseTime != -0x1000 && mng->m_endRequested == 0) {
            pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
            pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);

            if (mng->m_baseTime >= 0) {
                mng->m_baseTime--;
                if (mng->m_baseTime < 0) {
                    _pppDataHead* pdtHead = *reinterpret_cast<_pppDataHead**>(mng->m_pppResSet);
                    PppPartResourceRaw* partResource =
                        reinterpret_cast<PppPartResourceRaw*>(reinterpret_cast<unsigned char*>(pdtHead->m_cacheChunks) +
                                                              mng->m_partIndex * sizeof(PppPartResourceRaw));

                    CAmemCacheSet* cacheSet = &ppvAmemCacheSet;
                    if (cacheSet->IsEnable(partResource->m_cacheIndex) == 0) {
                        partResource->m_pdt = reinterpret_cast<long*>(
                            cacheSet->GetData(partResource->m_cacheIndex, s_partMng_cpp_801d8230, 0x9A9));
                        pppInitPdt(partResource->m_pdt, pppGetSysProgTable());
                    }

                    cacheSet->AddRef(partResource->m_cacheIndex);
                    mng->m_hasMapRef = 1;
                    _pppStartPart(reinterpret_cast<_pppMngSt*>(mng), partResource->m_pdt, 1);
                }
            }

            pppSetMatrix(reinterpret_cast<_pppMngSt*>(mng));
            pppSetFpMatrix(reinterpret_cast<_pppMngSt*>(mng));

            mng->m_spawnedCount += *reinterpret_cast<int*>(&mng->m_envColorR);
            gPppInSubFrameCalc = 0;

            while (mng->m_spawnedCount > 0xFFF) {
                _pppCalcPart(reinterpret_cast<_pppMngSt*>(mng));
                _pppDeadPart(reinterpret_cast<_pppMngSt*>(mng));
                if (mng->m_isFinished != 0) {
                    break;
                }

                gPppInSubFrameCalc = 1;
                mng->m_spawnedCount -= 0x1000;
            }

            gPppInSubFrameCalc = 0;
        }

        mng = reinterpret_cast<PppMngStDumpRaw*>(reinterpret_cast<unsigned char*>(mng) + 0x158);
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
    struct PppMngStDrawRaw {
        void* m_pppResSet;                   // 0x00
        int m_partIndex;                     // 0x04
        Vec m_position;                      // 0x08
        int m_baseTime;                      // 0x14
        unsigned char m_pad18[0x78 - 0x18]; // 0x18
        pppFMATRIX m_matrix;                 // 0x78
        unsigned char m_padA8[0xE4 - 0xA8]; // 0xA8
        unsigned char m_endRequested;        // 0xE4
        unsigned char m_stopRequested;       // 0xE5
        unsigned char m_isFinished;          // 0xE6
        unsigned char m_matrixMode;          // 0xE7
        unsigned char m_hitBgFlag;           // 0xE8
        unsigned char m_slotVisible;         // 0xE9
        unsigned char m_ownerFacing;         // 0xEA
        unsigned char m_drawVariant;         // 0xEB
        unsigned char m_rotationOrder;       // 0xEC
        unsigned char m_drawMode;            // 0xED
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
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec partPos;
    Vec cameraDelta;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix0, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    PppMngStDrawRaw* mng = reinterpret_cast<PppMngStDrawRaw*>(reinterpret_cast<unsigned char*>(this) + 0x2A18);
    for (int i = 0; i < 0x180; i++) {
        if (mng->m_endRequested == 0 && mng->m_baseTime != -0x1000
            && mng->m_drawMode == drawMode && mng->m_baseTime < 0
            && mng->m_slotVisible != 0 && mng->m_ownerVisible != 0) {
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            bool shouldDraw = (mng->m_cullRadiusSq == 0.0f);
            if (!shouldDraw) {
                PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                    CBound bound;
                    Vec min;
                    min.x = partPos.x - mng->m_cullRadius;
                    min.y = partPos.y;
                    min.z = partPos.z - mng->m_cullRadius;
                    shouldDraw = (bound.CheckFrustum(min, ppvCameraMatrix0, partPos.y + mng->m_cullYOffset) != 0);
                }
            }

            if (shouldDraw) {
                PSMTXMultVec(ppvCameraMatrix0, &partPos, &viewPos);
                mng->m_sortDepth = viewPos.z;
                pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);
                pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
                pppSetFpMatrix(pppMngStPtr);
                _pppDrawPart__FP9_pppMngSt(pppMngStPtr);
            }
        }
        mng++;
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
        unsigned char m_endRequested;        // 0xE4
        unsigned char m_stopRequested;       // 0xE5
        unsigned char m_isFinished;          // 0xE6
        unsigned char m_matrixMode;          // 0xE7
        unsigned char m_hitBgFlag;           // 0xE8
        unsigned char m_slotVisible;         // 0xE9
        unsigned char m_ownerFacing;         // 0xEA
        unsigned char m_drawVariant;         // 0xEB
        unsigned char m_rotationOrder;       // 0xEC
        unsigned char m_drawMode;            // 0xED
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
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec partPos;
    Vec cameraDelta;
    Vec viewPos;
    PppMngStDrawPdtRaw* mng;
    int remaining;

    PSMTXInverse(ppvCameraMatrix0, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    mng = reinterpret_cast<PppMngStDrawPdtRaw*>(m_pppMng);
    remaining = 0x180;
    while ((mng->m_nodeIndex != nodeIndex || mng->m_kind != kind || mng->m_endRequested != 0
            || mng->m_baseTime == -0x1000 || mng->m_drawMode != drawMode || mng->m_baseTime >= 0)) {
        mng++;
        remaining--;
        if (remaining == 0) {
            return;
        }
    }

    if (mng->m_slotVisible == 0) {
        return;
    }

    partPos.x = mng->m_matrix.value[0][3];
    partPos.y = mng->m_matrix.value[1][3];
    partPos.z = mng->m_matrix.value[2][3];
    pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);

    if ((double)mng->m_cullRadiusSq != 0.0) {
        CBound bound;
        Vec min;

        PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
        if (PSVECSquareMag(&cameraDelta) >= mng->m_cullRadiusSq) {
            return;
        }

        min.x = partPos.x - mng->m_cullRadius;
        min.y = partPos.y;
        min.z = partPos.z - mng->m_cullRadius;
        if (bound.CheckFrustum(min, ppvCameraMatrix0, partPos.y + mng->m_cullYOffset) == 0) {
            return;
        }
    }

    PSMTXMultVec(ppvCameraMatrix0, &partPos, &viewPos);
    mng->m_sortDepth = viewPos.z;
    pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);
    pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
    pppSetFpMatrix(pppMngStPtr);
    _pppDrawPart__FP9_pppMngSt(pppMngStPtr);
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
    Mtx invCamera;
    Vec cameraPos;
    Vec partPos;
    Vec cameraDelta;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix02, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    _pppMngSt* mng = reinterpret_cast<_pppMngSt*>(reinterpret_cast<unsigned char*>(this) + 0x2A18) + partIndex;
    if (mng->m_mode != 0) {
        return;
    }
    if (mng->m_baseTime == -0x1000) {
        return;
    }
    if (mng->m_baseTime >= 0) {
        return;
    }

    partPos.x = mng->m_matrix.value[0][3];
    partPos.y = mng->m_matrix.value[1][3];
    partPos.z = mng->m_matrix.value[2][3];
    pppMngStPtr = mng;

    if ((double)mng->m_cullRadiusSq != 0.0) {
        PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
        if (PSVECSquareMag(&cameraDelta) >= mng->m_cullRadiusSq) {
            return;
        }

        CBound bound;
        Vec min;
        min.x = partPos.x - mng->m_cullRadius;
        min.y = partPos.y;
        min.z = partPos.z - mng->m_cullRadius;
        if (bound.CheckFrustum(min, ppvCameraMatrix02, partPos.y + mng->m_cullYOffset) == 0) {
            return;
        }
    }

    PSMTXMultVec(ppvCameraMatrix02, &partPos, &viewPos);
    mng->m_sortDepth = viewPos.z;
    pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);
    pppMngStPtr = mng;
    pppSetFpMatrix(mng);
    _pppDrawPart__FP9_pppMngSt(mng);
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
    struct PppMngStDrawRaw {
        void* m_pppResSet;                   // 0x00
        int m_partIndex;                     // 0x04
        Vec m_position;                      // 0x08
        int m_baseTime;                      // 0x14
        unsigned char m_pad18[0x78 - 0x18]; // 0x18
        pppFMATRIX m_matrix;                 // 0x78
        unsigned char m_padA8[0xE4 - 0xA8]; // 0xA8
        unsigned char m_endRequested;        // 0xE4
        unsigned char m_stopRequested;       // 0xE5
        unsigned char m_isFinished;          // 0xE6
        unsigned char m_matrixMode;          // 0xE7
        unsigned char m_hitBgFlag;           // 0xE8
        unsigned char m_slotVisible;         // 0xE9
        unsigned char m_ownerFacing;         // 0xEA
        unsigned char m_drawVariant;         // 0xEB
        unsigned char m_rotationOrder;       // 0xEC
        unsigned char m_drawMode;            // 0xED
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
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec partPos;
    Vec cameraDelta;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix0, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    PppMngStDrawRaw* mng = reinterpret_cast<PppMngStDrawRaw*>(reinterpret_cast<unsigned char*>(this) + 0x1D4);
    for (int i = 0; i < 0x180; i++) {
        if (mng->m_endRequested == 0 && mng->m_baseTime != -0x1000 && mng->m_drawMode < 3 && mng->m_baseTime < 0
            && mng->m_slotVisible != 0 && mng->m_ownerVisible != 0) {
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            bool shouldDraw = (mng->m_cullRadiusSq == 0.0f);
            if (!shouldDraw) {
                PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                    CBound bound;
                    Vec min;
                    min.x = partPos.x - mng->m_cullRadius;
                    min.y = partPos.y;
                    min.z = partPos.z - mng->m_cullRadius;
                    shouldDraw = (bound.CheckFrustum(min, ppvCameraMatrix0, partPos.y + mng->m_cullYOffset) != 0);
                }
            }

            if (shouldDraw) {
                PSMTXMultVec(ppvCameraMatrix0, &partPos, &viewPos);
                mng->m_sortDepth = viewPos.z;

                if (mng->m_drawMode == 1) {
                    ppvDrawMng.AddPrimOt(0x3FF, reinterpret_cast<_pppMngSt*>(mng));
                } else if (mng->m_drawMode == 0) {
                    ppvDrawMng.AddPrim(viewPos.z, reinterpret_cast<_pppMngSt*>(mng), mng->m_drawSubType);
                } else if (mng->m_drawMode == 2) {
                    ppvDrawMng.AddPrimOt(0, reinterpret_cast<_pppMngSt*>(mng));
                }
            }
        }
        mng++;
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
    struct PppMngStDrawRaw {
        void* m_pppResSet;                   // 0x00
        int m_partIndex;                     // 0x04
        Vec m_position;                      // 0x08
        int m_baseTime;                      // 0x14
        unsigned char m_pad18[0x78 - 0x18]; // 0x18
        pppFMATRIX m_matrix;                 // 0x78
        unsigned char m_padA8[0xE4 - 0xA8]; // 0xA8
        unsigned char m_endRequested;        // 0xE4
        unsigned char m_stopRequested;       // 0xE5
        unsigned char m_isFinished;          // 0xE6
        unsigned char m_matrixMode;          // 0xE7
        unsigned char m_hitBgFlag;           // 0xE8
        unsigned char m_slotVisible;         // 0xE9
        unsigned char m_ownerFacing;         // 0xEA
        unsigned char m_drawVariant;         // 0xEB
        unsigned char m_rotationOrder;       // 0xEC
        unsigned char m_drawMode;            // 0xED
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
    };

    Mtx invCamera;
    Vec cameraPos;
    Vec partPos;
    Vec cameraDelta;
    Vec viewPos;

    PSMTXInverse(ppvCameraMatrix0, invCamera);
    cameraPos.x = invCamera[0][3];
    cameraPos.y = invCamera[1][3];
    cameraPos.z = invCamera[2][3];

    PppMngStDrawRaw* mng = reinterpret_cast<PppMngStDrawRaw*>(reinterpret_cast<unsigned char*>(this) + 0x1D4);
    for (int i = 0; i < 0x180; i++) {
        if (mng->m_endRequested == 0 && mng->m_baseTime != -0x1000 && mng->m_drawMode == 5 && mng->m_baseTime < 0
            && mng->m_slotVisible != 0 && mng->m_ownerVisible != 0) {
            partPos.x = mng->m_matrix.value[0][3];
            partPos.y = mng->m_matrix.value[1][3];
            partPos.z = mng->m_matrix.value[2][3];

            bool shouldDraw = (mng->m_cullRadiusSq == 0.0f);
            if (!shouldDraw) {
                PSVECSubtract(&cameraPos, &partPos, &cameraDelta);
                if (PSVECSquareMag(&cameraDelta) < mng->m_cullRadiusSq) {
                    CBound bound;
                    Vec min;
                    min.x = partPos.x - mng->m_cullRadius;
                    min.y = partPos.y;
                    min.z = partPos.z - mng->m_cullRadius;
                    shouldDraw = (bound.CheckFrustum(min, ppvCameraMatrix0, partPos.y + mng->m_cullYOffset) != 0);
                }
            }

            if (shouldDraw) {
                PSMTXMultVec(ppvCameraMatrix0, &partPos, &viewPos);
                mng->m_sortDepth = viewPos.z;
                pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(mng->m_pppResSet) + 4);
                pppMngStPtr = reinterpret_cast<_pppMngSt*>(mng);
                pppSetFpMatrix(pppMngStPtr);
                _pppDrawPart__FP9_pppMngSt(pppMngStPtr);
            }
        }
        mng++;
    }

    gPppHeapUseRateWords[0] = pppHeapCheckLeak__FPQ27CMemory6CStage2(pppEnvStPtr->m_stagePtr);
    if ((gPppHeapUseRateWords[2] == 0)
        || ((gPppHeapUseRateWords[2] = gPppHeapUseRateWords[2] - 1), gPppHeapUseRateWords[1] < gPppHeapUseRateWords[0])) {
        gPppHeapUseRateWords[2] = *(int*)((char*)this + 0x16C) << 1;
        gPppHeapUseRateWords[1] = gPppHeapUseRateWords[0];
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
    char* pppMngSt = reinterpret_cast<char*>(this);
    int i = 0;

    *reinterpret_cast<int*>(reinterpret_cast<char*>(this) + 0x8) = 0;
    do {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if (baseTime != -0x1000 && baseTime < 0) {
            _pppInitPart(reinterpret_cast<_pppMngSt*>(pppMngSt));
        }
        pppMngSt += 0x158;
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
        readBuffer = File.m_readBuffer;
        if (fileSize == 0) {
            readBuffer = 0;
        } else {
            Memory.CopyFromAMemorySync(
                File.m_readBuffer, reinterpret_cast<void*>(loadState->m_partAMemCursor), (fileSize + 0x1f) & ~0x1f);
            loadState->m_partAMemCursor += fileSize;
            CheckSum__FPvi(readBuffer, fileSize);
            loadState->m_partChunkIndex++;
        }
    } else if (readBuffer == 0 && (fileHandle = File.Open(filePath, 0, CFile::PRI_LOW), fileHandle == 0)) {
        readBuffer = 0;
    } else if (loadState->m_partLoadMode == 3) {
        File.ReadASync(fileHandle);
        readBuffer = reinterpret_cast<void*>(1);
        loadState->m_partAsyncBusy[loadState->m_asyncHandleCount] = fileHandle;
        loadState->m_asyncHandleCount++;
    } else {
        if (readBuffer == 0) {
            fileSize = File.GetLength(fileHandle);
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);
            readBuffer = File.m_readBuffer;
            File.Close(fileHandle);
        } else {
            fileSize = readBufferSize;
        }
        if (loadState->m_partLoadMode == 2) {
            Memory.CopyToAMemorySync(readBuffer, reinterpret_cast<void*>(loadState->m_partAMemCursor), fileSize);
            loadState->m_partChunkSize[loadState->m_partChunkIndex] = fileSize;
            loadState->m_partChunkChecksum[loadState->m_partChunkIndex] = CheckSum__FPvi(readBuffer, fileSize);
            loadState->m_partChunkIndex++;
            loadState->m_partAMemCursor += fileSize;
        }
    }

    return readBuffer;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::LoadPartNoSyncCalc()
{
    char* base = reinterpret_cast<char*>(this);
    char* slotBase = base;
    for (int i = 0; i < 0x10; i++) {
        CFile::CHandle** handleSlot = reinterpret_cast<CFile::CHandle**>(slotBase + 0x2378c);
        CFile::CHandle* handle = *handleSlot;
        if (handle != 0) {
            if (File.IsCompleted(handle)) {
                void* readBuffer = File.m_readBuffer;
                int len = File.GetLength(handle);
                void* amemCursor = *reinterpret_cast<void**>(base + 0x236f8);

                Memory.CopyToAMemorySync(readBuffer, amemCursor, (len + 0x1f) & ~0x1f);
                *reinterpret_cast<int*>(slotBase + 0x2370c) = len;
                *reinterpret_cast<unsigned int*>(slotBase + 0x2374c) = CheckSum__FPvi(readBuffer, len);
                (*reinterpret_cast<int*>(base + 0x23700))++;
                *reinterpret_cast<char**>(base + 0x236f8) += len;

                File.Close(handle);
                *handleSlot = 0;
            }
        }
        slotBase += 4;
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
    struct PartMngResRaw {
        unsigned char m_unk0[0x7e4];
        CMaterialSet* m_materialSet;
        CTextureSet* m_textureSet;
    };

    static const unsigned int kChunkTSET = 0x54534554;
    static const int kEnvOffset = 0x2351c;

    CMemory::CStage* stageLoad =
        *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartPcs) + 0x1c);
    PartMngResRaw* res = reinterpret_cast<PartMngResRaw*>(this);

    ppvAmemCacheSet.CacheClear();
    stageLoad->setDefaultParam(pdtSlotIndex);

    char path[256];
    sprintf(path, "%s.ptx", baseName);
    if (System.m_execParam > 2) {
        System.Printf("ReadPtx fn=[%s]\n", path);
    }

    unsigned long fileSize = 0;
    void* fileData = pppFileRead(path, fileSize, readBuffer, readBufferSize);
    if (fileData == 0) {
        if (System.m_execParam != 0) {
            System.Printf("CAN NOT READ[%s]!!\n", path);
        }
        stageLoad->resDefaultParam();
        return 0;
    }

    if (fileData == reinterpret_cast<void*>(1)) {
        stageLoad->resDefaultParam();
        return 1;
    }

    if (res->m_textureSet == 0) {
        CTextureSet* textureSet = static_cast<CTextureSet*>(
            __nw__11CTextureSetFUlPQ27CMemory6CStagePci(0x24, stageLoad, s_partMng_cpp_801d8230, 0xC10));
        if (textureSet != 0) {
            textureSet = __ct__11CTextureSetFv(textureSet);
        }
        res->m_textureSet = textureSet;
    }

    if (res->m_materialSet == 0) {
        CMaterialSet* materialSet = static_cast<CMaterialSet*>(
            __nw__12CMaterialSetFUlPQ27CMemory6CStagePci(0x24, stageLoad, s_partMng_cpp_801d8230, 0xC14));
        if (materialSet != 0) {
            materialSet = __ct__12CMaterialSetFv(materialSet);
        }
        res->m_materialSet = materialSet;
        reinterpret_cast<_pppEnvSt*>(reinterpret_cast<unsigned char*>(this) + kEnvOffset)->m_materialSetPtr =
            res->m_materialSet;

        CMaterial* defaultMaterial = static_cast<CMaterial*>(
            __nw__9CMaterialFUlPQ27CMemory6CStagePci(0xA8, stageLoad, s_partMng_cpp_801d8230, 0xC17));
        if (defaultMaterial != 0) {
            defaultMaterial = __ct__9CMaterialFv(defaultMaterial);
        }
        if (defaultMaterial != 0) {
            Create__9CMaterialFUlQ212CMaterialMan7TEV_BIT(defaultMaterial, 0, 0xFFF531F0);
            AddMaterial__12CMaterialSetFP9CMateriali(res->m_materialSet, defaultMaterial, 0);
        }
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id == kChunkTSET) {
            Create__11CTextureSetFPvPQ27CMemory6CStageiP13CAmemCacheSetii(
                res->m_textureSet, &chunkFile, stageLoad, 1, &ppvAmemCacheSet, appendMode, 0);
        }
    }

    SetPartFromTextureSet__12CMaterialSetFP11CTextureSeti(res->m_materialSet, res->m_textureSet, pdtSlotIndex);
    SetTextureSet__12CMaterialSetFP11CTextureSet(res->m_materialSet, res->m_textureSet);
    stageLoad->resDefaultParam();
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
void CPartMng::pppLoadPmd(const char* baseName)
{
    char path[256];
    unsigned long fileSize = 0;

    sprintf(path, "%s.pmd", baseName);
    if (System.m_execParam > 2) {
        System.Printf("ReadPmd fn=[%s]\n", path);
    }

    void* fileData = pppFileRead(path, fileSize, 0, 0);
    if (fileData == 0) {
        if (System.m_execParam != 0) {
            System.Printf("CAN NOT READ[%s]!!\n", path);
        }
        return;
    }

    pppModelSt** modelArrayPtr = reinterpret_cast<pppModelSt**>(reinterpret_cast<unsigned char*>(this) + 0x7ec);
    if (*modelArrayPtr == 0) {
        CMemory::CStage* stageLoad =
            *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartPcs) + 0x1c);
        pppModelSt* modelArray = reinterpret_cast<pppModelSt*>(
            __nw__FUlPQ27CMemory6CStagePci(0x6c00, stageLoad, s_partMng_cpp_801d8230, 0xca9));
        if (modelArray != 0) {
            __construct_array(modelArray, reinterpret_cast<void (*)(void*)>(__ct__10pppModelStFv),
                              reinterpret_cast<void (*)(void*, int)>(__dt__10pppModelStFv), 0x6c, 0x100);
            for (int i = 0; i < 0x100; i++) {
                modelArray[i].m_isUsed = 0;
            }
        }
        *modelArrayPtr = modelArray;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    CChunkFile::CChunk outerChunk;
    while (chunkFile.GetNextChunk(outerChunk)) {
        chunkFile.PushChunk();
        if (outerChunk.m_id == 0x52534554) {
            pppModelSt* modelArray = *modelArrayPtr;
            pppModelSt* targetModel = 0;

            CChunkFile::CChunk innerChunk;
            while (chunkFile.GetNextChunk(innerChunk)) {
                if (innerChunk.m_id == 0x5253444d) {
                    if (targetModel != 0) {
                        CChunkFile rsdFile;
                        rsdFile.SetBuf(chunkFile.GetAddress());
                        pppReadRsd(rsdFile, targetModel);
                        targetModel->Ptr2Off();

                        void** meshDataPtr =
                            reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(targetModel) + 0x24);
                        targetModel->m_cacheId = static_cast<short>(ppvAmemCacheSet.SetData(
                            *meshDataPtr, 0, static_cast<CAmemCache::TYPE>(1), 1));

                        if (*meshDataPtr != 0) {
                            __dl__FPv(*meshDataPtr);
                            *meshDataPtr = 0;
                        }

                        targetModel->m_refCount++;
                        targetModel = 0;
                    }
                } else if (innerChunk.m_id == 0x4e414d45) {
                    char* name = chunkFile.GetString();

                    targetModel = 0;
                    for (unsigned int i = 0; i < 0x100; i++) {
                        if (modelArray[i].m_isUsed != 0 && strcmp(modelArray[i].m_name, name) == 0) {
                            targetModel = &modelArray[i];
                            break;
                        }
                    }

                    if (targetModel == 0) {
                        for (int i = 0; i < 0x100; i++) {
                            if (modelArray[i].m_isUsed == 0) {
                                targetModel = &modelArray[i];
                                break;
                            }
                        }

                        if (targetModel != 0) {
                            targetModel->m_refCount = 0;
                            targetModel->m_isUsed = 1;
                            strcpy(targetModel->m_name, name);
                        }
                    } else {
                        targetModel = 0;
                    }
                }
            }
        }
        chunkFile.PopChunk();
    }
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
void CPartMng::pppLoadPan(const char* baseName)
{
    char path[256];
    unsigned long fileSize = 0;

    sprintf(path, "%s.pan", baseName);
    if (System.m_execParam > 2) {
        System.Printf("ReadPan fn=[%s]\n", path);
    }

    void* fileData = pppFileRead(path, fileSize, 0, 0);
    if (fileData == 0) {
        if (System.m_execParam != 0) {
            System.Printf("CAN NOT READ[%s]!!\n", path);
        }
        return;
    }

    pppShapeSt** shapeArrayPtr = reinterpret_cast<pppShapeSt**>(reinterpret_cast<unsigned char*>(this) + 0x7f0);
    if (*shapeArrayPtr == 0) {
        CMemory::CStage* stageLoad =
            *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartPcs) + 0x1c);
        pppShapeSt* shapeArray = reinterpret_cast<pppShapeSt*>(
            __nw__FUlPQ27CMemory6CStagePci(0x2c00, stageLoad, s_partMng_cpp_801d8230, 0xd0b));
        if (shapeArray != 0) {
            __construct_array(shapeArray, reinterpret_cast<void (*)(void*)>(__ct__10pppShapeStFv),
                              reinterpret_cast<void (*)(void*, int)>(__dt__10pppShapeStFv), 0x2c, 0x100);
            for (int i = 0; i < 0x100; i++) {
                shapeArray[i].m_inUse = 0;
            }
        }
        *shapeArrayPtr = shapeArray;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(fileData);

    CChunkFile::CChunk outerChunk;
    while (chunkFile.GetNextChunk(outerChunk)) {
        chunkFile.PushChunk();
        if (outerChunk.m_id == 0x53534554) {
            pppShapeSt* shapeArray = *shapeArrayPtr;
            pppShapeSt* targetShape = 0;

            CChunkFile::CChunk innerChunk;
            while (chunkFile.GetNextChunk(innerChunk)) {
                if (innerChunk.m_id == 0x5348504d) {
                    if (targetShape != 0) {
                        CChunkFile shpFile;
                        shpFile.SetBuf(chunkFile.GetAddress());
                        pppReadShp(shpFile, targetShape);
                        targetShape->m_refCount++;
                        targetShape = 0;
                    }
                } else if (innerChunk.m_id == 0x4e414d45) {
                    char* name = chunkFile.GetString();

                    targetShape = 0;
                    for (unsigned int i = 0; i < 0x100; i++) {
                        if (shapeArray[i].m_inUse != 0 && strcmp(shapeArray[i].m_name, name) == 0) {
                            targetShape = &shapeArray[i];
                            break;
                        }
                    }

                    if (targetShape == 0) {
                        for (int i = 0; i < 0x100; i++) {
                            if (shapeArray[i].m_inUse == 0) {
                                targetShape = &shapeArray[i];
                                break;
                            }
                        }

                        if (targetShape != 0) {
                            targetShape->m_refCount = 0;
                            targetShape->m_inUse = 1;
                            strcpy(targetShape->m_name, name);
                        }
                    } else {
                        targetShape = 0;
                    }
                }
            }
        }
        chunkFile.PopChunk();
    }
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
void CPartMng::pppLoadPdt(const char* baseName, int pdtSlotIndex, int cachePriority, void* readBuffer, int readBufferSize)
{
    struct PppPdtSlotRaw {
        _pppDataHead* m_pppDataHead;
        unsigned int m_envFields[5];
        char m_name[0x20];
    };

    CMemory::CStage* stageLoad =
        *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartPcs) + 0x1c);
    PppPdtSlotRaw* pdtSlots = reinterpret_cast<PppPdtSlotRaw*>(reinterpret_cast<char*>(this) + 0x22e18);
    PppPdtSlotRaw* pdtSlot = &pdtSlots[pdtSlotIndex];

    ppvAmemCacheSet.CacheClear();
    stageLoad->setDefaultParam(pdtSlotIndex);

    char pdtPath[256];
    sprintf(pdtPath, "%s.pdt", baseName);
    strncpy(pdtSlot->m_name, baseName, sizeof(pdtSlot->m_name));
    pdtSlot->m_name[sizeof(pdtSlot->m_name) - 1] = '\0';

    if (System.m_execParam > 2) {
        System.Printf("ReadPdt fn=[%s]\n", pdtPath);
    }

    unsigned long pdtSize = 0;
    void* pdtData = pppFileRead(pdtPath, pdtSize, readBuffer, readBufferSize);
    if (pdtData == 0) {
        pdtSlot->m_pppDataHead = 0;
        if (System.m_execParam != 0) {
            System.Printf("CAN NOT READ[%s]!!\n", pdtPath);
        }
        stageLoad->resDefaultParam();
        return;
    }

    // Async file mode can return sentinel 1 before data is available.
    if (pdtData == reinterpret_cast<void*>(1)) {
        stageLoad->resDefaultParam();
        return;
    }

    CChunkFile pdtFile;
    pdtFile.SetBuf(pdtData);

    CChunkFile::CChunk parentChunk;
    while (pdtFile.GetNextChunk(parentChunk)) {
        pdtFile.PushChunk();
        if (parentChunk.m_id == 0x50445420) { // "PDT "
            CChunkFile::CChunk childChunk;
            while (pdtFile.GetNextChunk(childChunk)) {
                pdtFile.PushChunk();
                if (childChunk.m_id == 0x50445453) { // "PDTS"
                    _pppDataHead* sourceHead = reinterpret_cast<_pppDataHead*>(pdtFile.GetAddress());
                    pppInitData(sourceHead, pppGetSysProgTable(), cachePriority);

                    unsigned long copySize = sourceHead->m_partCount * 0x60 + 0x20;
                    _pppDataHead* copiedHead = static_cast<_pppDataHead*>(
                        __nwa__FUlPQ27CMemory6CStagePci(copySize, stageLoad, s_partMng_cpp_801d8230, 0xd56));
                    pdtSlot->m_pppDataHead = copiedHead;

                    if (copiedHead != 0) {
                        memcpy(copiedHead, sourceHead, copySize);
                    }

                    pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(pdtSlot->m_envFields);
                    pdtSlot->m_envFields[0] = reinterpret_cast<unsigned int>(stageLoad);
                    pdtSlot->m_envFields[1] = pppEnvStPtr != 0
                                                  ? reinterpret_cast<unsigned int>(pppEnvStPtr->m_materialSetPtr)
                                                  : 0;

                    if (copiedHead != 0) {
                        pdtSlot->m_envFields[2] = copiedHead->m_modelNames;
                        pdtSlot->m_envFields[3] = copiedHead->m_shapeNames;
                        pdtSlot->m_envFields[4] = copiedHead->m_shapeGroups;
                    }
                }
                pdtFile.PopChunk();
            }
        }
        pdtFile.PopChunk();
    }

    stageLoad->resDefaultParam();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CPartMng::pppGetFreeDataMng()
{
    char* self = reinterpret_cast<char*>(this);
    char* freeSlot = 0;
    int slotIndex = 8;
    int count = 0x18;

    while (count != 0) {
        char* slot = self + 0x22E18 + slotIndex * 0x38;
        if (*reinterpret_cast<_pppDataHead**>(slot) == 0) {
            freeSlot = self + 0x22E18 + slotIndex * 0x38;
            break;
        }

        slotIndex++;
        count--;
    }

    if (freeSlot == 0) {
        if ((unsigned int)System.m_execParam >= 1) {
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
    g_dcp.m_paramC = FLOAT_8032fe18;
    g_dcp.m_paramD = FLOAT_8032fe18;
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
        int m_prioTime;              // 0xAC
        int m_previousFrame2;        // 0xB0
        int m_numPrograms;           // 0xB4
        int m_reservedB8;            // 0xB8
        unsigned int m_objHitMask;   // 0xBC
        unsigned int m_cylinderAttribute; // 0xC0
        _pppPObjLink m_pppPObjLinkHead;   // 0xC4
        void* m_pppPDataVals;        // 0xCC
        unsigned char m_padD0[0xE4 - 0xD0];
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
        short m_frameCounter;             // 0xF9
        unsigned char m_padFB[0x100 - 0xFB];
        unsigned int m_paramA;            // 0x100
        unsigned int m_paramB;            // 0x104
        float m_cullRadiusSq;             // 0x108
        float m_cullRadius;               // 0x10C
        float m_cullYOffset;              // 0x110
        float m_sortDepth;                // 0x114
        unsigned short m_field118;        // 0x118
        short m_mapObjIndex;              // 0x11A
        PPPSEST m_soundEffectData;        // 0x11C
        PPPIFPARAM m_hitParams;           // 0x130
        short m_hitObjectIds[0x10];       // 0x138
    };

    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    unsigned char* slot = self + 0x22E18 + pdtSlotIndex * 0x38;
    _pppDataHead* pdt = *reinterpret_cast<_pppDataHead**>(slot + 0x0);
    if (pdt == 0) {
        return -1;
    }

    int freeIdx = -1;
    for (int i = 0; i < 0x180; i++) {
        unsigned char* mngBytes = self + 0x1D4 + i * 0x158;
        if (*reinterpret_cast<int*>(mngBytes + 0x14) == -0x1000) {
            freeIdx = i;
            break;
        }
    }
    if (freeIdx < 0) {
        return -1;
    }

    PppMngStCreateRaw* mng = reinterpret_cast<PppMngStCreateRaw*>(self + 0x1D4 + freeIdx * 0x158);
    unsigned char* fpData = reinterpret_cast<unsigned char*>(pdt) + 0x20 + fpNo * 0x60;
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
    memcpy(mng->m_hitObjectIds, createParam->m_hitObjectIds, sizeof(mng->m_hitObjectIds));

    mng->m_mapTexLoaded = 0;
    mng->m_hasMapRef = 0;
    mng->m_envColorR = 0;
    mng->m_envColorG = 0;
    mng->m_envColorB = 0x13;
    mng->m_envColorA = 0x33;
    if (reinterpret_cast<unsigned char*>(&PartPcs)[0x5b145] != 0 && pdtSlotIndex == 7 && fpNo == 0) {
        mng->m_envColorR = 0;
        mng->m_envColorG = 0;
        mng->m_envColorB = 0x10;
        mng->m_envColorA = 0;
    }

    mng->m_soundEffectData = createParam->m_soundEffectParams;
    mng->m_soundEffectData.m_soundEffectStartFrame <<= 0xC;

    mng->m_isFinished = 0;
    mng->m_endRequested = 0;
    mng->m_stopRequested = 0;
    mng->m_slotVisible = 1;
    mng->m_ownerFacing = 1;

    const int initialTime = *reinterpret_cast<int*>(fpData1 + 0x0C);
    if (initialTime == -0x1000) {
        mng->m_baseTime = 0;
    } else {
        int scaled = initialTime * 0x19;
        scaled = scaled / 0x1E + (scaled >> 0x1F);
        mng->m_baseTime = scaled - (scaled >> 0x1F);
    }

    mng->m_pppResSet = slot;
    mng->m_partIndex = *reinterpret_cast<int*>(fpData1 + 0x10);
    mng->m_cullRadiusSq = *reinterpret_cast<float*>(fpData1 + 0x14);
    if (mng->m_cullRadiusSq > 0.0f) {
        mng->m_cullRadiusSq *= mng->m_cullRadiusSq;
    }
    mng->m_cullRadius = *reinterpret_cast<float*>(fpData1 + 0x18);
    mng->m_cullYOffset = *reinterpret_cast<float*>(fpData1 + 0x1C);
    mng->m_pppPObjLinkHead.m_next = 0;
    mng->m_pppPObjLinkHead.m_owner = 0;
    mng->m_pppPDataVals = 0;

    *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(mng) + 0xFC) =
        *reinterpret_cast<unsigned short*>(fpData2 + 0x0);
    mng->m_field118 = *reinterpret_cast<unsigned short*>(fpData2 + 0x2);
    mng->m_matrixMode = *reinterpret_cast<unsigned char*>(fpData2 + 0x5);
    mng->m_drawVariant = *reinterpret_cast<unsigned char*>(fpData2 + 0x6);
    mng->m_rotationOrder = *reinterpret_cast<unsigned char*>(fpData2 + 0x7);
    mng->m_slotVisible = *reinterpret_cast<unsigned char*>(fpData2 + 0x4);
    mng->m_drawSubType = *reinterpret_cast<signed char*>(fpData2 + 0x0C);
    mng->m_ownerFlagsInitialized = *reinterpret_cast<unsigned char*>(fpData2 + 0x0D);
    mng->m_nodeScaleInitialized = *reinterpret_cast<unsigned char*>(fpData2 + 0x0E);
    mng->m_fieldF2 = 1;
    if (allowFpOverride != 0) {
        const unsigned char mode = *reinterpret_cast<unsigned char*>(fpData2 + 0x05);
        if (mode == 4 || mode < 3 || mode > 8) {
            mng->m_fieldF2 = *reinterpret_cast<unsigned char*>(fpData2 + 0x0F);
        }
    }

    mng->m_fpBillboard = *reinterpret_cast<unsigned char*>(fpData2 + 0x0A);
    mng->m_prio = *reinterpret_cast<unsigned char*>(fpData2 + 0x0B);
    mng->m_mapObjIndex = *reinterpret_cast<short*>(fpData2 + 0x08);

    mng->m_objHitMask = createParam->m_objectHitMask;
    mng->m_cylinderAttribute = createParam->m_cylinderAttribute;
    mng->m_paramA = createParam->m_paramA;
    mng->m_paramB = createParam->m_paramB;

    const float baseX = *reinterpret_cast<float*>(fpData + 0x00);
    const float baseY = *reinterpret_cast<float*>(fpData + 0x04);
    const float baseZ = *reinterpret_cast<float*>(fpData + 0x08);
    if (createParam->m_positionOffsetPtr == 0) {
        mng->m_position.x = baseX;
        mng->m_position.y = baseY;
        mng->m_position.z = baseZ;
    } else {
        mng->m_position.x = createParam->m_positionOffsetPtr->x + baseX;
        mng->m_position.y = createParam->m_positionOffsetPtr->y + baseY;
        mng->m_position.z = createParam->m_positionOffsetPtr->z + baseZ;
    }
    mng->m_savedPosition = mng->m_position;
    mng->m_previousPosition = mng->m_position;

    if (createParam->m_extraPositionPtr != 0) {
        mng->m_paramVec0.x = createParam->m_extraPositionPtr->x + baseX;
        mng->m_paramVec0.y = createParam->m_extraPositionPtr->y + baseY;
        mng->m_paramVec0.z = createParam->m_extraPositionPtr->z + baseZ;
    }

    if (createParam->m_rotationPtr == 0) {
        mng->m_rotation.x = *reinterpret_cast<short*>(fpData + 0x10);
        mng->m_rotation.y = *reinterpret_cast<short*>(fpData + 0x12);
        mng->m_rotation.z = *reinterpret_cast<short*>(fpData + 0x14);
        mng->m_rotation.w = *reinterpret_cast<short*>(fpData + 0x16);
        mng->m_rotationSpeed = *reinterpret_cast<int*>(fpData + 0x18);
    } else {
        const float rotScale = 65536.0f / 360.0f;
        int rotX = static_cast<int>(createParam->m_rotationPtr->x * rotScale);
        int rotY = static_cast<int>(createParam->m_rotationPtr->y * rotScale);
        mng->m_rotation.x = static_cast<short>(rotX >> 16);
        mng->m_rotation.y = static_cast<short>(rotX);
        mng->m_rotation.z = static_cast<short>(rotY >> 16);
        mng->m_rotation.w = static_cast<short>(rotY);
        mng->m_rotationSpeed = static_cast<int>(createParam->m_rotationPtr->z * rotScale);
    }

    const float scaleX = *reinterpret_cast<float*>(fpData1 + 0x00);
    const float scaleY = *reinterpret_cast<float*>(fpData1 + 0x04);
    const float scaleZ = *reinterpret_cast<float*>(fpData1 + 0x08);
    if (createParam->m_scalePtr == 0) {
        mng->m_scale.x = scaleX;
        mng->m_scale.y = scaleY;
        mng->m_scale.z = scaleZ;
    } else {
        mng->m_scale.x = createParam->m_scalePtr->x * scaleX;
        mng->m_scale.y = createParam->m_scalePtr->y * scaleY;
        mng->m_scale.z = createParam->m_scalePtr->z * scaleZ;
    }

    mng->m_ownerScale = FLOAT_8032fe18;
    mng->m_scaleFactor = FLOAT_8032fe18;
    mng->m_userFloat0 = FLOAT_8032fe18;
    mng->m_userFloat1 = FLOAT_8032fe18;
    mng->m_useOwnerScaleSign = 0;
    *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(mng) + 0xD8) = 0;
    *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(mng) + 0xDC) = createParam->m_lookTargetPtr;
    *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(mng) + 0xE0) = 0;

    const unsigned char mode = *reinterpret_cast<unsigned char*>(fpData2 + 0x05);
    if (mode == 2 || mode == 4) {
        mng->m_mapObjIndex = static_cast<short>(MapMng.GetMapObjEffectIdx(*reinterpret_cast<unsigned short*>(fpData2 + 0x08)));
    } else if (mode >= 3 && mode <= 8) {
        mng->m_ownerFacing = 0;
        CGObject* owner = reinterpret_cast<CGObject*>(createParam->m_paramB);
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(mng) + 0xD8) = owner;
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(mng) + 0xDC) = createParam->m_lookTargetPtr;
        if (owner != 0 && owner->m_charaModelHandle != 0 && owner->m_charaModelHandle->m_model != 0) {
            int node = SearchNodeSk__Q26CChara6CModelFPc(owner->m_charaModelHandle->m_model,
                                                         reinterpret_cast<char*>(fpData2 + 0x10));
            if (node >= 0) {
                *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(mng) + 0xE0) = 0;
            }
        }
    }

    return freeIdx;
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
struct PppMngLifecycleState {
    unsigned char m_pad00[0xE4];
    unsigned char m_endRequested;
    unsigned char m_stopRequested;
    unsigned char m_padE6[0x36];
    PPPSEST m_soundEffectData;
};

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
        if (*reinterpret_cast<int*>(pppMngSt + 0x2A2C) != -0x1000
            && *reinterpret_cast<int*>(pppMngSt + 0x2B18) == slot) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0x2B01) = isVisible;
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
    char* pppMngSt = reinterpret_cast<char*>(this) + (index * 0x158) + 0x2A18;

    if (*reinterpret_cast<int*>(pppMngSt + 0x14) < 0) {
        *reinterpret_cast<unsigned char*>(pppMngSt + 0xE8) = 1;
        pppStopSe__FP9_pppMngStP7PPPSEST(
            reinterpret_cast<_pppMngSt*>(pppMngSt), reinterpret_cast<PPPSEST*>(pppMngSt + 0x11C));
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
    char* pppMngSt = reinterpret_cast<char*>(this) + (index * 0x158) + 0x2A18;
    *reinterpret_cast<unsigned char*>(pppMngSt + 0xE5) = 1;
    pppStopSe__FP9_pppMngStP7PPPSEST(
        reinterpret_cast<_pppMngSt*>(pppMngSt), reinterpret_cast<PPPSEST*>(pppMngSt + 0x11C));
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
    // NOTE: This __sinit is compiler-generated from global variable initialization.
    // To match, replace with proper constructors or initializer expressions, then
    // delete this function so the compiler auto-generates it.

    __construct_array(reinterpret_cast<unsigned char*>(&PartMng) + 0x2A18, (void (*)(void*))__ct__9_pppMngStFv, 0,
                      0x158, 0x180);

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
    *reinterpret_cast<unsigned char*>(&g_dcp.m_owner) = 0;
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
