#include "ffcc/textureman.h"
#include "ffcc/chunkfile.h"
#include "ffcc/gxfunc.h"
#include "ffcc/system.h"

#include <string.h>
#include <PowerPC_EABI_Support/Runtime/New.h>

CTextureMan TextureMan;

enum {
    kTextureC8TlutEntries = 0x100,
    kTextureC4TlutEntries = 0x10
};

/*
 * --INFO--
 * PAL Address: 0x8003BE3C
 * PAL Size: 52b
 * EN Address: 0x800463AC
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
CPtrArray<T>::CPtrArray()
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
 * EN Address: 0x800463E8
 * EN Size: 96b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
CPtrArray<T>::~CPtrArray()
{
    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8003BECC
 * PAL Size: 112b
 * EN Address: 0x80046448
 * EN Size: 112b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
int CPtrArray<T>::Add(T item)
{
    if (setSize(m_numItems + 1) == 0) {
        return 0;
    }

    m_items[m_numItems] = item;
    m_numItems++;
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8003BF3C
 * PAL Size: 16b
 * EN Address: 0x800464B8
 * EN Size: 148b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
void CPtrArray<T>::SetAt(unsigned long index, T item)
{
    m_items[index] = item;
}

/*
 * --INFO--
 * PAL Address: 0x8003BF4C
 * PAL Size: 8b
 * EN Address: 0x8004654C
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
int CPtrArray<T>::GetSize()
{
    return m_numItems;
}

/*
 * --INFO--
 * PAL Address: 0x8003BF54
 * PAL Size: 76b
 * EN Address: 0x80046554
 * EN Size: 80b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
void CPtrArray<T>::RemoveAll()
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
 * EN Address: 0x800465A4
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
void CPtrArray<T>::ReleaseAndRemoveAll()
{
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        CRef* item = m_items[i];
        if (item != 0) {
            if (--item->refCount == 0) {
                delete item;
            }
            m_items[i] = 0;
        }
    }

    RemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8003C06C
 * PAL Size: 32b
 * EN Address: 0x80046628
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
T CPtrArray<T>::operator[](unsigned long index)
{
    return GetAt(index);
}

/*
 * --INFO--
 * PAL Address: 0x8003C08C
 * PAL Size: 8b
 * EN Address: 0x80046658
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
void CPtrArray<T>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

/*
 * --INFO--
 * PAL Address: 0x8003C094
 * PAL Size: 8b
 * EN Address: 0x80046660
 * EN Size: 8b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
void CPtrArray<T>::SetDefaultSize(unsigned long defaultSize)
{
    m_defaultSize = defaultSize;
}

/*
 * --INFO--
 * PAL Address: 0x8003C09C
 * PAL Size: 240b
 * EN Address: 0x80046668
 * EN Size: 380b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
int CPtrArray<T>::setSize(unsigned long newSize)
{
    T* newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf("\203o\203b\203t\203@\220\254\222\267\202\252\225s\213\226\211\302\202\305\202\267\201B\012");
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<T*>(
            Memory._Alloc(m_size * sizeof(T), m_stage,
                          "collection_ptrarray.h", 0xFA, 0));
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems * sizeof(T));
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
 * EN Address: 0x800467E4
 * EN Size: 140b
 * JP Address: TODO
 * JP Size: TODO
 */
template <class T>
T CPtrArray<T>::GetAt(unsigned long index)
{
    return m_items[index];
}
/*
 * --INFO--
 * PAL Address: 0x8003BDF4
 * PAL Size: 72b
 * EN Address: 0x80044CF0
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureMan::Init()
{
	m_memoryStage = Memory.CreateStage(0x40000, "CTexture.texture", 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003BDC4
 * PAL Size: 48b
 * EN Address: 0x80044D38
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureMan::Quit()
{
	Memory.DestroyStage(m_memoryStage);
}

/*
 * --INFO--
 * PAL Address: 0x8003BD10
 * PAL Size: 180b
 * EN Address: 0x80044D70
 * EN Size: 284b
 * JP Address: TODO
 * JP Size: TODO
 */
int CTextureMan::SetTexture(_GXTexMapID texMapId, CTexture* texture)
{
    int usePalette = (texture->m_format == GX_TF_C8) || (texture->m_format == GX_TF_C4);

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
 * PAL Address: 0x8003B9EC
 * PAL Size: 804b
 * EN Address: 0x80044E8C
 * EN Size: 908b
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

    usePalette = (texture->m_format == GX_TF_C8) || (texture->m_format == GX_TF_C4);
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
 * PAL Address: 0x8003B988
 * PAL Size: 100b
 * EN Address: 0x80045218
 * EN Size: 140b
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

static inline int TextureTlutEntryCount(unsigned int format)
{
    if (format == GX_TF_C8) {
        return kTextureC8TlutEntries;
    }
    if (format == GX_TF_C4) {
        return kTextureC4TlutEntries;
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003B8D8
 * PAL Size: 176b
 * EN Address: 0x800452A4
 * EN Size: 200b
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
 * PAL Address: 0x8003B894
 * PAL Size: 68b
 * EN Address: 0x8004536C
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
void* CTexture::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, TextureMan.m_memoryStage, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003B730
 * PAL Size: 356b
 * EN Address: 0x800453B8
 * EN Size: 296b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::InitTexObj()
{
    unsigned int format = m_format;
    if ((format == GX_TF_C8) || (format == GX_TF_C4)) {
        GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                       static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                       static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);
        void* tlutData = (m_tlutData != 0) ? m_tlutData : m_tlutData;
        {
            int numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
            GXInitTlutObj(&m_tlutObj0, tlutData, GX_TL_IA8, numEntries);
            numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
            int tlutOffset = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
            GXInitTlutObj(&m_tlutObj1, static_cast<u8*>(tlutData) + tlutOffset * 2,
                          GX_TL_IA8, numEntries);
        }
    } else {
        GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                     static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                     static_cast<GXTexWrapMode>(m_wrapMode), (1 < m_maxLod) ? GX_TRUE : GX_FALSE);
    }

    if (1 < m_maxLod) {
        GXInitTexObjLOD(&m_texObj, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f, static_cast<float>(m_maxLod) - 1.0f,
                        0.0f, GX_TRUE, GX_FALSE, GX_ANISO_1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003B244
 * PAL Size: 1260b
 * EN Address: 0x800454E0
 * EN Size: 1104b
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
                System.Printf("Error width=%d height=%d\n", m_width, m_height);
                chunkFile.PopChunk();
                return;
            }
            break;
        case 0x494D4147:
            if (amemCacheSet != 0) {
                u8* data = static_cast<u8*>(
                    Memory._Alloc(chunk.m_size, stage, "textureman.cpp", 0x150, 0));
                chunkFile.Get(data, chunk.m_size);
                m_cacheId = amemCacheSet->SetData(data, chunk.m_size, CAmemCache::TEXTURE, cacheTag);
                operator delete(data);
                m_imageData = 0;
            } else {
                if (m_usesExternalAddress != 0) {
                    m_imageData = chunkFile.GetAddress();
                } else {
                    m_imageData =
                        Memory._Alloc(chunk.m_size, stage, "textureman.cpp", 0x15C, 0);
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
                    Memory._Alloc(chunk.m_size, stage, "textureman.cpp", 0x178, 0);
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
    if ((format == GX_TF_C8) || (format == GX_TF_C4)) {
        GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                       static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                       static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);
        void* tlutData = (m_tlutData != 0) ? m_tlutData : m_tlutData;
        {
            int numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
            GXInitTlutObj(&m_tlutObj0, tlutData, GX_TL_IA8, numEntries);
            numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
            int tlutOffset = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
            GXInitTlutObj(&m_tlutObj1, static_cast<u8*>(tlutData) + tlutOffset * 2,
                          GX_TL_IA8, numEntries);
        }
    } else {
        GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                     static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                     static_cast<GXTexWrapMode>(m_wrapMode), (1 < m_maxLod) ? GX_TRUE : GX_FALSE);
    }

    if (1 < m_maxLod) {
        GXInitTexObjLOD(&m_texObj, GX_LIN_MIP_LIN, GX_LINEAR, 0.0f,
                        static_cast<float>(m_maxLod) - 1.0f, 0.0f, GX_TRUE, GX_FALSE, GX_ANISO_1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003B090
 * PAL Size: 436b
 * EN Address: 0x80045930
 * EN Size: 132b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::CacheLoadTexture(CAmemCacheSet* amemCacheSet)
{
    if (m_cacheId != -1) {
        if (amemCacheSet->IsEnable(m_cacheId) == 0) {
            m_imageData = reinterpret_cast<void*>(
                amemCacheSet->GetData(m_cacheId, "textureman.cpp", 0x1DD));

            unsigned int format = m_format;
            if ((format == GX_TF_C8) || (format == GX_TF_C4)) {
                GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                               static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                               static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);
                void* tlutData = (m_tlutData != 0) ? m_tlutData : m_tlutData;
                {
                    int numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
                    GXInitTlutObj(&m_tlutObj0, tlutData, GX_TL_IA8, numEntries);
                    numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
                    int tlutOffset = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
                    GXInitTlutObj(&m_tlutObj1, static_cast<u8*>(tlutData) + tlutOffset * 2,
                                  GX_TL_IA8, numEntries);
                }
            } else {
                GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                             static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                             static_cast<GXTexWrapMode>(m_wrapMode), (1 < m_maxLod) ? GX_TRUE : GX_FALSE);
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
 * PAL Address: 0x8003B05C
 * PAL Size: 52b
 * EN Address: 0x800459B4
 * EN Size: 68b
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
 * PAL Address: 0x8003B030
 * PAL Size: 44b
 * EN Address: 0x80045AA4
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
int CTexture::CheckName(char* name)
{
    return strcmp(m_name, name) == 0;
}

/*
 * --INFO--
 * PAL Address: 0x8003AF64
 * PAL Size: 204b
 * EN Address: 0x80045AE4
 * EN Size: 236b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::SetExternalTlut(void* tlutData, int loadToGX)
{
    if (tlutData == 0) {
        tlutData = m_tlutData;
    }

    int numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
    GXInitTlutObj(&m_tlutObj0, tlutData, GX_TL_IA8, numEntries);
    numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
    int tlutOffset = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;
    GXInitTlutObj(&m_tlutObj1, static_cast<u8*>(tlutData) + tlutOffset * 2, GX_TL_IA8, numEntries);

    if (loadToGX != 0) {
        GXLoadTlut(&m_tlutObj0, GX_TLUT0);
        GXLoadTlut(&m_tlutObj1, GX_TLUT1);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003AEEC
 * PAL Size: 120b
 * EN Address: 0x80045BD0
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
_GXColor CTexture::GetTlutColor(int index)
{
    return GetExternalTlutColor(m_tlutData, GetNumTlut(), index);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 76b
 * EN Address: 0x80045C14
 * EN Size: 108b
 * JP Address: TODO
 * JP Size: TODO
 */
inline _GXColor CTexture::GetExternalTlutColor(void* tlutData, int tlutOffset, int index)
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
 * EN Address: 0x80045C80
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::SetTlutColor(int index, _GXColor color)
{
    SetExternalTlutColor(m_tlutData, GetNumTlut(), index, color);
}

/*
 * --INFO--
 * PAL Address: 0x8003AE30
 * PAL Size: 72b
 * EN Address: 0x80045CCC
 * EN Size: 84b
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
 * PAL Size: 88b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CTexture::CopyTlut(_GXColor* colors)
{
    int numEntries = (m_format == GX_TF_C8) ? kTextureC8TlutEntries : kTextureC4TlutEntries;

    for (int i = 0; i < numEntries; i++) {
        colors[i] = GetTlutColor(i);
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003ADE0
 * PAL Size: 80b
 * EN Address: 0x80045D20
 * EN Size: 60b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::FlushTlut()
{
    int numEntries = GetNumTlut();
    DCFlushRange(m_tlutData, numEntries << 2);
}

/*
 * --INFO--
 * PAL Address: 0x8003AD90
 * PAL Size: 80b
 * EN Address: 0x80045D5C
 * EN Size: 56b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::FlushExternalTlut(void* tlutData)
{
    int numEntries = GetNumTlut();
    DCFlushRange(tlutData, numEntries << 2);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 36b
 * EN Address: 0x80045D94
 * EN Size: 52b
 * JP Address: TODO
 * JP Size: TODO
 */
inline void CTexture::FlushExternalTlut(void* tlutData, int format)
{
    int numEntries = TextureTlutEntryCount(format);
    DCFlushRange(tlutData, numEntries << 2);
}

/*
 * --INFO--
 * PAL Address: 0x8003AD30
 * PAL Size: 96b
 * EN Address: 0x80045DC8
 * EN Size: 100b
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
 * PAL Address: 0x8003AD7C
 * PAL Size: 132b
 * EN Address: 0x80045E2C
 * EN Size: 120b
 * JP Address: TODO
 * JP Size: TODO
 */
CTextureSet::~CTextureSet()
{
    m_textureArray.ReleaseAndRemoveAll();
}

/*
 * --INFO--
 * PAL Address: 0x8003AC74
 * PAL Size: 68b
 * EN Address: 0x80045EA4
 * EN Size: 76b
 * JP Address: TODO
 * JP Size: TODO
 */
void* CTextureSet::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, TextureMan.m_memoryStage, file, line, 0);
}

/*
 * --INFO--
 * PAL Address: 0x8003A9AC
 * PAL Size: 712b
 * EN Address: 0x80045EF0
 * EN Size: 316b
 * JP Address: TODO
 * JP Size: TODO
 */
void CTextureSet::Create(void* filePtr, CMemory::CStage* stage, int append, CAmemCacheSet* amemCacheSet, int cacheTag, int useAddress)
{
    CChunkFile::CChunk chunk;
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
                        Create(chunkFile, stage, append, amemCacheSet, cacheTag, useAddress);
                    }
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x8003A77C
 * PAL Size: 560b
 * EN Address: 0x8004602C
 * EN Size: 424b
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
            texture = new (stage, "textureman.cpp", 0x2ED) CTexture;
            texture->Create(chunkFile, stage, amemCacheSet, cacheTag, useAddress);

            if (texture->m_name[0] != 0) {
                unsigned int duplicateIdx = static_cast<unsigned int>(Find(texture->m_name));
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
 * PAL Address: 0x8003A6F0
 * PAL Size: 140b
 * EN Address: 0x800461D4
 * EN Size: 144b
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
 * PAL Address: 0x8003A5FC
 * PAL Size: 244b
 * EN Address: 0x80046264
 * EN Size: 256b
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
