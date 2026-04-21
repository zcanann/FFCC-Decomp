#include "ffcc/mapmesh.h"
#include "ffcc/chunkfile.h"
#include "ffcc/linkage.h"

#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>

#include <string.h>

class CMaterial;

extern "C" void __dl__FPv(void* ptr);
extern "C" void __dla__FPv(void* ptr);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long size, CMemory::CStage* stage, char* file, int line);
extern "C" CMemory::CStage* DAT_8032EC98;
extern "C" char s_mapmesh_cpp_801D70B0[];
extern "C" float FLOAT_8032F930;
extern "C" float FLOAT_8032F934;

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
    int displayListOffset;
};

static inline MeshDrawEntry* DrawEntries(CMapMesh* self)
{
    return reinterpret_cast<MeshDrawEntry*>(PtrAt(self, 0x40));
}

static inline CMaterialSet* DefaultMaterialSet()
{
    return *reinterpret_cast<CMaterialSet**>(reinterpret_cast<unsigned char*>(&MapMng) + 0x213D4);
}

static inline unsigned int Align32(unsigned int value)
{
    return (value + 0x1F) & ~0x1FU;
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
CMapMesh::~CMapMesh()
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
    if (PtrAt(this, 0x24) == 0) {
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
    int iVar1;
    int iVar2;
    int iVar3;

    S32At(this, 0x2C) += S32At(this, 0x24);
    S32At(this, 0x30) += S32At(this, 0x24);
    S32At(this, 0x34) += S32At(this, 0x24);
    S32At(this, 0x38) += S32At(this, 0x24);
    S32At(this, 0x3C) += S32At(this, 0x24);
    S32At(this, 0x40) += S32At(this, 0x24);

    iVar3 = 0;
    iVar1 = 0;
    while (iVar3 < (int)(unsigned int)U16At(this, 0xA)) {
        int base = S32At(this, 0x24);
        int drawEntriesBase = S32At(this, 0x40);
        iVar2 = drawEntriesBase + iVar1;
        iVar1 = iVar1 + 0x10;
        *reinterpret_cast<int*>(iVar2 + 4) = base + *reinterpret_cast<int*>(iVar2 + 0xC);
        iVar3++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80027c4c
 * PAL Size: 2292b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CMapMesh::ReadOtmMesh(CChunkFile& chunkFile, CMemory::CStage* stage, int usePreallocated, int halfColor)
{
    unsigned int workSize;
    CChunkFile::CChunk chunk;
    CChunkFile reader = chunkFile;
    workSize = 0;
    reader.PushChunk();
    while (reader.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x56455254:
            workSize = Align32(workSize);
            workSize += chunk.m_size;
            break;
        case 0x4E4F524D:
            workSize = Align32(workSize);
            workSize += chunk.m_size;
            break;
        case 0x4E425420:
            workSize = Align32(workSize);
            workSize += chunk.m_size;
            break;
        case 0x434F4C52:
            workSize = Align32(workSize);
            workSize += chunk.m_size;
            break;
        case 0x55562020:
            workSize = Align32(workSize);
            workSize += chunk.m_size;
            break;
        case 0x444C4844:
            U16At(this, 0xA) = static_cast<unsigned short>(chunk.m_arg0);
            workSize = Align32(workSize);
            workSize += static_cast<unsigned int>(U16At(this, 0xA)) * 0x10U;
            reader.PushChunk();
            while (reader.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 0x444C5354:
                    reader.Align(0x20);
                    if (chunk.m_arg0 != 0) {
                        workSize = Align32(workSize);
                        workSize += Align32(chunk.m_arg0);
                    }
                    reader.Align(0x20);
                    break;
                }
            }
            reader.PopChunk();
            break;
        }
    }
    reader.PopChunk();
    workSize = Align32(workSize);

    reader = chunkFile;
    DAT_8032EC98 = stage;
    unsigned char* cursor;
    int offset;
    float minInit;
    float maxInit;
    unsigned int dlOffset;
    reader.PushChunk();
    while (reader.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x56455254:
            m_meshData = __nwa__FUlPQ27CMemory6CStagePci(workSize, DAT_8032EC98, s_mapmesh_cpp_801D70B0, 0x13A);

            minInit = FLOAT_8032F930;
            maxInit = FLOAT_8032F934;
            offset = 0;
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(m_meshData)));
            m_vertexCount = static_cast<unsigned short>(chunk.m_size / 0xC);
            m_vertices = cursor;
            m_bboxMinZ = minInit;
            m_bboxMinY = minInit;
            m_bboxMinX = minInit;
            m_bboxMaxZ = maxInit;
            m_bboxMaxY = maxInit;
            m_bboxMaxX = maxInit;
            cursor += chunk.m_size;

            for (int i = 0; i < static_cast<int>(m_vertexCount); i++) {
                float value = reader.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset) = value;
                value = reader.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset + 4) = value;
                value = reader.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset + 8) = value;

                float* vert = reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset);
                m_bboxMinX = (m_bboxMinX < vert[0]) ? m_bboxMinX : vert[0];
                m_bboxMinY = (m_bboxMinY < vert[1]) ? m_bboxMinY : vert[1];
                m_bboxMinZ = (m_bboxMinZ < vert[2]) ? m_bboxMinZ : vert[2];
                m_bboxMaxX = (m_bboxMaxX > vert[0]) ? m_bboxMaxX : vert[0];
                m_bboxMaxY = (m_bboxMaxY > vert[1]) ? m_bboxMaxY : vert[1];
                m_bboxMaxZ = (m_bboxMaxZ > vert[2]) ? m_bboxMaxZ : vert[2];

                offset += 0xC;
            }
            break;
        case 0x4E4F524D:
            m_normalCount = static_cast<unsigned short>(chunk.m_size / 6);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_normals = cursor;
            cursor += chunk.m_size;

            offset = 0;
            for (int i = 0; i < static_cast<int>(m_normalCount); i++) {
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_normals) + offset) = reader.Get2();
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_normals) + offset + 2) =
                    reader.Get2();
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_normals) + offset + 4) =
                    reader.Get2();
                offset += 6;
            }
            break;
        case 0x434F4C52:
            m_colorCount = static_cast<unsigned short>(chunk.m_size >> 2);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_colors = cursor;
            cursor += chunk.m_size;

            offset = 0;
            for (int i = 0; i < static_cast<int>(m_colorCount); i++) {
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset) = reader.Get1();
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 1) =
                    reader.Get1();
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 2) =
                    reader.Get1();
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 3) =
                    reader.Get1();
                if (halfColor != 0) {
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset) =
                        static_cast<unsigned char>(
                            *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset) >> 1);
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 1) =
                        static_cast<unsigned char>(
                            *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 1) >>
                            1);
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 2) =
                        static_cast<unsigned char>(
                            *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 2) >>
                            1);
                }
                offset += 4;
            }
            break;
        case 0x55562020:
            m_uvCount = static_cast<unsigned short>(chunk.m_size >> 2);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_uvPairs = cursor;
            cursor += chunk.m_size;

            offset = 0;
            for (int i = 0; i < static_cast<int>(m_uvCount); i++) {
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_uvPairs) + offset) = reader.Get2();
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_uvPairs) + offset + 2) =
                    reader.Get2();
                offset += 4;
            }
            break;
        case 0x444C4844:
            m_displayListCount = static_cast<unsigned short>(chunk.m_arg0);
            unsigned int drawEntriesBase;
            if (usePreallocated != 0) {
                m_displayListData = __nwa__FUlPQ27CMemory6CStagePci(workSize, DAT_8032EC98, s_mapmesh_cpp_801D70B0, 0x1D5);
                drawEntriesBase = reinterpret_cast<unsigned int>(m_displayListData);
            } else {
                drawEntriesBase = Align32(reinterpret_cast<unsigned int>(cursor));
            }
            m_drawEntries = reinterpret_cast<void*>(drawEntriesBase);

            cursor = reinterpret_cast<unsigned char*>(drawEntriesBase + (static_cast<unsigned int>(m_displayListCount) * 0x10U));
            offset = 0;
            for (int i = 0; i < static_cast<int>(m_displayListCount); i++) {
                *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int>(m_drawEntries) + offset) = 0;
                *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int>(m_drawEntries) + offset + 4) = 0;
                offset += 0x10;
            }

            dlOffset = 0;
            reader.PushChunk();
            while (reader.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 0x444C5354: {
                    MeshDrawEntry* entry = reinterpret_cast<MeshDrawEntry*>(reinterpret_cast<unsigned int>(m_drawEntries) + dlOffset);
                    dlOffset += 0x10;
                    entry->materialIdx = reader.Get2();
                    entry->size = chunk.m_arg0;

                    reader.Align(0x20);
                    entry->displayList = 0;
                    if (entry->size != 0) {
                        entry->displayList = reinterpret_cast<void*>(Align32(reinterpret_cast<unsigned int>(cursor)));
                        if (usePreallocated != 0) {
                            entry->displayListOffset = reinterpret_cast<unsigned int>(entry->displayList) -
                                                       reinterpret_cast<unsigned int>(m_displayListData);
                        } else {
                            entry->displayListOffset = reinterpret_cast<unsigned int>(entry->displayList) -
                                                       reinterpret_cast<unsigned int>(m_meshData);
                        }

                        cursor = reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(entry->displayList) +
                                                                 Align32(chunk.m_arg0));
                        memset(entry->displayList, 0, Align32(entry->size));
                        reader.Get(entry->displayList, entry->size);
                        DCFlushRange(entry->displayList, Align32(entry->size));
                    }
                    reader.Align(0x20);
                    break;
                }
                }
            }
            reader.PopChunk();

            DCFlushRange(m_vertices, static_cast<unsigned int>(m_vertexCount) * 0xC);
            DCFlushRange(m_normals, static_cast<unsigned int>(m_normalCount) * 0xC);
            DCFlushRange(m_nbt, static_cast<unsigned int>(m_nbtCount) * 0x12);
            DCFlushRange(m_colors, static_cast<unsigned int>(m_colorCount) * 0xC);
            DCFlushRange(m_uvPairs, static_cast<unsigned int>(m_uvCount) * 0xC);
            break;
        case 0x424F4646: {
            float x = reader.GetF4();
            float y = reader.GetF4();
            float z = reader.GetF4();
            m_bboxMinX -= x;
            m_bboxMinY -= y;
            m_bboxMinZ -= z;
            m_bboxMaxX += x;
            m_bboxMaxY += y;
            m_bboxMaxZ += z;
            break;
        }
        }
    }
    reader.PopChunk();
    return workSize;
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
    *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MaterialMan) + 4) = PtrAt(this, 0x30);
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
    int remaining = count;
    unsigned char* mapMng = reinterpret_cast<unsigned char*>(&MapMng);
    MeshDrawEntry* entry = DrawEntries(this) + startIdx;

    while (remaining-- != 0) {
        if (entry->size != 0) {
            SetBlendMode__12CMaterialManFP12CMaterialSeti(
                &MaterialMan, *reinterpret_cast<CMaterialSet**>(mapMng + 0x213D4), entry->materialIdx);
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(
                &MaterialMan, *reinterpret_cast<CMaterialSet**>(mapMng + 0x213D4),
                                                                       entry->materialIdx, 0, 1);
            GXCallDisplayList(entry->displayList, entry->size);
        }
        entry++;
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
    unsigned char* mapMng = reinterpret_cast<unsigned char*>(&MapMng);
    int remaining = count;
    MeshDrawEntry* entry = DrawEntries(this) + startIdx;

    while (remaining-- != 0) {
        if (entry->size != 0) {
            CMaterial* material =
                (*reinterpret_cast<CPtrArray<CMaterial*>*>(
                    reinterpret_cast<unsigned char*>(*reinterpret_cast<CMaterialSet**>(mapMng + 0x213D4)) + 8))[
                    entry->materialIdx];

            if ((*reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(material) + 0x24) &
                 0x100000) != 0) {
                SetMaterialCharaShadow__12CMaterialManFP9CMaterial(&MaterialMan, material);
                GXCallDisplayList(entry->displayList, entry->size);
            }
        }
        entry++;
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
    if (materialSet == 0) {
        materialSet = *reinterpret_cast<CMaterialSet**>(reinterpret_cast<unsigned char*>(&MapMng) + 0x213D4);
    }

    int remaining = static_cast<int>(U16At(this, 0xA));
    MeshDrawEntry* entry = DrawEntries(this);

    while (remaining-- != 0) {
        if (entry->size != 0) {
            SetBlendMode__12CMaterialManFP12CMaterialSeti(&MaterialMan, materialSet, entry->materialIdx);
            SetMaterial__12CMaterialManFP12CMaterialSetii11_GXTevScale(&MaterialMan, materialSet, entry->materialIdx, 0,
                                                                       1);
            GXCallDisplayList(entry->displayList, entry->size);
        }
        entry++;
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
    int remaining = static_cast<int>(U16At(this, 0xA));
    MeshDrawEntry* entry = DrawEntries(this);

    while (remaining-- != 0) {
        if (entry->size != 0) {
            if (drawMaterialPart != 0) {
                SetMaterialPart__12CMaterialManFP12CMaterialSetii(&MaterialMan, materialSet, entry->materialIdx, 1);
            }
            GXCallDisplayList(entry->displayList, entry->size);
        }
        entry++;
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
    unsigned int* drawEntry;

    if (U16At(this, 0xA) != 0) {
        drawEntry = reinterpret_cast<unsigned int*>(PtrAt(this, 0x40));
        if (*drawEntry != 0) {
            textureIndex = (unsigned int)*reinterpret_cast<unsigned short*>(drawEntry + 2);
            CMaterial* material = (*reinterpret_cast<CPtrArray<CMaterial*>*>(
                reinterpret_cast<unsigned char*>(materialSet) + 8))[*reinterpret_cast<unsigned short*>(drawEntry + 2)];
            return *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(material) + 0x3C);
        }
    }

    return 0;
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
    int remaining = static_cast<int>(U16At(this, 0xA));
    MeshDrawEntry* entry = DrawEntries(this);

    while (remaining-- != 0) {
        if (entry->size != 0) {
            if (entry->materialIdx == 0xFFFF) {
                entry->materialIdx = 0;
            } else {
                entry->materialIdx = FindTexName__12CMaterialSetFPcPl(materialSet, textureNames[entry->materialIdx], 0);
            }
        }
        entry++;
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
    int remaining = static_cast<int>(U16At(this, 0xA));
    MeshDrawEntry* entry = DrawEntries(this);
    while (remaining-- != 0) {
        if (entry->size != 0) {
            if (entry->materialIdx == 0xFFFF) {
                entry->materialIdx = 0;
            } else {
                CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, (unsigned int)entry->materialIdx, cacheSet);
            }
        }
        entry++;
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
    int remaining = static_cast<int>(U16At(this, 0xA));
    MeshDrawEntry* entry = DrawEntries(this);
    while (remaining-- != 0) {
        if (entry->size != 0) {
            if (entry->materialIdx == 0xFFFF) {
                entry->materialIdx = 0;
            } else {
                CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, (unsigned int)entry->materialIdx, cacheSet);
            }
        }
        entry++;
    }
}
