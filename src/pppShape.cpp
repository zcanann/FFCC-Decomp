#include "ffcc/pppShape.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"

#include <string.h>

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
void* pppShapeSt::GetTexture(long* animData, CMaterialSet* materialSet, int& textureIndex)
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
 * PAL Address: 0x800658fc
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCacheLoadShapeTexture(pppShapeSt* shapeSt, CMaterialSet* materialSet)
{
    char textureUsed[256];
    void* animData = shapeSt->m_animData;

    memset(textureUsed, 0, 256);

    void* currentFrame = animData;
    for (int frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex++) {
        short shapeOffset = *(short*)((int)currentFrame + 0x10);
        int shapeEntryOffset = 0;

        for (int shapeIndex = 0; shapeIndex < *(short*)((int)animData + shapeOffset + 2); shapeIndex++) {
            int entryPtr = shapeEntryOffset + shapeOffset;
            shapeEntryOffset += 8;
            textureUsed[*(unsigned char*)((int)animData + entryPtr + 10)] = 1;
        }
        currentFrame = (void*)((int)currentFrame + 8);
    }

    for (unsigned int textureIndex = 0; textureIndex < 256; textureIndex++) {
        if (textureUsed[textureIndex] != 0) {
            materialSet->CacheLoadTexture(textureIndex, (CAmemCacheSet*)CAMemCacheSet);
        }
    }
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
    char textureUsed[256];
    void* animData = shapeSt->m_animData;
    
    memset(textureUsed, 0, 256);
    
    void* currentFrame = animData;
    for (int frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex++) {
        short shapeOffset = *(short*)((int)currentFrame + 0x10);
        int shapeEntryOffset = 0;
        
        for (int shapeIndex = 0; shapeIndex < *(short*)((int)animData + shapeOffset + 2); shapeIndex++) {
            int entryPtr = shapeEntryOffset + shapeOffset;
            shapeEntryOffset += 8;
            textureUsed[*(unsigned char*)((int)animData + entryPtr + 10)] = 1;
        }
        currentFrame = (void*)((int)currentFrame + 8);
    }
    
    for (unsigned int textureIndex = 0; textureIndex < 256; textureIndex++) {
        if (textureUsed[textureIndex] != 0) {
            CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, textureIndex, CAMemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80065794
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetShapePos(long* animData, short frameIndex, Vec& minPos, Vec& maxPos, int shapeIndex)
{
    int shapeBase = *(short*)((int)animData + frameIndex * 8 + 0x10);
    int shapeEntry = *(int*)((int)animData + shapeBase + 0xc + shapeIndex * 8);

    memcpy(&minPos, (void*)(shapeEntry + 3), 0xc);
    memcpy(&maxPos, (void*)(shapeEntry + 0x2b), 0xc);
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
 * PAL Address: 0x80065678
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCalcFrameShape(long* animData, short& currentFrame, short& drawFrame, short& frameTime,
                       short deltaTime)
{
    drawFrame = currentFrame;
    frameTime += deltaTime;

    short duration = *(short*)((int)animData + currentFrame * 8 + 0x12);
    if (frameTime < duration) {
        return;
    }

    frameTime -= duration;
    currentFrame += 1;
    if (currentFrame < *(short*)((int)animData + 6)) {
        return;
    }

    currentFrame = 0;
    frameTime = 0;
}
