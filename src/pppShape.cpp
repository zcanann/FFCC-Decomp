#include "ffcc/pppShape.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"

#include <string.h>

extern "C" {
    extern unsigned char MaterialMan[];
    extern void* CAMemCacheSet;
    unsigned short FindTexName__12CMaterialSetFPcPl(CMaterialSet* materialSet, char* textureName,
                                                     long* outIndex);
    void CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet(CMaterialSet* materialSet, unsigned int textureIndex,
                                                             void* amemCacheSet);
}

class CMaterial;

template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    int m_size;
    int m_numItems;
    int m_defaultSize;
    T* m_items;
    void* m_stage;
    int m_growCapacity;

    T GetAt(unsigned long index);
    T operator[](unsigned long index);
};

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
    unsigned char* shape = (unsigned char*)animData + *(short*)((int)animData + 0x10) + 8;

    textureIndex = shape[2];
    CMaterial* material = (*reinterpret_cast<CPtrArray<CMaterial*>*>((char*)materialSet + 8))[shape[2]];
    return *(void**)((char*)material + 0x3C);
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
    int iVar1;
    int iVar2;

    int shapePtr = (int)animData;
    shapePtr = shapePtr + *(short*)(shapePtr + frameIndex * 8 + 0x10);

    *(int*)(MaterialMan + 296) = *(int*)(MaterialMan + 284);
    *(int*)(MaterialMan + 300) = *(int*)(MaterialMan + 288);
    *(int*)(MaterialMan + 304) = *(int*)(MaterialMan + 292);
    *(int*)(MaterialMan + 64) = *(int*)(MaterialMan + 72);

    SetMaterialPart__12CMaterialManFP12CMaterialSetii((CMaterialMan*)MaterialMan, materialSet,
                                                      *(unsigned char*)(shapePtr + 10), 0);

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_DIRECT);
    GXSetVtxDesc((GXAttr)11, GX_DIRECT);
    GXSetVtxDesc((GXAttr)13, GX_DIRECT);

    iVar1 = shapePtr;
    for (iVar2 = 0; iVar2 < *(short*)(shapePtr + 2); iVar2 = iVar2 + 1) {
        if (blendMode == 0xFF) {
            pppSetBlendMode__FUc(*(unsigned char*)(iVar1 + 8));
        }
        GXCallDisplayList(*(void**)(iVar1 + 0xc), 0x60);
        iVar1 = iVar1 + 8;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80065a94
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShp(tagOAN3_SHAPE* shape, CMaterialSet* materialSet, unsigned char blendMode)
{
    int iVar1;
    int iVar2;

    int shapePtr = (int)shape;

    *(int*)(MaterialMan + 296) = *(int*)(MaterialMan + 284);
    *(int*)(MaterialMan + 300) = *(int*)(MaterialMan + 288);
    *(int*)(MaterialMan + 304) = *(int*)(MaterialMan + 292);
    *(int*)(MaterialMan + 64) = *(int*)(MaterialMan + 72);

    SetMaterialPart__12CMaterialManFP12CMaterialSetii((CMaterialMan*)MaterialMan, materialSet,
                                                      *(unsigned char*)(shapePtr + 10), 0);

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_DIRECT);
    GXSetVtxDesc((GXAttr)11, GX_DIRECT);
    GXSetVtxDesc((GXAttr)13, GX_DIRECT);

    iVar2 = shapePtr;
    for (iVar1 = 0; iVar1 < *(short*)(shapePtr + 2); iVar1 = iVar1 + 1) {
        if (blendMode == 0xFF) {
            pppSetBlendMode__FUc(*(unsigned char*)(iVar2 + 8));
        }
        GXCallDisplayList(*(void**)(iVar2 + 0xc), 0x60);
        iVar2 = iVar2 + 8;
    }
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
 * PAL Address: 0x800659ec
 * PAL Size: 168b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSetShapeMaterial(pppShapeSt* shapeSt, CMaterialSet* materialSet, char** textureNames)
{
    void* animData = shapeSt->m_animData;
    void* currentFrame = animData;

    for (int frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex++) {
        int shapeEntry = (int)animData + *(short*)((int)currentFrame + 0x10);

        for (int shapeIndex = 0; shapeIndex < *(short*)(shapeEntry + 2); shapeIndex++) {
            *(unsigned char*)(shapeEntry + 10) =
                FindTexName__12CMaterialSetFPcPl(materialSet, textureNames[*(unsigned char*)(shapeEntry + 10)], 0);
            *(int*)(shapeEntry + 0xc) = (int)shapeSt->m_displayListData + *(int*)(shapeEntry + 0xc);
            shapeEntry += 8;
        }

        currentFrame = (void*)((int)currentFrame + 8);
    }
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
    unsigned char textureUsed[0x100];
    void* animData = shapeSt->m_animData;
    void* currentFrame;
    unsigned int textureIndex;
    int frameIndex;
    unsigned char* texturePtr;

    memset(textureUsed, 0, 0x100);

    currentFrame = animData;
    for (frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex++) {
        short shapeOffset = *(short*)((int)currentFrame + 0x10);
        int shapeEntryOffset = 0;
        int shapeIndex;

        for (shapeIndex = 0; shapeIndex < *(short*)((int)animData + shapeOffset + 2); shapeIndex++) {
            int entryOffset = shapeEntryOffset + shapeOffset;
            shapeEntryOffset += 8;
            textureUsed[*(unsigned char*)((int)animData + entryOffset + 10)] = 1;
        }
        currentFrame = (void*)((int)currentFrame + 8);
    }

    texturePtr = textureUsed;
    textureIndex = 0;
    do {
        if (*texturePtr != 0) {
            CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, textureIndex, CAMemCacheSet);
        }
        textureIndex++;
        texturePtr++;
    } while (textureIndex < 0x100);
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
    unsigned char textureUsed[0x100];
    void* animData = shapeSt->m_animData;
    void* currentFrame;
    unsigned int textureIndex;
    int frameIndex;
    unsigned char* texturePtr;

    memset(textureUsed, 0, 0x100);

    currentFrame = animData;
    for (frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex++) {
        short shapeOffset = *(short*)((int)currentFrame + 0x10);
        int shapeEntryOffset = 0;
        int shapeIndex;

        for (shapeIndex = 0; shapeIndex < *(short*)((int)animData + shapeOffset + 2); shapeIndex++) {
            int entryOffset = shapeEntryOffset + shapeOffset;
            shapeEntryOffset += 8;
            textureUsed[*(unsigned char*)((int)animData + entryOffset + 10)] = 1;
        }
        currentFrame = (void*)((int)currentFrame + 8);
    }

    texturePtr = textureUsed;
    textureIndex = 0;
    do {
        if (*texturePtr != 0) {
            CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, textureIndex, CAMemCacheSet);
        }
        textureIndex++;
        texturePtr++;
    } while (textureIndex < 0x100);
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
    u8* shapeEntry = (u8*)*(int*)((int)animData + shapeBase + 0xc + shapeIndex * 8);
    u8* minSrc = shapeEntry + 3;

    memcpy(&minPos, minSrc, 0xc);
    memcpy(&maxPos, minSrc + 0x28, 0xc);
}

/*
 * --INFO--
 * PAL Address: 0x800656dc
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetShapeUV(long* animData, short frameIndex, Vec2d& minUv, Vec2d& maxUv, int shapeIndex)
{
    int shapeBase = *(short*)((int)animData + frameIndex * 8 + 0x10);
    int shapeEntry = *(int*)((int)animData + shapeBase + 0xc + shapeIndex * 8);
    float* minUvF = (float*)&minUv;
    float* maxUvF = (float*)&maxUv;
    const float uvScale = 1.0f / 4096.0f;

    minUvF[0] = (float)*(short*)(shapeEntry + 0x13) * uvScale;
    minUvF[1] = (float)*(short*)(shapeEntry + 0x15) * uvScale;
    maxUvF[0] = (float)*(short*)(shapeEntry + 0x3b) * uvScale;
    maxUvF[1] = (float)*(short*)(shapeEntry + 0x3d) * uvScale;
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
    short frame = currentFrame;
    drawFrame = frame;
    frameTime = frameTime + deltaTime;
    frame = *(short*)((int)animData + frame * 8 + 0x12);
    if (frameTime < frame) {
        return;
    }
    frameTime = frameTime - frame;
    currentFrame = currentFrame + 1;
    if (currentFrame < *(short*)((int)animData + 6)) {
        return;
    }
    currentFrame = 0;
    frameTime = 0;
}
