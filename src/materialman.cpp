#include "ffcc/materialman.h"
#include "ffcc/textureman.h"

#include <string.h>

extern "C" unsigned long UnkMaterialSetGetter(void*);

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
        if (materialItems == 0) {
            break;
        }

        CMaterial* material = materialItems[index];
        if ((material != 0) && (*reinterpret_cast<int*>(Ptr(material, 0x9C)) == pdtSlotIndex)) {
            int numTexture = static_cast<int>(*reinterpret_cast<unsigned short*>(Ptr(material, 0x18)));

            for (int i = 0; i < numTexture; i++) {
                void*& textureRef = *reinterpret_cast<void**>(Ptr(material, 0x3C + (i * 4)));
                if (textureRef != 0) {
                    ReleaseRef(textureRef);
                    textureRef = 0;
                }

                short textureIndex = *reinterpret_cast<short*>(Ptr(material, 0x1A + (i * 2)));
                textureSet->ReleaseTextureIdx(static_cast<int>(textureIndex), amemCacheSet);
                textureRef = 0;
            }

            ReleaseRef(material);
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
