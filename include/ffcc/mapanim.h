#ifndef _FFCC_MAPANIM_H_
#define _FFCC_MAPANIM_H_

#include "ffcc/ptrarray.h"
#include "dolphin/mtx.h"

class CChunkFile;
class CMapAnim;
class CMapAnimNode;
class CMapObj;
class CMapAnimKey;
class CMapAnimKeyDt;
class CMapAnimRun;
class CMemory;
class CMapAnimKey
{
public:
    unsigned int frame;
    Vec value;
};

struct CMapAnimNodeTrack
{
    unsigned int count;
    CMapAnimKey* keys;
};

class CMapAnimKeyDt
{
public:
    CMapAnimNodeTrack position;
    CMapAnimNodeTrack rotation;
    CMapAnimNodeTrack scale;

    CMapAnimKeyDt();
    ~CMapAnimKeyDt();
};

class CMapAnimNode
{
public:
    CMapObj* m_node;
    CMapAnim* m_mapAnim;
    CMapAnimKeyDt* m_tracks;

    CMapAnimNode();
    ~CMapAnimNode();
    void ReadOtmAnimNode(CChunkFile&, CMapAnim*);
    void Interp(int);
    void interp(Vec* out, CMapAnimKey* keys, int trackCount, int frameInLoop);
};

class CMapAnim
{
    friend class CMapAnimNode;
    friend class CMapMng;

    CPtrArray<CMapAnimNode*> mapAnimNodes;
    int m_startFrame;
    int m_endFrame;

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
