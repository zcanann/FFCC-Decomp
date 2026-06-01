#define FFCC_P_CHARA_DEFINE_LAYOUT
#include "ffcc/p_chara.h"
#include "ffcc/chunkfile.h"
#include "ffcc/color.h"
#include "ffcc/game.h"
#include "ffcc/graphic.h"
#include "ffcc/gxfunc.h"
#include "ffcc/linkage.h"
#include "ffcc/map.h"
#include "ffcc/memory.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_dbgmenu.h"
#include "ffcc/partMng.h"
#include "ffcc/p_light.h"
#include "ffcc/p_tina.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/ref.h"
#include "ffcc/sound.h"
#include "ffcc/textureman.h"
#include "ffcc/util.h"
#include "ffcc/vector.h"
extern "C" {
extern u8* gCharaPartWorkPtr;
}

extern const float FLOAT_80330288;
extern const float FLOAT_8033028c;
extern const float FLOAT_8033030C;
extern const float FLOAT_80330310;
extern const float FLOAT_80330314;
extern const float FLOAT_80330318;
extern const float FLOAT_8033031C;
extern const float FLOAT_80330320;

#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

CCharaPcs CharaPcs;

extern "C" {
u8* gCharaPartWorkPtr = 0;
}

extern "C" void create__9CCharaPcsFv(CCharaPcs*);
extern "C" void destroy__9CCharaPcsFv(CCharaPcs*);
extern "C" void calc__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawBefore__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawShadow__9CCharaPcsFv(CCharaPcs*);
extern "C" void draw__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawOverlap__9CCharaPcsFv(CCharaPcs*);
extern "C" void calcAfter__9CCharaPcsFv(CCharaPcs*);
extern "C" void createViewer__9CCharaPcsFv(CCharaPcs*);
extern "C" void destroyViewer__9CCharaPcsFv(CCharaPcs*);
extern "C" void calcViewer__9CCharaPcsFv(CCharaPcs*);
extern "C" void drawViewer__9CCharaPcsFv(CCharaPcs*);

static const char s_CCharaPcs_GAME[] = "CCharaPcs GAME";
static const char s_CCharaPcs_VIEWER[] = "CCharaPcs VIEWER";
static const char s_CCharaPcs_PART[] = "CCharaPcs PART";

static unsigned int s_charaTableDescCreate[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CCharaPcsFv)};
static unsigned int s_charaTableDescDestroy[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CCharaPcsFv)};
static unsigned int s_charaTableDescCalc[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CCharaPcsFv)};
static unsigned int s_charaTableDescDrawBefore[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawBefore__9CCharaPcsFv)};
static unsigned int s_charaTableDescDrawShadow[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadow__9CCharaPcsFv)};
static unsigned int s_charaTableDescDraw[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CCharaPcsFv)};
static unsigned int s_charaTableDescDrawOverlap[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawOverlap__9CCharaPcsFv)};
static unsigned int s_charaTableDescCalcAfter[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcAfter__9CCharaPcsFv)};
static unsigned int s_charaTableDescCreateViewer[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__9CCharaPcsFv)};
static unsigned int s_charaTableDescDestroyViewer[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroyViewer__9CCharaPcsFv)};
static unsigned int s_charaTableDescCalcViewer[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__9CCharaPcsFv)};
static unsigned int s_charaTableDescDrawViewer[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__9CCharaPcsFv)};
static unsigned int s_charaTableDescViewerCalcAfter[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcAfter__9CCharaPcsFv)};
static unsigned int s_charaTableDescPartCreate[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(create__9CCharaPcsFv)};
static unsigned int s_charaTableDescPartDestroy[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__9CCharaPcsFv)};
static unsigned int s_charaTableDescPartCalc[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calc__9CCharaPcsFv)};
static unsigned int s_charaTableDescPartDraw[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(draw__9CCharaPcsFv)};
static unsigned int s_charaTableDescPartCalcAfter[3] = {0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcAfter__9CCharaPcsFv)};

extern "C" CProcessTable PTR_s_CCharaPcs_GAME_[3] = {
    {
        const_cast<char*>(s_CCharaPcs_GAME),
        {
            s_charaTableDescCreate[0], s_charaTableDescCreate[1], s_charaTableDescCreate[2],
            s_charaTableDescDestroy[0], s_charaTableDescDestroy[1], s_charaTableDescDestroy[2],
            s_charaTableDescCalc[0], s_charaTableDescCalc[1], s_charaTableDescCalc[2],
            0x1F, 0,
            s_charaTableDescDrawBefore[0], s_charaTableDescDrawBefore[1], s_charaTableDescDrawBefore[2],
            0x36, 1,
            s_charaTableDescDrawShadow[0], s_charaTableDescDrawShadow[1], s_charaTableDescDrawShadow[2],
            0x30, 1,
            s_charaTableDescDraw[0], s_charaTableDescDraw[1], s_charaTableDescDraw[2],
            0x3B, 1,
            s_charaTableDescDrawOverlap[0], s_charaTableDescDrawOverlap[1], s_charaTableDescDrawOverlap[2],
            0x46, 1,
            s_charaTableDescCalcAfter[0], s_charaTableDescCalcAfter[1], s_charaTableDescCalcAfter[2],
            0x4D, 8,
        },
    },
    {
        const_cast<char*>(s_CCharaPcs_VIEWER),
        {
            s_charaTableDescCreateViewer[0], s_charaTableDescCreateViewer[1], s_charaTableDescCreateViewer[2],
            s_charaTableDescDestroyViewer[0], s_charaTableDescDestroyViewer[1], s_charaTableDescDestroyViewer[2],
            s_charaTableDescCalcViewer[0], s_charaTableDescCalcViewer[1], s_charaTableDescCalcViewer[2],
            0x1F, 0,
            s_charaTableDescDrawViewer[0], s_charaTableDescDrawViewer[1], s_charaTableDescDrawViewer[2],
            0x3B, 1,
            s_charaTableDescViewerCalcAfter[0], s_charaTableDescViewerCalcAfter[1],
            s_charaTableDescViewerCalcAfter[2],
            0x4D, 0,
        },
    },
    {
        const_cast<char*>(s_CCharaPcs_PART),
        {
            s_charaTableDescPartCreate[0], s_charaTableDescPartCreate[1], s_charaTableDescPartCreate[2],
            s_charaTableDescPartDestroy[0], s_charaTableDescPartDestroy[1], s_charaTableDescPartDestroy[2],
            s_charaTableDescPartCalc[0], s_charaTableDescPartCalc[1], s_charaTableDescPartCalc[2],
            0x1F, 0,
            s_charaTableDescPartDraw[0], s_charaTableDescPartDraw[1], s_charaTableDescPartDraw[2],
            0x3B, 1,
            s_charaTableDescPartCalcAfter[0], s_charaTableDescPartCalcAfter[1], s_charaTableDescPartCalcAfter[2],
            0x4D, 0,
        },
    },
};

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

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
static const char s_charaFreeMergeFmt[] = "CCharaPcs.FreeMergeFile: 0x%08x\n";
static const char s_charaAmemCompactFailed[] =
    "\x83\x4b\x83\x78\x81\x5b\x83\x57\x83\x52\x83\x8c\x83\x4e\x83\x56\x83\x87"
    "\x83\x93\x82\xc9\x8e\xb8\x94\x73\x82\xb5\x82\xbd\x82\xcc\x82\xc5\x81\x41"
    "\x91\x53\x82\xc4\x8f\xc1\x8b\x8e\x82\xb5\x82\xdc\x82\xb7\x81\x42\n";
static const char s_charaBasePathFmt[] = "dvd/char/%s/%s%03d/%s%03d%s";
static const char s_charaAnimPathFmt[] = "dvd/char/k%02d/chara%03d/%s.cha";
static const char s_charaModelSuffix[] = ".mdl";
static const char s_charaDynamicsSuffix[] = ".dyn";
static const char s_charaTextureSuffix[] = ".tex";
static const char s_charaTextureVariantFmt[] = "%s_%c";
static const char s_mogFurTextureName[] = "mog_hair";
static const char s_charaSetAnimMissingFmt[] = "CCharaPcs missing anim %d %d %d\n";
static const char s_charaLoadAnimLogFmt[] = "CCharaPcs LoadAnim %s %d %d\n";
static const char s_charaReleaseAnimBankFmt[] = "bank release %d %s\n";
static const char s_charaAsyncCancelFmt[] =
    "\x83\x82\x83\x66\x83\x8b\x94\xf1\x93\xaf\x8a\xfa\x93\xc7\x82\xdd"
    "\x8d\x9e\x82\xdd\x92\x86\x82\xc9\x83\x4c\x83\x83\x83\x93\x83\x5a"
    "\x83\x8b\x82\xb3\x82\xea\x82\xdc\x82\xb5\x82\xbd\x81\x42\n";
static const char s_charaAsyncCompleteFmt[] =
    "\x94\xf1\x93\xaf\x8a\xfa\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x8a\xae"
    "\x97\xb9\n";
static const char s_charaAsyncEntryFmt[] =
    "\x94\xf1\x93\xaf\x8a\xfa\x93\xc7\x82\xdd\x8d\x9e\x82\xdd\x83\x47"
    "\x83\x93\x83\x67\x83\x8a\x81\x5b\n";
static const char s_charaDumpModelHdr1[] = "MODEL\n";
static const char s_charaDumpModelHdr2[] = " no t num lv mask addr a? a_addr a_size\n";
static const char s_charaDumpLineSep[] = "----------------------------------------\n";
static const char s_charaDumpModelFmt[] = "%3d %1d %3d %3d %08x %08x %d %08x %08x\n";
static const char s_charaDumpTextureHdr1[] = "TEXTURE\n";
static const char s_charaDumpTextureHdr2[] = " no t num t lv mask addr a? a_addr a_size\n";
static const char s_charaDumpTextureFmt[] = "%3d %1d %3d %1d %3d %08x %08x %d %08x %08x\n";
static const char s_charaDumpPdtHdr1[] = "PDT\n";
static const char s_charaDumpPdtHdr2[] = " no t num t pdt hdl lv mask\n";
static const char s_charaDumpPdtFmt[] = "%3d %1d %3d %1d %8d %3d %08x\n";
static const char s_charaDumpAnimHdr1[] = "ANIM\n";
static const char s_charaDumpAnimHdr2[] = " no t num name lv mask addr banksz sum bankaddr\n";
static const char s_charaDumpAnimFmt[] = "%3d %1d %3d %-14s %3d %08x %08x %d %08x\n";
static char s_p_chara_collection_ptrarray_h[] = "collection_ptrarray.h";
static char s_p_chara_ptrarray_grow_error[] = "CPtrArray grow error";
static const char s_charaKindPath0[] = "k00";
static const char s_charaKindPath1[] = "k01";
static const char s_charaKindPath2[] = "k02";
static const char s_charaKindPath3[] = "k03";
static const char s_charaKindPath4[] = "k04";
static const char s_charaKindPath5[] = "k05";
static const char s_charaKindFile[] = "chara";
static const char s_charaKindSuffix[] = "";
static const char* s_charaKindPathParts[][3] = {
    {s_charaKindPath0, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath1, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath2, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath3, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath4, s_charaKindFile, s_charaKindSuffix},
    {s_charaKindPath5, s_charaKindFile, s_charaKindSuffix},
};

#pragma dont_inline on

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

template <class T>
CPtrArray<T>::~CPtrArray()
{
    if (m_items != 0) {
        delete[] m_items;
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
    for (unsigned int i = 0; i < (unsigned int)m_numItems; i++) {
        T item = m_items[i];
        if (item != 0) {
            CRef* ref = reinterpret_cast<CRef*>(item);
            if (ref->DecRef() == 0) {
                delete ref;
            }
            m_items[i] = 0;
        }
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
                System.Printf(s_p_chara_ptrarray_grow_error);
            }
            m_size = m_size << 1;
        }

        newItems = static_cast<T*>(
            Memory._Alloc(static_cast<unsigned long>(m_size << 2), m_stage, s_p_chara_collection_ptrarray_h, 0xFA, 0));
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

template <class T>
T CPtrArray<T>::GetAt(unsigned long index)
{
    return m_items[index];
}

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

template class CPtrArray<CCharaPcs::CLoadPdt*>;
template class CPtrArray<CCharaPcs::CLoadTexture*>;
template class CPtrArray<CCharaPcs::CLoadAnim*>;
template class CPtrArray<CCharaPcs::CLoadModel*>;

STATIC_ASSERT(sizeof(CCharaPcs::CLoadModel) == 0x28);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadAnim) == 0x30);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadTexture) == 0x2C);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadPdt) == 0x20);

#pragma dont_inline reset

namespace {
static inline unsigned char* Ptr(void* p, unsigned int offset)
{
    return reinterpret_cast<unsigned char*>(p) + offset;
}

static inline CPtrArray<CCharaPcs::CLoadModel*>* LoadModelArray(CCharaPcs* self)
{
    return &self->m_loadModels;
}

static inline CPtrArray<CCharaPcs::CLoadAnim*>* LoadAnimArray(CCharaPcs* self)
{
    return &self->m_loadAnims;
}

static inline CPtrArray<CCharaPcs::CLoadTexture*>* LoadTextureArray(CCharaPcs* self)
{
    return &self->m_loadTextures;
}

static inline CPtrArray<CCharaPcs::CLoadPdt*>* LoadPdtArray(CCharaPcs* self)
{
    return &self->m_loadPdts;
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
    return self->m_handleList;
}

static inline u32& FreeMergeMask(CCharaPcs* self)
{
    return self->m_noFreeMergeMask;
}

static inline int& LoadStageMode(CCharaPcs* self)
{
    return self->m_charaAllocStage;
}

static inline u32& LoadStreamCursor(CCharaPcs* self)
{
    return self->m_loadStreamCursor;
}

static inline u32 CurrentSceneId()
{
    return Game.m_currentSceneId;
}

static inline u32& CharaAmemSize()
{
    return Chara.AmemSize();
}

static inline void SetupBaseCharaLights(CCharaPcs* self)
{
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    Graphic.SetFog(1, 0);
    LightPcs.SetAmbient(self->m_viewerAmbientColor[0]);
    LightPcs.SetNumDiffuse(3);

    for (unsigned long lightIndex = 0; lightIndex < 3; lightIndex++) {
        LightPcs.SetDiffuse(lightIndex, self->m_viewerDiffuseColor[0][lightIndex],
                            &self->m_viewerDiffusePos[lightIndex], static_cast<int>(lightIndex == 2));
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
static inline void ReleaseSharedNonNull(T* ptr)
{
    CRef* ref = reinterpret_cast<CRef*>(ptr);
    if (ref->DecRef() == 0) {
        delete ref;
    }
}

template <typename T>
static inline void ReleaseShared(T*& ptr)
{
    if (ptr != 0) {
        ReleaseSharedNonNull(ptr);
        ptr = 0;
    }
}

template <typename T>
static inline void AddSharedRef(T* ptr)
{
    if (ptr != 0) {
        reinterpret_cast<CRef*>(ptr)->AddRef();
    }
}

static inline CCharaPcs::CLoadAnim* FindLoadedAnim(CCharaPcs* self, int charaKind, int charaNo, const char* animName)
{
    for (int i = 0; i < LoadAnimArray(self)->GetSize(); i++) {
        CCharaPcs::CLoadAnim* loadAnim = (*LoadAnimArray(self))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_keyTag != reinterpret_cast<void*>(charaKind) || loadAnim->m_keyId != charaNo) {
            continue;
        }

        if (strcmp(loadAnim->m_name, animName) == 0) {
            return loadAnim;
        }
    }

    return 0;
}

static CCharaPcs::CLoadAnim* LoadAnimFromDisk(
    CCharaPcs* self, int charaKind, int charaNo, const char* animName, int mergeFileId, int mergeFlags)
{
    char path[0x100];
    sprintf(path, s_charaAnimPathFmt, charaKind, charaNo, animName);

    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
    if (fileHandle == 0) {
        return 0;
    }

    File.Read(fileHandle);
    File.SyncCompleted(fileHandle);

    CChara::CAnim* anim = new (StageAt(self, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x62A) CChara::CAnim;
    if (anim != 0) {
        anim->Create(File.m_readBuffer, StageAt(self, 0xD4));
    }

    CCharaPcs::CLoadAnim* loadAnim = new (StageAt(self, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x62D) CCharaPcs::CLoadAnim;
    if (loadAnim != 0) {
        loadAnim->m_keyTag = reinterpret_cast<void*>(charaKind);
        loadAnim->m_keyId = charaNo;
        loadAnim->m_mergeFileId = mergeFileId;
        loadAnim->m_mergeFlags = mergeFlags;
        strcpy(loadAnim->m_name, animName);
        loadAnim->m_anim = anim;
        LoadAnimArray(self)->Add(loadAnim);
    }

    File.Close(fileHandle);

    if (loadAnim != 0 && System.m_execParam != 0) {
        System.Printf(const_cast<char*>(s_charaLoadAnimLogFmt), animName, charaKind, charaNo);
    }

    return loadAnim;
}

static inline void ReleaseHandleAnimSlot(CCharaPcs::CHandle* handle, int slot)
{
    CRef* animRef = handle->m_animSlot[slot];
    if (animRef != 0) {
        ReleaseSharedNonNull(animRef);
        handle->m_animSlot[slot] = 0;
    }
}

static inline void PruneUnsharedAnimRefs(CCharaPcs* self, CCharaPcs::CLoadAnim* target)
{
    for (int i = LoadAnimArray(self)->GetSize() - 1; i >= 0; i--) {
        CCharaPcs::CLoadAnim* loadAnim = (*LoadAnimArray(self))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_mergeFileId >= 0 || loadAnim->GetRef() != 1) {
            continue;
        }
        if (target != 0 && loadAnim != target) {
            continue;
        }

        CCharaPcs::CLoadAnim* releasedAnim = loadAnim;
        ReleaseSharedNonNull(releasedAnim);
        LoadAnimArray(self)->RemoveAt(static_cast<unsigned long>(i));
    }
}

static inline void BuildCharaBasePath(int charaKind, unsigned long charaNo, char* outPath)
{
    const char** pathParts = s_charaKindPathParts[charaKind];
    sprintf(outPath, s_charaBasePathFmt, pathParts[0], pathParts[1], static_cast<int>(charaNo), pathParts[1],
            static_cast<int>(charaNo), pathParts[2]);
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
    switch (stageIndex) {
    case 1:
        return MapMng.m_stage;
    case 2:
        return PartPcs.m_usbStreamData.m_stageLoad;
    case 3:
        return PartMng.m_pppEnvSt.m_stagePtr;
    case 4:
        return *reinterpret_cast<CMemory::CStage**>(reinterpret_cast<unsigned char*>(&CharaPcs) + 0xd4);
    default:
        return stage;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CCharaPcs()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::~CCharaPcs()
{
}

/*
 * --INFO--
 * PAL Address: 0x8007a51c
 * PAL Size: 1124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::Init()
{
    m_stage = Memory.CreateStage(0x38000, const_cast<char*>(s_CCharaPcs_stage), 0);
    m_amemStage = Memory.CreateStage(0x380000, const_cast<char*>(s_CCharaPcs_amem), 2);
    m_amemWorkStage = Memory.CreateStage(0x70000, const_cast<char*>(s_CCharaPcs_amemw), 2);
    Chara.SetAmemStage(m_amemStage);

    LoadModelArray(this)->SetStage(m_stage);
    LoadModelArray(this)->SetDefaultSize(0x80);
    LoadModelArray(this)->SetGrow(0);

    LoadAnimArray(this)->SetStage(m_stage);
    LoadAnimArray(this)->SetDefaultSize(0x200);
    LoadAnimArray(this)->SetGrow(0);

    LoadTextureArray(this)->SetStage(m_stage);
    LoadTextureArray(this)->SetDefaultSize(0x100);
    LoadTextureArray(this)->SetGrow(0);

    LoadPdtArray(this)->SetStage(m_stage);
    LoadPdtArray(this)->SetDefaultSize(0x80);
    LoadPdtArray(this)->SetGrow(0);

    for (int i = 0; i < 2; i++) {
        _GXColor& ambientColor = m_viewerAmbientColor[i];
        ambientColor.r = 0x3F;
        ambientColor.g = 0x3F;
        ambientColor.b = 0x3F;
        ambientColor.a = 0xFF;

        for (int lightIndex = 0; lightIndex < 3; lightIndex++) {
            _GXColor& lightColor = m_viewerDiffuseColor[i][lightIndex];
            const unsigned char intensity = static_cast<unsigned char>(lightIndex == 0 ? 0x3F : 0x00);
            lightColor.r = intensity;
            lightColor.g = intensity;
            lightColor.b = intensity;
            lightColor.a = 0xFF;
        }
    }

    m_viewerDiffusePos[0].x = 0.0f;
    m_viewerDiffusePos[0].y = 0.0f;
    m_viewerDiffusePos[0].z = 1.0f;
    m_viewerDiffusePos[1].x = 0.0f;
    m_viewerDiffusePos[1].y = 0.0f;
    m_viewerDiffusePos[1].z = 1.0f;
    m_viewerDiffusePos[2].x = 0.0f;
    m_viewerDiffusePos[2].y = 0.0f;
    m_viewerDiffusePos[2].z = 1.0f;

    for (int i = 0; i < 5; i++) {
        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        CColor shade;

        float scale = static_cast<float>(i) * 0.25f;
        shade.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.r) * scale));
        shade.color.g = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.g) * scale));
        shade.color.b = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.b) * scale));
        shade.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.a) * scale));
        CColor shadeCopy(shade);

        m_viewerChoiceColor[i].color.r = shadeCopy.color.r;
        m_viewerChoiceColor[i].color.g = shadeCopy.color.g;
        m_viewerChoiceColor[i].color.b = shadeCopy.color.b;
        m_viewerChoiceColor[i].color.a = shadeCopy.color.a;
    }

    m_charaAllocStage = 0;
    m_overlapEnabled = 0;
    CColor baseColor(0x00, 0x00, 0x40, 0x40);
    m_texShadowColor = baseColor.color;

    CVector baseVec(0.0f, 10.0f, 0.0f);
    Vec* constructedVec = reinterpret_cast<Vec*>(&baseVec);
    m_texShadowPos.x = constructedVec->x;
    m_texShadowPos.y = constructedVec->y;
    m_texShadowPos.z = constructedVec->z;
    m_texShadowRadius = 120.0f;
    m_texShadowSize = 0x80;
    m_texShadowDistance = 100;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::Quit()
{
    CharaAmemSize() = 0;
    Memory.DestroyStage(m_amemWorkStage);
    Memory.DestroyStage(m_amemStage);
    Memory.DestroyStage(m_stage);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::GetTable(unsigned long index)
{
    return reinterpret_cast<int>(&PTR_s_CCharaPcs_GAME_[index]);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::create()
{
    FreeMergeMask(this) = 0;

    StageAt(this, 0xCC) = Memory.CreateStage(0x177000, const_cast<char*>(s_CCharaPcs_loadModel), 0);
    StageAt(this, 0xD0) = Memory.CreateStage(0x130000, const_cast<char*>(s_CCharaPcs_loadTex), 0);
    StageAt(this, 0xD8) = Memory.CreateStage(0x8400, const_cast<char*>(s_CCharaPcs_loadWepTex), 0);
    StageAt(this, 0xDC) = Memory.CreateStage(0x18000, const_cast<char*>(s_CCharaPcs_loadWepModel), 0);
    StageAt(this, 0xE0) = Memory.CreateStage(0x10000, const_cast<char*>(s_CCharaPcs_loadFaModel), 0);
    StageAt(this, 0xD4) =
        Memory.CreateStage((s32)CurrentSceneId() == 4 ? 0x190000UL : 0x1E0000UL, const_cast<char*>(s_CCharaPcs_loadAnim), 0);

    CHandle* sentinel = reinterpret_cast<CHandle*>(
        Memory._Alloc(0x194, StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0xDB, 0));
    if (sentinel != 0) {
        sentinel->m_previous = 0;
        sentinel->m_next = 0;
        sentinel->m_model = 0;
        sentinel->m_textureSet = 0;
        sentinel->m_modelLoadRef = 0;
        sentinel->m_texLoadRef = 0;

        for (int i = 0; i < 64; i++) {
            sentinel->m_animSlot[i] = 0;
        }

        sentinel->m_pdtLoadRef = 0;
        sentinel->m_currentAnimIndex = -1;
        sentinel->m_flags = 0;
        sentinel->m_colorPhase = FLOAT_8033028c;
        sentinel->m_sortZ = FLOAT_80330288;
        sentinel->m_shadowTexturePtr = 0;
        sentinel->m_asyncState = 0;
        sentinel->m_asyncFileHandle = 0;
        sentinel->m_fogBlend = FLOAT_80330288;
        sentinel->m_unk0x158 = 0;
        sentinel->m_drawListFlags = static_cast<unsigned char>(__rlwimi(sentinel->m_drawListFlags, 1, 7, 24, 24));
    }

    HandleListHead(this) = sentinel;
    HandleListHead(this)->m_previous = HandleListHead(this);
    HandleListHead(this)->m_next = HandleListHead(this);

    for (int i = 0; i < 4; i++) {
        CameraCountAt(this, i) = 0;
        CameraDataAt(this, i) = 0;
    }

    CLightPcs::CBumpLight bumpLight;

    bumpLight.m_type = 1;
    bumpLight.m_position.x = FLOAT_8033030C;
    bumpLight.m_position.y = FLOAT_80330310;
    bumpLight.m_position.z = FLOAT_80330314;
    bumpLight.m_targetPosition.x = FLOAT_80330318;
    bumpLight.m_targetPosition.y = FLOAT_8033031C;
    bumpLight.m_targetPosition.z = FLOAT_80330320;
    PSVECSubtract(reinterpret_cast<Vec*>(&bumpLight.m_targetPosition), reinterpret_cast<Vec*>(&bumpLight.m_position),
                  reinterpret_cast<Vec*>(&bumpLight.m_direction));
    PSVECNormalize(reinterpret_cast<Vec*>(&bumpLight.m_direction), reinterpret_cast<Vec*>(&bumpLight.m_direction));
    bumpLight.m_bumpShade[0] = 0x80;
    bumpLight.m_bumpShade[1] = 0x80;
    bumpLight.m_bumpShade[2] = 0x00;
    bumpLight.m_bumpShade[3] = 0xFF;
    bumpLight.m_offsetX = FLOAT_80330288;
    bumpLight.m_offsetZ = FLOAT_80330288;

    gCharaPartWorkPtr = reinterpret_cast<u8*>(LightPcs.AddBump(
        &bumpLight, static_cast<CLightPcs::TARGET>(0), Chara.GetMemoryStage(), 4));
    Chara.Create();
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
    CharaPcs.m_loadStreamCursor = 0;
    Memory.DefaultGroup() = 2;
    CharaPcs.LoadMergeFile(0, 0x10000000, 1);
    Memory.DefaultGroup() = 0;
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
    LightPcs.DestroyBumpLightAll(static_cast<CLightPcs::TARGET>(0));
    gCharaPartWorkPtr = 0;

    if (m_handleList != 0) {
        delete m_handleList;
        m_handleList = 0;
    }

    Memory.DestroyStage(StageAt(this, 0xCC));
    Memory.DestroyStage(StageAt(this, 0xD0));
    Memory.DestroyStage(StageAt(this, 0xD8));
    Memory.DestroyStage(StageAt(this, 0xDC));
    Memory.DestroyStage(StageAt(this, 0xE0));
    Memory.DestroyStage(StageAt(this, 0xD4));
    Chara.Destroy();
}

/*
 * --INFO--
 * PAL Address: 0x80079d9c
 * PAL Size: 568b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::Reset(CCharaPcs::RESET mode)
{
    const int resetMode = static_cast<int>(mode);

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        unsigned char* loadAnim = reinterpret_cast<unsigned char*>((*LoadAnimArray(this))[static_cast<unsigned long>(i)]);
        unsigned char* anim = *reinterpret_cast<unsigned char**>(loadAnim + 0x28);
        if (*reinterpret_cast<void**>(anim + 0x20) != 0) {
            operator delete(*reinterpret_cast<void**>(anim + 0x20));
            *reinterpret_cast<void**>(anim + 0x20) = 0;
        }
    }

    for (int i = 0; i < 4; i++) {
        CameraCountAt(this, i) = 0;
        if (CameraDataAt(this, i) != 0) {
            delete[] static_cast<u8*>(CameraDataAt(this, i));
            CameraDataAt(this, i) = 0;
        }
    }

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        CHandle* next = handle->m_next;
        delete handle;
        handle = next;
    }

    if (resetMode != 1) {
        if (resetMode == 0) {
            const unsigned int releaseMask = ~(FreeMergeMask(this) | 0x10000000U);
            releaseUnuseLoadModel(static_cast<int>(releaseMask));

            for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
                CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
                if (!(((loadAnim->m_mergeFileId < 0) && (loadAnim->GetRef() == 1)) ||
                      ((loadAnim->m_mergeFileId >= 0) && ((releaseMask & static_cast<unsigned int>(loadAnim->m_mergeFlags)) != 0)))) {
                    continue;
                }

                CRef* loadAnimRef = loadAnim;
                if (loadAnimRef->DecRef() == 0) {
                    delete loadAnimRef;
                }
                LoadAnimArray(this)->RemoveAt(static_cast<unsigned long>(i));
            }

            System.Printf(const_cast<char*>(s_charaFreeMergeFmt), releaseMask);
            LoadPdtArray(this)->ReleaseAndRemoveAll();
            int charaAmemSize = correctLoadAnimAmem();
            if (charaAmemSize >= 0) {
                CharaAmemSize() = static_cast<unsigned int>(charaAmemSize);
                goto complete;
            }

            if (System.m_execParam > 1) {
                System.Printf(const_cast<char*>(s_charaAmemCompactFailed));
            }
        }
    }

    LoadModelArray(this)->ReleaseAndRemoveAll();
    LoadAnimArray(this)->ReleaseAndRemoveAll();
    LoadTextureArray(this)->ReleaseAndRemoveAll();
    LoadPdtArray(this)->ReleaseAndRemoveAll();
    CharaAmemSize() = 0;

complete:
    gCharaPartWorkPtr[0x6B] = 0xFF;
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
        Memory._Alloc(0x80000, StageAt(this, 0xD4), const_cast<char*>(s_p_chara_cpp), 0x162, 1));
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

            Memory.CopyFromAMemorySync(
                tempBuffer + chunkSize,
                reinterpret_cast<void*>(*reinterpret_cast<int*>(Ptr(StageAt(this, 0xC4), 8)) + static_cast<int>(animOffset)),
                static_cast<unsigned long>(animSize));

            *reinterpret_cast<int*>(anim + 0x28) = compactedSize + chunkSize;
            chunkSize += animSize;
        }

        if (chunkSize != 0) {
            Memory.CopyToAMemorySync(
                tempBuffer, reinterpret_cast<void*>(*reinterpret_cast<int*>(Ptr(StageAt(this, 0xC4), 8)) + compactedSize),
                static_cast<unsigned long>(chunkSize));
        }

        compactedSize += chunkSize;
        scanOffset = nextOffset;
    }

    operator delete(tempBuffer);
    return compactedSize;
}

/*
 * --INFO--
 * PAL Address: 0x8007999c
 * PAL Size: 420b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::onScriptChanging(char*)
{
    unsigned char* fadeColor = reinterpret_cast<unsigned char*>(this);

    for (int i = 0; i < 5; i++) {
        CColor white(0xFF, 0xFF, 0xFF, 0xFF);
        CColor shade;

        float scale = static_cast<float>(i) * 0.25f;
        shade.color.r = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.r) * scale));
        shade.color.g = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.g) * scale));
        shade.color.b = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.b) * scale));
        shade.color.a = static_cast<unsigned char>(static_cast<int>(static_cast<float>(white.color.a) * scale));
        CColor shadeCopy(shade);

        fadeColor[0x12C] = shadeCopy.color.r;
        fadeColor[0x12D] = shadeCopy.color.g;
        fadeColor[0x12E] = shadeCopy.color.b;
        fadeColor[0x12F] = shadeCopy.color.a;
        fadeColor += 4;
    }

    m_overlapEnabled = 0;
    m_charaAllocStage = 0;
    m_texShadowSize = 0x80;
    m_texShadowDistance = 100;
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
    CHandle* head = m_handleList;
    CHandle* handle = head->m_next;

    while (head != handle) {
        CHandle* next = handle->m_next;
        handle->m_shadowTexturePtr = 0;
        handle->loadModelASyncFrame();
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
    Chara.FlipDBuffer();

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_anim == 0) {
            continue;
        }

        void*& bankPtr = loadAnim->m_anim->m_bank;
        const int bankRefCount = loadAnim->m_anim->GetRef();
        if (bankRefCount == 1 && bankPtr != 0) {
            operator delete(bankPtr);
            bankPtr = 0;
        }
    }

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_anim == 0) {
            continue;
        }

        const int bankRefCount = loadAnim->m_anim->GetRef();
        if (bankRefCount == 1) {
            loadAnim->m_anim->m_lastFrame++;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseAllAnimBank()
{
    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_anim == 0) {
            continue;
        }

        void*& bankPtr = loadAnim->m_anim->m_bank;
        if (bankPtr != 0) {
            operator delete(bankPtr);
            bankPtr = 0;
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseUnusedAnimBank()
{
    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        if (loadAnim == 0 || loadAnim->m_anim == 0) {
            continue;
        }

        void*& bankPtr = loadAnim->m_anim->m_bank;
        const int bankRefCount = loadAnim->m_anim->GetRef();
        if (bankRefCount == 1 && bankPtr != 0) {
            operator delete(bankPtr);
            bankPtr = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80079760
 * PAL Size: 248b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::TryReleaseAnimBank(int requiredSize)
{
    (void)requiredSize;

    CLoadAnim* releaseAnim = 0;
    int releaseSize = -1;

    for (int i = LoadAnimArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];

        void* bankPtr = loadAnim->m_anim->m_bank;
        const int bankHistory = loadAnim->m_anim->m_lastFrame;
        if (bankPtr != 0 && releaseSize < bankHistory) {
            releaseAnim = loadAnim;
            releaseSize = bankHistory;
        }
    }

    if (releaseAnim == 0) {
        return 0;
    }

    void* bankPtr = releaseAnim->m_anim->m_bank;
    if (bankPtr != 0) {
        operator delete(bankPtr);
        releaseAnim->m_anim->m_bank = 0;
    }

    if (System.m_execParam > 2) {
        System.Printf(const_cast<char*>(s_charaReleaseAnimBankFmt), releaseSize, releaseAnim->m_name);
    }

    return 1;
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
void CCharaPcs::InitEnv(int envMode)
{
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);

    if (envMode == 1 || envMode == 2) {
        _GXColor black = {0x00, 0x00, 0x00, 0xFF};
        LightPcs.SetAmbient(black);
        LightPcs.SetNumDiffuse(0);
        LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
    } else {
        SetupBaseCharaLights(this);
    }

    if (envMode == 4) {
        GXSetProjection(reinterpret_cast<Mtx44Ptr>(Ptr(&Graphic, 0x73A4)), GX_ORTHOGRAPHIC);
    }
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
void CCharaPcs::GetTexShadow(int startIndex, int maxCount, _GXTexObj* texObjs, Vec* worldPositions, float (*shadowMatrices)[3][4])
{
    int shadowIndex = 0;
    CHandle* handle = HandleListHead(this)->m_next;

    while (handle != HandleListHead(this)) {
        if ((handle->m_flags & 0x200) != 0 && handle->m_shadowTexturePtr != 0) {
            if (startIndex <= shadowIndex) {
                const int outIndex = shadowIndex - startIndex;
                PSMTXConcat(m_texShadowProjectionMtx, handle->m_shadowViewMtx, reinterpret_cast<MtxPtr>(shadowMatrices[outIndex]));

                const unsigned short texSize = static_cast<unsigned short>(m_texShadowSize);
                GXInitTexObj(
                    &texObjs[outIndex], handle->m_shadowTexturePtr, texSize, texSize, GX_TF_RGBA8, GX_CLAMP, GX_CLAMP,
                    GX_FALSE);

                Mtx modelMtx;
                PSMTXCopy(*ModelLocalMtx(handle->m_model), modelMtx);
                worldPositions[outIndex].x = modelMtx[0][3];
                worldPositions[outIndex].y = modelMtx[1][3];
                worldPositions[outIndex].z = modelMtx[2][3];
            }

            shadowIndex++;
            if (shadowIndex >= startIndex + maxCount) {
                return;
            }
        }

        handle = handle->m_next;
    }
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
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
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
    CameraPcs.SetStdProjectionMatrix();
    SetupBaseCharaLights(this);

    if (HandleListHead(this) == 0) {
        return;
    }

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
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
    if (GetNumTexShadow() == 0) {
        return;
    }

    const int texSize = m_texShadowSize;
    _GXTexObj backBufferTexObj;
    _GXColor clearColor = {0x00, 0x00, 0x00, 0x00};
    _GXColor shadowColor = {0x00, 0x00, 0x00, 0xFF};

    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    Graphic.GetBackBufferRect2(Graphic.m_scratchTextureBuffer, &backBufferTexObj, 0, 0, texSize, texSize, 0, GX_NEAR, GX_TF_RGBA8, 0);

    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    LightPcs.SetAmbient(shadowColor);
    LightPcs.SetNumDiffuse(0);
    LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);

    GXSetPixelFmt((GXPixelFmt)1, GX_ZC_LINEAR);
    GXSetAlphaUpdate(GX_TRUE);
    GXSetViewport(0.0f, 0.0f, static_cast<float>(texSize), static_cast<float>(texSize), 0.0f, 1.0f);
    GXSetScissor(0, 0, static_cast<unsigned int>(texSize), static_cast<unsigned int>(texSize));
    Graphic.SetCopyClear(clearColor, 0);

    m_texShadowTextureBase = Graphic.m_scratchTextureBuffer;
    m_texShadowTextureSize = 0xD2000;
    m_texShadowTextureOffset = texSize * texSize * 4;
    C_MTXLightPerspective(m_texShadowProjectionMtx, CameraPcs.m_fov, 1.0f, 0.5f, -0.5f, 0.5f, 0.5f);

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
            handle->draw(2, 1);
        }
        handle = handle->m_next;
    }

    Graphic.SetViewport();
    Graphic.SetStdPixelFmt();
    Graphic.SetCopyClear(clearColor, 0);
    gUtil.RenderTextureQuad(
        0.0f, 0.0f, static_cast<float>(texSize), static_cast<float>(texSize), &backBufferTexObj, 0, 0, 0,
        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawShadow()
{
    if (CameraPcs.m_fullScreenShadowEnabled == 0) {
        return;
    }

    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP1, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    _GXSetTevSwapModeTable(GX_TEV_SWAP2, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);

    _GXColor shadowColor = {0x00, 0x00, 0x00, 0xFF};
    LightPcs.SetAmbient(shadowColor);
    LightPcs.SetNumDiffuse(0);
    LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);

    if (HandleListHead(this) == 0) {
        return;
    }

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
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
CTextureSet* CCharaPcs::createTextureSet(void* textureData, int useWeaponStage)
{
    CTextureSet* textureSet = new (StageAt(this, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
    if (textureSet != 0) {
        textureSet = textureSet;
    }

    if (textureSet != 0) {
        textureSet->Create(textureData, SelectLoadStage(this, StageAt(this, useWeaponStage != 0 ? 0xD8 : 0xD0)), 0, 0, 0, 0);
    }

    return textureSet;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::releaseUnuseLoadModel(int releaseMask)
{
    int activeCount = 0;

    for (int i = LoadModelArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadModel* loadModel = (*LoadModelArray(this))[static_cast<unsigned long>(i)];
        const bool shouldRelease =
            (((loadModel->m_mergeFileId < 0) || (loadModel->m_streamMode != 0)) && loadModel->GetRef() == 1) ||
            (loadModel->m_mergeFileId >= 0 && (releaseMask & loadModel->m_mergeFlags) != 0);

        if (!shouldRelease) {
            activeCount++;
            continue;
        }

        if (loadModel->m_streamMode != 0 && loadModel->GetRef() == 1) {
            ReleaseShared(loadModel->m_model);
            continue;
        }

        CLoadModel* releasedModel = loadModel;
        ReleaseShared(releasedModel);
        LoadModelArray(this)->RemoveAt(static_cast<unsigned long>(i));
    }

    for (int i = LoadTextureArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadTexture* loadTexture = (*LoadTextureArray(this))[static_cast<unsigned long>(i)];
        const bool shouldRelease =
            (((loadTexture->m_mergeFileId < 0) || (loadTexture->m_streamMode != 0)) && loadTexture->GetRef() == 1) ||
            (loadTexture->m_mergeFileId >= 0 && (releaseMask & loadTexture->m_mergeFlags) != 0);

        if (!shouldRelease) {
            activeCount++;
            continue;
        }

        if (loadTexture->m_streamMode != 0 && loadTexture->GetRef() == 1) {
            ReleaseShared(loadTexture->m_textureSet);
            continue;
        }

        CLoadTexture* releasedTexture = loadTexture;
        ReleaseShared(releasedTexture);
        LoadTextureArray(this)->RemoveAt(static_cast<unsigned long>(i));
    }

    for (int i = LoadPdtArray(this)->GetSize() - 1; i >= 0; i--) {
        CLoadPdt* loadPdt = (*LoadPdtArray(this))[static_cast<unsigned long>(i)];
        const bool shouldRelease =
            (loadPdt->m_mergeFileId < 0 && loadPdt->GetRef() == 1) ||
            (loadPdt->m_mergeFileId >= 0 && (releaseMask & loadPdt->m_mergeFlags) != 0);

        if (!shouldRelease) {
            activeCount++;
            continue;
        }

        CLoadPdt* releasedPdt = loadPdt;
        ReleaseShared(releasedPdt);
        LoadPdtArray(this)->RemoveAt(static_cast<unsigned long>(i));
    }

    return activeCount;
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
    if (System.m_execParam <= 2) {
        return;
    }

    System.Printf(const_cast<char*>(s_charaDumpModelHdr1));
    System.Printf(const_cast<char*>(s_charaDumpModelHdr2));
    System.Printf(const_cast<char*>(s_charaDumpLineSep));
    for (int i = 0; i < LoadModelArray(this)->GetSize(); i++) {
        CLoadModel* loadModel = (*LoadModelArray(this))[static_cast<unsigned long>(i)];
        unsigned int streamAddr = 0;
        unsigned int streamSize = 0;
        if (loadModel->m_streamMode != 0) {
            streamAddr = reinterpret_cast<unsigned int>(loadModel->m_streamOffset);
            streamSize = static_cast<unsigned int>(loadModel->m_streamSize);
        }

        System.Printf(
            const_cast<char*>(s_charaDumpModelFmt), i, reinterpret_cast<int>(loadModel->m_keyTag), loadModel->m_keyId,
            loadModel->m_mergeFileId, loadModel->m_mergeFlags, reinterpret_cast<unsigned int>(loadModel->m_model),
            loadModel->m_streamMode, streamAddr, streamSize);
    }

    System.Printf(const_cast<char*>(s_charaDumpTextureHdr1));
    System.Printf(const_cast<char*>(s_charaDumpTextureHdr2));
    System.Printf(const_cast<char*>(s_charaDumpLineSep));
    for (int i = 0; i < LoadTextureArray(this)->GetSize(); i++) {
        CLoadTexture* loadTexture = (*LoadTextureArray(this))[static_cast<unsigned long>(i)];
        unsigned int streamAddr = 0;
        unsigned int streamSize = 0;
        if (loadTexture->m_streamMode != 0) {
            streamAddr = reinterpret_cast<unsigned int>(loadTexture->m_streamOffset);
            streamSize = static_cast<unsigned int>(loadTexture->m_streamSize);
        }

        System.Printf(
            const_cast<char*>(s_charaDumpTextureFmt), i, reinterpret_cast<int>(loadTexture->m_keyTag), loadTexture->m_keyId,
            reinterpret_cast<int>(loadTexture->m_variantTag), loadTexture->m_mergeFileId, loadTexture->m_mergeFlags,
            reinterpret_cast<unsigned int>(loadTexture->m_textureSet), loadTexture->m_streamMode, streamAddr, streamSize);
    }

    System.Printf(const_cast<char*>(s_charaDumpPdtHdr1));
    System.Printf(const_cast<char*>(s_charaDumpPdtHdr2));
    System.Printf(const_cast<char*>(s_charaDumpLineSep));
    for (int i = 0; i < LoadPdtArray(this)->GetSize(); i++) {
        CLoadPdt* loadPdt = (*LoadPdtArray(this))[static_cast<unsigned long>(i)];
        System.Printf(
            const_cast<char*>(s_charaDumpPdtFmt), i, reinterpret_cast<int>(loadPdt->m_keyTag), loadPdt->m_keyId,
            reinterpret_cast<int>(loadPdt->m_variantTag), loadPdt->m_pdtSlot, loadPdt->m_mergeFileId,
            loadPdt->m_mergeFlags);
    }

    System.Printf(const_cast<char*>(s_charaDumpAnimHdr1));
    System.Printf(const_cast<char*>(s_charaDumpAnimHdr2));
    System.Printf(const_cast<char*>(s_charaDumpLineSep));
    int totalBankSize = 0;
    for (int i = 0; i < LoadAnimArray(this)->GetSize(); i++) {
        CLoadAnim* loadAnim = (*LoadAnimArray(this))[static_cast<unsigned long>(i)];
        unsigned int animAddr = 0;
        int bankSize = 0;
        unsigned int bankAddr = 0;
        if (loadAnim->m_anim != 0) {
            animAddr = reinterpret_cast<unsigned int>(loadAnim->m_anim);
            bankSize = loadAnim->m_anim->m_bankSize;
            bankAddr = loadAnim->m_anim->m_bankAddress;
        }

        System.Printf(
            const_cast<char*>(s_charaDumpAnimFmt), i, reinterpret_cast<int>(loadAnim->m_keyTag), loadAnim->m_keyId,
            loadAnim->m_name, loadAnim->m_mergeFileId, loadAnim->m_mergeFlags, animAddr, bankSize, totalBankSize, bankAddr);
        totalBankSize += bankSize;
    }
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
        delete[] static_cast<u8*>(cameraBuffer);
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
        cameraBuffer = new (stage, s_p_chara_cpp, 0x4D4) u8[static_cast<unsigned long>(cameraCounts[index] << 5)];

        float* values = reinterpret_cast<float*>(cameraBuffer);
        for (int i = 0; i < cameraCounts[index] * 8; i++) {
            values[i] = chunkFile.GetF4();
        }
    }

    File.Close(fileHandle);
}

/*
 * --INFO--
 * PAL Address: 0x800778dc
 * PAL Size: 2804b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::LoadMergeFile(int mergeFileId, int mergeFlags, int streamToAmem)
{
    bool hasLoaded = false;

    for (unsigned int i = 0; i < LoadModelArray(this)->GetSize(); i++) {
        CLoadModel* loadModel = (*LoadModelArray(this))[i];
        if (loadModel->m_mergeFileId == mergeFileId) {
            hasLoaded = true;
            break;
        }
    }

    if (!hasLoaded) {
        for (unsigned int i = 0; i < LoadTextureArray(this)->GetSize(); i++) {
            CLoadTexture* loadTexture = (*LoadTextureArray(this))[i];
            if (loadTexture->m_mergeFileId == mergeFileId) {
                hasLoaded = true;
                break;
            }
        }
    }

    if (!hasLoaded) {
        for (unsigned int i = 0; i < LoadPdtArray(this)->GetSize(); i++) {
            CLoadPdt* loadPdt = (*LoadPdtArray(this))[i];
            if (loadPdt->m_mergeFileId == mergeFileId) {
                hasLoaded = true;
                break;
            }
        }
    }

    if (!hasLoaded) {
        for (unsigned int i = 0; i < LoadAnimArray(this)->GetSize(); i++) {
            CLoadAnim* loadAnim = (*LoadAnimArray(this))[i];
            if (loadAnim->m_mergeFileId == mergeFileId) {
                hasLoaded = true;
                break;
            }
        }
    }

    if (hasLoaded) {
        System.Printf(const_cast<char*>(s_charaMergeDupFmt), mergeFileId);
        return;
    }

    CCharaPcs* pcs = &CharaPcs;
    int mergePartCount = 1;
    for (int mergePartIndex = 0; mergePartIndex < mergePartCount; mergePartIndex++) {
        char path[0x100];
        sprintf(path, s_charaMergePathFmt, mergeFileId, mergePartIndex);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle == 0) {
            System.Printf(const_cast<char*>(s_charaMergeOpenFmt), mergeFileId);
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
                        for (int i = 0; i < LoadModelArray(pcs)->GetSize(); i++) {
                            CLoadModel* it = (*LoadModelArray(pcs))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId) {
                                loadModel = it;
                                break;
                            }
                        }

                        if (loadModel == 0) {
                            loadModel = new (StageAt(pcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
                            if (loadModel != 0) {
                                loadModel->m_keyTag = keyTag;
                                loadModel->m_keyId = keyId;
                                loadModel->m_mergeFileId = mergeFileId;
                                loadModel->m_mergeFlags = mergeFlags;
                                loadModel->m_model = 0;
                                loadModel->m_streamMode = 0;
                                loadModel->m_streamOffset = 0;
                                loadModel->m_streamSize = 0;
                                LoadModelArray(pcs)->Add(loadModel);

                                if (streamToAmem == 0) {
                                    loadModel->m_model =
                                        new (StageAt(pcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5F1) CChara::CModel;
                                    if (loadModel->m_model != 0) {
                                        loadModel->m_model->Create(rawData, SelectLoadStage(pcs, StageAt(pcs, 0xCC)));
                                    }
                                } else {
                                    loadModel->m_streamMode = 1;
                                    loadModel->m_streamOffset = reinterpret_cast<void*>(LoadStreamCursor(this));
                                    loadModel->m_streamSize = rawSize;
                                    Memory.CopyToAMemorySync(
                                        rawData, reinterpret_cast<unsigned char*>(StageBase(StageAt(this, 0xC8))) + LoadStreamCursor(this),
                                        static_cast<unsigned long>(rawSize));
                                    LoadStreamCursor(this) += static_cast<unsigned int>(rawSize);
                                }
                            }
                        }

                        if (hasDynamics != 0 && loadModel != 0 && loadModel->m_model != 0 && chunkFile.GetNextChunk(chunk)) {
                            loadModel->m_model->CreateDynamics(
                                chunkFile.GetAddress(), SelectLoadStage(pcs, StageAt(pcs, 0xCC)));
                        }
                    } else if (dataType == 1) {
                        CLoadTexture* loadTexture = 0;
                        for (int i = 0; i < LoadTextureArray(pcs)->GetSize(); i++) {
                            CLoadTexture* it = (*LoadTextureArray(pcs))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId && it->m_variantTag == variantTag) {
                                loadTexture = it;
                                break;
                            }
                        }

                        if (loadTexture == 0) {
                            loadTexture = new (StageAt(pcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
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
                                LoadTextureArray(pcs)->Add(loadTexture);

                                if (streamToAmem == 0) {
                                    loadTexture->m_textureSet =
                                        new (StageAt(pcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
                                    if (loadTexture->m_textureSet != 0) {
                                        loadTexture->m_textureSet->Create(
                                            rawData,
                                            SelectLoadStage(
                                                pcs, StageAt(pcs, variantTag == reinterpret_cast<void*>(4) ? 0xD8 : 0xD0)),
                                            0, 0, 0, 0);
                                    }
                                } else {
                                    loadTexture->m_streamMode = 1;
                                    loadTexture->m_streamOffset = reinterpret_cast<void*>(LoadStreamCursor(this));
                                    loadTexture->m_streamSize = rawSize;
                                    Memory.CopyToAMemorySync(
                                        rawData, reinterpret_cast<unsigned char*>(StageBase(StageAt(this, 0xC8))) + LoadStreamCursor(this),
                                        static_cast<unsigned long>(rawSize));
                                    LoadStreamCursor(this) += static_cast<unsigned int>(rawSize);
                                }
                            }
                        }
                    } else if (dataType == 2) {
                        CLoadAnim* loadAnim = 0;
                        for (int i = 0; i < LoadAnimArray(pcs)->GetSize(); i++) {
                            CLoadAnim* it = (*LoadAnimArray(pcs))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId &&
                                animName != 0 && strcmp(it->m_name, animName) == 0) {
                                loadAnim = it;
                                break;
                            }
                        }

                        if (loadAnim == 0) {
                            CChara::CAnim* anim =
                                new (StageAt(pcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x62A) CChara::CAnim;
                            if (anim != 0) {
                                anim->Create(rawData, StageAt(pcs, 0xD4));
                            }

                            loadAnim = new (StageAt(pcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x62D) CLoadAnim;
                            if (loadAnim != 0) {
                                loadAnim->m_keyTag = keyTag;
                                loadAnim->m_keyId = keyId;
                                loadAnim->m_mergeFileId = mergeFileId;
                                loadAnim->m_mergeFlags = mergeFlags;
                                strcpy(loadAnim->m_name, animName != 0 ? animName : "");
                                loadAnim->m_anim = anim;
                                LoadAnimArray(pcs)->Add(loadAnim);
                            }
                        }
                    } else if (dataType == 3) {
                        Sound.LoadSe(rawData);
                    } else if (dataType == 4) {
                        Sound.LoadWave(rawData);
                    } else if (dataType == 5) {
                        CLoadPdt* loadPdt = 0;
                        for (int i = 0; i < LoadPdtArray(pcs)->GetSize(); i++) {
                            CLoadPdt* it = (*LoadPdtArray(pcs))[static_cast<unsigned long>(i)];
                            if (it != 0 && it->m_keyTag == keyTag && it->m_keyId == keyId && it->m_variantTag == variantTag) {
                                loadPdt = it;
                                break;
                            }
                        }

                        if (loadPdt == 0 && chunkFile.GetNextChunk(chunk)) {
                            loadPdt = new (StageAt(pcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x572) CLoadPdt;
                            if (loadPdt != 0) {
                                loadPdt->m_keyTag = keyTag;
                                loadPdt->m_keyId = keyId;
                                loadPdt->m_variantTag = variantTag;
                                loadPdt->m_pdtSlot = PartPcs.LoadMonsterPdt(
                                    keyId, reinterpret_cast<int>(variantTag), rawData, rawSize, chunkFile.GetAddress(),
                                    static_cast<int>(chunk.m_size));
                                loadPdt->m_mergeFileId = mergeFileId;
                                loadPdt->m_mergeFlags = mergeFlags;
                                LoadPdtArray(pcs)->Add(loadPdt);
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

    System.Printf(const_cast<char*>(s_charaMergeDoneFmt), mergeFileId, mergeFlags);
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
    if (m_overlapEnabled == 0) {
        return;
    }

    int left = 0;
    int top = 0;
    int width = 0x280;
    int height = 0x1C0;
    _GXTexObj* backBufferTex = Graphic.GetBackBufferRect(left, top, width, height, 0);

    Mtx savedCameraMtx;
    Mtx lookAtMtx;
    Mtx identityMtx;
    Mtx texMtx;
    Mtx44 projectionMtx;
    Vec up = {0.0f, 1.0f, 0.0f};

    PSMTXCopy(CameraPcs.m_cameraMatrix, savedCameraMtx);

    C_MTXOrtho(projectionMtx, 0.0f, 448.0f, 0.0f, 640.0f, 0.5f, -0.5f);
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);

    _GXColor black = {0x00, 0x00, 0x00, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, black);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumTevStages(1);
    GXSetZMode(GX_TRUE, GX_ALWAYS, GX_TRUE);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD_NULL, GX_TEXMAP_NULL, GX_COLOR0A0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);
    _GXSetTevSwapModeTable(GX_TEV_SWAP0, GX_CH_RED, GX_CH_GREEN, GX_CH_BLUE, GX_CH_ALPHA);
    Graphic.SetFog(0, 0);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 1.0f);
    GXPosition3f32(640.0f, 0.0f, 1.0f);
    GXPosition3f32(0.0f, 448.0f, 1.0f);
    GXPosition3f32(640.0f, 448.0f, 1.0f);

    PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
    GXSetProjection(projectionMtx, GX_PERSPECTIVE);

    C_MTXLookAt(lookAtMtx, &m_overlapEyePos, &up, &m_overlapTargetPos);
    PSMTXCopy(lookAtMtx, CameraPcs.m_cameraMatrix);

    SetupBaseCharaLights(this);

    CHandle* handle = HandleListHead(this)->m_next;
    while (handle != HandleListHead(this)) {
        if ((DbgMenuPcs.GetDbgFlagsRaw() & 0x8000) != 0) {
            handle->draw(0, 1);
        }
        handle = handle->m_next;
    }

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0A0, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_SPEC);
    GXSetChanCtrl(GX_COLOR1A1, GX_FALSE, GX_SRC_REG, GX_SRC_VTX, GX_LIGHT_NULL, GX_DF_NONE, GX_AF_NONE);

    black.a = static_cast<unsigned char>(m_overlapAlpha & 0xFF);
    GXSetChanMatColor(GX_COLOR0A0, black);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    C_MTXOrtho(projectionMtx, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, -1.0f);
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, GX_PNMTX0);
    GXSetCurrentMtx(GX_PNMTX0);
    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetNumTevStages(1);
    Graphic.SetFog(0, 0);
    GXSetTevDirect(GX_TEVSTAGE0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_PASSCLR);
    _GXSetTevOrder(GX_TEVSTAGE0, GX_TEXCOORD0, GX_TEXMAP0, GX_COLOR0A0);
    _GXSetTevSwapMode(GX_TEVSTAGE0, GX_TEV_SWAP0, GX_TEV_SWAP0);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXPosition3f32(640.0f, 0.0f, 0.0f);
    GXPosition3f32(0.0f, 448.0f, 0.0f);
    GXPosition3f32(640.0f, 448.0f, 0.0f);

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    _GXColor white = {0xFF, 0xFF, 0xFF, 0xFF};
    GXSetChanMatColor(GX_COLOR0A0, white);
    GXLoadTexObj(backBufferTex, GX_TEXMAP0);
    PSMTXScale(texMtx, 0.003125f, -0.002232143f, 1.0f);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_U16, 0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);

    GXBegin(GX_QUADS, GX_VTXFMT0, 4);
    GXPosition3f32(0.0f, 0.0f, 0.0f);
    GXTexCoord2u16(0, 0);
    GXPosition3f32(640.0f, 0.0f, 0.0f);
    GXTexCoord2u16(0x280, 0);
    GXPosition3f32(0.0f, 448.0f, 0.0f);
    GXTexCoord2u16(0, 0x1C0);
    GXPosition3f32(640.0f, 448.0f, 0.0f);
    GXTexCoord2u16(0x280, 0x1C0);

    PSMTX44Copy(CameraPcs.m_screenMatrix, projectionMtx);
    GXSetProjection(projectionMtx, GX_PERSPECTIVE);
    PSMTXCopy(savedCameraMtx, CameraPcs.m_cameraMatrix);
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
void* CCharaPcs::CHandle::operator new(unsigned long size, CMemory::CStage*, char* file, int line)
{
    return Memory._Alloc(size, StageAt(&CharaPcs, 0xC0), file, line, 0);
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

	m_colorPhase = FLOAT_8033028c;
	m_sortZ = FLOAT_80330288;
	m_shadowTexturePtr = nullptr;

	m_asyncState = 0;
	m_asyncFileHandle = (CFile::CHandle*)nullptr;

	m_fogBlend = FLOAT_80330288;
	m_unk0x158 = 0;
	m_drawListFlags = static_cast<unsigned char>(__rlwimi(m_drawListFlags, 1, 7, 24, 24));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CHandle::~CHandle()
{
    if (m_asyncFileHandle != 0) {
        if (static_cast<unsigned int>(System.m_execParam) >= 2U) {
            System.Printf(const_cast<char*>(s_charaAsyncCancelFmt));
        }
        File.Close(m_asyncFileHandle);
        m_asyncFileHandle = 0;
    }

    m_asyncState = 0;
    PartMng.pppDeleteCHandle(this);

    if (m_next != 0 && m_previous != 0) {
        m_previous->m_next = m_next;
        m_next->m_previous = m_previous;
        m_previous = 0;
        m_next = 0;
    }

    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x717);
    Graphic._WaitDrawDone(const_cast<char*>(s_p_chara_cpp), 0x8C9);
    PartMng.pppDeleteCHandle(this);

    ReleaseShared(m_model);
    ReleaseShared(m_textureSet);
    ReleaseShared(m_modelLoadRef);
    ReleaseShared(m_texLoadRef);
    ReleaseShared(m_pdtLoadRef);

    CharaPcs.releaseUnuseLoadModel(0);
    for (int i = 0; i < 64; i++) {
        ReleaseHandleAnimSlot(this, i);
    }
    PruneUnsharedAnimRefs(&CharaPcs, 0);
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
        m_model->AttachTextureSet(0);
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
    } else if (loadTexture->m_streamOffset != 0 && loadTexture->GetRef() == 1) {
        File.LockBuffer();
        Memory.CopyFromAMemorySync(
            File.m_readBuffer,
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
        m_model->AttachTextureSet(m_textureSet);
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
            loadModel->m_model =
                new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5F1) CChara::CModel;
            loadModel->m_streamMode = 0;
            loadModel->m_streamOffset = 0;
            loadModel->m_streamSize = 0;

            if (loadModel->m_model != 0) {
                loadModel->m_model->Create(File.m_readBuffer, HandleModelStage(charaKind, 0));
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
                m_model->CreateDynamics(File.m_readBuffer, HandleModelStage(charaKind, 0));
            }
            File.Close(fileHandle);
        }
    } else {
        m_modelLoadRef = loadModel;

        if (loadModel->GetRef() == 1) {
            if (loadModel->m_streamOffset != 0) {
                File.LockBuffer();
                Memory.CopyFromAMemorySync(
                    File.m_readBuffer,
                    reinterpret_cast<unsigned char*>(StageBase(StageAt(&CharaPcs, 0xC8))) +
                        reinterpret_cast<unsigned int>(loadModel->m_streamOffset),
                    static_cast<unsigned long>(loadModel->m_streamSize));
                loadModel->m_model =
                    new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x7C7) CChara::CModel;
                if (loadModel->m_model != 0) {
                    loadModel->m_model->Create(File.m_readBuffer, HandleModelStage(charaKind, specialModelStage));
                }
                File.UnlockBuffer();
            }

            AddSharedRef(m_modelLoadRef);
            m_model = loadModel->m_model;
            AddSharedRef(m_model);
            if (m_model != 0) {
                m_model->Init();
            }
        } else {
            AddSharedRef(m_modelLoadRef);
            m_model = loadModel->m_model != 0 ? loadModel->m_model->Duplicate(HandleModelStage(charaKind, specialModelStage)) : 0;
        }
    }

    ChangeTexture(charaKind, charaNo, textureVariant, mergeFileId, mergeFlags);
    if (m_textureSet != 0 && m_textureSet->Find(const_cast<char*>(s_mogFurTextureName)) >= 0 && m_model != 0) {
        m_model->InitMogFurTex();
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
int CCharaPcs::CHandle::LoadAnim(
    char* animName, int animIndex, int animFlags, int charaKind, int charaNo, int mergeFileId, int mergeFlags)
{
    if (animIndex == -1) {
        for (int i = 0; i < 64; i++) {
            ReleaseHandleAnimSlot(this, i);
        }
        PruneUnsharedAnimRefs(&CharaPcs, 0);
    } else {
        CLoadAnim* previousAnim = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex]);
        if (previousAnim != 0) {
            ReleaseShared(m_animSlot[animIndex]);
            PruneUnsharedAnimRefs(&CharaPcs, previousAnim);
            m_animSlot[animIndex] = 0;
        }
    }

    const int resolvedKind = charaKind == -1 ? m_charaKind : charaKind;
    const int resolvedNo = charaNo == -1 ? m_charaNo : charaNo;

    CLoadAnim* loadAnim = FindLoadedAnim(&CharaPcs, resolvedKind, resolvedNo, animName);
    if (loadAnim == 0) {
        loadAnim = LoadAnimFromDisk(&CharaPcs, resolvedKind, resolvedNo, animName, mergeFileId, mergeFlags);
    }
    if (loadAnim == 0) {
        return 0;
    }

    m_animSlot[animIndex] = loadAnim;
    AddSharedRef(m_animSlot[animIndex]);

    *reinterpret_cast<unsigned int*>(Ptr(loadAnim, 0x70)) = static_cast<unsigned int>(animFlags);
    if (loadAnim->m_anim != 0) {
        unsigned char& flags = loadAnim->m_anim->m_flags;
        flags = static_cast<unsigned char>((flags & 0x7F) | ((animFlags << 7) & 0x80));
        flags = static_cast<unsigned char>((flags & 0xBF) | ((animFlags << 5) & 0x40));
    }

    return 1;
}

int CCharaPcs::CHandle::IsModelLoaded(int checkModelField)
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
int CCharaPcs::LoadAnim(int charaKind, int charaNo, char* animName, int unusedArg, int mergeFileId, int mergeFlags)
{
    (void)unusedArg;

    CLoadAnim* loadAnim = FindLoadedAnim(this, charaKind, charaNo, animName);
    if (loadAnim == 0) {
        loadAnim = LoadAnimFromDisk(this, charaKind, charaNo, animName, mergeFileId, mergeFlags);
    }

    return loadAnim != 0;
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
void CCharaPcs::CHandle::FreeAnim(int animIndex)
{
    if (animIndex == -1) {
        for (int i = 0; i < 64; i++) {
            ReleaseHandleAnimSlot(this, i);
        }
        PruneUnsharedAnimRefs(&CharaPcs, 0);
        return;
    }

    CLoadAnim* previousAnim = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex]);
    if (previousAnim == 0) {
        return;
    }

    ReleaseShared(m_animSlot[animIndex]);
    PruneUnsharedAnimRefs(&CharaPcs, previousAnim);
    m_animSlot[animIndex] = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CCharaPcs::CHandle::SetAnim(int animIndex, int startFrame, int endFrame, int blendMode, int forceSet)
{
    if (m_model == 0) {
        return 0;
    }
    if (m_currentAnimIndex == animIndex && forceSet == 0) {
        return 0;
    }

    CChara::CAnim* anim = 0;
    if (animIndex >= 0 && m_animSlot[animIndex] != 0) {
        anim = reinterpret_cast<CLoadAnim*>(m_animSlot[animIndex])->m_anim;
    }

    if (anim == 0) {
        if (m_charaKind != 3 && System.m_execParam > 1) {
            System.Printf(const_cast<char*>(s_charaSetAnimMissingFmt), m_charaKind, m_charaNo, animIndex);
        }
        return 0;
    }

    m_model->AttachAnim(anim, startFrame, endFrame, blendMode);
    m_currentAnimIndex = animIndex;
    return 1;
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
	unsigned int dbgMenuFlags = DbgMenuPcs.GetDbgFlagsRaw();
	if ((dbgMenuFlags & 0x8000) != 0) {
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
    const float lightAlpha = m_model->m_lightAlpha;
    if (lightAlpha == FLOAT_80330288 && (flags & 0x80) == 0) {
        return;
    }
    if ((flags & 0x100) != 0 && drawPass != 5) {
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

    if (immediatePass != 0 && drawPass == 0 && (lightAlpha < FLOAT_8033028c || (flags & 0x40000) != 0)) {
        ppvDrawMng.AddPrim(-m_sortZ, this);
        return;
    }

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
        _GXColor shade;
        if ((flags & 0x20000) == 0 || drawPass == 3) {
            const float blendT = phase - static_cast<float>(phaseIndex);
            shade = BlendColor(CharaPcs.m_viewerChoiceColor[phaseIndex].color,
                               CharaPcs.m_viewerChoiceColor[phaseIndex + 1].color, blendT);
        } else {
            shade.r = 0xFF;
            shade.g = 0xFF;
            shade.b = 0xFF;
            shade.a = 0xFF;
        }
        const _GXColor ambientBase = CharaPcs.m_viewerAmbientColor[lightBank];
        const _GXColor ambientColor = ModulateColor(ambientBase, shade);
        LightPcs.SetAmbient(ambientColor);

        for (unsigned long i = 0; i < 3; i++) {
            const _GXColor diffuseBase = CharaPcs.m_viewerDiffuseColor[lightBank][i];
            LightPcs.SetDiffuseColor(i, ModulateColor(diffuseBase, shade));
        }

        Vec lightPos;
        Mtx* modelMtx = ModelLocalMtx(m_model);
        lightPos.x = (*modelMtx)[0][3];
        lightPos.y = (*modelMtx)[1][3];
        lightPos.z = (*modelMtx)[2][3];
        LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), &lightPos, 0xFFFFFFFF);
    }

    Mtx viewMtx;
    PSMTXCopy(CameraPcs.m_cameraMatrix, viewMtx);

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
            PSMTXConcat(viewMtx, CFlatCenterMatrix(), viewMtx);
        }
    } else if (drawPass == 2) {
        Mtx* modelMtx = ModelLocalMtx(m_model);
        Vec modelPos;
        modelPos.x = (*modelMtx)[0][3];
        modelPos.y = (*modelMtx)[1][3];
        modelPos.z = (*modelMtx)[2][3];

        Vec focusPos = CharaPcs.m_texShadowPos;
        Vec delta;
        PSVECSubtract(&focusPos, &modelPos, &delta);
        if (delta.x == 0.0f && delta.z == 0.0f) {
            return;
        }

        const float distance = PSVECMag(&delta);
        const float shadowRange = CharaPcs.m_texShadowRadius;
        if (distance > shadowRange) {
            return;
        }

        PSVECNormalize(&delta, &delta);

        Vec up = {0.0f, 1.0f, 0.0f};
        Vec eye = modelPos;
        eye.y += 1.0f;

        Vec shadowPos;
        PSVECScale(&delta, &shadowPos, static_cast<float>(CharaPcs.m_texShadowDistance));
        PSVECAdd(&modelPos, &shadowPos, &shadowPos);
        shadowPos.y += 1.0f;

        C_MTXLookAt(m_shadowViewMtx, reinterpret_cast<Point3d*>(&shadowPos), &up, reinterpret_cast<Point3d*>(&eye));
        PSMTXCopy(m_shadowViewMtx, viewMtx);

        _GXColor shadowFog = CharaPcs.m_texShadowColor;
        GXSetFog(GX_FOG_ORTHO_LIN, 0.0f, shadowRange, 0.0f, 512.0f, shadowFog);
    }

    bool restoreFog = false;
    if ((drawPass == 0 || drawPass == 4) && m_fogBlend > 0.0f) {
        _GXColor fogColor = CharaPcs.m_texShadowColor;
        GXSetFog(GX_FOG_PERSP_LIN, m_fogBlend, m_fogBlend + 2.0f, 0.0f, 1024.0f, fogColor);
        restoreFog = true;
    }

    if (drawPass == 1 || drawPass == 2) {
        if (drawPass == 2) {
            const unsigned short shadowSize = static_cast<unsigned short>(CharaPcs.m_texShadowSize);
            GXSetTexCopySrc(0, 0, shadowSize, shadowSize);
            GXSetTexCopyDst(shadowSize, shadowSize, GX_TF_I8, GX_FALSE);
            m_shadowTexturePtr = reinterpret_cast<unsigned char*>(CharaPcs.m_texShadowTextureBase) +
                                 CharaPcs.m_texShadowTextureOffset;
            DCInvalidateRange(m_shadowTexturePtr, (shadowSize * shadowSize) / 2);
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
        }

        const int shadowMode = __cntlzw(static_cast<unsigned int>(1 - drawPass)) >> 5;
        m_model->DrawShadow(viewMtx, shadowMode);

        if (drawPass == 2) {
            const unsigned int shadowBytes =
                (static_cast<unsigned int>(CharaPcs.m_texShadowSize) *
                 static_cast<unsigned int>(CharaPcs.m_texShadowSize)) / 2;
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
            CharaPcs.m_texShadowTextureOffset += shadowBytes;
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
        m_model->Draw(viewMtx, modelDrawFlags, 0);
    }

    if (drawPass == 0 || drawPass == 4) {
        m_model->DrawFur(viewMtx, static_cast<int>((flags >> 23) & 1));
    }

    if (restoreFog) {
        Graphic.SetFog(1, 0);
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
    if (System.m_execParam > 2)
    {
        System.Printf(const_cast<char*>(s_charaAsyncEntryFmt));
    }

    if (m_asyncFileHandle != 0)
	{
        if (System.m_execParam > 1)
        {
            System.Printf(const_cast<char*>(s_charaAsyncCancelFmt));
        }
		File.Close(m_asyncFileHandle);
		m_asyncFileHandle = (CFile::CHandle*)0;
	}

	m_asyncState = 0;
	Graphic._WaitDrawDone((char*)"p_chara.cpp", 0x8C9);
	PartMng.pppDeleteCHandle(this);

	ReleaseShared(m_model);
	ReleaseShared(m_textureSet);
	ReleaseShared(m_modelLoadRef);
	ReleaseShared(m_texLoadRef);
	ReleaseShared(m_pdtLoadRef);

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
            strcat(path, s_charaModelSuffix);
        } else if (m_asyncState == 3) {
            strcpy(path, basePath);
            strcat(path, s_charaDynamicsSuffix);
        } else {
            if (m_asyncTextureVariant < 1) {
                strcpy(path, basePath);
            } else {
                sprintf(path, s_charaTextureVariantFmt, basePath, m_asyncTextureVariant + 0x61);
            }
            strcat(path, s_charaTextureSuffix);
        }

        m_asyncFileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (m_asyncFileHandle == 0 && m_asyncState == 3) {
            m_asyncState = 5;
            loadModelASyncFrame();
            return;
        }
        File.ReadASync(m_asyncFileHandle);
        m_asyncState++;
        return;
    }

    if ((asyncState != 2 && asyncState != 4 && asyncState != 6) || !File.IsCompleted(m_asyncFileHandle)) {
        return;
    }

    if (m_asyncState == 2) {
        CLoadModel* loadModel = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5E8) CLoadModel;
        loadModel->m_keyTag = reinterpret_cast<void*>(m_asyncCharaKind);
        loadModel->m_keyId = m_asyncCharaNo;
        loadModel->m_mergeFileId = -1;
        loadModel->m_mergeFlags = 0;
        LoadModelArray(&CharaPcs)->Add(loadModel);
        loadModel->m_model =
            new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x5F1) CChara::CModel;
        loadModel->m_streamMode = 0;
        loadModel->m_streamOffset = 0;
        loadModel->m_streamSize = 0;
        loadModel->m_model->Create(File.m_readBuffer, HandleModelStage(m_asyncCharaKind, 0));
        m_modelLoadRef = loadModel;
        AddSharedRef(m_modelLoadRef);
        m_model = loadModel->m_model;
        AddSharedRef(m_model);
        m_charaKind = m_asyncCharaKind;
        m_charaNo = m_asyncCharaNo;
    } else if (m_asyncState == 4) {
        m_model->CreateDynamics(File.m_readBuffer, HandleModelStage(m_asyncCharaKind, 0));
    } else {
        CLoadTexture* loadTexture = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x609) CLoadTexture;
        loadTexture->m_keyTag = reinterpret_cast<void*>(m_asyncCharaKind);
        loadTexture->m_keyId = m_asyncCharaNo;
        loadTexture->m_mergeFileId = -1;
        loadTexture->m_mergeFlags = 0;
        loadTexture->m_variantTag = reinterpret_cast<void*>(m_asyncTextureVariant);
        LoadTextureArray(&CharaPcs)->Add(loadTexture);
        loadTexture->m_textureSet = new (StageAt(&CharaPcs, 0xC0), const_cast<char*>(s_p_chara_cpp), 0x397) CTextureSet;
        loadTexture->m_streamMode = 0;
        loadTexture->m_streamOffset = 0;
        loadTexture->m_streamSize = 0;
        loadTexture->m_textureSet->Create(File.m_readBuffer, HandleTextureStage(m_asyncCharaKind), 0, 0, 0, 0);
        m_texLoadRef = loadTexture;
        AddSharedRef(m_texLoadRef);
        m_textureSet = loadTexture->m_textureSet;
        AddSharedRef(m_textureSet);
        m_model->AttachTextureSet(m_textureSet);
        m_textureVariant = m_asyncTextureVariant;
    }

    File.Close(m_asyncFileHandle);
    m_asyncFileHandle = 0;
    if (m_asyncState == 6) {
        m_asyncState = 7;
        if (System.m_execParam > 2) {
            System.Printf(const_cast<char*>(s_charaAsyncCompleteFmt));
        }
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
int CCharaPcs::CHandle::IsLoadModelASyncCompleted()
{
    return m_asyncState == 7;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::CancelLoadModelASync()
{
    if (m_asyncFileHandle != 0) {
        File.Close(m_asyncFileHandle);
        m_asyncFileHandle = 0;
    }

    m_asyncState = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::CLoadModel()
{
    m_keyTag = 0;
    m_keyId = -1;
    m_mergeFileId = -1;
    m_mergeFlags = 0;
    m_model = 0;
    m_streamMode = 0;
    m_streamOffset = 0;
    m_streamSize = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel::~CLoadModel()
{
    ReleaseShared(m_model);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim::CLoadAnim()
{
    m_anim = 0;
    m_unk2C = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim::~CLoadAnim()
{
    ReleaseShared(m_anim);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::CLoadTexture()
{
    m_keyTag = 0;
    m_keyId = -1;
    m_mergeFileId = -1;
    m_mergeFlags = 0;
    m_variantTag = 0;
    m_textureSet = 0;
    m_streamMode = 0;
    m_streamOffset = 0;
    m_streamSize = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture::~CLoadTexture()
{
    ReleaseShared(m_textureSet);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::CLoadPdt()
{
    m_keyTag = 0;
    m_keyId = -1;
    m_variantTag = 0;
    m_pdtSlot = -1;
    m_mergeFileId = -1;
    m_mergeFlags = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt::~CLoadPdt()
{
    if (m_pdtSlot >= 0) {
        PartPcs.ReleasePdt(m_pdtSlot);
        m_pdtSlot = -1;
    }
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
