#ifndef _FFCC_MAPMESH_H_
#define _FFCC_MAPMESH_H_

class CChunkFile;
class CMemory;
class CMaterialSet;
class CMaterialMan;
class CMaterial;
class CAmemCacheSet;
struct S16Vec;

class CMapMesh
{
public:
    CMapMesh();
    void Destroy();
    ~CMapMesh();
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
