#include "ffcc/textureman.h"
#include "ffcc/chunkfile.h"
#include "ffcc/system.h"

#include <string.h>

CTextureMan TextureMan;

template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    unsigned long m_numItems;
    unsigned long m_size;
    unsigned long m_defaultSize;
    T* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;

    CPtrArray();
    ~CPtrArray();

    bool Add(T item);
    void SetAt(unsigned long index, T item);
    int GetSize();
    void RemoveAll();
    void ReleaseAndRemoveAll();
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    void SetDefaultSize(unsigned long defaultSize);
    int setSize(unsigned long newSize);
    T GetAt(unsigned long index);
};

extern "C" void __dl__FPv(void*);
extern "C" void __dla__FPv(void*);
extern "C" void __ct__4CRefFv(void*);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* __vt__8CPtrArrayIP8CTexture[];
extern "C" void* __vt__8CTexture[];
extern "C" void* __vt__11CTextureSet[];
extern "C" void _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(int, int, int, int);
extern "C" void _GXSetTevOp__F13_GXTevStageID10_GXTevMode(int, int);
extern "C" void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
    int, int, int, int, int);
extern "C" void _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(
    int, int, int, int, int);
extern "C" void _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int,
                                                                                                       int, int);
extern "C" void _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(int, int, int);
extern "C" void _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(
    int, int, int, int, int);
extern "C" void _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(int, int, int, int,
                                                                                                       int, int);
extern "C" unsigned short SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi(CAmemCacheSet*, void*, int, CAmemCache::TYPE,
                                                                             int);
extern "C" unsigned int IsEnable__13CAmemCacheSetFs(CAmemCacheSet*, short);
extern "C" int GetData__13CAmemCacheSetFsPci(CAmemCacheSet*, short, char*, int);
extern "C" void AddRef__13CAmemCacheSetFs(CAmemCacheSet*, short);
extern "C" void __ct__21CPtrArray_P8CTexture_Fv(void*);
extern "C" void __dt__21CPtrArray_P8CTexture_Fv(void*, int);
extern "C" void SetDefaultSize__21CPtrArray_P8CTexture_FUl(void*, unsigned long);
extern "C" void SetStage__21CPtrArray_P8CTexture_FPQ27CMemory6CStage(void*, CMemory::CStage*);
extern "C" void ReleaseAndRemoveAll__21CPtrArray_P8CTexture_Fv(void*);

static char s_ptrarray_grow_error_801D79D8[] = "CPtrArray grow error";
static char s_collection_ptrarray_h_801D79F4[] = "collection_ptrarray.h";
static char s_textureman_cpp[] = "textureman.cpp";
static char s_error_width_height[] = "Error width %d, height %d\n";

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline CPtrArray<CTexture*>* Textures(CTextureSet* textureSet)
{
    return reinterpret_cast<CPtrArray<CTexture*>*>(Ptr(textureSet, 8));
}

static inline unsigned char& U8At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned char*>(Ptr(p, offset));
}

static inline unsigned short& U16At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned short*>(Ptr(p, offset));
}

static inline short& S16At(void* p, unsigned int offset)
{
    return *reinterpret_cast<short*>(Ptr(p, offset));
}

static inline unsigned int& U32At(void* p, unsigned int offset)
{
    return *reinterpret_cast<unsigned int*>(Ptr(p, offset));
}

static inline void*& PtrAt(void* p, unsigned int offset)
{
    return *reinterpret_cast<void**>(Ptr(p, offset));
}

static inline CTexture* AllocTexture()
{
    CTexture* texture = static_cast<CTexture*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
        &Memory,
        0x80,
        *reinterpret_cast<CMemory::CStage**>(Ptr(&TextureMan, 4)),
        s_textureman_cpp,
        0x2ED,
        0));
    if (texture != 0) {
        __ct__4CRefFv(texture);
        *reinterpret_cast<void**>(texture) = __vt__8CTexture;
        texture->m_maxLod = 0;
        texture->m_imageData = 0;
        texture->m_tlutData = 0;
        texture->m_isIntensityAlpha = 0;
        texture->m_isAlphaLut = 0;
        texture->m_name[0] = 0;
        texture->m_cacheId = -1;
        texture->m_usesExternalAddress = 0;
    }
    return texture;
}
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
    m_vtable = __vt__8CPtrArrayIP8CTexture;
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
    m_vtable = __vt__8CPtrArrayIP8CTexture;
    RemoveAll();
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
extern "C" CPtrArray<CTexture*>* dtor_8003BE70(CPtrArray<CTexture*>* ptrArray, short param_2)
{
    if (ptrArray != 0) {
        ptrArray->m_vtable = __vt__8CPtrArrayIP8CTexture;
        ptrArray->RemoveAll();
        if (0 < param_2) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
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
    int* numItems = reinterpret_cast<int*>(Ptr(this, 4));
    CTexture*** items = reinterpret_cast<CTexture***>(Ptr(this, 0x10));

    if (setSize(*numItems + 1) == 0) {
        return false;
    }

    (*items)[*numItems] = item;
    *numItems = *numItems + 1;
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
        __dla__FPv(m_items);
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
    int offset = 0;

    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        int* item = *(int**)((int)m_items + offset);
        if (item != 0) {
            int refCount = item[1];
            item[1] = refCount - 1;
            if ((refCount - 1 == 0) && (item != 0)) {
                (*(void (**)(int*, int))(*item + 8))(item, 1);
            }
            *(unsigned int*)((int)m_items + offset) = 0;
        }
        offset += 4;
    }

    if (m_items != 0) {
        __dla__FPv(m_items);
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
                System.Printf(s_ptrarray_grow_error_801D79D8);
            }
            m_size = m_size << 1;
        }

        newItems = (CTexture**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, (unsigned long)(m_size << 2), m_stage, s_collection_ptrarray_h_801D79F4, 0xFA, 0);
        if (newItems == 0) {
            return 0;
        }

        if (m_items != 0) {
            memcpy(newItems, m_items, m_numItems << 2);
        }
        if (m_items != 0) {
            __dla__FPv(m_items);
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
	m_memoryStage = Memory.CreateStage(0x40000, (char*)"CTexture.texture", 0);
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
 * PAL Address: 0x8003BD10
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CTextureMan::SetTexture(_GXTexMapID texMapId, CTexture* texture)
{
    bool usePalette;

    usePalette = false;
    if ((U8At(texture, 0x60) == 9) || (U8At(texture, 0x60) == 8)) {
        usePalette = true;
    }

    if (usePalette) {
        GXInitTexObjTlut(reinterpret_cast<GXTexObj*>(Ptr(texture, 0x28)), GX_TLUT0);
    }

    GXLoadTexObj(reinterpret_cast<GXTexObj*>(Ptr(texture, 0x28)), texMapId);

    if (usePalette) {
        GXInitTexObjTlut(reinterpret_cast<GXTexObj*>(Ptr(texture, 0x28)), GX_TLUT1);
        GXLoadTexObj(reinterpret_cast<GXTexObj*>(Ptr(texture, 0x28)), static_cast<_GXTexMapID>(texMapId + 1));
        GXLoadTlut(reinterpret_cast<GXTlutObj*>(Ptr(texture, 0x48)), GX_TLUT0);
        GXLoadTlut(reinterpret_cast<GXTlutObj*>(Ptr(texture, 0x54)), GX_TLUT1);
    }

    return 0;
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
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0xFF, 0xFF, 4);
        _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 4);
        return 1;
    }

    usePalette = *(u8*)((u8*)texture + 0x60) == 9 || *(u8*)((u8*)texture + 0x60) == 8;
    if (usePalette) {
        GXColor tevColor1 = {0xFF, 0, 0, 0xFF};
        GXSetTevColor((GXTevRegID)1, tevColor1);

        GXColor tevColor2 = {0, 0, 0, 0xFF};
        GXSetTevColor((GXTevRegID)2, tevColor2);

        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
            0, 0, 1, 2, 3);
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
            1, 0, 3, 3, 3);
        _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
            2, 2, 2, 2, 3);

        GXSetTevKAlphaSel(GX_TEVSTAGE0, GX_TEV_KASEL_1);
        GXSetTevKAlphaSel(GX_TEVSTAGE1, GX_TEV_KASEL_1);
        GXSetTevKAlphaSel(GX_TEVSTAGE2, GX_TEV_KASEL_1);

        GXSetNumTevStages(3);
        GXSetTevDirect(GX_TEVSTAGE0);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(0, 0xF, 8,
                                                                                                              2, 0xF);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(0, 0, 0, 0, 0, 0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 1);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 0xFF);

        GXSetTevDirect(GX_TEVSTAGE1);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(1, 0xF, 8,
                                                                                                              4, 0);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(1, 7, 6,
                                                                                                              4, 7);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(1, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(1, 0, 2);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(1, 0, 1, 0xFF);

        GXSetTevDirect(GX_TEVSTAGE2);
        _GXSetTevColorIn__F13_GXTevStageID14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg14_GXTevColorArg(2, 0xF, 0,
                                                                                                              10, 0xF);
        _GXSetTevAlphaIn__F13_GXTevStageID14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg14_GXTevAlphaArg(2, 7, 0,
                                                                                                              5, 7);
        _GXSetTevColorOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
        _GXSetTevAlphaOp__F13_GXTevStageID8_GXTevOp10_GXTevBias11_GXTevScaleUc11_GXTevRegID(2, 0, 0, 0, 1, 0);
        _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(2, 0, 0);
        _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(2, 0xFF, 0xFF, 4);
        return 3;
    }

    GXSetNumTevStages(1);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOp__F13_GXTevStageID10_GXTevMode(0, 0);
    _GXSetTevOrder__F13_GXTevStageID13_GXTexCoordID11_GXTexMapID12_GXChannelID(0, 0, 0, 4);
    _GXSetTevSwapMode__F13_GXTevStageID13_GXTevSwapSel13_GXTevSwapSel(0, 0, 0);
    return 1;
}

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
    __ct__4CRefFv(this);
    *reinterpret_cast<void**>(this) = __vt__8CTexture;
    m_maxLod = 0;
    m_imageData = 0;
    m_tlutData = 0;
    m_isIntensityAlpha = 0;
    m_isAlphaLut = 0;
    m_name[0] = 0;
    m_cacheId = -1;
    m_usesExternalAddress = 0;
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
extern "C" CTexture* __dt__8CTextureFv(CTexture* texture, short shouldDelete)
{
    if (texture != 0) {
        *reinterpret_cast<void**>(texture) = __vt__8CTexture;
        if (texture->m_usesExternalAddress == 0) {
            if (texture->m_imageData != 0) {
                __dla__FPv(texture->m_imageData);
                texture->m_imageData = 0;
            }
            if (texture->m_tlutData != 0) {
                __dla__FPv(texture->m_tlutData);
                texture->m_tlutData = 0;
            }
        } else {
            texture->m_imageData = 0;
            texture->m_tlutData = 0;
        }
        __dt__4CRefFv(texture, 0);
        if (shouldDelete > 0) {
            __dl__FPv(texture);
        }
    }
    return texture;
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
    const int format = m_format;
    if ((format == 9) || (format == 8)) {
        GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height), static_cast<GXCITexFmt>(format),
                       static_cast<GXTexWrapMode>(m_wrapMode), static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);

        int numEntries = 0x10;
        if (m_format == 9) {
            numEntries = 0x100;
        }

        GXInitTlutObj(&m_tlutObj0, m_tlutData, GX_TL_IA8, static_cast<u16>(numEntries));
        GXInitTlutObj(&m_tlutObj1, Ptr(m_tlutData, numEntries * 2), GX_TL_IA8, static_cast<u16>(numEntries));
    } else {
        GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height), static_cast<GXTexFmt>(format),
                     static_cast<GXTexWrapMode>(m_wrapMode), static_cast<GXTexWrapMode>(m_wrapMode), 1 - (m_maxLod >> 31));
    }

    const unsigned char maxLod = m_maxLod;
    if (maxLod >= 2) {
        GXInitTexObjLOD(&m_texObj, GX_LINEAR, GX_LINEAR, 0.0f, static_cast<float>(maxLod - 1), 0.0f, GX_FALSE, GX_FALSE,
                        GX_ANISO_1);
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
    unsigned char* texture = reinterpret_cast<unsigned char*>(this);
    unsigned int width;
    unsigned int height;
    int format;

    *reinterpret_cast<unsigned int*>(texture + 0x6C) = 1;
    *reinterpret_cast<unsigned int*>(texture + 0x60) = 6;
    texture[0x71] = 0;
    texture[0x75] = static_cast<unsigned char>(useAddress);

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 0x4E414D45:
            strcpy(reinterpret_cast<char*>(texture + 0x08), chunkFile.GetString());
            break;
        case 0x494D4147:
            if (amemCacheSet != 0) {
                void* data = _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, chunk.m_size, stage, s_textureman_cpp, 0x150, 0);
                chunkFile.Get(data, chunk.m_size);
                *reinterpret_cast<short*>(texture + 0x72) = SetData__13CAmemCacheSetFPviQ210CAmemCache4TYPEi(
                    amemCacheSet, data, chunk.m_size, static_cast<CAmemCache::TYPE>(0), cacheTag);
                __dl__FPv(data);
                *reinterpret_cast<void**>(texture + 0x78) = 0;
            } else {
                if (texture[0x75] != 0) {
                    *reinterpret_cast<void**>(texture + 0x78) = chunkFile.GetAddress();
                } else {
                    *reinterpret_cast<void**>(texture + 0x78) =
                        _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, chunk.m_size, stage, s_textureman_cpp, 0x15C, 0);
                    chunkFile.Get(*reinterpret_cast<void**>(texture + 0x78), chunk.m_size);
                }
                DCFlushRange(*reinterpret_cast<void**>(texture + 0x78), chunk.m_size);
                *reinterpret_cast<short*>(texture + 0x72) = -1;
            }
            break;
        case 0x464D5420: {
            unsigned char chunkFormat = chunkFile.Get1();

            switch (chunkFormat) {
            case 0:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 6;
                break;
            case 1:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 4;
                break;
            case 2:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 9;
                break;
            case 3:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 8;
                break;
            case 5:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 0;
                break;
            case 6:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 0xE;
                break;
            case 7:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 3;
                texture[0x70] = 1;
                break;
            case 8:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 3;
                break;
            case 9:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 1;
                break;
            case 10:
                *reinterpret_cast<unsigned int*>(texture + 0x60) = 0xE;
                texture[0x71] = 1;
                break;
            }

            texture[0x74] = chunkFile.Get1();
            chunkFormat = chunkFile.Get1();
            if (chunk.m_arg0 > 3) {
                *reinterpret_cast<unsigned int*>(texture + 0x6C) = chunkFormat;
            }
            break;
        }
        case 0x53495A45:
            *reinterpret_cast<unsigned int*>(texture + 0x64) = chunkFile.Get4();
            *reinterpret_cast<unsigned int*>(texture + 0x68) = chunkFile.Get4();
            if ((*reinterpret_cast<unsigned int*>(texture + 0x64) == 0) || (*reinterpret_cast<unsigned int*>(texture + 0x68) == 0)) {
                System.Printf(s_error_width_height, *reinterpret_cast<unsigned int*>(texture + 0x64),
                              *reinterpret_cast<unsigned int*>(texture + 0x68));
                chunkFile.PopChunk();
                return;
            }
            break;
        case 0x50414C54:
            if (texture[0x75] != 0) {
                *reinterpret_cast<void**>(texture + 0x7C) = chunkFile.GetAddress();
            } else {
                *reinterpret_cast<void**>(texture + 0x7C) =
                    _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, chunk.m_size, stage, s_textureman_cpp, 0x178, 0);
                chunkFile.Get(*reinterpret_cast<void**>(texture + 0x7C), chunk.m_size);
            }
            DCFlushRange(*reinterpret_cast<void**>(texture + 0x7C), chunk.m_size);
            break;
        }
    }
    chunkFile.PopChunk();

    width = *reinterpret_cast<unsigned int*>(texture + 0x64);
    while ((width & 1) == 0) {
        width >>= 1;
    }
    height = *reinterpret_cast<unsigned int*>(texture + 0x68);
    while ((height & 1) == 0) {
        height >>= 1;
    }
    if ((width != 1) || (height != 1)) {
        *reinterpret_cast<unsigned int*>(texture + 0x6C) = 0;
    }
    if (*reinterpret_cast<short*>(texture + 0x72) != -1) {
        return;
    }

    format = *reinterpret_cast<unsigned int*>(texture + 0x60);
    if ((format == 9) || (format == 8)) {
        int tlutBase;
        unsigned int numEntries;
        int offset;

        GXInitTexObjCI(reinterpret_cast<GXTexObj*>(texture + 0x28), *reinterpret_cast<void**>(texture + 0x78),
                       *reinterpret_cast<unsigned int*>(texture + 0x64) & 0xFFFF, *reinterpret_cast<unsigned int*>(texture + 0x68) & 0xFFFF,
                       static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(*reinterpret_cast<unsigned int*>(texture + 0x6C)),
                       static_cast<GXTexWrapMode>(*reinterpret_cast<unsigned int*>(texture + 0x6C)), 0, 0);

        tlutBase = reinterpret_cast<int>(*reinterpret_cast<void**>(texture + 0x7C));
        numEntries = 0x10;
        if (*reinterpret_cast<unsigned int*>(texture + 0x60) == 9) {
            numEntries = 0x100;
        }
        GXInitTlutObj(reinterpret_cast<GXTlutObj*>(texture + 0x48), reinterpret_cast<void*>(tlutBase), GX_TL_IA8,
                      static_cast<u16>(numEntries));

        numEntries = 0x10;
        if (*reinterpret_cast<unsigned int*>(texture + 0x60) == 9) {
            numEntries = 0x100;
        }
        offset = 0x10;
        if (*reinterpret_cast<unsigned int*>(texture + 0x60) == 9) {
            offset = 0x100;
        }
        GXInitTlutObj(reinterpret_cast<GXTlutObj*>(texture + 0x54), reinterpret_cast<void*>(tlutBase + offset * 2), GX_TL_IA8,
                      static_cast<u16>(numEntries));
    } else {
        GXInitTexObj(reinterpret_cast<GXTexObj*>(texture + 0x28), *reinterpret_cast<void**>(texture + 0x78),
                     *reinterpret_cast<unsigned int*>(texture + 0x64) & 0xFFFF, *reinterpret_cast<unsigned int*>(texture + 0x68) & 0xFFFF,
                     static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(*reinterpret_cast<unsigned int*>(texture + 0x6C)),
                     static_cast<GXTexWrapMode>(*reinterpret_cast<unsigned int*>(texture + 0x6C)), 1 - (texture[0x74] >> 31));
    }

    if (texture[0x74] >= 2) {
        GXInitTexObjLOD(reinterpret_cast<GXTexObj*>(texture + 0x28), GX_LINEAR, GX_LINEAR, 0.0f,
                        static_cast<float>(texture[0x74] - 1), 0.0f, GX_FALSE, GX_FALSE, GX_ANISO_1);
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
        if (IsEnable__13CAmemCacheSetFs(amemCacheSet, m_cacheId) == 0) {
            m_imageData = reinterpret_cast<void*>(GetData__13CAmemCacheSetFsPci(amemCacheSet, m_cacheId, s_textureman_cpp, 0x1DD));

            const int format = m_format;
            if ((format == 9) || (format == 8)) {
                GXInitTexObjCI(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                               static_cast<GXCITexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                               static_cast<GXTexWrapMode>(m_wrapMode), 0, 0);

                unsigned int numEntries = 0x10;
                if (m_format == 9) {
                    numEntries = 0x100;
                }
                GXInitTlutObj(&m_tlutObj0, m_tlutData, GX_TL_IA8, static_cast<u16>(numEntries));

                numEntries = 0x10;
                if (m_format == 9) {
                    numEntries = 0x100;
                }
                int offset = 0x10;
                if (m_format == 9) {
                    offset = 0x100;
                }
                GXInitTlutObj(&m_tlutObj1, Ptr(m_tlutData, offset * 2), GX_TL_IA8, static_cast<u16>(numEntries));
            } else {
                GXInitTexObj(&m_texObj, m_imageData, static_cast<u16>(m_width), static_cast<u16>(m_height),
                             static_cast<GXTexFmt>(format), static_cast<GXTexWrapMode>(m_wrapMode),
                             static_cast<GXTexWrapMode>(m_wrapMode), 1 - (m_maxLod >> 31));
            }

            const unsigned char maxLod = m_maxLod;
            if (maxLod >= 2) {
                GXInitTexObjLOD(&m_texObj, GX_LINEAR, GX_LINEAR, 0.0f, static_cast<float>(maxLod - 1), 0.0f, GX_FALSE,
                                GX_FALSE, GX_ANISO_1);
            }
        }
        AddRef__13CAmemCacheSetFs(amemCacheSet, m_cacheId);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheUnLoadTexture(CAmemCacheSet* amemCacheSet)
{
    if (m_cacheId != -1) {
        amemCacheSet->Release(m_cacheId);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheRefCnt0UpTexture(CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheDumpTexture(CAmemCacheSet*)
{
	// TODO
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
 * PAL Address: 0x8003AF64
 * PAL Size: 204b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CTexture::SetExternalTlut(void* tlutData, int loadToGX)
{
    int tlutBase;
    unsigned int numEntries;
    int offset;

    if (tlutData == 0) {
        tlutData = m_tlutData;
    }

    tlutBase = reinterpret_cast<int>(tlutData);
    numEntries = 0x10;
    if (m_format == 9) {
        numEntries = 0x100;
    }

    GXInitTlutObj(&m_tlutObj0, reinterpret_cast<void*>(tlutBase), GX_TL_IA8, static_cast<u16>(numEntries));

    numEntries = 0x10;
    if (m_format == 9) {
        numEntries = 0x100;
    }
    offset = 0x10;
    if (m_format == 9) {
        offset = 0x100;
    }
    GXInitTlutObj(&m_tlutObj1, reinterpret_cast<void*>(tlutBase + offset * 2), GX_TL_IA8, static_cast<u16>(numEntries));

    if (loadToGX != 0) {
        GXLoadTlut(&m_tlutObj0, GX_TLUT0);
        GXLoadTlut(&m_tlutObj1, GX_TLUT1);
    }
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
    unsigned short* tlut = reinterpret_cast<unsigned short*>(m_tlutData);
    unsigned short color0;
    unsigned short color1;
    _GXColor color;

    if (format == 9) {
        offset = 0x100;
    } else if (format == 8) {
        offset = 0x10;
    } else {
        offset = 0;
    }

    color1 = tlut[index + offset];
    color0 = tlut[index];
    color.r = static_cast<unsigned char>(color0);
    color.g = static_cast<unsigned char>(color0 >> 8);
    color.b = static_cast<unsigned char>(color1);
    color.a = static_cast<unsigned char>(color1 >> 8);
    return color;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::GetExternalTlutColor(void*, int, int)
{
	// TODO
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
    int offset;
    u16* tlut = reinterpret_cast<u16*>(m_tlutData);
    union {
        _GXColor color;
        u32 value;
    } packedColor;

    if (m_format == 9) {
        offset = 0x100;
    } else if (m_format == 8) {
        offset = 0x10;
    } else {
        offset = 0;
    }

    packedColor.color = color;
    tlut[index + offset] = static_cast<u16>(packedColor.value >> 16);
    tlut[index] = static_cast<u16>(packedColor.value);
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
    U16At(tlutData, (index + tlutOffset) * 2) = static_cast<unsigned short>(packedColor >> 16);
    U16At(tlutData, index * 2) = static_cast<unsigned short>(packedColor);
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
    int numEntries = 0;
    if (m_format == 9) {
        numEntries = 0x100;
    } else if (m_format == 8) {
        numEntries = 0x10;
    }
    DCFlushRange(m_tlutData, static_cast<unsigned int>(numEntries << 2));
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
    int numEntries = 0;
    if (m_format == 9) {
        numEntries = 0x100;
    } else if (m_format == 8) {
        numEntries = 0x10;
    }
    DCFlushRange(tlutData, static_cast<unsigned int>(numEntries << 2));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::FlushExternalTlut(void*, int)
{
	// TODO
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
    __ct__4CRefFv(this);
    *reinterpret_cast<void**>(this) = __vt__11CTextureSet;
    __ct__21CPtrArray_P8CTexture_Fv(Textures(this));
    SetDefaultSize__21CPtrArray_P8CTexture_FUl(Textures(this), 0x10);
    SetStage__21CPtrArray_P8CTexture_FPQ27CMemory6CStage(Textures(this), TextureMan.m_memoryStage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
extern "C" CTextureSet* __dt__11CTextureSetFv(CTextureSet* textureSet, short shouldDelete)
{
    if (textureSet != 0) {
        *reinterpret_cast<void**>(textureSet) = __vt__11CTextureSet;
        ReleaseAndRemoveAll__21CPtrArray_P8CTexture_Fv(Textures(textureSet));
        __dt__21CPtrArray_P8CTexture_Fv(Textures(textureSet), -1);
        __dt__4CRefFv(textureSet, 0);
        if (shouldDelete > 0) {
            __dl__FPv(textureSet);
        }
    }

    return textureSet;
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
                            Textures(this)->ReleaseAndRemoveAll();
                        }

                        chunkFile.PushChunk();
                        while (chunkFile.GetNextChunk(chunk)) {
                            if (chunk.m_id == 0x54585452) {
                                CTexture* texture = static_cast<CTexture*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
                                    &Memory,
                                    0x80,
                                    *reinterpret_cast<CMemory::CStage**>(Ptr(&TextureMan, 4)),
                                    s_textureman_cpp,
                                    0x2ED,
                                    0));
                                if (texture != 0) {
                                    __ct__4CRefFv(texture);
                                    *reinterpret_cast<void**>(texture) = __vt__8CTexture;
                                    U8At(texture, 0x74) = 0;
                                    PtrAt(texture, 0x78) = 0;
                                    PtrAt(texture, 0x7C) = 0;
                                    U8At(texture, 0x70) = 0;
                                    U8At(texture, 0x71) = 0;
                                    U8At(texture, 0x08) = 0;
                                    S16At(texture, 0x72) = -1;
                                    U8At(texture, 0x75) = 0;
                                }
                                texture->Create(chunkFile, stage, amemCacheSet, cacheTag, useAddress);

                                if (*reinterpret_cast<unsigned char*>(Ptr(texture, 8)) != 0) {
                                    unsigned int duplicateIdx;
                                    for (duplicateIdx = 0; duplicateIdx < (unsigned int)Textures(this)->GetSize(); duplicateIdx++) {
                                        CTexture* existing = (*Textures(this))[duplicateIdx];
                                        if ((existing != 0)
                                            && (strcmp(reinterpret_cast<char*>(Ptr(existing, 8)), reinterpret_cast<char*>(Ptr(texture, 8)))
                                                == 0)) {
                                            goto found_duplicate;
                                        }
                                    }
                                    duplicateIdx = 0xFFFFFFFF;

                                found_duplicate:
                                    if ((int)duplicateIdx >= 0) {
                                        if (amemCacheSet != 0) {
                                            amemCacheSet->DestroyCache(static_cast<int>(*reinterpret_cast<short*>(Ptr(texture, 0x72))));
                                            amemCacheSet->AmemPrev();
                                        }

                                        int* refObj = reinterpret_cast<int*>(texture);
                                        int refCount = refObj[1] - 1;
                                        refObj[1] = refCount;
                                        if ((refCount == 0) && (refObj != 0)) {
                                            (*reinterpret_cast<void (**)(int*, int)>(*refObj + 8))(refObj, 1);
                                        }

                                        texture = (*Textures(this))[duplicateIdx];
                                        *reinterpret_cast<int*>(Ptr(texture, 4)) = *reinterpret_cast<int*>(Ptr(texture, 4)) + 1;
                                    }
                                }

                                if (append != 0) {
                                    for (unsigned long i = 0; i < static_cast<unsigned long>(Textures(this)->GetSize()); i++) {
                                        if ((*Textures(this))[i] == 0) {
                                            Textures(this)->SetAt(i, texture);
                                            goto next_texture;
                                        }
                                    }
                                }

                                Textures(this)->Add(texture);
                            }
                        next_texture:;
                        }
                        chunkFile.PopChunk();
                    }
                }
                chunkFile.PopChunk();
            }
        }
        chunkFile.PopChunk();
    }
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
    CPtrArray<CTexture*>& textures = *Textures(this);

    if (append == 0) {
        textures.ReleaseAndRemoveAll();
    }

    chunkFile.PushChunk();
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id != 0x54585452) {
            continue;
        }

        texture = static_cast<CTexture*>(_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory,
            0x80,
            *reinterpret_cast<CMemory::CStage**>(Ptr(&TextureMan, 4)),
            s_textureman_cpp,
            0x2ED,
            0));
        if (texture != 0) {
            __ct__4CRefFv(texture);
            *reinterpret_cast<void**>(texture) = __vt__8CTexture;
            U8At(texture, 0x74) = 0;
            PtrAt(texture, 0x78) = 0;
            PtrAt(texture, 0x7C) = 0;
            U8At(texture, 0x70) = 0;
            U8At(texture, 0x71) = 0;
            U8At(texture, 0x08) = 0;
            S16At(texture, 0x72) = -1;
            U8At(texture, 0x75) = 0;
        }
        texture->Create(chunkFile, stage, amemCacheSet, cacheTag, useAddress);

        if (*reinterpret_cast<unsigned char*>(Ptr(texture, 8)) != 0) {
            unsigned int duplicateIdx;
            for (duplicateIdx = 0; duplicateIdx < (unsigned int)textures.GetSize(); duplicateIdx++) {
                CTexture* existing = textures[duplicateIdx];
                if ((existing != 0)
                    && (strcmp(reinterpret_cast<char*>(Ptr(existing, 8)), reinterpret_cast<char*>(Ptr(texture, 8))) == 0)) {
                    goto found_duplicate;
                }
            }
            duplicateIdx = 0xFFFFFFFF;

        found_duplicate:
            if ((int)duplicateIdx >= 0) {
                if (amemCacheSet != 0) {
                    amemCacheSet->DestroyCache((int)*reinterpret_cast<short*>(Ptr(texture, 0x72)));
                    amemCacheSet->AmemPrev();
                }

                int* refObj = reinterpret_cast<int*>(texture);
                int refCount = refObj[1] - 1;
                refObj[1] = refCount;
                if ((refCount == 0) && (refObj != 0)) {
                    (*reinterpret_cast<void (**)(int*, int)>(*refObj + 8))(refObj, 1);
                }

                texture = textures[duplicateIdx];
                *reinterpret_cast<int*>(Ptr(texture, 4)) = *reinterpret_cast<int*>(Ptr(texture, 4)) + 1;
            }
        }

        if (append != 0) {
            for (unsigned int i = 0; i < (unsigned int)textures.GetSize(); i++) {
                if (textures[i] == 0) {
                    textures.SetAt(i, texture);
                    goto next_chunk;
                }
            }
        }

        textures.Add(texture);
    next_chunk:;
    }
    chunkFile.PopChunk();
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
    for (unsigned long i = 0; i < static_cast<unsigned long>(Textures(this)->GetSize()); i++) {
        CTexture* texture = (*Textures(this))[i];
        if ((texture != 0) && (strcmp(reinterpret_cast<char*>(Ptr(texture, 8)), name) == 0)) {
            return static_cast<int>(i);
        }
    }
    return -1;
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
    CTexture* texture = (*Textures(this))[static_cast<unsigned long>(idx)];
    if (texture == 0) {
        return;
    }

    if ((S16At(texture, 0x72) != -1) && (*reinterpret_cast<int*>(Ptr(texture, 4)) < 2)) {
        amemCacheSet->DestroyCache(static_cast<int>(S16At(texture, 0x72)));
        PtrAt(texture, 0x78) = 0;
    }

    int* refObj = reinterpret_cast<int*>(texture);
    int refCount = refObj[1] - 1;
    refObj[1] = refCount;
    if ((refCount == 0) && (refObj != 0)) {
        (*reinterpret_cast<void (**)(int*, int)>(*refObj + 8))(refObj, 1);
    }

    Textures(this)->SetAt(static_cast<unsigned long>(idx), 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::GetNumTlut()
{
	// TODO
}

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
    return _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, size, TextureMan.m_memoryStage, file, line, 0);
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
    return _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, size, TextureMan.m_memoryStage, file, line, 0);
}
