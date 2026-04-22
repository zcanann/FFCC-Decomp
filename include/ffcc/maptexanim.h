#ifndef _FFCC_MAPTEXANIM_H_
#define _FFCC_MAPTEXANIM_H_

#include "ffcc/map.h"
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
    void SetMapTexAnim(int frameStart, int frameEnd, int wrapMode)
    {
        int end = frameEnd;

        if (m_usesKeyFrame != 0) {
            m_keyFrame.m_startFrame = frameStart;
            m_keyFrame.m_currentFrame = frameStart;
            if (frameEnd > m_keyFrame.m_frameCount) {
                end = m_keyFrame.m_frameCount;
            }
            m_keyFrame.m_endFrame = end;
            m_keyFrame.m_loop = static_cast<unsigned char>(wrapMode);
            m_keyFrame.m_isRun = 1;
        } else {
            m_startFrame = static_cast<short>(frameStart);
            m_currentFrame = static_cast<float>(static_cast<short>(frameStart));
            if (frameEnd > m_frameCount) {
                end = m_frameCount;
            }
            m_endFrame = static_cast<short>(end);
            m_wrapMode = static_cast<unsigned char>(wrapMode);
        }
    }

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
    unsigned short* m_frameTable;
    CMapKeyFrame m_keyFrame;
};

#endif // _FFCC_MAPTEXANIM_H_
