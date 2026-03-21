#ifndef _PPP_SHAPE_H_
#define _PPP_SHAPE_H_

class CMaterialSet;
class pppShapeSt;
class tagOAN3_SHAPE;
struct Vec;
class Vec2d;
class CMaterialMan;

extern "C" {
    void SetMaterialPart__12CMaterialManFP12CMaterialSetii(CMaterialMan*, CMaterialSet*, unsigned int, int);
    void pppSetBlendMode__FUc(unsigned char);
    void CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet(CMaterialSet*, unsigned int, void*);
}

void pppDrawShp(long*, short, CMaterialSet*, unsigned char);
void pppDrawShp(tagOAN3_SHAPE*, CMaterialSet*, unsigned char);
void pppSetShapeMaterial(pppShapeSt*, CMaterialSet*, char **);
void pppCacheLoadShapeTexture(pppShapeSt*, CMaterialSet*);
void pppCacheDumpShapeTexture(pppShapeSt*, CMaterialSet*);
void pppGetShapePos(long*, short, Vec&, Vec&, int);
void pppGetShapeUV(long*, short, Vec2d&, Vec2d&, int);
void pppCalcFrameShape(long*, short&, short&, short&, short);

#endif // _PPP_SHAPE_H_
