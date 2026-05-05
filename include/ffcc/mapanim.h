#ifndef _FFCC_MAPANIM_H_
#define _FFCC_MAPANIM_H_

#include "ffcc/ptrarray.h"

class CChunkFile;
class CMapAnim;
class CMapAnimNode;
class CMapAnimKey;
class CMapAnimKeyDt;
class CMapAnimRun;
class CMemory;
struct Vec;

class CMapAnimKeyDt
{
public:
    CMapAnimKeyDt();
    ~CMapAnimKeyDt();
};

class CMapAnimNode
{
public:
    CMapAnimNode();
    ~CMapAnimNode();
    void ReadOtmAnimNode(CChunkFile&, CMapAnim*);
    void Interp(int);
    void interp(Vec*, CMapAnimKey*, int, int);
};

class CMapAnim
{
    CPtrArray<CMapAnimNode*> mapAnimNodes;

public:
    CMapAnim();
    ~CMapAnim();
    void ReadOtmAnim(CChunkFile&);
    void Calc(long);
};

class CMapAnimRun
{
public:
    int m_currentFrame;
    int m_startFrame;
    int m_endFrame;
    int m_triggerFrame;
    unsigned char m_loop;
    unsigned char m_animId;
    unsigned short m_mapAnimIndex;

    void Calc(long);
    void Start(int, int, int);
};

#endif // _FFCC_MAPANIM_H_
