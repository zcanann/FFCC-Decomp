#ifndef _FFCC_PPP_TEXTUREMAN_H_
#define _FFCC_PPP_TEXTUREMAN_H_

#include "ffcc/manager.h"
#include "ffcc/memory.h"
#include "ffcc/ref.h"

#include <dolphin/gx.h>

class CChunkFile;
class CAmemCacheSet;
class CMemory;

enum _GXTexMapID;

class CTexture : public CRef
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

    char m_name[0x20];
    GXTexObj m_texObj;
    GXTlutObj m_tlutObj0;
    GXTlutObj m_tlutObj1;
    int m_format;
    int m_width;
    int m_height;
    int m_wrapMode;
    unsigned char m_isIntensityAlpha;
    unsigned char m_isAlphaLut;
    short m_cacheId;
    unsigned char m_maxLod;
    unsigned char m_usesExternalAddress;
    void* m_imageData;
    void* m_tlutData;
};

class CTextureSet : public CRef
{
public:
    CTextureSet();
    ~CTextureSet();

    static void* operator new(unsigned long, CMemory::CStage*, char*, int);

    void Create(void*, CMemory::CStage*, int, CAmemCacheSet*, int, int);
    void Create(CChunkFile&, CMemory::CStage*, int, CAmemCacheSet*, int, int);
    int Find(char*);
    void ReleaseTextureIdx(int, CAmemCacheSet*);

    unsigned char m_textureArrayStorage[0x1C];
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

extern CTextureMan TextureMan;

#endif // _FFCC_PPP_TEXTUREMAN_H_
