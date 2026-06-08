#ifndef _FFCC_MATERIALMAN_H_
#define _FFCC_MATERIALMAN_H_

#include "ffcc/color.h"
#include "ffcc/manager.h"
#include "ffcc/mapshadow.h"
#include "ffcc/memory.h"
#include "ffcc/p_light.h"
#include "ffcc/ptrarray_decl.h"
#include "ffcc/ref.h"

#include <dolphin/gx.h>

class CChunkFile;
class CMaterial;
class CMaterialSet;
class CTexture;
class CTextureSet;
class CFullScreenShadow;
class CLightPcs;
class CAmemCacheSet;
class CMapKeyFrame;
class CMapTexAnim;
struct Vec;
struct CBound;

class CTexScroll
{
public:
    CTexScroll();
    ~CTexScroll();

    unsigned char m_type0;
    unsigned char m_type1;
    unsigned char m_pad[2];
    float m_u0;
    float m_v0;
    union {
        float m_u1;
        CMapKeyFrame* m_uKeyFrame;
    };
    union {
        float m_v1;
        CMapKeyFrame* m_vKeyFrame;
    };
};
typedef char CTexScroll_size_check[(sizeof(CTexScroll) == 0x14) ? 1 : -1];

class CMaterialMan : public CManager
{
    friend class CMaterial;

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
    void SetStoneTexObj(_GXTexObj*);
    void SetObjMatrix(float(*)[4], float(*)[4]);
    void SetTexScroll(float, float, float, float);
    void SetFullScreenShadow(CFullScreenShadow&, float(*)[4], long);
    void SetShadow(CMapShadow&, float(*)[4], int, unsigned long);
    void SetShadowBit32(CMapShadow::TARGET, unsigned long*, float(*)[4]);
    void SetPosition(CMapShadow::TARGET, Vec*, float, float, float(*)[4], int);
    int GetCharaShadow(int, CMaterial**, float(**)[4], Vec*, float, float, int);
    void SetShadowBound(CMapShadow::TARGET, CBound*, float(*)[4]);
    void InitVtxFmt(int, _GXCompType, int, _GXCompType, int, _GXCompType, int);
    void IncNumTevStage();
    int GetTexMtxCur();
    int GetTexCoordIdCur();
    int IncTexCoordIdCur();
    int IncTexMtxCur();
    int IncTexMapIdCur();
    int GetTexMapIdCur();
    void SetStdEnv();
    void DecTexCoordIdCur();
    void SetTevBit(CMaterialMan::TEV_BIT);
    void ErrorTexCoordIdCur();
    void ErrorTexMtxCur();
    void ErrorTexMapIdCur();
    CMemory::CStage* GetMemoryStage();
    void ClearManaParaboloidTexObjs()
    {
        m_manaParaboloidTexObj0 = 0;
        m_manaParaboloidTexObj1 = 0;
    }
    void SetManaAlpha(unsigned char alpha)
    {
        m_manaAlpha = alpha;
    }
    void SetBlendOverrideMode(unsigned char mode)
    {
        m_blendOverrideMode = mode;
    }
    void OrCurrentEnvTevBit(unsigned int tevBit)
    {
        m_curEnvTevBit |= tevBit;
    }
    unsigned char GetManaAlpha()
    {
        return m_manaAlpha;
    }
    void SetDefaultDrawEnv(unsigned int tevBit)
    {
        m_curEnvTevBit = tevBit;
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_stdTexMapId = 0;
        m_texMapIdCur = 0;
        m_stdTexMtx = 0x1E;
        m_texMtxCur = 0x1E;
        m_stdTexCoordId = 0;
        m_texCoordIdCur = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
    }
    void LockEnvInline()
    {
        m_stdTexMapId = m_texMapIdCur;
        m_stdTexMtx = m_texMtxCur;
        m_stdTexCoordId = m_texCoordIdCur;
        m_stdEnvTevBit = m_curEnvTevBit;
    }
    void SetDefaultStdDrawEnv(unsigned int tevBit)
    {
        m_curEnvTevBit = tevBit;
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_texMapIdCur = 0;
        m_texMtxCur = 0x1E;
        m_texCoordIdCur = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_stdEnvTevBit = tevBit;
    }
    void SetGeometryArraySource(void* arraySource)
    {
        m_geometryArraySource = arraySource;
    }
    void* GetGeometryArraySource()
    {
        return m_geometryArraySource;
    }
    float (*GetObjTextureMtx()) [4]
    {
        return m_objTextureMtx;
    }
    void SetManaReflectionEnv(Vec* reflectionVec, _GXTexObj* paraboloidTexObj0, _GXTexObj* paraboloidTexObj1, unsigned int tevBit)
    {
        m_manaReflectionVec = reflectionVec;
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_texMapIdCur = 0;
        m_texMtxCur = 0x1E;
        m_texCoordIdCur = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
        m_curEnvTevBit = tevBit;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_stdEnvTevBit = tevBit;
        m_manaParaboloidTexObj0 = paraboloidTexObj0;
        m_manaParaboloidTexObj1 = paraboloidTexObj1;
    }
    void SetManaReflectionEnv(Vec* reflectionVec, _GXTexObj* paraboloidTexObj0, unsigned int tevBit)
    {
        m_manaReflectionVec = reflectionVec;
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_texMapIdCur = 0;
        m_texMtxCur = 0x1E;
        m_texCoordIdCur = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
        m_curEnvTevBit = tevBit;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_stdEnvTevBit = tevBit;
        m_manaParaboloidTexObj0 = paraboloidTexObj0;
    }
    void SetChangeTexReflectionEnv(void* arraySource, _GXTexObj* texObj, unsigned int tevBit)
    {
        m_geometryArraySource = arraySource;
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_texMapIdCur = 0;
        m_texMtxCur = 0x1E;
        m_texCoordIdCur = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
        m_curEnvTevBit = tevBit;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_stdEnvTevBit = tevBit;
        m_manaParaboloidTexObj0 = texObj;
    }
    void SetChangeTexReflectionArray(void* arraySource)
    {
        SetGeometryArraySource(arraySource);
    }
    void SetChangeTexReflectionTexture(_GXTexObj* texObj)
    {
        m_manaParaboloidTexObj0 = texObj;
    }
    void SaveCurrentEnvAsStd()
    {
        m_stdTexMapId = m_texMapIdCur;
        m_stdTexMtx = m_texMtxCur;
        m_stdTexCoordId = m_texCoordIdCur;
        m_stdEnvTevBit = m_curEnvTevBit;
    }
    void SetChangeTexReflectionState(unsigned int tevBit, unsigned int stdTevBit)
    {
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_texMapIdCur = 0;
        m_texMtxCur = 0x1E;
        m_texCoordIdCur = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
        m_curEnvTevBit = tevBit;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_curEnvTevBit = stdTevBit;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_stdEnvTevBit = stdTevBit;
    }
    void SetChangeTexReflectionState(_GXTexObj* texObj, unsigned int tevBit, unsigned int stdTevBit)
    {
        m_stdTexMapId = 0;
        m_curEnvTevBit = tevBit;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_texMapIdCur = 0;
        m_texMtxCur = 0x1E;
        m_texCoordIdCur = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
        m_curEnvTevBit = stdTevBit;
        m_manaParaboloidTexObj0 = texObj;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_stdEnvTevBit = stdTevBit;
    }
    void SetEmissionTextureEnv(unsigned int tevBit)
    {
        m_activeEnvTevBit = 0xFFFFFFFF;
        m_vtxDescMode = 0xFF;
        m_curEnvTevBit = tevBit;
        m_texMapIdCur = 0;
        m_texMtxCur = 0x1E;
        m_texCoordIdCur = 0;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_blendMode = 0xFF;
        m_fogEnable = 0xFF;
        m_shadowMaterialCount = 0;
        m_shadowTextureCount = 0;
        m_shadowKColorMask = 0;
        m_curEnvTevBit |= 0x40000;
        m_stdTexMapId = 0;
        m_stdTexMtx = 0x1E;
        m_stdTexCoordId = 0;
        m_stdEnvTevBit = m_curEnvTevBit;
    }

private:
    void* m_geometryArraySource;        // 0x04
    Vec* m_manaReflectionVec;           // 0x08
    _GXTexObj* m_underWaterTexture;      // 0x0C
    Mtx m_underWaterTexMtx;              // 0x10
    unsigned int m_stdEnvTevBit;         // 0x40
    unsigned int m_activeEnvTevBit;      // 0x44
    unsigned int m_curEnvTevBit;         // 0x48
    unsigned char m_vtxDescMode;         // 0x4C
    unsigned char m_shadowMaterialType[0x0B]; // 0x4D
    int m_shadowMaterialCount;           // 0x58
    int m_shadowTextureCount;            // 0x5C
    unsigned int m_numTevStage;          // 0x60
    Mtx m_fullScreenShadowMtx0;          // 0x64
    Mtx m_fullScreenShadowMtx1;          // 0x94
    _GXTexObj* m_fullScreenShadowTexObj0; // 0xC4
    _GXTexObj* m_fullScreenShadowTexObj1; // 0xC8
    unsigned char m_pad0CC[0x04];
    _GXTexObj* m_manaParaboloidTexObj0;  // 0xD0
    unsigned char m_pad0D4[0x08];
    _GXTexObj* m_manaParaboloidTexObj1;  // 0xDC
    unsigned char m_pad0E0[0x04];
    unsigned char m_manaAlpha;           // 0xE4
    unsigned char m_pad0E5[0x03];
    Mtx m_objTextureMtx;                  // 0xE8
    unsigned char m_pad118[0x04];
    int m_texMapIdCur;                   // 0x11C
    int m_texMtxCur;                     // 0x120
    int m_texCoordIdCur;                 // 0x124
    int m_stdTexMapId;                   // 0x128
    int m_stdTexMtx;                     // 0x12C
    int m_stdTexCoordId;                 // 0x130
    int m_texMapIdCurShadow;             // 0x134
    int m_texMtxCurShadow;               // 0x138
    int m_texCoordIdCurShadow;           // 0x13C
    unsigned int m_unknown140;           // 0x140
    unsigned int m_texScroll0TexMtx;     // 0x144
    unsigned int m_texScroll0TexCoord;   // 0x148
    unsigned int m_unknown14C;           // 0x14C
    unsigned int m_texScroll1TexMtx;     // 0x150
    unsigned int m_texScroll1TexCoord;   // 0x154
    int m_shadowTexMapIds[5];            // 0x158
    int m_shadowTexMtxIds[5];            // 0x16C
    int m_shadowTexCoordIds[5];          // 0x180
    int m_fullScreenShadowTexMapIds0[2]; // 0x194
    int m_fullScreenShadowTexMtxIds0[2]; // 0x19C
    int m_fullScreenShadowTexCoordIds0[2]; // 0x1A4
    int m_fullScreenShadowTexMapIds1[2]; // 0x1AC
    int m_fullScreenShadowTexMtxIds1[2]; // 0x1B4
    int m_fullScreenShadowTexCoordIds1[2]; // 0x1BC
    int m_bumpTexMapIds[4];              // 0x1C4
    int m_bumpTexMtxIds[5];              // 0x1D4
    int m_bumpTexCoordIds[7];            // 0x1E8
    unsigned char m_fullShadowTevColor;  // 0x204
    unsigned char m_blendMode;           // 0x205
    unsigned char m_fogEnable;           // 0x206
    unsigned char m_blendOverrideMode;   // 0x207
    unsigned char m_shadowKColorMask;    // 0x208
    unsigned char m_shadowKColorIds[5];  // 0x209
    unsigned char m_shadowIndices[5];    // 0x20E
    CColor m_color213;                   // 0x213
    CMemory::CStage* m_materialStage;    // 0x218
};

class CMaterial : public CRef
{
    friend class CMaterialMan;
    friend class CTexAnimSet;
    friend class CMaterialSet;
    friend class CMapTexAnim;

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
    unsigned short GetTextureCount() const
    {
        return m_textureCount;
    }
    unsigned char GetMaterialId() const
    {
        return m_unkA6;
    }
    short GetTextureIndex(int index) const
    {
        return m_textureIndices[index];
    }
    int IsFurEnabled() const
    {
        return m_singleTextureFlag != 0;
    }
    CTexture* GetFurPickTexture()
    {
        return m_textureData.m_textures[1];
    }
    CTexture* GetFurTexture(int index)
    {
        return m_textureData.m_textures[index + 2];
    }
    void SetTag(int);
    void AddTextureIdx(int, int);
    void SetMaterialColor(unsigned int rgba)
    {
        GXColor& color = m_materialColor;
        color.r = static_cast<unsigned char>((rgba >> 24) & 0xFF);
        color.g = static_cast<unsigned char>((rgba >> 16) & 0xFF);
        color.b = static_cast<unsigned char>((rgba >> 8) & 0xFF);
        color.a = static_cast<unsigned char>(rgba & 0xFF);
    }
    unsigned long GetTevBit()
    {
        return m_tevBit;
    }
    CTexture* GetTexture(int index)
    {
        return m_textureData.m_textures[index];
    }
    CTexScroll* GetTexScroll(int index)
    {
        return &m_textureData.m_texScroll[index];
    }

private:
    friend class CTexAnimSet;

    char m_name[0x10];                    // 0x008
    unsigned short m_textureCount;        // 0x018
    short m_textureIndices[5];            // 0x01A
    unsigned long m_tevBit;               // 0x024
    CLightPcs::CBumpLight* m_bumpLight;   // 0x028
    float m_scaleU;                       // 0x02C
    float m_scaleV;                       // 0x030
    char m_texShiftU;                     // 0x034
    char m_texShiftV;                     // 0x035
    unsigned char m_unk36;                // 0x036
    unsigned char m_pad37;                // 0x037
    GXColor m_materialColor;              // 0x038
    struct TextureColorView
    {
        CTexture* m_texture0;             // 0x03C
        CTexture* m_texture1;             // 0x040
        CTexture* m_texture2;             // 0x044
    };
    struct {
        union {
            CTexture* m_textures[4];      // 0x03C
            TextureColorView m_textureColorView;
        };
        CTexScroll m_texScroll[4];        // 0x04C
    } m_textureData;
    int m_pdtSlotIndex;                   // 0x09C
    unsigned char m_blendMode;            // 0x0A0
    unsigned char m_fogEnable;            // 0x0A1
    unsigned char m_materialType;         // 0x0A2
    unsigned char m_bumpLightDirect;      // 0x0A3
    unsigned char m_shadowKColorId;       // 0x0A4
    unsigned char m_unkA5;                // 0x0A5
    unsigned char m_unkA6;                // 0x0A6
    unsigned char m_singleTextureFlag;    // 0x0A7
};

typedef int CMaterial_size_mismatch[(sizeof(CMaterial) == 0xA8) ? 1 : -1];

class CMaterialSet : public CRef
{
public:
    CMaterialSet();
    ~CMaterialSet();
    void* operator new(unsigned long, CMemory::CStage*, char*, int);
    void GetFreeMaterielIdx();
    void Create(CChunkFile&, CTextureSet*, CMaterialMan::TEV_BIT, CLightPcs::CBumpLight*);
    void SetTextureSet(CTextureSet*);
    void Calc();
    unsigned int FindTexName(char*, long*);
    void CacheLoadTexture(int, CAmemCacheSet*);
    void CacheUnLoadTexture(int, CAmemCacheSet*);
    void CacheRefCnt0UpTexture(int, CAmemCacheSet*);
    void CacheDumpTexture(int, CAmemCacheSet*);
    unsigned long Find(char*);
    void SetPartFromTextureSet(CTextureSet*, int);
    void ReleaseTag(CTextureSet*, int, CAmemCacheSet*);
    void AddMaterial(CMaterial*, int);

    CPtrArray<CMaterial*> m_materials;        // 0x008
    int GetNumMaterial()
    {
        return m_materials.GetSize();
    }
    CMaterial* GetMaterial(long index)
    {
        return m_materials[index];
    }
};

extern CMaterialMan MaterialMan;

#endif // _FFCC_MATERIALMAN_H_
