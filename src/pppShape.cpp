#include "ffcc/pppShape.h"
#include "ffcc/materialman.h"

extern "C" {
    extern CMaterialMan MaterialMan;
    extern void* CAMemCacheSet;
}

/*
 * --INFO--
 * PAL Address: 0x80065c6c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* pppShapeSt_GetTexture(long* animData, CMaterialSet* materialSet, int& textureIndex)
{
    int shapePtr = (int)animData + *(short*)((int)animData + 0x10) + 8;
    textureIndex = (unsigned int)*(unsigned char*)(shapePtr + 2);
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x80065b74
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShp(long* animData, short frameIndex, CMaterialSet* materialSet, unsigned char blendMode)
{
    // TODO: Implement function body
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppDrawShp(tagOAN3_SHAPE*, CMaterialSet*, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetShapeMaterial0(pppShapeSt*, tagOAN3_SHAPE*, CMaterialSet*, char **)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetShapeMaterial(pppShapeSt*, CMaterialSet*, char **)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppShapeSetUseTexture(tagOAN3_SHAPE*, unsigned char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheLoadShapeTexture(pppShapeSt*, CMaterialSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheUnLoadShapeTexture(pppShapeSt*, CMaterialSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCacheRefCnt0UpShapeTexture(pppShapeSt*, CMaterialSet*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8006580c
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCacheDumpShapeTexture(pppShapeSt* shapeSt, CMaterialSet* materialSet)
{
    // TODO: Implement function body
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetShapePos(long*, short, Vec&, Vec&, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppGetShapeUV(long*, short, Vec2d&, Vec2d&, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppCalcFrameShape(long*, short&, short&, short&, short)
{
	// TODO
}
