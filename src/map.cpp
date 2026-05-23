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
#include "ffcc/p_camera.h"
#include "ffcc/game.h"
#include "ffcc/gxfunc.h"
#include "ffcc/p_light.h"
#include "ffcc/p_tina.h"
#include "ffcc/file.h"
#include "ffcc/system.h"

#include <string.h>
#include <PowerPC_EABI_Support/Runtime/MWCPlusLib.h>
#include <PowerPC_EABI_Support/Runtime/NMWException.h>
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CMapMng MapMng;
char g_StrTmp[0x400];

extern "C" unsigned long UnkMaterialSetGetter(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void __dt__8COctTreeFv(void*, int);
extern "C" void __dt__7CMapHitFv(void*, int);
extern "C" void __dt__7CMapObjFv(void*, int);
extern "C" void __dt__8CMapMeshFv(void*, int);
extern "C" void __dt__7CMapMngFv(void*, int);
extern "C" void __dt__8CMapAnimFv(void*, int);
extern "C" void __dt__13CMapAnimKeyDtFv(void*, int);
extern "C" void __ct__8COctTreeFv(void*);
extern "C" void __ct__7CMapHitFv(void*);
extern "C" void __ct__7CMapObjFv(void*);
extern "C" void __ct__8CMapMeshFv(void*);
extern "C" void __ct__9CMapIdGrpFv(void*);
extern "C" void __ct__25CPtrArray_P11CMapAnimRun_Fv(void*);
extern "C" void __ct__21CPtrArray_P8CMapAnim_Fv(void*);
extern "C" void __ct__27CPtrArray_P13CMapAnimKeyDt_Fv(void*);
extern "C" void __ct__24CPtrArray_P10CMapShadow_Fv(void*);
extern "C" void __ct__29CPtrArray_P15CMapLightHolder_Fv(void*);
extern "C" void* PTR_PTR_s_CMapTexAnimSet_801e896c;
extern const float kMapViewScaleXPrimary = 0.73898232f;
extern const float kMapViewScaleY = 0.88677877f;
extern const float kMapViewScaleZ = 1.0f;
extern const float kMapViewScaleXSecondary = 0.84455127f;
extern "C" void* __vt__8CPtrArrayIP14CMapLightHolder[];
extern "C" void* __vt__8CPtrArrayIP11CMapAnimRun[];
extern "C" void* __vt__8CPtrArrayIP7CMapAnim[];
extern "C" void* __vt__8CPtrArrayIP13CMapAnimKeyDt[];
extern "C" void* __vt__8CPtrArrayIP10CMapShadow[];
unsigned char DAT_8032ec88;
extern const float FLOAT_8032f988 = 1.0e15f;
extern const float FLOAT_8032f98c = -1.0f;
extern const float FLOAT_8032f9a0 = 0.0f;

static inline CMapMngAsyncLoadState& GetMapMngAsyncLoadState(CMapMng* mapMng)
{
    return mapMng->m_asyncLoadState;
}
extern const float FLOAT_8032f9a4 = 0.0001f;
extern const float FLOAT_8032f9a8 = -0.0001f;
extern const float FLOAT_8032f9ac = 10.0f;
extern const float FLOAT_8032F9B0 = 100000.0f;
extern const float FLOAT_8032F9B4 = 360.0f;
extern const float FLOAT_8032F9B8 = 5.0e-6f;
extern const float FLOAT_8032f9bc = -0.1f;
extern char g_MsgFlashy[];
extern const char DAT_8032f984[] = "\n";
extern "C" unsigned char Vec_80245758[];
extern "C" void __ct__Q29CLightPcs6CLightFv(void*);
extern "C" CPtrArray<CMapLightHolder*>* dtor_80034414(CPtrArray<CMapLightHolder*>*, short);

static const char s_mapMidPathFmt[] = "%s.mid";
static const char s_mapOtmPathFmt[] = "%s.otm";
static const char s_map_cpp[] = "map.cpp";
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
static const char s_CMapTexAnimSet[] = "CMapTexAnimSet";
static const char s_map_ptrarray_grow_error[] =
    "\x83\x6f\x83\x62\x83\x74\x83\x40\x90\xac\x92\xb7\x82\xaa\x95\x73\x8b\x96\x89\xc2\x82\xc5\x82\xb7\x81\x42\n";
static const char s_map_collection_ptrarray_h[] = "collection_ptrarray.h";

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

struct MapObjAttachAttr
{
    void* vtable;
    int type;
    char name[1];
};

struct MapObjAttachObj
{
    char pad_00[0x0C];
    CMapHit* mapHit;
    char pad_10[0xDC];
    MapObjAttachAttr* attr;
};

static inline CMapObj* MapObjFromBytes(unsigned char* mapObj)
{
    return reinterpret_cast<CMapObj*>(mapObj);
}

static inline float MapObjWorldX(unsigned char* mapObj)
{
    return MapObjFromBytes(mapObj)->m_worldMtx[0][3];
}

static inline float MapObjWorldY(unsigned char* mapObj)
{
    return MapObjFromBytes(mapObj)->m_worldMtx[1][3];
}

static inline float MapObjWorldZ(unsigned char* mapObj)
{
    return MapObjFromBytes(mapObj)->m_worldMtx[2][3];
}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapTexAnimSet::CMapTexAnimSet()
{
	// TODO
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
    unsigned char* const p = reinterpret_cast<unsigned char*>(this);
    const short count = *reinterpret_cast<short*>(p + 8);

    *reinterpret_cast<void**>(p) = &PTR_PTR_s_CMapTexAnimSet_801e896c;

    for (int i = 0; i < count; i++) {
        int* entry = *reinterpret_cast<int**>(p + 0xC + (i * 4));
        if (entry != 0) {
            const int refCount = entry[1];
            entry[1] = refCount - 1;
            if ((refCount - 1) == 0 && entry != 0) {
                (*reinterpret_cast<void (**)(int*, int)>(*entry + 8))(entry, 1);
            }
            *reinterpret_cast<int**>(p + 0xC + (i * 4)) = 0;
        }
    }

    __dt__4CRefFv(this, 0);
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
 * Address:	TODO
 * Size:	TODO
 */
float CMapKeyFrame::Get()
{
    switch (m_mode) {
    case 1:
        return Math.Spline1D(
            static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame, m_splineTable);
    case 0:
        return Math.Line1D(static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame);
    default:
        return 0.0f;
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
extern "C" unsigned long UnkMaterialSetGetter(void* ptrArray)
{
    return *reinterpret_cast<unsigned long*>(reinterpret_cast<unsigned char*>(ptrArray) + 4);
}

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
void CPtrArray<CMaterial*>::SetDefaultSize(unsigned long defaultSize)
{
    m_defaultSize = defaultSize;
}

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
void CPtrArray<CMaterial*>::SetGrow(int growCapacity)
{
    m_growCapacity = growCapacity;
}

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

/*
 * --INFO--
 * PAL Address: 0x80034414
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapLightHolder*>* dtor_80034414(CPtrArray<CMapLightHolder*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = __vt__8CPtrArrayIP14CMapLightHolder;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            operator delete(ptrArray);
        }
    }

    return ptrArray;
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
int CPtrArray<CMapLightHolder*>::Add(CMapLightHolder* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }
    m_items[m_numItems] = item;
    m_numItems++;
    return 1;
}

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
void CPtrArray<CMapLightHolder*>::RemoveAll()
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
 * Address:	TODO
 * Size:	TODO
 */
template <>
void CPtrArray<CMapLightHolder*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

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
int CPtrArray<CMapAnim*>::Add(CMapAnim* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }
    m_items[m_numItems] = item;
    m_numItems++;
    return 1;
}

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
int CPtrArray<CMapAnim*>::GetSize()
{
    return m_numItems;
}

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
void CPtrArray<CMapAnim*>::RemoveAll()
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
 * PAL Address: 0x80034018
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnim* CPtrArray<CMapAnim*>::operator[](unsigned long index)
{
    return GetAt(index);
}

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
int CPtrArray<CMapAnimKeyDt*>::GetSize()
{
    return m_numItems;
}

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
CMapAnimKeyDt* CPtrArray<CMapAnimKeyDt*>::operator[](unsigned long index)
{
    return GetAt(index);
}

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
template <>
void CPtrArray<CMapAnimKeyDt*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

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
void CPtrArray<CMapAnimKeyDt*>::RemoveAll()
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
 * PAL Address: 0x80034038
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnim*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

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
CPtrArray<CMapAnimRun*>::CPtrArray()
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
 * PAL Address: 0x800344c4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapAnimRun*>* dtor_800344C4(CPtrArray<CMapAnimRun*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = __vt__8CPtrArrayIP11CMapAnimRun;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            operator delete(ptrArray);
        }
    }

    return ptrArray;
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
CPtrArray<CMapAnim*>::CPtrArray()
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
 * PAL Address: 0x80034574
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapAnim*>* dtor_80034574(CPtrArray<CMapAnim*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = __vt__8CPtrArrayIP7CMapAnim;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            operator delete(ptrArray);
        }
    }

    return ptrArray;
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
CPtrArray<CMapAnimKeyDt*>::CPtrArray()
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
 * PAL Address: 0x80034624
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapAnimKeyDt*>* dtor_80034624(CPtrArray<CMapAnimKeyDt*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = __vt__8CPtrArrayIP13CMapAnimKeyDt;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            operator delete(ptrArray);
        }
    }

    return ptrArray;
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
CPtrArray<CMapShadow*>::CPtrArray()
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
 * PAL Address: 0x800346d4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMapShadow*>* dtor_800346D4(CPtrArray<CMapShadow*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        *reinterpret_cast<void***>(Ptr(ptrArray, 0)) = __vt__8CPtrArrayIP10CMapShadow;

        void*& items = *reinterpret_cast<void**>(Ptr(ptrArray, 0x10));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            items = 0;
        }

        *reinterpret_cast<int*>(Ptr(ptrArray, 8)) = 0;
        *reinterpret_cast<int*>(Ptr(ptrArray, 4)) = 0;

        if (0 < param_2) {
            operator delete(ptrArray);
        }
    }

    return ptrArray;
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
int CPtrArray<CMapAnimRun*>::GetSize()
{
    return m_numItems;
}

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
void CPtrArray<CMapAnimRun*>::RemoveAll()
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
 * PAL Address: 0x8003413c
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapAnimRun* CPtrArray<CMapAnimRun*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034170
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapAnimRun*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

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
int CPtrArray<CMapShadow*>::GetSize()
{
    return m_numItems;
}

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
void CPtrArray<CMapShadow*>::RemoveAll()
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
 * PAL Address: 0x80034228
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMapShadow* CPtrArray<CMapShadow*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x80034248
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CMapShadow*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

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
 * Address:	TODO
 * Size:	TODO
 */
int CMapKeyFrame::Get(int& key0, int& key1, float& blend)
{
    switch (m_mode) {
    case 1:
        blend = Math.Spline1D(
            static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame, m_splineTable);
        break;
    case 0:
        blend = Math.Line1D(
            static_cast<int>(m_keyCount) - 1, static_cast<float>(m_currentFrame), m_keyValue, m_keyFrame);
        break;
    default:
        blend = 0.0f;
        key0 = m_junTable[0];
        key1 = key0;
        return 0;
    }

    if (blend <= 0.0f) {
        key0 = m_junTable[0];
        key1 = key0;
        blend = 0.0f;
        return 0;
    }

    const float junMax = static_cast<float>(m_junCount - 1);
    if (blend >= junMax) {
        key0 = m_junTable[m_junCount - 1];
        key1 = key0;
        blend = 1.0f;
        return 0;
    }

    key0 = static_cast<int>(blend);
    key1 = static_cast<int>(1.0f + blend);
    blend = blend - static_cast<float>(key0);
    key0 = m_junTable[key0];
    if (blend == 0.0f) {
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
    m_unknown10 = 0;
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

    GetMapAnimRunArray().SetStage(stage);
    GetMapAnimArray().SetStage(stage);
    GetMapAnimKeyDtArray().SetStage(stage);
    GetMapShadowArray().SetStage(stage);

    for (int i = 0; i < 2; i++) {
        GetMapLightHolderArray(i).SetStage(stage);
    }

    gMapHitFaceFlag = 0;
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);

    short octTreeCount = m_octTreeCount;
    for (int i = 0; i < octTreeCount; i++) {
        __dt__8COctTreeFv(self + 0x14 + (i * 0x4C), 0xFFFF);
    }
    m_octTreeCount = 0;

    short mapHitCount = m_mapHitCount;
    for (int i = 0; i < mapHitCount; i++) {
        __dt__7CMapHitFv(self + 0x4D4 + (i * 0x24), 0xFFFF);
    }
    m_mapHitCount = 0;

    short mapObjCount = m_mapObjCount;
    for (int i = 0; i < mapObjCount; i++) {
        __dt__7CMapObjFv(self + 0x954 + (i * 0xF0), -1);
    }
    m_mapObjCount = 0;

    short mapMeshCount = m_mapMeshCount;
    for (int i = 0; i < mapMeshCount; i++) {
        __dt__8CMapMeshFv(self + 0x1E954 + (i * 0x44), 0xFFFF);
    }
    m_mapMeshCount = 0;

    int* materialSet = reinterpret_cast<int*>(m_materialSet);
    if (materialSet != 0) {
        (*reinterpret_cast<void (**)(int*, int)>(*materialSet + 8))(materialSet, 1);
        m_materialSet = 0;
    }

    int* textureSet = reinterpret_cast<int*>(m_textureSet);
    if (textureSet != 0) {
        (*reinterpret_cast<void (**)(int*, int)>(*textureSet + 8))(textureSet, 1);
        m_textureSet = 0;
    }

    int* mapTexAnimSet = reinterpret_cast<int*>(m_mapTexAnimSet);
    if (mapTexAnimSet != 0) {
        (*reinterpret_cast<void (**)(int*, int)>(*mapTexAnimSet + 8))(mapTexAnimSet, 1);
        m_mapTexAnimSet = 0;
    }

    CPtrArray<CMapAnim*>* mapAnimArray = &GetMapAnimArray();
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapAnimArray->GetSize()); i++) {
        CMapAnim* mapAnim = (*mapAnimArray)[i];
        if (mapAnim != 0) {
            __dt__8CMapAnimFv(mapAnim, 1);
        }
    }
    mapAnimArray->RemoveAll();

    CPtrArray<CMapAnimKeyDt*>* mapAnimKeyDtArray = &GetMapAnimKeyDtArray();
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapAnimKeyDtArray->GetSize()); i++) {
        CMapAnimKeyDt* mapAnimKeyDt = (*mapAnimKeyDtArray)[i];
        if (mapAnimKeyDt != 0) {
            __dt__13CMapAnimKeyDtFv(mapAnimKeyDt, 1);
        }
    }
    mapAnimKeyDtArray->RemoveAll();

    CPtrArray<CMapAnimRun*>* mapAnimRunArray = &GetMapAnimRunArray();
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapAnimRunArray->GetSize()); i++) {
        CMapAnimRun* mapAnimRun = (*mapAnimRunArray)[i];
        if (mapAnimRun != 0) {
            operator delete(mapAnimRun);
        }
    }
    mapAnimRunArray->RemoveAll();

    CPtrArray<CMapShadow*>* mapShadowArray = &GetMapShadowArray();
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* mapShadow = (*mapShadowArray)[i];
        if (mapShadow != 0) {
            operator delete(mapShadow);
        }
    }
    mapShadowArray->RemoveAll();

    for (int i = 0; i < 2; i++) {
        CPtrArray<CMapLightHolder*>* mapLightHolderArray = &GetMapLightHolderArray(i);

        for (unsigned int j = 0; j < static_cast<unsigned int>(mapLightHolderArray->GetSize()); j++) {
            CMapLightHolder* holder = (*mapLightHolderArray)[j];
            if (holder != 0) {
                operator delete(holder);
            }
        }
        mapLightHolderArray->RemoveAll();
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
        void** handleSlot = &m_asyncLoadState.m_asyncHandles[i];
        CFile::CHandle* handle = reinterpret_cast<CFile::CHandle*>(*handleSlot);
        if (handle != 0 && File.IsCompleted(handle)) {
            int len = File.GetLength(handle);
            void* readBuffer = File.m_readBuffer;
            void* amemCursor = m_asyncLoadState.m_mapLoadCursor;

            Memory.CopyToAMemorySync(readBuffer, amemCursor, (len + 0x1F) & ~0x1F);
            m_asyncLoadState.m_fileSizes[i] = len;
            m_asyncLoadState.m_fileChecksums[i] = CheckSum(readBuffer, len);
            m_asyncLoadState.m_asyncReadIndex++;
            m_asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(m_asyncLoadState.m_mapLoadCursor) + len;

            File.Close(handle);
            *handleSlot = 0;
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
    CMapObj* mapObjEnd =
        reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + 0x954 + objCount * 0xF0);

    for (CMapObj* obj = searchStart; obj < mapObjEnd; obj = reinterpret_cast<CMapObj*>(Ptr(obj, 0xF0))) {
        if (*reinterpret_cast<CMapObj**>(Ptr(obj, 0x0)) == parentObj) {
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
    MapObjAttachObj* mapObj = reinterpret_cast<MapObjAttachObj*>(GetMapObjArray());

    goto search;
    while (true) {
        if (strcmp(mapHitName, mapObj->attr->name) == 0) {
            mapObj->mapHit = mapHit;

            MapObjAttachAttr* mapObjAtr = mapObj->attr;
            if (mapObjAtr != 0) {
                if (mapObjAtr != 0) {
                    typedef void (*MapObjAtrDtor)(MapObjAttachAttr*, int);
                    reinterpret_cast<MapObjAtrDtor*>(*reinterpret_cast<void***>(mapObjAtr))[2](mapObjAtr, 1);
                }
                mapObj->attr = 0;
            }
        }

        mapObj++;

search:
        unsigned int stride = 0xF0;
        MapObjAttachObj* mapObjEnd = reinterpret_cast<MapObjAttachObj*>(GetMapObjArray()) + m_mapObjCount;
        unsigned int remaining =
            (reinterpret_cast<unsigned int>(mapObjEnd) + (stride - 1) - reinterpret_cast<unsigned int>(mapObj)) /
            stride;

        if (mapObj < mapObjEnd) {
            do {
                if (mapObj->attr != 0 && mapObj->attr->type == CMapObjAtr::MESH_NAME) {
                    goto found;
                }
                mapObj++;
                remaining--;
            } while (remaining != 0);
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
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(GetMapObjArray());

    goto search;
    while (true) {
        unsigned char* mapObjAtr = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);
        if (*(mapObjAtr + 8) == playStaNo) {
            vec->x = MapObjWorldX(mapObj);
            vec->y = MapObjWorldY(mapObj);
            vec->z = MapObjWorldZ(mapObj);
            return 1;
        }
        mapObj += 0xF0;

search:
        unsigned int stride = sizeof(CMapObj);
        unsigned char* mapObjEnd = reinterpret_cast<unsigned char*>(GetMapObjArray() + m_mapObjCount);
        unsigned int remaining =
            (reinterpret_cast<unsigned int>(mapObjEnd) + (stride - 1) - reinterpret_cast<unsigned int>(mapObj)) /
            stride;

        if (mapObj < mapObjEnd) {
            do {
                unsigned char* mapObjAtr = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);
                if (mapObjAtr != 0 && *reinterpret_cast<int*>(mapObjAtr + 4) == CMapObjAtr::PLAY_STA) {
                    goto found;
                }
                mapObj += 0xF0;
                remaining--;
            } while (remaining != 0);
        }

        mapObj = 0;
found:
        if (mapObj == 0) {
            vec->z = FLOAT_8032f9a0;
            vec->y = FLOAT_8032f9a0;
            vec->x = FLOAT_8032f9a0;
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
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(GetMapObjArray());
    unsigned char* mapObjEnd = reinterpret_cast<unsigned char*>(GetMapObjArray() + mapObjCount);

    while (mapObj < mapObjEnd) {
        unsigned char* atr = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);
        if (atr != 0) {
            const int type = *reinterpret_cast<int*>(atr + 4);

            if (type == CMapObjAtr::SPOT_LIGHT) {
                if (*reinterpret_cast<int*>(atr + 0x34) == 0) {
                    CLightPcs::CLight light;
                    light.m_type = 1;
                    light.m_position.x = MapObjWorldX(mapObj);
                    light.m_position.y = MapObjWorldY(mapObj);
                    light.m_position.z = MapObjWorldZ(mapObj);

                    light.m_direction.x = 0.0f;
                    light.m_direction.y = 0.0f;
                    light.m_direction.z = 1.0f;

                    unsigned char* targetObj = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(atr + 0x10));
                    light.m_targetPosition.x = MapObjWorldX(targetObj);
                    light.m_targetPosition.y = MapObjWorldY(targetObj);
                    light.m_targetPosition.z = MapObjWorldZ(targetObj);

                    PSVECSubtract(reinterpret_cast<Vec*>(&light.m_targetPosition),
                                  reinterpret_cast<Vec*>(&light.m_position),
                                  reinterpret_cast<Vec*>(&light.m_direction));
                    PSVECNormalize(reinterpret_cast<Vec*>(&light.m_direction), reinterpret_cast<Vec*>(&light.m_direction));

                    light.m_attenRadius = *reinterpret_cast<float*>(atr + 0x14);
                    light.m_range = *reinterpret_cast<float*>(atr + 0x18);
                    light.m_attenFalloff = *reinterpret_cast<float*>(atr + 0x1C);

                    light.m_targetColor[0].r = atr[0x8];
                    light.m_targetColor[0].g = atr[0x9];
                    light.m_targetColor[0].b = atr[0xA];
                    light.m_targetColor[0].a = atr[0xB];
                    light.m_targetColor[1].r = atr[0xC];
                    light.m_targetColor[1].g = atr[0xD];
                    light.m_targetColor[1].b = atr[0xE];
                    light.m_targetColor[1].a = atr[0xF];

                    light.m_spotFn = atr[0x2C];
                    light.m_unk4D = (atr[0x2D] == 0) ? 4 : 2;
                    light.m_directionMode = atr[0x30];
                    light.m_partMask = 1 << mapLightIndex;
                    *(u32*)light.m_targetEnable = 0;
                    LightPcs.Add(&light);
                } else {
                    CLightPcs::CLight* light = *reinterpret_cast<CLightPcs::CLight**>(atr + 0x38);
                    light->m_type = 1;
                    light->m_targetColor[1].r = atr[0x8];
                    light->m_targetColor[1].g = atr[0x9];
                    light->m_targetColor[1].b = atr[0xA];
                    light->m_targetColor[1].a = atr[0xB];
                    light->m_position.x = MapObjWorldX(mapObj);
                    light->m_position.y = MapObjWorldY(mapObj);
                    light->m_position.z = MapObjWorldZ(mapObj);
                    light->m_direction.x = 0.0f;
                    light->m_direction.y = 0.0f;
                    light->m_direction.z = 1.0f;

                    unsigned char* targetObj = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(atr + 0x10));
                    light->m_targetPosition.x = MapObjWorldX(targetObj);
                    light->m_targetPosition.y = MapObjWorldY(targetObj);
                    light->m_targetPosition.z = MapObjWorldZ(targetObj);
                    PSVECSubtract(reinterpret_cast<Vec*>(&light->m_targetPosition),
                                  reinterpret_cast<Vec*>(&light->m_position),
                                  reinterpret_cast<Vec*>(&light->m_direction));
                    PSVECNormalize(reinterpret_cast<Vec*>(&light->m_direction), reinterpret_cast<Vec*>(&light->m_direction));
                }
                mapLightIndex += 1;
            } else if (type == CMapObjAtr::POINT_LIGHT) {
                CLightPcs::CLight light;
                light.m_type = 0;
                light.m_position.x = MapObjWorldX(mapObj);
                light.m_position.y = MapObjWorldY(mapObj);
                light.m_position.z = MapObjWorldZ(mapObj);
                light.m_direction.x = 0.0f;
                light.m_direction.y = 0.0f;
                light.m_direction.z = 1.0f;
                light.m_partMask = 1 << mapLightIndex;
                light.m_attenRadius = *reinterpret_cast<float*>(atr + 0x10);
                light.m_range = *reinterpret_cast<float*>(atr + 0x14);
                light.m_attenFalloff = 1.0f;
                light.m_targetColor[0].r = atr[0x8];
                light.m_targetColor[0].g = atr[0x9];
                light.m_targetColor[0].b = atr[0xA];
                light.m_targetColor[0].a = atr[0xB];
                light.m_targetColor[1].r = atr[0xC];
                light.m_targetColor[1].g = atr[0xD];
                light.m_targetColor[1].b = atr[0xE];
                light.m_targetColor[1].a = atr[0xF];
                *(u32*)light.m_targetEnable = 0;
                light.m_spotFn = atr[0x1C];
                light.m_unk4D = 4;
                light.m_directionMode = atr[0x20];
                LightPcs.Add(&light);
                mapLightIndex += 1;
            }
        }

        mapObj += 0xF0;
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
void CMapMng::ReadMtx(char* mapName)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CMapMngAsyncLoadState& asyncLoadState = GetMapMngAsyncLoadState(this);
    int loadIndex = 0;
    int append = 0;

    m_mapReadReady = 1;

    if (asyncLoadState.m_mapReadMode != 2 && asyncLoadState.m_mapReadMode != 3) {
        CMemory::CStage* stage = m_stage;
        CTextureSet* textureSet = new (stage, const_cast<char*>(s_map_cpp), 0x3A9) CTextureSet;
        m_textureSet = textureSet;
    }

    while (true) {
        sprintf(g_StrTmp, const_cast<char*>(s_mapMtxPathFmt), mapName, loadIndex);

        bool exists = false;
        if (asyncLoadState.m_mapReadMode == 1) {
            exists = true;
        } else {
            CFile::CHandle* openProbe = File.Open(g_StrTmp, 0, CFile::PRI_LOW);
            if (openProbe != 0) {
                File.Close(openProbe);
                exists = true;
            }
        }
        if (!exists) {
            break;
        }

        void* filePtr = File.m_readBuffer;
        if (asyncLoadState.m_mapReadMode == 1) {
            int& readIndex = asyncLoadState.m_asyncReadIndex;
            int size = asyncLoadState.m_fileSizes[readIndex];
            void* amemCursor = asyncLoadState.m_mapLoadCursor;
            Memory.CopyFromAMemorySync(File.m_readBuffer, amemCursor, static_cast<unsigned long>((size + 0x1F) & ~0x1F));
            asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
            CheckSum(filePtr, size);
            readIndex += 1;
        } else {
            CFile::CHandle* handle = File.Open(g_StrTmp, 0, CFile::PRI_LOW);
            if (handle == 0) {
                filePtr = 0;
            } else {
                int size = File.GetLength(handle);
                if (asyncLoadState.m_mapReadMode == 3) {
                    File.ReadASync(handle);
                    filePtr = reinterpret_cast<void*>(1);
                    int& openIndex = asyncLoadState.m_asyncOpenIndex;
                    asyncLoadState.m_asyncHandles[openIndex] = handle;
                    openIndex += 1;
                } else {
                    File.Read(handle);
                    File.SyncCompleted(handle);
                    filePtr = File.m_readBuffer;
                    File.Close(handle);
                    if (asyncLoadState.m_mapReadMode == 2) {
                        int& readIndex = asyncLoadState.m_asyncReadIndex;
                        void* amemCursor = asyncLoadState.m_mapLoadCursor;
                        Memory.CopyToAMemorySync(filePtr, amemCursor, static_cast<unsigned long>(size));
                        asyncLoadState.m_fileSizes[readIndex] = size;
                        asyncLoadState.m_fileChecksums[readIndex] = CheckSum(filePtr, size);
                        readIndex += 1;
                        asyncLoadState.m_mapLoadCursor =
                            reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
                    }
                }
            }
        }

        if (filePtr == 0) {
            return;
        }

        if (asyncLoadState.m_mapReadMode != 3) {
            CChunkFile chunkFile;
            chunkFile.SetBuf(filePtr);
            CChunkFile::CChunk chunk;

            if (asyncLoadState.m_mapReadMode == 2) {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x54534554 && chunk.m_arg0 == 1) {
                        return;
                    }
                }
            } else {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x54534554) {
                        m_textureSet->Create(chunkFile, m_stage, append, 0, 0, 0);
                        append = 1;
                        if (chunk.m_arg0 == 1) {
                            return;
                        }
                    }
                }
            }
        }

        loadIndex += 1;
    }
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
void CMapMng::ReadMpl(char* mapName)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CMapMngAsyncLoadState& asyncLoadState = GetMapMngAsyncLoadState(this);
    int loadIndex = 0;

    m_mapReadReady = 1;

    while (true) {
        sprintf(g_StrTmp, const_cast<char*>(s_mapMplPathFmt), mapName, loadIndex);

        bool canRead = false;
        const int readMode = asyncLoadState.m_mapReadMode;
        if (readMode == 1) {
            canRead = true;
        } else {
            CFile::CHandle* existsHandle = File.Open(g_StrTmp, 0, CFile::PRI_LOW);
            if (existsHandle != 0) {
                File.Close(existsHandle);
                canRead = true;
            }
        }

        if (!canRead) {
            if (readMode == 3) {
                return;
            }
            if (loadIndex == 0) {
                if (System.m_execParam != 0) {
                    System.Printf(const_cast<char*>(s_mapReadOpenErrorFmt), g_StrTmp);
                }
                return;
            }
            return;
        }

        if (static_cast<unsigned int>(System.m_execParam) > 2) {
            System.Printf(const_cast<char*>(s_mapReadMplFmt), g_StrTmp);
        }

        void* filePtr = File.m_readBuffer;
        if (readMode == 1) {
            int& readIndex = asyncLoadState.m_asyncReadIndex;
            const int size = asyncLoadState.m_fileSizes[readIndex];
            void* amemCursor = asyncLoadState.m_mapLoadCursor;

            Memory.CopyFromAMemorySync(File.m_readBuffer, amemCursor, (size + 0x1F) & ~0x1F);
            asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
            CheckSum(filePtr, size);
            readIndex += 1;
        } else {
            CFile::CHandle* fileHandle = File.Open(g_StrTmp, 0, CFile::PRI_LOW);
            if (fileHandle == 0) {
                filePtr = 0;
            } else {
                const int size = File.GetLength(fileHandle);
                if (readMode == 3) {
                    File.ReadASync(fileHandle);
                    filePtr = reinterpret_cast<void*>(1);
                    int& openIndex = asyncLoadState.m_asyncOpenIndex;
                    asyncLoadState.m_asyncHandles[openIndex] = fileHandle;
                    openIndex += 1;
                } else {
                    File.Read(fileHandle);
                    File.SyncCompleted(fileHandle);
                    filePtr = File.m_readBuffer;
                    File.Close(fileHandle);
                    if (readMode == 2) {
                        int& readIndex = asyncLoadState.m_asyncReadIndex;
                        void* amemCursor = asyncLoadState.m_mapLoadCursor;
                        Memory.CopyToAMemorySync(filePtr, amemCursor, static_cast<unsigned long>(size));
                        asyncLoadState.m_fileSizes[readIndex] = size;
                        asyncLoadState.m_fileChecksums[readIndex] = CheckSum(filePtr, size);
                        readIndex += 1;
                        asyncLoadState.m_mapLoadCursor =
                            reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
                    }
                }
            }
        }

        if (filePtr == 0) {
            if (System.m_execParam != 0) {
                System.Printf(const_cast<char*>(s_mapReadErrorFmt), g_StrTmp);
            }
            return;
        }

        if (readMode != 3) {
            CChunkFile chunkFile;
            chunkFile.SetBuf(filePtr);
            CChunkFile::CChunk chunk;

            if (readMode == 2) {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x4D455348 && chunk.m_arg0 == 1) {
                        return;
                    }
                }
            } else {
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id != 0x4D455348) {
                        continue;
                    }

                    chunkFile.PushChunk();
                    CChunkFile::CChunk meshChunk;
                    while (chunkFile.GetNextChunk(meshChunk)) {
                        if (meshChunk.m_id == 0x56534554) {
                            short& meshCount = m_mapMeshCount;
                            if (meshCount > 0x9F) {
                                return;
                            }
                            CMapMesh* mesh = reinterpret_cast<CMapMesh*>(self + 0x16AC + (meshCount * 0x44));
                            mesh->ReadOtmMesh(chunkFile, m_stage, 1, 1);
                        } else if (meshChunk.m_id == 0x44534554) {
                            short& meshCount = m_mapMeshCount;
                            CMapMesh* mesh = reinterpret_cast<CMapMesh*>(self + 0x16AC + (meshCount * 0x44));
                            mesh->ReadOtmMesh(chunkFile, m_stage, 1, 1);
                            meshCount += 1;
                        }
                    }
                    chunkFile.PopChunk();

                    if (chunk.m_arg0 == 1) {
                        return;
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
void CMapMng::ReadOtm(char* mapName)
{
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CMapMngAsyncLoadState& asyncLoadState = GetMapMngAsyncLoadState(this);
    CFile::CHandle* fileHandle = 0;
    void* filePtr = File.m_readBuffer;

    m_mapReadReady = 1;
    sprintf(g_StrTmp, const_cast<char*>(s_mapOtmPathFmt), mapName);
    m_mapAnimFrame = 0;

    const int readMode = asyncLoadState.m_mapReadMode;
    if (readMode == 1) {
        int& readIndex = asyncLoadState.m_asyncReadIndex;
        const int size = asyncLoadState.m_fileSizes[readIndex];
        void* amemCursor = asyncLoadState.m_mapLoadCursor;

        Memory.CopyFromAMemorySync(File.m_readBuffer, amemCursor, (size + 0x1F) & ~0x1F);
        asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
        CheckSum(File.m_readBuffer, size);
        readIndex += 1;
    } else {
        fileHandle = File.Open(g_StrTmp, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            const int size = File.GetLength(fileHandle);
            if (readMode == 3) {
                File.ReadASync(fileHandle);
                filePtr = reinterpret_cast<void*>(1);
                int& openIndex = asyncLoadState.m_asyncOpenIndex;
                asyncLoadState.m_asyncHandles[openIndex] = fileHandle;
                openIndex += 1;
            } else {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                filePtr = File.m_readBuffer;
                File.Close(fileHandle);

                if (readMode == 2) {
                    int& readIndex = asyncLoadState.m_asyncReadIndex;
                    void* amemCursor = asyncLoadState.m_mapLoadCursor;
                    Memory.CopyToAMemorySync(filePtr, amemCursor, static_cast<unsigned long>(size));
                    asyncLoadState.m_fileSizes[readIndex] = size;
                    asyncLoadState.m_fileChecksums[readIndex] = CheckSum(filePtr, size);
                    readIndex += 1;
                    asyncLoadState.m_mapLoadCursor =
                        reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
                }
            }
        } else {
            filePtr = 0;
        }
    }

    if (filePtr == 0) {
        return;
    }

    if (readMode == 2 || readMode == 3) {
        return;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(filePtr);

    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id != 0x4F544D20) {
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk)) {
            if (chunk.m_id == 0x4F43544D) {
                short& octTreeCount = m_octTreeCount;
                if (octTreeCount > 0xF) {
                    return;
                }

                COctTree* octTree = reinterpret_cast<COctTree*>(self + 0x14 + (octTreeCount * 0x4C));
                octTree->ReadOtmOctTree(chunkFile);
                octTreeCount += 1;
                continue;
            }

            if (chunk.m_id == 0x4C495448) {
                CMapLightHolder* light = reinterpret_cast<CMapLightHolder*>(
                    Memory._Alloc(0x10, m_stage, const_cast<char*>(s_map_cpp), 0x4D3, 0));
                if (light != 0) {
                    unsigned char* lightRaw = reinterpret_cast<unsigned char*>(light);
                    lightRaw[0] = chunkFile.Get1();
                    lightRaw[1] = chunkFile.Get1();
                    lightRaw[2] = chunkFile.Get1();
                    lightRaw[3] = chunkFile.Get1();
                    *reinterpret_cast<float*>(lightRaw + 4) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(lightRaw + 8) = chunkFile.GetF4();
                    *reinterpret_cast<float*>(lightRaw + 0xC) = chunkFile.GetF4();

                    CPtrArray<CMapLightHolder*>* holderArray = &GetMapLightHolderArray(chunk.m_arg0);
                    holderArray->Add(light);
                }
                continue;
            }

            if (chunk.m_id != 0x5343454E) {
                continue;
            }

            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 0x4D455348) {
                    short& meshCount = m_mapMeshCount;
                    if (meshCount > 0x9F) {
                        return;
                    }
                    CMapMesh* mesh = reinterpret_cast<CMapMesh*>(self + 0x16AC + (meshCount * 0x44));
                    mesh->ReadOtmMesh(chunkFile, m_stage, 0, 1);
                    meshCount += 1;
                    continue;
                }

                if (chunk.m_id == 0x41534554) {
                    CMapTexAnimSet* texAnimSet =
                        new (m_stage, const_cast<char*>(s_map_cpp), 0x49A) CMapTexAnimSet();
                    m_mapTexAnimSet = texAnimSet;
                    if (texAnimSet != 0) {
                        texAnimSet->Create(chunkFile, m_materialSet, m_textureSet);
                    }
                    continue;
                }

                if (chunk.m_id == 0x414E494D) {
                    CMapAnim* mapAnim = new (m_stage, const_cast<char*>(s_map_cpp), 0x4BF) CMapAnim();
                    if (mapAnim != 0) {
                        mapAnim->ReadOtmAnim(chunkFile);
                        GetMapAnimArray().Add(mapAnim);
                    }
                    continue;
                }

                if (chunk.m_id == 0x48495420) {
                    short& hitCount = m_mapHitCount;
                    if (hitCount > 0x1F) {
                        return;
                    }
                    CMapHit* hit = reinterpret_cast<CMapHit*>(self + 0x4D4 + (hitCount * 0x24));
                    hit->ReadOtmHit(chunkFile);
                    hitCount += 1;
                    continue;
                }

                if (chunk.m_id == 0x4E4F4445) {
                    short& mapObjCount = m_mapObjCount;
                    if (mapObjCount > 0x1FF) {
                        return;
                    }
                    CMapObj* mapObj = reinterpret_cast<CMapObj*>(self + 0x954 + (mapObjCount * 0xF0));
                    mapObj->ReadOtmObj(chunkFile);
                    mapObjCount += 1;
                    continue;
                }

                if (chunk.m_id == 0x4D534554) {
                    CMaterialSet* materialSet =
                        new (m_stage, const_cast<char*>(s_map_cpp), 0x482) CMaterialSet();
                    m_materialSet = materialSet;
                    if (materialSet != 0) {
                        reinterpret_cast<CPtrArray<CMaterial*>*>(reinterpret_cast<unsigned char*>(materialSet) + 8)
                            ->SetDefaultSize(0x180);
                        reinterpret_cast<CPtrArray<CMaterial*>*>(reinterpret_cast<unsigned char*>(materialSet) + 8)
                            ->SetGrow(0);
                        materialSet->Create(chunkFile, m_textureSet, static_cast<CMaterialMan::TEV_BIT>(0xFFF53060), 0);
                    }
                }
            }
            chunkFile.PopChunk();
        }
        chunkFile.PopChunk();
    }

    const short octTreeCount = m_octTreeCount;
    for (int i = 0; i < octTreeCount; i++) {
        unsigned char* octTreeRaw = self + 0x14 + (i * 0x4C);
        if (*reinterpret_cast<void**>(octTreeRaw + 8) != 0) {
            *reinterpret_cast<char*>(octTreeRaw + 0x1F) = static_cast<char>(i);
        }
    }

    CPtrArray<CMapShadow*>* mapShadowArray = &GetMapShadowArray();
    for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* mapShadow = (*mapShadowArray)[i];
        mapShadow->Init();
    }

    CMapObj* mapObj = reinterpret_cast<CMapObj*>(self + 0x954);
    CMapObj* mapObjEnd = reinterpret_cast<CMapObj*>(self + 0x954 + (m_mapObjCount * 0xF0));
    CMapObj* root = 0;
    while (mapObj < mapObjEnd) {
        if (*reinterpret_cast<CMapObj**>(mapObj) != 0) {
            root = mapObj;
            break;
        }
        mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(mapObj) + 0xF0);
    }

    m_rootMapObj = root;
    if (root == 0) {
        return;
    }

    root->SetLink();

    Mtx identity;
    PSMTXIdentity(identity);
    root->CalcMtx(identity, 1);

    const int mapObjCount = m_mapObjCount;
    for (int i = 0; i < mapObjCount; i++) {
        unsigned char* obj = self + 0x954 + (i * 0xF0);
        unsigned char* atr = *reinterpret_cast<unsigned char**>(obj + 0xEC);
        if (atr == 0) {
            continue;
        }
        if (*reinterpret_cast<int*>(atr + 4) != CMapObjAtr::SPOT_LIGHT || *reinterpret_cast<int*>(atr + 0x34) == 0) {
            continue;
        }

        unsigned char lightRaw[0xB0];
        __ct__Q29CLightPcs6CLightFv(lightRaw);
        *reinterpret_cast<int*>(lightRaw + 0x8) = 1;
        *reinterpret_cast<float*>(lightRaw + 0xC) = MapObjWorldX(obj);
        *reinterpret_cast<float*>(lightRaw + 0x10) = MapObjWorldY(obj);
        *reinterpret_cast<float*>(lightRaw + 0x14) = MapObjWorldZ(obj);

        unsigned char* targetObj = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(atr + 0x10));
        Vec source;
        source.x = MapObjWorldX(targetObj);
        source.y = MapObjWorldY(targetObj);
        source.z = MapObjWorldZ(targetObj);
        Vec target;
        target.x = MapObjWorldX(obj);
        target.y = MapObjWorldY(obj);
        target.z = MapObjWorldZ(obj);
        Vec dir;
        PSVECSubtract(&source, &target, &dir);
        PSVECNormalize(&dir, &dir);

        *reinterpret_cast<float*>(lightRaw + 0x40) = dir.x;
        *reinterpret_cast<float*>(lightRaw + 0x44) = dir.y;
        *reinterpret_cast<float*>(lightRaw + 0x48) = dir.z;
        *reinterpret_cast<unsigned int*>(lightRaw + 0x4C) = *reinterpret_cast<unsigned int*>(atr + 0x34);
        *reinterpret_cast<unsigned int*>(lightRaw + 0x20) = *reinterpret_cast<unsigned int*>(atr + 0x20);
        *reinterpret_cast<unsigned int*>(lightRaw + 0x24) = *reinterpret_cast<unsigned int*>(atr + 0x24);
        *reinterpret_cast<unsigned int*>(lightRaw + 0x28) = *reinterpret_cast<unsigned int*>(atr + 0x28);
        lightRaw[0x58] = atr[8];
        lightRaw[0x59] = atr[9];
        lightRaw[0x5A] = atr[10];
        lightRaw[0x5B] = atr[11];

        CLightPcs::CBumpLight* bump = LightPcs.AddBump(
            reinterpret_cast<CLightPcs::CLight*>(lightRaw),
            static_cast<CLightPcs::TARGET>(1),
            m_stage,
            1);
        *reinterpret_cast<CLightPcs::CBumpLight**>(atr + 0x38) = bump;

        for (int j = 0; j < mapObjCount; j++) {
            unsigned char* scan = self + 0x954 + (j * 0xF0);
            if (*reinterpret_cast<short*>(scan + 0x16) == i) {
                *reinterpret_cast<CLightPcs::CBumpLight**>(scan + 0x10) = bump;
            }
        }

    }
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    CMapMngAsyncLoadState& asyncLoadState = GetMapMngAsyncLoadState(this);
    void* filePtr = File.m_readBuffer;

    sprintf(g_StrTmp, const_cast<char*>(s_mapMidPathFmt), mapName);
    bool ok = true;

    if (static_cast<unsigned int>(System.m_execParam) > 2) {
        System.Printf(const_cast<char*>(s_read_mid_fmt), g_StrTmp);
    }

    const int readMode = asyncLoadState.m_mapReadMode;
    if (readMode == 1) {
        int& readIndex = asyncLoadState.m_asyncReadIndex;
        const int size = asyncLoadState.m_fileSizes[readIndex];
        void* amemCursor = asyncLoadState.m_mapLoadCursor;

        Memory.CopyFromAMemorySync(File.m_readBuffer, amemCursor, static_cast<unsigned long>((size + 0x1F) & ~0x1F));
        asyncLoadState.m_mapLoadCursor = reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
        CheckSum(filePtr, size);
        readIndex += 1;
    } else {
        CFile::CHandle* fileHandle = File.Open(g_StrTmp, 0, CFile::PRI_LOW);
        if (fileHandle == 0) {
            filePtr = 0;
        } else {
            const int size = File.GetLength(fileHandle);
            if (readMode == 3) {
                File.ReadASync(fileHandle);
                filePtr = reinterpret_cast<void*>(1);
                int& openIndex = asyncLoadState.m_asyncOpenIndex;
                asyncLoadState.m_asyncHandles[openIndex] = fileHandle;
                openIndex += 1;
            } else {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                filePtr = File.m_readBuffer;
                File.Close(fileHandle);

                if (readMode == 2) {
                    int& readIndex = asyncLoadState.m_asyncReadIndex;
                    void* amemCursor = asyncLoadState.m_mapLoadCursor;
                    Memory.CopyToAMemorySync(filePtr, amemCursor, static_cast<unsigned long>(size));
                    asyncLoadState.m_fileSizes[readIndex] = size;
                    asyncLoadState.m_fileChecksums[readIndex] = CheckSum(filePtr, size);
                    readIndex += 1;
                    asyncLoadState.m_mapLoadCursor =
                        reinterpret_cast<unsigned char*>(asyncLoadState.m_mapLoadCursor) + size;
                }
            }
        }
    }

    if (filePtr == 0) {
        if (System.m_execParam != 0) {
            System.Printf(const_cast<char*>(s_mapReadErrorFmt), g_StrTmp);
        }
        return 0;
    }

    if (readMode == 2 || readMode == 3) {
        return 1;
    }

    CChunkFile chunkFile;
    chunkFile.SetBuf(filePtr);

    CMapObj* nextMapObj = reinterpret_cast<CMapObj*>(self + 0x954);
    CChunkFile::CChunk chunk;
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id != 0x4D494420) {
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk)) {
            if (chunk.m_id == 0x5343454E) {
                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id != 0x48495420) {
                        continue;
                    }

                    short& hitCount = m_mapHitCount;
                    if (hitCount > 0x1F) {
                        return 0;
                    }
                    CMapHit* hit = reinterpret_cast<CMapHit*>(self + 0x4D4 + (hitCount * 0x24));
                    hit->ReadOtmHit(chunkFile);
                    hitCount += 1;
                }
                chunkFile.PopChunk();
                continue;
            }

            if (chunk.m_id != 0x4F43544D) {
                continue;
            }

            CMapObj* mapObj = nextMapObj;
            int mapObjIndex = 0;
            while (mapObjIndex < m_mapObjCount) {
                unsigned char* objRaw = reinterpret_cast<unsigned char*>(mapObj);
                if (objRaw[0x1E] == 1 || objRaw[0x1E] == 2) {
                    short& octTreeCount = m_octTreeCount;
                    if (octTreeCount > 0xF) {
                        return 0;
                    }

                    unsigned char* octTree = self + 0x14 + (octTreeCount * 0x4C);
                    reinterpret_cast<COctTree*>(octTree)->ReadOtmOctTree(chunkFile);
                    *reinterpret_cast<CMapObj**>(octTree + 8) = mapObj;

                    if (*reinterpret_cast<int*>(objRaw + 0xC) == 0) {
                        if (System.m_execParam != 0) {
                            System.Printf(const_cast<char*>(s_read_mid_mapobj_error));
                        }
                    } else if (objRaw[0x1E] == 1 || objRaw[0x1E] == 2) {
                        nextMapObj = reinterpret_cast<CMapObj*>(objRaw + 0xF0);
                        octTreeCount += 1;
                        break;
                    }

                    if (System.m_execParam != 0) {
                        System.Printf(const_cast<char*>(s_read_mid_octtree_error));
                    }
                    ok = false;
                    nextMapObj = reinterpret_cast<CMapObj*>(objRaw + 0xF0);
                    octTreeCount += 1;
                    break;
                }

                mapObj = reinterpret_cast<CMapObj*>(objRaw + 0xF0);
                mapObjIndex += 1;
            }

            if (mapObjIndex >= m_mapObjCount) {
                if (System.m_execParam != 0) {
                    System.Printf(const_cast<char*>(s_error_root_mapobj_not_found));
                    System.Printf(const_cast<char*>(s_read_mid_octtree_error));
                }
                ok = false;
            }
        }
        chunkFile.PopChunk();
    }

    const int mapObjCount = m_mapObjCount;
    for (int i = 0; i < mapObjCount; i++) {
        unsigned char* obj = self + 0x954 + (i * 0xF0);
        unsigned char type = obj[0x1D];
        CMapHit* hit = *reinterpret_cast<CMapHit**>(obj + 0xC);
        if ((type == 2 || type == 3) && hit != 0) {
            int hitIndex = (reinterpret_cast<unsigned char*>(hit) - (self + 0x4D4)) / 0x24;
            if (m_mapHitCount <= hitIndex) {
                if (System.m_execParam != 0) {
                    System.Printf(const_cast<char*>(s_read_mid_hit_error));
                }
                *reinterpret_cast<CMapHit**>(obj + 0xC) = 0;
            }
        }
    }

    if (ok) {
        if (static_cast<unsigned int>(System.m_execParam) > 2) {
            System.Printf(const_cast<char*>(s_read_mid_ok));
        }
    } else if (System.m_execParam != 0) {
        System.Printf(const_cast<char*>(s_read_mid_error));
    }

    const short octTreeCount = m_octTreeCount;
    for (int i = 0; i < octTreeCount; i++) {
        unsigned char* octTree = self + 0x14 + (i * 0x4C);
        unsigned char* obj = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(octTree + 8));
        if (obj != 0) {
            obj[0x1F] = static_cast<unsigned char>(i);
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

    const int mapObjCount = m_mapObjCount;
    if (mapObjCount == 0) {
        return;
    }

    CPtrArray<CMapAnimRun*>* mapAnimRunArray = &GetMapAnimRunArray();
    const int mapAnimRunCount = mapAnimRunArray->GetSize();
    for (int i = 0; i < mapAnimRunCount; i++) {
        CMapAnimRun* mapAnimRun = (*mapAnimRunArray)[i];
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
    if (mapLightId != 0x1E) {
        mapLightId = 0x1C;
    }

    SetLightSource();

    CPtrArray<CMapShadow*>* mapShadowArray = &GetMapShadowArray();
    const int mapShadowCount = mapShadowArray->GetSize();
    for (int i = 0; i < mapShadowCount; i++) {
        CMapShadow* mapShadow = (*mapShadowArray)[i];
        mapShadow->Calc();
    }

    for (int i = 0; i < mapObjCount; i++) {
        reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)))->Calc();
    }

    CMapTexAnimSet* mapTexAnimSet = m_mapTexAnimSet;
    if (mapTexAnimSet != 0) {
        mapTexAnimSet->Calc();
    }

    CMaterialSet* materialSet = m_materialSet;
    materialSet->Calc();

    const int octTreeCount = m_octTreeCount;
    for (int i = 0; i < octTreeCount; i++) {
        COctTree* octTree = reinterpret_cast<COctTree*>(Ptr(this, 0x14 + (i * 0x4C)));
        LightPcs.InsertOctTree(static_cast<CLightPcs::TARGET>(1), *octTree);
    }

    for (int i = 0; i < octTreeCount; i++) {
        COctTree* octTree = reinterpret_cast<COctTree*>(Ptr(this, 0x14 + (i * 0x4C)));
        CMapShadowInsertOctTree(static_cast<CMapShadow::TARGET>(1), *octTree);
    }

    for (int i = 0; i < octTreeCount; i++) {
        reinterpret_cast<COctTree*>(Ptr(this, 0x14 + (i * 0x4C)))->SetDrawFlag();
    }

    for (int i = 0; i < mapObjCount; i++) {
        reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)))->SetDrawFlag();
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
    unsigned char* self = reinterpret_cast<unsigned char*>(this);
    if (m_mapObjCount != 0) {
        for (unsigned int i = 0; i < static_cast<unsigned int>(GetMapShadowArray().GetSize()); i++) {
            CMapShadow* mapShadow = GetMapShadowArray()[i];
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
    const short mapObjCount = m_mapObjCount;
    if ((mapObjCount == 0) || (m_mapReadReady == 0)) {
        return;
    }

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZMode(1, GX_LEQUAL, 1);
    LightPcs.SetNumDiffuse(0);

    if ((gMapHitDrawMode.m_byte & 8) == 0) {
        CMapObj* mapObj = GetMapObjArray();
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->Draw(0xFE);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        const short octTreeCount = m_octTreeCount;
        COctTree* octTree = GetOctTreeArray();
        for (int i = 0; i < octTreeCount; i++) {
            octTree->Draw(0xFF);
            octTree++;
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
    const short mapObjCount = m_mapObjCount;
    if ((mapObjCount == 0) || (m_mapReadReady == 0)) {
        return;
    }

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZMode(1, GX_LEQUAL, 1);
    LightPcs.SetNumDiffuse(0);

    Mtx44 projection;
    PSMTX44Copy(CameraPcs.m_screenMatrix, projection);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);
    m_underWaterTexPending = 1;

    if ((gMapHitDrawMode.m_byte & 8) == 0) {
        const short octTreeCount = m_octTreeCount;

        COctTree* octTree = GetOctTreeArray();
        for (int i = 0; i < octTreeCount; i++) {
            octTree->Draw(0);
            octTree++;
        }

        CMapObj* mapObj = GetMapObjArray();
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->Draw(0x40);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        PartPcs.DrawShoki();

        GXSetColorUpdate(1);
        GXSetAlphaUpdate(0);
        GXSetCullMode(GX_CULL_BACK);
        GXSetZMode(1, GX_LEQUAL, 1);
        LightPcs.SetNumDiffuse(0);

        mapObj = GetMapObjArray();
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->Draw(0);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        octTree = GetOctTreeArray();
        for (int i = 0; i < octTreeCount; i++) {
            octTree->Draw(1);
            octTree++;
        }
    }

    if ((gMapHitDrawMode.m_byte & 8) != 0) {
        _GXColor clearColor;
        clearColor.r = 0xFF;
        clearColor.g = 0xFF;
        clearColor.b = 0xFF;
        clearColor.a = 0xFF;
        GXSetCopyClear(clearColor, 0x00FFFFFF);
    }

    if ((gMapHitDrawMode.m_byte & 4) != 0) {
        _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
        _GXSetAlphaCompare(GX_GEQUAL, 1, GX_AOP_AND, GX_ALWAYS, 0);
        GXSetZCompLoc(0);
        GXSetZMode(1, GX_LEQUAL, 1);
        GXSetCullMode(GX_CULL_BACK);
        GXSetNumTevStages(1);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        GXSetNumChans(1);
        GXSetChanCtrl(GX_COLOR0A0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
        GXSetChanCtrl(GX_ALPHA0, 0, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
        _GXColor wireColor;
        wireColor.r = 0x80;
        wireColor.g = 0x80;
        wireColor.b = 0x80;
        wireColor.a = 0x80;
        GXSetChanMatColor(GX_COLOR0A0, wireColor);

        CameraPcs.SetOffsetZBuff(FLOAT_8032f9bc);

        CMapObj* mapObj = GetMapObjArray();
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->DrawHitWire();
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        mapObj = GetMapObjArray();
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->DrawHitNormal();
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
        }

        CameraPcs.SetOffsetZBuff(FLOAT_8032f9a0);
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
    const short mapObjCount = m_mapObjCount;
    if ((mapObjCount == 0) || (m_mapReadReady == 0)) {
        return;
    }

    Mtx44 projection;
    PSMTX44Copy(CameraPcs.m_screenMatrix, projection);
    GXSetProjection(projection, GX_ORTHOGRAPHIC);

    GXSetColorUpdate(1);
    GXSetAlphaUpdate(0);
    GXSetCullMode(GX_CULL_BACK);
    GXSetZMode(1, GX_LEQUAL, 1);
    LightPcs.SetNumDiffuse(0);

    if (gMapHitDrawMode.m_byte == 0) {
        COctTree* octTree = GetOctTreeArray();
        const short octTreeCount = m_octTreeCount;
        for (int i = 0; i < octTreeCount; i++) {
            octTree->Draw(2);
            octTree++;
        }

        CMapObj* mapObj = GetMapObjArray();
        for (int i = 0; i < mapObjCount; i++) {
            mapObj->Draw(2);
            mapObj = reinterpret_cast<CMapObj*>(Ptr(mapObj, 0xF0));
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
    if ((FLOAT_8032f9a0 == move->x) && (FLOAT_8032f9a0 == move->y) && (FLOAT_8032f9a0 == move->z)) {
        return 0;
    }

    if ((move->x <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->x) && (move->y <= FLOAT_8032f9a4) &&
        (FLOAT_8032f9a8 <= move->y) && (move->z <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->z)) {
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(const_cast<char*>(s_check_hit_cylinder_small_vec_fmt), static_cast<double>(move->x),
                static_cast<double>(move->y), static_cast<double>(move->z));
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(g_MsgFlashy);
        }
    }

    g_hit_edge_idx_min = -2;
    g_hit_t_min = FLOAT_8032f9ac;
    PSVECAdd(&cylinder->m_bottom, move, &cylinder->m_top);

    for (int i = 0; i < m_octTreeCount; i++) {
        COctTree* octTree = reinterpret_cast<COctTree*>(Ptr(this, 0x14 + (i * 0x4C)));
        if (octTree->CheckHitCylinder(cylinder, move, mask) != 0) {
            m_hitMapObj = *reinterpret_cast<CMapObj**>(Ptr(octTree, 8));
            return 1;
        }
    }

    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)));
        m_hitMapObj = mapObj;
        if (mapObj->CheckHitCylinder(cylinder, move, mask) != 0) {
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
    int hit = 0;

    if ((FLOAT_8032f9a0 == move->x) && (FLOAT_8032f9a0 == move->y) && (FLOAT_8032f9a0 == move->z)) {
        return 0;
    }

    if ((move->x <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->x) && (move->y <= FLOAT_8032f9a4) &&
        (FLOAT_8032f9a8 <= move->y) && (move->z <= FLOAT_8032f9a4) && (FLOAT_8032f9a8 <= move->z)) {
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(g_MsgFlashy);
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(const_cast<char*>(s_check_hit_cylinder_near_small_vec_fmt), static_cast<double>(move->x),
                static_cast<double>(move->y), static_cast<double>(move->z));
        }
        if (static_cast<unsigned int>(System.m_execParam) > 1) {
            System.Printf(g_MsgFlashy);
        }
    }

    g_hit_edge_idx_min = -2;
    g_hit_t_min = FLOAT_8032f9ac;
    PSVECAdd(&cylinder->m_bottom, move, &cylinder->m_top);

    for (int i = 0; i < m_octTreeCount; i++) {
        COctTree* octTree = reinterpret_cast<COctTree*>(Ptr(this, 0x14 + (i * 0x4C)));
        DAT_8032ec88 = 0;
        octTree->CheckHitCylinderNear(cylinder, move, mask);
        if (DAT_8032ec88 != 0) {
            hit = 1;
            m_hitMapObj = *reinterpret_cast<CMapObj**>(Ptr(octTree, 8));
        }
    }

    for (int i = 0; i < m_mapObjCount; i++) {
        CMapObj* mapObj = reinterpret_cast<CMapObj*>(Ptr(this, 0x954 + (i * 0xF0)));
        DAT_8032ec88 = 0;
        mapObj->CheckHitCylinderNear(cylinder, move, mask);
        if (DAT_8032ec88 != 0) {
            hit = 1;
            m_hitMapObj = mapObj;
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
    float scaleY = kMapViewScaleY * proj[5];
    float scaleX = proj[0];
    Mtx* viewCopy = &m_viewMtx;

    PSMTXCopy(viewMtx, *viewCopy);
    PSMTXScaleApply(
        *viewCopy, m_scaledViewMtxPrimary, kMapViewScaleXPrimary * scaleX, scaleY, kMapViewScaleZ);
    PSMTXScaleApply(
        *viewCopy, m_scaledViewMtxSecondary, kMapViewScaleXSecondary * scaleX, scaleY, kMapViewScaleZ);
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
    CMapIdGrp* mapIdGrp = GetMapIdGrpArray() + mapIdGrpIndex;

    switch (channelIndex) {
    case 0:
        mapIdGrp->m_primaryColor = color;
        return;
    case 1:
        mapIdGrp->m_secondaryColor = color;
        return;
    case 2:
        mapIdGrp->m_tertiaryColor = color;
        return;
    case 3:
        mapIdGrp->m_quaternaryColor = color;
        return;
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
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < m_mapObjCount; i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x988) == id) {
            *reinterpret_cast<float*>(mapObj + 0x998) = nearRange;
            *reinterpret_cast<float*>(mapObj + 0x99C) = farRange;
            *reinterpret_cast<float*>(mapObj + 0x9A8) = fadeRange;
            *reinterpret_cast<float*>(mapObj + 0x9A0) = minAlpha;
            *reinterpret_cast<float*>(mapObj + 0x9A4) = maxAlpha;
            if (*reinterpret_cast<void**>(mapObj + 0x960) != 0 && *reinterpret_cast<signed char*>(mapObj + 0x973) != -1) {
                *reinterpret_cast<float*>(mapObj + 0x9A0) = FLOAT_8032f988;
                *reinterpret_cast<float*>(mapObj + 0x9A4) = FLOAT_8032f98c;
                *reinterpret_cast<unsigned char*>(mapObj + 0x969) = 2;
                *reinterpret_cast<unsigned char*>(mapObj + 0x97A) = 1;
            }
            *reinterpret_cast<short*>(mapObj + 0x97E) = 0x4000;
            found = 1;
            *reinterpret_cast<short*>(mapObj + 0x97C) = 0x4000;
            *reinterpret_cast<short*>(mapObj + 0x980) = 0;
        }
        mapObj += 0xF0;
    }

    if (!found) {
        if (System.m_execParam >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (System.m_execParam >= 1) {
            System.Printf(const_cast<char*>(s_set_bg_transparent_missing_fmt), id);
        }
        if (System.m_execParam >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (System.m_execParam >= 1) {
            System.Printf(const_cast<char*>(DAT_8032f984));
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
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < m_mapObjCount; i++) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x988) == id) {
            *reinterpret_cast<short*>(mapObj + 0x97E) = static_cast<short>(alpha << 7);
            found = 1;
            *reinterpret_cast<short*>(mapObj + 0x980) = static_cast<short>(
                (static_cast<int>(*reinterpret_cast<short*>(mapObj + 0x97E)) -
                 static_cast<int>(*reinterpret_cast<short*>(mapObj + 0x97C))) /
                frameCount);
        }
        mapObj += 0xF0;
    }

    if (!found) {
        if (System.m_execParam >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (System.m_execParam >= 1) {
            System.Printf(const_cast<char*>(s_set_bg_camera_semi_trans_missing_fmt), id);
        }
        if (System.m_execParam >= 1) {
            System.Printf(g_MsgFlashy);
        }
        if (System.m_execParam >= 1) {
            System.Printf(const_cast<char*>(DAT_8032f984));
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
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    int objIndex = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (0 < objCount) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x982) == id) {
            return objIndex;
        }
        mapObj += 0xF0;
        objIndex++;
        objCount--;
    }

    return -1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterial* CMapMng::GetMaterialID(unsigned char materialId)
{
    unsigned long index = 0;
    unsigned char* materialSet = reinterpret_cast<unsigned char*>(m_materialSet);
    CPtrArray<CMaterial*>* materials = reinterpret_cast<CPtrArray<CMaterial*>*>(materialSet + 8);

    while (index < UnkMaterialSetGetter(materials)) {
        CMaterial* material = (*materials)[index];
        if (material != 0 && reinterpret_cast<unsigned char*>(material)[0xA6] == materialId) {
            return (*materials)[index];
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
    int objCount = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    int objIndex = 0;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);

    while (0 < objCount) {
        if (*reinterpret_cast<unsigned short*>(mapObj + 0x984) == effectId) {
            return objIndex;
        }
        mapObj += 0xF0;
        objIndex++;
        objCount--;
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
    int offset = mapObjIndex * 0xF0;
    CMapMng* self = this;
    PSMTXCopy(source, reinterpret_cast<MtxPtr>(Ptr(self, offset + 0x9DC)));

    u8* mapObj = Ptr(self, offset);
    mapObj[0x970] = 1;
    mapObj[0x96F] = 1;
    mapObj[0x970] = 0;
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
    CMapObj* mapObj = GetMapObjArray() + mapObjIndex;
    PSMTXCopy(*reinterpret_cast<Mtx*>(reinterpret_cast<unsigned char*>(mapObj) + 0xB8), destination);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::SetMapObjAnim(int mapObjIndex, int startFrame, int endFrame, int loop)
{
    CPtrArray<CMapAnimRun*>* mapAnimRunArray = &GetMapAnimRunArray();
    CPtrArray<CMapAnim*>* mapAnimArray = &GetMapAnimArray();
    CMapAnimRun* foundMapAnimRun = 0;
    CMapObj* mapObj = GetMapObjArray() + mapObjIndex;
    int mapAnimRunCount = mapAnimRunArray->GetSize();

    for (unsigned int mapAnimRunIndex = 0; mapAnimRunIndex < static_cast<unsigned int>(mapAnimRunCount); mapAnimRunIndex++) {
        CMapAnimRun* mapAnimRun = (*mapAnimRunArray)[mapAnimRunIndex];
        CPtrArray<CMapAnimNode*>* mapAnimNodeArray =
            reinterpret_cast<CPtrArray<CMapAnimNode*>*>((*mapAnimArray)[mapAnimRun->m_mapAnimIndex]);
        int mapAnimNodeCount = mapAnimNodeArray->GetSize();

        for (int mapAnimNodeIndex = 0; mapAnimNodeIndex < mapAnimNodeCount; mapAnimNodeIndex++) {
            CMapAnimNode* mapAnimNode = (*mapAnimNodeArray)[mapAnimNodeIndex];
            if (reinterpret_cast<CMapObj*>(*reinterpret_cast<int*>(mapAnimNode)) == mapObj) {
                foundMapAnimRun = mapAnimRun;
                goto startMapObjAnim;
            }
        }
    }

startMapObjAnim:
    foundMapAnimRun->Start(startFrame, endFrame, loop);
}

/*
 * --INFO--
 * PAL Address: 0x8002f710
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMng::SetMapAnimID(int animId, int startFrame, int endFrame, int loop)
{
    CPtrArray<CMapAnimRun*>* mapAnimRunArray = &GetMapAnimRunArray();
    CMapAnimRun* mapAnimRun = 0;
    int mapAnimRunCount = mapAnimRunArray->GetSize();

    for (unsigned long i = 0; i < static_cast<unsigned long>(mapAnimRunCount); i++) {
        CMapAnimRun* current = (*mapAnimRunArray)[i];
        if (current->m_animId == static_cast<unsigned char>(animId)) {
            mapAnimRun = current;
            break;
        }
    }

    mapAnimRun->Start(startFrame, endFrame, loop);
}

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
    CMapObj* mapObj = reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954);
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
    CMapMng* mapMng = this;

    for (int i = 0; i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC); i++) {
        unsigned char* mapObj = reinterpret_cast<unsigned char*>(mapMng);

        if (*reinterpret_cast<unsigned short*>(mapObj + 0x982) == id) {
            if (show != 0) {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) | 1);
            } else {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) & 0xFE);
            }
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(mapMng) + 0xF0);
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
    CMapMng* mapMng = this;

    for (int i = 0; i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC); i++) {
        if (*reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned char*>(mapMng) + 0x982) == id) {
            reinterpret_cast<CMapObj*>(reinterpret_cast<unsigned char*>(mapMng) + 0x954)->SetShow(show);
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(mapMng) + 0xF0);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMng::ShowMapMeshID(int id, int show)
{
    CMapMng* mapMng = this;

    for (int i = 0; i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC); i++) {
        unsigned char* mapObj = reinterpret_cast<unsigned char*>(mapMng);

        if (*reinterpret_cast<unsigned short*>(mapObj + 0x988) == id) {
            if (show != 0) {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) | 1);
            } else {
                *reinterpret_cast<unsigned char*>(mapObj + 0x96C) =
                    static_cast<unsigned char>(*reinterpret_cast<unsigned char*>(mapObj + 0x96C) & 0xFE);
            }
        }
        mapMng = reinterpret_cast<CMapMng*>(reinterpret_cast<unsigned char*>(mapMng) + 0xF0);
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
    int numMapObj = *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC);
    unsigned char* scan = reinterpret_cast<unsigned char*>(this);

    while (0 < numMapObj) {
        if (*reinterpret_cast<unsigned short*>(scan + 0x982) == static_cast<unsigned short>(id)) {
            goto found;
        }
        scan += 0xF0;
        objIndex++;
        numMapObj--;
    }
    objIndex = -1;

found:
    const unsigned int packedColor = *reinterpret_cast<unsigned int*>(&color);
    const float posX = position.x;
    const float posY = position.y;
    const float posZ = position.z;
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this) + (objIndex * 0xF0) + 0x954;
    unsigned char* mapObjLight = *reinterpret_cast<unsigned char**>(mapObj + 0xEC);

    if (*reinterpret_cast<int*>(mapObjLight + 4) == CMapObjAtr::SPOT_LIGHT) {
        const unsigned char* colorBytes = reinterpret_cast<const unsigned char*>(&packedColor);
        *reinterpret_cast<unsigned char*>(mapObjLight + 8) = colorBytes[0];
        *reinterpret_cast<unsigned char*>(mapObjLight + 9) = colorBytes[1];
        *reinterpret_cast<unsigned char*>(mapObjLight + 10) = colorBytes[2];
        *reinterpret_cast<unsigned char*>(mapObjLight + 11) = colorBytes[3];
        *reinterpret_cast<float*>(mapObj + 0x70) = posX;
        *reinterpret_cast<float*>(mapObj + 0x74) = posY;
        *reinterpret_cast<float*>(mapObj + 0x78) = posZ;
        *reinterpret_cast<unsigned char*>(mapObj + 0x1C) = 1;
        *reinterpret_cast<unsigned char*>(mapObj + 0x1B) = 1;
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
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this) + (mapObjIndex * 0xF0) + 0x954;
    *reinterpret_cast<float*>(mapObj + 0x58) = x;
    *reinterpret_cast<float*>(mapObj + 0x5C) = y;
    *reinterpret_cast<float*>(mapObj + 0x60) = z;
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
    unsigned char* mapObj = reinterpret_cast<unsigned char*>(this);
    int i = 0;

    while (i < *reinterpret_cast<short*>(reinterpret_cast<unsigned char*>(this) + 0xC)) {
        if (static_cast<int>(*reinterpret_cast<unsigned short*>(mapObj + 0x982)) == id) {
            *reinterpret_cast<unsigned char*>(mapObj + 0x969) = prio;
            *reinterpret_cast<unsigned char*>(mapObj + 0x968) = prio;
        }
        mapObj += 0xF0;
        i++;
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
 * PAL Address: 0x800342a0
 * PAL Size: 320b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_map_cpp(void)
{
    __construct_array(MapMng.GetOctTreeArray(), reinterpret_cast<ConstructorDestructor>(__ct__8COctTreeFv),
                      reinterpret_cast<ConstructorDestructor>(__dt__8COctTreeFv), 0x4C, 0x10);
    __construct_array(MapMng.GetMapHitArray(), reinterpret_cast<ConstructorDestructor>(__ct__7CMapHitFv),
                      reinterpret_cast<ConstructorDestructor>(__dt__7CMapHitFv), 0x24, 0x20);
    __construct_array(MapMng.GetMapObjArray(), reinterpret_cast<ConstructorDestructor>(__ct__7CMapObjFv),
                      reinterpret_cast<ConstructorDestructor>(__dt__7CMapObjFv), 0xF0, 0x200);
    __construct_array(MapMng.GetMapMeshArray(), reinterpret_cast<ConstructorDestructor>(__ct__8CMapMeshFv),
                      reinterpret_cast<ConstructorDestructor>(__dt__8CMapMeshFv), 0x44, 0xA0);
    __ct__25CPtrArray_P11CMapAnimRun_Fv(&MapMng.GetMapAnimRunArray());
    __ct__21CPtrArray_P8CMapAnim_Fv(&MapMng.GetMapAnimArray());
    __ct__27CPtrArray_P13CMapAnimKeyDt_Fv(&MapMng.GetMapAnimKeyDtArray());
    __ct__24CPtrArray_P10CMapShadow_Fv(&MapMng.GetMapShadowArray());
    __construct_array(
        MapMng.GetMapLightHolderArrays(),
        reinterpret_cast<ConstructorDestructor>(__ct__29CPtrArray_P15CMapLightHolder_Fv),
        reinterpret_cast<ConstructorDestructor>(dtor_80034414),
        0x1C,
        2);

    __construct_array(MapMng.GetMapIdGrpArray(), reinterpret_cast<ConstructorDestructor>(__ct__9CMapIdGrpFv), 0, 0x14, 0x100);
    __register_global_object(&MapMng, reinterpret_cast<void*>(__dt__7CMapMngFv), &Vec_80245758);
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
    __destroy_arr(GetMapLightHolderArrays(), reinterpret_cast<ConstructorDestructor>(dtor_80034414), 0x1C, 2);
    if (Ptr(this, 0x21434) != 0) {
        *reinterpret_cast<void***>(Ptr(this, 0x21434)) = __vt__8CPtrArrayIP10CMapShadow;
        void* items = *reinterpret_cast<void**>(Ptr(this, 0x21444));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            *reinterpret_cast<void**>(Ptr(this, 0x21444)) = 0;
        }
        *reinterpret_cast<int*>(Ptr(this, 0x2143C)) = 0;
        *reinterpret_cast<int*>(Ptr(this, 0x21438)) = 0;
    }
    if (Ptr(this, 0x21418) != 0) {
        *reinterpret_cast<void***>(Ptr(this, 0x21418)) = __vt__8CPtrArrayIP13CMapAnimKeyDt;
        void* items = *reinterpret_cast<void**>(Ptr(this, 0x21428));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            *reinterpret_cast<void**>(Ptr(this, 0x21428)) = 0;
        }
        *reinterpret_cast<int*>(Ptr(this, 0x21420)) = 0;
        *reinterpret_cast<int*>(Ptr(this, 0x2141C)) = 0;
    }
    if (Ptr(this, 0x213FC) != 0) {
        *reinterpret_cast<void***>(Ptr(this, 0x213FC)) = __vt__8CPtrArrayIP7CMapAnim;
        void* items = *reinterpret_cast<void**>(Ptr(this, 0x2140C));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            *reinterpret_cast<void**>(Ptr(this, 0x2140C)) = 0;
        }
        *reinterpret_cast<int*>(Ptr(this, 0x21404)) = 0;
        *reinterpret_cast<int*>(Ptr(this, 0x21400)) = 0;
    }
    if (Ptr(this, 0x213E0) != 0) {
        *reinterpret_cast<void***>(Ptr(this, 0x213E0)) = __vt__8CPtrArrayIP11CMapAnimRun;
        void* items = *reinterpret_cast<void**>(Ptr(this, 0x213F0));
        if (items != 0) {
            delete[] reinterpret_cast<void**>(items);
            *reinterpret_cast<void**>(Ptr(this, 0x213F0)) = 0;
        }
        *reinterpret_cast<int*>(Ptr(this, 0x213E8)) = 0;
        *reinterpret_cast<int*>(Ptr(this, 0x213E4)) = 0;
    }
    __destroy_arr(GetMapMeshArray(), reinterpret_cast<ConstructorDestructor>(__dt__8CMapMeshFv), 0x44, 0xA0);
    __destroy_arr(GetMapObjArray(), reinterpret_cast<ConstructorDestructor>(__dt__7CMapObjFv), 0xF0, 0x200);
    __destroy_arr(GetMapHitArray(), reinterpret_cast<ConstructorDestructor>(__dt__7CMapHitFv), 0x24, 0x20);
    __destroy_arr(GetOctTreeArray(), reinterpret_cast<ConstructorDestructor>(__dt__8COctTreeFv), 0x4C, 0x10);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapMng::CMapMng()
{
	// TODO
}
