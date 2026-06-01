#ifndef _FFCC_MAPANIM_H_
#define _FFCC_MAPANIM_H_

#include "ffcc/ptrarray.h"
#include "dolphin/mtx.h"

class CChunkFile;
class CMapAnim;
struct CMapAnimData;
class CMapAnimNode;
struct CMapAnimNodeTrackKey;
struct CMapAnimNodeTracks;
struct CMapAnimTargetNode;
class CMapAnimKey;
class CMapAnimKeyDt;
class CMapAnimRun;
class CMemory;
struct CMapAnimNodeTrackKey
{
    unsigned int frame;
    Vec value;
};

struct CMapAnimNodeTrack
{
    unsigned int count;
    CMapAnimNodeTrackKey* keys;
};

class CMapAnimKey
{
public:
    unsigned int count;
    CMapAnimNodeTrackKey* keys;
};

struct CMapAnimNodeTracks
{
    CMapAnimNodeTrack position;
    CMapAnimNodeTrack rotation;
    CMapAnimNodeTrack scale;
};

struct CMapAnimData
{
    unsigned char _00[0x1C];
    int startFrame;
    int endFrame;
};

struct CMapAnimTargetNode
{
    unsigned char _00[0x1B];
    unsigned char dirty;
    unsigned char _1C[0x48];
    Vec position;
    Vec rotation;
    Vec scale;
};

class CMapAnimKeyDt
{
public:
    unsigned int m_positionCount;
    CMapAnimNodeTrackKey* m_positionKeys;
    unsigned int m_rotationCount;
    CMapAnimNodeTrackKey* m_rotationKeys;
    unsigned int m_scaleCount;
    CMapAnimNodeTrackKey* m_scaleKeys;

    CMapAnimKeyDt();
    ~CMapAnimKeyDt();
};

class CMapAnimNode
{
public:
    CMapAnimTargetNode* m_node;
    CMapAnimData* m_mapAnim;
    CMapAnimNodeTracks* m_tracks;

    CMapAnimNode();
    ~CMapAnimNode();
    void ReadOtmAnimNode(CChunkFile&, CMapAnim*);
    void Interp(int);
    void interp(Vec*, CMapAnimKey*, int, int);
};

class CMapAnim
{
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
