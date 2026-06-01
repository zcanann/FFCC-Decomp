#define FFCC_TEXTUREMAN_USE_PTRARRAY_MEMBER
#include "ffcc/textureman.h"
#include "ffcc/chunkfile.h"
#include "ffcc/gxfunc.h"
#include "ffcc/system.h"

#include <string.h>
#include <PowerPC_EABI_Support/Runtime/New.h>

CTextureMan TextureMan;

inline void* operator new(unsigned long, void* p)
{
    return p;
}

extern const char s_CTextureSet_801D7968[] = "CTextureSet";
extern "C" const char s_textureman_cpp[] = "textureman.cpp";
static const char s_Error_width_pctd_height_pctd_801D7984[] = "Error width=%d height=%d\n";
static const char s_CTexture_texture_801D79A0[] = "CTexture.texture";
extern const char s_CTexture_801D79B4[] = "CTexture";
extern const char s_CTextureMan_801D79C0[] = "CTextureMan";
extern const char s_CManager_801D79CC[] = "CManager";
extern const char s_ptrarray_grow_error_801D79D8[] = {
    0x83, 0x6f, 0x83, 0x62, 0x83, 0x74, 0x83, 0x40, 0x90, 0xac, 0x92, 0xb7, 0x82, 0xaa,
    0x95, 0x73, 0x8b, 0x96, 0x89, 0xc2, 0x82, 0xc5, 0x82, 0xb7, 0x81, 0x42, 0x0a, 0x00,
};
extern const char s_collection_ptrarray_h_801D79F4[] = "collection_ptrarray.h";
extern const char s_CPtrArray_CTexture_801D7A0C[] = "CPtrArray<CTexture *>";
extern const char s_CRef_8032FAE8[];
extern const float FLOAT_8032faf0;
extern const float FLOAT_8032faf4;

/*
 * --INFO--
 * PAL Address: 0x8003B988
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexture::CTexture()
{
    m_maxLod = 0;
    m_imageData = 0;
    m_tlutData = 0;
    m_isIntensityAlpha = 0;
    m_isAlphaLut = 0;
    m_name[0] = 0;
    m_cacheId = -1;
    m_usesExternalAddress = 0;
}

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline unsigned short& U16At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned short*>(Ptr(p, offset));
}

static inline CTexture* AllocTexture()
{
    return ::new (Memory._Alloc(sizeof(CTexture), *reinterpret_cast<CMemory::CStage**>(Ptr(&TextureMan, 4)),
                                const_cast<char*>(s_textureman_cpp), 0x2ED, 0)) CTexture;
}

}

/*
 * --INFO--
 * PAL Address: 0x8003A5FC
 * PAL Size: 244b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureSet::ReleaseTextureIdx(int idx, CAmemCacheSet* amemCacheSet)
{
    if (m_textureArray[idx] != 0) {
        if (m_textureArray[idx]->m_cacheId != -1) {
            if (m_textureArray[idx]->GetRef() <= 1) {
                amemCacheSet->DestroyCache(m_textureArray[idx]->m_cacheId);
                m_textureArray[idx]->m_imageData = 0;
            }
        }

        CTexture* texture = m_textureArray[idx];
        if (texture->DecRef() == 0) {
            delete texture;
        }

        m_textureArray.SetAt(idx, 0);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003A6F0
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTextureSet::Find(char* name)
{
    for (unsigned long i = 0; i < static_cast<unsigned long>(m_textureArray.GetSize()); i++) {
        CTexture* texture = m_textureArray[i];
        if ((texture != 0) && (strcmp(texture->m_name, name) == 0)) {
            return static_cast<int>(i);
        }
    }
    return -1;
}

/*
 * --INFO--
 * PAL Address: 0x8003A77C
 * PAL Size: 560b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureSet::Create(CChunkFile& chunkFile, CMemory::CStage* stage, int append, CAmemCacheSet* amemCacheSet, int cacheTag, int useAddress)
{
    CChunkFile::CChunk chunk;
    CTexture* texture;

    if (append == 0) {
        m_textureArray.ReleaseAndRemoveAll();
    }

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x54585452:
            texture = AllocTexture();
            texture->Create(chunkFile, stage, amemCacheSet, cacheTag, useAddress);

            if (texture->m_name[0] != 0) {
                unsigned int duplicateIdx;
                for (duplicateIdx = 0; duplicateIdx < (unsigned int)m_textureArray.GetSize(); duplicateIdx++) {
                    CTexture* existing = m_textureArray[duplicateIdx];
                    if ((existing != 0) && (strcmp(existing->m_name, texture->m_name) == 0)) {
                        goto found_duplicate;
                    }
                }
                duplicateIdx = 0xFFFFFFFF;

            found_duplicate:
                if ((int)duplicateIdx >= 0) {
                    if (amemCacheSet != 0) {
                        amemCacheSet->DestroyCache(static_cast<int>(texture->m_cacheId));
                        amemCacheSet->AmemPrev();
                    }

                    if (texture->DecRef() == 0) {
                        delete texture;
                    }

                    texture = m_textureArray[duplicateIdx];
                    texture->AddRef();
                }
            }

            if (append != 0) {
                for (unsigned int i = 0; i < (unsigned int)m_textureArray.GetSize(); i++) {
                    if (m_textureArray[i] == 0) {
                        m_textureArray.SetAt(i, texture);
                        goto next_chunk;
                    }
                }
            }

            m_textureArray.Add(texture);
        next_chunk:;
            break;
        }
    }
    chunkFile.PopChunk();
}

/*
 * --INFO--
 * PAL Address: 0x8003A9AC
 * PAL Size: 712b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureSet::Create(void* filePtr, CMemory::CStage* stage, int append, CAmemCacheSet* amemCacheSet, int cacheTag, int useAddress)
{
    CChunkFile::CChunk chunk;
    CChunkFile::CChunk textureChunk;
    CChunkFile chunkFile(filePtr);

    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id != 0x54455820) {
            continue;
        }

        chunkFile.PushChunk();
        while (chunkFile.GetNextChunk(chunk)) {
            if (chunk.m_id == 0x5343454E) {
                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 0x54534554) {
                        if (append == 0) {
                            m_textureArray.ReleaseAndRemoveAll();
                        }

                        chunkFile.PushChunk();
                        while (chunkFile.GetNextChunk(textureChunk)) {
                            switch (textureChunk.m_id) {
                            case 0x54585452:
                                CTexture* texture = AllocTexture();
                                texture->Create(chunkFile, stage, amemCacheSet, cacheTag, useAddress);

                                if (texture->m_name[0] != 0) {
                                    char* textureName = texture->m_name;
                                    unsigned int duplicateIdx;
                                    for (duplicateIdx = 0; duplicateIdx < (unsigned int)m_textureArray.GetSize(); duplicateIdx++) {
                                        CTexture* existing = m_textureArray[duplicateIdx];
                                        if ((existing != 0)
                                            && (strcmp(existing->m_name, textureName) == 0)) {
                                            goto found_duplicate;
                                        }
                                    }
                                    duplicateIdx = 0xFFFFFFFF;

                                found_duplicate:
                                    if ((int)duplicateIdx >= 0) {
                                        if (amemCacheSet != 0) {
                                            amemCacheSet->DestroyCache(static_cast<int>(texture->m_cacheId));
                                            amemCacheSet->AmemPrev();
                                        }

                                        if (texture->DecRef() == 0) {
                                            delete texture;
                                        }

                                        texture = m_textureArray[duplicateIdx];
                                        texture->AddRef();
                                    }
                                }

                                if (append != 0) {
                                    for (unsigned long i = 0; i < static_cast<unsigned long>(m_textureArray.GetSize()); i++) {
                                        if (m_textureArray[i] == 0) {
                                            m_textureArray.SetAt(i, texture);
                                            goto next_texture;
                                        }
                                    }
                                }

                                m_textureArray.Add(texture);
                                break;
                            }
                        next_texture:;
                            }
                        chunkFile.PopChunk();
                    }
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003AC74
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CTextureSet::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, TextureMan.m_memoryStage, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003AD7C
 * PAL Size: 132b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTextureSet::~CTextureSet()
{
    m_textureArray.ReleaseAndRemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8003AD30
 * PAL Size: 96b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTextureSet::CTextureSet()
{
    m_textureArray.SetDefaultSize(0x10);
    m_textureArray.SetStage(TextureMan.m_memoryStage);
}

/*
 * --INFO--
 * PAL Address: 0x8003AD90
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::FlushExternalTlut(void* tlutData)
{
    int numEntries;

    if (m_format == 9) {
        numEntries = 0x100;
    } else if (m_format == 8) {
        numEntries = 0x10;
    } else {
        numEntries = 0;
    }
    DCFlushRange(tlutData, numEntries << 2);
}

/*
 * --INFO--
 * PAL Address: 0x8003ADE0
 * PAL Size: 80b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::FlushTlut()
{
    int numEntries;

    if (m_format == 9) {
        numEntries = 0x100;
    } else if (m_format == 8) {
        numEntries = 0x10;
    } else {
        numEntries = 0;
    }
    DCFlushRange(m_tlutData, numEntries << 2);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::FlushExternalTlut(void* tlutData, int format)
{
    int numEntries;

    if (format == 9) {
        numEntries = 0x100;
    } else if (format == 8) {
        numEntries = 0x10;
    } else {
        numEntries = 0;
    }
    DCFlushRange(tlutData, numEntries << 2);
}

/*
 * --INFO--
 * PAL Address: 0x8003AE30
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::SetExternalTlutColor(void* tlutData, int tlutOffset, int index, _GXColor& color)
{
    unsigned int packedColor;
    unsigned char* packedBytes = reinterpret_cast<unsigned char*>(&packedColor);
    packedBytes[3] = color.r;
    packedBytes[0] = color.a;
    packedBytes[1] = color.b;
    packedBytes[2] = color.g;

    unsigned short* tlut = reinterpret_cast<unsigned short*>(tlutData);
    tlut[index + tlutOffset] = static_cast<unsigned short>(packedColor >> 16);
    tlut[index] = static_cast<unsigned short>(packedColor);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
_GXColor CTexture::GetExternalTlutColor(void* tlutData, int tlutOffset, int index)
{
    unsigned short* tlut = reinterpret_cast<unsigned short*>(tlutData);
    _GXColor color;
    unsigned int packed = tlut[index] | (tlut[index + tlutOffset] << 16);
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&packed);

    color.a = bytes[0];
    color.r = bytes[3];
    color.g = bytes[2];
    color.b = bytes[1];
    return color;
}

/*
 * --INFO--
 * PAL Address: 0x8003AE78
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::SetTlutColor(int index, _GXColor color)
{
    unsigned char* packedColor = reinterpret_cast<unsigned char*>(&color);
    int offset;

    if (m_format == 9) {
        offset = 0x100;
    } else if (m_format == 8) {
        offset = 0x10;
    } else {
        offset = 0;
    }

    u32 packed;
    unsigned char* packedBytes = reinterpret_cast<unsigned char*>(&packed);
    packedBytes[3] = packedColor[0];
    packedBytes[0] = packedColor[3];
    packedBytes[1] = packedColor[2];
    packedBytes[2] = packedColor[1];

    u16* tlut = reinterpret_cast<u16*>(m_tlutData);
    tlut[index + offset] = packed >> 16;
    tlut[index] = packed;
}

/*
 * --INFO--
 * PAL Address: 0x8003AEEC
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
_GXColor CTexture::GetTlutColor(int index)
{
    unsigned int format = static_cast<unsigned int>(m_format);
    int offset;
    if (format == 9) {
        offset = 0x100;
    } else if (format == 8) {
        offset = 0x10;
    } else {
        offset = 0;
    }

    unsigned short* tlut = reinterpret_cast<unsigned short*>(m_tlutData);
    _GXColor color;
    unsigned int packed = tlut[index] | (tlut[index + offset] << 16);
    unsigned char* bytes = reinterpret_cast<unsigned char*>(&packed);

    color.a = bytes[0];
    color.r = bytes[3];
    color.g = bytes[2];
    color.b = bytes[1];
    return color;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::CopyTlut(_GXColor* colors)
{
    int numEntries = (m_format == 9) ? 0x100 : 0x10;

    for (int i = 0; i < numEntries; i++) {
        colors[i] = GetTlutColor(i);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003AF64
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::SetExternalTlut(void* tlutData, int loadToGX)
{
    if (tlutData == 0) {
        tlutData = m_tlutData;
    }

    int numEntries = (static_cast<unsigned int>(m_format) == 9) ? 0x100 : 0x10;
    GXInitTlutObj(&m_tlutObj0, tlutData, GX_TL_IA8, numEntries);

    numEntries = (static_cast<unsigned int>(m_format) == 9) ? 0x100 : 0x10;
    int offset = (static_cast<unsigned int>(m_format) == 9) ? 0x100 : 0x10;
    GXInitTlutObj(&m_tlutObj1, reinterpret_cast<void*>(reinterpret_cast<int>(tlutData) + offset * 2), GX_TL_IA8, numEntries);

    if (loadToGX != 0) {
        GXLoadTlut(&m_tlutObj0, GX_TLUT0);
        GXLoadTlut(&m_tlutObj1, GX_TLUT1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003B030
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTexture::CheckName(char* name)
{
    return strcmp(m_name, name) == 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003B05C
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::CacheUnLoadTexture(CAmemCacheSet* amemCacheSet)
{
    if (m_cacheId != -1) {
        amemCacheSet->Release(m_cacheId);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003B090
 * PAL Size: 436b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::CacheLoadTexture(CAmemCacheSet* amemCacheSet)
{
    if (m_cacheId != -1) {
        if (amemCacheSet->IsEnable(m_cacheId) == 0) {
            m_imageData = reinterpret_cast<void*>(
                amemCacheSet->GetData(m_cacheId, const_cast<char*>(s_textureman_cpp), 0x1DD));

            unsigned int format = m_format;
            int tlutData = reinterpret_cast<int>(m_tlutData);
            if ((format == 9) || (format == 8)) {
                GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                               static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                               static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);
                GXInitTlutObj(&m_tlutObj0, reinterpret_cast<void*>(tlutData), GX_TL_IA8,
                              m_format == 9 ? 0x100 : 0x10);
                GXInitTlutObj(&m_tlutObj1,
                              reinterpret_cast<void*>(tlutData + (m_format == 9 ? 0x100 : 0x10) * 2),
                              GX_TL_IA8, m_format == 9 ? 0x100 : 0x10);
            } else {
                unsigned int mipmap = (1 - m_maxLod) >> 31;
                GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                             static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                             static_cast<GXTexWrapMode>(m_wrapMode), mipmap);
            }

            if (1 < m_maxLod) {
                GXInitTexObjLOD(&m_texObj, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, static_cast<float>(m_maxLod) - 1.0f,
                                0.0f, GX_TRUE, GX_FALSE, GX_ANISO_1);
            }
        }
        amemCacheSet->AddRef(m_cacheId);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003B244
 * PAL Size: 1260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::Create(CChunkFile& chunkFile, CMemory::CStage* stage, CAmemCacheSet* amemCacheSet, int cacheTag, int useAddress)
{
    CChunkFile::CChunk chunk;
    unsigned int width;
    unsigned int height;
    unsigned int format;

    m_wrapMode = 1;
    m_format = 6;
    m_isAlphaLut = 0;
    m_usesExternalAddress = static_cast<unsigned char>(useAddress);

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x4E414D45:
            strcpy(m_name, chunkFile.GetString());
            break;
        case 0x53495A45:
            m_width = chunkFile.Get4();
            m_height = chunkFile.Get4();
            if ((static_cast<unsigned int>(m_width) == 0) || (static_cast<unsigned int>(m_height) == 0)) {
                System.Printf(const_cast<char*>(s_Error_width_pctd_height_pctd_801D7984), m_width, m_height);
                chunkFile.PopChunk();
                return;
            }
            break;
        case 0x494D4147:
            if (amemCacheSet != 0) {
                u8* data = static_cast<u8*>(
                    Memory._Alloc(chunk.m_size, stage, const_cast<char*>(s_textureman_cpp), 0x150, 0));
                chunkFile.Get(data, chunk.m_size);
                m_cacheId = amemCacheSet->SetData(data, chunk.m_size, CAmemCache::TEXTURE, cacheTag);
                operator delete(data);
                m_imageData = 0;
            } else {
                if (m_usesExternalAddress != 0) {
                    m_imageData = chunkFile.GetAddress();
                } else {
                    m_imageData =
                        Memory._Alloc(chunk.m_size, stage, const_cast<char*>(s_textureman_cpp), 0x15C, 0);
                    chunkFile.Get(m_imageData, chunk.m_size);
                }
                DCFlushRange(m_imageData, chunk.m_size);
                m_cacheId = -1;
            }
            break;
        case 0x50414C54:
            if (m_usesExternalAddress != 0) {
                m_tlutData = chunkFile.GetAddress();
            } else {
                m_tlutData =
                    Memory._Alloc(chunk.m_size, stage, const_cast<char*>(s_textureman_cpp), 0x178, 0);
                chunkFile.Get(m_tlutData, chunk.m_size);
            }
            DCFlushRange(m_tlutData, chunk.m_size);
            break;
        case 0x464D5420: {
            unsigned char chunkFormat = chunkFile.Get1();

            switch (chunkFormat) {
            case 0:
                m_format = 6;
                break;
            case 1:
                m_format = 4;
                break;
            case 2:
                m_format = 9;
                break;
            case 3:
                m_format = 8;
                break;
            case 6:
                m_format = 0xE;
                break;
            case 7:
                m_format = 3;
                m_isIntensityAlpha = 1;
                break;
            case 8:
                m_format = 3;
                break;
            case 9:
                m_format = 1;
                break;
            case 10:
                m_format = 0xE;
                m_isAlphaLut = 1;
                break;
            case 5:
                m_format = 0;
                break;
            }

            m_maxLod = chunkFile.Get1();
            chunkFormat = chunkFile.Get1();
            unsigned int wrapMode = chunkFormat;
            if (static_cast<int>(chunk.m_size) > 3) {
                m_wrapMode = wrapMode;
            }
            break;
        }
        }
    }
    chunkFile.PopChunk();

    width = m_width;
    for (;;) {
        if ((width & 1) != 0) {
            break;
        }
        width >>= 1;
    }
    height = m_height;
    for (;;) {
        if ((height & 1) != 0) {
            break;
        }
        height >>= 1;
    }
    if ((width != 1) || (height != 1)) {
        m_wrapMode = 0;
    }
    if (m_cacheId != -1) {
        return;
    }

    format = m_format;
    int tlutData = reinterpret_cast<int>(m_tlutData);
    if ((format == 9) || (format == 8)) {
        GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                       static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                       static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);
        GXInitTlutObj(&m_tlutObj0, reinterpret_cast<void*>(tlutData), GX_TL_IA8,
                      m_format == 9 ? 0x100 : 0x10);
        GXInitTlutObj(&m_tlutObj1,
                      reinterpret_cast<void*>(tlutData + (m_format == 9 ? 0x100 : 0x10) * 2),
                      GX_TL_IA8, m_format == 9 ? 0x100 : 0x10);
    } else {
        unsigned int mipmap = (1 - m_maxLod) >> 31;
        GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                     static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                     static_cast<GXTexWrapMode>(m_wrapMode), mipmap);
    }

    if (1 < m_maxLod) {
        GXInitTexObjLOD(&m_texObj, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f,
                        static_cast<float>(m_maxLod) - 1.0f, 0.0f, GX_TRUE, GX_FALSE, GX_ANISO_1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003B730
 * PAL Size: 356b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::InitTexObj()
{
    unsigned int format = m_format;
    int tlutData = reinterpret_cast<int>(m_tlutData);
    if ((format == 9) || (format == 8)) {
        GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                       static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                       static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);
        GXInitTlutObj(&m_tlutObj0, reinterpret_cast<void*>(tlutData), GX_TL_IA8, m_format == 9 ? 0x100 : 0x10);
        GXInitTlutObj(&m_tlutObj1,
                      reinterpret_cast<void*>(tlutData + (m_format == 9 ? 0x100 : 0x10) * 2),
                      GX_TL_IA8, m_format == 9 ? 0x100 : 0x10);
    } else {
        unsigned int mipmap = (1 - m_maxLod) >> 31;
        GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                     static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                     static_cast<GXTexWrapMode>(m_wrapMode), mipmap);
    }

    if (1 < m_maxLod) {
        GXInitTexObjLOD(&m_texObj, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, static_cast<float>(m_maxLod) - 1.0f,
                        0.0f, GX_TRUE, GX_FALSE, GX_ANISO_1);
    }
}

extern const char s_CRef_8032FAE8[] = "CRef";
extern const float FLOAT_8032faf0 = 1.0f;
extern const float FLOAT_8032faf4 = 0.0f;

/*
 * --INFO--
 * PAL Address: 0x8003B894
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CTexture::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, TextureMan.m_memoryStage, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003B8D8
 * PAL Size: 176b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CTexture::~CTexture()
{
    if (m_usesExternalAddress != 0) {
        m_imageData = 0;
        m_tlutData = 0;
    } else {
        if (m_imageData != 0) {
            delete[] static_cast<u8*>(m_imageData);
            m_imageData = 0;
        }
        if (m_tlutData != 0) {
            delete[] static_cast<u8*>(m_tlutData);
            m_tlutData = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003B9EC
 * PAL Size: 804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTextureMan::SetTextureTev(CTexture* texture)
{
    bool usePalette;

    GXSetNumIndStages(0);
    if (texture == 0) {
        GXSetNumTevStages(1);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
        return 1;
    }

    usePalette = (texture->m_format == 9) || (texture->m_format == 8);
    if (usePalette) {
        GXColor tevColor2;
        GXColor tevColor1;

        tevColor1.r = 0xFF;
        tevColor1.g = 0xFF;
        tevColor1.b = 0;
        tevColor1.a = 0;

        tevColor2.r = 0;
        tevColor2.g = 0;
        tevColor2.b = 0xFF;
        tevColor2.a = 0xFF;

        GXSetTevColor((GXTevRegID)1, tevColor1);
        GXSetTevColor((GXTevRegID)2, tevColor2);

        _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_ALPHA, GX_CH_ALPHA, GX_CH_ALPHA);
        _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_BLUE, GX_CH_BLUE, GX_CH_BLUE, GX_CH_ALPHA);

        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
        GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_1);
        GXSetTevKAlphaSel(GX_TEVSTAGE2, GX_TEV_KASEL_1);

        GXSetNumTevStages(3);
        GXSetTevDirect(GX_TEVSTAGE0);
        _GXSetTevColorIn(GX_TEVSTAGE0, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C0, GX_CC_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE0, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_FALSE, GX_TEVPREV);
        _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP1);
        _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR_NULL);

        GXSetTevDirect(GX_TEVSTAGE1);
        _GXSetTevColorIn(GX_TEVSTAGE1, GX_CC_ZERO, GX_CC_TEXC, GX_CC_C1, GX_CC_CPREV);
        _GXSetTevAlphaIn(GX_TEVSTAGE1, GX_CA_ZERO, GX_CA_KONST, GX_CA_TEXA, GX_CA_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaOp(GX_TEVSTAGE1, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevSwapMode(GX_TEVSTAGE1, GX_TEV_SWAP0, GX_TEV_SWAP2);
        _GXSetTevOrder(GX_TEVSTAGE1, GX_TEXCOORD0, GX_TEXMAP1, GX_COLOR_NULL);

        GXSetTevDirect(GX_TEVSTAGE2);
        _GXSetTevColorIn(GX_TEVSTAGE2, GX_CC_ZERO, GX_CC_CPREV, GX_CC_RASC, GX_CC_ZERO);
        _GXSetTevAlphaIn(GX_TEVSTAGE2, GX_CA_ZERO, GX_CA_APREV, GX_CA_RASA, GX_CA_ZERO);
        _GXSetTevColorOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevAlphaOp(GX_TEVSTAGE2, GX_TEV_ADD, GX_TB_ZERO, GX_CS_SCALE_1, GX_TRUE, GX_TEVPREV);
        _GXSetTevSwapMode(GX_TEVSTAGE2, GX_TEV_SWAP0, GX_TEV_SWAP0);
        _GXSetTevOrder(GX_TEVSTAGE2, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
        return 3;
    }

    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8003BD10
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTextureMan::SetTexture(_GXTexMapID texMapId, CTexture* texture)
{
    int usePalette = (texture->m_format == 9) || (texture->m_format == 8);

    if (usePalette) {
        GXInitTexObjTlut(&texture->m_texObj, GX_TLUT0);
    }

    GXLoadTexObj(&texture->m_texObj, texMapId);

    if (usePalette) {
        GXInitTexObjTlut(&texture->m_texObj, GX_TLUT1);
        GXLoadTexObj(&texture->m_texObj, static_cast<_GXTexMapID>(texMapId + 1));
        GXLoadTlut(&texture->m_tlutObj0, GX_TLUT0);
        GXLoadTlut(&texture->m_tlutObj1, GX_TLUT1);
    }

    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003BDC4
 * PAL Size: 48b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureMan::Quit()
{
	Memory.DestroyStage(m_memoryStage);
}

/*
 * --INFO--
 * PAL Address: 0x8003BDF4
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureMan::Init()
{
	m_memoryStage = Memory.CreateStage(0x40000, const_cast<char*>(s_CTexture_texture_801D79A0), 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003BE3C
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CTexture*>::CPtrArray()
{
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8003BE70
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CPtrArray<CTexture*>::~CPtrArray()
{
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8003BECC
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
bool CPtrArray<CTexture*>::Add(CTexture* item)
{
    if (setSize(m_numItems + 1) == 0) {
        return false;
    }

    m_items[m_numItems] = item;
    m_numItems++;
    return true;
}

/*
 * --INFO--
 * PAL Address: 0x8003BF3C
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
#pragma dont_inline on
template <>
void CPtrArray<CTexture*>::SetAt(unsigned long index, CTexture* item)
{
    m_items[index] = item;
}

/*
 * --INFO--
 * PAL Address: 0x8003BF4C
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CTexture*>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x8003BF54
 * PAL Size: 76b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexture*>::RemoveAll()
{
    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003BFA0
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexture*>::ReleaseAndRemoveAll()
{
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        CTexture* item = m_items[i];
        if (item != 0) {
            int nextRefCount = item->refCount - 1;
            item->refCount = nextRefCount;
            if (nextRefCount == 0) {
                delete item;
            }
            m_items[i] = 0;
        }
    }

    if (m_items != 0) {
        delete[] m_items;
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003C06C
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CTexture* CPtrArray<CTexture*>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x8003C08C
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexture*>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x8003C094
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
void CPtrArray<CTexture*>::SetDefaultSize(unsigned long defaultSize)
{
    m_defaultSize = defaultSize;
}
#pragma dont_inline reset

/*
 * --INFO--
 * PAL Address: 0x8003C09C
 * PAL Size: 240b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
int CPtrArray<CTexture*>::setSize(unsigned long newSize)
{
    CTexture** newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(const_cast<char*>(s_ptrarray_grow_error_801D79D8));
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<CTexture**>(
            Memory._Alloc(static_cast<unsigned long>(m_size << 2), m_stage,
                          const_cast<char*>(s_collection_ptrarray_h_801D79F4), 0xFA, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            delete[] m_items;
            m_items = 0;
        }
        m_items = newItems;
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8003C18C
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
template <>
CTexture* CPtrArray<CTexture*>::GetAt(unsigned long index)
{
    return m_items[index];
}
