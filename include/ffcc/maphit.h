#ifndef _FFCC_MAPHIT_H_
#define _FFCC_MAPHIT_H_

class CChunkFile;
class CMapCylinder;
class CMapHit;
class CMapHitFace;
class CBound;
struct Vec;

void FindIntersection(const Vec&, const Vec&, const CMapCylinder&, float&);
void CheckLineCylinder(const Vec&, const Vec&, const CMapCylinder&, float&);
void GXEnd(void);

class CMapCylinder
{
public:
    CMapCylinder();
    void operator=(const CMapCylinder&);
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
    void CheckHitCylinder(CMapCylinder*, Vec*, unsigned long);
    void CheckHitCylinder(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long);
    void CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned long);
    void CheckHitCylinderNear(CMapCylinder*, Vec*, unsigned short, unsigned short, unsigned long);
    void Draw();
    void DrawWire();
    void DrawNormal();
};

#endif // _FFCC_MAPHIT_H_
