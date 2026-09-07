#include "ffcc/mapmesh.h"
#include "ffcc/chunkfile.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/materialman.h"

#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>

#include <string.h>

class CMapHitFace;

static const char s_mapmesh_cpp[] = "mapmesh.cpp";
static const float kMapMeshInitialMinBound = 10000000000.0f;
static const float kMapMeshInitialMaxBound = -10000000000.0f;

static CMemory::CStage* g_pStage;

namespace {
static inline void AddMeshDataBase(void*& ptr, void* base)
{
    ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void AddMeshDataBase(Vec*& ptr, void* base)
{
    ptr = reinterpret_cast<Vec*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void AddMeshDataBase(S16Vec*& ptr, void* base)
{
    ptr = reinterpret_cast<S16Vec*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void AddMeshDataBase(CMapMeshUvPair*& ptr, void* base)
{
    ptr = reinterpret_cast<CMapMeshUvPair*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void AddMeshDataBase(GXColor*& ptr, void* base)
{
    ptr = reinterpret_cast<GXColor*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void AddMeshDataBase(CMapMeshDrawEntry*& ptr, void* base)
{
    ptr = reinterpret_cast<CMapMeshDrawEntry*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void SubMeshDataBase(void*& ptr, void* base)
{
    ptr = reinterpret_cast<void*>(static_cast<u8*>(ptr) - static_cast<u8*>(base));
}

static inline void SubMeshDataBase(Vec*& ptr, void* base)
{
    ptr = reinterpret_cast<Vec*>(reinterpret_cast<u8*>(ptr) - static_cast<u8*>(base));
}

static inline void SubMeshDataBase(S16Vec*& ptr, void* base)
{
    ptr = reinterpret_cast<S16Vec*>(reinterpret_cast<u8*>(ptr) - static_cast<u8*>(base));
}

static inline void SubMeshDataBase(CMapMeshUvPair*& ptr, void* base)
{
    ptr = reinterpret_cast<CMapMeshUvPair*>(reinterpret_cast<u8*>(ptr) - static_cast<u8*>(base));
}

static inline void SubMeshDataBase(GXColor*& ptr, void* base)
{
    ptr = reinterpret_cast<GXColor*>(reinterpret_cast<u8*>(ptr) - static_cast<u8*>(base));
}

static inline void SubMeshDataBase(CMapMeshDrawEntry*& ptr, void* base)
{
    ptr = reinterpret_cast<CMapMeshDrawEntry*>(reinterpret_cast<u8*>(ptr) - static_cast<u8*>(base));
}

static inline unsigned int Align32(unsigned int value)
{
    return (value + 0x1F) & ~0x1FU;
}

static inline CMemory::CStage*& MapMeshAllocStage()
{
    return g_pStage;
}
}

/*
 * --INFO--
 * PAL Address: TODO
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CMapMesh::pppCacheRefCnt0UpModelTexture(CMaterialSet* materialSet, CAmemCacheSet* cacheSet)
{
    int remaining = static_cast<int>(m_displayListCount);
    CMapMeshDrawEntry* entry = m_drawEntries;
    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            if (entry->m_materialIdx == 0xFFFF) {
                entry->m_materialIdx = 0;
            } else {
                materialSet->CacheRefCnt0UpTexture(entry->m_materialIdx, cacheSet);
            }
        }
        entry++;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80027774
 * PAL Size: 120b
 * EN Address: 0x8003324C
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::pppCacheUnLoadModelTexture(CMaterialSet* materialSet, CAmemCacheSet* cacheSet)
{
    int remaining = static_cast<int>(m_displayListCount);
    CMapMeshDrawEntry* entry = m_drawEntries;
    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            if (entry->m_materialIdx == 0xFFFF) {
                entry->m_materialIdx = 0;
            } else {
                materialSet->CacheUnLoadTexture(entry->m_materialIdx, cacheSet);
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
    int remaining = static_cast<int>(m_displayListCount);
    CMapMeshDrawEntry* entry = m_drawEntries;
    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            if (entry->m_materialIdx == 0xFFFF) {
                entry->m_materialIdx = 0;
            } else {
                materialSet->CacheLoadTexture(entry->m_materialIdx, cacheSet);
            }
        }
        entry++;
    }
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
    int remaining = static_cast<int>(m_displayListCount);
    CMapMeshDrawEntry* entry = m_drawEntries;

    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            if (entry->m_materialIdx == 0xFFFF) {
                entry->m_materialIdx = 0;
            } else {
                entry->m_materialIdx = materialSet->FindTexName(textureNames[entry->m_materialIdx], 0);
            }
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
CTexture* CMapMesh::GetTexture(CMaterialSet* materialSet, int& textureIndex)
{
    if (m_displayListCount != 0) {
        CMapMeshDrawEntry* drawEntry = m_drawEntries;
        if (drawEntry->m_size != 0) {
            textureIndex = static_cast<unsigned int>(drawEntry->m_materialIdx);
            CMaterial* material = materialSet->GetMaterial(drawEntry->m_materialIdx);
            return material->GetTexture(0);
        }
    }

    return 0;
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
    int remaining = static_cast<int>(m_displayListCount);
    CMapMeshDrawEntry* entry = m_drawEntries;

    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            if (drawMaterialPart != 0) {
                MaterialMan.SetMaterialPart(materialSet, entry->m_materialIdx, 1);
            }
            GXCallDisplayList(entry->m_displayList, entry->m_size);
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
        materialSet = MapMng.m_materialSet;
    }

    int remaining = static_cast<int>(m_displayListCount);
    CMapMeshDrawEntry* entry = m_drawEntries;

    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            MaterialMan.SetBlendMode(materialSet, entry->m_materialIdx);
            MaterialMan.SetMaterial(materialSet, entry->m_materialIdx, 0, (_GXTevScale)1);
            GXCallDisplayList(entry->m_displayList, entry->m_size);
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
    CMapMng* mapMng = &MapMng;
    int remaining = count;
    CMapMeshDrawEntry* entry = m_drawEntries + startIdx;

    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            CMaterial* material = mapMng->m_materialSet->GetMaterial(entry->m_materialIdx);

            if ((material->GetTevBit() & 0x100000) != 0) {
                MaterialMan.SetMaterialCharaShadow(material);
                GXCallDisplayList(entry->m_displayList, entry->m_size);
            }
        }
        entry++;
    }
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
    CMapMng* mapMng = &MapMng;
    int remaining = count;
    CMapMeshDrawEntry* entry = m_drawEntries + startIdx;

    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            MaterialMan.SetBlendMode(mapMng->m_materialSet, entry->m_materialIdx);
            MaterialMan.SetMaterial(mapMng->m_materialSet, entry->m_materialIdx, 0, (_GXTevScale)1);
            GXCallDisplayList(entry->m_displayList, entry->m_size);
        }
        entry++;
    }
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
    GXSetArray((GXAttr)9, m_vertices, 0xC);
    GXSetArray((GXAttr)0xB, m_colors, 4);
    GXSetArray((GXAttr)0xD, m_uvPairs, 4);
    GXSetArray((GXAttr)0xE, m_uvPairs, 4);
    MaterialMan.SetGeometryArraySource(m_normals);
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
            m_displayListCount = static_cast<unsigned short>(chunk.m_arg0);
            workSize = Align32(workSize);
            workSize += static_cast<unsigned int>(m_displayListCount) * 0x10U;
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
    MapMeshAllocStage() = stage;
    unsigned char* cursor;
    int offset;
    int dlIndex;
    reader.PushChunk();
    while (reader.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x56455254:
            m_meshData = new (MapMeshAllocStage(), const_cast<char*>(s_mapmesh_cpp), 0x13A) unsigned char[workSize];

            cursor = reinterpret_cast<unsigned char*>(m_meshData);
            m_vertexCount = static_cast<unsigned short>(chunk.m_size / 0xC);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_vertices = reinterpret_cast<Vec*>(cursor);
            cursor += chunk.m_size;
            m_bound.m_min.z = kMapMeshInitialMinBound;
            m_bound.m_min.y = kMapMeshInitialMinBound;
            m_bound.m_min.x = kMapMeshInitialMinBound;
            m_bound.m_max.z = kMapMeshInitialMaxBound;
            m_bound.m_max.y = kMapMeshInitialMaxBound;
            m_bound.m_max.x = kMapMeshInitialMaxBound;

            int vertexIndex = 0;
            for (; vertexIndex < static_cast<int>(m_vertexCount); vertexIndex++) {
                float value = reader.GetF4();
                m_vertices[vertexIndex].x = value;
                value = reader.GetF4();
                m_vertices[vertexIndex].y = value;
                value = reader.GetF4();
                m_vertices[vertexIndex].z = value;

                Vec* vert = &m_vertices[vertexIndex];
                m_bound.m_min.x = (m_bound.m_min.x < vert->x) ? m_bound.m_min.x : vert->x;
                m_bound.m_min.y = (m_bound.m_min.y < vert->y) ? m_bound.m_min.y : vert->y;
                m_bound.m_min.z = (m_bound.m_min.z < vert->z) ? m_bound.m_min.z : vert->z;
                m_bound.m_max.x = (m_bound.m_max.x > vert->x) ? m_bound.m_max.x : vert->x;
                m_bound.m_max.y = (m_bound.m_max.y > vert->y) ? m_bound.m_max.y : vert->y;
                m_bound.m_max.z = (m_bound.m_max.z > vert->z) ? m_bound.m_max.z : vert->z;
            }
            break;
        case 0x4E4F524D:
            m_normalCount = static_cast<unsigned short>(chunk.m_size / 6);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_normals = reinterpret_cast<S16Vec*>(cursor);
            cursor += chunk.m_size;

            for (int i = 0; i < static_cast<int>(m_normalCount); i++) {
                m_normals[i].x = reader.Get2();
                m_normals[i].y = reader.Get2();
                m_normals[i].z = reader.Get2();
            }
            break;
        case 0x434F4C52:
            m_colorCount = static_cast<unsigned short>(chunk.m_size >> 2);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_colors = reinterpret_cast<GXColor*>(cursor);
            cursor += chunk.m_size;

            for (int i = 0; i < static_cast<int>(m_colorCount); i++) {
                m_colors[i].r = reader.Get1();
                m_colors[i].g = reader.Get1();
                m_colors[i].b = reader.Get1();
                m_colors[i].a = reader.Get1();
                if (halfColor != 0) {
                    m_colors[i].r >>= 1;
                    m_colors[i].g >>= 1;
                    m_colors[i].b >>= 1;
                }
            }
            break;
        case 0x55562020:
            m_uvCount = static_cast<unsigned short>(chunk.m_size >> 2);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_uvPairs = reinterpret_cast<CMapMeshUvPair*>(cursor);
            cursor += chunk.m_size;

            int i = 0;
            offset = 0;
            for (; i < static_cast<int>(m_uvCount); i++) {
                m_uvPairs[i].m_u = reader.Get2();
                m_uvPairs[i].m_v = reader.Get2();
            }
            break;
        case 0x444C4844:
            m_displayListCount = static_cast<unsigned short>(chunk.m_arg0);
            if (usePreallocated != 0) {
                m_displayListData =
                    new (MapMeshAllocStage(), const_cast<char*>(s_mapmesh_cpp), 0x1D5) unsigned char[workSize];
                cursor = reinterpret_cast<unsigned char*>(m_displayListData);
            } else {
                cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            }
            m_drawEntries = reinterpret_cast<CMapMeshDrawEntry*>(cursor);

            cursor += static_cast<unsigned int>(m_displayListCount) * 0x10U;
            for (int i = 0; i < static_cast<int>(m_displayListCount); i++) {
                m_drawEntries[i].m_size = 0;
                m_drawEntries[i].m_displayList = 0;
            }

            dlIndex = 0;
            reader.PushChunk();
            while (reader.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 0x444C5354: {
                    CMapMeshDrawEntry* entry = m_drawEntries + dlIndex++;
                    entry->m_materialIdx = reader.Get2();
                    entry->m_size = chunk.m_arg0;

                    reader.Align(0x20);
                    entry->m_displayList = 0;
                    if (entry->m_size != 0) {
                        cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
                        entry->m_displayList = cursor;
                        if (usePreallocated != 0) {
                            entry->m_displayListOffset = reinterpret_cast<unsigned int>(entry->m_displayList) -
                                                         reinterpret_cast<unsigned int>(m_displayListData);
                        } else {
                            entry->m_displayListOffset = reinterpret_cast<unsigned int>(entry->m_displayList) -
                                                         reinterpret_cast<unsigned int>(m_meshData);
                        }

                        cursor += Align32(chunk.m_arg0);
                        memset(entry->m_displayList, 0, Align32(entry->m_size));
                        reader.Get(entry->m_displayList, entry->m_size);
                        DCFlushRange(entry->m_displayList, Align32(entry->m_size));
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
            m_bound.m_min.x -= x;
            m_bound.m_min.y -= y;
            m_bound.m_min.z -= z;
            m_bound.m_max.x += x;
            m_bound.m_max.y += y;
            m_bound.m_max.z += z;
            break;
        }
        }
    }
    reader.PopChunk();
    return workSize;
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
    int offset;
    CMapMeshDrawEntry* entry;
    int i = 0;
    offset = 0;

    AddMeshDataBase(m_vertices, m_meshData);
    AddMeshDataBase(m_normals, m_meshData);
    AddMeshDataBase(m_nbt, m_meshData);
    AddMeshDataBase(m_uvPairs, m_meshData);
    AddMeshDataBase(m_colors, m_meshData);
    AddMeshDataBase(m_drawEntries, m_meshData);

    for (; i < static_cast<int>(static_cast<unsigned short>(m_displayListCount)); i++) {
        entry = reinterpret_cast<CMapMeshDrawEntry*>(reinterpret_cast<unsigned int>(m_drawEntries) + offset);
        offset += sizeof(CMapMeshDrawEntry);
        entry->m_displayList = static_cast<u8*>(m_meshData) + entry->m_displayListOffset;
    }
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
    if (m_meshData == 0) {
        return;
    }

    SubMeshDataBase(m_vertices, m_meshData);
    SubMeshDataBase(m_normals, m_meshData);
    SubMeshDataBase(m_nbt, m_meshData);
    SubMeshDataBase(m_uvPairs, m_meshData);
    SubMeshDataBase(m_colors, m_meshData);
    SubMeshDataBase(m_drawEntries, m_meshData);
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
    if (m_meshData != 0) {
        delete[] static_cast<unsigned char*>(m_meshData);
        m_meshData = 0;
    }

    if (m_displayListData != 0) {
        delete[] static_cast<unsigned char*>(m_displayListData);
        m_displayListData = 0;
    }

    m_vertexCount = 0;
    m_normalCount = 0;
    m_nbtCount = 0;
    m_colorCount = 0;
    m_uvCount = 0;
    m_displayListCount = 0;
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
    if (m_meshData != 0) {
        delete[] static_cast<unsigned char*>(m_meshData);
        m_meshData = 0;
    }

    if (m_displayListData != 0) {
        delete[] static_cast<unsigned char*>(m_displayListData);
        m_displayListData = 0;
    }

    m_vertexCount = 0;
    m_normalCount = 0;
    m_nbtCount = 0;
    m_colorCount = 0;
    m_uvCount = 0;
    m_displayListCount = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80028754
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMapMesh::CMapMesh()
{
    m_bound.m_min.z = kMapMeshInitialMinBound;
    m_bound.m_min.y = kMapMeshInitialMinBound;
    m_bound.m_min.x = kMapMeshInitialMinBound;
    m_bound.m_max.z = kMapMeshInitialMaxBound;
    m_bound.m_max.y = kMapMeshInitialMaxBound;
    m_bound.m_max.x = kMapMeshInitialMaxBound;

    m_meshData = 0;
    m_displayListData = 0;
    m_vertices = 0;
    m_normals = 0;
    m_nbt = 0;
    m_colors = 0;
    m_uvPairs = 0;
    m_drawEntries = 0;
    m_displayListCount = 0;
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
