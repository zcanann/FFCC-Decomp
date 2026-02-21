#ifndef _FFCC_PPP_TEXTUREMAN_H_
#define _FFCC_PPP_TEXTUREMAN_H_

#include "ffcc/manager.h"
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
    int CheckName(char*);
    void SetExternalTlut(void*, int);
    _GXColor GetTlutColor(int);
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
    int Find(char*);
    void ReleaseTextureIdx(int, CAmemCacheSet*);
};

class CTextureMan : public CManager
{
public:
    void Init();
    void Quit();
    int SetTexture(_GXTexMapID, CTexture*);
    int SetTextureTev(CTexture*);

    friend class CTexture;
    friend class CTextureSet;

private:
    CMemory::CStage* m_memoryStage;
};

#endif // _FFCC_PPP_TEXTUREMAN_H_
