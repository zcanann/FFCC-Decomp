#include "ffcc/textureman.h"
#include "ffcc/system.h"

#include <string.h>

CTextureMan TextureMan;
extern CMemory Memory;
extern CSystem System;

template <class T>
class CPtrArray
{
public:
    void** m_vtable;
    int m_size;
    int m_numItems;
    int m_defaultSize;
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
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" void* lbl_801E9BA0[];
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

static char s_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error[] = "CPtrArray grow error";

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
    m_vtable = lbl_801E9BA0;
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
        ptrArray->m_vtable = lbl_801E9BA0;
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
    if (setSize(m_numItems + 1) != 0) {
        m_items[m_numItems] = item;
        m_numItems = m_numItems + 1;
        return true;
    }
    return false;
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
    return m_size;
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
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (CTexture**)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
            &Memory, (unsigned long)(m_size << 2), m_stage, s_collection_ptrarray_h, 0xFA, 0);
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
 * Address:	TODO
 * Size:	TODO
 */
void CTextureMan::SetTexture(_GXTexMapID, CTexture*)
{
	// TODO
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
    GXColorS10 tevColor1;
    GXColorS10 tevColor2;
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
        tevColor1.r = -1;
        tevColor1.g = 0;
        tevColor1.b = 0;
        tevColor1.a = -1;
        GXSetTevColorS10((GXTevRegID)1, tevColor1);

        tevColor2.r = 0;
        tevColor2.g = 0;
        tevColor2.b = 0;
        tevColor2.a = -1;
        GXSetTevColorS10((GXTevRegID)2, tevColor2);

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
 * Address:	TODO
 * Size:	TODO
 */
CTexture::CTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTexture::~CTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::InitTexObj()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::Create(CChunkFile&, CMemory::CStage*, CAmemCacheSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheLoadTexture(CAmemCacheSet*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CacheUnLoadTexture(CAmemCacheSet*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::CheckName(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::SetExternalTlut(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::GetTlutColor(int)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::SetTlutColor(int, _GXColor)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::SetExternalTlutColor(void*, int, int, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::FlushTlut()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTexture::FlushExternalTlut(void*)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
CTextureSet::CTextureSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CTextureSet::~CTextureSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::Create(void*, CMemory::CStage*, int, CAmemCacheSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::Create(CChunkFile&, CMemory::CStage*, int, CAmemCacheSet*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::Find(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CTextureSet::ReleaseTextureIdx(int, CAmemCacheSet*)
{
	// TODO
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
	return ::operator new(size, TextureMan.m_memoryStage, file, line);
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
	return ::operator new(size, TextureMan.m_memoryStage, file, line);
}
