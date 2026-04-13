#ifndef _FFCC_MAPMESH_H_
#define _FFCC_MAPMESH_H_

#include "ffcc/memory.h"

#include <dolphin/mtx.h>

class CChunkFile;
class CMaterialSet;
class CMaterialMan;
class CMaterial;
class CAmemCacheSet;

class CMapMesh
{
public:
    CMapMesh();
    ~CMapMesh();

    void Destroy();
    void Ptr2Off();
    void Off2Ptr();
    unsigned int ReadOtmMesh(CChunkFile&, CMemory::CStage*, int, int);
    void SetRenderArray();
    void DrawMesh(unsigned short, unsigned short);
    void DrawMeshCharaShadow(unsigned short, unsigned short);
    void Draw(CMaterialSet*);
    void DrawPart(CMaterialSet*, int);
    void* GetTexture(CMaterialSet*, int&);
    void SetDisplayListMaterial(CMaterialSet*, char**, CAmemCacheSet*);
    void pppCacheLoadModelTexture(CMaterialSet*, CAmemCacheSet*);
    void pppCacheUnLoadModelTexture(CMaterialSet*, CAmemCacheSet*);
    void pppCacheRefCnt0UpModelTexture(CMaterialSet*, CAmemCacheSet*);
    void pppCacheDumpModelTexture(CMaterialSet*, CAmemCacheSet*);

    unsigned short m_vertexCount;      // 0x00
    unsigned short m_normalCount;      // 0x02
    unsigned short m_nbtCount;         // 0x04
    unsigned short m_uvCount;          // 0x06
    unsigned short m_colorCount;       // 0x08
    unsigned short m_displayListCount; // 0x0A
    float m_bboxMinX;                  // 0x0C
    float m_bboxMinY;                  // 0x10
    float m_bboxMinZ;                  // 0x14
    float m_bboxMaxX;                  // 0x18
    float m_bboxMaxY;                  // 0x1C
    float m_bboxMaxZ;                  // 0x20
    void* m_meshData;                  // 0x24
    void* m_displayListData;           // 0x28
    void* m_vertices;                  // 0x2C
    void* m_normals;                   // 0x30
    void* m_nbt;                       // 0x34
    void* m_uvPairs;                   // 0x38
    void* m_colors;                    // 0x3C
    void* m_drawEntries;               // 0x40
};

#endif // _FFCC_MAPMESH_H_
