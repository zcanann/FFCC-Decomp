#ifndef _FFCC_MAPHIT_H_
#define _FFCC_MAPHIT_H_

#include <dolphin/mtx.h>

class CChunkFile;
class CMapCylinder;
class CMapHit;
class CBound;

void FindIntersection(const Vec&, const Vec&, const CMapCylinder&, float&);
void CheckLineCylinder(const Vec&, const Vec&, const CMapCylinder&, float&);

class CMapCylinder
{
public:
    CMapCylinder();
    void operator=(const CMapCylinder&);

    Vec m_bottom;     // 0x0
    Vec m_direction;  // 0xc
    float m_radius;   // 0x18
    float m_height;   // 0c1c
    Vec m_top;        // 0x20
    Vec m_direction2; // 0x2c
    float m_radius2;  // 0x38
    float m_height2;  // 0x3c
};

class CMapHitFace
{
public:
    CMapHitFace();

    // TODO: decode concrete fields used by collision and rendering.
    unsigned char _unk0[0x10]; // 0x00
    Vec m_boundsMin;            // 0x10
    Vec m_boundsMax;            // 0x1c
    unsigned char _unk28[0x28]; // 0x28
};

class CMapHit
{
public:
    CMapHit();
    ~CMapHit();

    void ReadOtmHit(CChunkFile&);
    int CheckHitFaceCylinder(unsigned long);
    void GetHitFaceNormal(Vec*);
    int CalcHitSlide(Vec*, float);
    void CalcHitPosition(Vec*);
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long);
    int CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
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

#endif // _FFCC_MAPHIT_H_
