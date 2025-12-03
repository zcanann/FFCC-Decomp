#ifndef _FFCC_MAPANIM_H_
#define _FFCC_MAPANIM_H_

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
public:
    CMapAnim();
    ~CMapAnim();
    void ReadOtmAnim(CChunkFile&);
    void Calc(long);
};

class CMapAnimRun
{
public:
    void Calc(long);
    void Start(int, int, int);
};

#endif // _FFCC_MAPANIM_H_
