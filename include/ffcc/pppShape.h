#ifndef _PPP_SHAPE_H_
#define _PPP_SHAPE_H_

class CMaterialSet;
class pppShapeSt;
class tagOAN3_SHAPE;
struct Vec;
class Vec2d;

void pppDrawShp(long*, short, CMaterialSet*, unsigned char);
void pppDrawShp(tagOAN3_SHAPE*, CMaterialSet*, unsigned char);
void pppSetShapeMaterial(pppShapeSt*, CMaterialSet*, char **);
void pppCacheLoadShapeTexture(pppShapeSt*, CMaterialSet*);
void pppCacheDumpShapeTexture(pppShapeSt*, CMaterialSet*);
void pppGetShapePos(long*, short, Vec&, Vec&, int);
void pppGetShapeUV(long*, short, Vec2d&, Vec2d&, int);
void pppCalcFrameShape(long*, short&, short&, short&, short);

#endif // _PPP_SHAPE_H_
