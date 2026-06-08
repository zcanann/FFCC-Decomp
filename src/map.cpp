#include "ffcc/map.h"
#include "ffcc/chunkfile.h"
#include "ffcc/math.h"
#include "ffcc/memory.h"
#include "ffcc/maphit.h"
#include "ffcc/mapmesh.h"
#include "ffcc/mapshadow.h"
#include "ffcc/mapanim.h"
#include "ffcc/maptexanim.h"
#include "ffcc/materialman.h"
#include "ffcc/textureman.h"
#include "ffcc/graphic.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_chara.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_light.h"
#include "ffcc/p_tina.h"
#include "ffcc/file.h"
#include "ffcc/system.h"

#include <string.h>
#include <PowerPC_EABI_Support/Runtime/NMWException.h>
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

CMapMng MapMng;
char g_StrTmp[0x400];

extern const float kMapViewScaleXPrimary = 0.73898232f;
extern const float kMapViewScaleY = 0.88677877f;
extern const float kMapViewScaleZ = 1.0f;
extern const float kMapViewScaleXSecondary = 0.84455127f;
CMapHitDrawMode g_MapHitDrawMode;
unsigned char g_MapHitFaceFlag;
unsigned int s_loadedMapNo__7CMapPcs;
extern const float kMapCameraSemiTransMinSentinel = 1.0e15f;
extern const float kMapCameraSemiTransMaxSentinel = -1.0f;
extern const float kMapZero = 0.0f;

static inline CMapMngAsyncLoadState& GetMapMngAsyncLoadState(CMapMng* mapMng)
{
    return mapMng->m_asyncLoadState;
}
extern const float kMapHitMoveEpsilon = 0.0001f;
extern const float kMapHitMoveNegEpsilon = -0.0001f;
extern const float kMapHitTInitial = 10.0f;
extern const float kMapLargeDistance = 100000.0f;
extern const float kMapFullTurnDegrees = 360.0f;
extern const float kMapTinyEpsilon = 5.0e-6f;
extern const float kMapHitWireZOffset = -0.1f;
static const char s_mapNewLine[] = "\n";
extern "C" unsigned char Vec_80245758[];

static const char s_mapMidPathFmt[] = "%s.mid";
static const char s_mapOtmPathFmt[] = "%s.otm";
extern "C" const char s_map_cpp[] = "map.cpp";
static const char s_set_bg_camera_semi_trans_missing_fmt[] =
    "SET_BG_CAMERA_SEMI_TRANS  mesh_id=%d  "
    "\x82\xaa\x94\xad\x8c\xa9\x82\xc5\x82\xab\x82\xc8\x82\xa2\x81\x42\n";
static const char s_set_bg_transparent_missing_fmt[] =
    "SET_BG_TRANSPARENT  mesh_id=%d  "
    "\x82\xaa\x94\xad\x8c\xa9\x82\xc5\x82\xab\x82\xc8\x82\xa2\x81\x42\n";
static const char s_check_hit_cylinder_near_small_vec_fmt[] =
    "CheckHitCylinderNear "
    "\x93\x96\x82\xe8\x82\xc5\x83\x78\x83\x4e\x83\x67\x83\x8b\x82\xaa\x8f\xac\x82\xb3\x82\xb7\x82\xac\x82\xe9 "
    "vec=(%f,%f,%f)\n";
static const char s_check_hit_cylinder_small_vec_fmt[] =
    "CheckHitCylinder "
    "\x93\x96\x82\xe8\x82\xc5\x83\x78\x83\x4e\x83\x67\x83\x8b\x82\xaa\x8f\xac\x82\xb3\x82\xb7\x82\xac\x82\xe9 "
    "vec=(%f,%f,%f)\n";
static const char s_read_mid_fmt[] = "ReadMid fn=%s\n";
static const char s_read_otm_fmt[] = "ReadOtm fn=%s\n";
static const char s_mapReadErrorFmt[] = "CAN NOT READ %s !!!!!!\n";
static const char s_error_root_mapobj_not_found[] = "Error root mapobj not found\n";
static const char s_read_mid_mapobj_error[] = "Error CMapMng::ReadMid m_mapobj\n";
static const char s_read_mid_octtree_error[] = "Error CMapMng::ReadMid octtree\n";
static const char s_read_mid_hit_error[] = "Error CMapMng::ReadMid hit\n";
static const char s_read_mid_ok[] = "ReadMid OK\n";
static const char s_read_mid_error[] = "ReadMid Error\n";
static const char s_mapMplPathFmt[] = "%s_%d.mpl";
static const char s_mapReadOpenErrorFmt[] = "CAN NOT READ OPEN %s !!!!!!\n";
static const char s_mapReadMplFmt[] = "ReadMpl fn=%s\n";
static const char s_mapMtxPathFmt[] = "%s_%d.mtx";
static const char s_mapReadMtxFmt[] = "ReadMtx fn=%s\n";
static const char s_map_manager_label_block[] = "CMapMng.mapmng\0\0CMapObjAtr\0";
extern const char s_CMapTexAnimSet[] = "CMapTexAnimSet";
static const char s_map_ptrarray_grow_error[] =
    "\x83\x6f\x83\x62\x83\x74\x83\x40\x90\xac\x92\xb7\x82\xaa\x95\x73\x8b\x96\x89\xc2\x82\xc5\x82\xb7\x81\x42\n";
static const char s_map_collection_ptrarray_h[] = "collection_ptrarray.h";

namespace {
static inline float MapObjWorldX(CMapObj* mapObj)
{
    return mapObj->m_worldMtx[0][3];
}

static inline float MapObjWorldY(CMapObj* mapObj)
{
    return mapObj->m_worldMtx[1][3];
}

static inline float MapObjWorldZ(CMapObj* mapObj)
{
    return mapObj->m_worldMtx[2][3];
}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnimSet::CMapTexAnimSet()
{
    m_count = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800335d0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapTexAnimSet::~CMapTexAnimSet()
{
    for (int i = 0; i < m_count; i++) {
        CMapTexAnim* entry = m_anims[i];
        if (entry != 0) {
            if (entry->DecRef() == 0) {
                delete entry;
            }
            m_anims[i] = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003492c
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapIdGrp::CMapIdGrp()
{
    m_mask = -1;
    m_primaryColor.r = 0x80;
    m_primaryColor.b = 0;
    m_primaryColor.g = 0;
    m_primaryColor.a = 0x80;
    m_secondaryColor.r = 0;
    m_secondaryColor.g = 0;
    m_secondaryColor.b = 0x80;
    m_secondaryColor.a = 0x80;
    m_tertiaryColor.r = 0xFF;
    m_tertiaryColor.g = 0x40;
    m_tertiaryColor.b = 0x40;
    m_tertiaryColor.a = 0x80;
    m_quaternaryColor.r = 0x40;
    m_quaternaryColor.g = 0x40;
    m_quaternaryColor.b = 0;
    m_quaternaryColor.a = 0x80;
}

/*
 * --INFO--
 * PAL Address: 0x80033c48
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CMapKeyFrame::Get()
{
    switch (m_mode) {
    case 0:
        return Math.Line1D(static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame);
    case 1:
        return Math.Spline1D(
            static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame, m_splineTable);
    default:
        return kMapZero;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80033d0c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
template <>
int CPtrArray<CMaterial*>::GetSize()
{
    return m_numItems;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80033d14
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
void CPtrArray<CMaterial*>::SetDefaultSize(unsigned long defaultSize)
{
    m_defaultSize = defaultSize;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80033d1c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
void CPtrArray<CMaterial*>::SetGrow(int growCapacity)
{
    m_growCapacity = growCapacity;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800343e0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapLightHolder*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x80034414
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapLightHolder*>::~CPtrArray()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }

    m_size = 0;
    m_numItems = 0;
}

template <>
int CPtrArray<CMapLightHolder*>::setSize(unsigned long newSize);

/*
 * --INFO--
 * PAL Address: 0x80033d24
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
int CPtrArray<CMapLightHolder*>::Add(CMapLightHolder* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }
    m_items[m_numItems] = item;
    m_numItems++;
    return 1;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80033d94
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
void CPtrArray<CMapLightHolder*>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma dont_inline on
template <>
void CPtrArray<CMapLightHolder*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80033de8
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapLightHolder*>::setSize(unsigned long newSize)
{
    CMapLightHolder** newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(const_cast<char*>(s_map_ptrarray_grow_error));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CMapLightHolder**>(
            Memory._Alloc(m_size << 2, m_stage, const_cast<char*>(s_map_collection_ptrarray_h), 0xFA, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            delete[] m_items;
            m_items = 0;
        }

        m_items = newItems;
    }

    return 1;
}

template <>
int CPtrArray<CMapAnim*>::setSize(unsigned long newSize);

/*
 * --INFO--
 * PAL Address: 0x80033f54
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
int CPtrArray<CMapAnim*>::Add(CMapAnim* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }
    m_items[m_numItems] = item;
    m_numItems++;
    return 1;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80033fc4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
int CPtrArray<CMapAnim*>::GetSize()
{
    return m_numItems;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80033fcc
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
void CPtrArray<CMapAnim*>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034018
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CMapAnim* CPtrArray<CMapAnim*>::operator[](unsigned long index)
{
    return GetAt(index);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034130
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnimNode*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x80034138
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimNode* CPtrArray<CMapAnimNode*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034270
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimNode* CPtrArray<CMapAnimNode*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x80034158
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
int CPtrArray<CMapAnimKeyDt*>::GetSize()
{
    return m_numItems;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800341ac
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CMapAnimKeyDt* CPtrArray<CMapAnimKeyDt*>::operator[](unsigned long index)
{
    return GetAt(index);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034280
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimKeyDt* CPtrArray<CMapAnimKeyDt*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x800341cc
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
template <>
void CPtrArray<CMapAnimKeyDt*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034160
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
void CPtrArray<CMapAnimKeyDt*>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034038
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
template <>
void CPtrArray<CMapAnim*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034040
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CMapAnim*>::setSize(unsigned long newSize)
{
    CMapAnim** newItems;

    if (m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(const_cast<char*>(s_map_ptrarray_grow_error));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CMapAnim**>(
            Memory._Alloc(m_size << 2, m_stage, const_cast<char*>(s_map_collection_ptrarray_h), 0xFA, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
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
 * PAL Address: 0x80034490
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CPtrArray<CMapAnimRun*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800344c4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimRun*>::~CPtrArray()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034540
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CPtrArray<CMapAnim*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034574
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnim*>::~CPtrArray()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }

    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800345f0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CPtrArray<CMapAnimKeyDt*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034624
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapAnimKeyDt*>::~CPtrArray()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }

    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800346a0
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CPtrArray<CMapShadow*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800346d4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CMapShadow*>::~CPtrArray()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }

    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80034260
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnim* CPtrArray<CMapAnim*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
template <>
#pragma dont_inline on
int CPtrArray<CMapAnimRun*>::GetSize()
{
    return m_numItems;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800340f0
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
void CPtrArray<CMapAnimRun*>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x8003413c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CMapAnimRun* CPtrArray<CMapAnimRun*>::operator[](unsigned long index)
{
    return GetAt(index);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034170
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
template <>
void CPtrArray<CMapAnimRun*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034a44
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimRun* CPtrArray<CMapAnimRun*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x800341d4
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
int CPtrArray<CMapShadow*>::GetSize()
{
    return m_numItems;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x800341dc
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
void CPtrArray<CMapShadow*>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034228
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
#pragma dont_inline on
CMapShadow* CPtrArray<CMapShadow*>::operator[](unsigned long index)
{
    return GetAt(index);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034248
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
template <>
void CPtrArray<CMapShadow*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x80034290
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapShadow* CPtrArray<CMapShadow*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x80033a20
 * PAL Size: 552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapKeyFrame::Get(int& key0, int& key1, float& blend)
{
    switch (m_mode) {
    case 0:
        blend = Math.Line1D(
            static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame);
        break;
    case 1:
        blend = Math.Spline1D(
            static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame, m_splineTable);
        break;
    default:
        blend = kMapZero;
        {
            unsigned char key = m_junTable[0];
            key1 = key;
            key0 = key;
        }
        return 0;
    }

    if (blend <= kMapZero) {
        unsigned char key = m_junTable[0];
        key1 = key;
        key0 = key;
        blend = kMapZero;
        return 0;
    }

    const float junMax = static_cast<float>(m_junCount - 1);
    if (blend >= junMax) {
        unsigned char key = m_junTable[m_junCount - 1];
        key1 = key;
        key0 = key;
        blend = kMapViewScaleZ;
        return 0;
    }

    key0 = static_cast<int>(blend);
    key1 = static_cast<int>(1.0f + blend);
    blend = blend - static_cast<float>(key0);
    key0 = m_junTable[key0];
    if (blend == kMapZero) {
        key1 = key0;
        return 0;
    }
    key1 = m_junTable[key1];
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::Calc()
{
    m_currentFrame++;
    if (m_currentFrame <= m_endFrame) {
        return;
    }
    if (m_startFrame == m_endFrame) {
        m_isRun = 0;
        return;
    }
    if (m_loop != 0) {
        m_currentFrame = m_startFrame;
        return;
    }

    m_currentFrame = m_endFrame;
    m_isRun = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapKeyFrame::IsRun()
{
    return m_isRun;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadJun(CChunkFile& chunkFile, int count)
{
    m_junCount = static_cast<unsigned char>(count);
    m_junTable = new (MapMng.m_stage, const_cast<char*>(s_map_cpp), 0xC1) unsigned char[m_junCount];

    for (int i = 0; i < static_cast<int>(m_junCount); i++) {
        m_junTable[i] = chunkFile.Get1();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadFrame(CChunkFile& chunkFile, int)
{
    int frame = chunkFile.Get4();

    m_startFrame = frame;
    m_currentFrame = frame;

    frame = chunkFile.Get4();
    m_endFrame = frame;
    m_frameCount = frame;
    m_mode = static_cast<unsigned char>(chunkFile.Get4());
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapKeyFrame::ReadKey(CChunkFile& chunkFile, int count)
{
    m_isRun = 1;
    m_keyCount = static_cast<unsigned char>(count);
    m_keyFrame = new (MapMng.m_stage, const_cast<char*>(s_map_cpp), 0xD5) float[m_keyCount];
    m_keyValue = new (MapMng.m_stage, const_cast<char*>(s_map_cpp), 0xD6) float[m_keyCount];

    for (int i = 0; i < static_cast<int>(m_keyCount); i++) {
        m_keyFrame[i] = chunkFile.GetF4();
        m_keyValue[i] = chunkFile.GetF4();
    }

    if (m_mode == 1) {
        m_splineTable = new (MapMng.m_stage, const_cast<char*>(s_map_cpp), 0xDE) float[m_keyCount];
        Math.MakeSpline1Dtable(static_cast<int>(m_keyCount) - 1, m_keyValue, m_keyFrame, m_splineTable);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003368c
 * PAL Size: 304b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Create()
{
    m_calcCount = 0;
    m_shadowKeyInfoCount = 0;
    m_mapMeshCount = 0;
    m_mapObjCount = 0;
    m_octTreeCount = 0;
    m_mapColor.r = 0xFF;
    m_mapColor.g = 0xFF;
    m_mapColor.b = 0xFF;
    m_mapColor.a = 0xFF;

    if (Game.m_currentSceneId == 3) {
        m_fogEnable = 0;
    } else {
        m_fogEnable = 1;
    }

    m_mapAnimFrame = 0;
    m_rootMapObj = 0;

    CMemory::CStage* stage = Memory.CreateStage(0x540000, const_cast<char*>(s_map_manager_label_block), 0);
    m_stage = stage;

    GetMapAnimRunArray().SetStage(m_stage);
    GetMapAnimArray().SetStage(m_stage);
    GetMapAnimKeyDtArray().SetStage(m_stage);
    GetMapShadowArray().SetStage(m_stage);

    for (int i = 0; i < 2; i++) {
        GetMapLightHolderArray(i).SetStage(m_stage);
    }

    s_bitMask.m_fields.m_drawFlags = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyOctTree()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapHit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapMesh()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyTextureSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMaterialSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapTexAnimSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyAnimation()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::DestroyMapLightHolder()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80033254
 * PAL Size: 892b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::DestroyMap()
{
    for (int i = 0; i < m_octTreeCount; i++) {
        m_octTreeArray[i].~COctTree();
    }
    m_octTreeCount = 0;

    for (int i = 0; i < m_mapHitCount; i++) {
        m_mapHitArray[i].~CMapHit();
    }
    m_mapHitCount = 0;

    for (int i = 0; i < m_mapObjCount; i++) {
        m_mapObjArray[i].~CMapObj();
    }
    m_mapObjCount = 0;

    for (int i = 0; i < m_mapMeshCount; i++) {
        m_mapMeshArray[i].~CMapMesh();
    }
    m_mapMeshCount = 0;

    if (m_materialSet != 0) {
        delete m_materialSet;
        m_materialSet = 0;
    }

    if (m_textureSet != 0) {
        delete m_textureSet;
        m_textureSet = 0;
    }

    if (m_mapTexAnimSet != 0) {
        delete m_mapTexAnimSet;
        m_mapTexAnimSet = 0;
    }

    for (unsigned int i = 0; i < static_cast<unsigned int>(GetMapAnimArray().GetSize()); i++) {
        if (GetMapAnimArray()[i] != 0) {
            delete GetMapAnimArray()[i];
        }
    }
    GetMapAnimArray().RemoveAll();

    for (unsigned int i = 0; i < static_cast<unsigned int>(GetMapAnimKeyDtArray().GetSize()); i++) {
        if (GetMapAnimKeyDtArray()[i] != 0) {
            delete GetMapAnimKeyDtArray()[i];
        }
    }
    GetMapAnimKeyDtArray().RemoveAll();

    for (unsigned int i = 0; i < static_cast<unsigned int>(GetMapAnimRunArray().GetSize()); i++) {
        if (GetMapAnimRunArray()[i] != 0) {
            operator delete(GetMapAnimRunArray()[i]);
        }
    }
    GetMapAnimRunArray().RemoveAll();

    for (unsigned int i = 0; i < static_cast<unsigned int>(GetMapShadowArray().GetSize()); i++) {
        if (GetMapShadowArray()[i] != 0) {
            operator delete(GetMapShadowArray()[i]);
        }
    }
    GetMapShadowArray().RemoveAll();

    for (int i = 0; i < 2; i++) {
        for (unsigned int j = 0; j < static_cast<unsigned int>(GetMapLightHolderArray(i).GetSize()); j++) {
            if (GetMapLightHolderArray(i)[j] != 0) {
                operator delete(GetMapLightHolderArray(i)[j]);
            }
        }
        GetMapLightHolderArray(i).RemoveAll();
    }

    LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(1));
    m_rootMapObj = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80033218
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Destroy()
{
    DestroyMap();
    Memory.DestroyStage(m_stage);
}

/*
 * --INFO--
 * PAL Address: 0x8003311c
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::MapFileRead(char*, unsigned long&)
{
    for (int i = 0; i < 0x10; i++) {
        if (m_asyncLoadState.m_asyncHandles[i] != 0) {
            int completed = File.IsCompleted(reinterpret_cast<CFile::CHandle*>(m_asyncLoadState.m_asyncHandles[i]));
            if (completed != 0) {
                void* readBuffer = File.m_readBuffer;
                int len = File.GetLength(reinterpret_cast<CFile::CHandle*>(m_asyncLoadState.m_asyncHandles[i]));
                void* amemCursor = m_asyncLoadState.m_mapLoadCursor;

                Memory.CopyToAMemorySync(readBuffer, amemCursor, (len + 0x1F) & ~0x1F);
                m_asyncLoadState.m_fileSizes[i] = len;
                m_asyncLoadState.m_fileChecksums[i] = CheckSum(readBuffer, len);
                m_asyncLoadState.m_asyncReadIndex++;
                m_asyncLoadState.m_mapLoadCursor =
                    reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + len;

                File.Close(reinterpret_cast<CFile::CHandle*>(m_asyncLoadState.m_asyncHandles[i]));
                m_asyncLoadState.m_asyncHandles[i] = 0;
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::MapCheckFileRead(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::LoadMapNoSyncCalc()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800330CC
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapObj* CMapMng::SearchChildMapObj(CMapObj* searchStart, CMapObj* parentObj)
{
    const int objCount = m_mapObjCount;
    CMapObj* mapObjEnd = m_mapObjArray + objCount;

    for (CMapObj* obj = searchStart; obj < mapObjEnd; obj++) {
        if (obj->m_parent == parentObj) {
            return obj;
        }
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SearchAtribMapObj(CMapObj*, CMapObjAtr::TYPE)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80032fd0
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::AttachMapHit(CMapHit* mapHit, char* mapHitName)
{
    CMapObj* mapObj = GetMapObjArray();

    goto search;
    while (true) {
        CMapObjAtrMeshName* meshName = static_cast<CMapObjAtrMeshName*>(mapObj->m_attribute);
        if (strcmp(mapHitName, meshName->m_name) == 0) {
            mapObj->m_mapData = mapHit;

            CMapObjAtr* mapObjAtr = mapObj->m_attribute;
            if (mapObjAtr != 0) {
                delete mapObjAtr;
                mapObj->m_attribute = 0;
            }
        }

        mapObj++;

search:
        unsigned int stride =
            reinterpret_cast<unsigned int>(mapObj + 1) - reinterpret_cast<unsigned int>(mapObj);
        CMapObj* mapObjEnd = m_mapObjArray + m_mapObjCount;
        unsigned int remaining =
            (reinterpret_cast<unsigned int>(mapObjEnd) + (stride - 1) - reinterpret_cast<unsigned int>(mapObj)) /
            stride;

        for (unsigned int i = 0; i < remaining; i++) {
            if (mapObj >= mapObjEnd) {
                break;
            }
            CMapObjAtr* mapObjAtr = mapObj->m_attribute;
            if (mapObjAtr != 0 && mapObjAtr->m_type == CMapObjAtr::MESH_NAME) {
                goto found;
            }
            mapObj++;
        }

        mapObj = 0;
found:
        if (mapObj == 0) {
            return;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80032f1c
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::GetDebugPlaySta(int playStaNo, Vec* vec)
{
    CMapObj* mapObj = GetMapObjArray();

    goto search;
    while (true) {
        CMapObjAtrPlaySta* mapObjAtr = static_cast<CMapObjAtrPlaySta*>(mapObj->m_attribute);
        if (mapObjAtr->m_playStaNo == playStaNo) {
            vec->x = MapObjWorldX(mapObj);
            vec->y = MapObjWorldY(mapObj);
            vec->z = MapObjWorldZ(mapObj);
            return 1;
        }
        mapObj++;

search:
        unsigned int stride =
            reinterpret_cast<unsigned int>(mapObj + 1) - reinterpret_cast<unsigned int>(mapObj);
        CMapObj* mapObjEnd = m_mapObjArray + m_mapObjCount;
        unsigned int remaining =
            (reinterpret_cast<unsigned int>(mapObjEnd) + (stride - 1) - reinterpret_cast<unsigned int>(mapObj)) /
            stride;

        if (mapObj < mapObjEnd) {
            for (unsigned int i = 0; i < remaining; i++) {
                CMapObjAtr* mapObjAtr = mapObj->m_attribute;
                if (mapObjAtr != 0 && mapObjAtr->m_type == CMapObjAtr::PLAY_STA) {
                    goto found;
                }
                mapObj++;
            }
        }

        mapObj = 0;
found:
        if (mapObj == 0) {
            vec->z = kMapZero;
            vec->y = kMapZero;
            vec->x = kMapZero;
            return 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80032bf0
 * PAL Size: 812b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetLightSource()
{
    int mapLightIndex = 0;
    const short mapObjCount = m_mapObjCount;
    CMapObj* mapObj = GetMapObjArray();
    CMapObj* mapObjEnd = m_mapObjArray + mapObjCount;

    while (mapObj < mapObjEnd) {
        CMapObjAtr* attr = mapObj->m_attribute;
        if (attr != 0) {
            const int type = attr->m_type;

            switch (type) {
            case CMapObjAtr::POINT_LIGHT: {
                CMapObjAtrPointLight* pointAttr = static_cast<CMapObjAtrPointLight*>(attr);
                CLightPcs::CLight light;
                light.m_type = 0;
                light.m_position.x = MapObjWorldX(mapObj);
                light.m_position.y = MapObjWorldY(mapObj);
                light.m_position.z = MapObjWorldZ(mapObj);
                light.m_direction.x = kMapZero;
                light.m_direction.y = kMapZero;
                light.m_direction.z = kMapViewScaleZ;
                light.m_partMask = 1 << mapLightIndex;
                light.m_attenRadius = pointAttr->m_radius;
                light.m_range = pointAttr->m_intensity;
                light.m_attenFalloff = kMapViewScaleZ;
                light.m_targetColor[0] = pointAttr->m_altColor;
                light.m_targetColor[1] = pointAttr->m_color;
                *(u32*)light.m_targetEnable = 0;
                light.m_spotFn = pointAttr->m_colorMode;
                light.m_unk4D = 4;
                light.m_directionMode = pointAttr->m_unknown20;
                LightPcs.Add(&light);
                mapLightIndex += 1;
                break;
            }
            case CMapObjAtr::SPOT_LIGHT: {
                CMapObjAtrSpotLight* spotAttr = static_cast<CMapObjAtrSpotLight*>(attr);
                if (*reinterpret_cast<unsigned int*>(&spotAttr->m_baseColor) != 0) {
                    CLightPcs::CLight* light = spotAttr->m_light;
                    light->m_type = 1;
                    light->m_targetColor[1] = spotAttr->m_color;
                    light->m_position.x = MapObjWorldX(mapObj);
                    light->m_position.y = MapObjWorldY(mapObj);
                    light->m_position.z = MapObjWorldZ(mapObj);
                    light->m_direction.x = kMapZero;
                    light->m_direction.y = kMapZero;
                    light->m_direction.z = kMapViewScaleZ;

                    CMapObj* targetObj = spotAttr->m_target;
                    light->m_targetPosition.x = MapObjWorldX(targetObj);
                    light->m_targetPosition.y = MapObjWorldY(targetObj);
                    light->m_targetPosition.z = MapObjWorldZ(targetObj);
                    PSVECSubtract(reinterpret_cast<Vec*>(&light->m_targetPosition),
                                  reinterpret_cast<Vec*>(&light->m_position),
                                  reinterpret_cast<Vec*>(&light->m_direction));
                    PSVECNormalize(reinterpret_cast<Vec*>(&light->m_direction), reinterpret_cast<Vec*>(&light->m_direction));
                } else {
                    CLightPcs::CLight light;
                    light.m_type = 1;
                    light.m_position.x = MapObjWorldX(mapObj);
                    light.m_position.y = MapObjWorldY(mapObj);
                    light.m_position.z = MapObjWorldZ(mapObj);

                    light.m_direction.x = kMapZero;
                    light.m_direction.y = kMapZero;
                    light.m_direction.z = kMapViewScaleZ;

                    CMapObj* targetObj = spotAttr->m_target;
                    light.m_targetPosition.x = MapObjWorldX(targetObj);
                    light.m_targetPosition.y = MapObjWorldY(targetObj);
                    light.m_targetPosition.z = MapObjWorldZ(targetObj);

                    PSVECSubtract(reinterpret_cast<Vec*>(&light.m_targetPosition),
                                  reinterpret_cast<Vec*>(&light.m_position),
                                  reinterpret_cast<Vec*>(&light.m_direction));
                    PSVECNormalize(reinterpret_cast<Vec*>(&light.m_direction), reinterpret_cast<Vec*>(&light.m_direction));

                    light.m_attenRadius = spotAttr->m_radius;
                    light.m_range = spotAttr->m_nearRange;
                    light.m_attenFalloff = spotAttr->m_farRange;

                    light.m_targetColor[0] = spotAttr->m_altColor;
                    light.m_targetColor[1] = spotAttr->m_color;

                    light.m_spotFn = spotAttr->m_colorMode;
                    light.m_unk4D = (spotAttr->m_useAltColor == 0) ? 4 : 2;
                    light.m_directionMode = spotAttr->m_keyFrameCount;
                    light.m_partMask = 1 << mapLightIndex;
                    *(u32*)light.m_targetEnable = 0;
                    LightPcs.Add(&light);
                }
                mapLightIndex += 1;
                break;
            }
            }
        }

        mapObj++;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetBumpLightSource()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::InitMapShadow()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80032784
 * PAL Size: 1132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::ReadMtx(char* mapName)
{
    int append = 0;

    MapMng.m_mapReadReady = 1;

    if (m_asyncLoadState.m_mapReadMode != 2 && m_asyncLoadState.m_mapReadMode != 3) {
        CMemory::CStage* stage = MapMng.m_stage;
        CTextureSet* textureSet = new (stage, const_cast<char*>(s_map_cpp), 0x3A9) CTextureSet;
        m_textureSet = textureSet;
    }

    char* strTmp = g_StrTmp;
    int loadIndex = 0;
    while (true) {
        sprintf(strTmp, const_cast<char*>(s_mapMtxPathFmt), mapName, loadIndex);

        int exists;
        if (m_asyncLoadState.m_mapReadMode == 1) {
            exists = 1;
        } else {
            CFile::CHandle* openProbe = File.Open(strTmp, 0, CFile::PRI_LOW);
            if (openProbe != 0) {
                File.Close(openProbe);
                exists = 1;
            } else {
                exists = 0;
            }
        }
        if (!exists) {
            if (m_asyncLoadState.m_mapReadMode == 2) {
                return 1;
            }
            if (m_asyncLoadState.m_mapReadMode == 3) {
                return 1;
            }
            if (loadIndex == 0) {
                if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                    System.Printf(const_cast<char*>(s_mapReadOpenErrorFmt), strTmp);
                }
                return 0;
            }
            return 1;
        }

        if (static_cast<int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(s_mapReadMtxFmt), strTmp);
        }

        void* filePtr;
        if (m_asyncLoadState.m_mapReadMode == 1) {
            int size = m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex];
            filePtr = File.m_readBuffer;
            Memory.CopyFromAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, static_cast<unsigned long>((size + 0x1F) & ~0x1F));
            m_asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
            CheckSum(filePtr, size);
            m_asyncLoadState.m_asyncReadIndex += 1;
        } else {
            CFile::CHandle* handle = File.Open(strTmp, 0, CFile::PRI_LOW);
            if (handle != 0) {
                int size = File.GetLength(handle);
                if (m_asyncLoadState.m_mapReadMode == 3) {
                    File.ReadASync(handle);
                    filePtr = reinterpret_cast<void*>(1);
                    m_asyncLoadState.m_asyncHandles[m_asyncLoadState.m_asyncOpenIndex] = handle;
                    m_asyncLoadState.m_asyncOpenIndex += 1;
                } else {
                    File.Read(handle);
                    File.SyncCompleted(handle);
                    filePtr = File.m_readBuffer;
                    File.Close(handle);
                    if (m_asyncLoadState.m_mapReadMode == 2) {
                        Memory.CopyToAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, static_cast<unsigned long>(size));
                        m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex] = size;
                        m_asyncLoadState.m_fileChecksums[m_asyncLoadState.m_asyncReadIndex] = CheckSum(filePtr, size);
                        m_asyncLoadState.m_asyncReadIndex += 1;
                        m_asyncLoadState.m_mapLoadCursor =
                            reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
                    }
                }
            } else {
                filePtr = 0;
            }
        }

        if (filePtr == 0) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(s_mapReadErrorFmt), strTmp);
            }
            return 0;
        }

        if (m_asyncLoadState.m_mapReadMode != 3) {
            CChunkFile chunkFile;
            chunkFile.SetBuf(filePtr);
            CChunkFile::CChunk chunk;

            if (m_asyncLoadState.m_mapReadMode == 2) {
                while (chunkFile.GetNextChunk(chunk)) {
                    switch (chunk.m_id) {
                    case 0x54534554:
                        if (chunk.m_arg0 == 1) {
                            return 1;
                        }
                        break;
                    }
                }
            } else {
                while (chunkFile.GetNextChunk(chunk)) {
                    switch (chunk.m_id) {
                    case 0x54534554:
                        m_textureSet->Create(chunkFile, MapMng.m_stage, append, 0, 0, 0);
                        append = 1;
                        if (chunk.m_arg0 == 1) {
                            return 1;
                        }
                        break;
                    }
                }
            }
        }

        loadIndex += 1;
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800322c4
 * PAL Size: 1216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::ReadMpl(char* mapName)
{
    int loadIndex = 0;

    MapMng.m_mapReadReady = 1;

    char* strTmp = g_StrTmp;
    while (true) {
        sprintf(strTmp, const_cast<char*>(s_mapMplPathFmt), mapName, loadIndex);

        int canRead;
        if (m_asyncLoadState.m_mapReadMode == 1) {
            canRead = 1;
        } else {
            CFile::CHandle* existsHandle = File.Open(strTmp, 0, CFile::PRI_LOW);
            if (existsHandle != 0) {
                File.Close(existsHandle);
                canRead = 1;
            } else {
                canRead = 0;
            }
        }

        if (!canRead) {
            if (m_asyncLoadState.m_mapReadMode == 3) {
                return 1;
            }
            if (loadIndex == 0) {
                if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                    System.Printf(const_cast<char*>(s_mapReadOpenErrorFmt), strTmp);
                }
                return 0;
            }
            return 1;
        }

        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(s_mapReadMplFmt), strTmp);
        }

        void* filePtr;
        if (m_asyncLoadState.m_mapReadMode == 1) {
            const int size = m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex];
            filePtr = File.m_readBuffer;

            Memory.CopyFromAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, (size + 0x1F) & ~0x1F);
            m_asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
            CheckSum(filePtr, size);
            m_asyncLoadState.m_asyncReadIndex += 1;
        } else {
            CFile::CHandle* fileHandle = File.Open(strTmp, 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                const int size = File.GetLength(fileHandle);
                if (m_asyncLoadState.m_mapReadMode == 3) {
                    File.ReadASync(fileHandle);
                    filePtr = reinterpret_cast<void*>(1);
                    m_asyncLoadState.m_asyncHandles[m_asyncLoadState.m_asyncOpenIndex] = fileHandle;
                    m_asyncLoadState.m_asyncOpenIndex += 1;
                } else {
                    File.Read(fileHandle);
                    File.SyncCompleted(fileHandle);
                    filePtr = File.m_readBuffer;
                    File.Close(fileHandle);
                    if (m_asyncLoadState.m_mapReadMode == 2) {
                        Memory.CopyToAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, static_cast<unsigned long>(size));
                        m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex] = size;
                        m_asyncLoadState.m_fileChecksums[m_asyncLoadState.m_asyncReadIndex] = CheckSum(filePtr, size);
                        m_asyncLoadState.m_asyncReadIndex += 1;
                        m_asyncLoadState.m_mapLoadCursor =
                            reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
                    }
                }
            } else {
                filePtr = 0;
            }
        }

        if (filePtr == 0) {
            if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                System.Printf(const_cast<char*>(s_mapReadErrorFmt), strTmp);
            }
            return 0;
        }

        if (m_asyncLoadState.m_mapReadMode != 3) {
            CChunkFile chunkFile;
            chunkFile.SetBuf(filePtr);
            CChunkFile::CChunk chunk;

            if (m_asyncLoadState.m_mapReadMode == 2) {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x4D455348 && chunk.m_arg0 == 1) {
                        return 1;
                    }
                }
            } else {
                while (chunkFile.GetNextChunk(chunk)) {
                    switch (chunk.m_id) {
                    case 0x4D455348:
                        break;
                    default:
                        continue;
                    }

                    chunkFile.PushChunk();
                    CChunkFile::CChunk meshChunk;
                    while (chunkFile.GetNextChunk(meshChunk)) {
                        switch (meshChunk.m_id) {
                        case 0x56534554: {
                            short& meshCount = m_mapMeshCount;
                            if (meshCount >= 0xA0) {
                                return 0;
                            }
                            CMapMesh* mesh = GetMapMeshArray() + meshCount;
                            mesh->ReadOtmMesh(chunkFile, m_stage, 1, 1);
                            break;
                        }
                        case 0x44534554: {
                            short& meshCount = m_mapMeshCount;
                            CMapMesh* mesh = GetMapMeshArray() + meshCount;
                            mesh->ReadOtmMesh(chunkFile, m_stage, 1, 1);
                            meshCount += 1;
                            break;
                        }
                        }
                    }
                    chunkFile.PopChunk();

                    if (chunk.m_arg0 == 1) {
                        return 1;
                    }
                }
            }
        }

        loadIndex += 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800319ec
 * PAL Size: 2264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::ReadOtm(char* mapName)
{
    void* filePtr;

    MapMng.m_mapReadReady = 1;
    char* strTmp = g_StrTmp;
    sprintf(strTmp, const_cast<char*>(s_mapOtmPathFmt), mapName);
    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_read_otm_fmt), strTmp);
    }
    m_mapAnimFrame = 0;

    if (m_asyncLoadState.m_mapReadMode == 1) {
        const int size = m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex];
        filePtr = File.m_readBuffer;

        Memory.CopyFromAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, (size + 0x1F) & ~0x1F);
        m_asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
        CheckSum(filePtr, size);
        m_asyncLoadState.m_asyncReadIndex += 1;
    } else {
        CFile::CHandle* fileHandle = File.Open(strTmp, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            const int size = File.GetLength(fileHandle);
            if (m_asyncLoadState.m_mapReadMode == 3) {
                File.ReadASync(fileHandle);
                filePtr = reinterpret_cast<void*>(1);
                m_asyncLoadState.m_asyncHandles[m_asyncLoadState.m_asyncOpenIndex] = fileHandle;
                m_asyncLoadState.m_asyncOpenIndex += 1;
            } else {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                filePtr = File.m_readBuffer;
                File.Close(fileHandle);

                if (m_asyncLoadState.m_mapReadMode == 2) {
                    Memory.CopyToAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, static_cast<unsigned long>(size));
                    m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex] = size;
                    m_asyncLoadState.m_fileChecksums[m_asyncLoadState.m_asyncReadIndex] = CheckSum(filePtr, size);
                    m_asyncLoadState.m_asyncReadIndex += 1;
                    m_asyncLoadState.m_mapLoadCursor =
                        reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
                }
            }
        } else {
            filePtr = 0;
        }
    }

    if (filePtr == 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_mapReadErrorFmt), strTmp);
        }
        return 0;
    }

    if (m_asyncLoadState.m_mapReadMode == 2) {
        return 1;
    }
    if (m_asyncLoadState.m_mapReadMode == 3) {
        return 1;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(filePtr);

    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x4F544D20:
            break;
        default:
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk)) {
            switch (chunk.m_id) {
            case 0x5343454E:
                break;

            case 0x4F43544D: {
                short& octTreeCount = m_octTreeCount;
                if (octTreeCount >= 0x10) {
                    return 0;
                }

                COctTree* octTree = GetOctTreeArray() + octTreeCount;
                octTree->ReadOtmOctTree(chunkFile);
                octTreeCount += 1;
                continue;
            }

            case 0x4C495448: {
                CMapLightHolder* light = static_cast<CMapLightHolder*>(
                    operator new(0x10, MapMng.m_stage, const_cast<char*>(s_map_cpp), 0x4D3));
                unsigned char* lightRaw = reinterpret_cast<unsigned char*>(light);
                lightRaw[0] = chunkFile.Get1();
                lightRaw[1] = chunkFile.Get1();
                lightRaw[2] = chunkFile.Get1();
                lightRaw[3] = chunkFile.Get1();
                *reinterpret_cast<float*>(lightRaw + 4) = chunkFile.GetF4();
                *reinterpret_cast<float*>(lightRaw + 8) = chunkFile.GetF4();
                *reinterpret_cast<float*>(lightRaw + 0xC) = chunkFile.GetF4();

                GetMapLightHolderArray(chunk.m_arg0).Add(light);
                continue;
            }

            default:
                goto otmDone;
            }

            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 0x4D534554: {
                    m_materialSet =
                        new (MapMng.m_stage, const_cast<char*>(s_map_cpp), 0x482) CMaterialSet();
                    m_materialSet->m_materials.SetDefaultSize(0x180);
                    m_materialSet->m_materials.SetGrow(0);
                    m_materialSet->Create(chunkFile, m_textureSet, static_cast<CMaterialMan::TEV_BIT>(0xFFF53060), 0);
                    break;
                }

                case 0x41534554: {
                    m_mapTexAnimSet =
                        new (MapMng.m_stage, const_cast<char*>(s_map_cpp), 0x49A) CMapTexAnimSet();
                    m_mapTexAnimSet->Create(chunkFile, m_materialSet, m_textureSet);
                    break;
                }

                case 0x4D455348: {
                    short& meshCount = m_mapMeshCount;
                    if (meshCount >= 0xA0) {
                        return 0;
                    }
                    CMapMesh* mesh = GetMapMeshArray() + meshCount;
                    mesh->ReadOtmMesh(chunkFile, MapMng.m_stage, 0, 1);
                    meshCount += 1;
                    break;
                }

                case 0x48495420: {
                    short& hitCount = m_mapHitCount;
                    if (hitCount >= 0x20) {
                        return 0;
                    }
                    CMapHit* hit = GetMapHitArray() + hitCount;
                    hit->ReadOtmHit(chunkFile);
                    hitCount += 1;
                    break;
                }

                case 0x4E4F4445: {
                    short& mapObjCount = m_mapObjCount;
                    if (mapObjCount >= 0x200) {
                        return 0;
                    }
                    CMapObj* mapObj = GetMapObjArray() + mapObjCount;
                    mapObj->ReadOtmObj(chunkFile);
                    mapObjCount += 1;
                    break;
                }

                case 0x414E494D: {
                    CMapAnim* mapAnim = new (MapMng.m_stage, const_cast<char*>(s_map_cpp), 0x4BF) CMapAnim();
                    mapAnim->ReadOtmAnim(chunkFile);
                    GetMapAnimArray().Add(mapAnim);
                    break;
                }
                }
            }
            chunkFile.PopChunk();
        }
    otmDone:
        chunkFile.PopChunk();
    }

    for (int i = 0; i < m_octTreeCount; i++) {
        CMapObj* mapObj = m_octTreeArray[i].GetMapObject();
        if (mapObj != 0) {
            mapObj->m_octTreeIndex = static_cast<signed char>(i);
        }
    }

    for (unsigned int i = 0; i < static_cast<unsigned int>(GetMapShadowArray().GetSize()); i++) {
        GetMapShadowArray()[i]->Init();
    }

    CMapObj* mapObj = GetMapObjArray();
    CMapObj* mapObjEnd = GetMapObjArray() + m_mapObjCount;
    CMapObj* root = 0;
    while (mapObj < mapObjEnd) {
        if (mapObj->m_parent == 0) {
            root = mapObj;
            break;
        }
        mapObj++;
    }

    m_rootMapObj = root;
    if (root == 0) {
        if (System.m_execParam != 0) {
            System.Printf(const_cast<char*>(s_error_root_mapobj_not_found));
        }
        return 0;
    }

    root->SetLink();

    Mtx identity;
    PSMTXIdentity(identity);
    root->CalcMtx(identity, 1);

    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* obj = GetMapObjArray() + i;
        CMapObjAtr* attr = obj->m_attribute;
        if (attr == 0) {
            continue;
        }
        if (attr->m_type != CMapObjAtr::SPOT_LIGHT) {
            continue;
        }

        CMapObjAtrSpotLight* spotAttr = static_cast<CMapObjAtrSpotLight*>(attr);
        if (*reinterpret_cast<unsigned int*>(&spotAttr->m_baseColor) == 0) {
            continue;
        }

        CLightPcs::CBumpLight light;
        light.m_type = 1;
        light.m_position.x = MapObjWorldX(obj);
        light.m_position.y = MapObjWorldY(obj);
        light.m_position.z = MapObjWorldZ(obj);

        CMapObj* targetObj = spotAttr->m_target;
        light.m_targetPosition.x = MapObjWorldX(targetObj);
        light.m_targetPosition.y = MapObjWorldY(targetObj);
        light.m_targetPosition.z = MapObjWorldZ(targetObj);
        PSVECSubtract(
            reinterpret_cast<Vec*>(&light.m_targetPosition),
            reinterpret_cast<Vec*>(&light.m_position),
            reinterpret_cast<Vec*>(&light.m_direction));
        PSVECNormalize(
            reinterpret_cast<Vec*>(&light.m_direction),
            reinterpret_cast<Vec*>(&light.m_direction));

        *reinterpret_cast<unsigned int*>(&light.m_bumpShade) =
            *reinterpret_cast<unsigned int*>(&spotAttr->m_baseColor);
        light.m_offsetX = spotAttr->m_intensity;
        light.m_offsetZ = spotAttr->m_falloff;
        light.m_specularScale = spotAttr->m_angle;
        light.m_targetColor[1].r = spotAttr->m_color.r;
        light.m_targetColor[1].g = spotAttr->m_color.g;
        light.m_targetColor[1].b = spotAttr->m_color.b;
        light.m_targetColor[1].a = spotAttr->m_color.a;

        CLightPcs::CBumpLight* bump = LightPcs.AddBump(
            &light,
            static_cast<CLightPcs::TARGET>(1),
            m_stage,
            1);
        spotAttr->m_light = bump;

        for (int j = 0; j < m_mapObjCount; j++) {
            CMapObj* scan = GetMapObjArray() + j;
            if (scan->m_bumpObjId == i) {
                scan->m_bumpLight = spotAttr->m_light;
            }
        }

    }
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80031410
 * PAL Size: 1500b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::ReadMid(char* mapName)
{
    char* strTmp = g_StrTmp;
    sprintf(strTmp, const_cast<char*>(s_mapMidPathFmt), mapName);
    int ok = 1;

    if (static_cast<unsigned int>(System.m_execParam) >= 3) {
        System.Printf(const_cast<char*>(s_read_mid_fmt), strTmp);
    }

    void* filePtr;
    if (m_asyncLoadState.m_mapReadMode == 1) {
        const int size = m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex];
        filePtr = File.m_readBuffer;

        Memory.CopyFromAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, static_cast<unsigned long>((size + 0x1F) & ~0x1F));
        m_asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
        CheckSum(filePtr, size);
        m_asyncLoadState.m_asyncReadIndex += 1;
    } else {
        CFile::CHandle* fileHandle = File.Open(strTmp, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            const int size = File.GetLength(fileHandle);
            if (m_asyncLoadState.m_mapReadMode == 3) {
                File.ReadASync(fileHandle);
                filePtr = reinterpret_cast<void*>(1);
                m_asyncLoadState.m_asyncHandles[m_asyncLoadState.m_asyncOpenIndex] = fileHandle;
                m_asyncLoadState.m_asyncOpenIndex += 1;
            } else {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                filePtr = File.m_readBuffer;
                File.Close(fileHandle);

                if (m_asyncLoadState.m_mapReadMode == 2) {
                    Memory.CopyToAMemorySync(filePtr, m_asyncLoadState.m_mapLoadCursor, static_cast<unsigned long>(size));
                    m_asyncLoadState.m_fileSizes[m_asyncLoadState.m_asyncReadIndex] = size;
                    m_asyncLoadState.m_fileChecksums[m_asyncLoadState.m_asyncReadIndex] = CheckSum(filePtr, size);
                    m_asyncLoadState.m_asyncReadIndex += 1;
                    m_asyncLoadState.m_mapLoadCursor =
                        reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + size;
                }
            }
        } else {
            filePtr = 0;
        }
    }

    if (filePtr == 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_mapReadErrorFmt), strTmp);
        }
        return 0;
    }

    if (m_asyncLoadState.m_mapReadMode == 2) {
        return 1;
    }
    if (m_asyncLoadState.m_mapReadMode == 3) {
        return 1;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(filePtr);

    CMapObj* nextMapObj = GetMapObjArray();
    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x4D494420:
            break;
        default:
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk)) {
            switch (chunk.m_id) {
            case 0x5343454E: {
                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk)) {
                    switch (chunk.m_id) {
                    case 0x48495420:
                        break;
                    default:
                        continue;
                    }

                    short& hitCount = m_mapHitCount;
                    if (hitCount >= 0x20) {
                        return 0;
                    }
                    CMapHit* hit = GetMapHitArray() + hitCount;
                    hit->ReadOtmHit(chunkFile);
                    hitCount += 1;
                }
                chunkFile.PopChunk();
                continue;
            }
            case 0x4F43544D:
                break;
            default:
                continue;
            }

            CMapObj* mapObj = nextMapObj;
            int mapObjIndex = 0;
            while (mapObjIndex < m_mapObjCount) {
                if (mapObj->m_meshType == 1 || mapObj->m_meshType == 2) {
                    short& octTreeCount = m_octTreeCount;
                    if (octTreeCount >= 0x10) {
                        return 0;
                    }

                    COctTree* octTree = GetOctTreeArray() + octTreeCount;
                    octTree->ReadOtmOctTree(chunkFile);
                    octTree->SetMapObject(mapObj);

                    if (mapObj->m_mapData == 0) {
                        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                            System.Printf(const_cast<char*>(s_read_mid_mapobj_error));
                        }
                    } else if (mapObj->m_meshType == 1 || mapObj->m_meshType == 2) {
                        nextMapObj = mapObj + 1;
                        octTreeCount += 1;
                        break;
                    }

                    if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                        System.Printf(const_cast<char*>(s_read_mid_octtree_error));
                    }
                    ok = 0;
                    nextMapObj = mapObj + 1;
                    octTreeCount += 1;
                    break;
                }

                mapObj++;
                mapObjIndex += 1;
            }

            if (mapObjIndex >= m_mapObjCount) {
                if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                    System.Printf(const_cast<char*>(s_error_root_mapobj_not_found));
                    System.Printf(const_cast<char*>(s_read_mid_octtree_error));
                }
                ok = 0;
            }
        }
        chunkFile.PopChunk();
    }

    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* obj = &MapMng.m_mapObjArray[i];
        signed char type = obj->m_mapDataType;
        CMapHit* hit = static_cast<CMapHit*>(obj->m_mapData);
        if ((type == 2 || type == 3) && hit != 0) {
            int hitIndex = hit - GetMapHitArray();
            if (hitIndex >= m_mapHitCount) {
                if (static_cast<unsigned int>(System.m_execParam) >= 1) {
                    System.Printf(const_cast<char*>(s_read_mid_hit_error));
                }
                obj->m_mapData = 0;
            }
        }
    }

    if (ok) {
        if (static_cast<unsigned int>(System.m_execParam) >= 3) {
            System.Printf(const_cast<char*>(s_read_mid_ok));
        }
    } else if (static_cast<unsigned int>(System.m_execParam) >= 1) {
        System.Printf(const_cast<char*>(s_read_mid_error));
    }

    for (int i = 0; i < m_octTreeCount; i++) {
        CMapObj* mapObj = m_octTreeArray[i].GetMapObject();
        if (mapObj != 0) {
            mapObj->m_octTreeIndex = static_cast<signed char>(i);
        }
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800311e8
 * PAL Size: 552b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Calc()
{
    m_calcCount += 1;

    if (m_mapObjCount == 0) {
        return;
    }

    const int mapAnimRunCount = GetMapAnimRunArray().GetSize();
    for (unsigned int i = 0; static_cast<int>(i) < mapAnimRunCount; i++) {
        CMapAnimRun* mapAnimRun = GetMapAnimRunArray()[i];
        mapAnimRun->Calc(m_mapAnimFrame);
    }

    Mtx identity;
    PSMTXIdentity(identity);

    CMapObj* mapObj = m_rootMapObj;
    if (mapObj != 0) {
        mapObj->CalcMtx(identity, 0);
    }

    int& mapLightId = m_mapAnimFrame;
    mapLightId += 1;
    mapLightId += 1;
    if (static_cast<unsigned char>(mapLightId) != 0x1E) {
        mapLightId = 0x1C;
    }

    SetLightSource();

    for (unsigned int i = 0; i < static_cast<unsigned int>(GetMapShadowArray().GetSize()); i++) {
        CMapShadow* mapShadow = GetMapShadowArray()[i];
        mapShadow->Calc();
    }

    for (int i = 0; i < m_mapObjCount; i++) {
        MapMng.m_mapObjArray[i].Calc();
    }

    CMapTexAnimSet* mapTexAnimSet = m_mapTexAnimSet;
    if (mapTexAnimSet != 0) {
        mapTexAnimSet->Calc();
    }

    CMaterialSet* materialSet = m_materialSet;
    materialSet->Calc();

    for (int i = 0; i < m_octTreeCount; i++) {
        LightPcs.InsertOctTree(static_cast<CLightPcs::TARGET>(1), m_octTreeArray[i]);
    }

    for (int i = 0; i < m_octTreeCount; i++) {
        CMapShadowInsertOctTree(static_cast<CMapShadow::TARGET>(1), m_octTreeArray[i]);
    }

    for (int i = 0; i < m_octTreeCount; i++) {
        m_octTreeArray[i].SetDrawFlag();
    }

    for (int i = 0; i < m_mapObjCount; i++) {
        MapMng.m_mapObjArray[i].SetDrawFlag();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
#pragma dont_inline on
void CMapMng::DrawMapShadow()
{
    if (m_mapObjCount != 0) {
        for (unsigned int i = 0; i < static_cast<unsigned int>(m_mapShadowArray.GetSize()); i++) {
            CMapShadow* mapShadow = m_mapShadowArray[i];
            mapShadow->Draw();
        }
    }
}
#pragma dont_inline reset

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void setDbgLight(int, Vec&, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80031084
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::DrawBefore()
{
    if ((m_mapObjCount != 0) && (m_mapReadReady != 0)) {
        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetZMode(1, GX_LEQUAL, 1);
        LightPcs.SetNumDiffuse(0);

        if ((s_bitMask.m_fields.m_mode & 8) == 0) {
            for (int i = 0; i < m_mapObjCount; i++) {
                CMapObj* mapObj = MapMng.GetMapObj(i);
                mapObj->Draw(0xFE);
            }

            for (int i = 0; i < m_octTreeCount; i++) {
                m_octTreeArray[i].Draw(0xFF);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80030394
 * PAL Size: 3312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::Draw()
{
    if ((m_mapReadReady == 0) || (m_mapObjCount == 0)) {
        return;
    }

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(GX_CULL_FRONT);
    GXSetZMode(1, GX_LEQUAL, 1);
    LightPcs.SetNumDiffuse(0);

    Mtx44 projection;
    PSMTX44Copy(CameraPcs.m_screenMatrix, projection);
    GXSetProjection(projection, GX_PERSPECTIVE);
    m_underWaterTexPending = 1;

    if ((s_bitMask.m_fields.m_mode & 8) == 0) {
        for (int i = 0; i < m_octTreeCount; i++) {
            m_octTreeArray[i].Draw(0);
        }

        for (int i = 0; i < m_mapObjCount; i++) {
            MapMng.m_mapObjArray[i].Draw(0x40);
        }

        PartPcs.DrawShoki();

        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetZMode(1, GX_LEQUAL, 1);
        LightPcs.SetNumDiffuse(0);

        for (int i = 0; i < m_mapObjCount; i++) {
            MapMng.m_mapObjArray[i].Draw(0);
        }

        for (int i = 0; i < m_octTreeCount; i++) {
            m_octTreeArray[i].Draw(1);
        }

        if (Game.m_currentSceneId == 4) {
            CharaPcs.drawMakeTexShadow();
            MaterialMan.InitVtxFmt(-1, GX_RGB565, 0, GX_U16, 0xE, GX_U16, 10);
            MaterialMan.SetDefaultDrawEnv(0x000ACE0F);
            Graphic.SetFog(MapMng.m_fogEnable, 0);

            GXSetColorUpdate(1);
            GXSetAlphaUpdate(0);
            GXSetCullMode(GX_CULL_FRONT);
            GXSetZMode(1, GX_LEQUAL, 1);
            _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapModeTable(GX_TEV_SWAP3, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
            _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
            _GXSetTevSwapMode(GX_TEVSTAGE3, GX_TEV_SWAP0, GX_TEV_SWAP0);

            GXSetColorUpdate(1);
            GXSetAlphaUpdate(0);
            GXSetCullMode(GX_CULL_FRONT);
            GXSetZMode(1, GX_LEQUAL, 1);
            LightPcs.SetNumDiffuse(0);

            unsigned int shadowCount = CharaPcs.GetNumTexShadow();
            if (shadowCount != 0) {
                _GXTexObj texObjs[8];
                Vec shadowPositions[8];
                float shadowMatrices[8][3][4];

                GXSetNumIndStages(0);
                GXSetTevDirect(GX_TEVSTAGE0);
                GXSetNumChans(1);
                GXSetColorUpdate(1);
                GXSetAlphaUpdate(0);
                GXSetCullMode(GX_CULL_NONE);
                GXSetZMode(1, GX_LEQUAL, 0);
                _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_COPY);
                GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
                GXSetChanMatColor(GX_COLOR0A0, CharaPcs.m_texShadowColor);
                _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
                _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_RED, GX_CH_RED, GX_CH_RED);
                GXSetNumTevStages(1);
                GXSetZCompLoc(0);
                _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);

                int startIndex = 0;
                do {
                    unsigned int batchCount = 8;
                    if (shadowCount < batchCount) {
                        batchCount = shadowCount;
                    }

                    CharaPcs.GetTexShadow(startIndex, batchCount, texObjs, shadowPositions, shadowMatrices);

                    int texMtx = 0x1E;
                    int stage = 0;
                    for (unsigned int i = 0; i < batchCount; i++) {
                        GXLoadTexMtxImm(shadowMatrices[i], texMtx, GX_MTX2x4);
                        GXLoadTexObj(&texObjs[i], static_cast<GXTexMapID>(i));
                        GXSetTexCoordGen2(
                            static_cast<GXTexCoordID>(i), GX_TG_MTX2x4, GX_TG_TEX0,
                            static_cast<GXTexMtx>(texMtx), 0, GX_PTIDENTITY);
                        GXSetTevDirect(static_cast<GXTevStageID>(stage));
                        _GXSetTevOrder(
                            static_cast<GXTevStageID>(stage), static_cast<GXTexCoordID>(i),
                            static_cast<GXTexMapID>(i), GX_COLOR0A0);
                        _GXSetTevSwapMode(static_cast<GXTevStageID>(stage), GX_TEV_SWAP0, GX_TEV_SWAP1);
                        if (i == 0) {
                            _GXSetTevColorIn(
                                static_cast<GXTevStageID>(stage), GX_CC_ZERO, GX_CC_TEXC, GX_CC_RASC,
                                GX_CC_ZERO);
                            _GXSetTevColorOp(
                                static_cast<GXTevStageID>(stage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                                GX_TEVPREV);
                            _GXSetTevAlphaIn(
                                static_cast<GXTevStageID>(stage), GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA,
                                GX_CA_ZERO);
                            _GXSetTevAlphaOp(
                                static_cast<GXTevStageID>(stage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                                GX_TEVPREV);
                        } else {
                            _GXSetTevColorIn(
                                static_cast<GXTevStageID>(stage), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO,
                                GX_CC_CPREV);
                            _GXSetTevColorOp(
                                static_cast<GXTevStageID>(stage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                                GX_TEVPREV);
                            _GXSetTevAlphaIn(
                                static_cast<GXTevStageID>(stage), GX_CA_ZERO, GX_CA_TEXA, GX_CA_RASA,
                                GX_CA_APREV);
                            _GXSetTevAlphaOp(
                                static_cast<GXTevStageID>(stage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                                GX_TEVPREV);
                        }
                        texMtx += 3;
                        stage++;
                    }

                    GXSetTevDirect(static_cast<GXTevStageID>(stage));
                    _GXSetTevOrder(static_cast<GXTevStageID>(stage), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
                    _GXSetTevColorIn(
                        static_cast<GXTevStageID>(stage), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
                    _GXSetTevColorOp(
                        static_cast<GXTevStageID>(stage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1, GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<GXTevStageID>(stage), GX_CA_ZERO, GX_CA_RASA, GX_CA_APREV, GX_CA_TEXA);
                    _GXSetTevAlphaOp(
                        static_cast<GXTevStageID>(stage), GX_TEV_SUB, GX_TB_ZERO, GX_CS_SCALE_1, 0, GX_TEVREG2);

                    int finalStage = stage + 1;
                    GXSetTevDirect(static_cast<GXTevStageID>(finalStage));
                    _GXSetTevOrder(
                        static_cast<GXTevStageID>(finalStage), GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
                    _GXSetTevColorIn(
                        static_cast<GXTevStageID>(finalStage), GX_CC_ZERO, GX_CC_ZERO, GX_CC_ZERO, GX_CC_CPREV);
                    _GXSetTevColorOp(
                        static_cast<GXTevStageID>(finalStage), GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, 1,
                        GX_TEVPREV);
                    _GXSetTevAlphaIn(
                        static_cast<GXTevStageID>(finalStage), GX_CA_A2, GX_CA_TEXA, GX_CA_A2, GX_CA_APREV);
                    _GXSetTevAlphaOp(
                        static_cast<GXTevStageID>(finalStage), GX_TEV_COMP_R8_GT, GX_TB_ZERO, GX_CS_SCALE_1, 0,
                        GX_TEVPREV);

                    GXSetNumTexGens(static_cast<unsigned char>(batchCount));
                    GXSetNumTevStages(static_cast<unsigned char>(stage + 2));

                    shadowCount -= batchCount;
                    startIndex += batchCount;

                    for (int i = 0; i < m_octTreeCount; i++) {
                        m_octTreeArray[i].DrawCharaShadow(0);
                    }
                } while (shadowCount != 0);
            }
        }
    }

    if ((s_bitMask.m_fields.m_mode & 8) != 0) {
        _GXColor clearColor;
        clearColor.r = 0;
        clearColor.g = 0;
        clearColor.b = 0;
        clearColor.a = 0xFF;
        GXSetCopyClear(clearColor, 0x00FFFFFF);
    }

    if ((s_bitMask.m_fields.m_mode & 1) != 0) {
        _GXColor lightColor;
        *reinterpret_cast<u32*>(&lightColor) = 0xFFFFFFFF;

        Vec lightDir0;
        lightDir0.x = 1.0f;
        lightDir0.y = 1.0f;
        lightDir0.z = 1.0f;

        Mtx cameraMtx0;
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx0);

        Vec lightPos0;
        lightPos0.x = kMapLargeDistance * -lightDir0.x;
        lightPos0.y = kMapLargeDistance * -lightDir0.y;
        lightPos0.z = kMapLargeDistance * -lightDir0.z;

        GXLightObj lightObj0;
        GXInitLightColor(&lightObj0, lightColor);
        PSMTXMultVec(cameraMtx0, &lightPos0, &lightPos0);
        GXInitLightPos(&lightObj0, lightPos0.x, lightPos0.y, lightPos0.z);
        PSMTXMultVecSR(cameraMtx0, &lightDir0, &lightDir0);
        GXInitLightDir(&lightObj0, lightDir0.x, lightDir0.y, lightDir0.z);
        GXInitLightSpot(&lightObj0, kMapFullTurnDegrees, GX_SP_SHARP);
        GXInitLightAttnK(&lightObj0, kMapZero, kMapTinyEpsilon, kMapZero);
        GXLoadLightObjImm(&lightObj0, GX_LIGHT0);

        Vec lightDir1;
        lightDir1.x = -1.0f;
        lightDir1.y = 1.0f;
        lightDir1.z = -1.0f;

        Mtx cameraMtx1;
        PSMTXCopy(CameraPcs.m_cameraMatrix, cameraMtx1);

        Vec lightPos1;
        lightPos1.x = kMapLargeDistance * -lightDir1.x;
        lightPos1.y = kMapLargeDistance * -lightDir1.y;
        lightPos1.z = kMapLargeDistance * -lightDir1.z;

        GXLightObj lightObj1;
        GXInitLightColor(&lightObj1, lightColor);
        PSMTXMultVec(cameraMtx1, &lightPos1, &lightPos1);
        GXInitLightPos(&lightObj1, lightPos1.x, lightPos1.y, lightPos1.z);
        PSMTXMultVecSR(cameraMtx1, &lightDir1, &lightDir1);
        GXInitLightDir(&lightObj1, lightDir1.x, lightDir1.y, lightDir1.z);
        GXInitLightSpot(&lightObj1, kMapFullTurnDegrees, GX_SP_SHARP);
        GXInitLightAttnK(&lightObj1, kMapZero, kMapTinyEpsilon, kMapZero);
        GXLoadLightObjImm(&lightObj1, GX_LIGHT1);

        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0, 1, GX_SRC_REG, GX_SRC_VTX, static_cast<GXLightID>(GX_LIGHT0 | GX_LIGHT1),
                      GX_DF_CLAMP, GX_AF_SPEC);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPOT);

        _GXColor materialColor;
        *reinterpret_cast<u32*>(&materialColor) = 0xFFFFFFFF;
        GXSetChanMatColor(GX_COLOR0A0, materialColor);

        _GXColor ambientColor;
        *reinterpret_cast<u32*>(&ambientColor) = 0x404040FF;
        GXSetChanAmbColor(GX_COLOR0A0, ambientColor);

        if ((s_bitMask.m_fields.m_mode & 2) == 0) {
            _GXSetBlendMode(GX_BM_NONE, GX_BL_ONE, GX_BL_INVSRCALPHA, GX_LO_COPY);
            _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
            GXSetZCompLoc(1);
            GXSetZMode(1, GX_LEQUAL, 1);
            GXSetCullMode(GX_CULL_FRONT);
        } else {
            _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_COPY);
            _GXSetAlphaCompare(GX_ALWAYS, 0, GX_AOP_AND, GX_ALWAYS, 0xFF);
            GXSetZCompLoc(1);
            GXSetZMode(0, GX_ALWAYS, 0);
            GXSetCullMode(GX_CULL_FRONT);
        }

        GXSetNumTexGens(1);
        GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX3x4, GX_TG_NRM, GX_TEXMTX0, 0, GX_PTIDENTITY);
        GXSetNumTevStages(1);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);

        for (int i = 0; i < m_mapObjCount; i++) {
            MapMng.m_mapObjArray[i].DrawHit();
        }

        CameraPcs.SetOffsetZBuff(kMapZero);
    }

    if ((s_bitMask.m_fields.m_mode & 4) != 0) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZCompLoc(0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        _GXColor wireColor;
        wireColor.r = 0xFF;
        wireColor.g = 0xFF;
        wireColor.b = 0xFF;
        wireColor.a = 0x80;
        GXSetChanMatColor(GX_COLOR0A0, wireColor);

        CameraPcs.SetOffsetZBuff(kMapHitWireZOffset);

        CMapObj* mapObj = MapMng.GetMapObjArray();
        for (int i = 0; i < m_mapObjCount; i++) {
            mapObj->DrawHitWire();
            mapObj++;
        }

        mapObj = MapMng.GetMapObjArray();
        for (int i = 0; i < m_mapObjCount; i++) {
            mapObj->DrawHitNormal();
            mapObj++;
        }

        CameraPcs.SetOffsetZBuff(kMapZero);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void GXSetTexCoordGen(void)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80030280
 * PAL Size: 276b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::DrawAfter()
{
    if ((m_mapObjCount != 0) && (m_mapReadReady != 0)) {
        Mtx44 projection;
        PSMTX44Copy(CameraPcs.m_screenMatrix, projection);
        GXSetProjection(projection, GX_PERSPECTIVE);

        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetCullMode(GX_CULL_FRONT);
        GXSetZMode(1, GX_LEQUAL, 1);
        LightPcs.SetNumDiffuse(0);

        if (static_cast<signed char>(s_bitMask.m_fields.m_mode) == 0) {
            for (int i = 0; i < m_octTreeCount; i++) {
                m_octTreeArray[i].Draw(2);
            }

            for (int i = 0; i < m_mapObjCount; i++) {
                CMapObj* mapObj = MapMng.GetMapObj(i);
                mapObj->Draw(2);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003007c
 * PAL Size: 516b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::CheckHitCylinder(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((kMapZero == move->x) && (kMapZero == move->z) && (kMapZero == move->y)) {
        return 0;
    }

    if ((move->x <= kMapHitMoveEpsilon) && (move->x >= kMapHitMoveNegEpsilon) &&
        (move->y <= kMapHitMoveEpsilon) && (move->y >= kMapHitMoveNegEpsilon) &&
        (move->z <= kMapHitMoveEpsilon) && (move->z >= kMapHitMoveNegEpsilon)) {
        if (static_cast<unsigned int>(System.m_execParam) >= 2) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 2) {
            System.Printf(const_cast<char*>(s_check_hit_cylinder_small_vec_fmt), static_cast<double>(move->x),
                static_cast<double>(move->y), static_cast<double>(move->z));
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 2) {
            System.Printf(g_MsgFlashy);
        }
    }

    g_hit_edge_idx_min = -2;
    g_hit_t_min = kMapHitTInitial;
    PSVECAdd(&cylinder->m_bottom, move, &cylinder->m_top);

    for (int i = 0; i < m_octTreeCount; i++) {
        if (m_octTreeArray[i].CheckHitCylinder(cylinder, move, mask) != 0) {
            m_hitMapObj = m_octTreeArray[i].GetMapObject();
            return 1;
        }
    }

    for (int i = 0; i < m_mapObjCount; i++) {
        m_hitMapObj = &m_mapObjArray[i];
        if (m_hitMapObj->CheckHitCylinder(cylinder, move, mask) != 0) {
            return 1;
        }
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002fe6c
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMapMng::CheckHitCylinderNear(CMapCylinder* cylinder, Vec* move, unsigned long mask)
{
    if ((kMapZero == move->x) && (kMapZero == move->z) && (kMapZero == move->y)) {
        return 0;
    }

    if ((move->x <= kMapHitMoveEpsilon) && (move->x >= kMapHitMoveNegEpsilon) &&
        (move->y <= kMapHitMoveEpsilon) && (move->y >= kMapHitMoveNegEpsilon) &&
        (move->z <= kMapHitMoveEpsilon) && (move->z >= kMapHitMoveNegEpsilon)) {
        if (static_cast<unsigned int>(System.m_execParam) >= 2) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 2) {
            System.Printf(const_cast<char*>(s_check_hit_cylinder_near_small_vec_fmt), static_cast<double>(move->x),
                static_cast<double>(move->y), static_cast<double>(move->z));
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 2) {
            System.Printf(g_MsgFlashy);
        }
    }

    g_hit_edge_idx_min = -2;
    g_hit_t_min = kMapHitTInitial;
    int hit = 0;
    PSVECAdd(&cylinder->m_bottom, move, &cylinder->m_top);

    for (int i = 0; i < m_octTreeCount; i++) {
        gMapHitFaceFlag = 0;
        m_octTreeArray[i].CheckHitCylinderNear(cylinder, move, mask);
        if (gMapHitFaceFlag != 0) {
            hit = 1;
            m_hitMapObj = m_octTreeArray[i].GetMapObject();
        }
    }

    for (int i = 0; i < m_mapObjCount; i++) {
        gMapHitFaceFlag = 0;
        m_mapObjArray[i].CheckHitCylinderNear(cylinder, move, mask);
        if (gMapHitFaceFlag != 0) {
            hit = 1;
            m_hitMapObj = &m_mapObjArray[i];
        }
    }

    return hit;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetAnimRunMapObj(CMapObj*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetAnimRunID(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002fdb0
 * PAL Size: 188b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetViewMtx(float (*viewMtx)[4], float (*projMtx)[4])
{
    float* proj = reinterpret_cast<float*>(projMtx);

    PSMTXCopy(viewMtx, m_viewMtx);
    float scaleY = kMapViewScaleY * proj[5];
    float scaleX = proj[0];
    PSMTXScaleApply(
        m_viewMtx, m_scaledViewMtxPrimary, kMapViewScaleXPrimary * scaleX, scaleY, kMapViewScaleZ);
    PSMTXScaleApply(
        m_viewMtx, m_scaledViewMtxSecondary, kMapViewScaleXSecondary * scaleX, scaleY, kMapViewScaleZ);
}

/*
 * --INFO--
 * PAL Address: 0x8002fd9c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetIdGrpMask(int mapIdGrpIndex, unsigned long mask)
{
    GetMapIdGrpArray()[mapIdGrpIndex].m_mask = mask;
}

/*
 * --INFO--
 * PAL Address: 0x8002fcb4
 * PAL Size: 232b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetIdGrpColor(int mapIdGrpIndex, int channelIndex, _GXColor color)
{
    switch (channelIndex) {
    case 0:
    {
        u8 g = color.g;
        u8 b = color.b;
        m_mapIdGrpArray[mapIdGrpIndex].m_primaryColor.r = color.r;
        u8 a = color.a;
        m_mapIdGrpArray[mapIdGrpIndex].m_primaryColor.g = g;
        m_mapIdGrpArray[mapIdGrpIndex].m_primaryColor.b = b;
        m_mapIdGrpArray[mapIdGrpIndex].m_primaryColor.a = a;
        return;
    }
    case 1:
    {
        u8 g = color.g;
        u8 b = color.b;
        m_mapIdGrpArray[mapIdGrpIndex].m_secondaryColor.r = color.r;
        u8 a = color.a;
        m_mapIdGrpArray[mapIdGrpIndex].m_secondaryColor.g = g;
        m_mapIdGrpArray[mapIdGrpIndex].m_secondaryColor.b = b;
        m_mapIdGrpArray[mapIdGrpIndex].m_secondaryColor.a = a;
        return;
    }
    case 2:
    {
        u8 g = color.g;
        u8 b = color.b;
        m_mapIdGrpArray[mapIdGrpIndex].m_tertiaryColor.r = color.r;
        u8 a = color.a;
        m_mapIdGrpArray[mapIdGrpIndex].m_tertiaryColor.g = g;
        m_mapIdGrpArray[mapIdGrpIndex].m_tertiaryColor.b = b;
        m_mapIdGrpArray[mapIdGrpIndex].m_tertiaryColor.a = a;
        return;
    }
    case 3:
    {
        u8 g = color.g;
        u8 b = color.b;
        m_mapIdGrpArray[mapIdGrpIndex].m_quaternaryColor.r = color.r;
        u8 a = color.a;
        m_mapIdGrpArray[mapIdGrpIndex].m_quaternaryColor.g = g;
        m_mapIdGrpArray[mapIdGrpIndex].m_quaternaryColor.b = b;
        m_mapIdGrpArray[mapIdGrpIndex].m_quaternaryColor.a = a;
        return;
    }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002fb4c
 * PAL Size: 360b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMeshCameraSemiTransRange(unsigned short id, float nearRange, float farRange, float minAlpha,
                                          float maxAlpha, float fadeRange)
{
    int found = 0;

    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* mapObj = &m_mapObjArray[i];
        if (mapObj->m_meshId == id) {
            mapObj->m_cameraSemiTransNear = nearRange;
            mapObj->m_cameraSemiTransFar = farRange;
            mapObj->m_cameraSemiTransFadeRange = fadeRange;
            mapObj->m_cameraSemiTransMinAlpha = minAlpha;
            mapObj->m_cameraSemiTransMaxAlpha = maxAlpha;
            if (mapObj->m_mapData != 0 && mapObj->m_octTreeIndex != -1) {
                mapObj->m_cameraSemiTransMinAlpha = kMapCameraSemiTransMinSentinel;
                mapObj->m_cameraSemiTransMaxAlpha = kMapCameraSemiTransMaxSentinel;
                mapObj->m_drawPriority = 2;
                mapObj->m_cameraSemiTransActive = 1;
            }
            mapObj->m_cameraSemiTransTargetAlpha = 0x4000;
            found = 1;
            mapObj->m_cameraSemiTransAlpha = 0x4000;
            mapObj->m_cameraSemiTransStep = 0;
        }
    }

    if (!found) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_set_bg_transparent_missing_fmt), id);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_mapNewLine));
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002fa2c
 * PAL Size: 288b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMeshCameraSemiTransAlpha(unsigned short id, int alpha, int frameCount)
{
    int found = 0;

    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* mapObj = &m_mapObjArray[i];
        if (mapObj->m_meshId == id) {
            mapObj->m_cameraSemiTransTargetAlpha = static_cast<short>(alpha << 7);
            found = 1;
            mapObj->m_cameraSemiTransStep = static_cast<short>(
                (static_cast<int>(mapObj->m_cameraSemiTransTargetAlpha) -
                 static_cast<int>(mapObj->m_cameraSemiTransAlpha)) /
                frameCount);
        }
    }

    if (!found) {
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_set_bg_camera_semi_trans_missing_fmt), id);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) >= 1) {
            System.Printf(const_cast<char*>(s_mapNewLine));
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::GetMapObjIdx(unsigned short id)
{
    for (int i = 0; i < m_mapObjCount; i++) {
        if (m_mapObjArray[i].m_objId == id) {
            return i;
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8002f950
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterial* CMapMng::GetMaterialID(unsigned char materialId)
{
    CMaterialSet* materialSet = m_materialSet;
    unsigned long index = 0;

    while (index < static_cast<unsigned long>(materialSet->GetNumMaterial())) {
        if ((materialSet->GetMaterial(index) != 0) &&
            (materialId == materialSet->GetMaterial(index)->GetMaterialId())) {
            return materialSet->GetMaterial(index);
        }
        index++;
    }

    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CMapMng::GetMapObjEffectIdx(unsigned short effectId)
{
    for (int i = 0; i < m_mapObjCount; i++) {
        if (m_mapObjArray[i].m_effectId == effectId) {
            return i;
        }
    }

    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8002f8b4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjLMtx(int mapObjIndex, float (*source)[4])
{
    PSMTXCopy(source, m_mapObjArray[mapObjIndex].m_localMtx);

    m_mapObjArray[mapObjIndex].m_localMtxDirty = 1;
    m_mapObjArray[mapObjIndex].m_calcMtxPending = 1;
    m_mapObjArray[mapObjIndex].m_localMtxDirty = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8002f880
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::GetMapObjWMtx(int mapObjIndex, float (*destination)[4])
{
    PSMTXCopy(m_mapObjArray[mapObjIndex].m_worldMtx, destination);
}

/*
 * --INFO--
 * PAL Address: 0x8002f7a4
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void CMapMng::SetMapObjAnim(int mapObjIndex, int startFrame, int endFrame, int loop)
{
    CMapAnimRun* foundMapAnimRun;
    CMapObj* mapObj = m_mapObjArray + mapObjIndex;
    int mapAnimRunCount = m_mapAnimRunArray.GetSize();

    for (int mapAnimRunIndex = 0; mapAnimRunIndex < mapAnimRunCount; mapAnimRunIndex++) {
        CMapAnimRun* mapAnimRun = m_mapAnimRunArray[mapAnimRunIndex];
        CPtrArray<CMapAnimNode*>* mapAnimNodeArray =
            reinterpret_cast<CPtrArray<CMapAnimNode*>*>(m_mapAnimArray[mapAnimRun->m_mapAnimIndex]);
        int mapAnimNodeCount = mapAnimNodeArray->GetSize();

        for (int mapAnimNodeIndex = 0; mapAnimNodeIndex < mapAnimNodeCount; mapAnimNodeIndex++) {
            CMapAnimNode* mapAnimNode = (*mapAnimNodeArray)[mapAnimNodeIndex];
            if (mapAnimNode->m_node == reinterpret_cast<CMapAnimTargetNode*>(mapObj)) {
                foundMapAnimRun = mapAnimRun;
                goto startMapObjAnim;
            }
        }
    }

    foundMapAnimRun = 0;

startMapObjAnim:
    foundMapAnimRun->Start(startFrame, endFrame, loop);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x8002f710
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
void CMapMng::SetMapAnimID(int animId, int startFrame, int endFrame, int loop)
{
    CMapAnimRun* mapAnimRun;
    int mapAnimRunCount = m_mapAnimRunArray.GetSize();

    for (int i = 0; i < mapAnimRunCount; i++) {
        CMapAnimRun* current = m_mapAnimRunArray[i];
        if (current->m_animId == static_cast<unsigned char>(animId)) {
            mapAnimRun = current;
            goto startMapAnim;
        }
    }

    mapAnimRun = 0;

startMapAnim:
    mapAnimRun->Start(startFrame, endFrame, loop);
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x8002f6d4
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjMime(int mapObjIndex, int mode, int target, int type)
{
    CMapObj* mapObj = &m_mapObjArray[mapObjIndex];
    mapObj->SetMime(mode, target, type);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapTexAnim(int materialId, int frameStart, int frameEnd, int wrapMode)
{
    CMapTexAnimSet* mapTexAnimSet = m_mapTexAnimSet;
    mapTexAnimSet->SetMapTexAnim(materialId, frameStart, frameEnd, wrapMode);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObj(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObjID(int id, int show)
{
    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* mapObj = &m_mapObjArray[i];
        if (mapObj->m_objId == id) {
            if (show != 0) {
                mapObj->m_showFlags = static_cast<unsigned char>(mapObj->m_showFlags | 1);
            } else {
                mapObj->m_showFlags = static_cast<unsigned char>(mapObj->m_showFlags & 0xFE);
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapObjChild(int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8002f5f0
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::ShowMapObjChildID(int id, int show)
{
    for (int i = 0; i < m_mapObjCount; i++) {
        if (m_mapObjArray[i].m_objId == id) {
            m_mapObjArray[i].SetShow(show);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapMeshID(int id, int show)
{
    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* mapObj = &m_mapObjArray[i];
        if (mapObj->m_meshId == id) {
            if (show != 0) {
                mapObj->m_showFlags = static_cast<unsigned char>(mapObj->m_showFlags | 1);
            } else {
                mapObj->m_showFlags = static_cast<unsigned char>(mapObj->m_showFlags & 0xFE);
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002f45c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetDrawRangeMapObj(float drawRange)
{
    m_octTreeFrustumRange = -drawRange;
}

/*
 * --INFO--
 * PAL Address: 0x8002f46c
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetDrawRangeOctTree(float drawRange)
{
    m_octTreeDrawMinDepth = -drawRange;
}

/*
 * --INFO--
 * PAL Address: 0x8002f47c
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjWorldMapLightID(int id, _GXColor color, Vec position)
{
    int objIndex = 0;
    int numMapObj = m_mapObjCount;

    while (0 < numMapObj) {
        if (m_mapObjArray[objIndex].m_objId == static_cast<unsigned short>(id)) {
            goto found;
        }
        objIndex++;
        numMapObj--;
    }
    objIndex = -1;

found:
    const Vec spotPosition = position;
    const _GXColor spotColor = color;
    CMapObj* mapObj = m_mapObjArray + objIndex;
    CMapObjAtr* attr = mapObj->m_attribute;

    if (attr->m_type == CMapObjAtr::SPOT_LIGHT) {
        CMapObjAtrSpotLight* spotAttr = static_cast<CMapObjAtrSpotLight*>(attr);
        spotAttr->m_color = spotColor;
        mapObj->m_localRotationX = spotPosition.x;
        mapObj->m_localRotationY = spotPosition.y;
        mapObj->m_localRotationZ = spotPosition.z;
        mapObj->m_localMtxDirty = 1;
        mapObj->m_calcMtxPending = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8002f548
 * PAL Size: 28b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjTransRate(int mapObjIndex, float x, float y, float z)
{
    CMapObj& mapObj = m_mapObjArray[mapObjIndex];
    mapObj.m_transRateX = x;
    mapObj.m_transRateY = y;
    mapObj.m_transRateZ = z;
}

/*
 * --INFO--
 * PAL Address: 0x8002f564
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapObjPrioID(int id, unsigned char prio)
{
    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* mapObj = &m_mapObjArray[i];
        if (static_cast<int>(mapObj->m_objId) == id) {
            mapObj->m_drawPriority = prio;
            mapObj->m_baseDrawPriority = prio;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjWorldMapLightIdx(int, _GXColor, Vec)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetDraw(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::GetFogEnable()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80034750
 * PAL Size: 476b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapMng::~CMapMng()
{
}
