#ifndef _FFCC_MAPOBJ_H_
#define _FFCC_MAPOBJ_H_

#include "ffcc/mapkeyframe.h"
#include "ffcc/p_light.h"

#include <dolphin/gx/GXStruct.h>

class CChunkFile;
class CMapCylinder;
class CMapShadow;
class CMapAnimRun;
class CMapObjAtr;
class CMapObjAtrPlaySta;
class CMapObjAtrMime;
class CMapObjAtrSpotLight;
class CMapObjAtrPointLight;
class CMapObjAtrMeshName;
class CMapObj;
class CMaterialMan;
class CCameraPcs;
struct Vec;

static inline void InitMapObjAtrColorKeyFrame(CMapKeyFrame& keyFrame)
{
    keyFrame.m_junTable = 0;
    keyFrame.m_keyFrame = 0;
    keyFrame.m_keyValue = 0;
    keyFrame.m_splineTable = 0;
    keyFrame.m_loop = 1;
    keyFrame.m_isRun = 0;
}

class CMapObjAtr
{
public:
    enum TYPE
    {
        POINT_LIGHT = 0,
        SPOT_LIGHT = 1,
        MIME = 2,
        MESH_NAME = 3,
        PLAY_STA = 4,
    };
    
    CMapObjAtr();
    virtual ~CMapObjAtr();

    TYPE m_type; // 0x04
};

class CMapObjAtrPlaySta : public CMapObjAtr
{
public:
    CMapObjAtrPlaySta();
    ~CMapObjAtrPlaySta();

    unsigned char m_playStaNo; // 0x08
    unsigned char m_pad09[3];
};

class CMapObjAtrMime : public CMapObjAtr
{
public:
    CMapObjAtrMime();
    ~CMapObjAtrMime();

    unsigned char m_vertexListCount; // 0x08
    unsigned char m_pad09[3];
    float** m_vertexLists;           // 0x0C
    int m_vertexCount;               // 0x10
    CMapKeyFrame m_keyFrame;         // 0x14
};

class CMapObjAtrSpotLight : public CMapObjAtr
{
public:
    CMapObjAtrSpotLight()
    {
        m_type = SPOT_LIGHT;
        m_light = 0;
        m_intensity = 1.0f;
        m_falloff = 1.0f;
        m_colorMode = 0;
        m_useAltColor = 0;
        m_keyFrameCount = 0;
    }

    ~CMapObjAtrSpotLight();

    _GXColor m_color;              // 0x08
    _GXColor m_altColor;           // 0x0C
    CMapObj* m_target;             // 0x10
    float m_radius;                // 0x14
    float m_nearRange;             // 0x18
    float m_farRange;              // 0x1C
    float m_intensity;             // 0x20
    float m_falloff;               // 0x24
    float m_angle;                 // 0x28
    unsigned char m_colorMode;     // 0x2C
    unsigned char m_useAltColor;   // 0x2D
    unsigned char m_unknown2E;     // 0x2E
    unsigned char m_unknown2F;     // 0x2F
    unsigned char m_keyFrameCount; // 0x30
    unsigned char m_pad31[3];
    _GXColor m_baseColor;          // 0x34
    CLightPcs::CLight* m_light;    // 0x38
    unsigned char m_colorCount;    // 0x3C
    unsigned char m_altColorCount; // 0x3D
    unsigned char m_pad3E[2];
    _GXColor m_colors[16];         // 0x40
    _GXColor m_altColors[16];      // 0x80
    CMapKeyFrame m_colorKeyFrame;  // 0xC0
    CMapKeyFrame m_altColorKeyFrame; // 0xE8
};

class CMapObjAtrPointLight : public CMapObjAtr
{
public:
    CMapObjAtrPointLight()
    {
        m_type = POINT_LIGHT;
        m_colorMode = 0;
        m_useAltColor = 0;
        m_unknown20 = 0;
    }

    ~CMapObjAtrPointLight();

    _GXColor m_color;              // 0x08
    _GXColor m_altColor;           // 0x0C
    float m_radius;                // 0x10
    float m_intensity;             // 0x14
    unsigned char m_pad18[4];
    unsigned char m_colorMode;     // 0x1C
    unsigned char m_colorCount;    // 0x1D
    unsigned char m_altColorCount; // 0x1E
    unsigned char m_useAltColor;   // 0x1F
    unsigned char m_unknown20;     // 0x20
    unsigned char m_pad21[3];
    _GXColor m_colors[16];         // 0x24
    _GXColor m_altColors[16];      // 0x64
    CMapKeyFrame m_colorKeyFrame;  // 0xA4
    CMapKeyFrame m_altColorKeyFrame; // 0xCC
};

class CMapObjAtrMeshName : public CMapObjAtr
{
public:
    CMapObjAtrMeshName();
    ~CMapObjAtrMeshName();

    char m_name[0x20]; // 0x08
};

typedef char CMapObjAtr_size_check[(sizeof(CMapObjAtr) == 0x8) ? 1 : -1];
typedef char CMapObjAtrPlaySta_size_check[(sizeof(CMapObjAtrPlaySta) == 0xC) ? 1 : -1];
typedef char CMapObjAtrMime_size_check[(sizeof(CMapObjAtrMime) == 0x3C) ? 1 : -1];
typedef char CMapObjAtrSpotLight_size_check[(sizeof(CMapObjAtrSpotLight) == 0x110) ? 1 : -1];
typedef char CMapObjAtrPointLight_size_check[(sizeof(CMapObjAtrPointLight) == 0xF4) ? 1 : -1];
typedef char CMapObjAtrMeshName_size_check[(sizeof(CMapObjAtrMeshName) == 0x28) ? 1 : -1];

class CMapObj
{
public:
    void Init();
    CMapObj();
    ~CMapObj();
    int ReadOtmObj(CChunkFile&);
    void CalcMtx(float (*)[4], unsigned char);
    void SetShow_r(int);
    void SetShow(int);
    void SetLink();
    void Calc();
    void SetDrawEnv();
    void IsDrawAlphaLight();
    void Draw(unsigned char);
    void SetDrawFlag();
    void DrawHit();
    void DrawHitWire();
    void DrawHitNormal();
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
    void CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
    void GetHitFaceNormal(Vec*);
    int CalcHitSlide(Vec*, float);
    void CalcHitPosition(Vec*);
    void SetMime(int, int, int);
    void SetCalcMtx();

    CMapObj* m_parent;            // 0x00
    CMapObj* m_child;             // 0x04
    CMapObj* m_next;              // 0x08
    void* m_mapData;              // 0x0C
    void* m_bumpLight;            // 0x10
    unsigned char m_baseDrawPriority; // 0x14
    unsigned char m_drawPriority;     // 0x15
    short m_bumpObjId;            // 0x16
    unsigned char m_showFlags;      // 0x18
    unsigned char m_unknown19;     // 0x19
    unsigned char m_bumpTexMatrixMode; // 0x1A
    unsigned char m_calcMtxPending; // 0x1B
    unsigned char m_localMtxDirty;  // 0x1C
    unsigned char m_mapDataType; // 0x1D
    signed char m_meshType;      // 0x1E
    signed char m_octTreeIndex;      // 0x1F
    unsigned char m_unknown20;     // 0x20
    unsigned char m_useAmbientColor; // 0x21
    unsigned char m_enableFullScreenShadow; // 0x22
    unsigned char m_lightAlpha;      // 0x23
    unsigned char m_colorAlphaRate;  // 0x24
    unsigned char m_cameraSemiTransBeyondMax; // 0x25
    unsigned char m_cameraSemiTransActive; // 0x26
    unsigned char m_disableZWrite;   // 0x27
    short m_cameraSemiTransAlpha;       // 0x28
    short m_cameraSemiTransTargetAlpha; // 0x2A
    short m_cameraSemiTransStep;        // 0x2C
    unsigned short m_objId;         // 0x2E
    unsigned short m_effectId;      // 0x30
    unsigned short m_groupId;       // 0x32
    unsigned short m_meshId;        // 0x34
    char m_pad36[0x02];
    int m_lightSetIndex;            // 0x38
    unsigned long m_shadowTarget;   // 0x3C
    float m_zBufferOffset;          // 0x40
    float m_cameraSemiTransNear;    // 0x44
    float m_cameraSemiTransFar;     // 0x48
    float m_cameraSemiTransMinAlpha; // 0x4C
    float m_cameraSemiTransMaxAlpha; // 0x50
    float m_cameraSemiTransFadeRange; // 0x54
    float m_transRateX;             // 0x58
    float m_transRateY;             // 0x5C
    float m_transRateZ;             // 0x60
    float m_localTranslateX;        // 0x64
    float m_localTranslateY;        // 0x68
    float m_localTranslateZ;        // 0x6C
    float m_localRotationX;         // 0x70
    float m_localRotationY;         // 0x74
    float m_localRotationZ;         // 0x78
    float m_localScaleX;            // 0x7C
    float m_localScaleY;            // 0x80
    float m_localScaleZ;            // 0x84
    float m_localMtx[3][4];         // 0x88
    float m_worldMtx[3][4];         // 0xB8
    _GXColor m_ambientColor;        // 0xE8
    CMapObjAtr* m_attribute;        // 0xEC
};

typedef char CMapObj_size_check[(sizeof(CMapObj) == 0xF0) ? 1 : -1];
#endif // _FFCC_MAPOBJ_H_
