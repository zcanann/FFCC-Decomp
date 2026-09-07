#ifndef _FFCC_PPP_TEXANIM_H_
#define _FFCC_PPP_TEXANIM_H_

#include "ffcc/memory.h"
#include "ffcc/ptrarray_decl.h"
#include "ffcc/ref.h"

#include <dolphin/mtx.h>

class CMaterialSet;
class CMaterial;
class CChunkFile;
class CMemory;
class CTexAnim;
class CTexAnimSeq;

struct CTexAnimKey
{
    unsigned int m_frame;
    unsigned char _pad04[0x24 - 0x04];
    Vec m_texGen;
};

class CTexAnimSet : public CRef
{
public:
    enum ANIM_TYPE
    {
        TODO,
    };

    CTexAnimSet();
    ~CTexAnimSet();

    void Create(CChunkFile&, CMemory::CStage*);
    CTexAnimSet* Duplicate(CMemory::CStage*);
    void AttachMaterialSet(CMaterialSet*);
    void AddFrame();
    void Change(char*, float, ANIM_TYPE);
    void SetTexGen();
    float GetChin() { return m_chin; }

private:
    CPtrArray<CTexAnim*> m_texAnims;
    float m_chin;
};

class CTexAnimSeq : public CRef
{
public:
    CTexAnimSeq();
    ~CTexAnimSeq();

    void Create(CChunkFile&, CMemory::CStage*);
    void Interp(float, Vec&);
    unsigned int GetTotalFrame();
    char* GetName();
    int IsChin();

private:
    friend class CTexAnim;
    friend class CTexAnimSet;

    char m_name[0x100];
    unsigned int m_totalFrames;
    int m_keyCount;
    signed char m_interp : 1;
    signed char m_chin : 1;
    signed char m_e1 : 1;
    signed char m_flagsRest : 5;
    unsigned char m_pad111[3];
    CTexAnimKey* m_keys;
};

class CTexAnim : public CRef
{
public:
    class CRefData : public CRef
    {
    public:
        CRefData();
        ~CRefData();

    private:
        friend class CTexAnim;
        friend class CTexAnimSet;

        char m_name[0x100];
        CMaterial* m_material;
        int m_texSrtIndex;
        CPtrArray<CTexAnimSeq*> m_texAnimSeqs;
    };

    CTexAnim();
    ~CTexAnim();

    void Create(CChunkFile&, CMemory::CStage*);
    CTexAnim* Duplicate(CMemory::CStage*);
    void AttachMaterialSet(CMaterialSet*);
    void AddFrame(float);
    int Find(char*);
    void Change(int, float, CTexAnimSet::ANIM_TYPE);
    void SetTexGen();
    int IsChin();
    float GetChin();

private:
    friend class CTexAnimSet;

    CRefData* m_refData;
    int m_seqIndex;
    float m_frame;
    int m_mode;
    Vec m_texGen;
};

#endif // _FFCC_PPP_TEXANIM_H_
