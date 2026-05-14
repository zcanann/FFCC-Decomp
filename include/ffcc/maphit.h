#ifndef _FFCC_MAPHIT_H_
#define _FFCC_MAPHIT_H_

#include <dolphin/mtx.h>

class CChunkFile;
class CMapCylinder;
class CMapHit;
class CBound;

int FindIntersection(const Vec&, const Vec&, const CMapCylinder&, float&);
void CheckLineCylinder(const Vec&, const Vec&, const CMapCylinder&, float&);

class CMapCylinder
{
public:
    CMapCylinder();

    Vec m_bottom;    // 0x00
    Vec m_top;       // 0x0c
    Vec m_axis;      // 0x18
    float m_radius;  // 0x24
    Vec m_boundsMin; // 0x28
    Vec m_boundsMax; // 0x34
};

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

extern unsigned char gMapHitDrawMode;
extern int g_hit_edge_idx_min;
extern float g_hit_edge_t;
extern float g_hit_t;
extern float g_hit_t_min;
extern float g_hit_t_slide_min;
extern CMapHitFace* g_hit_f;
extern CMapHitFace* g_hit_lpface;
extern CMapHitFace* g_hit_lpface_min;
extern unsigned char gMapHitFaceFlag;

#define gMapHitFace g_hit_f

#endif // _FFCC_MAPHIT_H_
