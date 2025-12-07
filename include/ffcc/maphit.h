#ifndef _FFCC_MAPHIT_H_
#define _FFCC_MAPHIT_H_

#include <dolphin/mtx.h>

class CChunkFile;
class CMapCylinder;
class CMapHit;
class CBound;

void FindIntersection(const Vec&, const Vec&, const CMapCylinder&, float&);
void CheckLineCylinder(const Vec&, const Vec&, const CMapCylinder&, float&);
void GXEnd(void);

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
};

class CMapHit
{
public:
    CMapHit();
    ~CMapHit();

    void ReadOtmHit(CChunkFile&);
    void CheckHitFaceCylinder(unsigned long);
    void GetHitFaceNormal(Vec*);
    void CalcHitSlide(Vec*, float);
    void CalcHitPosition(Vec*);
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
    int CheckHitCylinder(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long);
    int CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
    int CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long);
    void Draw();
    void DrawWire();
    void DrawNormal();
};

#endif // _FFCC_MAPHIT_H_
