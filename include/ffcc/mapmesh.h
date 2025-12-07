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
    void ReadOtmMesh(CChunkFile&, CMemory::CStage*, int, int);
    void SetRenderArray();
    void DrawMesh(unsigned short, unsigned short);
    void DrawMeshCharaShadow(unsigned short, unsigned short);
    void Draw(CMaterialSet*);
    void DrawPart(CMaterialSet*, int);
    void GetTexture(CMaterialSet*, int&);
    void SetDisplayListMaterial(CMaterialSet*, char**, CAmemCacheSet*);
    void pppCacheLoadModelTexture(CMaterialSet*, CAmemCacheSet*);
    void pppCacheUnLoadModelTexture(CMaterialSet*, CAmemCacheSet*);
    void pppCacheRefCnt0UpModelTexture(CMaterialSet*, CAmemCacheSet*);
    void pppCacheDumpModelTexture(CMaterialSet*, CAmemCacheSet*);
};

#endif // _FFCC_MAPMESH_H_
