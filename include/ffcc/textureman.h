#ifndef _FFCC_PPP_TEXTUREMAN_H_
#define _FFCC_PPP_TEXTUREMAN_H_

#include "ffcc/memory.h"

#include <dolphin/gx.h>

class CChunkFile;
class CAmemCacheSet;
class CMemory;

enum _GXTexMapID;

class CTexture
{
public:
    CTexture();
    ~CTexture();

    static void* operator new(unsigned long, CMemory::CStage*, char*, int);

    void InitTexObj();
    void Create(CChunkFile&, CMemory::CStage*, CAmemCacheSet*, int, int);
    void CacheLoadTexture(CAmemCacheSet*);
    void CacheUnLoadTexture(CAmemCacheSet*);
    void CacheRefCnt0UpTexture(CAmemCacheSet*);
    void CacheDumpTexture(CAmemCacheSet*);
    void CheckName(char*);
    void SetExternalTlut(void*, int);
    void GetTlutColor(int);
    void GetExternalTlutColor(void*, int, int);
    void SetTlutColor(int, _GXColor);
    void SetExternalTlutColor(void*, int, int, _GXColor&);
    void FlushTlut();
    void FlushExternalTlut(void*);
    void FlushExternalTlut(void*, int);
    void GetNumTlut();
};

class CTextureSet
{
public:
    CTextureSet();
    ~CTextureSet();

    static void* operator new(unsigned long, CMemory::CStage*, char*, int);

    void Create(void*, CMemory::CStage*, int, CAmemCacheSet*, int, int);
    void Create(CChunkFile&, CMemory::CStage*, int, CAmemCacheSet*, int, int);
    void Find(char*);
    void ReleaseTextureIdx(int, CAmemCacheSet*);
};

class CTextureMan
{
public:
    CTextureMan();

    void Init();
    void Quit();
    void SetTexture(_GXTexMapID, CTexture*);
    void SetTextureTev(CTexture*);

    friend class CTexture;
    friend class CTextureSet;

private:
    void* m_vtable;
    CMemory::CStage* m_memoryStage;
};

#endif // _FFCC_PPP_TEXTUREMAN_H_
