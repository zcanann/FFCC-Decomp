#ifndef _FFCC_MATERIALMAN_H_
#define _FFCC_MATERIALMAN_H_

#include "ffcc/mapshadow.h"
#include "ffcc/memory.h"
#include "ffcc/p_light.h"

#include <dolphin/gx.h>

class CChunkFile;
class CMaterial;
class CMaterialSet;
class CTexture;
class CTextureSet;
class CFullScreenShadow;
class CLightPcs;
class CAmemCacheSet;
struct Vec;
struct CBound;

class CTexScroll
{
public:
    CTexScroll();
    ~CTexScroll();

private:
    unsigned char m_type0;
    unsigned char m_type1;
    unsigned char m_pad[2];
    float m_u0;
    float m_v0;
    float m_u1;
    float m_v1;
};

class CMaterialMan
{
public:
    enum TEV_BIT
    {
        TODO,
    };

    CMaterialMan();
    
    void Init();
    void Quit();
    void InitEnv();
    void LockEnv();
    void SetBlendMode(CMaterialSet*, int);
    void addtev_bump_st(int, _GXTevScale);
    void addtev_bump_water(_GXTevScale);
    void addtev_bump_spec_col_water(_GXTevScale);
    void addtev_bump_jimen(_GXTevScale);
    void addtev_lightmap(long);
    void addtev_shadow(long);
    void addtev_stdShadow(unsigned long);
    void addtev_full_shadow(long);
    void SetUnderWaterTex();
    void SetMaterial(CMaterialSet*, int, int, _GXTevScale);
    void SetMaterialCharaShadow(CMaterial*);
    void SetMaterialPart(CMaterialSet*, int, int);
    void SetMaterialMenu(CMaterialSet*, int, int);
    void SetObjMatrix(float(*)[4], float(*)[4]);
    void SetTexScroll(float, float, float, float);
    void SetFullScreenShadow(CFullScreenShadow&, float(*)[4], long);
    void SetShadow(CMapShadow&, float(*)[4], int, unsigned long);
    void SetShadowBit32(CMapShadow::TARGET, unsigned long*, float(*)[4]);
    void SetPosition(CMapShadow::TARGET, Vec*, float, float, float(*)[4], int);
    void GetCharaShadow(int, CMaterial**, float(**)[4], Vec*, float, float, int);
    void SetShadowBound(CMapShadow::TARGET, CBound*, float(*)[4]);
    void InitVtxFmt(int, _GXCompType, int, _GXCompType, int, _GXCompType, int);
    void IncNumTevStage();
    void GetTexMtxCur();
    void GetTexCoordIdCur();
    int IncTexCoordIdCur();
    int IncTexMtxCur();
    int IncTexMapIdCur();
    void GetTexMapIdCur();
    void SetStdEnv();
    void DecTexCoordIdCur();
    void SetTevBit(CMaterialMan::TEV_BIT);
    void ErrorTexCoordIdCur();
    void ErrorTexMtxCur();
    void ErrorTexMapIdCur();
    void GetMemoryStage();
};

class CMaterial
{
public:
    CMaterial();
    ~CMaterial();
    void Create(unsigned long, CMaterialMan::TEV_BIT);
    int Set(_GXTexMapID);
    void CacheLoadTexture(CAmemCacheSet*);
    void CacheUnLoadTexture(CAmemCacheSet*);
    void CacheRefCnt0UpTexture(CAmemCacheSet*);
    void CacheDumpTexture(CAmemCacheSet*);
    void* operator new(unsigned long, CMemory::CStage*, char*, int);
    void IncNumTexture();
    void SetTevBit(CMaterialMan::TEV_BIT);
    void GetNumTexture();
    void SetTag(int);
    void AddTextureIdx(int, int);
};

class CMaterialSet
{
public:
    CMaterialSet();
    ~CMaterialSet();
    void* operator new(unsigned long, CMemory::CStage*, char*, int);
    void GetFreeMaterielIdx();
    void Create(CChunkFile&, CTextureSet*, CMaterialMan::TEV_BIT, CLightPcs::CBumpLight*);
    void SetTextureSet(CTextureSet*);
    void Calc();
    unsigned short FindTexName(char*, long*);
    void CacheLoadTexture(int, CAmemCacheSet*);
    void CacheUnLoadTexture(int, CAmemCacheSet*);
    void CacheRefCnt0UpTexture(int, CAmemCacheSet*);
    void CacheDumpTexture(int, CAmemCacheSet*);
    unsigned long Find(char*);
    void SetPartFromTextureSet(CTextureSet*, int);
    void ReleaseTag(CTextureSet*, int, CAmemCacheSet*);
    void AddMaterial(CMaterial*, int);
};

#endif // _FFCC_MATERIALMAN_H_
