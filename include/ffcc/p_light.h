#ifndef _FFCC_P_LIGHT_H_
#define _FFCC_P_LIGHT_H_

#include "ffcc/memory.h"
#include "ffcc/system.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

class COctTree;
struct Vec;

class CLightPcs : public CProcess
{
public:
    class CLight
    {
    public:
        CLight();
        void Set(CLightPcs::CLight*);

        u32 m_type;               // 0x00
        Vec m_position;           // 0x04
        Vec m_targetPosition;     // 0x10
        float m_attenRadius;      // 0x1C
        float m_attenFalloff;     // 0x20
        float m_range;            // 0x24
        float m_radius;           // 0x28
        float m_offsetX;          // 0x2C
        float m_offsetZ;          // 0x30
        u32 m_partMask;           // 0x34
        Vec m_direction;          // 0x38
        float m_spotScale;        // 0x44
        float m_specularScale;    // 0x48
        u8 m_spotFn;              // 0x4C
        u8 m_unk4D;               // 0x4D
        u8 m_directionMode;       // 0x4E
        u8 m_specularMode;        // 0x4F
        _GXColor m_targetColor[4];// 0x50
        u8 m_targetEnable[4];     // 0x60
        void* m_part;             // 0x64
        u8 m_bumpShade[4];        // 0x68
        GXLightObj m_gxLightObj;  // 0x6C
        float m_unkAC;            // 0xAC
    };
    class CBumpLight
        : public CLight
    {
    public:
        CBumpLight();
        
        void MakeLightMap();
        void SetTexture(_GXTexMapID, int);

        u8 m_hasTexture;      // 0xB0
        u8 m_useViewSpace;    // 0xB1
        u8 m_target;          // 0xB2
        u8 m_textureCount;    // 0xB3
        u8* m_textureData;    // 0xB4
        GXTexObj m_textures[4]; // 0xB8
    };
    enum TARGET
    {
        TODO,
    };

    CLightPcs();
    static CProcessCallbackTable m_table;

    void Init();
    void Quit();
    int GetTable(unsigned long);
    void create();
    void destroy();
    void DestroyBumpLightAll(CLightPcs::TARGET);
    void calc();
    void draw();
    void Add(CLightPcs::CLight*);
    CLightPcs::CBumpLight* GetFreeBumpLight(CLightPcs::TARGET);
    CLightPcs::CBumpLight* AddBump(CLightPcs::CLight*, CLightPcs::TARGET, CMemory::CStage*, int);
    void Clear();
    void SetMapColorAlpha(float (*)[4], _GXColor, _GXColor, unsigned char, float, float, float, unsigned char);
    void SetAmbient(_GXColor);
    void SetAmbientAlpha(float);
    void SetNumDiffuse(unsigned long);
    void SetDiffuseColor(unsigned long, _GXColor);
    void EnableLight(int, int);
    void SetDiffuse(unsigned long, _GXColor, Vec*, int);
    void SetPosition(CLightPcs::TARGET, Vec*, unsigned long);
    void SetBit32(CLightPcs::TARGET, unsigned long*);
    void SetPart(CLightPcs::TARGET, void*, unsigned char);
    void SetForEmissionModel(CLightPcs::TARGET, void*);
    void InsertOctTree(CLightPcs::TARGET, COctTree&);
    void MakeLightMap();
    void SetBumpTexMatirx(float (*)[4], CLightPcs::CBumpLight*, Vec*, unsigned char);
    float (*GetBumpIndTexMtx())[3] { return m_bumpIndTexMtx; }
    CBumpLight* GetBumpLight(CLightPcs::TARGET target, int index) { return &m_bumpLights[target][index]; }

    Mtx m_bumpTexMtx0;               // 0x04
    Mtx m_bumpTexMtx1;               // 0x34
    Mtx m_bumpTexMtx2;               // 0x64
    Mtx23 m_bumpIndTexMtx;            // 0x94
    u32 m_numDiffuse;                // 0xAC
    u32 m_loadedLightCount;          // 0xB0
    u32 m_loadedLightMask;           // 0xB4
    u32 m_sceneLightCount;           // 0xB8
    CLight m_diffuseLights[8];       // 0xBC
    CLight m_sceneLights[0x20];      // 0x63C
    CBumpLight m_bumpLights[4][8];   // 0x1C3C
    _GXColor m_mapLightColor[4];     // 0x433C
    Vec m_mapLightParams[3];         // 0x434C
    GXLightObj m_mapLightObj;        // 0x4370
};

typedef int CLight_size_check[(sizeof(CLightPcs::CLight) == 0xB0) ? 1 : -1];
typedef int CBumpLight_size_check[(sizeof(CLightPcs::CBumpLight) == 0x138) ? 1 : -1];
typedef int CLightPcs_size_check[(sizeof(CLightPcs) == 0x43B0) ? 1 : -1];

extern CLightPcs LightPcs;
extern CLightPcs::CBumpLight* gCharaPartWorkPtr;

#endif // _FFCC_P_LIGHT_H_
