#include "ffcc/mapobj.h"

extern const char s_CPtrArrayGrowError[];
extern const char s_CPtrArrayFile[];
#define FFCC_PTRARRAY_GROW_ERROR s_CPtrArrayGrowError
#define FFCC_PTRARRAY_FILE s_CPtrArrayFile
#include "ffcc/ptrarray.h"
#undef FFCC_PTRARRAY_GROW_ERROR
#undef FFCC_PTRARRAY_FILE

#include "ffcc/map.h"
#include "ffcc/mapanim.h"
#include "ffcc/chunkfile.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/math.h"
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/p_light.h"
#include "ffcc/system.h"
#include "ffcc/memory.h"
#include <dolphin/mtx.h>
#include <dolphin/os/OSCache.h>
#include <string.h>
#include <PowerPC_EABI_Support/Runtime/New.h>

static const float kMapObjBoundMinInit = 10000000000.0f;
static const float kMapObjBoundMaxInit = -10000000000.0f;
static const float kMapObjZero = 1.0f;
static const float kMapObjOne = 0.0f;
static const float kMapObjInitNegOne = 1000000000000000.0f;
static const float kMapObjColorBlendScale = 255.0f;
static const float kMapObjDegToRad = 0.017453292f;
static const float kMapObjInitValue50 = -1.0f;
extern const char s_mapobj_cpp[] = "mapobj.cpp";
extern const char sMapObjScaleWithoutNameWarn[0x78] = {
    (char)0x83, (char)0x47, (char)0x83, (char)0x89, (char)0x81, (char)0x5b, (char)0x81, (char)0x49,
    (char)0x81, (char)0x49, (char)0x81, (char)0x49, (char)0x20, (char)0x67, (char)0x72, (char)0x6f,
    (char)0x75, (char)0x6e, (char)0x64, (char)0x5f, (char)0x61, (char)0x20, (char)0x6f, (char)0x72,
    (char)0x20, (char)0x6f, (char)0x62, (char)0x6a, (char)0x5f, (char)0x61, (char)0x20, (char)0x83,
    (char)0x6d, (char)0x81, (char)0x5b, (char)0x83, (char)0x68, (char)0x20, (char)0x82, (char)0xcc,
    (char)0x83, (char)0x58, (char)0x83, (char)0x50, (char)0x81, (char)0x5b, (char)0x83, (char)0x8b,
    (char)0x82, (char)0xaa, (char)0x20, (char)0x82, (char)0x50, (char)0x20, (char)0x82, (char)0xc5,
    (char)0x82, (char)0xcd, (char)0x82, (char)0xc8, (char)0x82, (char)0xa2, (char)0x81, (char)0x42,
    (char)0x0a, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x8c, (char)0xc3,
    (char)0x82, (char)0xa2, (char)0x83, (char)0x6f, (char)0x81, (char)0x5b, (char)0x83, (char)0x57,
    (char)0x83, (char)0x87, (char)0x83, (char)0x93, (char)0x82, (char)0xcc, (char)0x20, (char)0x82,
    (char)0x6e, (char)0x82, (char)0x73, (char)0x82, (char)0x6c, (char)0x82, (char)0xc8, (char)0x82,
    (char)0xcc, (char)0x82, (char)0xc5, (char)0x83, (char)0x6d, (char)0x81, (char)0x5b, (char)0x83,
    (char)0x68, (char)0x96, (char)0xbc, (char)0x82, (char)0xcd, (char)0x95, (char)0x73, (char)0x96,
    (char)0xbe, (char)0x82, (char)0xc5, (char)0x82, (char)0xb7, (char)0x81, (char)0x42, (char)0x00,
};
extern const char sMapObjScaleWithNameWarn[0x48] = {
    (char)0x83, (char)0x47, (char)0x83, (char)0x89, (char)0x81, (char)0x5b, (char)0x81, (char)0x49,
    (char)0x81, (char)0x49, (char)0x81, (char)0x49, (char)0x20, (char)0x67, (char)0x72, (char)0x6f,
    (char)0x75, (char)0x6e, (char)0x64, (char)0x5f, (char)0x61, (char)0x20, (char)0x6f, (char)0x72,
    (char)0x20, (char)0x6f, (char)0x62, (char)0x6a, (char)0x5f, (char)0x61, (char)0x20, (char)0x83,
    (char)0x6d, (char)0x81, (char)0x5b, (char)0x83, (char)0x68, (char)0x20, (char)0x25, (char)0x73,
    (char)0x20, (char)0x82, (char)0xcc, (char)0x83, (char)0x58, (char)0x83, (char)0x50, (char)0x81,
    (char)0x5b, (char)0x83, (char)0x8b, (char)0x82, (char)0xaa, (char)0x20, (char)0x82, (char)0x50,
    (char)0x20, (char)0x82, (char)0xc5, (char)0x82, (char)0xcd, (char)0x82, (char)0xc8, (char)0x82,
    (char)0xa2, (char)0x81, (char)0x42, (char)0x0a, (char)0x00, (char)0x00, (char)0x00, (char)0x00,
};
extern const char sMapObjTooManyAttributesWarn[0x34] = {
    (char)0x6e, (char)0x6f, (char)0x64, (char)0x65, (char)0x20, (char)0x25, (char)0x64, (char)0x20,
    (char)0x82, (char)0xcd, (char)0x82, (char)0xb1, (char)0x82, (char)0xea, (char)0x88, (char)0xc8,
    (char)0x8f, (char)0xe3, (char)0x83, (char)0x41, (char)0x83, (char)0x67, (char)0x83, (char)0x8a,
    (char)0x83, (char)0x72, (char)0x83, (char)0x85, (char)0x81, (char)0x5b, (char)0x83, (char)0x67,
    (char)0x82, (char)0xf0, (char)0x92, (char)0xc7, (char)0x89, (char)0xc1, (char)0x82, (char)0xc5,
    (char)0x82, (char)0xab, (char)0x82, (char)0xdc, (char)0x82, (char)0xb9, (char)0x82, (char)0xf1,
    (char)0x81, (char)0x42, (char)0x0a, (char)0x00,
};
_GXColor s_mapObjLightColor = {0xFF, 0xFF, 0xFF, 0xFF};

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

namespace {
static inline CMapObj* NextSlot(CMapObj* obj)
{
    return obj + 1;
}

static inline CMapObj* MapObjArrayStart()
{
    return MapMng.GetMapObjArray();
}

static inline Mtx& MapObjHitDrawMtx()
{
    return MapMng.m_viewMtx;
}

static inline float LoadFloat(const float& value)
{
    return value;
}

static inline float LoadFloatVolatile(const volatile float& value)
{
    return value;
}

}

/*
 * --INFO--
 * PAL Address: 0x8002C444
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimRun*>::Add(CMapAnimRun* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }

    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8002C4B4
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimRun*>::setSize(unsigned long newSize)
{
    CMapAnimRun** newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(const_cast<char*>(s_CPtrArrayGrowError));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CMapAnimRun**>(Memory._Alloc(m_size * sizeof(CMapAnimRun*), m_stage,
                                                            const_cast<char*>(s_CPtrArrayFile), 0xfa, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems * sizeof(CMapAnimRun*));
        }

        if (m_items != 0) {
            delete[] m_items;
            m_items = 0;
        }

        m_items = newItems;
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8002C5A4
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapShadow*>::Add(CMapShadow* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }

    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8002C614
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapShadow*>::setSize(unsigned long newSize)
{
    CMapShadow** newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(const_cast<char*>(s_CPtrArrayGrowError));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CMapShadow**>(Memory._Alloc(m_size * sizeof(CMapShadow*), m_stage,
                                                           const_cast<char*>(s_CPtrArrayFile), 0xfa, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems * sizeof(CMapShadow*));
        }

        if (m_items != 0) {
            delete[] m_items;
            m_items = 0;
        }

        m_items = newItems;
    }

    return 1;
}

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
    float max = kMapObjBoundMaxInit;
    float min = kMapObjBoundMinInit;

    m_min.z = min;
    m_min.y = min;
    m_min.x = min;
    m_max.z = max;
    m_max.y = max;
    m_max.x = max;
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
    if (m_attribute != 0) {
        delete m_attribute;
        m_attribute = 0;
    }

    Init();
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
    m_calcMtxPending = 1;
    m_localMtxDirty = 1;
    m_parent = 0;
    m_mapData = 0;
    m_attribute = 0;

    m_drawPriority = 0x7E;
    m_baseDrawPriority = 0x7E;
    m_octTreeIndex = -1;
    m_unknown20 = 0;
    m_disableZWrite = 0;
    m_useAmbientColor = 0;

    m_objId = 0xFFFF;
    m_effectId = 0xFFFF;
    m_groupId = 0xFFFF;
    m_showFlags = 1;
    m_unknown19 = 1;
    m_meshId = 0xFFFF;

    m_cameraSemiTransFar = kMapObjInitNegOne;
    m_cameraSemiTransNear = kMapObjInitNegOne;
    m_cameraSemiTransMinAlpha = kMapObjInitNegOne;
    m_cameraSemiTransMaxAlpha = kMapObjInitValue50;

    m_cameraSemiTransStep = 0;
    m_cameraSemiTransTargetAlpha = 0;
    m_cameraSemiTransAlpha = 0;
    m_colorAlphaRate = 0xFF;
    m_lightAlpha = 0xFF;
    m_bumpLight = 0;
    m_bumpObjId = -1;
    m_enableFullScreenShadow = 1;
    m_shadowTarget = -1;

    m_transRateZ = kMapObjOne;
    m_transRateY = kMapObjOne;
    m_transRateX = kMapObjOne;
    m_bumpTexMatrixMode = 0;
    m_zBufferOffset = kMapObjOne;
    m_cameraSemiTransBeyondMax = 1;
    m_cameraSemiTransActive = 0;
    m_lightSetIndex = -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CMapObjAtr::CMapObjAtr()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CMapObjAtrPlaySta::CMapObjAtrPlaySta()
{
    m_type = CMapObjAtr::PLAY_STA;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CMapObjAtrMime::CMapObjAtrMime()
{
    InitMapObjAtrColorKeyFrame(m_keyFrame);
    m_type = CMapObjAtr::MIME;
    m_vertexLists = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline CMapObjAtrMeshName::CMapObjAtrMeshName()
{
    m_type = CMapObjAtr::MESH_NAME;
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
int CMapObj::ReadOtmObj(CChunkFile& chunkFile)
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
        CHUNK_LDAT = 0x4C444154,
        CHUNK_LSDW = 0x4C534457,
        CHUNK_MIME = 0x4D494D45,
        CHUNK_MSID = 0x4D534944,
        CHUNK_PIDX = 0x50494458,
        CHUNK_PLIT = 0x504C4954,
        CHUNK_PSTA = 0x50535441,
        CHUNK_PRIO = 0x5052494F,
        CHUNK_SDST = 0x53445354,
        CHUNK_SLIT = 0x534C4954,
        CHUNK_TFRM = 0x5446524D,
        CHUNK_TRNS = 0x54524E53,
        CHUNK_CFRM = 0x4346524D,
        CHUNK_CJUN = 0x434A554E,
        CHUNK_CKEY = 0x434B4559,
        CHUNK_FRAM = 0x4652414D,
        CHUNK_JUN = 0x4A554E20,
        CHUNK_KEY = 0x4B455920,
        CHUNK_MFRM = 0x4D46524D,
        CHUNK_MJUN = 0x4D4A554E,
        CHUNK_MKEY = 0x4D4B4559,
        CHUNK_VTX = 0x56545820,
        CHUNK_VTXL = 0x5654584C,
    };

    Init();

    chunkFile.PushChunk();
    int objIndex = this - MapObjArrayStart();
    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk) != 0) {
        switch (chunk.m_id) {
        case CHUNK_FSDW: {
            CameraPcs.m_fullScreenShadowEnabled = chunkFile.Get1();
            break;
        }
        case CHUNK_ID: {
            m_objId = chunkFile.Get2();
            break;
        }
        case CHUNK_MSID: {
            m_meshId = static_cast<unsigned short>(chunkFile.Get4());
            break;
        }
        case CHUNK_PRIO: {
            unsigned char priority = chunkFile.Get1();
            m_drawPriority = priority;
            m_baseDrawPriority = priority;
            break;
        }
        case CHUNK_LTST: {
            if (chunk.m_version == 1) {
                m_lightSetIndex = static_cast<int>(chunkFile.Get4());
            } else if (chunkFile.Get1() == 0) {
                m_lightSetIndex = 0;
            }
            break;
        }
        case CHUNK_LSDW: {
            break;
        }
        case CHUNK_PIDX: {
            short parentIdx = static_cast<short>(chunkFile.Get2());
            int meshOrHitIdx = static_cast<short>(chunkFile.Get2());

            m_meshType = chunkFile.Get1();
            m_mapDataType = chunkFile.Get1();

            if (parentIdx == -1) {
                m_parent = 0;
            } else {
                m_parent = MapMng.m_mapObjArray + parentIdx;
            }

            if (meshOrHitIdx == -1) {
                m_mapData = 0;
            } else if (m_mapDataType == 1) {
                m_mapData = MapMng.GetMapMeshArray() + meshOrHitIdx;
                m_baseDrawPriority = 0;
                m_drawPriority = 0;
            } else if ((m_mapDataType == 2) || (m_mapDataType == 3)) {
                if (meshOrHitIdx != -2) {
                    m_mapData = MapMng.GetMapHitArray() + meshOrHitIdx;
                } else {
                    CMapObjAtrMeshName* meshName =
                        new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x84) CMapObjAtrMeshName();
                    m_attribute = meshName;
                    char* name = chunkFile.GetString();
                    strncpy(meshName->m_name, name, 0x20);
                }
            }

            if (((Game.m_currentSceneId == 4) || (Game.m_currentSceneId == 7)) &&
                (m_meshType < 10) && (m_meshType >= 8)) {
                m_transRateX = kMapObjZero;
                m_transRateY = kMapObjOne;
                m_transRateZ = kMapObjZero;
            }
            break;
        }
        case CHUNK_TRNS: {
            m_transRateX = chunkFile.GetF4();
            m_transRateY = chunkFile.GetF4();
            m_transRateZ = chunkFile.GetF4();
            break;
        }
        case CHUNK_SDST: {
            if (chunk.m_version == 2) {
                m_enableFullScreenShadow = chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                m_shadowTarget = static_cast<int>(chunkFile.Get4());
            } else if (chunk.m_version == 1) {
                m_enableFullScreenShadow = chunkFile.Get1();
                if (chunkFile.Get1() == 0) {
                    m_shadowTarget = 0;
                } else {
                    m_shadowTarget = -1;
                }
            } else {
                m_enableFullScreenShadow = chunkFile.Get1();
                m_shadowTarget = -1;
            }
            break;
        }
        case CHUNK_TFRM: {
            m_localTranslateX = chunkFile.GetF4();
            m_localTranslateY = chunkFile.GetF4();
            m_localTranslateZ = chunkFile.GetF4();
            m_localRotationX = chunkFile.GetF4();
            m_localRotationY = chunkFile.GetF4();
            m_localRotationZ = chunkFile.GetF4();
            m_localScaleX = chunkFile.GetF4();
            m_localScaleY = chunkFile.GetF4();
            m_localScaleZ = chunkFile.GetF4();

            if (((m_mapDataType == 2) || (m_mapDataType == 3)) &&
                ((kMapObjZero != m_localScaleX) || (kMapObjZero != m_localScaleY) || (kMapObjZero != m_localScaleZ))) {
                if (m_attribute == 0) {
                    System.Printf(const_cast<char*>(sMapObjScaleWithoutNameWarn));
                } else {
                    System.Printf(const_cast<char*>(sMapObjScaleWithNameWarn),
                                  reinterpret_cast<CMapObjAtrMeshName*>(m_attribute)->m_name);
                }
                m_localScaleX = kMapObjZero;
                m_localScaleY = kMapObjZero;
                m_localScaleZ = kMapObjZero;
            }

            m_localMtxDirty = 1;
            m_calcMtxPending = 1;
            break;
        }
        case CHUNK_EFID: {
            m_effectId = chunkFile.Get2();
            break;
        }
        case CHUNK_MIME: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrMime* mimeAttr =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x33B) CMapObjAtrMime();
            CMapObjAtrMime* mime = mimeAttr;

            chunkFile.PushChunk();
            CChunkFile::CChunk mimeChunk;
            while (chunkFile.GetNextChunk(mimeChunk) != 0) {
                if (mimeChunk.m_id == CHUNK_KEY) {
                    mime->m_keyFrame.ReadKey(chunkFile, mimeChunk.m_arg0);
                } else if (mimeChunk.m_id == CHUNK_JUN) {
                    mime->m_keyFrame.ReadJun(chunkFile, static_cast<char>(mimeChunk.m_arg0));
                } else if (mimeChunk.m_id == CHUNK_FRAM) {
                    mime->m_keyFrame.ReadFrame(chunkFile, mimeChunk.m_arg0);
                } else if (mimeChunk.m_id == CHUNK_VTXL) {
                    mime->m_vertexListCount = static_cast<unsigned char>(mimeChunk.m_arg0);
                    mime->m_vertexLists = reinterpret_cast<float**>(
                        operator new[](static_cast<unsigned long>(mime->m_vertexListCount) << 2,
                                       MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x348));

                    chunkFile.PushChunk();
                    CChunkFile::CChunk vtxChunk;
                    int vtxTableIndex = 0;
                    while (chunkFile.GetNextChunk(vtxChunk) != 0) {
                        if (vtxChunk.m_id == CHUNK_VTX) {
                            float* vtx = reinterpret_cast<float*>(operator new[](
                                static_cast<unsigned long>(vtxChunk.m_arg0) * 0xC,
                                MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x353));
                            mime->m_vertexLists[vtxTableIndex] = vtx;
                            vtxTableIndex++;
                            mime->m_vertexCount = static_cast<int>(vtxChunk.m_arg0);

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
            m_attribute = mimeAttr;
            break;
        }
        case CHUNK_SLIT: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrSpotLight* spotLightAttr =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x139) CMapObjAtrSpotLight();
            CMapObjAtrSpotLight* spotLight = spotLightAttr;

            if (chunk.m_version == 6) {
                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk) != 0) {
                    if (chunk.m_id == CHUNK_LDAT) {
                        spotLight->m_baseColor.r = chunkFile.Get1();
                        spotLight->m_baseColor.g = chunkFile.Get1();
                        spotLight->m_baseColor.b = chunkFile.Get1();
                        spotLight->m_baseColor.a = chunkFile.Get1();
                        spotLight->m_radius = chunkFile.GetF4();
                        spotLight->m_nearRange = chunkFile.GetF4();
                        spotLight->m_farRange = chunkFile.GetF4();
                        spotLight->m_intensity = chunkFile.GetF4();
                        chunkFile.GetF4();
                        spotLight->m_falloff = chunkFile.GetF4();
                        unsigned short targetIndex = chunkFile.Get2();
                        spotLight->m_target = MapMng.m_mapObjArray + targetIndex;
                        spotLight->m_colorMode = chunkFile.Get1();
                        spotLight->m_useAltColor = chunkFile.Get1();
                        spotLight->m_angle = chunkFile.GetF4();
                        spotLight->m_unknown2E = chunkFile.Get1();
                        spotLight->m_unknown2F = chunkFile.Get1();
                        spotLight->m_keyFrameCount = chunkFile.Get1();
                        chunkFile.Get1();
                        chunkFile.Get4();
                        chunkFile.Get4();
                        chunkFile.Get4();
                        chunkFile.Get4();

                        spotLight->m_colorCount = chunkFile.Get1();
                        for (int i = 0; i < static_cast<int>(spotLight->m_colorCount); i++) {
                            spotLight->m_colors[i].r = chunkFile.Get1();
                            spotLight->m_colors[i].g = chunkFile.Get1();
                            spotLight->m_colors[i].b = chunkFile.Get1();
                            spotLight->m_colors[i].a = chunkFile.Get1();
                        }

                        spotLight->m_altColorCount = chunkFile.Get1();
                        for (int i = 0; i < static_cast<int>(spotLight->m_altColorCount); i++) {
                            spotLight->m_altColors[i].r = chunkFile.Get1();
                            spotLight->m_altColors[i].g = chunkFile.Get1();
                            spotLight->m_altColors[i].b = chunkFile.Get1();
                            spotLight->m_altColors[i].a = chunkFile.Get1();
                        }

                        spotLight->m_color = spotLight->m_colors[0];
                        spotLight->m_altColor = spotLight->m_altColors[0];
                    } else switch (chunk.m_id) {
                    case CHUNK_CFRM:
                        spotLight->m_altColorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CJUN:
                        spotLight->m_altColorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_CKEY:
                        spotLight->m_altColorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_MFRM:
                        spotLight->m_colorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_MJUN:
                        spotLight->m_colorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                        break;
                    case CHUNK_MKEY:
                        spotLight->m_colorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                        break;
                    }
                }
                chunkFile.PopChunk();
            } else if (chunk.m_version == 5) {
                spotLight->m_color.r = chunkFile.Get1();
                spotLight->m_color.g = chunkFile.Get1();
                spotLight->m_color.b = chunkFile.Get1();
                spotLight->m_color.a = chunkFile.Get1();
                spotLight->m_altColor.r = chunkFile.Get1();
                spotLight->m_altColor.g = chunkFile.Get1();
                spotLight->m_altColor.b = chunkFile.Get1();
                spotLight->m_altColor.a = chunkFile.Get1();
                spotLight->m_baseColor.r = chunkFile.Get1();
                spotLight->m_baseColor.g = chunkFile.Get1();
                spotLight->m_baseColor.b = chunkFile.Get1();
                spotLight->m_baseColor.a = chunkFile.Get1();
                spotLight->m_radius = chunkFile.GetF4();
                spotLight->m_nearRange = chunkFile.GetF4();
                spotLight->m_farRange = chunkFile.GetF4();
                spotLight->m_intensity = chunkFile.GetF4();
                chunkFile.GetF4();
                spotLight->m_falloff = chunkFile.GetF4();
                unsigned short targetIndex = chunkFile.Get2();
                spotLight->m_target = MapMng.m_mapObjArray + targetIndex;
                spotLight->m_colorMode = chunkFile.Get1();
                spotLight->m_useAltColor = chunkFile.Get1();
                spotLight->m_angle = chunkFile.GetF4();
                spotLight->m_unknown2E = chunkFile.Get1();
            }
            m_attribute = spotLightAttr;
            break;
        }
        case CHUNK_GEOM: {
            m_zBufferOffset = chunkFile.GetF4();
            m_bumpTexMatrixMode = chunkFile.Get1();
            m_disableZWrite = chunkFile.Get1();
            break;
        }
        case CHUNK_AMBI: {
            m_ambientColor.r = chunkFile.Get1();
            m_ambientColor.g = chunkFile.Get1();
            m_ambientColor.b = chunkFile.Get1();
            m_ambientColor.a = chunkFile.Get1();
            m_useAmbientColor = 1;
            break;
        }
        case CHUNK_ANIM: {
            CMapAnimRun* animRun = static_cast<CMapAnimRun*>(
                operator new(sizeof(CMapAnimRun), MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x21E));
            if (animRun != 0) {
                animRun->m_currentFrame = -1;
            }
            animRun->m_mapAnimIndex = static_cast<unsigned short>(chunkFile.Get4());
            animRun->m_startFrame = static_cast<int>(chunkFile.Get4());
            animRun->m_endFrame = static_cast<int>(chunkFile.Get4());
            animRun->m_triggerFrame = static_cast<int>(chunkFile.Get4());
            animRun->m_loop = chunkFile.Get1();
            if (chunk.m_version == 1) {
                animRun->m_animId = chunkFile.Get1();
            } else {
                animRun->m_animId = 0;
            }
            MapMng.GetMapAnimRunArray().Add(animRun);
            break;
        }
        case CHUNK_BOBJ: {
            m_bumpObjId = chunkFile.Get2();
            break;
        }
        case CHUNK_GBID: {
            m_groupId = chunkFile.Get2();
            break;
        }
        case CHUNK_PLIT: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrPointLight* pointLightAttr =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0xD4) CMapObjAtrPointLight();
            CMapObjAtrPointLight* pointLight = pointLightAttr;

            if (chunk.m_version == 2) {
                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk) != 0) {
                    if (chunk.m_id == CHUNK_LDAT) {
                        pointLight->m_radius = chunkFile.GetF4();
                        pointLight->m_intensity = chunkFile.GetF4();
                        pointLight->m_colorMode = chunkFile.Get1();
                        pointLight->m_useAltColor = chunkFile.Get1();
                        pointLight->m_unknown20 = chunkFile.Get1();
                        chunkFile.Get1();

                        unsigned char colorCount = chunkFile.Get1();
                        pointLight->m_colorCount = colorCount;
                        for (int i = 0; i < static_cast<int>(colorCount); i++) {
                            pointLight->m_colors[i].r = chunkFile.Get1();
                            pointLight->m_colors[i].g = chunkFile.Get1();
                            pointLight->m_colors[i].b = chunkFile.Get1();
                            pointLight->m_colors[i].a = chunkFile.Get1();
                        }

                        pointLight->m_altColorCount = chunkFile.Get1();
                        for (int i = 0; i < static_cast<int>(pointLight->m_altColorCount); i++) {
                            pointLight->m_altColors[i].r = chunkFile.Get1();
                            pointLight->m_altColors[i].g = chunkFile.Get1();
                            pointLight->m_altColors[i].b = chunkFile.Get1();
                            pointLight->m_altColors[i].a = chunkFile.Get1();
                        }

                        pointLight->m_color = pointLight->m_colors[0];
                        pointLight->m_altColor = pointLight->m_altColors[0];
                    } else {
                        if (static_cast<int>(chunk.m_id) < CHUNK_LDAT) {
                            if (chunk.m_id == CHUNK_CJUN) {
                                pointLight->m_altColorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                            } else if (static_cast<int>(chunk.m_id) < CHUNK_CJUN) {
                                if (chunk.m_id == CHUNK_CFRM) {
                                    pointLight->m_altColorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                                }
                            } else if (chunk.m_id == CHUNK_CKEY) {
                                pointLight->m_altColorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                            }
                        } else if (chunk.m_id == CHUNK_MJUN) {
                            pointLight->m_colorKeyFrame.ReadJun(chunkFile, chunk.m_arg0);
                        } else if (static_cast<int>(chunk.m_id) < CHUNK_MJUN) {
                            if (chunk.m_id == CHUNK_MFRM) {
                                pointLight->m_colorKeyFrame.ReadFrame(chunkFile, chunk.m_arg0);
                            }
                        } else if (chunk.m_id == CHUNK_MKEY) {
                            pointLight->m_colorKeyFrame.ReadKey(chunkFile, chunk.m_arg0);
                        }
                    }
                }
                chunkFile.PopChunk();
            } else if (static_cast<int>(chunk.m_version) == 1) {
                pointLight->m_color.r = chunkFile.Get1();
                pointLight->m_color.g = chunkFile.Get1();
                pointLight->m_color.b = chunkFile.Get1();
                pointLight->m_color.a = chunkFile.Get1();
                pointLight->m_altColor.r = chunkFile.Get1();
                pointLight->m_altColor.g = chunkFile.Get1();
                pointLight->m_altColor.b = chunkFile.Get1();
                pointLight->m_altColor.a = chunkFile.Get1();
                pointLight->m_radius = chunkFile.GetF4();
                pointLight->m_intensity = chunkFile.GetF4();
                pointLight->m_colorMode = chunkFile.Get1();
            }
            m_attribute = pointLightAttr;
            break;
        }
        case CHUNK_PSTA: {
            if (m_attribute != 0) {
                System.Printf(const_cast<char*>(sMapObjTooManyAttributesWarn), objIndex);
            }
            CMapObjAtrPlaySta* playSta =
                new (MapMng.m_stage, const_cast<char*>(s_mapobj_cpp), 0x39B) CMapObjAtrPlaySta();
            playSta->m_playStaNo = chunkFile.Get1();
            m_attribute = playSta;
            break;
        }
        }
    }
    chunkFile.PopChunk();
    return 1;
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
    Mtx mtx2;
    Mtx mtx1;
    Mtx mtx0;
    CMapObj* obj = this;

    do {
        unsigned char dirty = inDirty;

        if (obj->m_calcMtxPending != 0) {
            obj->m_calcMtxPending = 0;
            if (obj->m_localMtxDirty != 0) {
                PSMTXScale(obj->m_localMtx, obj->m_localScaleX, obj->m_localScaleY, obj->m_localScaleZ);
                PSMTXRotRad(mtx2, 'x', kMapObjDegToRad * obj->m_localRotationX);
                PSMTXConcat(mtx2, obj->m_localMtx, obj->m_localMtx);
                PSMTXRotRad(mtx2, 'y', kMapObjDegToRad * obj->m_localRotationY);
                PSMTXConcat(mtx2, obj->m_localMtx, obj->m_localMtx);
                PSMTXRotRad(mtx2, 'z', kMapObjDegToRad * obj->m_localRotationZ);
                PSMTXConcat(mtx2, obj->m_localMtx, obj->m_localMtx);
                PSMTXTrans(mtx2, obj->m_localTranslateX, obj->m_localTranslateY, obj->m_localTranslateZ);
                PSMTXConcat(mtx2, obj->m_localMtx, obj->m_localMtx);
            }

            dirty = 1;
        }

        if (dirty != 0) {
            PSMTXConcat(*reinterpret_cast<Mtx*>(parentMtx), obj->m_localMtx, obj->m_worldMtx);
        }

        CMapObj* child = obj->m_child;
        if (child != 0) {
            do {
                unsigned char childDirty = dirty;

                if (child->m_calcMtxPending != 0) {
                    child->m_calcMtxPending = 0;
                    if (child->m_localMtxDirty != 0) {
                        PSMTXScale(child->m_localMtx, child->m_localScaleX, child->m_localScaleY, child->m_localScaleZ);
                        PSMTXRotRad(mtx1, 'x', kMapObjDegToRad * child->m_localRotationX);
                        PSMTXConcat(mtx1, child->m_localMtx, child->m_localMtx);
                        PSMTXRotRad(mtx1, 'y', kMapObjDegToRad * child->m_localRotationY);
                        PSMTXConcat(mtx1, child->m_localMtx, child->m_localMtx);
                        PSMTXRotRad(mtx1, 'z', kMapObjDegToRad * child->m_localRotationZ);
                        PSMTXConcat(mtx1, child->m_localMtx, child->m_localMtx);
                        PSMTXTrans(mtx1, child->m_localTranslateX, child->m_localTranslateY, child->m_localTranslateZ);
                        PSMTXConcat(mtx1, child->m_localMtx, child->m_localMtx);
                    }

                    childDirty = 1;
                }

                if (childDirty != 0) {
                    PSMTXConcat(obj->m_worldMtx, child->m_localMtx, child->m_worldMtx);
                }

                CMapObj* grandChild = child->m_child;
                if (grandChild != 0) {
                    float (*childWorldMtx)[4] = child->m_worldMtx;
                    do {
                        unsigned char grandChildDirty = childDirty;

                        if (grandChild->m_calcMtxPending != 0) {
                            grandChild->m_calcMtxPending = 0;
                            if (grandChild->m_localMtxDirty != 0) {
                                PSMTXScale(
                                    grandChild->m_localMtx, grandChild->m_localScaleX, grandChild->m_localScaleY, grandChild->m_localScaleZ);
                                PSMTXRotRad(mtx0, 'x', kMapObjDegToRad * grandChild->m_localRotationX);
                                PSMTXConcat(mtx0, grandChild->m_localMtx, grandChild->m_localMtx);
                                PSMTXRotRad(mtx0, 'y', kMapObjDegToRad * grandChild->m_localRotationY);
                                PSMTXConcat(mtx0, grandChild->m_localMtx, grandChild->m_localMtx);
                                PSMTXRotRad(mtx0, 'z', kMapObjDegToRad * grandChild->m_localRotationZ);
                                PSMTXConcat(mtx0, grandChild->m_localMtx, grandChild->m_localMtx);
                                PSMTXTrans(mtx0, grandChild->m_localTranslateX, grandChild->m_localTranslateY, grandChild->m_localTranslateZ);
                                PSMTXConcat(mtx0, grandChild->m_localMtx, grandChild->m_localMtx);
                            }

                            grandChildDirty = 1;
                        }

                        if (grandChildDirty != 0) {
                            PSMTXConcat(childWorldMtx, grandChild->m_localMtx, grandChild->m_worldMtx);
                        }

                        if (grandChild->m_child != 0) {
                            grandChild->m_child->CalcMtx(grandChild->m_worldMtx, grandChildDirty);
                        }

                        grandChild = grandChild->m_next;
                    } while (grandChild != 0);
                }

                child = child->m_next;
            } while (child != 0);
        }

        obj = obj->m_next;
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
        if (show != 0) {
            root->m_showFlags |= 1;
        } else {
            root->m_showFlags &= 0xFE;
        }

        CMapObj* c0 = root->m_child;
        if (c0 != 0) {
            do {
                if (show != 0) {
                    c0->m_showFlags |= 1;
                } else {
                    c0->m_showFlags &= 0xFE;
                }

                CMapObj* c1 = c0->m_child;
                if (c1 != 0) {
                    do {
                        if (show != 0) {
                            c1->m_showFlags |= 1;
                        } else {
                            c1->m_showFlags &= 0xFE;
                        }

                        CMapObj* c2 = c1->m_child;
                        if (c2 != 0) {
                            do {
                                if (show != 0) {
                                    c2->m_showFlags |= 1;
                                } else {
                                    c2->m_showFlags &= 0xFE;
                                }

                                CMapObj* c3 = c2->m_child;
                                if (c3 != 0) {
                                    do {
                                        if (show != 0) {
                                            c3->m_showFlags |= 1;
                                        } else {
                                            c3->m_showFlags &= 0xFE;
                                        }

                                        CMapObj* c4 = c3->m_child;
                                        if (c4 != 0) {
                                            do {
                                                if (show != 0) {
                                                    c4->m_showFlags |= 1;
                                                } else {
                                                    c4->m_showFlags &= 0xFE;
                                                }

                                                CMapObj* c5 = c4->m_child;
                                                if (c5 != 0) {
                                                    do {
                                                        if (show != 0) {
                                                            c5->m_showFlags |= 1;
                                                        } else {
                                                            c5->m_showFlags &= 0xFE;
                                                        }

                                                        CMapObj* c6 = c5->m_child;
                                                        if (c6 != 0) {
                                                            do {
                                                                if (show != 0) {
                                                                    c6->m_showFlags |= 1;
                                                                } else {
                                                                    c6->m_showFlags &= 0xFE;
                                                                }

                                                                CMapObj* c7 = c6->m_child;
                                                                if (c7 != 0) {
                                                                    do {
                                                                        if (show != 0) {
                                                                            c7->m_showFlags |= 1;
                                                                        } else {
                                                                            c7->m_showFlags &= 0xFE;
                                                                        }

                                                                        if (c7->m_child != 0) {
                                                                            c7->m_child->SetShow_r(show);
                                                                        }

                                                                        c7 = c7->m_next;
                                                                    } while (c7 != 0);
                                                                }

                                                                c6 = c6->m_next;
                                                            } while (c6 != 0);
                                                        }

                                                        c5 = c5->m_next;
                                                    } while (c5 != 0);
                                                }

                                                c4 = c4->m_next;
                                            } while (c4 != 0);
                                        }

                                        c3 = c3->m_next;
                                    } while (c3 != 0);
                                }

                                c2 = c2->m_next;
                            } while (c2 != 0);
                        }

                        c1 = c1->m_next;
                    } while (c1 != 0);
                }

                c0 = c0->m_next;
            } while (c0 != 0);
        }

        root = root->m_next;
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
        m_showFlags |= 1;
    } else {
        m_showFlags &= 0xFE;
    }

    if (m_child != 0) {
        m_child->SetShow_r(show);
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
    CMapObj* head0 = 0;
    CMapObj* head1;
    CMapObj* head2;
    CMapObj* head3;
    CMapObj* head4;
    CMapObj* head5;
    CMapObj* head6;
    CMapObj* head7;
    CMapObj* head8;
    CMapObj* search0 = MapObjArrayStart();

    while ((search0 = MapMng.SearchChildMapObj(search0, this)) != 0) {
        CMapObj* child0 = search0;

        child0->m_next = head0;
        head0 = child0;
        CMapObj* search1 = MapObjArrayStart();
        head1 = 0;
        while ((search1 = MapMng.SearchChildMapObj(search1, child0)) != 0) {
            CMapObj* child1 = search1;
            head2 = 0;

            child1->m_next = head1;
            head1 = child1;
            CMapObj* cursor2 = MapObjArrayStart();
            while ((cursor2 = MapMng.SearchChildMapObj(cursor2, child1)) != 0) {
                CMapObj* child2 = cursor2;
                child2->m_next = head2;
                head2 = child2;
                CMapObj* cursor3 = MapObjArrayStart();
                head3 = 0;
                while ((cursor3 = MapMng.SearchChildMapObj(cursor3, child2)) != 0) {
                    CMapObj* child3 = cursor3;
                    child3->m_next = head3;
                    head3 = child3;
                    CMapObj* cursor4 = MapObjArrayStart();
                    head4 = 0;
                    while ((cursor4 = MapMng.SearchChildMapObj(cursor4, child3)) != 0) {
                        CMapObj* child4 = cursor4;
                        child4->m_next = head4;
                        head4 = child4;
                        CMapObj* cursor5 = MapObjArrayStart();
                        head5 = 0;
                        while ((cursor5 = MapMng.SearchChildMapObj(cursor5, child4)) != 0) {
                            CMapObj* child5 = cursor5;
                            child5->m_next = head5;
                            head5 = child5;
                            CMapObj* cursor6 = MapObjArrayStart();
                            head6 = 0;
                            while ((cursor6 = MapMng.SearchChildMapObj(cursor6, child5)) != 0) {
                                CMapObj* child6 = cursor6;
                                child6->m_next = head6;
                                head6 = child6;
                                CMapObj* cursor7 = MapObjArrayStart();
                                head7 = 0;
                                while ((cursor7 = MapMng.SearchChildMapObj(cursor7, child6)) != 0) {
                                    CMapObj* child7 = cursor7;
                                    child7->m_next = head7;
                                    head7 = child7;
                                    CMapObj* cursor8 = MapObjArrayStart();
                                    head8 = 0;
                                    while ((cursor8 = MapMng.SearchChildMapObj(cursor8, child7)) != 0) {
                                        CMapObj* child8 = cursor8;
                                        child8->m_next = head8;
                                        head8 = child8;
                                        child8->SetLink();
                                        cursor8 = NextSlot(cursor8);
                                    }

                                    child7->m_child = head8;
                                    cursor7 = NextSlot(cursor7);
                                }

                                child6->m_child = head7;
                                cursor6 = NextSlot(cursor6);
                            }

                            child5->m_child = head6;
                            cursor5 = NextSlot(cursor5);
                        }

                        child4->m_child = head5;
                        cursor4 = NextSlot(cursor4);
                    }

                    child3->m_child = head4;
                    cursor3 = NextSlot(cursor3);
                }

                child2->m_child = head3;
                cursor2 = NextSlot(cursor2);
            }

            child1->m_child = head2;
            search1 = NextSlot(search1);
        }

        child0->m_child = head1;
        search0 = NextSlot(search0);
    }

    m_child = head0;
}

static inline void calcRunningColorKeyFrame(CMapKeyFrame* keyFrame, _GXColor& out, _GXColor* colors)
{
    float blend;
    int key0;
    int key1;
    if (keyFrame->Get(key0, key1, blend) != 0) {
        int blendRate = static_cast<int>(kMapObjColorBlendScale * blend);
        _GXColor c0 = colors[key0];
        _GXColor c1 = colors[key1];

        c0.r = static_cast<unsigned char>(
            c0.r + ((blendRate * (static_cast<int>(c1.r) - static_cast<int>(c0.r))) >> 8));
        c0.g = static_cast<unsigned char>(
            c0.g + ((blendRate * (static_cast<int>(c1.g) - static_cast<int>(c0.g))) >> 8));
        c0.b = static_cast<unsigned char>(
            c0.b + ((blendRate * (static_cast<int>(c1.b) - static_cast<int>(c0.b))) >> 8));
        c0.a = static_cast<unsigned char>(
            c0.a + ((blendRate * (static_cast<int>(c1.a) - static_cast<int>(c0.a))) >> 8));
        out = c0;
    } else {
        out = colors[key0];
    }

    keyFrame->Calc();
}

static inline void calcColorKeyFrame(CMapKeyFrame* keyFrame, _GXColor& out, _GXColor* colors)
{
    if (keyFrame->IsRun() == 0) {
        return;
    }

    float blend;
    int key0;
    int key1;
    if (keyFrame->Get(key0, key1, blend) != 0) {
        int blendRate = static_cast<int>(kMapObjColorBlendScale * blend);
        _GXColor c0 = colors[key0];
        _GXColor c1 = colors[key1];

        c0.r = static_cast<unsigned char>(
            c0.r + ((blendRate * (static_cast<int>(c1.r) - static_cast<int>(c0.r))) >> 8));
        c0.g = static_cast<unsigned char>(
            c0.g + ((blendRate * (static_cast<int>(c1.g) - static_cast<int>(c0.g))) >> 8));
        c0.b = static_cast<unsigned char>(
            c0.b + ((blendRate * (static_cast<int>(c1.b) - static_cast<int>(c0.b))) >> 8));
        c0.a = static_cast<unsigned char>(
            c0.a + ((blendRate * (static_cast<int>(c1.a) - static_cast<int>(c0.a))) >> 8));
        out = c0;
    } else {
        out = colors[key0];
    }

    keyFrame->Calc();
}

/*
 * --INFO--
 * PAL Address: 0x80029538
 * PAL Size: 2016b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapObj::Calc()
{
    Vec delta;
    Vec posCam;
    Vec pos;
    Mtx cameraMtx;

    if (m_cameraSemiTransStep != 0) {
        m_cameraSemiTransAlpha = static_cast<short>(m_cameraSemiTransAlpha + m_cameraSemiTransStep);
        if (m_cameraSemiTransStep > 0) {
            if (m_cameraSemiTransAlpha >= m_cameraSemiTransTargetAlpha) {
                m_cameraSemiTransAlpha = m_cameraSemiTransTargetAlpha;
                m_cameraSemiTransStep = 0;
            }
        } else if (m_cameraSemiTransAlpha <= m_cameraSemiTransTargetAlpha) {
            m_cameraSemiTransAlpha = m_cameraSemiTransTargetAlpha;
            m_cameraSemiTransStep = 0;
        }

        if (m_cameraSemiTransAlpha != 0) {
            m_drawPriority = 2;
        } else {
            m_drawPriority = m_baseDrawPriority;
        }
    }

    if ((static_cast<unsigned int>(m_mapDataType) == 1U) && (m_mapData != 0) &&
        (m_octTreeIndex == -1) &&
        ((m_showFlags & 1) != 0)) {
        if ((m_cameraSemiTransMaxAlpha < kMapObjOne) && (m_cameraSemiTransMinAlpha >= kMapObjInitNegOne)) {
            m_drawPriority = m_baseDrawPriority;
            m_cameraSemiTransBeyondMax = 1;
            m_cameraSemiTransActive = 0;
        } else {
            pos.x = m_worldMtx[0][3];
            pos.y = m_worldMtx[1][3];
            pos.z = m_worldMtx[2][3];
            PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx);
            PSMTXMultVec(cameraMtx, &pos, &posCam);
            posCam.z = -posCam.z;

            m_cameraSemiTransBeyondMax = static_cast<unsigned char>(posCam.z > m_cameraSemiTransMaxAlpha);
            if (posCam.z < m_cameraSemiTransMinAlpha) {
                m_cameraSemiTransActive = 1;
                m_drawPriority = 2;
            } else {
                m_cameraSemiTransActive = 1;
                m_drawPriority = m_baseDrawPriority;
            }
        }
    }

    CMapObjAtr* attr = m_attribute;
    if (attr != 0) {
        int attrType = attr->m_type;
        switch (attrType) {
        case CMapObjAtr::MIME:
            if (reinterpret_cast<CMapObjAtrMime*>(attr)->m_keyFrame.IsRun() != 0) {
                CMapObjAtrMime* mime = reinterpret_cast<CMapObjAtrMime*>(attr);
                float blend;
                int key0;
                int key1;
                Vec* outVerts = *reinterpret_cast<Vec**>(reinterpret_cast<unsigned char*>(m_mapData) + 0x2C);

                if (mime->m_keyFrame.Get(key0, key1, blend) != 0) {
                    Vec* src0 = reinterpret_cast<Vec*>(mime->m_vertexLists[key0]);
                    Vec* src1 = reinterpret_cast<Vec*>(mime->m_vertexLists[key1]);
                    Vec* dst = outVerts;
                    for (int i = 0; i < mime->m_vertexCount; i++) {
                        PSVECSubtract(src1, src0, &delta);
                        PSVECScale(&delta, &delta, blend);
                        PSVECAdd(src0, &delta, dst);
                        src0++;
                        src1++;
                        dst++;
                    }
                } else {
                    float* src = mime->m_vertexLists[key0];
                    for (int i = 0; i < mime->m_vertexCount; i++) {
                        outVerts[i].x = src[0];
                        outVerts[i].y = src[1];
                        outVerts[i].z = src[2];
                        src += 3;
                    }
                }

                DCFlushRange(outVerts, static_cast<unsigned long>(mime->m_vertexCount * 0xC));
                mime->m_keyFrame.Calc();
            }
            break;
        case CMapObjAtr::POINT_LIGHT: {
            CMapObjAtrPointLight* pointLight = reinterpret_cast<CMapObjAtrPointLight*>(attr);

            if (pointLight->m_colorKeyFrame.IsRun() != 0) {
                calcRunningColorKeyFrame(&pointLight->m_colorKeyFrame, pointLight->m_color, pointLight->m_colors);
                if (pointLight->m_useAltColor != 0) {
                    pointLight->m_altColor = pointLight->m_color;
                }
            }

            calcColorKeyFrame(&pointLight->m_altColorKeyFrame, pointLight->m_color, pointLight->m_colors);
            break;
        }
        case CMapObjAtr::SPOT_LIGHT: {
            CMapObjAtrSpotLight* spotLight = reinterpret_cast<CMapObjAtrSpotLight*>(attr);

            if (spotLight->m_colorKeyFrame.IsRun() != 0) {
                calcRunningColorKeyFrame(&spotLight->m_colorKeyFrame, spotLight->m_color, spotLight->m_colors);
                if (spotLight->m_unknown2F != 0) {
                    spotLight->m_altColor = spotLight->m_color;
                }
            }

            calcColorKeyFrame(&spotLight->m_altColorKeyFrame, spotLight->m_color, spotLight->m_colors);
            break;
        }
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

    s_mapObjLightColor.a = m_lightAlpha;

    if (m_useAmbientColor != 0) {
        mapColor = m_ambientColor;
    } else {
        mapColor = MapMng.m_mapColor;
    }

    if (MapMng.m_colorScaleEnable != 0) {
        mapColor.r = static_cast<unsigned char>((mapColor.r * MapMng.m_colorScale.r) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * MapMng.m_colorScale.g) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * MapMng.m_colorScale.b) >> 8);
        mapColor.a = static_cast<unsigned char>((mapColor.a * MapMng.m_colorScale.a) >> 8);
    }

    if (m_colorAlphaRate != 0xFF) {
        int alphaRate = m_colorAlphaRate;
        mapColor.r = static_cast<unsigned char>((mapColor.r * alphaRate) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * alphaRate) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * alphaRate) >> 8);
    }

    _GXColor lightColor = s_mapObjLightColor;
    LightPcs.SetMapColorAlpha(m_worldMtx, mapColor, lightColor, m_cameraSemiTransActive, m_cameraSemiTransNear,
                              m_cameraSemiTransFar, m_cameraSemiTransFadeRange,
                              static_cast<unsigned char>(m_cameraSemiTransAlpha >> 7));
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
    if (m_drawPriority != priority) {
        return;
    }
    if ((m_showFlags & 4) == 0) {
        return;
    }

    Vec lightPos;
    lightPos.x = m_worldMtx[0][3];
    lightPos.y = m_worldMtx[1][3];
    lightPos.z = m_worldMtx[2][3];
    LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(1), &lightPos, m_lightSetIndex);

    _GXColor mapColor;

    MaterialMan.SetDefaultDrawEnv(0xACE0F);

    if (m_enableFullScreenShadow != 0) {
        CameraPcs.SetFullScreenShadow(m_worldMtx, 0);
    }
    if (m_shadowTarget != 0) {
        MaterialMan.SetShadowBound(static_cast<CMapShadow::TARGET>(1),
                                   reinterpret_cast<CMapMesh*>(m_mapData)->GetBound(),
                                   m_worldMtx);
    }

    MaterialMan.SaveCurrentEnvAsStd();

    s_mapObjLightColor.a = m_lightAlpha;
    if (m_useAmbientColor != 0) {
        mapColor = m_ambientColor;
    } else {
        mapColor = MapMng.m_mapColor;
    }

    if (MapMng.m_colorScaleEnable != 0) {
        mapColor.r = static_cast<unsigned char>((mapColor.r * MapMng.m_colorScale.r) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * MapMng.m_colorScale.g) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * MapMng.m_colorScale.b) >> 8);
        mapColor.a = static_cast<unsigned char>((mapColor.a * MapMng.m_colorScale.a) >> 8);
    }

    if (m_colorAlphaRate != 0xFF) {
        unsigned char alphaRate = m_colorAlphaRate;
        mapColor.r = static_cast<unsigned char>((mapColor.r * alphaRate) >> 8);
        mapColor.g = static_cast<unsigned char>((mapColor.g * alphaRate) >> 8);
        mapColor.b = static_cast<unsigned char>((mapColor.b * alphaRate) >> 8);
    }

    _GXColor lightColor = s_mapObjLightColor;
    LightPcs.SetMapColorAlpha(m_worldMtx, mapColor, lightColor, m_cameraSemiTransActive, m_cameraSemiTransNear,
                              m_cameraSemiTransFar, m_cameraSemiTransFadeRange,
                              static_cast<unsigned char>(m_cameraSemiTransAlpha >> 7));
    LightPcs.SetBumpTexMatirx(m_worldMtx, reinterpret_cast<CLightPcs::CBumpLight*>(m_bumpLight),
                              reinterpret_cast<Vec*>(&m_transRateX), m_bumpTexMatrixMode);

    if (kMapObjOne != m_zBufferOffset) {
        CameraPcs.SetOffsetZBuff(m_zBufferOffset);
    }
    if (m_disableZWrite != 0) {
        GXSetZMode(1, GX_LEQUAL, 0);
    }

    reinterpret_cast<CMapMesh*>(m_mapData)->SetRenderArray();
    reinterpret_cast<CMapMesh*>(m_mapData)->Draw(0);

    if (m_disableZWrite != 0) {
        GXSetZMode(1, GX_LEQUAL, 1);
    }
    if (kMapObjOne != m_zBufferOffset) {
        CameraPcs.SetOffsetZBuff(m_zBufferOffset);
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
    m_showFlags &= ~4;

    if ((m_mapDataType == 1) && (m_mapData != 0)) {
        if ((m_octTreeIndex == -1) && ((m_showFlags & 1) != 0)) {
            Mtx concatMtx;

            PSMTXConcat(MapMng.m_scaledViewMtxSecondary, m_worldMtx, concatMtx);
            if (reinterpret_cast<CMapMesh*>(m_mapData)->GetBound()->CheckFrustum(
                    MapMng.m_cameraPosition, concatMtx, MapMng.m_octTreeFrustumRange) != 0) {
                m_showFlags |= 4;
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
    if ((m_mapDataType == 2) && (m_mapData != 0)) {
        MaterialMan.SetObjMatrix(MapObjHitDrawMtx(), m_worldMtx);
        reinterpret_cast<CMapHit*>(m_mapData)->Draw();
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
    if ((m_mapDataType == 2) && (m_mapData != 0)) {
        MaterialMan.SetObjMatrix(MapObjHitDrawMtx(), m_worldMtx);
        reinterpret_cast<CMapHit*>(m_mapData)->DrawWire();
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
    if ((m_mapDataType == 2) && (m_mapData != 0)) {
        MaterialMan.SetObjMatrix(MapObjHitDrawMtx(), m_worldMtx);
        reinterpret_cast<CMapHit*>(m_mapData)->DrawNormal();
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
    if ((m_mapDataType == 2) && (m_mapData != 0) && (m_octTreeIndex == -1)) {
        Mtx inverseMtx;

        PSMTXInverse(m_worldMtx, inverseMtx);
        CMapCylinder localCylinder(kMapObjBoundMinInit, kMapObjBoundMaxInit);
        PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &localCylinder.m_bottom);
        PSMTXMultVec(inverseMtx, &cylinder->m_top, &localCylinder.m_top);

        localCylinder.m_radius = cylinder->m_radius;
        float marginX = LoadFloat(kMapObjZero) + localCylinder.m_radius;

        if (localCylinder.m_bottom.x < localCylinder.m_top.x) {
            localCylinder.m_bound.m_min.x = localCylinder.m_bottom.x - marginX;
            localCylinder.m_bound.m_max.x = localCylinder.m_top.x + marginX;
        } else {
            localCylinder.m_bound.m_min.x = localCylinder.m_top.x - marginX;
            localCylinder.m_bound.m_max.x = localCylinder.m_bottom.x + marginX;
        }

        float marginY = LoadFloatVolatile(kMapObjZero);
        marginY += localCylinder.m_radius;
        if (localCylinder.m_bottom.y < localCylinder.m_top.y) {
            localCylinder.m_bound.m_min.y = localCylinder.m_bottom.y - marginY;
            localCylinder.m_bound.m_max.y = localCylinder.m_top.y + marginY;
        } else {
            localCylinder.m_bound.m_min.y = localCylinder.m_top.y - marginY;
            localCylinder.m_bound.m_max.y = localCylinder.m_bottom.y + marginY;
        }

        float marginZ = LoadFloatVolatile(kMapObjZero);
        marginZ += localCylinder.m_radius;
        if (localCylinder.m_bottom.z < localCylinder.m_top.z) {
            localCylinder.m_bound.m_min.z = localCylinder.m_bottom.z - marginZ;
            localCylinder.m_bound.m_max.z = localCylinder.m_top.z + marginZ;
        } else {
            localCylinder.m_bound.m_min.z = localCylinder.m_top.z - marginZ;
            localCylinder.m_bound.m_max.z = localCylinder.m_bottom.z + marginZ;
        }

        CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
        unsigned char hitBounds = 0;
        unsigned char xyOverlap = 0;
        {
            int xOverlap = 0;
            float positionMinX = mapHit->m_positionMin.x;
            if (positionMinX < localCylinder.m_bound.m_min.x) {
                xOverlap = localCylinder.m_bound.m_min.x <= mapHit->m_positionMax.x;
            } else if (positionMinX > localCylinder.m_bound.m_min.x) {
                xOverlap = positionMinX <= localCylinder.m_bound.m_max.x;
            } else {
                xOverlap = 1;
            }

            if (xOverlap) {
                int yOverlap = 0;
                float positionMinY = mapHit->m_positionMin.y;
                if (positionMinY < localCylinder.m_bound.m_min.y) {
                    yOverlap = localCylinder.m_bound.m_min.y <= mapHit->m_positionMax.y;
                } else if (positionMinY > localCylinder.m_bound.m_min.y) {
                    yOverlap = positionMinY <= localCylinder.m_bound.m_max.y;
                } else {
                    yOverlap = 1;
                }
                if (yOverlap) {
                    xyOverlap = 1;
                }
            }

            if (xyOverlap) {
                int zOverlap = 0;
                float positionMinZ = mapHit->m_positionMin.z;
                if (positionMinZ < localCylinder.m_bound.m_min.z) {
                    zOverlap = localCylinder.m_bound.m_min.z <= mapHit->m_positionMax.z;
                } else if (positionMinZ > localCylinder.m_bound.m_min.z) {
                    zOverlap = positionMinZ <= localCylinder.m_bound.m_max.z;
                } else {
                    zOverlap = 1;
                }

                if (zOverlap) {
                    hitBounds = 1;
                }
            }
        }
        if (hitBounds) {
            Vec localMove;
            PSMTXMultVecSR(inverseMtx, &cylinder->m_axis, &localCylinder.m_axis);
            PSMTXMultVecSR(inverseMtx, move, &localMove);
            if (reinterpret_cast<CMapHit*>(m_mapData)->CheckHitCylinder(&localCylinder, &localMove, mask) != 0) {
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
void CMapObj::CheckHitCylinderNear(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((m_mapDataType == 2) && (m_mapData != 0) && (m_octTreeIndex == -1)) {
        Mtx inverseMtx;
        Vec localMove;

        PSMTXInverse(m_worldMtx, inverseMtx);
        CMapCylinder localCylinder(kMapObjBoundMinInit, kMapObjBoundMaxInit);
        PSMTXMultVec(inverseMtx, &cylinder->m_bottom, &localCylinder.m_bottom);
        PSMTXMultVec(inverseMtx, &cylinder->m_top, &localCylinder.m_top);

        localCylinder.m_radius = cylinder->m_radius;
        float marginX = LoadFloat(kMapObjZero) + localCylinder.m_radius;

        if (localCylinder.m_bottom.x < localCylinder.m_top.x) {
            localCylinder.m_bound.m_min.x = localCylinder.m_bottom.x - marginX;
            localCylinder.m_bound.m_max.x = localCylinder.m_top.x + marginX;
        } else {
            localCylinder.m_bound.m_min.x = localCylinder.m_top.x - marginX;
            localCylinder.m_bound.m_max.x = localCylinder.m_bottom.x + marginX;
        }

        float marginY = LoadFloatVolatile(kMapObjZero);
        marginY += localCylinder.m_radius;
        if (localCylinder.m_bottom.y < localCylinder.m_top.y) {
            localCylinder.m_bound.m_min.y = localCylinder.m_bottom.y - marginY;
            localCylinder.m_bound.m_max.y = localCylinder.m_top.y + marginY;
        } else {
            localCylinder.m_bound.m_min.y = localCylinder.m_top.y - marginY;
            localCylinder.m_bound.m_max.y = localCylinder.m_bottom.y + marginY;
        }

        float marginZ = LoadFloatVolatile(kMapObjZero);
        marginZ += localCylinder.m_radius;
        if (localCylinder.m_bottom.z < localCylinder.m_top.z) {
            localCylinder.m_bound.m_min.z = localCylinder.m_bottom.z - marginZ;
            localCylinder.m_bound.m_max.z = localCylinder.m_top.z + marginZ;
        } else {
            localCylinder.m_bound.m_min.z = localCylinder.m_top.z - marginZ;
            localCylinder.m_bound.m_max.z = localCylinder.m_bottom.z + marginZ;
        }

        CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
        unsigned char hitBounds = 0;
        unsigned char xyOverlap = 0;
        {
            int xOverlap = 0;
            float positionMinX = mapHit->m_positionMin.x;
            if (positionMinX < localCylinder.m_bound.m_min.x) {
                xOverlap = localCylinder.m_bound.m_min.x <= mapHit->m_positionMax.x;
            } else if (positionMinX > localCylinder.m_bound.m_min.x) {
                xOverlap = positionMinX <= localCylinder.m_bound.m_max.x;
            } else {
                xOverlap = 1;
            }

            if (xOverlap) {
                int yOverlap = 0;
                float positionMinY = mapHit->m_positionMin.y;
                if (positionMinY < localCylinder.m_bound.m_min.y) {
                    yOverlap = localCylinder.m_bound.m_min.y <= mapHit->m_positionMax.y;
                } else if (positionMinY > localCylinder.m_bound.m_min.y) {
                    yOverlap = positionMinY <= localCylinder.m_bound.m_max.y;
                } else {
                    yOverlap = 1;
                }
                if (yOverlap) {
                    xyOverlap = 1;
                }
            }

            if (xyOverlap) {
                int zOverlap = 0;
                float positionMinZ = mapHit->m_positionMin.z;
                if (positionMinZ < localCylinder.m_bound.m_min.z) {
                    zOverlap = localCylinder.m_bound.m_min.z <= mapHit->m_positionMax.z;
                } else if (positionMinZ > localCylinder.m_bound.m_min.z) {
                    zOverlap = positionMinZ <= localCylinder.m_bound.m_max.z;
                } else {
                    zOverlap = 1;
                }

                if (zOverlap) {
                    hitBounds = 1;
                }
            }
        }
        if (hitBounds) {
            PSMTXMultVecSR(inverseMtx, &cylinder->m_axis, &localCylinder.m_axis);
            PSMTXMultVecSR(inverseMtx, move, &localMove);
            reinterpret_cast<CMapHit*>(m_mapData)->CheckHitCylinderNear(&localCylinder, &localMove, mask);
        }
    }

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
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
    mapHit->GetHitFaceNormal(out);
    PSMTXMultVecSR(m_worldMtx, out, out);
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
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
    int hit = mapHit->CalcHitSlide(out, y);
    PSMTXMultVecSR(m_worldMtx, out, out);
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
    CMapHit* mapHit = reinterpret_cast<CMapHit*>(m_mapData);
    mapHit->CalcHitPosition(out);
    PSMTXMultVec(m_worldMtx, out, out);
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
    CMapObjAtrMime* mime = reinterpret_cast<CMapObjAtrMime*>(m_attribute);

    mime->m_keyFrame.m_startFrame = mode;
    mime->m_keyFrame.m_currentFrame = mode;

    if (target > mime->m_keyFrame.m_frameCount) {
        target = mime->m_keyFrame.m_frameCount;
    }

    mime->m_keyFrame.m_endFrame = target;
    mime->m_keyFrame.m_loop = static_cast<unsigned char>(type);
    mime->m_keyFrame.m_isRun = 1;
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
    int i = 0;

    while (i < static_cast<int>(m_vertexListCount)) {
        if (m_vertexLists[i] != 0) {
            delete m_vertexLists[i];
            m_vertexLists[i] = 0;
        }

        i++;
    }

    if (m_vertexLists != 0) {
        delete m_vertexLists;
        m_vertexLists = 0;
    }
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
