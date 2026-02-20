#include "ffcc/materialman.h"
#include "ffcc/textureman.h"

#include <dolphin/mtx.h>

#include <string.h>

extern "C" unsigned long UnkMaterialSetGetter(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void __dla__FPv(void*);
extern "C" void __dl__FPv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void __ct__10CTexScrollFv(void*);
extern "C" void __dt__10CTexScrollFv(void*, int);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void __destroy_arr(void*, void*, unsigned long, unsigned long);
extern "C" int CheckName__8CTextureFPc(CTexture*, char*);
class CMapKeyFrame;
extern "C" float Get__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" void Calc__12CMapKeyFrameFv(CMapKeyFrame*);
extern "C" void* __vt__9CMaterial[];
extern "C" void* PTR_PTR_s_CMaterialSet_801e9bbc;
extern CMemory Memory;
extern unsigned char MaterialMan[];
extern float FLOAT_8032faf0;
extern float FLOAT_8032faf4;
static const char s_materialStageName[] = "material";

class CMapKeyFrame
{
public:
    float Get();
    void Calc();
};

namespace {
template <class T>
class CPtrArray
{
public:
    unsigned long m_size;
    unsigned long m_numItems;
    unsigned long m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    int GetSize();
    int Add(T item);
    ~CPtrArray();
    void RemoveAll();
    void SetStage(CMemory::CStage* stage);
    void SetAt(unsigned long index, T item);
    T operator[](unsigned long index);
};

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
    void** items;
    CMemory::CStage* stage;
    int growCapacity;
};

static int AddPtrArrayMaterial(void* ptrArray, void* item)
{
    RawPtrArray* array = reinterpret_cast<RawPtrArray*>(ptrArray);

    if (array->size < (array->numItems + 1)) {
        if (array->size == 0) {
            array->size = 0x10;
        } else {
            array->size = array->size << 1;
        }

        void** newItems = reinterpret_cast<void**>(
            _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                &Memory,
                array->size << 2,
                array->stage,
                s_collection_ptrarray_h,
                0xFA,
                0));
        if (newItems == 0) {
            return 0;
        }

        if (array->items != 0) {
            memcpy(newItems, array->items, array->numItems << 2);
            __dla__FPv(array->items);
        }
        array->items = newItems;
    }

    array->items[array->numItems] = item;
    array->numItems++;
    return 1;
}

static void SetAtPtrArrayMaterial(void* ptrArray, unsigned long index, void* item)
{
    RawPtrArray* array = reinterpret_cast<RawPtrArray*>(ptrArray);
    if (array->items != 0) {
        array->items[index] = item;
    }
}

static int HighestSetBit(unsigned int value)
{
    for (int bit = 31; bit >= 0; bit--) {
        if ((value & (1u << bit)) != 0) {
            return bit;
        }
    }
    return -1;
}
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::addtev_bump_jimen(_GXTevScale)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetShadowBound(CMapShadow::TARGET, CBound*, float (*) [4])
{
	// TODO
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
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::GetMemoryStage()
{
	// TODO
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
