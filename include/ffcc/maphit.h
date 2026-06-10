#ifndef _FFCC_MAPHIT_H_
#define _FFCC_MAPHIT_H_

#include <dolphin/mtx.h>

class CChunkFile;
class CMapCylinder;
class CMapHit;
class CBound;

int FindIntersection(const Vec&, const Vec&, const CMapCylinder&, float&);

extern "C" const float kMapHitBoundsMinInit;
extern "C" const float kMapHitBoundsMaxInit;

struct CMapCylinderProbeView
{
    Vec m_direction;  // 0x0c
    float m_radius;   // 0x18
    float m_height;   // 0x1c
    Vec m_top;        // 0x20
    Vec m_direction2; // 0x2c
    float m_radius2;  // 0x38
    float m_height2;  // 0x3c
};
typedef char CMapCylinderProbeView_size_check[(sizeof(CMapCylinderProbeView) == 0x34) ? 1 : -1];

struct CMapCylinderBound
{
    Vec m_min; // 0x00
    Vec m_max; // 0x0c
};
typedef char CMapCylinderBound_size_check[(sizeof(CMapCylinderBound) == 0x18) ? 1 : -1];

class CMapCylinder
{
public:
    CMapCylinder()
    {
        float min = kMapHitBoundsMinInit;

        m_bound.m_min.z = min;
        m_bound.m_min.y = min;
        m_bound.m_min.x = min;

        m_bound.m_max.z = kMapHitBoundsMaxInit;
        m_bound.m_max.y = kMapHitBoundsMaxInit;
        m_bound.m_max.x = kMapHitBoundsMaxInit;
    }

    CMapCylinder(float min, float max)
    {
        float minBound = min;
        float maxBound = max;

        m_bound.m_min.z = minBound;
        m_bound.m_min.y = minBound;
        m_bound.m_min.x = minBound;

        m_bound.m_max.z = maxBound;
        m_bound.m_max.y = maxBound;
        m_bound.m_max.x = maxBound;
    }

    CBound* GetBound() { return reinterpret_cast<CBound*>(&m_bound); }
    CMapCylinderProbeView& Probe() { return *reinterpret_cast<CMapCylinderProbeView*>(&m_top); }
    const CMapCylinderProbeView& Probe() const { return *reinterpret_cast<const CMapCylinderProbeView*>(&m_top); }

    Vec m_bottom;    // 0x00
    Vec m_top;       // 0x0c
    Vec m_axis;      // 0x18
    float m_radius;  // 0x24
    CMapCylinderBound m_bound; // 0x28
};
typedef char CMapCylinder_size_check[(sizeof(CMapCylinder) == 0x40) ? 1 : -1];

class CMapHitFace
{
public:
    CMapHitFace();

    Vec m_normal;                   // 0x00
    float m_planeD;                 // 0x0c
    Vec m_boundsMin;                // 0x10
    Vec m_boundsMax;                // 0x1c
    float m_radiusScale;            // 0x28
    float m_vertexOffsets[3][2];    // 0x2c
    unsigned char m_edgeFlags;      // 0x44
    unsigned char m_projectionAxis; // 0x45
    unsigned char m_vertexCount;    // 0x46
    unsigned char m_groupIndex;     // 0x47
    unsigned short m_vertexIndices[3]; // 0x48
    unsigned char m_flags;          // 0x4e
    unsigned char m_drawFlags;      // 0x4f
};

class CMapHit
{
public:
    CMapHit();
    ~CMapHit();

    int ReadOtmHit(CChunkFile&);
    int CheckHitFaceCylinder(unsigned long);
    void GetHitFaceNormal(Vec*);
    int CalcHitSlide(Vec*, float);
    void CalcHitPosition(Vec*);
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long);
    void CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
    void CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long);
    void Draw();
    void DrawWire();
    void DrawNormal();

    unsigned short m_vertexCount; // 0x00
    unsigned short m_faceCount;   // 0x02
    Vec m_positionMin;            // 0x04
    Vec m_positionMax;            // 0x10
    Vec* m_vertices;              // 0x1c
    CMapHitFace* m_faces;         // 0x20
};

union UMapHitDrawMode
{
    unsigned long m_word;
    struct {
        unsigned char m_mode;
        unsigned char m_drawFlags;
        unsigned char m_pad[2];
    } m_fields;
};

struct CMapHitDrawMode
{
    unsigned char m_byte;
};

extern UMapHitDrawMode s_bitMask;
extern CMapHitDrawMode g_MapHitDrawMode;
extern int g_hit_edge_idx_min;
extern float g_hit_t;
extern float g_hit_t_min;
extern float g_hit_t_slide_min;
extern CMapHitFace* g_hit_f;
extern CMapHitFace* g_hit_lpface;
extern CMapHitFace* g_hit_lpface_min;
extern unsigned char g_MapHitFaceFlag;
#define gMapHitFaceFlag g_MapHitFaceFlag

#define gMapHitFace g_hit_f

#endif // _FFCC_MAPHIT_H_
