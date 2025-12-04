#ifndef _FFCC_MAPTEXANIM_H_
#define _FFCC_MAPTEXANIM_H_

class CChunkFile;
class CMaterialSet;
class CTextureSet;
class CTexture;

class CMapTexAnimSet
{
public:
    CMapTexAnimSet();
    ~CMapTexAnimSet();

    void Create(CChunkFile&, CMaterialSet*, CTextureSet*);
    void Calc();
    void SetMapTexAnim(int, int, int, int);
};

class CMapTexAnim
{
public:
    CMapTexAnim();
    ~CMapTexAnim();
    void Calc(CMaterialSet*, CTextureSet*);
    void SetMapTexAnim(int, int, int);
};

#endif // _FFCC_MAPTEXANIM_H_
