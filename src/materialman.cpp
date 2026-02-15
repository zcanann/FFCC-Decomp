#include "ffcc/materialman.h"
#include "ffcc/textureman.h"

#include <string.h>

extern "C" unsigned long UnkMaterialSetGetter(void*);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void __dla__FPv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void __ct__10CTexScrollFv(void*);
extern "C" void __dt__10CTexScrollFv(void*, int);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern "C" void* __vt__9CMaterial[];
extern CMemory Memory;
extern unsigned char MaterialMan[];

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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::Quit()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetObjMatrix(float (*) [4], float (*) [4])
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::IncNumTevStage()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::IncTexCoordIdCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::IncTexMtxCur()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::IncTexMapIdCur()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CMaterialMan::SetStdEnv()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
CTexScroll::~CTexScroll()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexScroll::CTexScroll()
{
	// TODO
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
 * PAL Address: 0x8003c2f0
 * PAL Size: 428b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMaterialSet::SetPartFromTextureSet(CTextureSet* textureSet, int pdtSlotIndex)
{
    unsigned long textureIndex = 0;

    while (true) {
        void* textures = Ptr(textureSet, 8);
        unsigned long textureCount = UnkMaterialSetGetter(textures);
        if (textureCount <= textureIndex) {
            return;
        }

        void** textureItems = *reinterpret_cast<void***>(Ptr(textures, 0xC));
        if (textureItems[textureIndex] != 0) {
            void* materials = Ptr(this, 8);
            unsigned long materialIndex = textureIndex + 1;
            unsigned long materialCount = UnkMaterialSetGetter(materials);
            if ((materialIndex < materialCount) &&
                ((*reinterpret_cast<void***>(Ptr(materials, 0xC)))[materialIndex] != 0)) {
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

            if (materialIndex < materialCount) {
                SetAtPtrArrayMaterial(materials, materialIndex, material);
            } else {
                AddPtrArrayMaterial(materials, material);
            }
        }

        textureIndex++;
    }
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
 * PAL Address: 0x8003c690
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned long CMaterialSet::Find(char* name)
{
    void* materials = Ptr(this, 8);
    unsigned long index = 0;

    while (index < UnkMaterialSetGetter(materials)) {
        CMaterial** materialItems = *reinterpret_cast<CMaterial***>(Ptr(materials, 0xC));
        if (materialItems != 0) {
            CMaterial* material = materialItems[index];
            if ((material != 0) && (strcmp(reinterpret_cast<char*>(Ptr(material, 8)), name) == 0)) {
                return index;
            }
        }

        index++;
    }

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
