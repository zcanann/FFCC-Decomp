#include "ffcc/mapobj.h"
#include "ffcc/map.h"
#include "ffcc/chunkfile.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_game.h"
#include "ffcc/p_light.h"
#include <dolphin/mtx.h>
#include <string.h>

extern float kMapObjBoundMinInit;
extern float kMapObjBoundMaxInit;
extern const float kMapObjZero;
extern const float kMapObjOne;
extern const float kMapObjInitNegOne;
extern float kMapObjDegToRad;
extern const float kMapObjInitValue50;
extern unsigned int DAT_8032e498;
extern CMaterialMan MaterialMan;
extern "C" int IsRun__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" int Get__12CMapKeyFrameFRiRiRf(CMapKeyFrame*, int*, int*, float*);
extern "C" void Calc__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" void ReadJun__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*, int);
extern "C" void ReadFrame__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*);
extern "C" void ReadKey__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*, int);
extern "C" void DCFlushRange(void*, unsigned long);

namespace {
static inline unsigned char* Ptr(CMapObj* self, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(self) + offset;
}

static inline void*& PtrAt(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline unsigned char& U8At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<unsigned char*>(Ptr(self, offset));
}

static inline unsigned short& U16At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<unsigned short*>(Ptr(self, offset));
}

static inline short& S16At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<short*>(Ptr(self, offset));
}

static inline int& S32At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<int*>(Ptr(self, offset));
}

static inline float& F32At(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<float*>(Ptr(self, offset));
}

static inline CMapObj*& ObjAt(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<CMapObj**>(Ptr(self, offset));
}

static inline Mtx& MtxAt(CMapObj* self, unsigned int offset)
{
    return *reinterpret_cast<Mtx*>(Ptr(self, offset));
}

static inline CMapObj* NextSlot(CMapObj* obj)
{
    return reinterpret_cast<CMapObj*>(Ptr(obj, 0xF0));
}

static inline CMapObj* MapObjArrayStart()
{
    return reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(&MapMng) + 0x954);
}

}

extern "C" void __dl__FPv(void*);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);

template class CPtrArray<CMapAnimRun*>;
template class CPtrArray<CMapShadow*>;

/*
 * --INFO--
 * PAL Address: 0x8002BE10
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CBound::CBound()
{
    float* bounds = (float*)this;
    float max = kMapObjBoundMaxInit;
    float min = kMapObjBoundMinInit;

    bounds[2] = min;
    bounds[1] = min;
    bounds[0] = min;
    bounds[5] = max;
    bounds[4] = max;
    bounds[3] = max;
}

/*
 * --INFO--
 * PAL Address: 0x8002BEFC
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj::CMapObj()
{
    Init();
}

/*
 * --INFO--
 * PAL Address: 0x8002BE7C
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj::~CMapObj()
{
    void* attr = PtrAt(this, 0xEC);
    if (attr != 0) {
        (*(void (**)(void*, int))(*reinterpret_cast<unsigned int*>(attr) + 8))(attr, 1);
        PtrAt(this, 0xEC) = 0;
    }

    Init();
}

/*
 * --INFO--
 * PAL Address: 0x8002BE7C
 * PAL Size: 128b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CMapObj* dtor_8002BE7C(CMapObj* mapObj, short param_2)
{
    if (mapObj != 0) {
        int* piVar1 = reinterpret_cast<int*>(PtrAt(mapObj, 0xEC));
        if (piVar1 != 0) {
            if (piVar1 != 0) {
                (*(void (**)(int*, int))(*piVar1 + 8))(piVar1, 1);
            }
            PtrAt(mapObj, 0xEC) = 0;
        }

        mapObj->Init();
        if (0 < param_2) {
            __dl__FPv(mapObj);
        }
    }

    return mapObj;
}

/*
 * --INFO--
 * PAL Address: 0x8002BF2C
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::Init()
{
    U8At(this, 0x1B) = 1;
    U8At(this, 0x1C) = 1;
    S32At(this, 0x0) = 0;
    S32At(this, 0xC) = 0;
    S32At(this, 0xEC) = 0;

    U8At(this, 0x15) = 0x7E;
    U8At(this, 0x14) = 0x7E;
    U8At(this, 0x1F) = 0xFF;
    U8At(this, 0x20) = 0;
    U8At(this, 0x27) = 0;
    U8At(this, 0x21) = 0;

    U16At(this, 0x2E) = 0xFFFF;
    U16At(this, 0x30) = 0xFFFF;
    U16At(this, 0x32) = 0xFFFF;
    U8At(this, 0x18) = 1;
    U8At(this, 0x19) = 1;
    U16At(this, 0x34) = 0xFFFF;

    F32At(this, 0x48) = kMapObjInitNegOne;
    F32At(this, 0x44) = kMapObjInitNegOne;
    F32At(this, 0x4C) = kMapObjInitNegOne;
    F32At(this, 0x50) = kMapObjInitValue50;

    U16At(this, 0x2C) = 0;
    U16At(this, 0x2A) = 0;
    U16At(this, 0x28) = 0;
    U8At(this, 0x24) = 0xFF;
    U8At(this, 0x23) = 0xFF;
    S32At(this, 0x10) = 0;
    U16At(this, 0x16) = 0xFFFF;
    U8At(this, 0x22) = 1;
    S32At(this, 0x3C) = -1;

    F32At(this, 0x60) = kMapObjOne;
    F32At(this, 0x5C) = kMapObjOne;
    F32At(this, 0x58) = kMapObjOne;
    U8At(this, 0x1A) = 0;
    F32At(this, 0x40) = kMapObjOne;
    U8At(this, 0x25) = 1;
    U8At(this, 0x26) = 0;
    S32At(this, 0x38) = -1;
}

/*
 * --INFO--
 * PAL Address: 0x8002A5B0
 * PAL Size: 6240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::ReadOtmObj(CChunkFile& chunkFile)
{
    enum {
        CHUNK_AMBI = 0x414D4249,
        CHUNK_ANIM = 0x414E494D,
        CHUNK_BOBJ = 0x424F424A,
        CHUNK_EFID = 0x45464944,
        CHUNK_FSDW = 0x46534457,
        CHUNK_GBID = 0x47424944,
        CHUNK_GEOM = 0x47454F4D,
        CHUNK_ID = 0x49442020,
        CHUNK_LTST = 0x4C545354,
        CHUNK_MIME = 0x4D494D45,
        CHUNK_MSID = 0x4D534944,
        CHUNK_PIDX = 0x50494458,
        CHUNK_PSTA = 0x50535441,
        CHUNK_PRIO = 0x5052494F,
        CHUNK_SDST = 0x53445354,
        CHUNK_TFRM = 0x5446524D,
        CHUNK_TRNS = 0x54524E53,
        CHUNK_FRAM = 0x4652414D,
        CHUNK_JUN = 0x4A554E20,
        CHUNK_KEY = 0x4B455920,
        CHUNK_VTX = 0x56545820,
        CHUNK_VTXL = 0x5654584C,
    };

    Init();

    chunkFile.PushChunk();
    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk) != 0) {
        if (chunk.m_id == CHUNK_BOBJ) {
            U16At(this, 0x16) = chunkFile.Get2();
        } else if (chunk.m_id == CHUNK_GBID) {
            U16At(this, 0x32) = chunkFile.Get2();
        } else if (chunk.m_id == CHUNK_EFID) {
            U16At(this, 0x30) = chunkFile.Get2();
        } else if (chunk.m_id == CHUNK_FSDW) {
            *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x404) = chunkFile.Get1();
        } else if (chunk.m_id == CHUNK_ID) {
            U16At(this, 0x2E) = chunkFile.Get2();
        } else if (chunk.m_id == CHUNK_MSID) {
            U16At(this, 0x34) = static_cast<unsigned short>(chunkFile.Get4());
        } else if (chunk.m_id == CHUNK_PRIO) {
            unsigned char priority = chunkFile.Get1();
            U8At(this, 0x15) = priority;
            U8At(this, 0x14) = priority;
        } else if (chunk.m_id == CHUNK_AMBI) {
            U8At(this, 0xE8) = chunkFile.Get1();
            U8At(this, 0xE9) = chunkFile.Get1();
            U8At(this, 0xEA) = chunkFile.Get1();
            U8At(this, 0xEB) = chunkFile.Get1();
            U8At(this, 0x21) = 1;
        } else if (chunk.m_id == CHUNK_GEOM) {
            F32At(this, 0x40) = chunkFile.GetF4();
            U8At(this, 0x1A) = chunkFile.Get1();
            U8At(this, 0x27) = chunkFile.Get1();
        } else if (chunk.m_id == CHUNK_LTST) {
            if (chunk.m_version == 1) {
                S32At(this, 0x38) = static_cast<int>(chunkFile.Get4());
            } else if (chunkFile.Get1() == 0) {
                S32At(this, 0x38) = 0;
            }
        } else if (chunk.m_id == CHUNK_SDST) {
            if (chunk.m_version == 2) {
                U8At(this, 0x22) = chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                S32At(this, 0x3C) = static_cast<int>(chunkFile.Get4());
            } else if (chunk.m_version == 1) {
                U8At(this, 0x22) = chunkFile.Get1();
                if (chunkFile.Get1() == 0) {
                    S32At(this, 0x3C) = 0;
                } else {
                    S32At(this, 0x3C) = -1;
                }
            } else {
                U8At(this, 0x22) = chunkFile.Get1();
                S32At(this, 0x3C) = -1;
            }
        } else if (chunk.m_id == CHUNK_PIDX) {
            short parentIdx = static_cast<short>(chunkFile.Get2());
            short meshOrHitIdx = static_cast<short>(chunkFile.Get2());

            U8At(this, 0x1E) = chunkFile.Get1();
            U8At(this, 0x1D) = chunkFile.Get1();

            if (parentIdx == -1) {
                PtrAt(this, 0x0) = 0;
            } else {
                ObjAt(this, 0x0) = MapObjArrayStart() + parentIdx;
            }

            if (meshOrHitIdx == -1) {
                PtrAt(this, 0xC) = 0;
            } else if (U8At(this, 0x1D) == 1) {
                PtrAt(this, 0xC) = reinterpret_cast<unsigned char*>(&MapMng) + 0x1E954 + (meshOrHitIdx * 0x44);
                U8At(this, 0x14) = 0;
                U8At(this, 0x15) = 0;
            } else if ((U8At(this, 0x1D) == 2) || (U8At(this, 0x1D) == 3)) {
                if (meshOrHitIdx == -2) {
                    CMapObjAtrMeshName* meshName = reinterpret_cast<CMapObjAtrMeshName*>(
                        __nw__FUlPQ27CMemory6CStagePci(0x28, *reinterpret_cast<CMemory::CStage**>(&MapMng), "mapobj.cpp", 0x84));
                    if (meshName != 0) {
                        meshName->CMapObjAtrMeshName::CMapObjAtrMeshName();
                    }
                    PtrAt(this, 0xEC) = meshName;
                    char* name = chunkFile.GetString();
                    if (meshName != 0) {
                        strncpy(reinterpret_cast<char*>(meshName) + 8, name, 0x20);
                    }
                    PtrAt(this, 0xC) = 0;
                } else {
                    PtrAt(this, 0xC) = reinterpret_cast<unsigned char*>(&MapMng) + 0x4D4 + (meshOrHitIdx * 0x24);
                }
            }

            if (((Game.game.m_currentSceneId == 4) || (Game.game.m_currentSceneId == 7)) &&
                (static_cast<signed char>(U8At(this, 0x1E)) > 7) && (static_cast<signed char>(U8At(this, 0x1E)) < 10)) {
                F32At(this, 0x58) = kMapObjZero;
                F32At(this, 0x5C) = kMapObjOne;
                F32At(this, 0x60) = kMapObjZero;
            }
        } else if (chunk.m_id == CHUNK_TRNS) {
            F32At(this, 0x58) = chunkFile.GetF4();
            F32At(this, 0x5C) = chunkFile.GetF4();
            F32At(this, 0x60) = chunkFile.GetF4();
        } else if (chunk.m_id == CHUNK_TFRM) {
            F32At(this, 0x64) = chunkFile.GetF4();
            F32At(this, 0x68) = chunkFile.GetF4();
            F32At(this, 0x6C) = chunkFile.GetF4();
            F32At(this, 0x70) = chunkFile.GetF4();
            F32At(this, 0x74) = chunkFile.GetF4();
            F32At(this, 0x78) = chunkFile.GetF4();
            F32At(this, 0x7C) = chunkFile.GetF4();
            F32At(this, 0x80) = chunkFile.GetF4();
            F32At(this, 0x84) = chunkFile.GetF4();

            if (((U8At(this, 0x1D) == 2) || (U8At(this, 0x1D) == 3)) &&
                ((F32At(this, 0x7C) != kMapObjZero) || (F32At(this, 0x80) != kMapObjZero) || (F32At(this, 0x84) != kMapObjZero))) {
                F32At(this, 0x7C) = kMapObjZero;
                F32At(this, 0x80) = kMapObjZero;
                F32At(this, 0x84) = kMapObjZero;
            }

            U8At(this, 0x1C) = 1;
            U8At(this, 0x1B) = 1;
        } else if (chunk.m_id == CHUNK_ANIM) {
            unsigned char* animRun = reinterpret_cast<unsigned char*>(
                __nw__FUlPQ27CMemory6CStagePci(0x14, *reinterpret_cast<CMemory::CStage**>(&MapMng), "mapobj.cpp", 0x21E));
            if (animRun != 0) {
                *reinterpret_cast<int*>(animRun) = -1;
                *reinterpret_cast<unsigned short*>(animRun + 0x12) = static_cast<unsigned short>(chunkFile.Get4());
                *reinterpret_cast<int*>(animRun + 0x4) = static_cast<int>(chunkFile.Get4());
                *reinterpret_cast<int*>(animRun + 0x8) = static_cast<int>(chunkFile.Get4());
                *reinterpret_cast<int*>(animRun + 0xC) = static_cast<int>(chunkFile.Get4());
                *(animRun + 0x10) = chunkFile.Get1();
                if (chunk.m_version == 1) {
                    *(animRun + 0x11) = chunkFile.Get1();
                } else {
                    *(animRun + 0x11) = 0;
                }
                reinterpret_cast<CPtrArray<CMapAnimRun*>*>(reinterpret_cast<unsigned char*>(&MapMng) + 0x213E0)
                    ->Add(reinterpret_cast<CMapAnimRun*>(animRun));
            }
        } else if (chunk.m_id == CHUNK_MIME) {
            unsigned char* mime = reinterpret_cast<unsigned char*>(
                __nw__FUlPQ27CMemory6CStagePci(0x3C, *reinterpret_cast<CMemory::CStage**>(&MapMng), "mapobj.cpp", 0x33B));

            if (mime != 0) {
                reinterpret_cast<CMapObjAtrMime*>(mime)->CMapObjAtrMime::CMapObjAtrMime();
                *reinterpret_cast<int*>(mime + 0x4) = 2;
                *reinterpret_cast<void**>(mime + 0xC) = 0;
                *reinterpret_cast<int*>(mime + 0x10) = 0;
                *reinterpret_cast<int*>(mime + 0x14) = 0;
                *reinterpret_cast<int*>(mime + 0x18) = 0;
                *(mime + 0x17) = 1;
                *(mime + 0x8) = 0;
                *reinterpret_cast<int*>(mime + 0x1C) = 0;
            }

            chunkFile.PushChunk();
            CChunkFile::CChunk mimeChunk;
            while (chunkFile.GetNextChunk(mimeChunk) != 0) {
                if (mimeChunk.m_id == CHUNK_KEY) {
                    if (mime != 0) {
                        ReadKey__12CMapKeyFrameFR10CChunkFilei(
                            reinterpret_cast<CMapKeyFrame*>(mime + 0x14), &chunkFile, static_cast<char>(mimeChunk.m_arg0));
                    }
                } else if (mimeChunk.m_id == CHUNK_JUN) {
                    if (mime != 0) {
                        ReadJun__12CMapKeyFrameFR10CChunkFilei(
                            reinterpret_cast<CMapKeyFrame*>(mime + 0x14), &chunkFile, static_cast<char>(mimeChunk.m_arg0));
                    }
                } else if (mimeChunk.m_id == CHUNK_FRAM) {
                    if (mime != 0) {
                        ReadFrame__12CMapKeyFrameFR10CChunkFilei(reinterpret_cast<CMapKeyFrame*>(mime + 0x14), &chunkFile);
                    }
                } else if (mimeChunk.m_id == CHUNK_VTXL) {
                    if (mime != 0) {
                        *(mime + 0x8) = static_cast<unsigned char>(mimeChunk.m_arg0);
                        *reinterpret_cast<void**>(mime + 0xC) = __nwa__FUlPQ27CMemory6CStagePci(
                            static_cast<unsigned long>(*(mime + 0x8)) << 2,
                            *reinterpret_cast<CMemory::CStage**>(&MapMng), "mapobj.cpp", 0x348);
                    }

                    chunkFile.PushChunk();
                    CChunkFile::CChunk vtxChunk;
                    int vtxTableOffset = 0;
                    while (chunkFile.GetNextChunk(vtxChunk) != 0) {
                        if (vtxChunk.m_id == CHUNK_VTX) {
                            float* vtx = reinterpret_cast<float*>(__nwa__FUlPQ27CMemory6CStagePci(
                                static_cast<unsigned long>(vtxChunk.m_arg0) * 0xC,
                                *reinterpret_cast<CMemory::CStage**>(&MapMng), "mapobj.cpp", 0x353));
                            if ((mime != 0) && (*reinterpret_cast<void**>(mime + 0xC) != 0)) {
                                *reinterpret_cast<float**>(
                                    reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(mime + 0xC)) + vtxTableOffset) = vtx;
                            }
                            vtxTableOffset += 4;
                            if (mime != 0) {
                                *reinterpret_cast<int*>(mime + 0x10) = static_cast<int>(vtxChunk.m_arg0);
                            }

                            for (unsigned int i = 0; i < vtxChunk.m_arg0; i++) {
                                vtx[0] = chunkFile.GetF4();
                                vtx[1] = chunkFile.GetF4();
                                vtx[2] = chunkFile.GetF4();
                                vtx += 3;
                            }
                        }
                    }
                    chunkFile.PopChunk();
                }
            }
            chunkFile.PopChunk();
            PtrAt(this, 0xEC) = mime;
        } else if (chunk.m_id == CHUNK_PSTA) {
            CMapObjAtrPlaySta* playSta = reinterpret_cast<CMapObjAtrPlaySta*>(
                __nw__FUlPQ27CMemory6CStagePci(0xC, *reinterpret_cast<CMemory::CStage**>(&MapMng), "mapobj.cpp", 0x39B));
            if (playSta != 0) {
                playSta->CMapObjAtrPlaySta::CMapObjAtrPlaySta();
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned char*>(playSta) + 8) = chunkFile.Get1();
            }
            PtrAt(this, 0xEC) = playSta;
        }
    }
    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x8002A258
 * PAL Size: 856b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::CalcMtx(float (*parentMtx)[4], unsigned char inDirty)
{
    Mtx mtx0;
    Mtx mtx1;
    Mtx mtx2;
    CMapObj* obj = this;

    do {
        unsigned char dirty = inDirty;

        if (U8At(obj, 0x1B) != 0) {
            U8At(obj, 0x1B) = 0;
            if (U8At(obj, 0x1C) != 0) {
                PSMTXScale(MtxAt(obj, 0x88), F32At(obj, 0x7C), F32At(obj, 0x80), F32At(obj, 0x84));
                PSMTXRotRad(mtx2, 'x', kMapObjDegToRad * F32At(obj, 0x70));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
                PSMTXRotRad(mtx2, 'y', kMapObjDegToRad * F32At(obj, 0x74));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
                PSMTXRotRad(mtx2, 'z', kMapObjDegToRad * F32At(obj, 0x78));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
                PSMTXTrans(mtx2, F32At(obj, 0x64), F32At(obj, 0x68), F32At(obj, 0x6C));
                PSMTXConcat(mtx2, MtxAt(obj, 0x88), MtxAt(obj, 0x88));
            }

            dirty = 1;
        }

        if (dirty != 0) {
            PSMTXConcat(*reinterpret_cast<Mtx*>(parentMtx), MtxAt(obj, 0x88), MtxAt(obj, 0xB8));
        }

        for (CMapObj* child = ObjAt(obj, 0x4); child != 0; child = ObjAt(child, 0x8)) {
            unsigned char childDirty = dirty;

            if (U8At(child, 0x1B) != 0) {
                U8At(child, 0x1B) = 0;
                if (U8At(child, 0x1C) != 0) {
                    PSMTXScale(MtxAt(child, 0x88), F32At(child, 0x7C), F32At(child, 0x80), F32At(child, 0x84));
                    PSMTXRotRad(mtx1, 'x', kMapObjDegToRad * F32At(child, 0x70));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                    PSMTXRotRad(mtx1, 'y', kMapObjDegToRad * F32At(child, 0x74));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                    PSMTXRotRad(mtx1, 'z', kMapObjDegToRad * F32At(child, 0x78));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                    PSMTXTrans(mtx1, F32At(child, 0x64), F32At(child, 0x68), F32At(child, 0x6C));
                    PSMTXConcat(mtx1, MtxAt(child, 0x88), MtxAt(child, 0x88));
                }

                childDirty = 1;
            }

            if (childDirty != 0) {
                PSMTXConcat(MtxAt(obj, 0xB8), MtxAt(child, 0x88), MtxAt(child, 0xB8));
            }

            for (CMapObj* grandChild = ObjAt(child, 0x4); grandChild != 0; grandChild = ObjAt(grandChild, 0x8)) {
                unsigned char grandChildDirty = childDirty;

                if (U8At(grandChild, 0x1B) != 0) {
                    U8At(grandChild, 0x1B) = 0;
                    if (U8At(grandChild, 0x1C) != 0) {
                        PSMTXScale(
                            MtxAt(grandChild, 0x88), F32At(grandChild, 0x7C), F32At(grandChild, 0x80), F32At(grandChild, 0x84));
                        PSMTXRotRad(mtx0, 'x', kMapObjDegToRad * F32At(grandChild, 0x70));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                        PSMTXRotRad(mtx0, 'y', kMapObjDegToRad * F32At(grandChild, 0x74));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                        PSMTXRotRad(mtx0, 'z', kMapObjDegToRad * F32At(grandChild, 0x78));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                        PSMTXTrans(mtx0, F32At(grandChild, 0x64), F32At(grandChild, 0x68), F32At(grandChild, 0x6C));
                        PSMTXConcat(mtx0, MtxAt(grandChild, 0x88), MtxAt(grandChild, 0x88));
                    }

                    grandChildDirty = 1;
                }

                if (grandChildDirty != 0) {
                    PSMTXConcat(MtxAt(child, 0xB8), MtxAt(grandChild, 0x88), MtxAt(grandChild, 0xB8));
                }

                if (ObjAt(grandChild, 0x4) != 0) {
                    ObjAt(grandChild, 0x4)->CalcMtx(reinterpret_cast<float(*)[4]>(&MtxAt(grandChild, 0xB8)), grandChildDirty);
                }
            }
        }

        obj = ObjAt(obj, 0x8);
    } while (obj != 0);
}

/*
 * --INFO--
 * PAL Address: 0x8002A008
 * PAL Size: 592b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetShow_r(int show)
{
    CMapObj* root = this;

    do {
        if (show == 0) {
            U8At(root, 0x18) &= 0xFE;
        } else {
            U8At(root, 0x18) |= 1;
        }

        for (CMapObj* c0 = ObjAt(root, 0x4); c0 != 0; c0 = ObjAt(c0, 0x8)) {
            if (show == 0) {
                U8At(c0, 0x18) &= 0xFE;
            } else {
                U8At(c0, 0x18) |= 1;
            }

            for (CMapObj* c1 = ObjAt(c0, 0x4); c1 != 0; c1 = ObjAt(c1, 0x8)) {
                if (show == 0) {
                    U8At(c1, 0x18) &= 0xFE;
                } else {
                    U8At(c1, 0x18) |= 1;
                }

                for (CMapObj* c2 = ObjAt(c1, 0x4); c2 != 0; c2 = ObjAt(c2, 0x8)) {
                    if (show == 0) {
                        U8At(c2, 0x18) &= 0xFE;
                    } else {
                        U8At(c2, 0x18) |= 1;
                    }

                    for (CMapObj* c3 = ObjAt(c2, 0x4); c3 != 0; c3 = ObjAt(c3, 0x8)) {
                        if (show == 0) {
                            U8At(c3, 0x18) &= 0xFE;
                        } else {
                            U8At(c3, 0x18) |= 1;
                        }

                        for (CMapObj* c4 = ObjAt(c3, 0x4); c4 != 0; c4 = ObjAt(c4, 0x8)) {
                            if (show == 0) {
                                U8At(c4, 0x18) &= 0xFE;
                            } else {
                                U8At(c4, 0x18) |= 1;
                            }

                            for (CMapObj* c5 = ObjAt(c4, 0x4); c5 != 0; c5 = ObjAt(c5, 0x8)) {
                                if (show == 0) {
                                    U8At(c5, 0x18) &= 0xFE;
                                } else {
                                    U8At(c5, 0x18) |= 1;
                                }

                                for (CMapObj* c6 = ObjAt(c5, 0x4); c6 != 0; c6 = ObjAt(c6, 0x8)) {
                                    if (show == 0) {
                                        U8At(c6, 0x18) &= 0xFE;
                                    } else {
                                        U8At(c6, 0x18) |= 1;
                                    }

                                    for (CMapObj* c7 = ObjAt(c6, 0x4); c7 != 0; c7 = ObjAt(c7, 0x8)) {
                                        if (show == 0) {
                                            U8At(c7, 0x18) &= 0xFE;
                                        } else {
                                            U8At(c7, 0x18) |= 1;
                                        }

                                        if (ObjAt(c7, 0x4) != 0) {
                                            ObjAt(c7, 0x4)->SetShow_r(show);
                                        }
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        root = ObjAt(root, 0x8);
    } while (root != 0);
}

/*
 * --INFO--
 * PAL Address: 0x80029FB8
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetShow(int show)
{
    if (show != 0) {
        U8At(this, 0x18) |= 1;
    } else {
        U8At(this, 0x18) &= 0xFE;
    }

    if (ObjAt(this, 0x4) != 0) {
        ObjAt(this, 0x4)->SetShow_r(show);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80029D18
 * PAL Size: 672b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetLink()
{
    CMapObj* mapStart = MapObjArrayStart();
    CMapObj* head0 = 0;
    CMapObj* search0 = mapStart;
    CMapObj* search2Start = mapStart;
    CMapObj* search3Start = mapStart;
    CMapObj* search4Start = mapStart;
    CMapObj* search5Start = mapStart;
    CMapObj* search6Start = mapStart;
    CMapObj* search7Start = mapStart;
    CMapObj* search8Start = mapStart;
    CMapObj* child0;
    CMapObj* child1;
    CMapObj* child2;
    CMapObj* child3;
    CMapObj* child4;
    CMapObj* child5;
    CMapObj* child6;
    CMapObj* child7;
    CMapObj* child8;

    while ((child0 = MapMng.SearchChildMapObj(search0, this)) != 0) {
        CMapObj* search1 = mapStart;
        CMapObj* head1 = 0;

        ObjAt(child0, 0x8) = head0;
        while ((child1 = MapMng.SearchChildMapObj(search1, child0)) != 0) {
            CMapObj* search2 = search2Start;
            CMapObj* head2 = 0;

            ObjAt(child1, 0x8) = head1;
            while ((child2 = MapMng.SearchChildMapObj(search2, child1)) != 0) {
                CMapObj* search3 = search3Start;
                CMapObj* head3 = 0;

                ObjAt(child2, 0x8) = head2;
                while ((child3 = MapMng.SearchChildMapObj(search3, child2)) != 0) {
                    CMapObj* search4 = search4Start;
                    CMapObj* head4 = 0;

                    ObjAt(child3, 0x8) = head3;
                    while ((child4 = MapMng.SearchChildMapObj(search4, child3)) != 0) {
                        CMapObj* search5 = search5Start;
                        CMapObj* head5 = 0;

                        ObjAt(child4, 0x8) = head4;
                        while ((child5 = MapMng.SearchChildMapObj(search5, child4)) != 0) {
                            CMapObj* search6 = search6Start;
                            CMapObj* head6 = 0;

                            ObjAt(child5, 0x8) = head5;
                            while ((child6 = MapMng.SearchChildMapObj(search6, child5)) != 0) {
                                CMapObj* search7 = search7Start;
                                CMapObj* head7 = 0;

                                ObjAt(child6, 0x8) = head6;
                                while ((child7 = MapMng.SearchChildMapObj(search7, child6)) != 0) {
                                    CMapObj* search8 = search8Start;
                                    CMapObj* head8 = 0;

                                    ObjAt(child7, 0x8) = head7;
                                    while ((child8 = MapMng.SearchChildMapObj(search8, child7)) != 0) {
                                        ObjAt(child8, 0x8) = head8;
                                        child8->SetLink();
                                        search8 = NextSlot(child8);
                                        head8 = child8;
                                    }

                                    ObjAt(child7, 0x4) = head8;
                                    search7 = NextSlot(child7);
                                    head7 = child7;
                                }

                                ObjAt(child6, 0x4) = head7;
                                search6 = NextSlot(child6);
                                head6 = child6;
                            }

                            ObjAt(child5, 0x4) = head6;
                            search5 = NextSlot(child5);
                            head5 = child5;
                        }

                        ObjAt(child4, 0x4) = head5;
                        search4 = NextSlot(child4);
                        head4 = child4;
                    }

                    ObjAt(child3, 0x4) = head4;
                    search3 = NextSlot(child3);
                    head3 = child3;
                }

                ObjAt(child2, 0x4) = head3;
                search2 = NextSlot(child2);
                head2 = child2;
            }

            ObjAt(child1, 0x4) = head2;
            search1 = NextSlot(child1);
            head1 = child1;
        }

        ObjAt(child0, 0x4) = head1;
        search0 = NextSlot(child0);
        head0 = child0;
    }

    ObjAt(this, 0x4) = head0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void calcColorKeyFrame(CMapKeyFrame* keyFrame, _GXColor& out, _GXColor* colors)
{
    if (IsRun__12CMapKeyFrameFv(keyFrame) == 0) {
        return;
    }

    int key0 = 0;
    int key1 = 0;
    float blend = 0.0f;
    if (Get__12CMapKeyFrameFRiRiRf(keyFrame, &key0, &key1, &blend) == 0) {
        out = colors[key0];
    } else {
        int blendRate = static_cast<int>(kMapObjDegToRad * blend);
        _GXColor c0 = colors[key0];
        _GXColor c1 = colors[key1];

        out.r = static_cast<unsigned char>(
            c0.r + static_cast<char>((blendRate * (static_cast<int>(c1.r) - static_cast<int>(c0.r))) >> 8));
        out.g = static_cast<unsigned char>(
            c0.g + static_cast<char>((blendRate * (static_cast<int>(c1.g) - static_cast<int>(c0.g))) >> 8));
        out.b = static_cast<unsigned char>(
            c0.b + static_cast<char>((blendRate * (static_cast<int>(c1.b) - static_cast<int>(c0.b))) >> 8));
        out.a = static_cast<unsigned char>(
            c0.a + static_cast<char>((blendRate * (static_cast<int>(c1.a) - static_cast<int>(c0.a))) >> 8));
    }

    Calc__12CMapKeyFrameFv(keyFrame);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::Calc()
{
    if (S16At(this, 0x2C) != 0) {
        S16At(this, 0x28) = static_cast<short>(S16At(this, 0x28) + S16At(this, 0x2C));
        if (S16At(this, 0x2C) < 1) {
            if (S16At(this, 0x28) <= S16At(this, 0x2A)) {
                S16At(this, 0x28) = S16At(this, 0x2A);
                U16At(this, 0x2C) = 0;
            }
        } else if (S16At(this, 0x2A) <= S16At(this, 0x28)) {
            S16At(this, 0x28) = S16At(this, 0x2A);
            U16At(this, 0x2C) = 0;
        }

        if (S16At(this, 0x28) == 0) {
            U8At(this, 0x15) = U8At(this, 0x14);
        } else {
            U8At(this, 0x15) = 2;
        }
    }

    if ((static_cast<signed char>(U8At(this, 0x1D)) == 1) && (PtrAt(this, 0xC) != 0) &&
        (static_cast<signed char>(U8At(this, 0x1F)) == -1) &&
        ((U8At(this, 0x18) & 1) != 0)) {
        if ((kMapObjOne <= F32At(this, 0x50)) || (F32At(this, 0x4C) < kMapObjInitNegOne)) {
            Vec pos;
            Vec posCam;
            Mtx cameraMtx;
            pos.x = F32At(this, 0xC4);
            pos.y = F32At(this, 0xD4);
            pos.z = F32At(this, 0xE4);
            PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(&CameraPcs) + 0x4), cameraMtx);
            PSMTXMultVec(cameraMtx, &pos, &posCam);
            posCam.z = -posCam.z;

            U8At(this, 0x25) = static_cast<unsigned char>(F32At(this, 0x50) < posCam.z);
            if (F32At(this, 0x4C) <= posCam.z) {
                U8At(this, 0x26) = 1;
                U8At(this, 0x15) = U8At(this, 0x14);
            } else {
                U8At(this, 0x26) = 1;
                U8At(this, 0x15) = 2;
            }
        } else {
            U8At(this, 0x15) = U8At(this, 0x14);
            U8At(this, 0x25) = 1;
            U8At(this, 0x26) = 0;
        }
    }

    int attr = S32At(this, 0xEC);
    if (attr != 0) {
        int attrType = *reinterpret_cast<int*>(attr + 4);
        if (attrType == 1) {
            _GXColor& colorCurrent = *reinterpret_cast<_GXColor*>(attr + 8);
            _GXColor* colorTable = reinterpret_cast<_GXColor*>(attr + 0x40);

            calcColorKeyFrame(reinterpret_cast<CMapKeyFrame*>(attr + 0xC0), colorCurrent, colorTable);
            if (*reinterpret_cast<unsigned char*>(attr + 0x2F) != 0) {
                *reinterpret_cast<_GXColor*>(attr + 0xC) = colorCurrent;
            }

            calcColorKeyFrame(reinterpret_cast<CMapKeyFrame*>(attr + 0xE8), colorCurrent, colorTable);
        } else if (attrType < 1) {
            if (attrType >= 0) {
                _GXColor& colorCurrent = *reinterpret_cast<_GXColor*>(attr + 8);
                _GXColor* colorTable = reinterpret_cast<_GXColor*>(attr + 0x24);

                calcColorKeyFrame(reinterpret_cast<CMapKeyFrame*>(attr + 0xA4), colorCurrent, colorTable);
                if (*reinterpret_cast<unsigned char*>(attr + 0x1F) != 0) {
                    *reinterpret_cast<_GXColor*>(attr + 0xC) = colorCurrent;
                }

                calcColorKeyFrame(reinterpret_cast<CMapKeyFrame*>(attr + 0xCC), colorCurrent, colorTable);
            }
        } else if ((attrType < 3) && (IsRun__12CMapKeyFrameFv(reinterpret_cast<CMapKeyFrame*>(attr + 0x14)) != 0)) {
            int key0 = 0;
            int key1 = 0;
            float blend = 0.0f;
            int vertexCount = *reinterpret_cast<int*>(attr + 0x10);
            int frameList = *reinterpret_cast<int*>(attr + 0xC);
            Vec* outVerts = *reinterpret_cast<Vec**>(S32At(this, 0xC) + 0x2C);

            if (Get__12CMapKeyFrameFRiRiRf(reinterpret_cast<CMapKeyFrame*>(attr + 0x14), &key0, &key1, &blend) == 0) {
                float* src = *reinterpret_cast<float**>(frameList + key0 * 4);
                for (int i = 0; i < vertexCount; i++) {
                    outVerts[i].x = src[0];
                    outVerts[i].y = src[1];
                    outVerts[i].z = src[2];
                    src += 3;
                }
            } else {
                Vec* src0 = *reinterpret_cast<Vec**>(frameList + key0 * 4);
                Vec* src1 = *reinterpret_cast<Vec**>(frameList + key1 * 4);
                for (int i = 0; i < vertexCount; i++) {
                    Vec delta;
                    PSVECSubtract(src1, src0, &delta);
                    PSVECScale(&delta, &delta, blend);
                    PSVECAdd(src0, &delta, &outVerts[i]);
                    src0++;
                    src1++;
                }
            }

            DCFlushRange(outVerts, static_cast<unsigned long>(vertexCount * 0xC));
            Calc__12CMapKeyFrameFv(reinterpret_cast<CMapKeyFrame*>(attr + 0x14));
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800293C8
 * PAL Size: 368b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetDrawEnv()
{
    _GXColor mapColor;
    _GXColor lightColor = *reinterpret_cast<_GXColor*>(&DAT_8032e498);
    unsigned char* mapMng = reinterpret_cast<unsigned char*>(&MapMng);

    lightColor.a = U8At(this, 0x23);
    *reinterpret_cast<_GXColor*>(&DAT_8032e498) = lightColor;

    if (U8At(this, 0x21) == 0) {
        mapColor.r = mapMng[0x2298C];
        mapColor.g = mapMng[0x2298D];
        mapColor.b = mapMng[0x2298E];
        mapColor.a = mapMng[0x2298F];
    } else {
        mapColor = *reinterpret_cast<_GXColor*>(Ptr(this, 0xE8));
    }

    if (mapMng[0x22989] != 0) {
        mapColor.r = static_cast<unsigned char>((mapColor.r * mapMng[0x22990]) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * mapMng[0x22991]) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * mapMng[0x22992]) >> 8);
        mapColor.a = static_cast<unsigned char>((mapColor.a * mapMng[0x22993]) >> 8);
    }

    if (U8At(this, 0x24) != 0xFF) {
        unsigned int alphaRate = U8At(this, 0x24);
        mapColor.r = static_cast<unsigned char>((mapColor.r * alphaRate) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * alphaRate) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * alphaRate) >> 8);
    }

    LightPcs.SetMapColorAlpha(MtxAt(this, 0xB8), mapColor, lightColor, U8At(this, 0x26), F32At(this, 0x44), F32At(this, 0x48),
                              F32At(this, 0x54), (U16At(this, 0x28) >> 7) & 0xFF);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::IsDrawAlphaLight()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80029094
 * PAL Size: 820b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::Draw(unsigned char priority)
{
    if ((U8At(this, 0x15) != priority) || ((U8At(this, 0x18) & 4) == 0)) {
        return;
    }

    _GXColor mapColor;
    _GXColor lightColor;
    _GXColor* worldMapColor = reinterpret_cast<_GXColor*>(&DAT_8032e498);
    unsigned char* mapMng = reinterpret_cast<unsigned char*>(&MapMng);
    unsigned char* materialMan = reinterpret_cast<unsigned char*>(&MaterialMan);

    Vec lightPos;
    lightPos.x = F32At(this, 0xC4);
    lightPos.y = F32At(this, 0xD4);
    lightPos.z = F32At(this, 0xE4);
    LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(1), &lightPos, S32At(this, 0x38));

    *reinterpret_cast<unsigned int*>(materialMan + 72) = 0xACE0F;
    *reinterpret_cast<unsigned int*>(materialMan + 68) = 0xFFFFFFFF;
    *(materialMan + 76) = 0xFF;
    *reinterpret_cast<unsigned int*>(materialMan + 296) = 0;
    *reinterpret_cast<unsigned int*>(materialMan + 284) = 0;
    *reinterpret_cast<unsigned int*>(materialMan + 300) = 0x1E;
    *reinterpret_cast<unsigned int*>(materialMan + 288) = 0x1E;
    *reinterpret_cast<unsigned int*>(materialMan + 304) = 0;
    *reinterpret_cast<unsigned int*>(materialMan + 292) = 0;
    *(materialMan + 517) = 0xFF;
    *(materialMan + 518) = 0xFF;
    *reinterpret_cast<unsigned int*>(materialMan + 88) = 0;
    *reinterpret_cast<unsigned int*>(materialMan + 92) = 0;
    *(materialMan + 520) = 0;

    if (U8At(this, 0x22) != 0) {
        CameraPcs.SetFullScreenShadow(MtxAt(this, 0xB8), 0);
    }
    if (S32At(this, 0x3C) != 0) {
        MaterialMan.SetShadowBound(static_cast<CMapShadow::TARGET>(1),
                                   reinterpret_cast<CBound*>(reinterpret_cast<unsigned char*>(PtrAt(this, 0xC)) + 0xC),
                                   MtxAt(this, 0xB8));
    }

    *reinterpret_cast<unsigned int*>(materialMan + 296) = *reinterpret_cast<unsigned int*>(materialMan + 284);
    *reinterpret_cast<unsigned int*>(materialMan + 300) = *reinterpret_cast<unsigned int*>(materialMan + 288);
    *reinterpret_cast<unsigned int*>(materialMan + 304) = *reinterpret_cast<unsigned int*>(materialMan + 292);
    *reinterpret_cast<unsigned int*>(materialMan + 64) = *reinterpret_cast<unsigned int*>(materialMan + 72);

    worldMapColor->a = U8At(this, 0x23);
    if (U8At(this, 0x21) == 0) {
        mapColor.r = mapMng[0x2298C];
        mapColor.g = mapMng[0x2298D];
        mapColor.b = mapMng[0x2298E];
        mapColor.a = mapMng[0x2298F];
    } else {
        mapColor = *reinterpret_cast<_GXColor*>(Ptr(this, 0xE8));
    }

    if (mapMng[0x22989] != 0) {
        mapColor.r = static_cast<unsigned char>((mapColor.r * mapMng[0x22990]) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * mapMng[0x22991]) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * mapMng[0x22992]) >> 8);
        mapColor.a = static_cast<unsigned char>((mapColor.a * mapMng[0x22993]) >> 8);
    }

    if (U8At(this, 0x24) != 0xFF) {
        unsigned int alphaRate = U8At(this, 0x24);
        mapColor.r = static_cast<unsigned char>((mapColor.r * alphaRate) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * alphaRate) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * alphaRate) >> 8);
    }

    lightColor = *worldMapColor;
    LightPcs.SetMapColorAlpha(MtxAt(this, 0xB8), mapColor, lightColor, U8At(this, 0x26), F32At(this, 0x44), F32At(this, 0x48),
                              F32At(this, 0x54), (U16At(this, 0x28) >> 7) & 0xFF);
    LightPcs.SetBumpTexMatirx(MtxAt(this, 0xB8), reinterpret_cast<CLightPcs::CBumpLight*>(PtrAt(this, 0x10)),
                              reinterpret_cast<Vec*>(Ptr(this, 0x58)), U8At(this, 0x1A));

    if (kMapObjOne != F32At(this, 0x40)) {
        CameraPcs.SetOffsetZBuff(F32At(this, 0x40));
    }
    if (U8At(this, 0x27) != 0) {
        GXSetZMode(1, GX_LEQUAL, 0);
    }

    CMapMesh* mapMesh = reinterpret_cast<CMapMesh*>(PtrAt(this, 0xC));
    mapMesh->SetRenderArray();
    mapMesh->Draw(0);

    if (U8At(this, 0x27) != 0) {
        GXSetZMode(1, GX_LEQUAL, 1);
    }
    if (kMapObjOne != F32At(this, 0x40)) {
        CameraPcs.SetOffsetZBuff(F32At(this, 0x40));
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028FD8
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetDrawFlag()
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    self[0x18] &= 0xFB;

    if ((static_cast<signed char>(self[0x1D]) == 1) && (*reinterpret_cast<void**>(self + 0xC) != 0)) {
        if ((static_cast<signed char>(self[0x1F]) == -1) && ((self[0x18] & 1) != 0)) {
            Mtx concatMtx;
            unsigned char* mapMng = reinterpret_cast<unsigned char*>(&MapMng);
            CBound* bound = reinterpret_cast<CBound*>(reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(self + 0xC)) + 0xC);

            PSMTXConcat(*reinterpret_cast<Mtx*>(mapMng + 0x22958), *reinterpret_cast<Mtx*>(self + 0xB8), concatMtx);
            if (bound->CheckFrustum(*reinterpret_cast<Vec*>(mapMng + 0x228EC), concatMtx, *reinterpret_cast<float*>(mapMng + 0x22A74)) != 0) {
                self[0x18] |= 4;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028F70
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::DrawHit()
{
    if ((U8At(this, 0x1D) == 2) && (PtrAt(this, 0xC) != 0)) {
        MaterialMan.SetObjMatrix(reinterpret_cast<float(*)[4]>(0x8026805C), MtxAt(this, 0xB8));
        reinterpret_cast<CMapHit*>(PtrAt(this, 0xC))->Draw();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028F08
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::DrawHitWire()
{
    if ((U8At(this, 0x1D) == 2) && (PtrAt(this, 0xC) != 0)) {
        MaterialMan.SetObjMatrix(reinterpret_cast<float(*)[4]>(0x8026805C), MtxAt(this, 0xB8));
        reinterpret_cast<CMapHit*>(PtrAt(this, 0xC))->DrawWire();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028EA0
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::DrawHitNormal()
{
    if ((U8At(this, 0x1D) == 2) && (PtrAt(this, 0xC) != 0)) {
        MaterialMan.SetObjMatrix(reinterpret_cast<float(*)[4]>(0x8026805C), MtxAt(this, 0xB8));
        reinterpret_cast<CMapHit*>(PtrAt(this, 0xC))->DrawNormal();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80028BC0
 * PAL Size: 736b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapObj::CheckHitCylinder(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((U8At(this, 0x1D) != 2) || (PtrAt(this, 0xC) == 0) || (U8At(this, 0x1F) != 0xFF)) {
        return 0;
    }

    Mtx inverseMtx;
    CMapCylinder localCylinder;
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(PtrAt(this, 0xC));

    PSMTXInverse(MtxAt(this, 0xB8), inverseMtx);
    PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &localCylinder.m_bottom);
    PSMTXMultVec(inverseMtx, &cylinder->m_direction, &localCylinder.m_direction);

    localCylinder.m_top.y = cylinder->m_top.y;
    float margin = kMapObjZero + localCylinder.m_top.y;

    float minValue = localCylinder.m_direction.x;
    float maxValue = localCylinder.m_bottom.x;
    if (maxValue < minValue) {
        minValue = localCylinder.m_bottom.x;
        maxValue = localCylinder.m_direction.x;
    }
    localCylinder.m_direction2.z = maxValue + margin;
    localCylinder.m_top.z = minValue - margin;

    minValue = localCylinder.m_direction.y;
    maxValue = localCylinder.m_bottom.y;
    if (maxValue < minValue) {
        minValue = localCylinder.m_bottom.y;
        maxValue = localCylinder.m_direction.y;
    }
    localCylinder.m_radius2 = maxValue + margin;
    localCylinder.m_direction2.x = minValue - margin;

    minValue = localCylinder.m_direction.z;
    maxValue = localCylinder.m_bottom.z;
    if (maxValue < minValue) {
        minValue = localCylinder.m_bottom.z;
        maxValue = localCylinder.m_direction.z;
    }
    localCylinder.m_height2 = maxValue + margin;
    localCylinder.m_direction2.y = minValue - margin;

    bool xOverlap;
    if (localCylinder.m_top.z <= mapHit->m_positionMin.x) {
        if (mapHit->m_positionMin.x <= localCylinder.m_top.z) {
            xOverlap = true;
        } else {
            xOverlap = mapHit->m_positionMin.x <= localCylinder.m_direction2.z;
        }
    } else {
        xOverlap = localCylinder.m_top.z <= mapHit->m_positionMax.x;
    }

    bool xyOverlap = false;
    if (xOverlap) {
        bool yOverlap;
        if (localCylinder.m_direction2.x <= mapHit->m_positionMin.y) {
            if (mapHit->m_positionMin.y <= localCylinder.m_direction2.x) {
                yOverlap = true;
            } else {
                yOverlap = mapHit->m_positionMin.y <= localCylinder.m_radius2;
            }
        } else {
            yOverlap = localCylinder.m_direction2.x <= mapHit->m_positionMax.y;
        }
        if (yOverlap) {
            xyOverlap = true;
        }
    }

    if (xyOverlap) {
        bool zOverlap;
        if (localCylinder.m_direction2.y <= mapHit->m_positionMin.z) {
            if (mapHit->m_positionMin.z <= localCylinder.m_direction2.y) {
                zOverlap = true;
            } else {
                zOverlap = mapHit->m_positionMin.z <= localCylinder.m_height2;
            }
        } else {
            zOverlap = localCylinder.m_direction2.y <= mapHit->m_positionMax.z;
        }

        if (zOverlap) {
            Vec localMove;
            PSMTXMultVecSR(inverseMtx, reinterpret_cast<Vec*>(&cylinder->m_radius), reinterpret_cast<Vec*>(&localCylinder.m_radius));
            PSMTXMultVecSR(inverseMtx, move, &localMove);
            if (mapHit->CheckHitCylinder(&localCylinder, &localMove, mask) != 0) {
                return 1;
            }
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800288F4
 * PAL Size: 716b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapObj::CheckHitCylinderNear(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((U8At(this, 0x1D) != 2) || (PtrAt(this, 0xC) == 0) || (U8At(this, 0x1F) != 0xFF)) {
        return 0;
    }

    Mtx inverseMtx;
    CMapCylinder localCylinder;
    Vec localMove;
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(PtrAt(this, 0xC));

    PSMTXInverse(MtxAt(this, 0xB8), inverseMtx);
    PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &localCylinder.m_bottom);
    PSMTXMultVec(inverseMtx, &cylinder->m_direction, &localCylinder.m_direction);
    PSMTXMultVecSR(inverseMtx, reinterpret_cast<Vec*>(&cylinder->m_radius), reinterpret_cast<Vec*>(&localCylinder.m_radius));
    PSMTXMultVecSR(inverseMtx, move, &localMove);

    localCylinder.m_top.y = cylinder->m_top.y;
    float margin = kMapObjZero + localCylinder.m_top.y;

    float minValue = localCylinder.m_direction.x;
    float maxValue = localCylinder.m_bottom.x;
    if (maxValue < minValue) {
        minValue = localCylinder.m_bottom.x;
        maxValue = localCylinder.m_direction.x;
    }
    localCylinder.m_direction2.z = maxValue + margin;
    localCylinder.m_top.z = minValue - margin;

    minValue = localCylinder.m_direction.y;
    maxValue = localCylinder.m_bottom.y;
    if (maxValue < minValue) {
        minValue = localCylinder.m_bottom.y;
        maxValue = localCylinder.m_direction.y;
    }
    localCylinder.m_radius2 = maxValue + margin;
    localCylinder.m_direction2.x = minValue - margin;

    minValue = localCylinder.m_direction.z;
    maxValue = localCylinder.m_bottom.z;
    if (maxValue < minValue) {
        minValue = localCylinder.m_bottom.z;
        maxValue = localCylinder.m_direction.z;
    }
    localCylinder.m_height2 = maxValue + margin;
    localCylinder.m_direction2.y = minValue - margin;

    bool xOverlap;
    if (localCylinder.m_top.z <= mapHit->m_positionMin.x) {
        if (mapHit->m_positionMin.x <= localCylinder.m_top.z) {
            xOverlap = true;
        } else {
            xOverlap = mapHit->m_positionMin.x <= localCylinder.m_direction2.z;
        }
    } else {
        xOverlap = localCylinder.m_top.z <= mapHit->m_positionMax.x;
    }

    bool xyOverlap = false;
    if (xOverlap) {
        bool yOverlap;
        if (localCylinder.m_direction2.x <= mapHit->m_positionMin.y) {
            if (mapHit->m_positionMin.y <= localCylinder.m_direction2.x) {
                yOverlap = true;
            } else {
                yOverlap = mapHit->m_positionMin.y <= localCylinder.m_radius2;
            }
        } else {
            yOverlap = localCylinder.m_direction2.x <= mapHit->m_positionMax.y;
        }
        if (yOverlap) {
            xyOverlap = true;
        }
    }

    if (xyOverlap) {
        bool zOverlap;
        if (localCylinder.m_direction2.y <= mapHit->m_positionMin.z) {
            if (mapHit->m_positionMin.z <= localCylinder.m_direction2.y) {
                zOverlap = true;
            } else {
                zOverlap = mapHit->m_positionMin.z <= localCylinder.m_height2;
            }
        } else {
            zOverlap = localCylinder.m_direction2.y <= mapHit->m_positionMax.z;
        }

        if (zOverlap) {
            PSMTXMultVecSR(inverseMtx, reinterpret_cast<Vec*>(&cylinder->m_radius), reinterpret_cast<Vec*>(&localCylinder.m_radius));
            PSMTXMultVecSR(inverseMtx, move, &localMove);
            mapHit->CheckHitCylinderNear(&localCylinder, &localMove, mask);
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800288a8
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::GetHitFaceNormal(Vec* out)
{
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(PtrAt(this, 0xC));
    mapHit->GetHitFaceNormal(out);
    PSMTXMultVecSR(MtxAt(this, 0xB8), out, out);
}

/*
 * --INFO--
 * PAL Address: 0x8002884c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapObj::CalcHitSlide(Vec* out, float y)
{
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(PtrAt(this, 0xC));
    int hit = mapHit->CalcHitSlide(out, y);
    PSMTXMultVecSR(MtxAt(this, 0xB8), out, out);
    return hit;
}

/*
 * --INFO--
 * PAL Address: 0x80028800
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::CalcHitPosition(Vec* out)
{
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(PtrAt(this, 0xC));
    mapHit->CalcHitPosition(out);
    PSMTXMultVec(MtxAt(this, 0xB8), out, out);
}

/*
 * --INFO--
 * PAL Address: 0x800287D0
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::SetMime(int mode, int target, int type)
{
    unsigned char* mime = reinterpret_cast<unsigned char*>(PtrAt(this, 0xEC));

    *reinterpret_cast<int*>(mime + 0x20) = mode;
    *reinterpret_cast<int*>(mime + 0x1C) = mode;

    if (target > *reinterpret_cast<int*>(mime + 0x28)) {
        target = *reinterpret_cast<int*>(mime + 0x28);
    }

    *reinterpret_cast<int*>(mime + 0x24) = target;
    *(mime + 0x17) = static_cast<unsigned char>(type);
    *(mime + 0x18) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8002BE34
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObjAtr::~CMapObjAtr()
{
}

static inline void FreeAndClear(void* base, unsigned int offset)
{
    void*& ptr = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(base) + offset);
    if (ptr != 0) {
        __dl__FPv(ptr);
        ptr = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrPlaySta::CMapObjAtrPlaySta()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtr::CMapObjAtr()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrMime::CMapObjAtrMime()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapObj::SetCalcMtx()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapObjAtrMeshName::CMapObjAtrMeshName()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002C3E8
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObjAtrMeshName::~CMapObjAtrMeshName()
{
}

/*
 * --INFO--
 * PAL Address: 0x8002C2AC
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObjAtrPointLight::~CMapObjAtrPointLight()
{
    FreeAndClear(this, 0xE4);
    FreeAndClear(this, 0xE8);
    FreeAndClear(this, 0xEC);
    FreeAndClear(this, 0xF0);
    FreeAndClear(this, 0xBC);
    FreeAndClear(this, 0xC0);
    FreeAndClear(this, 0xC4);
    FreeAndClear(this, 0xC8);
}

/*
 * --INFO--
 * PAL Address: 0x8002C170
 * PAL Size: 316b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObjAtrSpotLight::~CMapObjAtrSpotLight()
{
    FreeAndClear(this, 0x100);
    FreeAndClear(this, 0x104);
    FreeAndClear(this, 0x108);
    FreeAndClear(this, 0x10C);
    FreeAndClear(this, 0xD8);
    FreeAndClear(this, 0xDC);
    FreeAndClear(this, 0xE0);
    FreeAndClear(this, 0xE4);
}

/*
 * --INFO--
 * PAL Address: 0x8002C04C
 * PAL Size: 292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObjAtrMime::~CMapObjAtrMime()
{
    int* self = reinterpret_cast<int*>(this);
    int i = 0;
    int offset = 0;

    while (i < static_cast<int>(*reinterpret_cast<unsigned char*>(self + 2))) {
        void** entry = reinterpret_cast<void**>(self[3] + offset);
        if (*entry != 0) {
            __dl__FPv(*entry);
            *entry = 0;
        }

        offset += 4;
        i++;
    }

    if (self[3] != 0) {
        __dl__FPv(reinterpret_cast<void*>(self[3]));
        self[3] = 0;
    }

    FreeAndClear(this, 0x2C);
    FreeAndClear(this, 0x30);
    FreeAndClear(this, 0x34);
    FreeAndClear(this, 0x38);
}

/*
 * --INFO--
 * PAL Address: 0x8002BFF0
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObjAtrPlaySta::~CMapObjAtrPlaySta()
{
}
