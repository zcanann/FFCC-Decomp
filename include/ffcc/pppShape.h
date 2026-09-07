#ifndef _PPP_SHAPE_H_
#define _PPP_SHAPE_H_

#include <stddef.h>

class CMaterialSet;
class pppShapeSt;
struct Vec;
class Vec2d;

struct pppShapeAnimFrame
{
    short m_shapeOffset; // 0x0
    short m_duration;    // 0x2
    unsigned char m_flags; // 0x4
    char m_pad5[3];        // 0x5
}; // Size 0x8

struct pppShapeAnimData
{
    char m_pad0[6];                  // 0x0
    short m_frameCount;              // 0x6
    char m_pad8[8];                  // 0x8
    pppShapeAnimFrame m_frames[1];   // 0x10
};

struct tagOAN3_SHAPE_ENTRY
{
    unsigned char m_blendMode;       // 0x0
    unsigned char m_field1;          // 0x1
    unsigned char m_textureIndex;    // 0x2
    unsigned char m_field3;          // 0x3
    unsigned char* m_displayList;    // 0x4
}; // Size 0x8

struct tagOAN3_SHAPE
{
    char m_pad0[2];                  // 0x0
    short m_shapeCount;              // 0x2
    char m_pad4[4];                  // 0x4
    tagOAN3_SHAPE_ENTRY m_entries[1]; // 0x8
};

static inline pppShapeAnimData* pppShapeAnim(long* animData)
{
    return reinterpret_cast<pppShapeAnimData*>(animData);
}

static inline tagOAN3_SHAPE* pppShapeFrame(pppShapeAnimData* animData, short frameIndex)
{
    short shapeOffset = *reinterpret_cast<short*>(
        reinterpret_cast<int>(animData) + frameIndex * sizeof(pppShapeAnimFrame) +
        offsetof(pppShapeAnimData, m_frames));
    return reinterpret_cast<tagOAN3_SHAPE*>(
        reinterpret_cast<unsigned char*>(animData) + shapeOffset);
}

static inline tagOAN3_SHAPE* pppShapeFrame(long* animData, short frameIndex)
{
    return pppShapeFrame(pppShapeAnim(animData), frameIndex);
}

void pppDrawShp(long*, short, CMaterialSet*, unsigned char);
void pppDrawShp(tagOAN3_SHAPE*, CMaterialSet*, unsigned char);
void pppSetShapeMaterial(pppShapeSt*, CMaterialSet*, char **);
void pppCacheLoadShapeTexture(pppShapeSt*, CMaterialSet*);
void pppCacheUnLoadShapeTexture(pppShapeSt*, CMaterialSet*);
void pppGetShapePos(long*, short, Vec&, Vec&, int);
void pppGetShapeUV(long*, short, Vec2d&, Vec2d&, int);
void pppCalcFrameShape(long*, short&, short&, short&, short);

#endif // _PPP_SHAPE_H_
