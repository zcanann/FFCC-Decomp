#ifndef _FFCC_MAPTEXANIM_H_
#define _FFCC_MAPTEXANIM_H_

#include "ffcc/map.h"
#include "ffcc/ref.h"

class CChunkFile;
class CMaterialSet;
class CTextureSet;
class CTexture;
class CMapTexAnim;

extern "C" float FLOAT_8032fd48;
extern "C" float FLOAT_8032fd4c;

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

class CMapKeyFrameData
{
public:
    float Get()
    {
        return reinterpret_cast<CMapKeyFrame*>(this)->Get();
    }

    int Get(int& key0, int& key1, float& blend)
    {
        return reinterpret_cast<CMapKeyFrame*>(this)->Get(key0, key1, blend);
    }

    void Calc()
    {
        reinterpret_cast<CMapKeyFrame*>(this)->Calc();
    }

    int IsRun()
    {
        return reinterpret_cast<CMapKeyFrame*>(this)->IsRun();
    }

    void ReadJun(CChunkFile& chunkFile, int count)
    {
        reinterpret_cast<CMapKeyFrame*>(this)->ReadJun(chunkFile, count);
    }

    void ReadFrame(CChunkFile& chunkFile, int count)
    {
        reinterpret_cast<CMapKeyFrame*>(this)->ReadFrame(chunkFile, count);
    }

    void ReadKey(CChunkFile& chunkFile, int count)
    {
        reinterpret_cast<CMapKeyFrame*>(this)->ReadKey(chunkFile, count);
    }

    void Destroy()
    {
        if (m_junTable != 0) {
            delete m_junTable;
            m_junTable = 0;
        }
        if (m_keyFrame != 0) {
            delete m_keyFrame;
            m_keyFrame = 0;
        }
        if (m_keyValue != 0) {
            delete m_keyValue;
            m_keyValue = 0;
        }
        if (m_splineTable != 0) {
            delete m_splineTable;
            m_splineTable = 0;
        }
    }

    unsigned char m_mode;
    unsigned char m_junCount;
    unsigned char m_keyCount;
    unsigned char m_loop;
    unsigned char m_isRun;
    unsigned char m_pad05[3];
    int m_currentFrame;
    int m_startFrame;
    int m_endFrame;
    int m_frameCount;
    unsigned char* m_junTable;
    float* m_keyFrame;
    float* m_keyValue;
    float* m_splineTable;
};

class CMapTexAnim : public CRef
{
public:
    CMapTexAnim()
    {
        float frameStep = FLOAT_8032fd48;
        m_keyFrame.m_junTable = 0;
        float currentFrame = FLOAT_8032fd4c;
        m_keyFrame.m_keyFrame = 0;
        m_keyFrame.m_keyValue = 0;
        m_keyFrame.m_splineTable = 0;
        m_keyFrame.m_loop = 1;
        m_keyFrame.m_isRun = 0;
        m_frameTable = 0;
        m_frameStep = frameStep;
        m_currentFrame = currentFrame;
        m_usesBlendTexture = 0;
        m_usesKeyFrame = 0;
        m_materialId = -1;
        m_wrapMode = 1;
    }

    ~CMapTexAnim();
    void Calc(CMaterialSet*, CTextureSet*);
    void SetMapTexAnim(int frameStart, int frameEnd, int wrapMode)
    {
        int end = frameEnd;

        if (m_usesKeyFrame != 0) {
            int keyEnd = frameEnd;
            m_keyFrame.m_startFrame = frameStart;
            m_keyFrame.m_currentFrame = frameStart;
            if (keyEnd > m_keyFrame.m_frameCount) {
                keyEnd = m_keyFrame.m_frameCount;
            }
            m_keyFrame.m_endFrame = keyEnd;
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
    CMapKeyFrameData m_keyFrame;
};

#endif // _FFCC_MAPTEXANIM_H_
