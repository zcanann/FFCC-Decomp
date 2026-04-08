#include "ffcc/pppShape.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"

#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

extern float FLOAT_80330108;

void pppSetBlendMode(unsigned char);

extern "C" {
    unsigned short FindTexName__12CMaterialSetFPcPl(CMaterialSet* materialSet, char* textureName,
                                                     long* outIndex);
    void CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet(CMaterialSet* materialSet, unsigned int textureIndex,
                                                             void* amemCacheSet);
}

static inline unsigned char* MaterialManRaw() { return reinterpret_cast<unsigned char*>(&MaterialMan); }

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

    *(int*)(MaterialManRaw() + 296) = *(int*)(MaterialManRaw() + 284);
    *(int*)(MaterialManRaw() + 300) = *(int*)(MaterialManRaw() + 288);
    *(int*)(MaterialManRaw() + 304) = *(int*)(MaterialManRaw() + 292);
    *(int*)(MaterialManRaw() + 64) = *(int*)(MaterialManRaw() + 72);

    SetMaterialPart__12CMaterialManFP12CMaterialSetii(&MaterialMan, materialSet,
                                                      *(unsigned char*)(shapePtr + 10), 0);

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_DIRECT);
    GXSetVtxDesc((GXAttr)11, GX_DIRECT);
    GXSetVtxDesc((GXAttr)13, GX_DIRECT);

    iVar2 = shapePtr;
    for (iVar1 = 0; iVar1 < *(short*)(shapePtr + 2); iVar1 = iVar1 + 1) {
        if (blendMode == 0xFF) {
            pppSetBlendMode(*(unsigned char*)(iVar2 + 8));
        }
        GXCallDisplayList(*(void**)(iVar2 + 0xc), 0x60);
        iVar2 = iVar2 + 8;
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
    int shapePtr;
    int shapeCount;

    *(int*)(MaterialManRaw() + 296) = *(int*)(MaterialManRaw() + 284);
    *(int*)(MaterialManRaw() + 300) = *(int*)(MaterialManRaw() + 288);
    *(int*)(MaterialManRaw() + 304) = *(int*)(MaterialManRaw() + 292);
    *(int*)(MaterialManRaw() + 64) = *(int*)(MaterialManRaw() + 72);

    SetMaterialPart__12CMaterialManFP12CMaterialSetii(&MaterialMan, materialSet,
                                                      *(unsigned char*)((int)shape + 10), 0);

    GXClearVtxDesc();
    GXSetVtxDesc((GXAttr)9, GX_DIRECT);
    GXSetVtxDesc((GXAttr)11, GX_DIRECT);
    GXSetVtxDesc((GXAttr)13, GX_DIRECT);

    shapePtr = (int)shape;
    for (shapeCount = 0; shapeCount < *(short*)((int)shape + 2); shapeCount = shapeCount + 1) {
        if (blendMode == 0xFF) {
            pppSetBlendMode(*(unsigned char*)(shapePtr + 8));
        }
        GXCallDisplayList(*(void**)(shapePtr + 0xc), 0x60);
        shapePtr = shapePtr + 8;
    }
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
    int shapeIndex;
    int shapeEntry;
    char* currentFrame;
    char* animData;
    int frameIndex;
    int shapeBase;

    animData = (char*)shapeSt->m_animData;
    currentFrame = animData;
    for (frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex = frameIndex + 1) {
        shapeBase = (int)animData + (int)*(short*)((int)currentFrame + 0x10);
        shapeEntry = shapeBase;
        for (shapeIndex = 0; shapeIndex < *(short*)(shapeBase + 2); shapeIndex = shapeIndex + 1) {
            *(unsigned char*)(shapeEntry + 10) =
                FindTexName__12CMaterialSetFPcPl(materialSet, textureNames[*(unsigned char*)(shapeEntry + 10)], 0);
            *(int*)(shapeEntry + 0xc) = (int)shapeSt->m_displayListData + *(int*)(shapeEntry + 0xc);
            shapeEntry = shapeEntry + 8;
        }
        currentFrame += 8;
    }
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
    short shapeOffset;
    char* currentFrame;
    int frameIndex;
    char* animData;
    unsigned char* texturePtr;
    unsigned int textureIndex;
    unsigned char textureUsed[0x100];

    animData = (char*)shapeSt->m_animData;
    memset(textureUsed, 0, sizeof(textureUsed));

    currentFrame = animData;
    for (frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex = frameIndex + 1) {
        int shapeIndex;
        int shapeStep;
        char* shapeBase;
        unsigned char* shapeEntry;

        shapeOffset = *(short*)((int)currentFrame + 0x10);
        shapeBase = animData + shapeOffset;
        shapeIndex = 0;
        shapeStep = 0;
        while (shapeIndex < *(short*)(shapeBase + 2)) {
            shapeEntry = (unsigned char*)(shapeBase + 8 + shapeStep);
            shapeIndex += 1;
            shapeStep += 8;
            textureUsed[shapeEntry[2]] = 1;
        }
        currentFrame += 8;
    }

    texturePtr = textureUsed;
    textureIndex = 0;
    do {
        if (*texturePtr != 0) {
            CacheLoadTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, textureIndex, &ppvAmemCacheSet);
        }
        textureIndex++;
        texturePtr++;
    } while (textureIndex < 0x100);
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
    short shapeOffset;
    char* currentFrame;
    int frameIndex;
    char* animData;
    unsigned char* texturePtr;
    unsigned int textureIndex;
    unsigned char textureUsed[0x100];

    animData = (char*)shapeSt->m_animData;
    memset(textureUsed, 0, sizeof(textureUsed));

    currentFrame = animData;
    for (frameIndex = 0; frameIndex < *(short*)((int)animData + 6); frameIndex = frameIndex + 1) {
        int shapeIndex;
        int shapeStep;
        char* shapeBase;
        unsigned char* shapeEntry;

        shapeOffset = *(short*)((int)currentFrame + 0x10);
        shapeBase = animData + shapeOffset;
        shapeIndex = 0;
        shapeStep = 0;
        while (shapeIndex < *(short*)(shapeBase + 2)) {
            shapeEntry = (unsigned char*)(shapeBase + 8 + shapeStep);
            shapeIndex += 1;
            shapeStep += 8;
            textureUsed[shapeEntry[2]] = 1;
        }
        currentFrame += 8;
    }

    texturePtr = textureUsed;
    textureIndex = 0;
    do {
        if (*texturePtr != 0) {
            CacheDumpTexture__12CMaterialSetFiP13CAmemCacheSet(materialSet, textureIndex, &ppvAmemCacheSet);
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
    const float uvScale = FLOAT_80330108;

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
    struct ShapeFrameEntry
    {
        short _00;
        short duration;
        int shapeOffset;
    };

    short frame = currentFrame;
    ShapeFrameEntry* frameData;

    drawFrame = frame;
    frameData = (ShapeFrameEntry*)((char*)animData + (frame << 3) + 0x10);
    frameTime = frameTime + deltaTime;
    if (frameTime < frameData->duration) {
        return;
    }
    frameTime = frameTime - frameData->duration;
    currentFrame = currentFrame + 1;
    if (currentFrame < *(short*)((int)animData + 6)) {
        return;
    }
    currentFrame = 0;
    frameTime = 0;
}
