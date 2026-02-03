#ifndef _FFCC_PPP_TEXANIM_H_
#define _FFCC_PPP_TEXANIM_H_

#include "ffcc/memory.h"
#include "ffcc/ptrarray.h"

class CMaterialSet;
class CChunkFile;
class CMemory;
struct Vec;

class CTexAnimSet
{
public:
    enum ANIM_TYPE
    {
        TODO,
    };

    CTexAnimSet();
    ~CTexAnimSet();

    void Create(CChunkFile&, CMemory::CStage*);
    void Duplicate(CMemory::CStage*);
    void AttachMaterialSet(CMaterialSet*);
    void AddFrame();
    void Change(char*, float, ANIM_TYPE);
    void SetTexGen();
};

class CTexAnimSeq
{
public:
    CTexAnimSeq();
    ~CTexAnimSeq();

    void Create(CChunkFile&, CMemory::CStage*);
    void Interp(float, Vec&);
    void GetTotalFrame();
    void GetName();
    void IsChin();
};

class CTexAnim
{
public:
	class CRefData
	{
	public:
		CRefData();
		~CRefData();
	};

    CTexAnim();
    ~CTexAnim();

    void Create(CChunkFile&, CMemory::CStage*);
    void Duplicate(CMemory::CStage*);
    void AttachMaterialSet(CMaterialSet*);
    void AddFrame(float);
    void Find(char*);
    void Change(int, float, CTexAnimSet::ANIM_TYPE);
    void SetTexGen();
    void IsChin();
    void GetChin();
};

#endif // _FFCC_PPP_TEXANIM_H_
