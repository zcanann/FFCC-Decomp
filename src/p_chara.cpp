#include "ffcc/p_chara.h"
#include "ffcc/chunkfile.h"
#include "ffcc/graphic.h"
#include "ffcc/linkage.h"
#include "ffcc/memory.h"
#include "ffcc/partMng.h"
#include "ffcc/p_light.h"
#include "ffcc/p_tina.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/textureman.h"
extern "C" {
extern u8* gCharaPartWorkPtr;
}

#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CCharaPcs CharaPcs;

extern "C" {
u8* gCharaPartWorkPtr = 0;
}

extern "C" void __dla__FPv(void*);
extern "C" void __dl__FPv(void*);
extern "C" int __cntlzw(unsigned int);
extern "C" void* __nw__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void* __nwa__FUlPQ27CMemory6CStagePci(unsigned long, CMemory::CStage*, char*, int);
extern "C" void __dt__4CRefFv(void*, int);
extern "C" void __dt__Q29CCharaPcs7CHandleFv(void*, int);
extern "C" void ReleasePdt__8CPartPcsFi(void*, int);
extern "C" void* _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(CMemory*, unsigned long, CMemory::CStage*, char*, int, int);
extern "C" CMemory::CStage* CreateStage__7CMemoryFUlPci(CMemory*, unsigned long, const char*, int);
extern "C" void CopyFromAMemorySync__7CMemoryFPvPvUl(CMemory*, void*, void*, unsigned long);
extern "C" void CopyToAMemorySync__7CMemoryFPvPvUl(CMemory*, void*, void*, unsigned long);
extern "C" void SetStdProjectionMatrix__10CCameraPcsFv(void*);
extern "C" void _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
    int, int, int, int, int);
extern "C" void SetFog__8CGraphicFii(void*, int, int);
extern "C" void SetAmbient__9CLightPcsF8_GXColor(void*, void*);
extern "C" void SetNumDiffuse__9CLightPcsFUl(void*, unsigned long);
extern "C" void SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(void*, unsigned long, void*, void*, int);
extern "C" void SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(void*, int, Vec*, unsigned long);
extern "C" void __ct__Q29CLightPcs10CBumpLightFv(void*);
extern "C" int AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
    void*, void*, int, void*, int);
extern "C" void Create__6CCharaFv(void*);
extern "C" void Destroy__6CCharaFv(void*);
extern "C" void Printf__7CSystemFPce(void*, const char*, ...);
extern "C" void* __ct__Q26CChara6CModelFv(void*);
extern "C" void Create__Q26CChara6CModelFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void AttachTextureSet__Q26CChara6CModelFP11CTextureSet(void*, void*);
extern "C" void Init__Q26CChara6CModelFv(void*);
extern "C" void* Duplicate__Q26CChara6CModelFPQ27CMemory6CStage(void*, void*);
extern "C" void InitMogFurTex__Q26CChara6CModelFv(void*);
extern "C" void Draw__Q26CChara6CModelFPA4_fii(void*, Mtx, int, int);
extern "C" void DrawShadow__Q26CChara6CModelFPA4_fi(void*, Mtx, int);
extern "C" void DrawFur__Q26CChara6CModelFPA4_fi(void*, Mtx, int);
extern "C" void* __ct__Q26CChara5CAnimFv(void*);
extern "C" void Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(void*, void*, void*);
extern "C" void LoadSe__6CSoundFPv(void*, void*);
extern "C" void LoadWave__6CSoundFPv(void*, void*);
extern "C" void DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(void*, int);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void loadModelASyncFrame__Q29CCharaPcs7CHandleFv(CCharaPcs::CHandle*);
extern "C" unsigned char MiniGamePcs[];
extern unsigned char PTR_s_CCharaPcs_GAME__801fce10[];

static const char s_p_chara_cpp[] = "p_chara.cpp";
static const char s_CCharaPcs_stage[] = "CCharaPcs";
static const char s_CCharaPcs_amem[] = "CCharaPcs amem";
static const char s_CCharaPcs_amemw[] = "CCharaPcs amemw";
static const char s_CCharaPcs_loadModel[] = "CCharaPcs LoadModel";
static const char s_CCharaPcs_loadTex[] = "CCharaPcs LoadTex";
static const char s_CCharaPcs_loadWepTex[] = "CCharaPcs LoadWepTex";
static const char s_CCharaPcs_loadWepModel[] = "CCharaPcs LoadWepModel";
static const char s_CCharaPcs_loadFaModel[] = "CCharaPcs LoadFaModel";
static const char s_CCharaPcs_loadAnim[] = "CCharaPcs LoadAnim";
static const char s_charaMergePathFmt[] = "dvd/mrg/m%04d_%02d.mrg";
static const char s_charaMergeDupFmt[] = "CCharaPcs duplicate merge %d\n";
static const char s_charaMergeOpenFmt[] = "CCharaPcs missing merge %d\n";
static const char s_charaMergeDoneFmt[] = "CCharaPcs LoadMergeFile %d 0x%x\n";
static const char s_charaBasePathFmt[] = "dvd/char/k%02d/chara%03d/chara%03d";
static const char s_charaModelSuffix[] = ".mdl";
static const char s_charaDynamicsSuffix[] = ".dyn";
static const char s_charaTextureSuffix[] = ".tex";
static const char s_charaTextureVariantFmt[] = "%s_%c";
static const char s_mogFurTextureName[] = "mog_hair";
static char s_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_ptrarray_grow_error[] = "CPtrArray grow error";

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
    int GetSize();
    void ReleaseAndRemoveAll();
    void RemoveAt(unsigned long index);
    T operator[](unsigned long index);
    void SetStage(CMemory::CStage* stage);
    void SetDefaultSize(unsigned long defaultSize);
    void SetGrow(int growCapacity);
    int setSize(unsigned long newSize);
    T GetAt(unsigned long index);
    void RemoveAll();
};

template <class T>
CPtrArray<T>::CPtrArray()
{
    m_vtable = 0;
    m_size = 0;
    m_numItems = 0;
    m_defaultSize = 0x10;
    m_items = 0;
    m_stage = 0;
    m_growCapacity = 1;
}

template <class T>
CPtrArray<T>::~CPtrArray()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

template <class T>
bool CPtrArray<T>::Add(T item)
{
    if (setSize(m_numItems + 1) == 0) {
        return false;
    }

    m_items[m_numItems] = item;
    m_numItems = m_numItems + 1;
    return true;
}

template <class T>
int CPtrArray<T>::GetSize()
{
    return m_numItems;
}

template <class T>
void CPtrArray<T>::ReleaseAndRemoveAll()
{
    int offset = 0;

    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        int* item = *(int**)((int)m_items + offset);
        if (item != 0) {
            int refCount = item[1];
            item[1] = refCount - 1;
            if (refCount - 1 == 0 && item != 0) {
                (*(void (**)(int*, int))(*item + 8))(item, 1);
            }
            *(unsigned int*)((int)m_items + offset) = 0;
        }
        offset += 4;
    }

    RemoveAll();
}

template <class T>
void CPtrArray<T>::RemoveAt(unsigned long index)
{
    int offset = (int)(index * 4);

    m_items[index] = 0;
    for (; index < (unsigned long)m_numItems; index++) {
        unsigned int* current = (unsigned int*)((int)m_items + offset);
        offset += 4;
        *current = current[1];
    }

    m_numItems = m_numItems - 1;
}

template <class T>
T CPtrArray<T>::operator[](unsigned long index)
{
    return GetAt(index);
}

template <class T>
void CPtrArray<T>::SetStage(CMemory::CStage* stage)
{
    m_stage = stage;
}

template <class T>
void CPtrArray<T>::SetDefaultSize(unsigned long defaultSize)
{
    m_defaultSize = defaultSize;
}

template <class T>
void CPtrArray<T>::SetGrow(int growCapacity)
{
    m_growCapacity = growCapacity;
}

template <class T>
int CPtrArray<T>::setSize(unsigned long newSize)
{
    T* newItems;

    if ((unsigned long)m_size < newSize) {
        if (m_size == 0) {
            m_size = m_defaultSize;
        } else {
            if (m_growCapacity == 0) {
                System.Printf(s_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = (T*)_Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(
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

template <class T>
T CPtrArray<T>::GetAt(unsigned long index)
{
    return m_items[index];
}

template <class T>
void CPtrArray<T>::RemoveAll()
{
    if (m_items != 0) {
        __dla__FPv(m_items);
        m_items = 0;
    }
    m_size = 0;
    m_numItems = 0;
}

template class CPtrArray<CCharaPcs::CLoadPdt*>;
template class CPtrArray<CCharaPcs::CLoadTexture*>;
template class CPtrArray<CCharaPcs::CLoadAnim*>;
template class CPtrArray<CCharaPcs::CLoadModel*>;

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline CPtrArray<CCharaPcs::CLoadModel*>* LoadModelArray(CCharaPcs* self)
{
    return reinterpret_cast<CPtrArray<CCharaPcs::CLoadModel*>*>(Ptr(self, 0x50));
}

static inline CPtrArray<CCharaPcs::CLoadAnim*>* LoadAnimArray(CCharaPcs* self)
{
    return reinterpret_cast<CPtrArray<CCharaPcs::CLoadAnim*>*>(Ptr(self, 0x6C));
}

static inline CPtrArray<CCharaPcs::CLoadTexture*>* LoadTextureArray(CCharaPcs* self)
{
    return reinterpret_cast<CPtrArray<CCharaPcs::CLoadTexture*>*>(Ptr(self, 0x88));
}

static inline CPtrArray<CCharaPcs::CLoadPdt*>* LoadPdtArray(CCharaPcs* self)
{
    return reinterpret_cast<CPtrArray<CCharaPcs::CLoadPdt*>*>(Ptr(self, 0xA4));
}

static inline CMemory::CStage*& StageAt(CCharaPcs* self, unsigned int offset)
{
    return *reinterpret_cast<CMemory::CStage**>(Ptr(self, offset));
}

static inline int& CameraCountAt(CCharaPcs* self, int index)
{
    return *reinterpret_cast<int*>(Ptr(self, 0x04 + index * 4));
}

static inline void*& CameraDataAt(CCharaPcs* self, int index)
{
    return *reinterpret_cast<void**>(Ptr(self, 0x14 + index * 4));
}

static inline CCharaPcs::CHandle*& HandleListHead(CCharaPcs* self)
{
    return *reinterpret_cast<CCharaPcs::CHandle**>(Ptr(self, 0x4C));
}

static inline unsigned int& FreeMergeMask(CCharaPcs* self)
{
    return *reinterpret_cast<unsigned int*>(Ptr(self, 0x718));
}

static inline int& LoadStageMode(CCharaPcs* self)
{
    return *reinterpret_cast<int*>(Ptr(self, 0xE4));
}

static inline unsigned int& LoadStreamCursor(CCharaPcs* self)
{
    return *reinterpret_cast<unsigned int*>(Ptr(self, 0x714));
}

static inline unsigned int& CurrentSceneId()
{
    return *reinterpret_cast<unsigned int*>(Ptr(&Game, 0xC7F0));
}

static inline unsigned int& CharaAmemSize()
{
    return *reinterpret_cast<unsigned int*>(Ptr(&Chara, 0x205C));
}

static inline CMemory::CStage*& CharaAmemStage()
{
    return *reinterpret_cast<CMemory::CStage**>(Ptr(&Chara, 0x2058));
}

static inline void SetupBaseCharaLights(CCharaPcs* self)
{
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        0, 0, 1, 2, 3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        1, 0, 1, 2, 3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        2, 0, 1, 2, 3);
    SetFog__8CGraphicFii(&Graphic, 1, 0);
    SetAmbient__9CLightPcsF8_GXColor(&LightPcs, Ptr(self, 0xE8));
    SetNumDiffuse__9CLightPcsFUl(&LightPcs, 3);

    for (unsigned long lightIndex = 0; lightIndex < 3; lightIndex++) {
        SetDiffuse__9CLightPcsFUl8_GXColorP3Veci(
            &LightPcs, lightIndex, Ptr(self, 0xF0 + static_cast<unsigned int>(lightIndex) * 4),
            Ptr(self, 0x108 + static_cast<unsigned int>(lightIndex) * 12), static_cast<int>(lightIndex == 2));
    }
}

static inline void* StageBase(CMemory::CStage* stage)
{
    return *reinterpret_cast<void**>(Ptr(stage, 8));
}

static inline CMemory::CStage* SelectLoadStage(CCharaPcs* self, CMemory::CStage* fallback)
{
    return GET_CHARA_ALLOC_STAGE_S(LoadStageMode(self), fallback);
}

template <typename T>
static inline void ReleaseShared(T*& ptr)
{
    if (ptr != 0) {
        int* refData = reinterpret_cast<int*>(ptr);
        refData[1]--;
        if (refData[1] == 0) {
            (*(void (**)(void*, int))(refData[0] + 8))(ptr, 1);
        }
        ptr = 0;
    }
}

template <typename T>
static inline void AddSharedRef(T* ptr)
{
    if (ptr != 0) {
        reinterpret_cast<int*>(ptr)[1]++;
    }
}

static inline void BuildCharaBasePath(int charaKind, unsigned long charaNo, char* outPath)
{
    sprintf(outPath, s_charaBasePathFmt, charaKind, static_cast<int>(charaNo), static_cast<int>(charaNo));
}

static inline CMemory::CStage* HandleModelStage(int charaKind, int specialModelStage)
{
    const unsigned int offset = specialModelStage != 0 ? (charaKind == 3 ? 0xE0U : 0xDCU) : 0xCCU;
    return SelectLoadStage(&CharaPcs, StageAt(&CharaPcs, offset));
}

static inline CMemory::CStage* HandleTextureStage(int charaKind)
{
    return SelectLoadStage(&CharaPcs, StageAt(&CharaPcs, charaKind == 4 ? 0xD8U : 0xD0U));
}

static inline Mtx* ModelLocalMtx(CChara::CModel* model)
{
    return reinterpret_cast<Mtx*>(Ptr(model, 8));
}

static inline _GXColor BlendColor(const _GXColor& a, const _GXColor& b, float t)
{
    _GXColor out;
    out.r = static_cast<unsigned char>(a.r + static_cast<int>((b.r - a.r) * t));
    out.g = static_cast<unsigned char>(a.g + static_cast<int>((b.g - a.g) * t));
    out.b = static_cast<unsigned char>(a.b + static_cast<int>((b.b - a.b) * t));
    out.a = static_cast<unsigned char>(a.a + static_cast<int>((b.a - a.a) * t));
    return out;
}

static inline _GXColor ModulateColor(const _GXColor& src, const _GXColor& shade)
{
    _GXColor out;
    out.r = static_cast<unsigned char>((static_cast<unsigned int>(src.r) * shade.r) / 255);
    out.g = static_cast<unsigned char>((static_cast<unsigned int>(src.g) * shade.g) / 255);
    out.b = static_cast<unsigned char>((static_cast<unsigned int>(src.b) * shade.b) / 255);
    out.a = src.a;
    return out;
}

static inline bool HasLoadedMergeFile(CCharaPcs* self, int mergeFileId)
{
    for (int i = 0; i < LoadModelArray(self)->GetSize(); i++) {
        CCharaPcs::CLoadModel* loadModel = (*LoadModelArray(self))[static_cast<unsigned long>(i)];
        if (loadModel != 0 && loadModel->m_mergeFileId == mergeFileId) {
            return true;
        }
    }

    for (int i = 0; i < LoadTextureArray(self)->GetSize(); i++) {
        CCharaPcs::CLoadTexture* loadTexture = (*LoadTextureArray(self))[static_cast<unsigned long>(i)];
        if (loadTexture != 0 && loadTexture->m_mergeFileId == mergeFileId) {
            return true;
        }
    }

    for (int i = 0; i < LoadPdtArray(self)->GetSize(); i++) {
        CCharaPcs::CLoadPdt* loadPdt = (*LoadPdtArray(self))[static_cast<unsigned long>(i)];
        if (loadPdt != 0 && loadPdt->m_mergeFileId == mergeFileId) {
            return true;
        }
    }

    for (int i = 0; i < LoadAnimArray(self)->GetSize(); i++) {
        CCharaPcs::CLoadAnim* loadAnim = (*LoadAnimArray(self))[static_cast<unsigned long>(i)];
        if (loadAnim != 0 && loadAnim->m_mergeFileId == mergeFileId) {
            return true;
        }
    }

    return false;
}
}

/*
 * --INFO--
 * PAL Address: 8007b904
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadPdt*>* dtor_8007B904(CPtrArray<CCharaPcs::CLoadPdt*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadPdt*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 8007b9b4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadTexture*>* dtor_8007B9B4(CPtrArray<CCharaPcs::CLoadTexture*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadTexture*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 8007ba64
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadAnim*>* dtor_8007BA64(CPtrArray<CCharaPcs::CLoadAnim*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadAnim*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 8007bb14
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CPtrArray<CCharaPcs::CLoadModel*>* dtor_8007BB14(CPtrArray<CCharaPcs::CLoadModel*>* ptrArray, short shouldDelete)
{
    if (ptrArray != 0) {
        ptrArray->~CPtrArray<CCharaPcs::CLoadModel*>();
        if (shouldDelete > 0) {
            __dl__FPv(ptrArray);
        }
    }
    return ptrArray;
}

/*
 * --INFO--
 * PAL Address: 0x8007a42c
 * PAL Size: 116b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CMemory::CStage* GET_CHARA_ALLOC_STAGE_S(int stageIndex, CMemory::CStage* stage)
{
    if (stageIndex == 3) {
        return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartMng) + 0x2351c);
    }

    if (stageIndex < 3) {
        if (stageIndex == 1) {
            return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&MapMng));
        }
        if (stageIndex > 0) {
            return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&PartPcs) + 0x20);
        }
    } else if (stageIndex < 5) {
        return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&CharaPcs) + 0xd4);
    }

    return stage;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CCharaPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::~CCharaPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Init()
{
    StageAt(this, 0xC0) = CreateStage__7CMemoryFUlPci(&Memory, 0x38000, s_CCharaPcs_stage, 0);
    StageAt(this, 0xC4) = CreateStage__7CMemoryFUlPci(&Memory, 0x380000, s_CCharaPcs_amem, 2);
    StageAt(this, 0xC8) = CreateStage__7CMemoryFUlPci(&Memory, 0x70000, s_CCharaPcs_amemw, 2);
    CharaAmemStage() = StageAt(this, 0xC4);

    LoadModelArray(this)->SetStage(StageAt(this, 0xC0));
    LoadModelArray(this)->SetDefaultSize(0x80);
    LoadModelArray(this)->SetGrow(0);

    LoadAnimArray(this)->SetStage(StageAt(this, 0xC0));
    LoadAnimArray(this)->SetDefaultSize(0x200);
    LoadAnimArray(this)->SetGrow(0);

    LoadTextureArray(this)->SetStage(StageAt(this, 0xC0));
    LoadTextureArray(this)->SetDefaultSize(0x100);
    LoadTextureArray(this)->SetGrow(0);

    LoadPdtArray(this)->SetStage(StageAt(this, 0xC0));
    LoadPdtArray(this)->SetDefaultSize(0x80);
    LoadPdtArray(this)->SetGrow(0);

    for (int i = 0; i < 2; i++) {
        _GXColor& ambientColor = *reinterpret_cast<_GXColor*>(Ptr(this, 0xE8 + i * 4));
        ambientColor.r = 0x3F;
        ambientColor.g = 0x3F;
        ambientColor.b = 0x3F;
        ambientColor.a = 0xFF;

        for (int lightIndex = 0; lightIndex < 3; lightIndex++) {
            _GXColor& lightColor = *reinterpret_cast<_GXColor*>(Ptr(this, 0xF0 + i * 0x0C + lightIndex * 4));
            const unsigned char intensity = static_cast<unsigned char>(lightIndex == 0 ? 0x3F : 0x00);
            lightColor.r = intensity;
            lightColor.g = intensity;
            lightColor.b = intensity;
            lightColor.a = 0xFF;
        }
    }

    reinterpret_cast<Vec*>(Ptr(this, 0x108))->x = 0.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x108))->y = 0.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x108))->z = 1.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x114))->x = 0.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x114))->y = 0.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x114))->z = 1.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x120))->x = 0.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x120))->y = 0.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x120))->z = 1.0f;

    for (int i = 0; i < 5; i++) {
        const unsigned char shade = static_cast<unsigned char>((i * 0xFF) / 4);
        _GXColor& fadeColor = *reinterpret_cast<_GXColor*>(Ptr(this, 0x12C + i * 4));
        fadeColor.r = shade;
        fadeColor.g = shade;
        fadeColor.b = shade;
        fadeColor.a = 0xFF;
    }

    *reinterpret_cast<int*>(Ptr(this, 0xE4)) = 0;
    *reinterpret_cast<int*>(Ptr(this, 0x24)) = 0;
    reinterpret_cast<_GXColor*>(Ptr(this, 0x18C))->r = 0x00;
    reinterpret_cast<_GXColor*>(Ptr(this, 0x18C))->g = 0x00;
    reinterpret_cast<_GXColor*>(Ptr(this, 0x18C))->b = 0x40;
    reinterpret_cast<_GXColor*>(Ptr(this, 0x18C))->a = 0x40;
    reinterpret_cast<Vec*>(Ptr(this, 0x17C))->x = 0.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x17C))->y = 10.0f;
    reinterpret_cast<Vec*>(Ptr(this, 0x17C))->z = 0.0f;
    *reinterpret_cast<float*>(Ptr(this, 0x188)) = 120.0f;
    *reinterpret_cast<int*>(Ptr(this, 0x44)) = 0x80;
    *reinterpret_cast<int*>(Ptr(this, 0x48)) = 100;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Quit()
{
    *reinterpret_cast<int*>(Ptr(&Chara, 0x205C)) = 0;
    Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(Ptr(this, 0xC8)));
    Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(Ptr(this, 0xC4)));
    Memory.DestroyStage(*reinterpret_cast<CMemory::CStage**>(Ptr(this, 0xC0)));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::GetTable(unsigned long index)
{
    unsigned char* table = PTR_s_CCharaPcs_GAME__801fce10;
    unsigned long offset = index * 0x15c;
    return (int)(table + offset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::create()
{
    FreeMergeMask(this) = 0;

    StageAt(this, 0xCC) = CreateStage__7CMemoryFUlPci(&Memory, 0x177000, s_CCharaPcs_loadModel, 0);
    StageAt(this, 0xD0) = CreateStage__7CMemoryFUlPci(&Memory, 0x130000, s_CCharaPcs_loadTex, 0);
    StageAt(this, 0xD8) = CreateStage__7CMemoryFUlPci(&Memory, 0x8400, s_CCharaPcs_loadWepTex, 0);
    StageAt(this, 0xDC) = CreateStage__7CMemoryFUlPci(&Memory, 0x18000, s_CCharaPcs_loadWepModel, 0);
    StageAt(this, 0xE0) = CreateStage__7CMemoryFUlPci(&Memory, 0x10000, s_CCharaPcs_loadFaModel, 0);
    StageAt(this, 0xD4) = CreateStage__7CMemoryFUlPci(
        &Memory, CurrentSceneId() == 4 ? 0x190000UL : 0x1E0000UL, s_CCharaPcs_loadAnim, 0);

    unsigned char* sentinel = reinterpret_cast<unsigned char*>(
        _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, 0x194, StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0xDB, 0));
    if (sentinel != 0) {
        memset(sentinel, 0, 0x194);
        *reinterpret_cast<int*>(sentinel + 0x110) = -1;
        *reinterpret_cast<float*>(sentinel + 0x11C) = 1.0f;
        *reinterpret_cast<float*>(sentinel + 0x154) = 0.0f;
        sentinel[0x190] = static_cast<unsigned char>(sentinel[0x190] | 0x80);
    }

    HandleListHead(this) = reinterpret_cast<CHandle*>(sentinel);
    if (HandleListHead(this) != 0) {
        HandleListHead(this)->m_previous = HandleListHead(this);
        HandleListHead(this)->m_next = HandleListHead(this);
    }

    for (int i = 0; i < 4; i++) {
        CameraCountAt(this, i) = 0;
        CameraDataAt(this, i) = 0;
    }

    CLightPcs::CBumpLight bumpLight;
    Vec lightPos = {0.0f, 40.0f, 60.0f};
    Vec lightTarget = {0.0f, 0.0f, 0.0f};
    Vec lightDir;

    PSVECSubtract(&lightTarget, &lightPos, &lightDir);
    PSVECNormalize(&lightDir, &lightDir);

    bumpLight.m_type = 1;
    bumpLight.m_bumpShade[0] = 0x80;
    bumpLight.m_bumpShade[1] = 0x80;
    bumpLight.m_bumpShade[2] = 0x00;
    bumpLight.m_bumpShade[3] = 0xFF;
    bumpLight.m_position.x = lightPos.x;
    bumpLight.m_position.y = lightPos.y;
    bumpLight.m_position.z = lightPos.z;
    bumpLight.m_targetPosition.x = lightTarget.x;
    bumpLight.m_targetPosition.y = lightTarget.y;
    bumpLight.m_targetPosition.z = lightTarget.z;
    bumpLight.m_direction.x = lightDir.x;
    bumpLight.m_direction.y = lightDir.y;
    bumpLight.m_direction.z = lightDir.z;
    bumpLight.m_offsetX = 0.0f;
    bumpLight.m_offsetZ = 0.0f;

    gCharaPartWorkPtr = reinterpret_cast<u8*>(AddBump__9CLightPcsFPQ29CLightPcs6CLightQ29CLightPcs6TARGETPQ27CMemory6CStagei(
        &LightPcs, &bumpLight, 0, *reinterpret_cast<void**>(Ptr(&Chara, 0x2058)), 4));
    Create__6CCharaFv(&Chara);
}

/*
 * --INFO--
 * PAL Address: 0x8007a0a4
 * PAL Size: 92b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::createLoad()
{
    *reinterpret_cast<int*>(Ptr(this, 0x714)) = 0;
    *reinterpret_cast<int*>(Ptr(&Memory, 0x779c)) = 2;
    LoadMergeFile(0, 0x10000000, 1);
    *reinterpret_cast<int*>(Ptr(&Memory, 0x779c)) = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80079fd4
 * PAL Size: 208b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::destroy()
{
    Reset(static_cast<RESET>(1));
    DestroyBumpLightAll__9CLightPcsFQ29CLightPcs6TARGET(&LightPcs, 0);
    gCharaPartWorkPtr = 0;

    if (*reinterpret_cast<void**>(Ptr(this, 0x4C)) != 0) {
        __dt__Q29CCharaPcs7CHandleFv(*reinterpret_cast<void**>(Ptr(this, 0x4C)), 1);
        *reinterpret_cast<void**>(Ptr(this, 0x4C)) = 0;
    }

    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *reinterpret_cast<void**>(Ptr(this, 0xCC)));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *reinterpret_cast<void**>(Ptr(this, 0xD0)));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *reinterpret_cast<void**>(Ptr(this, 0xD8)));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *reinterpret_cast<void**>(Ptr(this, 0xDC)));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *reinterpret_cast<void**>(Ptr(this, 0xE0)));
    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, *reinterpret_cast<void**>(Ptr(this, 0xD4)));
    Destroy__6CCharaFv(&Chara);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Reset(CCharaPcs::RESET mode)
{
    const int resetMode = static_cast<int>(mode);

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        unsigned char* loadAnim = reinterpret_cast<unsigned char*>((*LoadAnimArray(this))[static_cast<unsigned long>(i)]);
        if (loadAnim == 0) {
            continue;
        }

        unsigned char* anim = *reinterpret_cast<unsigned char**>(loadAnim + 0x28);
        if (anim != 0 && *reinterpret_cast<void**>(anim + 0x20) != 0) {
            __dl__FPv(*reinterpret_cast<void**>(anim + 0x20));
            *reinterpret_cast<void**>(anim + 0x20) = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        CameraCountAt(this, i) = 0;
        if (CameraDataAt(this, i) != 0) {
            __dla__FPv(CameraDataAt(this, i));
            CameraDataAt(this, i) = 0;
        }
    }

    if (HandleListHead(this) != 0) {
        CHandle* handle = HandleListHead(this)->m_next;
        while (handle != HandleListHead(this)) {
            CHandle* next = handle->m_next;
            __dt__Q29CCharaPcs7CHandleFv(handle, 1);
            handle = next;
        }
    }

    int charaAmemSize = static_cast<int>(CharaAmemSize());
    if (resetMode != 1) {
        if (resetMode == 0) {
            const unsigned int releaseMask = ~(FreeMergeMask(this) | 0x10000000U);
            releaseUnuseLoadModel(static_cast<int>(releaseMask));

            for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
                int* loadAnim = reinterpret_cast<int*>((*LoadAnimArray(this))[static_cast<unsigned long>(i)]);
                if (loadAnim == 0) {
                    continue;
                }

                const bool releaseByKind = loadAnim[4] < 0 && loadAnim[1] == 1;
                const bool releaseByMask = loadAnim[4] >= 0 && ((releaseMask & static_cast<unsigned int>(loadAnim[5])) != 0);
                if (!releaseByKind && !releaseByMask) {
                    continue;
                }

                loadAnim[1]--;
                if (loadAnim[1] == 0) {
                    (*(void (**)(void*, int))(*loadAnim + 8))(loadAnim, 1);
                }
                LoadAnimArray(this)->RemoveAt(static_cast<unsigned long>(i));
            }

            LoadPdtArray(this)->ReleaseAndRemoveAll();
            charaAmemSize = correctLoadAnimAmem();
        } else {
            LoadModelArray(this)->ReleaseAndRemoveAll();
            LoadAnimArray(this)->ReleaseAndRemoveAll();
            LoadTextureArray(this)->ReleaseAndRemoveAll();
            LoadPdtArray(this)->ReleaseAndRemoveAll();
            charaAmemSize = 0;
        }
    } else {
        LoadModelArray(this)->ReleaseAndRemoveAll();
        LoadAnimArray(this)->ReleaseAndRemoveAll();
        LoadTextureArray(this)->ReleaseAndRemoveAll();
        LoadPdtArray(this)->ReleaseAndRemoveAll();
        charaAmemSize = 0;
    }

    CharaAmemSize() = static_cast<unsigned int>(charaAmemSize < 0 ? 0 : charaAmemSize);
    if (gCharaPartWorkPtr != 0) {
        gCharaPartWorkPtr[0x6B] = 0xFF;
    }
    FreeMergeMask(this) = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::correctLoadAnimAmem()
{
    unsigned char* tempBuffer = reinterpret_cast<unsigned char*>(
        _Alloc__7CMemoryFUlPQ27CMemory6CStagePcii(&Memory, 0x80000, StageAt(this, 0xD4), const_cast<char*>(s_p_chara_cpp), 0x162, 1));
    if (tempBuffer == 0) {
        return -1;
    }

    int maxEnd = 0;
    for (int i = 0; i < LoadAnimArray(this)->GetSize(); i++) {
        unsigned char* loadAnim = reinterpret_cast<unsigned char*>((*LoadAnimArray(this))[static_cast<unsigned long>(i)]);
        if (loadAnim == 0) {
            continue;
        }

        unsigned char* anim = *reinterpret_cast<unsigned char**>(loadAnim + 0x28);
        if (anim == 0) {
            continue;
        }

        const int animEnd = *reinterpret_cast<int*>(anim + 0x28) + *reinterpret_cast<int*>(anim + 0x1C);
        if (maxEnd < animEnd) {
            maxEnd = animEnd;
        }
    }

    int compactedSize = 0;
    int scanOffset = 0;
    while (scanOffset < maxEnd) {
        int chunkSize = 0;
        int nextOffset = scanOffset;

        for (int i = 0; i < LoadAnimArray(this)->GetSize(); i++) {
            unsigned char* loadAnim = reinterpret_cast<unsigned char*>((*LoadAnimArray(this))[static_cast<unsigned long>(i)]);
            if (loadAnim == 0) {
                continue;
            }

            unsigned char* anim = *reinterpret_cast<unsigned char**>(loadAnim + 0x28);
            if (anim == 0) {
                continue;
            }

            const unsigned int animOffset = *reinterpret_cast<unsigned int*>(anim + 0x28);
            const int animSize = *reinterpret_cast<int*>(anim + 0x1C);
            const unsigned int animEnd = animOffset + static_cast<unsigned int>(animSize);
            if (animOffset < static_cast<unsigned int>(scanOffset) || animEnd >= static_cast<unsigned int>(scanOffset + 0x80000)) {
                continue;
            }

            if (nextOffset < static_cast<int>(animEnd)) {
                nextOffset = static_cast<int>(animEnd);
            }

            CopyFromAMemorySync__7CMemoryFPvPvUl(
                &Memory, tempBuffer + chunkSize,
                reinterpret_cast<void*>(*reinterpret_cast<int*>(Ptr(StageAt(this, 0xC4), 8)) + static_cast<int>(animOffset)),
                static_cast<unsigned long>(animSize));

            *reinterpret_cast<int*>(anim + 0x28) = compactedSize + chunkSize;
            chunkSize += animSize;
        }

        if (chunkSize != 0) {
            CopyToAMemorySync__7CMemoryFPvPvUl(
                &Memory, tempBuffer, reinterpret_cast<void*>(*reinterpret_cast<int*>(Ptr(StageAt(this, 0xC4), 8)) + compactedSize),
                static_cast<unsigned long>(chunkSize));
        }

        compactedSize += chunkSize;
        scanOffset = nextOffset;
    }

    __dl__FPv(tempBuffer);
    return compactedSize;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::onScriptChanging(char*)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80079938
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::calc()
{
    CHandle* head = *reinterpret_cast<CHandle**>(Ptr(this, 0x4c));
    CHandle* handle = head->m_next;

    while (head != handle) {
        CHandle* next = handle->m_next;
        handle->m_shadowTexturePtr = 0;
        loadModelASyncFrame__Q29CCharaPcs7CHandleFv(handle);
        handle = next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::calcAfter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseAllAnimBank()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseUnusedAnimBank()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::TryReleaseAnimBank(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80079754
 * PAL Size: 12b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::SetSpecularAlpha(int alpha)
{
    gCharaPartWorkPtr[0x6B] = (u8)alpha;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::InitEnv(int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80079590
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::GetNumTexShadow()
{
    int count = 0;
    CHandle* head = *(CHandle**)((char*)this + 0x4C);
    CHandle* current = head->m_next;

    while (head != current) {
        if (((current->m_flags & 0x200) != 0) && (current->m_shadowTexturePtr != 0)) {
            count++;
        }
        current = current->m_next;
    }

    return count;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetTexShadow(int, int, _GXTexObj*, Vec*, float (*) [3][4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::draw()
{
    SetupBaseCharaLights(this);

    if (HandleListHead(this) == 0) {
        return;
    }

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        if ((*reinterpret_cast<unsigned int*>(MiniGamePcs + 0x25732) & 0x8000) != 0) {
            handle->draw(0, 1);
        }
        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawBefore()
{
    SetStdProjectionMatrix__10CCameraPcsFv(&CameraPcs);
    SetupBaseCharaLights(this);

    if (HandleListHead(this) == 0) {
        return;
    }

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        if ((*reinterpret_cast<unsigned int*>(MiniGamePcs + 0x25732) & 0x8000) != 0) {
            handle->draw(3, 1);
        }
        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawMakeTexShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawShadow()
{
    if (*reinterpret_cast<unsigned char*>(Ptr(&CameraPcs, 0x404)) == 0) {
        return;
    }

    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        0, 0, 1, 2, 3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        1, 0, 1, 2, 3);
    _GXSetTevSwapModeTable__F13_GXTevSwapSel15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan15_GXTevColorChan(
        2, 0, 1, 2, 3);

    _GXColor shadowColor = {0x00, 0x00, 0x00, 0xFF};
    SetAmbient__9CLightPcsF8_GXColor(&LightPcs, &shadowColor);
    SetNumDiffuse__9CLightPcsFUl(&LightPcs, 0);
    SetPosition__9CLightPcsFQ29CLightPcs6TARGETP3VecUl(&LightPcs, 0, 0, 0xFFFFFFFF);

    if (HandleListHead(this) == 0) {
        return;
    }

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        if ((*reinterpret_cast<unsigned int*>(MiniGamePcs + 0x25732) & 0x8000) != 0) {
            handle->draw(1, 1);
        }
        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::createTextureSet(void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::releaseUnuseLoadModel(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::releaseUnuseLoadAnim(CCharaPcs::CLoadAnim*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::DumpLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchModel(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchTexture(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchAnim(int, int, char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::searchPdt(int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 800783d0
 * PAL Size: 488b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::LoadCam(int index, char* fileName)
{
    static char s_p_chara_cpp[] = "p_chara.cpp";
    char path[0x104];
    CChunkFile::CChunk chunk;

    int* cameraCounts = reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x04);
    void** cameraData = reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x14);
    void*& cameraBuffer = cameraData[index];

    if (cameraBuffer != 0) {
        __dla__FPv(cameraBuffer);
        cameraBuffer = 0;
    }

    sprintf(path, "dvd/cft/%s.cmd", fileName);
    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
    if (fileHandle == 0) {
        return;
    }

    File.Read(fileHandle);
    File.SyncCompleted(fileHandle);

    CChunkFile chunkFile(File.m_readBuffer);
    while (chunkFile.GetNextChunk(chunk)) {
        if (chunk.m_id != 'CAM ') {
            continue;
        }

        cameraCounts[index] = static_cast<int>(chunk.m_arg0);

        CMemory::CStage* stage = *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(this) + 0xD4);
        cameraBuffer = __nwa__FUlPQ27CMemory6CStagePci(
            static_cast<unsigned long>(cameraCounts[index] << 5), stage, s_p_chara_cpp, 0x4D4);

        float* values = reinterpret_cast<float*>(cameraBuffer);
        for (int i = 0; i < cameraCounts[index] * 8; i++) {
            values[i] = chunkFile.GetF4();
        }
    }

    File.Close(fileHandle);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::LoadMergeFile(int mergeFileId, int mergeFlags, int streamToAmem)
{
    if (HasLoadedMergeFile(this, mergeFileId)) {
        Printf__7CSystemFPce(&System, s_charaMergeDupFmt, mergeFileId);
        return;
    }

    int mergePartCount = 1;
    for (int mergePartIndex = 0; mergePartIndex < mergePartCount; mergePartIndex++) {
        char path[0x100];
        sprintf(path, s_charaMergePathFmt, mergeFileId, mergePartIndex);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle == 0) {
            Printf__7CSystemFPce(&System, s_charaMergeOpenFmt, mergeFileId);
            break;
        }

        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        CChunkFile chunkFile(File.m_readBuffer);
        CChunkFile::CChunk chunk;
        while (chunkFile.GetNextChunk(chunk)) {
            if (chunk.m_id != 'MRG ') {
                continue;
            }

            chunkFile.PushChunk();
            while (chunkFile.GetNextChunk(chunk)) {
                if (chunk.m_id == 'INFO') {
                    mergePartCount = static_cast<int>(chunkFile.Get4());
                    continue;
                }
                if (chunk.m_id != 'DATA') {
                    continue;
                }

                int dataType = -1;
                void* keyTag = reinterpret_cast<void*>(-1);
                int keyId = -1;
                void* variantTag = reinterpret_cast<void*>(-1);
                int hasDynamics = 0;
                char* animName = 0;

                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk)) {
                    if (chunk.m_id == 'NAME') {
                        animName = chunkFile.GetString();
                        continue;
                    }
                    if (chunk.m_id == 'INFO') {
                        dataType = static_cast<int>(chunkFile.Get4());
                        keyTag = reinterpret_cast<void*>(chunkFile.Get4());
                        keyId = static_cast<int>(chunkFile.Get4());
                        variantTag = reinterpret_cast<void*>(chunkFile.Get4());
                        hasDynamics = static_cast<int>(chunkFile.Get4());
                        continue;
                    }
                    if (chunk.m_id != 'RAW ') {
                        continue;
                    }

                    void* rawData = chunkFile.GetAddress();
                    const int rawSize = static_cast<int>(chunk.m_size);

                    if (dataType == 0) {
                        CLoadModel* loadModel = 0;
                        for (int i = 0; i < LoadModelArray(this)->GetSize(); i++) {
                            CLoadModel* it = (*LoadModelArray(this))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId) {
                                loadModel = it;
                                break;
                            }
                        }

                        if (loadModel == 0) {
                            loadModel = new (StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
                            if (loadModel != 0) {
                                loadModel->m_keyTag = keyTag;
                                loadModel->m_keyId = keyId;
                                loadModel->m_mergeFileId = mergeFileId;
                                loadModel->m_mergeFlags = mergeFlags;
                                loadModel->m_model = 0;
                                loadModel->m_streamMode = 0;
                                loadModel->m_streamOffset = 0;
                                loadModel->m_streamSize = 0;
                                LoadModelArray(this)->Add(loadModel);

                                if (streamToAmem == 0) {
                                    loadModel->m_model = reinterpret_cast<CChara::CModel*>(
                                        __nw__FUlPQ27CMemory6CStagePci(0x124, StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5F1));
                                    if (loadModel->m_model != 0) {
                                        loadModel->m_model = reinterpret_cast<CChara::CModel*>(__ct__Q26CChara6CModelFv(loadModel->m_model));
                                        Create__Q26CChara6CModelFPvPQ27CMemory6CStage(
                                            loadModel->m_model, rawData, SelectLoadStage(this, StageAt(this, 0xCC)));
                                    }
                                } else {
                                    loadModel->m_streamMode = 1;
                                    loadModel->m_streamOffset = reinterpret_cast<void*>(LoadStreamCursor(this));
                                    loadModel->m_streamSize = rawSize;
                                    CopyToAMemorySync__7CMemoryFPvPvUl(
                                        &Memory, rawData,
                                        reinterpret_cast<unsigned char*>(StageBase(StageAt(this, 0xC8))) + LoadStreamCursor(this),
                                        static_cast<unsigned long>(rawSize));
                                    LoadStreamCursor(this) += static_cast<unsigned int>(rawSize);
                                }
                            }
                        }

                        if (hasDynamics != 0 && loadModel != 0 && loadModel->m_model != 0 && chunkFile.GetNextChunk(chunk)) {
                            CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(
                                loadModel->m_model, chunkFile.GetAddress(), SelectLoadStage(this, StageAt(this, 0xCC)));
                        }
                    } else if (dataType == 1) {
                        CLoadTexture* loadTexture = 0;
                        for (int i = 0; i < LoadTextureArray(this)->GetSize(); i++) {
                            CLoadTexture* it = (*LoadTextureArray(this))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId && it->m_variantTag == variantTag) {
                                loadTexture = it;
                                break;
                            }
                        }

                        if (loadTexture == 0) {
                            loadTexture = new (StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
                            if (loadTexture != 0) {
                                loadTexture->m_keyTag = keyTag;
                                loadTexture->m_keyId = keyId;
                                loadTexture->m_mergeFileId = mergeFileId;
                                loadTexture->m_mergeFlags = mergeFlags;
                                loadTexture->m_variantTag = variantTag;
                                loadTexture->m_textureSet = 0;
                                loadTexture->m_streamMode = 0;
                                loadTexture->m_streamOffset = 0;
                                loadTexture->m_streamSize = 0;
                                LoadTextureArray(this)->Add(loadTexture);

                                if (streamToAmem == 0) {
                                    loadTexture->m_textureSet =
                                        new (StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
                                    if (loadTexture->m_textureSet != 0) {
                                        loadTexture->m_textureSet->Create(
                                            rawData,
                                            SelectLoadStage(
                                                this, StageAt(this, variantTag == reinterpret_cast<void*>(4) ? 0xD8 : 0xD0)),
                                            0, 0, 0, 0);
                                    }
                                } else {
                                    loadTexture->m_streamMode = 1;
                                    loadTexture->m_streamOffset = reinterpret_cast<void*>(LoadStreamCursor(this));
                                    loadTexture->m_streamSize = rawSize;
                                    CopyToAMemorySync__7CMemoryFPvPvUl(
                                        &Memory, rawData,
                                        reinterpret_cast<unsigned char*>(StageBase(StageAt(this, 0xC8))) + LoadStreamCursor(this),
                                        static_cast<unsigned long>(rawSize));
                                    LoadStreamCursor(this) += static_cast<unsigned int>(rawSize);
                                }
                            }
                        }
                    } else if (dataType == 2) {
                        CLoadAnim* loadAnim = 0;
                        for (int i = 0; i < LoadAnimArray(this)->GetSize(); i++) {
                            CLoadAnim* it = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId &&
                                animName != 0 && strcmp(it->m_name, animName) == 0) {
                                loadAnim = it;
                                break;
                            }
                        }

                        if (loadAnim == 0) {
                            CChara::CAnim* anim = reinterpret_cast<CChara::CAnim*>(
                                __nw__FUlPQ27CMemory6CStagePci(0x30, StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x62A));
                            if (anim != 0) {
                                anim = reinterpret_cast<CChara::CAnim*>(__ct__Q26CChara5CAnimFv(anim));
                                Create__Q26CChara5CAnimFPvPQ27CMemory6CStage(anim, rawData, StageAt(this, 0xD4));
                            }

                            loadAnim = new (StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x62D) CLoadAnim;
                            if (loadAnim != 0) {
                                loadAnim->m_keyTag = keyTag;
                                loadAnim->m_keyId = keyId;
                                loadAnim->m_mergeFileId = mergeFileId;
                                loadAnim->m_mergeFlags = mergeFlags;
                                strcpy(loadAnim->m_name, animName != 0 ? animName : "");
                                loadAnim->m_anim = anim;
                                LoadAnimArray(this)->Add(loadAnim);
                            }
                        }
                    } else if (dataType == 3) {
                        LoadSe__6CSoundFPv(&Sound, rawData);
                    } else if (dataType == 4) {
                        LoadWave__6CSoundFPv(&Sound, rawData);
                    } else if (dataType == 5) {
                        CLoadPdt* loadPdt = 0;
                        for (int i = 0; i < LoadPdtArray(this)->GetSize(); i++) {
                            CLoadPdt* it = (*LoadPdtArray(this))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId && it->m_variantTag == variantTag) {
                                loadPdt = it;
                                break;
                            }
                        }

                        if (loadPdt == 0 && chunkFile.GetNextChunk(chunk)) {
                            loadPdt = new (StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x572) CLoadPdt;
                            if (loadPdt != 0) {
                                loadPdt->m_keyTag = keyTag;
                                loadPdt->m_keyId = keyId;
                                loadPdt->m_variantTag = variantTag;
                                loadPdt->m_pdtSlot = PartPcs.LoadMonsterPdt(
                                    keyId, reinterpret_cast<int>(variantTag), rawData, rawSize, chunkFile.GetAddress(),
                                    static_cast<int>(chunk.m_size));
                                loadPdt->m_mergeFileId = mergeFileId;
                                loadPdt->m_mergeFlags = mergeFlags;
                                LoadPdtArray(this)->Add(loadPdt);
                            }
                        }
                    }
                }
                chunkFile.PopChunk();
            }
            chunkFile.PopChunk();
        }

        File.Close(fileHandle);
    }

    Printf__7CSystemFPce(&System, s_charaMergeDoneFmt, mergeFileId, mergeFlags);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::FreeMergeFile(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::isCached(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadModel(void*, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadTexture(void*, int, int, int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::loadAnimBuffer(void*, char*, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawOverlap()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 8007717c
 * PAL Size: 72b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void* CCharaPcs::CHandle::operator new(unsigned long size, CMemory::CStage* stage, char* file, int line)
{
    return ::operator new(size, stage, file, line);
}

/*
 * --INFO--
 * PAL Address: 80077080
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CCharaPcs::CHandle::CHandle()
{
	m_previous = (CCharaPcs::CHandle*)nullptr;
	m_next = (CCharaPcs::CHandle*)nullptr;
	m_model = (CChara::CModel*)nullptr;
	m_textureSet = (CTextureSet*)nullptr;
	m_modelLoadRef = (CRef*)nullptr;
	m_texLoadRef = (CRef*)nullptr;

	for (int i = 0; i < 64; ++i)
	{
		m_animSlot[i] = (CRef*)nullptr;
	}

	// PDT load ref
	m_pdtLoadRef = (CRef*)nullptr;

	// Playback / state
	m_currentAnimIndex = -1;
	m_flags = 0;

	m_colorPhase = 1.0f; // FLOAT_8033028c
	m_sortZ = 0.0f; // FLOAT_80330288
	m_shadowTexturePtr = nullptr;

	m_asyncState = 0;
	m_asyncFileHandle = (CFile::CHandle*)nullptr;

	m_fogBlend = m_sortZ;
	m_unk0x158 = 0;
	m_drawListFlags &= 0x80;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CHandle::~CHandle()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 80076cf4
 * PAL Size: 68b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::Add()
{
    if (m_next != nullptr) {
        return;
    }
    if (m_previous != nullptr) {
        return;
    }

    CCharaPcs::CHandle* head =
        (*reinterpret_cast<CCharaPcs::CHandle**>(reinterpret_cast<char*>(&CharaPcs) + 0x4C))->m_previous;

    m_previous = head;
    m_next = head->m_next;
    head->m_next->m_previous = this;
    head->m_next = this;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::ChangeTexture(
    int charaKind, unsigned long charaNo, unsigned long textureVariant, int mergeFileId, int mergeFlags)
{
    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x749);
    if (m_model != 0) {
        AttachTextureSet__Q26CChara6CModelFP11CTextureSet(m_model, 0);
    }

    ReleaseShared(m_textureSet);
    ReleaseShared(m_texLoadRef);

    char basePath[0x100];
    char path[0x100];
    BuildCharaBasePath(charaKind, charaNo, basePath);

    CLoadTexture* loadTexture = 0;
    for (int i = 0; i < LoadTextureArray(&CharaPcs)->GetSize(); i++) {
        CLoadTexture* it = (*LoadTextureArray(&CharaPcs))[static_cast<unsigned long>(i)];
        if (it != 0 && it->m_keyTag == reinterpret_cast<void*>(charaKind) && it->m_keyId == static_cast<int>(charaNo) &&
            it->m_variantTag == reinterpret_cast<void*>(textureVariant)) {
            loadTexture = it;
            break;
        }
    }

    if (loadTexture == 0) {
        if (textureVariant == 0) {
            strcpy(path, basePath);
        } else {
            sprintf(path, s_charaTextureVariantFmt, basePath, static_cast<int>(textureVariant) + 0x61);
        }
        strcpy(path + strlen(path), s_charaTextureSuffix);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle == 0) {
            m_textureSet = 0;
            return;
        }

        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        loadTexture = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
        if (loadTexture != 0) {
            loadTexture->m_keyTag = reinterpret_cast<void*>(charaKind);
            loadTexture->m_keyId = static_cast<int>(charaNo);
            loadTexture->m_mergeFileId = mergeFileId;
            loadTexture->m_mergeFlags = mergeFlags;
            loadTexture->m_variantTag = reinterpret_cast<void*>(textureVariant);
            loadTexture->m_textureSet = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
            loadTexture->m_streamMode = 0;
            loadTexture->m_streamOffset = 0;
            loadTexture->m_streamSize = 0;

            if (loadTexture->m_textureSet != 0) {
                loadTexture->m_textureSet->Create(File.m_readBuffer, HandleTextureStage(charaKind), 0, 0, 0, 0);
            }
            LoadTextureArray(&CharaPcs)->Add(loadTexture);
        }
        File.Close(fileHandle);
    } else if (loadTexture->m_streamOffset != 0 && reinterpret_cast<int*>(loadTexture)[1] == 1) {
        File.LockBuffer();
        CopyFromAMemorySync__7CMemoryFPvPvUl(
            &Memory, File.m_readBuffer,
            reinterpret_cast<unsigned char*>(StageBase(StageAt(&CharaPcs, 0xC8))) +
                reinterpret_cast<unsigned int>(loadTexture->m_streamOffset),
            static_cast<unsigned long>(loadTexture->m_streamSize));
        loadTexture->m_textureSet = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
        if (loadTexture->m_textureSet != 0) {
            loadTexture->m_textureSet->Create(File.m_readBuffer, HandleTextureStage(charaKind), 0, 0, 0, 0);
        }
        File.UnlockBuffer();
    }

    m_texLoadRef = loadTexture;
    AddSharedRef(m_texLoadRef);
    m_textureSet = loadTexture != 0 ? loadTexture->m_textureSet : 0;
    AddSharedRef(m_textureSet);

    if (m_model != 0) {
        AttachTextureSet__Q26CChara6CModelFP11CTextureSet(m_model, m_textureSet);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::LoadModel(
    int charaKind, unsigned long charaNo, unsigned long textureVariant, unsigned long unusedArg, int mergeFileId,
    int mergeFlags, int specialModelStage)
{
    (void)unusedArg;

    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x8C9);
    PartMng.pppDeleteCHandle(this);

    ReleaseShared(m_model);
    ReleaseShared(m_textureSet);
    ReleaseShared(m_modelLoadRef);
    ReleaseShared(m_texLoadRef);
    ReleaseShared(m_pdtLoadRef);

    CharaPcs.releaseUnuseLoadModel(0);

    m_charaKind = charaKind;
    m_charaNo = static_cast<int>(charaNo);
    m_textureVariant = static_cast<int>(textureVariant);

    char basePath[0x100];
    char path[0x100];
    BuildCharaBasePath(charaKind, charaNo, basePath);

    CLoadModel* loadModel = 0;
    for (int i = 0; i < LoadModelArray(&CharaPcs)->GetSize(); i++) {
        CLoadModel* it = (*LoadModelArray(&CharaPcs))[static_cast<unsigned long>(i)];
        if (it != 0 && it->m_keyTag == reinterpret_cast<void*>(charaKind) && it->m_keyId == static_cast<int>(charaNo)) {
            loadModel = it;
            break;
        }
    }

    if (loadModel == 0) {
        strcpy(path, basePath);
        strcpy(path + strlen(path), s_charaModelSuffix);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle == 0) {
            return;
        }

        File.Read(fileHandle);
        File.SyncCompleted(fileHandle);

        loadModel = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
        if (loadModel != 0) {
            loadModel->m_keyTag = reinterpret_cast<void*>(charaKind);
            loadModel->m_keyId = static_cast<int>(charaNo);
            loadModel->m_mergeFileId = mergeFileId;
            loadModel->m_mergeFlags = mergeFlags;
            loadModel->m_model = reinterpret_cast<CChara::CModel*>(
                __nw__FUlPQ27CMemory6CStagePci(0x124, StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5F1));
            loadModel->m_streamMode = 0;
            loadModel->m_streamOffset = 0;
            loadModel->m_streamSize = 0;

            if (loadModel->m_model != 0) {
                loadModel->m_model = reinterpret_cast<CChara::CModel*>(__ct__Q26CChara6CModelFv(loadModel->m_model));
                Create__Q26CChara6CModelFPvPQ27CMemory6CStage(loadModel->m_model, File.m_readBuffer, HandleModelStage(charaKind, 0));
            }
            LoadModelArray(&CharaPcs)->Add(loadModel);
        }

        m_modelLoadRef = loadModel;
        AddSharedRef(m_modelLoadRef);
        m_model = loadModel != 0 ? loadModel->m_model : 0;
        AddSharedRef(m_model);

        strcpy(path, basePath);
        strcpy(path + strlen(path), s_charaDynamicsSuffix);
        fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);
            if (m_model != 0) {
                CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(m_model, File.m_readBuffer, HandleModelStage(charaKind, 0));
            }
            File.Close(fileHandle);
        }
    } else {
        m_modelLoadRef = loadModel;

        if (reinterpret_cast<int*>(loadModel)[1] == 1) {
            if (loadModel->m_streamOffset != 0) {
                File.LockBuffer();
                CopyFromAMemorySync__7CMemoryFPvPvUl(
                    &Memory, File.m_readBuffer,
                    reinterpret_cast<unsigned char*>(StageBase(StageAt(&CharaPcs, 0xC8))) +
                        reinterpret_cast<unsigned int>(loadModel->m_streamOffset),
                    static_cast<unsigned long>(loadModel->m_streamSize));
                loadModel->m_model = reinterpret_cast<CChara::CModel*>(
                    __nw__FUlPQ27CMemory6CStagePci(0x124, StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x7C7));
                if (loadModel->m_model != 0) {
                    loadModel->m_model = reinterpret_cast<CChara::CModel*>(__ct__Q26CChara6CModelFv(loadModel->m_model));
                    Create__Q26CChara6CModelFPvPQ27CMemory6CStage(
                        loadModel->m_model, File.m_readBuffer, HandleModelStage(charaKind, specialModelStage));
                }
                File.UnlockBuffer();
            }

            AddSharedRef(m_modelLoadRef);
            m_model = loadModel->m_model;
            AddSharedRef(m_model);
            if (m_model != 0) {
                Init__Q26CChara6CModelFv(m_model);
            }
        } else {
            AddSharedRef(m_modelLoadRef);
            m_model = loadModel->m_model != 0
                          ? reinterpret_cast<CChara::CModel*>(
                                Duplicate__Q26CChara6CModelFPQ27CMemory6CStage(
                                    loadModel->m_model, HandleModelStage(charaKind, specialModelStage)))
                          : 0;
        }
    }

    ChangeTexture(charaKind, charaNo, textureVariant, mergeFileId, mergeFlags);
    if (m_textureSet != 0 && m_textureSet->Find(const_cast<char*>(s_mogFurTextureName)) >= 0 && m_model != 0) {
        InitMogFurTex__Q26CChara6CModelFv(m_model);
    }

    if (CurrentSceneId() != 7 && charaKind == 1) {
        CLoadPdt* loadPdt = 0;
        for (int i = 0; i < LoadPdtArray(&CharaPcs)->GetSize(); i++) {
            CLoadPdt* it = (*LoadPdtArray(&CharaPcs))[static_cast<unsigned long>(i)];
            if (it != 0 && it->m_keyTag == reinterpret_cast<void*>(1) && it->m_keyId == static_cast<int>(charaNo) &&
                it->m_variantTag == reinterpret_cast<void*>(textureVariant)) {
                loadPdt = it;
                break;
            }
        }

        if (loadPdt == 0) {
            loadPdt = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x868) CLoadPdt;
            if (loadPdt != 0) {
                loadPdt->m_keyTag = reinterpret_cast<void*>(1);
                loadPdt->m_keyId = static_cast<int>(charaNo);
                loadPdt->m_variantTag = reinterpret_cast<void*>(textureVariant);
                loadPdt->m_mergeFileId = mergeFileId;
                loadPdt->m_mergeFlags = mergeFlags;
                loadPdt->m_pdtSlot = PartPcs.LoadMonsterPdt(static_cast<int>(charaNo), static_cast<int>(textureVariant), 0, 0, 0, 0);
                LoadPdtArray(&CharaPcs)->Add(loadPdt);
            }
        }

        m_pdtLoadRef = loadPdt;
        AddSharedRef(m_pdtLoadRef);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::LoadAnim(char*, int, int, int, int, int, int)
{
	// TODO
}

bool CCharaPcs::CHandle::IsModelLoaded(int checkModelField)
{
	if ((m_asyncState == 0 || m_asyncState == 7)
		&& m_model != nullptr
		// TODO: Pending CModel decomp
		&& (checkModelField == 0 || *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(m_model) + 0xB0) != 0))
	{
			return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::LoadAnim(int, int, char*, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::FreeModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::FreeAnim(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::SetAnim(int, int, int, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::Draw(int drawPass)
{
	unsigned int miniGameFlags = *reinterpret_cast<unsigned int*>(MiniGamePcs + 0x25732);
	if ((miniGameFlags & 0x8000) != 0) {
		if ((drawPass == 4) && ((m_flags & 0x10000) != 0)) {
			draw(3, 0);
		}
		draw(drawPass, (4U - drawPass | drawPass - 4U) >> 0x1F);
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::draw(int drawPass, int immediatePass)
{
    if (m_model == 0) {
        return;
    }

    const unsigned int flags = m_flags;
    if ((flags & 1) == 0 || (flags & 0x400000) != 0) {
        return;
    }
    if (drawPass == 1 && (flags & 0x40) != 0) {
        return;
    }
    if (drawPass == 2 && (flags & 0x200) == 0) {
        return;
    }
    if (drawPass == 0 && (flags & 0x4000) != 0) {
        return;
    }
    if (drawPass == 3 && (flags & 0x81C) == 0) {
        return;
    }
    if ((drawPass == 0 || drawPass == 4) && (flags & 0x10) != 0) {
        return;
    }

    if (immediatePass == 0 && drawPass == 0 && (flags & 0x40000) == 0) {
        ppvDrawMng.AddPrim(-m_sortZ, this);
        return;
    }

    Mtx viewMtx;
    PSMTXCopy(*reinterpret_cast<Mtx*>(Ptr(&CameraPcs, 4)), viewMtx);

    if (drawPass != 1 && drawPass != 2 && (flags & 0x200000) == 0) {
        const unsigned int lightBank = (flags >> 19) & 1;
        const float phase = m_colorPhase * 4.0f;
        int phaseIndex = static_cast<int>(phase);
        if (phaseIndex < 0) {
            phaseIndex = 0;
        }
        if (phaseIndex > 3) {
            phaseIndex = 3;
        }
        const float blendT = phase - static_cast<float>(phaseIndex);
        _GXColor* phaseColors = reinterpret_cast<_GXColor*>(Ptr(&CharaPcs, 0x12C));
        const _GXColor shade = BlendColor(phaseColors[phaseIndex], phaseColors[phaseIndex + 1], blendT);
        const _GXColor ambientBase = *reinterpret_cast<_GXColor*>(Ptr(&CharaPcs, 0xE8 + lightBank * 4));
        const _GXColor ambientColor = ModulateColor(ambientBase, shade);
        LightPcs.SetAmbient(ambientColor);

        for (unsigned long i = 0; i < 3; i++) {
            const _GXColor diffuseBase =
                *reinterpret_cast<_GXColor*>(Ptr(&CharaPcs, 0xF0 + lightBank * 0x0C + static_cast<unsigned int>(i) * 4));
            LightPcs.SetDiffuseColor(i, ModulateColor(diffuseBase, shade));
        }

        Vec lightPos;
        Mtx* modelMtx = ModelLocalMtx(m_model);
        lightPos.x = (*modelMtx)[0][3];
        lightPos.y = (*modelMtx)[1][3];
        lightPos.z = (*modelMtx)[2][3];
        LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), &lightPos, 0xFFFFFFFF);
    }

    if (drawPass == 3) {
        if ((flags & 4) != 0) {
            const float offsetY = 0.25f * (m_worldPosY - m_bgCharmPlaneY);
            viewMtx[0][3] += viewMtx[0][1] * offsetY;
            viewMtx[1][3] += viewMtx[1][1] * offsetY;
            viewMtx[2][3] += viewMtx[2][1] * offsetY;
            viewMtx[0][1] *= 0.5f;
            viewMtx[1][1] *= 0.5f;
            viewMtx[2][1] *= 0.5f;
        } else if ((flags & 8) != 0) {
            PSMTXConcat(viewMtx, reinterpret_cast<MtxPtr>(Ptr(&CFlat, 0x12B4)), viewMtx);
        }
    } else if (drawPass == 2) {
        Mtx* modelMtx = ModelLocalMtx(m_model);
        Vec modelPos;
        modelPos.x = (*modelMtx)[0][3];
        modelPos.y = (*modelMtx)[1][3];
        modelPos.z = (*modelMtx)[2][3];

        Vec focusPos = *reinterpret_cast<Vec*>(Ptr(&CharaPcs, 0x17C));
        Vec delta;
        PSVECSubtract(&focusPos, &modelPos, &delta);
        if (delta.x == 0.0f && delta.z == 0.0f) {
            return;
        }

        const float distance = PSVECMag(&delta);
        const float shadowRange = *reinterpret_cast<float*>(Ptr(&CharaPcs, 0x188));
        if (distance > shadowRange) {
            return;
        }

        PSVECNormalize(&delta, &delta);

        Vec up = {0.0f, 1.0f, 0.0f};
        Vec eye = modelPos;
        eye.y += 1.0f;

        Vec shadowPos;
        PSVECScale(&delta, &shadowPos, static_cast<float>(*reinterpret_cast<int*>(Ptr(&CharaPcs, 0x48))));
        PSVECAdd(&modelPos, &shadowPos, &shadowPos);
        shadowPos.y += 1.0f;

        C_MTXLookAt(m_shadowViewMtx, reinterpret_cast<Point3d*>(&shadowPos), &up, reinterpret_cast<Point3d*>(&eye));
        PSMTXCopy(m_shadowViewMtx, viewMtx);

        _GXColor shadowFog = *reinterpret_cast<_GXColor*>(Ptr(&CharaPcs, 0x18C));
        GXSetFog(GX_FOG_ORTHO_LIN, 0.0f, shadowRange, 0.0f, 512.0f, shadowFog);
    }

    bool restoreFog = false;
    if ((drawPass == 0 || drawPass == 4) && m_fogBlend > 0.0f) {
        _GXColor fogColor = *reinterpret_cast<_GXColor*>(Ptr(&CharaPcs, 0x18C));
        GXSetFog(GX_FOG_PERSP_LIN, m_fogBlend, m_fogBlend + 2.0f, 0.0f, 1024.0f, fogColor);
        restoreFog = true;
    }

    if (drawPass == 1 || drawPass == 2) {
        if (drawPass == 2) {
            const unsigned short shadowSize = static_cast<unsigned short>(*reinterpret_cast<int*>(Ptr(&CharaPcs, 0x44)));
            GXSetTexCopySrc(0, 0, shadowSize, shadowSize);
            GXSetTexCopyDst(shadowSize, shadowSize, GX_TF_I8, GX_FALSE);
            m_shadowTexturePtr = reinterpret_cast<unsigned char*>(*reinterpret_cast<void**>(Ptr(&CharaPcs, 0x140))) +
                                 *reinterpret_cast<unsigned int*>(Ptr(&CharaPcs, 0x148));
            DCInvalidateRange(m_shadowTexturePtr, (shadowSize * shadowSize) / 2);
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
        }

        const int shadowMode = __cntlzw(static_cast<unsigned int>(1 - drawPass)) >> 5;
        DrawShadow__Q26CChara6CModelFPA4_fi(m_model, viewMtx, shadowMode);

        if (drawPass == 2) {
            const unsigned int shadowBytes =
                (static_cast<unsigned int>(*reinterpret_cast<int*>(Ptr(&CharaPcs, 0x44))) *
                 static_cast<unsigned int>(*reinterpret_cast<int*>(Ptr(&CharaPcs, 0x44)))) /
                2;
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
            *reinterpret_cast<unsigned int*>(Ptr(&CharaPcs, 0x148)) += shadowBytes;
            GXPixModeSync();
        }
    } else {
        int modelDrawFlags = 0;
        if (drawPass == 3 && (flags & 0x0C) != 0) {
            modelDrawFlags |= 1;
        }
        if ((flags & 0x400) != 0) {
            modelDrawFlags |= 2;
        }
        if ((flags & 0x2000) != 0) {
            modelDrawFlags |= 4;
        }
        if (drawPass == 3 && (flags & 0x8000) != 0) {
            modelDrawFlags |= 8;
        }
        if ((flags & 0x100000) != 0) {
            modelDrawFlags |= 0x10;
        }
        Draw__Q26CChara6CModelFPA4_fii(m_model, viewMtx, modelDrawFlags, 0);
    }

    if (drawPass == 0 || drawPass == 4) {
        DrawFur__Q26CChara6CModelFPA4_fi(m_model, viewMtx, static_cast<int>((flags >> 23) & 1));
    }

    if (restoreFog) {
        SetFog__8CGraphicFii(&Graphic, 1, 0);
    }
}

/*
 * --INFO--
 * PAL Address: 8007435c
 * PAL Size: 572b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::LoadModelASync(int charaKind, unsigned long charaNo, unsigned long textureVariant)
{
    if (m_asyncFileHandle != 0)
	{
		File.Close(m_asyncFileHandle);
		m_asyncFileHandle = (CFile::CHandle*)0;
	}

	m_asyncState = 0;
	Graphic._WaitDrawDone((char*)"p_chara.cpp", 0x8C9);
	PartMng.pppDeleteCHandle(this);

	if (m_model != 0)
	{
		int* modelRef = reinterpret_cast<int*>(m_model);
		int refCount = modelRef[1] - 1;
		modelRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*modelRef + 8))(m_model, 1);
		}
		m_model = (CChara::CModel*)0;
	}

	if (m_textureSet != 0)
	{
		int* textureRef = reinterpret_cast<int*>(m_textureSet);
		int refCount = textureRef[1] - 1;
		textureRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*textureRef + 8))(m_textureSet, 1);
		}
		m_textureSet = (CTextureSet*)0;
	}

	if (m_modelLoadRef != 0)
	{
		int* modelLoadRef = reinterpret_cast<int*>(m_modelLoadRef);
		int refCount = modelLoadRef[1] - 1;
		modelLoadRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*modelLoadRef + 8))(m_modelLoadRef, 1);
		}
		m_modelLoadRef = (CRef*)0;
	}

	if (m_texLoadRef != 0)
	{
		int* texLoadRef = reinterpret_cast<int*>(m_texLoadRef);
		int refCount = texLoadRef[1] - 1;
		texLoadRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*texLoadRef + 8))(m_texLoadRef, 1);
		}
		m_texLoadRef = (CRef*)0;
	}

	if (m_pdtLoadRef != 0)
	{
		int* pdtLoadRef = reinterpret_cast<int*>(m_pdtLoadRef);
		int refCount = pdtLoadRef[1] - 1;
		pdtLoadRef[1] = refCount;
		if (refCount == 0)
		{
			(*(void (**)(void*, int))(*pdtLoadRef + 8))(m_pdtLoadRef, 1);
		}
		m_pdtLoadRef = (CRef*)0;
	}

	CharaPcs.releaseUnuseLoadModel(0);
	m_asyncCharaKind = charaKind;
	m_asyncCharaNo = static_cast<int>(charaNo);
	m_asyncTextureVariant = static_cast<int>(textureVariant);
	m_asyncState = 1;
	loadModelASyncFrame();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::loadModelASyncFrame()
{
    char basePath[0x100];
    char path[0x100];
    const int asyncState = m_asyncState;

    if (asyncState == 1 || asyncState == 3 || asyncState == 5) {
        BuildCharaBasePath(m_asyncCharaKind, static_cast<unsigned long>(m_asyncCharaNo), basePath);
        if (m_asyncState == 1) {
            strcpy(path, basePath);
            strcpy(path + strlen(path), s_charaModelSuffix);
        } else if (m_asyncState == 3) {
            strcpy(path, basePath);
            strcpy(path + strlen(path), s_charaDynamicsSuffix);
        } else {
            if (m_asyncTextureVariant < 1) {
                strcpy(path, basePath);
            } else {
                sprintf(path, s_charaTextureVariantFmt, basePath, m_asyncTextureVariant + 0x61);
            }
            strcpy(path + strlen(path), s_charaTextureSuffix);
        }

        m_asyncFileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (m_asyncFileHandle == 0 && m_asyncState == 3) {
            m_asyncState = 5;
            loadModelASyncFrame();
            return;
        }
        if (m_asyncFileHandle != 0) {
            File.ReadASync(m_asyncFileHandle);
        }
        m_asyncState++;
        return;
    }

    if ((asyncState != 2 && asyncState != 4 && asyncState != 6) || m_asyncFileHandle == 0 ||
        !File.IsCompleted(m_asyncFileHandle)) {
        return;
    }

    if (m_asyncState == 2) {
        CLoadModel* loadModel = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
        if (loadModel != 0) {
            loadModel->m_keyTag = reinterpret_cast<void*>(m_asyncCharaKind);
            loadModel->m_keyId = m_asyncCharaNo;
            loadModel->m_mergeFileId = -1;
            loadModel->m_mergeFlags = 0;
            loadModel->m_model = reinterpret_cast<CChara::CModel*>(
                __nw__FUlPQ27CMemory6CStagePci(0x124, StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5F1));
            loadModel->m_streamMode = 0;
            loadModel->m_streamOffset = 0;
            loadModel->m_streamSize = 0;
            if (loadModel->m_model != 0) {
                loadModel->m_model = reinterpret_cast<CChara::CModel*>(__ct__Q26CChara6CModelFv(loadModel->m_model));
                Create__Q26CChara6CModelFPvPQ27CMemory6CStage(
                    loadModel->m_model, File.m_readBuffer, HandleModelStage(m_asyncCharaKind, 0));
            }
            LoadModelArray(&CharaPcs)->Add(loadModel);
            m_modelLoadRef = loadModel;
            AddSharedRef(m_modelLoadRef);
            m_model = loadModel->m_model;
            AddSharedRef(m_model);
            m_charaKind = m_asyncCharaKind;
            m_charaNo = m_asyncCharaNo;
        }
    } else if (m_asyncState == 4) {
        if (m_model != 0) {
            CreateDynamics__Q26CChara6CModelFPvPQ27CMemory6CStage(m_model, File.m_readBuffer, HandleModelStage(m_asyncCharaKind, 0));
        }
    } else {
        CLoadTexture* loadTexture = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
        if (loadTexture != 0) {
            loadTexture->m_keyTag = reinterpret_cast<void*>(m_asyncCharaKind);
            loadTexture->m_keyId = m_asyncCharaNo;
            loadTexture->m_mergeFileId = -1;
            loadTexture->m_mergeFlags = 0;
            loadTexture->m_variantTag = reinterpret_cast<void*>(m_asyncTextureVariant);
            loadTexture->m_textureSet = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
            loadTexture->m_streamMode = 0;
            loadTexture->m_streamOffset = 0;
            loadTexture->m_streamSize = 0;
            if (loadTexture->m_textureSet != 0) {
                loadTexture->m_textureSet->Create(File.m_readBuffer, HandleTextureStage(m_asyncCharaKind), 0, 0, 0, 0);
            }
            LoadTextureArray(&CharaPcs)->Add(loadTexture);
            m_texLoadRef = loadTexture;
            AddSharedRef(m_texLoadRef);
            m_textureSet = loadTexture->m_textureSet;
            AddSharedRef(m_textureSet);
            AttachTextureSet__Q26CChara6CModelFP11CTextureSet(m_model, m_textureSet);
            m_textureVariant = m_asyncTextureVariant;
        }
    }

    File.Close(m_asyncFileHandle);
    m_asyncFileHandle = 0;
    if (m_asyncState == 6) {
        m_asyncState = 7;
    } else {
        m_asyncState++;
        loadModelASyncFrame();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
bool CCharaPcs::CHandle::IsLoadModelASyncCompleted()
{
    if (m_asyncState == 7)
	{
		return true;
	}

	return false;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::CancelLoadModelASync()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::CLoadModel()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::~CLoadModel()
{
    void* model = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x18);
    if (model != 0) {
        int* refData = reinterpret_cast<int*>(model);
        int refCount = refData[1] - 1;
        refData[1] = refCount;
        if (refCount == 0) {
            (*(void (**)(void*, int))(*refData + 8))(model, 1);
        }
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x18) = 0;
    }

    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim::CLoadAnim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim::~CLoadAnim()
{
    void* anim = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x28);
    if (anim != 0) {
        int* refData = reinterpret_cast<int*>(anim);
        int refCount = refData[1] - 1;
        refData[1] = refCount;
        if (refCount == 0) {
            (*(void (**)(void*, int))(*refData + 8))(anim, 1);
        }
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x28) = 0;
    }

    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::CLoadTexture()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::~CLoadTexture()
{
    void* texture = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x1C);
    if (texture != 0) {
        int* refData = reinterpret_cast<int*>(texture);
        int refCount = refData[1] - 1;
        refData[1] = refCount;
        if (refCount == 0) {
            (*(void (**)(void*, int))(*refData + 8))(texture, 1);
        }
        *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(this) + 0x1C) = 0;
    }

    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::CLoadPdt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::~CLoadPdt()
{
    int& pdtSlot = *reinterpret_cast<int*>(reinterpret_cast<unsigned char*>(this) + 0x14);
    if (pdtSlot >= 0) {
        ReleasePdt__8CPartPcsFi(&PartPcs, pdtSlot);
        pdtSlot = -1;
    }

    __dt__4CRefFv(this, 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::GetAnimStage()
{
	// TODO
}
