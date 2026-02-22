#include "ffcc/materialman.h"
#include "ffcc/pad.h"
#include "ffcc/chunkfile.h"
#include "ffcc/textureman.h"
#include "ffcc/vector.h"

#include <dolphin/mtx.h>

#include <string.h>

extern "C" unsigned long UnkMaterialSetGetter(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void __dla__FPv(void*);
extern "C" void __dl__FPv(void*);
extern "C" void __ct__6CColorFv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void __ct__10CTexScrollFv(void*);
extern "C" void __dt__10CTexScrollFv(void*, int);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void __destroy_arr(void*, void*, unsigned long, unsigned long);
extern "C" int CheckName__8CTextureFPc(CTexture*, char*);
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int, int, int, int, int);
extern "C" void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int, int, int, int, int);
extern "C" void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int,
                                                                                                        int, int, int);
extern "C" void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int,
                                                                                                        int, int, int);
extern "C" int CheckFrustum__6CBoundFR3VecPA4_ff(CBound*, Vec*, float (*)[4], float);
extern "C" void SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl(
    CMaterialMan*, CMapShadow*, float (*)[4], int, unsigned long);
class CMapKeyFrame;
extern "C" float Get__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" void Calc__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" void ReadFrame__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*);
extern "C" void ReadKey__12CMapKeyFrameFR10CChunkFilei(CMapKeyFrame*, CChunkFile*, int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __vt__9CMaterial[];
extern "C" void* PTR_PTR_s_CMaterialMan_801e9bec;
extern "C" void* PTR_PTR_s_CMaterialSet_801e9bbc;
extern CMemory Memory;
extern CTextureMan TextureMan;
class CMapMng;
extern CMapMng MapMng;
extern unsigned char MaterialMan[];
extern float FLOAT_8032faf0;
extern float FLOAT_8032faf4;
extern float FLOAT_8032faf8;
extern float FLOAT_8032fafc;
static const char s_materialStageName[] = "material";

/*
 * --INFO--
 * PAL Address: 0x80043ccc
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_materialman_cpp(void)
{
    *reinterpret_cast<void**>(MaterialMan) = &PTR_PTR_s_CMaterialMan_801e9bec;
    __ct__6CColorFv(reinterpret_cast<void*>(0x80268E83));
}

class CMapKeyFrame
{
public:
    float Get();
    void Calc();
};

template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    unsigned long m_size;
    unsigned long m_numItems;
    unsigned long m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    CPtrArray();
    int GetSize();
    int Add(T item);
    ~CPtrArray();
    void RemoveAll();
    void SetStage(CMemory::CStage* stage);
    int setSize(unsigned long size);
    void SetAt(unsigned long index, T item);
    T operator[](unsigned long index);
};

template <>
CPtrArray<CMaterial*>::CPtrArray()
{
    m_vtable = reinterpret_cast<void**>(0x801E9BFC);
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

typedef void (*VirtualDtorFn)(void*, int);

static void ReleaseRef(void* object)
{
    if (object == 0) {
        return;
    }

    int& refCount = *reinterpret_cast<int*>(Ptr(object, 4));
    int nextRefCount = refCount - 1;
    refCount = nextRefCount;
    if (nextRefCount == 0) {
        void** vtable = *reinterpret_cast<void***>(object);
        reinterpret_cast<VirtualDtorFn>(vtable[2])(object, 1);
    }
}

static char s_materialman_cpp[] = "materialman.cpp";
static char s_collection_ptrarray_h[] = "collection_ptrarray.h";

struct RawPtrArray {
    void** vtable;
    unsigned long size;
    unsigned long numItems;
    unsigned long defaultSize;
    void** items;
    CMemory::CStage* stage;
    int growCapacity;
};

static int HighestSetBit(unsigned int value)
{
    for (int bit = 31; bit >= 0; bit--) {
        if ((value & (1u << bit)) != 0) {
            return bit;
        }
    }
    return -1;
}

static CMaterial* AllocMaterial()
{
    unsigned char* material = reinterpret_cast<unsigned char*>(
        _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory,
            0xA8,
            *reinterpret_cast<CMemory::CStage**>(MaterialMan + 0x218),
            s_materialman_cpp,
            0xCFF,
            0));
    if (material == 0) {
        return 0;
    }

    __ct__4CRefFv(material);
    *reinterpret_cast<void**>(material) = __vt__9CMaterial;
    __construct_array(material + 0x4C, __ct__10CTexScrollFv, __dt__10CTexScrollFv, 0x14, 4);
    memset(material + 8, 0, 0x10);
    *reinterpret_cast<int*>(material + 0x9C) = -1;
    material[0xA0] = 4;
    material[0xA1] = 1;
    material[0xA2] = 0;
    material[0xA4] = 0;
    *reinterpret_cast<void**>(material + 0x3C) = 0;
    *reinterpret_cast<void**>(material + 0x40) = 0;
    *reinterpret_cast<void**>(material + 0x44) = 0;
    *reinterpret_cast<void**>(material + 0x48) = 0;
    material[0x34] = 0;
    material[0x35] = 0;
    material[0x36] = 0;
    material[0xA5] = 0;

    return reinterpret_cast<CMaterial*>(material);
}

static void AddTextureIndex(CMaterial* material, unsigned short textureIndex)
{
    unsigned short numTexture = *reinterpret_cast<unsigned short*>(Ptr(material, 0x18));
    *reinterpret_cast<unsigned short*>(Ptr(material, 0x18)) = static_cast<unsigned short>(numTexture + 1);
    *reinterpret_cast<unsigned short*>(Ptr(material, 0x1A + (numTexture << 1))) = textureIndex;
}

static CMapKeyFrame* AllocMapKeyFrame(int line)
{
    CMapKeyFrame* keyFrame = reinterpret_cast<CMapKeyFrame*>(__nw__FUlPQ27CMemory6CStagePci(
        0x28,
        *reinterpret_cast<CMemory::CStage**>(MaterialMan + 0x218),
        s_materialman_cpp,
        line));
    if (keyFrame != 0) {
        memset(keyFrame, 0, 0x28);
        *reinterpret_cast<unsigned char*>(Ptr(keyFrame, 0xC)) = 1;
    }
    return keyFrame;
}

static void SetMaterialColor(CMaterial* material, unsigned int rgba)
{
    *Ptr(material, 0x48) = static_cast<unsigned char>((rgba >> 24) & 0xFF);
    *Ptr(material, 0x49) = static_cast<unsigned char>((rgba >> 16) & 0xFF);
    *Ptr(material, 0x4A) = static_cast<unsigned char>((rgba >> 8) & 0xFF);
    *Ptr(material, 0x4B) = static_cast<unsigned char>(rgba & 0xFF);
}
}

template <>
CPtrArray<CMaterial*>::~CPtrArray()
{
    m_vtable = reinterpret_cast<void**>(0x801E9BFC);
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x80043aac
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CMaterial*>* dtor_80043AAC(CPtrArray<CMaterial*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->m_vtable = reinterpret_cast<void**>(0x801E9BFC);
        ptrArray->RemoveAll();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

template <>
void CPtrArray<CMaterial*>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

template <>
void CPtrArray<CMaterial*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

template <>
int CPtrArray<CMaterial*>::Add(CMaterial* item)
{
    int result = setSize(m_numItems + 1);
    if (result != 0) {
        m_items[m_numItems] = item;
        m_numItems = m_numItems + 1;
    }
    return result != 0;
}

template <>
int CPtrArray<CMaterial*>::setSize(unsigned long size)
{
    if (m_size < size) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            m_size = m_size << 1;
        }

        void** newItems = reinterpret_cast<void**>(
            _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                &Memory,
                m_size << 2,
                m_stage,
                s_collection_ptrarray_h,
                0xFA,
                0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            __dla__FPv(m_items);
            m_items = 0;
        }
        m_items = reinterpret_cast<CMaterial**>(newItems);
    }
    return 1;
}

template <>
void CPtrArray<CMaterial*>::SetAt(unsigned long index, CMaterial* item)
{
    m_items[index] = item;
}

/*
 * --INFO--
 * PAL Address: 0x80041f28
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned short CPad::GetButtonDown(long padIndex)
{
    bool shouldZero = false;

    if (_1c4_4_ == 0) {
        if ((padIndex == 0) && (_1c0_4_ == 0xFFFFFFFF)) {
            goto read_slot;
        }
    }

    shouldZero = true;
read_slot:
    if (shouldZero) {
        return 0;
    }

    unsigned int padIndexU = static_cast<unsigned int>(padIndex);
    unsigned int resolvedIndex =
        padIndexU & ~((~(_1c0_4_ - padIndexU | padIndexU - _1c0_4_)) >> 31);
    return *reinterpret_cast<unsigned short*>(
        reinterpret_cast<unsigned char*>(this) + (resolvedIndex * 0x54) + 8);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void chkbit32(unsigned long*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void getHsb(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMaterialMan::CMaterialMan()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::Init()
{
	*reinterpret_cast<CMemory::CStage**>(Ptr(this, 0x218)) = Memory.CreateStage(0x20000, const_cast<char*>(s_materialStageName), 0);
	*Ptr(this, 0x204) = 0x30;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::Quit()
{
	Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(Ptr(this, 0x218)));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetBlendMode(CMaterialSet*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_bump_st(int, _GXTevScale)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_bump_water(_GXTevScale)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_bump_spec_col_water(_GXTevScale)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80042b58
 * PAL Size: 264b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::addtev_bump_jimen(_GXTevScale)
{
    int tevStage = *reinterpret_cast<int*>(Ptr(this, 0x60));

    GXSetIndTexMtx((GXIndTexMtxID)1, reinterpret_cast<const float(*)[3]>(0x8026901c), 0);
    GXSetNumIndStages(1);
    GXSetIndTexOrder((GXIndTexStageID)0,
                     *reinterpret_cast<GXTexCoordID*>(Ptr(this, 0x1E8)),
                     *reinterpret_cast<GXTexMapID*>(Ptr(this, 0x1C4)));
    GXSetIndTexCoordScale((GXIndTexStageID)0, (GXIndTexScale)0, (GXIndTexScale)0);
    GXSetTevIndBumpXYZ((GXTevStageID)tevStage, (GXIndTexStageID)0, (GXIndTexMtxID)1);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(
        tevStage, *reinterpret_cast<int*>(Ptr(this, 0x1F8)), *reinterpret_cast<int*>(Ptr(this, 0x1C8)), 0xFF);
    _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
        tevStage, 0xF, 4, 9, 0);
    _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
        tevStage, 7, 7, 7, 0);
    _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(tevStage, 0, 0, 0, 1, 0);
    _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(tevStage, 0, 0, 0, 1, 0);
    *reinterpret_cast<unsigned int*>(Ptr(this, 0x60)) =
        (((*reinterpret_cast<unsigned int*>(Ptr(this, 0x60))) & 0xFF) + 1) & 0xFF;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_lightmap(long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_shadow(long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_stdShadow(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_full_shadow(long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetUnderWaterTex()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetMaterial(CMaterialSet*, int, int, _GXTevScale)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetMaterialCharaShadow(CMaterial*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetMaterialPart(CMaterialSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetMaterialMenu(CMaterialSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003eb24
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetObjMatrix(float (*mtxA) [4], float (*mtxB) [4])
{
    Mtx tmp0;
    Mtx tmp1;

    PSMTXConcat(mtxA, mtxB, tmp0);
    GXLoadPosMtxImm(tmp0, GX_PNMTX0);
    PSMTXCopy(tmp0, tmp1);
    tmp1[0][3] = 0.0f;
    tmp1[1][3] = 0.0f;
    tmp1[2][3] = 0.0f;
    GXLoadNrmMtxImm(tmp1, GX_PNMTX0);
    PSMTXCopy(tmp1, reinterpret_cast<MtxPtr>(Ptr(this, 0xE8)));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetTexScroll(float, float, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetFullScreenShadow(CFullScreenShadow&, float (*) [4], long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetShadow(CMapShadow&, float (*) [4], int, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetShadowBit32(CMapShadow::TARGET, unsigned long*, float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetPosition(CMapShadow::TARGET, Vec*, float, float, float (*) [4], int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::GetCharaShadow(int, CMaterial **, float (**) [4], Vec*, float, float, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003e058
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetShadowBound(CMapShadow::TARGET target, CBound* bound, float (*viewMtx) [4])
{
    CPtrArray<CMapShadow*>* mapShadowArray = reinterpret_cast<CPtrArray<CMapShadow*>*>(Ptr(&MapMng, 0x21434));

    for (unsigned int i = 0; i < static_cast<unsigned int>(mapShadowArray->GetSize()); i++) {
        CMapShadow* shadow = (*mapShadowArray)[i];

        if (*reinterpret_cast<unsigned char*>(Ptr(shadow, static_cast<int>(target) + 0xF0)) == 0) {
            continue;
        }

        int model = *reinterpret_cast<int*>(Ptr(shadow, 0xC));
        Vec position;
        Mtx scaledShadowMtx;

        position.x = *reinterpret_cast<float*>(model + 0xC4);
        position.y = *reinterpret_cast<float*>(model + 0xD4);
        position.z = *reinterpret_cast<float*>(model + 0xE4);
        PSMTXScaleApply(reinterpret_cast<float(*)[4]>(Ptr(shadow, 0x78)), scaledShadowMtx, FLOAT_8032faf8,
                        FLOAT_8032faf8, FLOAT_8032faf0);

        if ((*reinterpret_cast<unsigned char*>(Ptr(shadow, 7)) == 1) ||
            (CheckFrustum__6CBoundFR3VecPA4_ff(bound, &position, scaledShadowMtx, FLOAT_8032fafc) != 0)) {
            SetShadow__12CMaterialManFR10CMapShadowPA4_fiUl(this, shadow, viewMtx, i, 0xFFFFFFFF);
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::InitVtxFmt(int, _GXCompType, int, _GXCompType, int, _GXCompType, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80041f8c
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::IncNumTevStage()
{
    unsigned int tevStage = *reinterpret_cast<unsigned int*>(Ptr(this, 0x60));
    *reinterpret_cast<unsigned int*>(Ptr(this, 0x60)) = ((tevStage & 0xFF) + 1) & 0xFF;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::GetTexMtxCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::GetTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80041fa4
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialMan::IncTexCoordIdCur()
{
    int texCoordId = *reinterpret_cast<int*>(Ptr(this, 0x124));
    *reinterpret_cast<int*>(Ptr(this, 0x124)) = texCoordId + 1;
    return texCoordId;
}

/*
 * --INFO--
 * PAL Address: 0x80041fb8
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialMan::IncTexMtxCur()
{
    int texMtx = *reinterpret_cast<int*>(Ptr(this, 0x120));
    *reinterpret_cast<int*>(Ptr(this, 0x120)) = texMtx + 3;
    return texMtx;
}

/*
 * --INFO--
 * PAL Address: 0x80041fcc
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterialMan::IncTexMapIdCur()
{
    int texMapId = *reinterpret_cast<int*>(Ptr(this, 0x11C));
    *reinterpret_cast<int*>(Ptr(this, 0x11C)) = texMapId + 1;
    return texMapId;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::GetTexMapIdCur()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80041fe0
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialMan::SetStdEnv()
{
    *reinterpret_cast<int*>(Ptr(this, 0x11C)) = *reinterpret_cast<int*>(Ptr(this, 0x128));
    *reinterpret_cast<int*>(Ptr(this, 0x134)) = *reinterpret_cast<int*>(Ptr(this, 0x128));
    *reinterpret_cast<int*>(Ptr(this, 0x120)) = *reinterpret_cast<int*>(Ptr(this, 0x12C));
    *reinterpret_cast<int*>(Ptr(this, 0x138)) = *reinterpret_cast<int*>(Ptr(this, 0x12C));
    *reinterpret_cast<int*>(Ptr(this, 0x124)) = *reinterpret_cast<int*>(Ptr(this, 0x130));
    *reinterpret_cast<int*>(Ptr(this, 0x13C)) = *reinterpret_cast<int*>(Ptr(this, 0x130));
    *reinterpret_cast<int*>(Ptr(this, 0x48)) = *reinterpret_cast<int*>(Ptr(this, 0x40));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::DecTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetTevBit(CMaterialMan::TEV_BIT)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::ErrorTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::ErrorTexMtxCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::ErrorTexMapIdCur()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003c49c
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void* dtor_8003C49C(void* material, short shouldDelete)
{
    if (material != 0) {
        __destroy_arr(Ptr(material, 0x10), (void*)__dt__10CTexScrollFv, 0x14, 4);
        if (shouldDelete > 0) {
            __dl__FPv(material);
        }
    }

    return material;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexScroll::~CTexScroll()
{
    if (m_type0 == 2) {
        void*& keyFrame0 = *reinterpret_cast<void**>(Ptr(this, 0xC));
        if (keyFrame0 != 0) {
            void*& table0 = *reinterpret_cast<void**>(Ptr(keyFrame0, 0x18));
            if (table0 != 0) {
                __dl__FPv(table0);
                table0 = 0;
            }

            void*& table1 = *reinterpret_cast<void**>(Ptr(keyFrame0, 0x1C));
            if (table1 != 0) {
                __dl__FPv(table1);
                table1 = 0;
            }

            void*& table2 = *reinterpret_cast<void**>(Ptr(keyFrame0, 0x20));
            if (table2 != 0) {
                __dl__FPv(table2);
                table2 = 0;
            }

            void*& table3 = *reinterpret_cast<void**>(Ptr(keyFrame0, 0x24));
            if (table3 != 0) {
                __dl__FPv(table3);
                table3 = 0;
            }

            __dl__FPv(keyFrame0);
            keyFrame0 = 0;
        }
    }

    if (m_type1 == 2) {
        void*& keyFrame1 = *reinterpret_cast<void**>(Ptr(this, 0x10));
        if (keyFrame1 != 0) {
            void*& table0 = *reinterpret_cast<void**>(Ptr(keyFrame1, 0x18));
            if (table0 != 0) {
                __dl__FPv(table0);
                table0 = 0;
            }

            void*& table1 = *reinterpret_cast<void**>(Ptr(keyFrame1, 0x1C));
            if (table1 != 0) {
                __dl__FPv(table1);
                table1 = 0;
            }

            void*& table2 = *reinterpret_cast<void**>(Ptr(keyFrame1, 0x20));
            if (table2 != 0) {
                __dl__FPv(table2);
                table2 = 0;
            }

            void*& table3 = *reinterpret_cast<void**>(Ptr(keyFrame1, 0x24));
            if (table3 != 0) {
                __dl__FPv(table3);
                table3 = 0;
            }

            __dl__FPv(keyFrame1);
            keyFrame1 = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c66c
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexScroll::CTexScroll()
{
    m_type0 = 0;
    m_type1 = 0;
    m_u0 = 0.0f;
    m_v0 = 0.0f;
    m_u1 = 0.0f;
    m_v1 = 0.0f;
}

/*
 * --INFO--
 * PAL Address: 0x8003dc38
 * PAL Size: 220b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterial::~CMaterial()
{
    *reinterpret_cast<void**>(this) = __vt__9CMaterial;

    int numTexture = static_cast<int>(*reinterpret_cast<unsigned short*>(Ptr(this, 0x18)));
    for (int i = 0; i < numTexture; i++) {
        unsigned char* textureRef = Ptr(this, 0x3C + (i << 2));
        ReleaseRef(*reinterpret_cast<void**>(textureRef));
        *reinterpret_cast<void**>(textureRef) = 0;
    }

    __destroy_arr(Ptr(this, 0x4C), (void*)__dt__10CTexScrollFv, 0x14, 4);
    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003dd14
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterial::CMaterial()
{
    __ct__4CRefFv(this);
    *reinterpret_cast<void**>(this) = __vt__9CMaterial;
    __construct_array(Ptr(this, 0x4C), __ct__10CTexScrollFv, __dt__10CTexScrollFv, 0x14, 4);
    memset(Ptr(this, 0x8C), 0, 0x10);
    *reinterpret_cast<int*>(Ptr(this, 0x9C)) = -1;
    *Ptr(this, 0xA0) = 4;
    *Ptr(this, 0xA1) = 1;
    *Ptr(this, 0xA2) = 0;
    *Ptr(this, 0xA4) = 0;
    *reinterpret_cast<void**>(Ptr(this, 0x3C)) = 0;
    *reinterpret_cast<void**>(Ptr(this, 0x40)) = 0;
    *reinterpret_cast<void**>(Ptr(this, 0x44)) = 0;
    *reinterpret_cast<void**>(Ptr(this, 0x48)) = 0;
    *Ptr(this, 0x34) = 0;
    *Ptr(this, 0x35) = 0;
    *Ptr(this, 0x36) = 0;
    *Ptr(this, 0xA5) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::GetMemoryStage()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003cdbc
 * PAL Size: 2748b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::Create(CChunkFile& chunkFile, CTextureSet* textureSet, CMaterialMan::TEV_BIT tevBit,
                          CLightPcs::CBumpLight* bumpLights)
{
    enum {
        CHUNK_MATL = 0x4D41544C,
        CHUNK_TIDX = 0x54494458,
        CHUNK_NAME = 0x4E414D45,
        CHUNK_ATTR = 0x41545242,
        CHUNK_BUMP = 0x42554D50,
        CHUNK_JIME = 0x4A494D45,
        CHUNK_WATR = 0x57415452,
        CHUNK_FUR  = 0x46555220,
        CHUNK_TSCL = 0x5453434C,
        CHUNK_TSDT = 0x54534454,
        CHUNK_UFRM = 0x5546524D,
        CHUNK_VFRM = 0x5646524D,
        CHUNK_UKEY = 0x554B4559,
        CHUNK_VKEY = 0x564B4559,
    };

    CMaterial* material = 0;
    CChunkFile::CChunk chunk;
    CPtrArray<CMaterial*>* materials = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8));

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk) != 0) {
        if (chunk.m_id != CHUNK_MATL) {
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk) != 0) {
            if (chunk.m_id == CHUNK_TIDX) {
                unsigned long materialIndex = 0;
                while (materialIndex < static_cast<unsigned long>(materials->GetSize())) {
                    if ((*materials)[materialIndex] == 0) {
                        break;
                    }
                    materialIndex++;
                }

                material = AllocMaterial();
                if (material == 0) {
                    continue;
                }

                *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) = static_cast<unsigned long>(tevBit);
                *reinterpret_cast<void**>(Ptr(material, 0x28)) = 0;
                *reinterpret_cast<unsigned short*>(Ptr(material, 0x18)) = 0;
                *reinterpret_cast<float*>(Ptr(material, 0x30)) = FLOAT_8032faf0;
                *reinterpret_cast<float*>(Ptr(material, 0x2C)) = FLOAT_8032faf0;
                *Ptr(material, 0xA7) = 0;
                *reinterpret_cast<unsigned short*>(Ptr(material, 0x18)) = static_cast<unsigned short>(chunk.m_arg0);

                if (*reinterpret_cast<unsigned short*>(Ptr(material, 0x18)) == 0) {
                    *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 1;
                } else {
                    for (int i = 0; i < static_cast<int>(static_cast<unsigned short>(chunk.m_arg0)); i++) {
                        *reinterpret_cast<unsigned short*>(Ptr(material, 0x1A + (i << 1))) =
                            static_cast<unsigned short>(chunkFile.Get4());
                    }
                    if (*reinterpret_cast<unsigned short*>(Ptr(material, 0x18)) == 2) {
                        *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 2;
                    }
                }

                if (materialIndex < static_cast<unsigned long>(materials->GetSize())) {
                    materials->SetAt(materialIndex, material);
                } else {
                    materials->Add(material);
                }
            } else if (chunk.m_id == CHUNK_NAME) {
                if (material != 0) {
                    strncpy(reinterpret_cast<char*>(Ptr(material, 8)), chunkFile.GetString(), 0x10);
                } else {
                    chunkFile.GetString();
                }
            } else if (chunk.m_id == CHUNK_ATTR) {
                unsigned int flags = chunkFile.Get4();
                if (material == 0) {
                    chunkFile.Get1();
                    chunkFile.Get1();
                    chunkFile.Get1();
                    chunkFile.Get1();
                    chunkFile.Get2();
                    chunkFile.Get2();
                    chunkFile.GetF4();
                    continue;
                }

                if ((flags & 1) != 0) {
                    *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 0x80;
                }
                if ((flags & 2) != 0) {
                    *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 0x10;
                }
                if ((flags & 4) != 0) {
                    *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 4;
                }
                if ((flags & 8) != 0) {
                    *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 0x100000;
                }

                *Ptr(material, 0xA0) = chunkFile.Get1();
                *Ptr(material, 0xA1) = chunkFile.Get1();
                chunkFile.Get1();
                chunkFile.Get1();
                *Ptr(material, 0xA6) = static_cast<unsigned char>(chunkFile.Get2());
                chunkFile.Get2();
                chunkFile.GetF4();
            } else if (chunk.m_id == CHUNK_FUR) {
                unsigned short textureIndex = chunkFile.Get2();
                if (material != 0) {
                    AddTextureIndex(material, textureIndex);
                    *Ptr(material, 0xA7) = 1;
                }
            } else if (chunk.m_id == CHUNK_BUMP) {
                unsigned char bumpLightDirect = 0;
                if (chunk.m_version == 1) {
                    bumpLightDirect = chunkFile.Get1();
                    if (material != 0) {
                        *Ptr(material, 0xA1) = chunkFile.Get1();
                    } else {
                        chunkFile.Get1();
                    }
                    chunkFile.Get2();
                }

                unsigned short texture0 = chunkFile.Get2();
                unsigned short texture1 = chunkFile.Get2();
                unsigned short bumpIndex = chunkFile.Get2();
                unsigned short texture2 = chunkFile.Get2();
                float scaleU = chunkFile.GetF4();
                float scaleV = chunkFile.GetF4();
                unsigned char a6 = static_cast<unsigned char>(chunkFile.Get4());
                unsigned int rgba = chunkFile.Get4();

                if (material != 0) {
                    AddTextureIndex(material, texture0);
                    AddTextureIndex(material, texture1);
                    AddTextureIndex(material, texture2);

                    *reinterpret_cast<float*>(Ptr(material, 0x30)) = FLOAT_8032faf0 / scaleU;
                    *reinterpret_cast<float*>(Ptr(material, 0x2C)) = FLOAT_8032faf0 / scaleV;
                    *Ptr(material, 0xA6) = a6;
                    SetMaterialColor(material, rgba);
                    *Ptr(material, 0xA2) = 1;

                    CLightPcs::CBumpLight* bumpLight = bumpLights;
                    if (bumpLight == 0) {
                        bumpLight = reinterpret_cast<CLightPcs::CBumpLight*>(0x8026B584 + (bumpIndex * 0x138));
                        *Ptr(material, 0xA3) = (bumpLightDirect == 0) ? 0 : 1;
                    } else {
                        *Ptr(material, 0xA3) = 1;
                    }

                    *reinterpret_cast<CLightPcs::CBumpLight**>(Ptr(material, 0x28)) = bumpLight;
                    *Ptr(bumpLight, 0xB1) = *Ptr(material, 0xA2);
                    *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 4;
                }
            } else if (chunk.m_id == CHUNK_JIME) {
                unsigned short texture0 = chunkFile.Get2();
                unsigned short texture1 = chunkFile.Get2();
                unsigned short bumpIndex = chunkFile.Get2();
                unsigned char a1 = chunkFile.Get1();
                unsigned char useJimen = chunkFile.Get1();
                float scaleU = chunkFile.GetF4();
                float scaleV = chunkFile.GetF4();
                chunkFile.Get4();
                unsigned int rgba = chunkFile.Get4();

                if (material != 0) {
                    AddTextureIndex(material, texture0);
                    AddTextureIndex(material, texture1);
                    *Ptr(material, 0xA1) = a1;
                    if (useJimen != 0) {
                        *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 0x20000;
                    }
                    *reinterpret_cast<float*>(Ptr(material, 0x30)) = FLOAT_8032faf0 / scaleU;
                    *reinterpret_cast<float*>(Ptr(material, 0x2C)) = FLOAT_8032faf0 / scaleV;
                    *Ptr(material, 0xA2) = 3;

                    CLightPcs::CBumpLight* bumpLight =
                        reinterpret_cast<CLightPcs::CBumpLight*>(0x8026B584 + (bumpIndex * 0x138));
                    *reinterpret_cast<CLightPcs::CBumpLight**>(Ptr(material, 0x28)) = bumpLight;
                    *Ptr(bumpLight, 0xB1) = *Ptr(material, 0xA2);
                    *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 0x4000;
                    SetMaterialColor(material, rgba);
                    *Ptr(material, 0xA3) = 1;
                }
            } else if (chunk.m_id == CHUNK_WATR) {
                unsigned short texture0 = chunkFile.Get2();
                unsigned short texture1 = chunkFile.Get2();
                unsigned short bumpIndex = chunkFile.Get2();
                unsigned char waterMode = chunkFile.Get1();
                unsigned char a1 = chunkFile.Get1();
                float scaleU = chunkFile.GetF4();
                float scaleV = chunkFile.GetF4();
                chunkFile.Get4();
                unsigned int rgba = chunkFile.Get4();

                if (material != 0) {
                    AddTextureIndex(material, texture0);
                    AddTextureIndex(material, texture1);
                    *Ptr(material, 0xA1) = a1;
                    *reinterpret_cast<float*>(Ptr(material, 0x30)) = FLOAT_8032faf0 / scaleU;
                    *reinterpret_cast<float*>(Ptr(material, 0x2C)) = FLOAT_8032faf0 / scaleV;
                    *Ptr(material, 0xA2) = 2;

                    CLightPcs::CBumpLight* bumpLight =
                        reinterpret_cast<CLightPcs::CBumpLight*>(0x8026B584 + (bumpIndex * 0x138));
                    *reinterpret_cast<CLightPcs::CBumpLight**>(Ptr(material, 0x28)) = bumpLight;
                    *Ptr(bumpLight, 0xB1) = *Ptr(material, 0xA2);
                    *Ptr(material, 0xA0) = 4;
                    SetMaterialColor(material, rgba);

                    if ((waterMode == 0) && (*Ptr(material, 0xA1) == 0)) {
                        *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 8;
                    } else {
                        *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 0x80000;
                    }
                }
            } else if (chunk.m_id == CHUNK_TSCL) {
                if (material == 0) {
                    continue;
                }

                if (chunk.m_version == 1) {
                    CMapKeyFrame* keyFrameU = 0;
                    CMapKeyFrame* keyFrameV = 0;

                    chunkFile.PushChunk();
                    while (chunkFile.GetNextChunk(chunk) != 0) {
                        if (chunk.m_id == CHUNK_UFRM) {
                            keyFrameU = AllocMapKeyFrame(0xDD3);
                            ReadFrame__12CMapKeyFrameFR10CChunkFilei(keyFrameU, &chunkFile);
                        } else if (chunk.m_id == CHUNK_VFRM) {
                            keyFrameV = AllocMapKeyFrame(0xDDD);
                            ReadFrame__12CMapKeyFrameFR10CChunkFilei(keyFrameV, &chunkFile);
                        } else if (chunk.m_id == CHUNK_UKEY) {
                            ReadKey__12CMapKeyFrameFR10CChunkFilei(
                                keyFrameU, &chunkFile, static_cast<char>(chunk.m_arg0));
                        } else if (chunk.m_id == CHUNK_VKEY) {
                            ReadKey__12CMapKeyFrameFR10CChunkFilei(
                                keyFrameV, &chunkFile, static_cast<char>(chunk.m_arg0));
                        } else if (chunk.m_id == CHUNK_TSDT) {
                            unsigned int slot = chunkFile.Get2() & 0xFFFF;
                            chunkFile.Get2();

                            if (keyFrameU == 0) {
                                float valueU = chunkFile.GetF4();
                                *reinterpret_cast<float*>(Ptr(material, 0x58 + (slot * 0x14))) = valueU;
                                *Ptr(material, 0x4C + (slot * 0x14)) = (valueU == FLOAT_8032faf4) ? 0 : 1;
                            } else {
                                chunkFile.GetF4();
                                *reinterpret_cast<CMapKeyFrame**>(Ptr(material, 0x58 + (slot * 0x14))) = keyFrameU;
                                *Ptr(material, 0x4C + (slot * 0x14)) = 2;
                            }

                            if (keyFrameV == 0) {
                                float valueV = chunkFile.GetF4();
                                *reinterpret_cast<float*>(Ptr(material, 0x5C + (slot * 0x14))) = valueV;
                                *Ptr(material, 0x4D + (slot * 0x14)) = (valueV == FLOAT_8032faf4) ? 0 : 1;
                            } else {
                                chunkFile.GetF4();
                                *reinterpret_cast<CMapKeyFrame**>(Ptr(material, 0x5C + (slot * 0x14))) = keyFrameV;
                                *Ptr(material, 0x4D + (slot * 0x14)) = 2;
                            }
                        }
                    }
                    chunkFile.PopChunk();
                } else {
                    unsigned int slot = chunkFile.Get2() & 0xFFFF;
                    chunkFile.Get2();
                    float valueU = chunkFile.GetF4();
                    float valueV = chunkFile.GetF4();

                    *reinterpret_cast<float*>(Ptr(material, 0x58 + (slot * 0x14))) = valueU;
                    *reinterpret_cast<float*>(Ptr(material, 0x5C + (slot * 0x14))) = valueV;
                    if (FLOAT_8032faf4 != valueU) {
                        *Ptr(material, 0x4C + (slot * 0x14)) = 1;
                    }
                    if (FLOAT_8032faf4 != valueV) {
                        *Ptr(material, 0x4D + (slot * 0x14)) = 1;
                    }
                }
            }
        }
        chunkFile.PopChunk();
    }
    chunkFile.PopChunk();
    SetTextureSet(textureSet);
}

/*
 * --INFO--
 * PAL Address: 0x8003ca30
 * PAL Size: 908b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::SetTextureSet(CTextureSet* textureSet)
{
    CPtrArray<CMaterial*>* materialArray = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8));
    unsigned long materialIndex = 0;

    while (materialIndex < static_cast<unsigned long>(materialArray->GetSize())) {
        CMaterial* material = (*materialArray)[materialIndex];
        if (material != 0) {
            unsigned short numTexture = *reinterpret_cast<unsigned short*>(Ptr(material, 0x18));
            if (numTexture == 0) {
                *reinterpret_cast<unsigned long*>(Ptr(material, 0x24)) |= 1;
            } else {
                unsigned char* textureIndexPtr = Ptr(material, 0x1A);
                unsigned char* texturePtr = Ptr(material, 0x3C);

                for (int i = 0; i < numTexture; i++) {
                    ReleaseRef(*reinterpret_cast<void**>(texturePtr));
                    *reinterpret_cast<void**>(texturePtr) = 0;

                    if (textureSet != 0) {
                        CTexture* texture = 0;
                        short textureIndex = *reinterpret_cast<short*>(textureIndexPtr);
                        if (textureIndex >= 0) {
                            CPtrArray<CTexture*>* textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(Ptr(textureSet, 8));
                            unsigned long textureCount = static_cast<unsigned long>(textureArray->GetSize());
                            if (static_cast<unsigned long>(textureIndex) < textureCount) {
                                texture = (*textureArray)[static_cast<unsigned long>(textureIndex)];
                            }
                        }

                        *reinterpret_cast<CTexture**>(texturePtr) = texture;
                        if (texture != 0) {
                            *reinterpret_cast<int*>(Ptr(texture, 4)) += 1;

                            unsigned long& flags = *reinterpret_cast<unsigned long*>(Ptr(material, 0x24));
                            int format = *reinterpret_cast<int*>(Ptr(texture, 0x60));
                            if ((format == 9) || (format == 8)) {
                                flags |= 0x200;
                            } else if (format == 1) {
                                flags |= 0x400;
                            }

                            if (*reinterpret_cast<char*>(Ptr(texture, 0x71)) != 0) {
                                flags |= 0x800;
                            }
                        }
                    }

                    textureIndexPtr += 2;
                    texturePtr += 4;
                }

                if ((*reinterpret_cast<char*>(Ptr(material, 0xA2)) != 0) &&
                    (numTexture > 1) &&
                    (*reinterpret_cast<void**>(Ptr(material, 0x3C)) != 0) &&
                    (*reinterpret_cast<void**>(Ptr(material, 0x40)) != 0)) {
                    void* texture0 = *reinterpret_cast<void**>(Ptr(material, 0x3C));
                    void* texture1 = *reinterpret_cast<void**>(Ptr(material, 0x40));

                    unsigned int scaleU =
                        *reinterpret_cast<unsigned int*>(Ptr(texture0, 0x64)) /
                        *reinterpret_cast<unsigned int*>(Ptr(texture1, 0x64));
                    int uShift = HighestSetBit(scaleU);
                    *reinterpret_cast<char*>(Ptr(material, 0x34)) = (uShift == -1) ? 0 : static_cast<char>(uShift);

                    unsigned int scaleV =
                        *reinterpret_cast<unsigned int*>(Ptr(texture0, 0x68)) /
                        *reinterpret_cast<unsigned int*>(Ptr(texture1, 0x68));
                    int vShift = HighestSetBit(scaleV);
                    *reinterpret_cast<char*>(Ptr(material, 0x35)) = (vShift == -1) ? 0 : static_cast<char>(vShift);
                }
            }
        }

        materialIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c2f0
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::SetPartFromTextureSet(CTextureSet* textureSet, int pdtSlotIndex)
{
    CPtrArray<CTexture*>* textureArray = reinterpret_cast<CPtrArray<CTexture*>*>(Ptr(textureSet, 8));
    CPtrArray<CMaterial*>* materialArray = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8));
    unsigned long textureIndex = 0;

    while (true) {
        unsigned long textureCount = static_cast<unsigned long>(textureArray->GetSize());
        if (textureCount <= textureIndex) {
            return;
        }

        if ((*textureArray)[textureIndex] != 0) {
            unsigned long materialIndex = textureIndex + 1;
            unsigned long materialCount = static_cast<unsigned long>(materialArray->GetSize());
            if ((materialIndex < materialCount) &&
                ((*materialArray)[materialIndex] != 0)) {
                textureIndex++;
                continue;
            }

            unsigned char* material = reinterpret_cast<unsigned char*>(
                _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                    &Memory,
                    0xA8,
                    *reinterpret_cast<CMemory::CStage**>(MaterialMan + 0x218),
                    s_materialman_cpp,
                    0xEE4,
                    0));

            if (material != 0) {
                __ct__4CRefFv(material);
                *reinterpret_cast<void**>(material) = __vt__9CMaterial;
                __construct_array(
                    material + 0x4C,
                    __ct__10CTexScrollFv,
                    __dt__10CTexScrollFv,
                    0x14,
                    4);
                memset(material + 8, 0, 0x10);
                *reinterpret_cast<int*>(material + 0x9C) = -1;
                material[0xA0] = 4;
                material[0xA1] = 1;
                material[0xA2] = 0;
                material[0xA4] = 0;
                *reinterpret_cast<int*>(material + 0x3C) = 0;
                *reinterpret_cast<void**>(material + 0x40) = 0;
                *reinterpret_cast<int*>(material + 0x44) = 0;
                *reinterpret_cast<void**>(material + 0x48) = 0;
                material[0x34] = 0;
                material[0x35] = 0;
                material[0x36] = 0;
                material[0xA5] = 0;
            }

            *reinterpret_cast<int*>(material + 0x24) = -0xACE10;
            *reinterpret_cast<void**>(material + 0x28) = 0;
            *reinterpret_cast<unsigned short*>(material + 0x18) = 1;
            *reinterpret_cast<float*>(material + 0x30) = 1.0f;
            *reinterpret_cast<float*>(material + 0x2C) = 1.0f;
            material[0xA7] = 0;
            *reinterpret_cast<unsigned short*>(material + 0x1A) = static_cast<unsigned short>(textureIndex);
            *reinterpret_cast<int*>(material + 0x9C) = pdtSlotIndex;

            materialCount = static_cast<unsigned long>(materialArray->GetSize());
            if (materialIndex < materialCount) {
                materialArray->SetAt(materialIndex, reinterpret_cast<CMaterial*>(material));
            } else {
                materialArray->Add(reinterpret_cast<CMaterial*>(material));
            }
        }

        textureIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003dc10
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterial::Create(unsigned long tag, CMaterialMan::TEV_BIT tevBit)
{
    *reinterpret_cast<unsigned long*>(Ptr(this, 0x24)) = tag;
    *reinterpret_cast<void**>(Ptr(this, 0x28)) = 0;
    *reinterpret_cast<unsigned short*>(Ptr(this, 0x18)) = 0;
    *reinterpret_cast<float*>(Ptr(this, 0x30)) = 1.0f;
    *reinterpret_cast<float*>(Ptr(this, 0x2C)) = 1.0f;
    *Ptr(this, 0xA7) = 0;
    *reinterpret_cast<unsigned short*>(Ptr(this, 0x18)) = static_cast<unsigned short>(tevBit);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterial::IncNumTexture()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003c1b8
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::ReleaseTag(CTextureSet* textureSet, int pdtSlotIndex, CAmemCacheSet* amemCacheSet)
{
    void* materials = Ptr(this, 8);
    unsigned long index = 0;

    while (index < UnkMaterialSetGetter(materials)) {
        CMaterial** materialItems = *reinterpret_cast<CMaterial***>(Ptr(materials, 0xC));
        CMaterial* material = materialItems[index];
        if ((material != 0) && (*reinterpret_cast<int*>(Ptr(material, 0x9C)) == pdtSlotIndex)) {
            int numTexture = static_cast<int>(*reinterpret_cast<unsigned short*>(Ptr(material, 0x18)));
            unsigned char* textureIndex = Ptr(material, 0x1A);
            unsigned char* textureRef = Ptr(material, 0x3C);

            for (int i = 0; i < numTexture; i++) {
                void* object = *reinterpret_cast<void**>(textureRef);
                if (object != 0) {
                    int& refCount = *reinterpret_cast<int*>(Ptr(object, 4));
                    int nextRefCount = refCount - 1;
                    refCount = nextRefCount;
                    if (nextRefCount == 0) {
                        void** vtable = *reinterpret_cast<void***>(object);
                        reinterpret_cast<VirtualDtorFn>(vtable[2])(object, 1);
                    }
                    *reinterpret_cast<void**>(textureRef) = 0;
                }

                textureSet->ReleaseTextureIdx(static_cast<int>(*reinterpret_cast<short*>(textureIndex)), amemCacheSet);
                *reinterpret_cast<void**>(textureRef) = 0;
                textureRef += 4;
                textureIndex += 2;
            }

            int& refCount = *reinterpret_cast<int*>(Ptr(material, 4));
            int nextRefCount = refCount - 1;
            refCount = nextRefCount;
            if (nextRefCount == 0) {
                void** vtable = *reinterpret_cast<void***>(material);
                reinterpret_cast<VirtualDtorFn>(vtable[2])(material, 1);
            }
            materialItems[index] = 0;
        }

        index++;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialSet::AddMaterial(CMaterial*, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8003d9f0
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMaterial::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
        &Memory,
        size,
        *reinterpret_cast<CMemory::CStage**>(MaterialMan + 0x218),
        file,
        line,
        0);
}

/*
 * --INFO--
 * PAL Address: 0x8003d878
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMaterialSet::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
        &Memory,
        size,
        *reinterpret_cast<CMemory::CStage**>(MaterialMan + 0x218),
        file,
        line,
        0);
}

/*
 * --INFO--
 * PAL Address: 0x8003d8c0
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialSet::~CMaterialSet()
{
    CPtrArray<CMaterial*>* const materials = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8));
    *reinterpret_cast<void**>(this) = &PTR_PTR_s_CMaterialSet_801e9bbc;

    for (unsigned long i = 0; i < UnkMaterialSetGetter(materials); i++) {
        CMaterial* const material = (*materials)[i];
        if (material != 0) {
            void** const vtable = *reinterpret_cast<void***>(material);
            reinterpret_cast<VirtualDtorFn>(vtable[2])(material, 1);
        }
    }

    materials->RemoveAll();
    materials->~CPtrArray<CMaterial*>();
    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003d998
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMaterialSet::CMaterialSet()
{
    __ct__4CRefFv(this);
    *reinterpret_cast<void**>(this) = &PTR_PTR_s_CMaterialSet_801e9bbc;

    CPtrArray<CMaterial*>* const materials = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8));
    materials->m_size = 0;
    materials->m_numItems = 0;
    materials->m_defaultSize = 0x10;
    materials->m_items = 0;
    materials->m_stage = 0;
    materials->m_growCapacity = 1;
    materials->SetStage(*reinterpret_cast<CMemory::CStage**>(MaterialMan + 0x218));
}

/*
 * --INFO--
 * PAL Address: 0x8003c71c
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::CacheDumpTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    int material = reinterpret_cast<int>(
        (*reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8)))[static_cast<unsigned long>(materialIndex)]);
    if (material == 0) {
        return;
    }

    int numTexture = static_cast<int>(*reinterpret_cast<unsigned short*>(Ptr(reinterpret_cast<void*>(material), 0x18)));
    for (int i = 0; i < numTexture; i++) {
        CTexture* texture = *reinterpret_cast<CTexture**>(Ptr(reinterpret_cast<void*>(material), 0x3C));
        if (texture != 0) {
            texture->CacheUnLoadTexture(amemCacheSet);
        }
        material += 4;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c7a0
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::CacheLoadTexture(int materialIndex, CAmemCacheSet* amemCacheSet)
{
    int material = reinterpret_cast<int>(
        (*reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8)))[static_cast<unsigned long>(materialIndex)]);
    if (material == 0) {
        return;
    }

    int numTexture = static_cast<int>(*reinterpret_cast<unsigned short*>(Ptr(reinterpret_cast<void*>(material), 0x18)));
    for (int i = 0; i < numTexture; i++) {
        CTexture* texture = *reinterpret_cast<CTexture**>(Ptr(reinterpret_cast<void*>(material), 0x3C));
        if (texture != 0) {
            texture->CacheLoadTexture(amemCacheSet);
        }
        material += 4;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c824
 * PAL Size: 172b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned short CMaterialSet::FindTexName(char* textureName, long* textureIndexOut)
{
    unsigned long materialIndex = 0;

    while (true) {
        if (UnkMaterialSetGetter(Ptr(this, 8)) <= materialIndex) {
            return 0xFFFF;
        }

        int material = reinterpret_cast<int>(
            (*reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8)))[materialIndex]);
        if (material != 0) {
            int numTexture = static_cast<int>(*reinterpret_cast<unsigned short*>(Ptr(reinterpret_cast<void*>(material), 0x18)));
            int slot = 0;

            while (slot < numTexture) {
                if (CheckName__8CTextureFPc(*reinterpret_cast<CTexture**>(Ptr(reinterpret_cast<void*>(material), 0x3C)),
                                            textureName)) {
                    if (textureIndexOut != 0) {
                        *textureIndexOut = slot;
                    }
                    return static_cast<unsigned short>(materialIndex);
                }
                slot++;
                material += 4;
            }
        }
        materialIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c8d0
 * PAL Size: 352b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::Calc()
{
    CPtrArray<CMaterial*>* materialArray = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8));
    unsigned long materialIndex = 0;

    while (materialIndex < static_cast<unsigned long>(materialArray->GetSize())) {
        unsigned char* material = reinterpret_cast<unsigned char*>((*materialArray)[materialIndex]);
        if (material != 0) {
            unsigned char* texScroll = material + 0x4C;
            for (int i = 0; i < 4; i++) {
                if (texScroll[0] == 1) {
                    float& offsetU = *reinterpret_cast<float*>(texScroll + 4);
                    offsetU += *reinterpret_cast<float*>(texScroll + 0xC);
                    if (offsetU > 1.0f) {
                        offsetU -= 1.0f;
                    } else if (offsetU < 0.0f) {
                        offsetU += 1.0f;
                    }
                } else if (texScroll[0] == 2) {
                    CMapKeyFrame* keyFrameU = *reinterpret_cast<CMapKeyFrame**>(texScroll + 0xC);
                    *reinterpret_cast<float*>(texScroll + 4) = keyFrameU->Get();
                    keyFrameU->Calc();
                }

                if (texScroll[1] == 1) {
                    float& offsetV = *reinterpret_cast<float*>(texScroll + 8);
                    offsetV += *reinterpret_cast<float*>(texScroll + 0x10);
                    if (offsetV > 1.0f) {
                        offsetV -= 1.0f;
                    } else if (offsetV < 0.0f) {
                        offsetV += 1.0f;
                    }
                } else if (texScroll[1] == 2) {
                    CMapKeyFrame* keyFrameV = *reinterpret_cast<CMapKeyFrame**>(texScroll + 0x10);
                    *reinterpret_cast<float*>(texScroll + 8) = keyFrameV->Get();
                    keyFrameV->Calc();
                }

                texScroll += 0x14;
            }
        }

        materialIndex++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003c690
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CMaterialSet::Find(char* name)
{
    CPtrArray<CMaterial*>* materialArray = reinterpret_cast<CPtrArray<CMaterial*>*>(Ptr(this, 8));
    unsigned long index = 0;

    do {
        CMaterial* material = (*materialArray)[index];
        if ((material != 0) && (strcmp(reinterpret_cast<char*>(Ptr(material, 8)), name) == 0)) {
            return index;
        }
        index++;
    } while (index < static_cast<unsigned long>(materialArray->GetSize()));

    return 0xFFFFFFFF;
}

/*
 * --INFO--
 * PAL Address: 0x8003da38
 * PAL Size: 472b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CMaterial::Set(_GXTexMapID texMapId)
{
    Mtx texMtx;
    PSMTXIdentity(texMtx);

    bool hasDualScroll = false;
    if ((*reinterpret_cast<unsigned short*>(Ptr(this, 0x18)) == 2) &&
        (FLOAT_8032faf4 == *reinterpret_cast<float*>(Ptr(this, 0x50))) &&
        (FLOAT_8032faf4 == *reinterpret_cast<float*>(Ptr(this, 0x54))) &&
        ((FLOAT_8032faf4 != *reinterpret_cast<float*>(Ptr(this, 0x64))) ||
         (FLOAT_8032faf4 != *reinterpret_cast<float*>(Ptr(this, 0x68))))) {
        hasDualScroll = true;
    }

    unsigned char* textureSlot = Ptr(this, 0x3C);
    unsigned char* scrollData = Ptr(this, 0x4C);
    int textureCount = static_cast<int>(*reinterpret_cast<unsigned short*>(Ptr(this, 0x18)));
    for (int i = 0; i < textureCount; i++) {
        CTexture* texture = *reinterpret_cast<CTexture**>(textureSlot);
        if ((texture != 0) && ((*Ptr(this, 0xA7) == 0) || (i < 1))) {
            TextureMan.SetTexture(texMapId, texture);
            texMapId = static_cast<_GXTexMapID>(static_cast<int>(texMapId) + 1);

            float scrollU = *reinterpret_cast<float*>(scrollData + 4);
            float scrollV = *reinterpret_cast<float*>(scrollData + 8);
            if ((FLOAT_8032faf4 != scrollU) || ((FLOAT_8032faf4 != scrollV) || hasDualScroll)) {
                unsigned int& texMtxCur = *reinterpret_cast<unsigned int*>(MaterialMan + 0x120);
                unsigned int& texCoordCur = *reinterpret_cast<unsigned int*>(MaterialMan + 0x124);
                texMtx[0][3] = scrollU;
                texMtx[1][3] = scrollV;

                if (i == 0) {
                    *reinterpret_cast<unsigned int*>(MaterialMan + 0x48) |= 0x20;
                    *reinterpret_cast<unsigned int*>(MaterialMan + 0x144) = texMtxCur;
                    *reinterpret_cast<unsigned int*>(MaterialMan + 0x148) = texCoordCur;
                    GXLoadTexMtxImm(texMtx, texMtxCur, GX_MTX2x4);
                    GXSetTexCoordGen2(
                        static_cast<GXTexCoordID>(texCoordCur),
                        GX_TG_MTX2x4,
                        GX_TG_TEX0,
                        texMtxCur,
                        GX_FALSE,
                        0x7D);
                } else {
                    *reinterpret_cast<unsigned int*>(MaterialMan + 0x48) |= 0x40;
                    *reinterpret_cast<unsigned int*>(MaterialMan + 0x150) = texMtxCur;
                    *reinterpret_cast<unsigned int*>(MaterialMan + 0x154) = texCoordCur;
                    GXLoadTexMtxImm(texMtx, texMtxCur, GX_MTX2x4);
                    GXSetTexCoordGen2(
                        static_cast<GXTexCoordID>(texCoordCur),
                        GX_TG_MTX2x4,
                        GX_TG_TEX1,
                        texMtxCur,
                        GX_FALSE,
                        0x7D);
                }

                texMtxCur += 3;
                texCoordCur += 1;
            }
        }

        textureSlot += 4;
        scrollData += 0x14;
    }

    return static_cast<int>(texMapId);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterial::SetTevBit(CMaterialMan::TEV_BIT)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterial::GetNumTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterial::SetTag(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterial::AddTextureIdx(int, int)
{
	// TODO
}
