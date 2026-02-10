#include "ffcc/mapmesh.h"

#include <dolphin/gx.h>

class CMaterial;

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);
extern char MaterialMan[];
extern unsigned char MapMng[];

extern "C" {
void SetBlendMode__12CMaterialManFP12CMaterialSeti(void* materialMan, CMaterialSet* materialSet, unsigned int materialIdx);
void SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(void* materialMan, CMaterialSet* materialSet,
                                                                 unsigned int materialIdx, int materialPart,
                                                                 int tevScale);
void SetMaterialPart__12CMaterialManFP12CMaterialSetii(void* materialMan, CMaterialSet* materialSet,
                                                        unsigned int materialIdx, int partIdx);
void SetMaterialCharaShadow__12CMaterialManFP9CMaterial(void* materialMan, void* material);
unsigned short FindTexName__12CMaterialSetFPcPl(CMaterialSet* materialSet, char* textureName, long* outIndex);
void CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet(CMaterialSet* materialSet, unsigned int materialIdx,
                                                         CAmemCacheSet* cacheSet);
void CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet(CMaterialSet* materialSet, unsigned int materialIdx,
                                                         CAmemCacheSet* cacheSet);
}

template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    int m_size;
    int m_numItems;
    int m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    T GetAt(unsigned long index);
    T operator[](unsigned long index);
};

namespace {
static inline unsigned char* Ptr(CMapMesh* self, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(self) + offset;
}

static inline void*& PtrAt(CMapMesh* self, unsigned int offset)
{
    return *reinterpret_cast<void**>(Ptr(self, offset));
}

static inline int& S32At(CMapMesh* self, unsigned int offset)
{
    return *reinterpret_cast<int*>(Ptr(self, offset));
}

static inline float& F32At(CMapMesh* self, unsigned int offset)
{
    return *reinterpret_cast<float*>(Ptr(self, offset));
}

static inline unsigned short& U16At(CMapMesh* self, unsigned int offset)
{
    return *reinterpret_cast<unsigned short*>(Ptr(self, offset));
}

struct MeshDrawEntry
{
    unsigned int size;
    void* displayList;
    unsigned short materialIdx;
    unsigned short _padA;
    unsigned int _padB;
};

static inline MeshDrawEntry* DrawEntries(CMapMesh* self)
{
    return reinterpret_cast<MeshDrawEntry*>(PtrAt(self, 0x40));
}

static inline CMaterialSet* DefaultMaterialSet()
{
    return *reinterpret_cast<CMaterialSet**>(MapMng + 0x21434);
}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMapMesh::CMapMesh()
{
    const float minInit = 10000000000.0f;
    const float maxInit = -10000000000.0f;

    F32At(this, 0x14) = minInit;
    F32At(this, 0x10) = minInit;
    F32At(this, 0xC) = minInit;
    F32At(this, 0x20) = maxInit;
    F32At(this, 0x1C) = maxInit;
    F32At(this, 0x18) = maxInit;

    S32At(this, 0x24) = 0;
    S32At(this, 0x28) = 0;
    S32At(this, 0x2C) = 0;
    S32At(this, 0x30) = 0;
    S32At(this, 0x34) = 0;
    S32At(this, 0x3C) = 0;
    S32At(this, 0x38) = 0;
    S32At(this, 0x40) = 0;
    U16At(this, 0xA) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80028648
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CMapMesh* dtor_80028648(CMapMesh* mapMesh, short param_2)
{
    if (mapMesh != 0) {
        if (PtrAt(mapMesh, 0x24) != 0) {
            __dla__FPv(PtrAt(mapMesh, 0x24));
            PtrAt(mapMesh, 0x24) = 0;
        }

        if (PtrAt(mapMesh, 0x28) != 0) {
            __dla__FPv(PtrAt(mapMesh, 0x28));
            PtrAt(mapMesh, 0x28) = 0;
        }

        U16At(mapMesh, 0x0) = 0;
        U16At(mapMesh, 0x2) = 0;
        U16At(mapMesh, 0x4) = 0;
        U16At(mapMesh, 0x8) = 0;
        U16At(mapMesh, 0x6) = 0;
        U16At(mapMesh, 0xA) = 0;

        if (0 < param_2) {
            __dl__FPv(mapMesh);
        }
    }

    return mapMesh;
}

/*
 * --INFO--
 * PAL Address: 0x800286e0
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::Destroy()
{
    if (PtrAt(this, 0x24) != 0) {
        __dla__FPv(PtrAt(this, 0x24));
        PtrAt(this, 0x24) = 0;
    }

    if (PtrAt(this, 0x28) != 0) {
        __dla__FPv(PtrAt(this, 0x28));
        PtrAt(this, 0x28) = 0;
    }

    U16At(this, 0x0) = 0;
    U16At(this, 0x2) = 0;
    U16At(this, 0x4) = 0;
    U16At(this, 0x8) = 0;
    U16At(this, 0x6) = 0;
    U16At(this, 0xA) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800285dc
 * PAL Size: 108b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::Ptr2Off()
{
    if (S32At(this, 0x24) == 0) {
        return;
    }

    S32At(this, 0x2C) -= S32At(this, 0x24);
    S32At(this, 0x30) -= S32At(this, 0x24);
    S32At(this, 0x34) -= S32At(this, 0x24);
    S32At(this, 0x38) -= S32At(this, 0x24);
    S32At(this, 0x3C) -= S32At(this, 0x24);
    S32At(this, 0x40) -= S32At(this, 0x24);
}

/*
 * --INFO--
 * PAL Address: 0x80028540
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::Off2Ptr()
{
    int iterOffset = 0;

    S32At(this, 0x2C) += S32At(this, 0x24);
    S32At(this, 0x30) += S32At(this, 0x24);
    S32At(this, 0x34) += S32At(this, 0x24);
    S32At(this, 0x38) += S32At(this, 0x24);
    S32At(this, 0x3C) += S32At(this, 0x24);
    S32At(this, 0x40) += S32At(this, 0x24);

    for (int i = 0; i < static_cast<int>(U16At(this, 0xA)); i++) {
        int entry = S32At(this, 0x40) + iterOffset;
        iterOffset += 0x10;
        *reinterpret_cast<int*>(entry + 4) = S32At(this, 0x24) + *reinterpret_cast<int*>(entry + 0xC);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::ReadOtmMesh(CChunkFile&, CMemory::CStage*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80027bd4
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::SetRenderArray()
{
    GXSetArray((GXAttr)9, PtrAt(this, 0x2C), 0xC);
    GXSetArray((GXAttr)0xB, PtrAt(this, 0x3C), 4);
    GXSetArray((GXAttr)0xD, PtrAt(this, 0x38), 4);
    GXSetArray((GXAttr)0xE, PtrAt(this, 0x38), 4);
    *reinterpret_cast<void**>(MaterialMan + 4) = PtrAt(this, 0x30);
}

/*
 * --INFO--
 * PAL Address: 0x80027b24
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::DrawMesh(unsigned short startIdx, unsigned short count)
{
    unsigned int remaining = count;
    MeshDrawEntry* entry = DrawEntries(this) + startIdx;

    while (remaining != 0) {
        if (entry->size != 0) {
            CMaterialSet* materialSet = DefaultMaterialSet();
            SetBlendMode__12CMaterialManFP12CMaterialSeti(MaterialMan, materialSet, entry->materialIdx);
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, materialSet, entry->materialIdx, 0,
                                                                       1);
            GXCallDisplayList(entry->displayList, entry->size);
        }
        entry++;
        remaining--;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80027a7c
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::DrawMeshCharaShadow(unsigned short startIdx, unsigned short count)
{
    unsigned int remaining = count;
    MeshDrawEntry* entry = DrawEntries(this) + startIdx;

    while (remaining != 0) {
        if (entry->size != 0) {
            CMaterial* material = (*reinterpret_cast<CPtrArray<CMaterial*>*>(reinterpret_cast<unsigned char*>(DefaultMaterialSet()) + 8))[entry->materialIdx];
            if ((material != 0) && ((*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(material) + 0x24) &
                                     0x100000) != 0)) {
                SetMaterialCharaShadow__12CMaterialManFP9CMaterial(MaterialMan, material);
                GXCallDisplayList(entry->displayList, entry->size);
            }
        }
        entry++;
        remaining--;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800279c4
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::Draw(CMaterialSet* materialSet)
{
    MeshDrawEntry* entry = DrawEntries(this);
    unsigned int remaining = U16At(this, 0xA);

    if (materialSet == 0) {
        materialSet = DefaultMaterialSet();
    }

    while (remaining != 0) {
        if (entry->size != 0) {
            SetBlendMode__12CMaterialManFP12CMaterialSeti(MaterialMan, materialSet, entry->materialIdx);
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(MaterialMan, materialSet, entry->materialIdx, 0,
                                                                       1);
            GXCallDisplayList(entry->displayList, entry->size);
        }
        entry++;
        remaining--;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80027940
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::DrawPart(CMaterialSet* materialSet, int drawMaterialPart)
{
    MeshDrawEntry* entry = DrawEntries(this);
    unsigned int remaining = U16At(this, 0xA);

    while (remaining != 0) {
        if (entry->size != 0) {
            if (drawMaterialPart != 0) {
                SetMaterialPart__12CMaterialManFP12CMaterialSetii(MaterialMan, materialSet, entry->materialIdx, 1);
            }
            GXCallDisplayList(entry->displayList, entry->size);
        }
        entry++;
        remaining--;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800278e8
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CMapMesh::GetTexture(CMaterialSet* materialSet, int& textureIndex)
{
    int* drawEntry;

    if (U16At(this, 0xA) == 0) {
        return 0;
    }

    drawEntry = reinterpret_cast<int*>(PtrAt(this, 0x40));
    if (*drawEntry == 0) {
        return 0;
    }

    unsigned short materialIdx = *reinterpret_cast<unsigned short*>(drawEntry + 2);
    textureIndex = materialIdx;

    CMaterial* material =
        (*reinterpret_cast<CPtrArray<CMaterial*>*>(reinterpret_cast<unsigned char*>(materialSet) + 8))[materialIdx];
    return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(material) + 0x3C);
}

/*
 * --INFO--
 * PAL Address: 0x800287a0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMaterial* CPtrArray<CMaterial*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x800287c0
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CMaterial* CPtrArray<CMaterial*>::GetAt(unsigned long index)
{
    return m_items[index];
}

/*
 * --INFO--
 * PAL Address: 0x80027864
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::SetDisplayListMaterial(CMaterialSet* materialSet, char** textureNames, CAmemCacheSet*)
{
    MeshDrawEntry* entry = DrawEntries(this);
    unsigned int remaining = U16At(this, 0xA);

    while (remaining != 0) {
        if (entry->size != 0) {
            if (entry->materialIdx == 0xFFFF) {
                entry->materialIdx = 0;
            } else {
                entry->materialIdx = FindTexName__12CMaterialSetFPcPl(materialSet, textureNames[entry->materialIdx], 0);
            }
        }
        entry++;
        remaining--;
    }
}

/*
 * --INFO--
 * PAL Address: 0x800277ec
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::pppCacheLoadModelTexture(CMaterialSet* materialSet, CAmemCacheSet* cacheSet)
{
    MeshDrawEntry* entry = DrawEntries(this);
    unsigned int remaining = U16At(this, 0xA);

    while (remaining != 0) {
        if (entry->size != 0) {
            if (entry->materialIdx == 0xFFFF) {
                entry->materialIdx = 0;
            } else {
                CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, entry->materialIdx, cacheSet);
            }
        }
        entry++;
        remaining--;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::pppCacheUnLoadModelTexture(CMaterialSet*, CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMapMesh::pppCacheRefCnt0UpModelTexture(CMaterialSet*, CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80027774
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::pppCacheDumpModelTexture(CMaterialSet* materialSet, CAmemCacheSet* cacheSet)
{
    MeshDrawEntry* entry = DrawEntries(this);
    unsigned int remaining = U16At(this, 0xA);

    while (remaining != 0) {
        if (entry->size != 0) {
            if (entry->materialIdx == 0xFFFF) {
                entry->materialIdx = 0;
            } else {
                CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, entry->materialIdx, cacheSet);
            }
        }
        entry++;
        remaining--;
    }
}
