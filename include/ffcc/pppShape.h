#ifndef _PPP_SHAPE_H_
#define _PPP_SHAPE_H_

class CMaterialSet;
class pppShapeSt;
class tagOAN3_SHAPE;
class Vec;
class Vec2d;

void pppShapeSt_GetTexture(long *, CMaterialSet *, int &);
void pppDrawShp(long *, short, CMaterialSet *, unsigned char);
void pppDrawShp(tagOAN3_SHAPE *, CMaterialSet *, unsigned char);
void pppSetShapeMaterial0(pppShapeSt *, tagOAN3_SHAPE *, CMaterialSet *, char **);
void pppSetShapeMaterial(pppShapeSt *, CMaterialSet *, char **);
void pppShapeSetUseTexture(tagOAN3_SHAPE *, unsigned char *);
void pppCacheLoadShapeTexture(pppShapeSt *, CMaterialSet *);
void pppCacheUnLoadShapeTexture(pppShapeSt *, CMaterialSet *);
void pppCacheRefCnt0UpShapeTexture(pppShapeSt *, CMaterialSet *);
void pppCacheDumpShapeTexture(pppShapeSt *, CMaterialSet *);
void pppGetShapePos(long *, short, Vec &, Vec &, int);
void pppGetShapeUV(long *, short, Vec2d &, Vec2d &, int);
void pppCalcFrameShape(long *, short &, short &, short &, short);

#endif // _PPP_SHAPE_H_
