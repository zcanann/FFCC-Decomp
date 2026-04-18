#ifndef _FFCC_MAPTEXANIM_H_
#define _FFCC_MAPTEXANIM_H_

#include "ffcc/ref.h"

class CChunkFile;
class CMaterialSet;
class CTextureSet;
class CTexture;
class CMapTexAnim;

class CMapTexAnimSet : public CRef
{
public:
    CMapTexAnimSet();
    ~CMapTexAnimSet();

    void Create(CChunkFile&, CMaterialSet*, CTextureSet*);
    void Calc();
    void SetMapTexAnim(int, int, int, int);

private:
    short m_count;
    unsigned short m_pad0A;
    CMapTexAnim* m_anims[64];
    CMaterialSet* m_materialSet;
    CTextureSet* m_textureSet;
};

class CMapTexAnim : public CRef
{
public:
    ~CMapTexAnim();
    void Calc(CMaterialSet*, CTextureSet*);
    void SetMapTexAnim(int, int, int);

private:
    friend class CMapTexAnimSet;

    short m_materialIndex;
    short m_textureSlot;
    short m_frameCount;
    short m_startFrame;
    short m_endFrame;
    short m_materialId;
    unsigned char m_usesBlendTexture;
    unsigned char m_usesKeyFrame;
    unsigned char m_wrapMode;
    unsigned char m_pad17;
    float m_frameStep;
    float m_currentFrame;
    void* m_frameTable;
    unsigned char m_keyFrame[0x18];
    void* m_keyJun;
    void* m_keyFrameData;
    void* m_keyKeyData;
    void* m_keyUnknown;
};

#endif // _FFCC_MAPTEXANIM_H_
