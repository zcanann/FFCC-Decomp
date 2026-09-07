#ifndef _FFCC_PPP_TEXTUREMAN_H_
#define _FFCC_PPP_TEXTUREMAN_H_

#include "ffcc/manager.h"
#include "ffcc/memory.h"
#include "ffcc/ptrarray_decl.h"
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
    void CacheRefCnt0UpTexture(CAmemCacheSet* amemCacheSet)
    {
        if (m_cacheId != -1) {
            amemCacheSet->RefCnt0Up(m_cacheId);
        }
    }
    void CacheDumpTexture(CAmemCacheSet* amemCacheSet)
    {
        if (m_cacheId != -1) {
            if (GetRef() <= 1) {
                m_imageData = 0;
            }
            amemCacheSet->Release(m_cacheId);
        }
    }
    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x80046364
     * EN Size: 48b
     * JP Address: TODO
     * JP Size: TODO
     */
    int GetNumTlut()
    {
        if (m_format == GX_TF_C8) {
            return 0x100;
        }
        if (m_format == GX_TF_C4) {
            return 0x10;
        }
        return 0;
    }

    int CheckName(char*);
    void SetExternalTlut(void*, int);
    void FlushExternalTlut(void*, int);
    _GXColor GetTlutColor(int);
    void CopyTlut(_GXColor*);
    void SetTlutColor(int, _GXColor);
    static _GXColor GetExternalTlutColor(void*, int, int);
    static void SetExternalTlutColor(void*, int, int, _GXColor&);
    void FlushTlut();
    void FlushExternalTlut(void*);

    char m_name[0x20];
    GXTexObj m_texObj;
    GXTlutObj m_tlutObj0;
    GXTlutObj m_tlutObj1;
    unsigned int m_format;
    unsigned int m_width;
    unsigned int m_height;
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
    CTexture* GetTexture(long index) { return m_textureArray.GetAt(static_cast<unsigned long>(index)); }
    int GetNumTexture() { return m_textureArray.GetSize(); }

    CPtrArray<CTexture*> m_textureArray;
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
