#include "ffcc/mapmesh.h"
#include "ffcc/chunkfile.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/materialman.h"

#include <dolphin/gx.h>
#include <dolphin/os/OSCache.h>

#include <string.h>

class CMapHitFace;

extern "C" char s_mapmesh_cpp[];
extern "C" const float FLOAT_8032F930;
extern "C" const float FLOAT_8032F934;

CMemory::CStage* g_pStage;
u32 s_insertShadowNo;

namespace {
static inline void AddMeshDataBase(void*& ptr, void* base)
{
    ptr = reinterpret_cast<void*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void AddMeshDataBase(CMapMeshUvPair*& ptr, void* base)
{
    ptr = reinterpret_cast<CMapMeshUvPair*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void AddMeshDataBase(CMapMeshDrawEntry*& ptr, void* base)
{
    ptr = reinterpret_cast<CMapMeshDrawEntry*>(reinterpret_cast<unsigned int>(ptr) + reinterpret_cast<unsigned int>(base));
}

static inline void SubMeshDataBase(void*& ptr, void* base)
{
    ptr = reinterpret_cast<void*>(static_cast<u8*>(ptr) - static_cast<u8*>(base));
}

static inline void SubMeshDataBase(CMapMeshUvPair*& ptr, void* base)
{
    ptr = reinterpret_cast<CMapMeshUvPair*>(reinterpret_cast<u8*>(ptr) - static_cast<u8*>(base));
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
 * PAL Address: 0x80027774
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CMapMesh::pppCacheDumpModelTexture(CMaterialSet* materialSet, CAmemCacheSet* cacheSet)
{
    int remaining = static_cast<int>(m_displayListCount);
    CMapMeshDrawEntry* entry = m_drawEntries;
    while (remaining-- != 0) {
        if (entry->m_size != 0) {
            if (entry->m_materialIdx == 0xFFFF) {
                entry->m_materialIdx = 0;
            } else {
                materialSet->CacheDumpTexture(entry->m_materialIdx, cacheSet);
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
    unsigned int* drawEntry;

    if (m_displayListCount != 0) {
        drawEntry = reinterpret_cast<unsigned int*>(m_drawEntries);
        if (*drawEntry != 0) {
            textureIndex = (unsigned int)*reinterpret_cast<unsigned short*>(drawEntry + 2);
            CMaterial* material = materialSet->GetMaterial(*reinterpret_cast<unsigned short*>(drawEntry + 2));
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
            m_meshData = new (MapMeshAllocStage(), s_mapmesh_cpp, 0x13A) unsigned char[workSize];

            cursor = reinterpret_cast<unsigned char*>(m_meshData);
            m_vertexCount = static_cast<unsigned short>(chunk.m_size / 0xC);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_vertices = cursor;
            cursor += chunk.m_size;
            m_bound.m_min.z = FLOAT_8032F930;
            m_bound.m_min.y = FLOAT_8032F930;
            m_bound.m_min.x = FLOAT_8032F930;
            m_bound.m_max.z = FLOAT_8032F934;
            m_bound.m_max.y = FLOAT_8032F934;
            m_bound.m_max.x = FLOAT_8032F934;

            int vertexIndex = 0;
            offset = 0;
            for (; vertexIndex < static_cast<int>(m_vertexCount); vertexIndex++) {
                float value = reader.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset) = value;
                value = reader.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset + 4) = value;
                value = reader.GetF4();
                *reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset + 8) = value;

                float* vert = reinterpret_cast<float*>(reinterpret_cast<unsigned int>(m_vertices) + offset);
                m_bound.m_min.x = (m_bound.m_min.x < vert[0]) ? m_bound.m_min.x : vert[0];
                m_bound.m_min.y = (m_bound.m_min.y < vert[1]) ? m_bound.m_min.y : vert[1];
                m_bound.m_min.z = (m_bound.m_min.z < vert[2]) ? m_bound.m_min.z : vert[2];
                m_bound.m_max.x = (m_bound.m_max.x > vert[0]) ? m_bound.m_max.x : vert[0];
                m_bound.m_max.y = (m_bound.m_max.y > vert[1]) ? m_bound.m_max.y : vert[1];
                m_bound.m_max.z = (m_bound.m_max.z > vert[2]) ? m_bound.m_max.z : vert[2];

                offset += 0xC;
            }
            break;
        case 0x4E4F524D:
            m_normalCount = static_cast<unsigned short>(chunk.m_size / 6);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_normals = cursor;
            cursor += chunk.m_size;

            for (int i = 0, offset = 0; i < static_cast<int>(m_normalCount); i++, offset += 6) {
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_normals) + offset) = reader.Get2();
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_normals) + offset + 2) =
                    reader.Get2();
                *reinterpret_cast<unsigned short*>(reinterpret_cast<unsigned int>(m_normals) + offset + 4) =
                    reader.Get2();
            }
            break;
        case 0x434F4C52:
            m_colorCount = static_cast<unsigned short>(chunk.m_size >> 2);
            cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            m_colors = cursor;
            cursor += chunk.m_size;

            for (int i = 0, offset = 0; i < static_cast<int>(m_colorCount); i++) {
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset) = reader.Get1();
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 1) =
                    reader.Get1();
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 2) =
                    reader.Get1();
                *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 3) =
                    reader.Get1();
                if (halfColor != 0) {
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset) >>= 1;
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 1) >>= 1;
                    *reinterpret_cast<unsigned char*>(reinterpret_cast<unsigned int>(m_colors) + offset + 2) >>= 1;
                }
                offset += 4;
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
                m_displayListData = new (MapMeshAllocStage(), s_mapmesh_cpp, 0x1D5) unsigned char[workSize];
                cursor = reinterpret_cast<unsigned char*>(m_displayListData);
            } else {
                cursor = reinterpret_cast<unsigned char*>(Align32(reinterpret_cast<unsigned int>(cursor)));
            }
            m_drawEntries = reinterpret_cast<CMapMeshDrawEntry*>(cursor);

            cursor += static_cast<unsigned int>(m_displayListCount) * 0x10U;
            offset = 0;
            for (int i = 0; i < static_cast<int>(m_displayListCount); i++) {
                *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int>(m_drawEntries) + offset) = 0;
                *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned int>(m_drawEntries) + offset + 4) = 0;
                offset += 0x10;
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
    const float minInit = 10000000000.0f;
    const float maxInit = -10000000000.0f;

    m_bound.m_min.z = minInit;
    m_bound.m_min.y = minInit;
    m_bound.m_min.x = minInit;
    m_bound.m_max.z = maxInit;
    m_bound.m_max.y = maxInit;
    m_bound.m_max.x = maxInit;

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
