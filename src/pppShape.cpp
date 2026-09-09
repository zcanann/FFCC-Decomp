#include "ffcc/pppShape.h"
#include "ffcc/pppVec.h"
#include "ffcc/linkage.h"
#include "ffcc/materialman.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"

#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h>

/*
 * --INFO--
 * PAL Address: 0x80065678
 * PAL Size: 100b
 * EN Address: 0x80064FE0
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCalcFrameShape(long* animData, short& currentFrame, short& drawFrame, short& frameTime,
                       short deltaTime)
{
    pppShapeAnimData* shapeAnim = pppShapeAnim(animData);
    pppShapeAnimFrame* frameData = &shapeAnim->m_frames[currentFrame];

    drawFrame = currentFrame;
    frameTime += deltaTime;
    if (frameTime < frameData->m_duration) {
        return;
    }
    frameTime -= frameData->m_duration;
    currentFrame += 1;
    if (currentFrame < shapeAnim->m_frameCount) {
        return;
    }
    currentFrame = 0;
    frameTime = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800656dc
 * PAL Size: 184b
 * EN Address: 0x80065044
 * EN Size: 184b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetShapeUV(long* animData, short frameIndex, Vec2d& minUv, Vec2d& maxUv, int shapeIndex)
{
    tagOAN3_SHAPE* shape = pppShapeFrame(animData, frameIndex);
    unsigned char* displayList = shape->m_entries[shapeIndex].m_displayList;

    minUv.x = (float)*(short*)(displayList + 0x13) / 1024.0f;
    minUv.y = (float)*(short*)(displayList + 0x15) / 1024.0f;
    maxUv.x = (float)*(short*)(displayList + 0x3b) / 1024.0f;
    maxUv.y = (float)*(short*)(displayList + 0x3d) / 1024.0f;
}

/*
 * --INFO--
 * PAL Address: 0x80065794
 * PAL Size: 120b
 * EN Address: 0x800650FC
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppGetShapePos(long* animData, short frameIndex, Vec& minPos, Vec& maxPos, int shapeIndex)
{
    tagOAN3_SHAPE* shape = pppShapeFrame(animData, frameIndex);
    unsigned char* minSrc = shape->m_entries[shapeIndex].m_displayList + 3;

    memcpy(&minPos, minSrc, 0xc);
    memcpy(&maxPos, minSrc + 0x28, 0xc);
}

/*
 * --INFO--
 * PAL Address: 0x8006580c
 * PAL Size: 240b
 * EN Address: 0x80065174
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCacheUnLoadShapeTexture(pppShapeSt* shapeSt, CMaterialSet* materialSet)
{
    pppShapeAnimData* animData = static_cast<pppShapeAnimData*>(shapeSt->m_animData);
    unsigned char textureUsed[0x100];
    memset(textureUsed, 0, sizeof(textureUsed));

    for (int frameIndex = 0; frameIndex < animData->m_frameCount; frameIndex++) {
        tagOAN3_SHAPE* shape = pppShapeFrame(animData, frameIndex);
        for (int shapeIndex = 0; shapeIndex < shape->m_shapeCount; shapeIndex++) {
            textureUsed[shape->m_entries[shapeIndex].m_textureIndex] = 1;
        }
    }

    for (unsigned int textureIndex = 0; textureIndex < sizeof(textureUsed); textureIndex++) {
        if (textureUsed[textureIndex] != 0) {
            materialSet->CacheUnLoadTexture(textureIndex, &ppvAmemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800658fc
 * PAL Size: 240b
 * EN Address: 0x80065264
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppCacheLoadShapeTexture(pppShapeSt* shapeSt, CMaterialSet* materialSet)
{
    pppShapeAnimData* animData = static_cast<pppShapeAnimData*>(shapeSt->m_animData);
    unsigned char textureUsed[0x100];
    memset(textureUsed, 0, sizeof(textureUsed));

    for (int frameIndex = 0; frameIndex < animData->m_frameCount; frameIndex++) {
        tagOAN3_SHAPE* shape = pppShapeFrame(animData, frameIndex);
        for (int shapeIndex = 0; shapeIndex < shape->m_shapeCount; shapeIndex++) {
            textureUsed[shape->m_entries[shapeIndex].m_textureIndex] = 1;
        }
    }

    for (unsigned int textureIndex = 0; textureIndex < sizeof(textureUsed); textureIndex++) {
        if (textureUsed[textureIndex] != 0) {
            materialSet->CacheLoadTexture(textureIndex, &ppvAmemCacheSet);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800659ec
 * PAL Size: 168b
 * EN Address: 0x80065354
 * EN Size: 168b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSetShapeMaterial(pppShapeSt* shapeSt, CMaterialSet* materialSet, char** textureNames)
{
    pppShapeAnimData* animData = static_cast<pppShapeAnimData*>(shapeSt->m_animData);
    for (int frameIndex = 0; frameIndex < animData->m_frameCount; frameIndex++) {
        tagOAN3_SHAPE* shape = pppShapeFrame(animData, frameIndex);
        for (int shapeIndex = 0; shapeIndex < shape->m_shapeCount; shapeIndex++) {
            tagOAN3_SHAPE_ENTRY* entry = &shape->m_entries[shapeIndex];
            entry->m_textureIndex = materialSet->FindTexName(textureNames[entry->m_textureIndex], 0);
            entry->m_displayList = static_cast<unsigned char*>(shapeSt->m_displayListData) +
                reinterpret_cast<unsigned int>(entry->m_displayList);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80065a94
 * PAL Size: 224b
 * EN Address: 0x800653FC
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShp(tagOAN3_SHAPE* shape, CMaterialSet* materialSet, unsigned char blendMode)
{
    MaterialMan.LockEnv();
    MaterialMan.SetMaterialPart(materialSet, shape->m_entries[0].m_textureIndex, 0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    for (int shapeIndex = 0; shapeIndex < shape->m_shapeCount; shapeIndex++) {
        tagOAN3_SHAPE_ENTRY* entry = &shape->m_entries[shapeIndex];
        if (blendMode == 0xFF) {
            pppSetBlendMode(entry->m_blendMode);
        }
        GXCallDisplayList(entry->m_displayList, 0x60);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80065b74
 * PAL Size: 248b
 * EN Address: 0x800654DC
 * EN Size: 248b
 * JP Address: TODO
 * JP Size: TODO
 */
void pppDrawShp(long* animData, short frameIndex, CMaterialSet* materialSet, unsigned char blendMode)
{
    tagOAN3_SHAPE* shape = pppShapeFrame(animData, frameIndex);

    MaterialMan.LockEnv();
    MaterialMan.SetMaterialPart(materialSet, shape->m_entries[0].m_textureIndex, 0);

    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_CLR0, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);

    for (int shapeIndex = 0; shapeIndex < shape->m_shapeCount; shapeIndex++) {
        tagOAN3_SHAPE_ENTRY* entry = &shape->m_entries[shapeIndex];
        if (blendMode == 0xFF) {
            pppSetBlendMode(entry->m_blendMode);
        }
        GXCallDisplayList(entry->m_displayList, 0x60);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80065c6c
 * PAL Size: 64b
 * EN Address: 0x800655D4
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
CTexture* pppShapeSt::GetTexture(long* animData, CMaterialSet* materialSet, int& textureIndex)
{
    tagOAN3_SHAPE_ENTRY* shapeEntry = pppShapeFrame(animData, 0)->m_entries;

    textureIndex = shapeEntry->m_textureIndex;
    CMaterial* material = materialSet->GetMaterial(shapeEntry->m_textureIndex);
    return material->GetTexture(0);
}
