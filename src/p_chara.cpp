#include "ffcc/ptrarray.h"
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


#include "PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/string.h"
#include <PowerPC_EABI_Support/Runtime/New.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>
#include <math.h>

const char* CCharaPcs::m_modelTable[6][3] = {
    {"pc", "c", "_root"},
    {"mon", "m", "_root"},
    {"npc", "n", "_root"},
    {"fa", "f", "_root"},
    {"wep", "w", "_root"},
    {"loc", "l", "_root"},
};

CCharaPcs CharaPcs;

inline int CSystem::GetErrorLevel()
{
    return m_execParam;
}

static const char s_CCharaPcs_GAME_801D9128[] = "CCharaPcs(GAME)";
static const char s_CCharaPcs_VIEWER_801D9138[] = "CCharaPcs(VIEWER)";
static const char s_CCharaPcs_PART_801D914C[] = "CCharaPcs(PART)";

inline void* operator new(unsigned long, void* ptr)
{
    return ptr;
}

STATIC_ASSERT(sizeof(CCharaPcs::CLoadModel) == 0x28);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadAnim) == 0x74);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadTexture) == 0x2C);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadAnim, m_pointCount) == 0x2C);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadAnim, m_points) == 0x2E);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadAnim, m_playbackFlags) == 0x70);
STATIC_ASSERT(sizeof(CCharaPcs::CLoadPdt) == 0x20);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadModel, m_keyTag) == 0x08);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadAnim, m_keyTag) == 0x08);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadTexture, m_keyTag) == 0x08);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadPdt, m_keyTag) == 0x08);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadTexture, m_variantTag) == 0x18);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadPdt, m_variantTag) == 0x10);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadModel, m_streamOffset) == 0x20);
STATIC_ASSERT(offsetof(CCharaPcs::CLoadTexture, m_streamOffset) == 0x24);
STATIC_ASSERT(sizeof(CCharaPcs::CCameraFrame) == 0x20);
STATIC_ASSERT(sizeof(CCharaPcs::CCameraFrame::Value) == 4);
STATIC_ASSERT(offsetof(CCharaPcs::CCameraFrame, m_values) == 0);
STATIC_ASSERT(offsetof(CCharaPcs::CHandle, m_drawListFlags) == 0x190);
STATIC_ASSERT(offsetof(CCharaPcs::CHandle, m_modelLoadRef) == 0x170);
STATIC_ASSERT(offsetof(CCharaPcs::CHandle, m_texLoadRef) == 0x174);
STATIC_ASSERT(offsetof(CCharaPcs::CHandle, m_pdtLoadRef) == 0x178);
STATIC_ASSERT(offsetof(CCharaPcs, m_cameraFrameCount) == 0x04);
STATIC_ASSERT(offsetof(CCharaPcs, m_cameraData) == 0x14);
STATIC_ASSERT(offsetof(CCharaPcs, m_overlapEyePos) == 0x2C);
STATIC_ASSERT(offsetof(CCharaPcs, m_overlapTargetPos) == 0x38);
STATIC_ASSERT(offsetof(CCharaPcs, m_handleList) == 0x4C);
STATIC_ASSERT(offsetof(CCharaPcs, m_stage) == 0xC0);
STATIC_ASSERT(offsetof(CCharaPcs, m_amemStage) == 0xC4);
STATIC_ASSERT(offsetof(CCharaPcs, m_amemWorkStage) == 0xC8);
STATIC_ASSERT(sizeof(((CCharaPcs*)0)->m_loadStages) == 0x18);
STATIC_ASSERT(offsetof(CCharaPcs, m_loadStages[CCharaPcs::LOAD_STAGE_MODEL]) == 0xCC);
STATIC_ASSERT(offsetof(CCharaPcs, m_loadStages[CCharaPcs::LOAD_STAGE_TEXTURE]) == 0xD0);
STATIC_ASSERT(offsetof(CCharaPcs, m_loadStages[CCharaPcs::LOAD_STAGE_ANIM]) == 0xD4);
STATIC_ASSERT(offsetof(CCharaPcs, m_loadStages[CCharaPcs::LOAD_STAGE_WEAPON_TEXTURE]) == 0xD8);
STATIC_ASSERT(offsetof(CCharaPcs, m_loadStages[CCharaPcs::LOAD_STAGE_WEAPON_MODEL]) == 0xDC);
STATIC_ASSERT(offsetof(CCharaPcs, m_loadStages[CCharaPcs::LOAD_STAGE_FAMILY_MODEL]) == 0xE0);
STATIC_ASSERT(offsetof(CCharaPcs, m_charaAllocStage) == 0xE4);


namespace {
template <typename T>
static inline void ReleaseSharedNonNull(T* ptr)
{
    CRef* ref = ptr;
    ref->Release();
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
        ptr->AddRef();
    }
}

static inline void ReleaseHandleAnimSlot(CCharaPcs::CHandle* handle, int slot)
{
    CRef* animRef = handle->m_animSlot[slot];
    if (animRef != 0) {
        ReleaseShared(handle->m_animSlot[slot]);
    }
}

static inline void BuildCharaBasePath(int charaKind, unsigned long charaNo, char* outPath)
{
    const char** pathParts = CCharaPcs::m_modelTable[charaKind];
    sprintf(outPath, "dvd/char/%s/%s%03d/%s%03d%s", pathParts[0], pathParts[1], static_cast<int>(charaNo), pathParts[1],
            static_cast<int>(charaNo), pathParts[2]);
}

static inline CMemory::CStage* HandleModelStage(int charaKind, int specialModelStage)
{
    CMemory::CStage* stage = CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_MODEL];
    if (specialModelStage != 0) {
        stage = charaKind == 3 ? CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_FAMILY_MODEL]
                              : CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_WEAPON_MODEL];
    }
    return GET_CHARA_ALLOC_STAGE_S(CharaPcs.GetCharaAllocStage(), stage);
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

static inline void CopyColor(_GXColor* dst, _GXColor src)
{
    dst->r = src.r;
    dst->g = src.g;
    dst->b = src.b;
    dst->a = src.a;
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
 * PAL Address: 0x8007a51c
 * PAL Size: 1124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::Init()
{
    m_stage = Memory.CreateStage(0x38000, "CCharaPcs", 0);
    m_amemStage = Memory.CreateStage(0x380000, "CCharaPcs.amem", 2);
    m_amemWorkStage = Memory.CreateStage(0x70000, "CCharaPcs.amemw", 2);
    Chara.SetAmemStage(m_amemStage);

    m_loadModels.SetStage(m_stage);
    m_loadModels.SetDefaultSize(0x80);
    m_loadModels.SetGrow(0);

    m_loadAnims.SetStage(m_stage);
    m_loadAnims.SetDefaultSize(0x200);
    m_loadAnims.SetGrow(0);

    m_loadTextures.SetStage(m_stage);
    m_loadTextures.SetDefaultSize(0x100);
    m_loadTextures.SetGrow(0);

    m_loadPdts.SetStage(m_stage);
    m_loadPdts.SetDefaultSize(0x80);
    m_loadPdts.SetGrow(0);

    for (unsigned int i = 0; i < 2; i++) {
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
            if (i == 0) {
                m_viewerDiffusePos[lightIndex].x = 0.0f;
                m_viewerDiffusePos[lightIndex].y = 0.0f;
                m_viewerDiffusePos[lightIndex].z = -1.0f;
            }
        }
    }

    for (int i = 0; i < 5; i++) {
        m_viewerChoiceColor[i] = CColor(0xFF, 0xFF, 0xFF, 0xFF) * (i / 4.0f);
    }

    m_charaAllocStage = 0;
    m_overlapEnabled = 0;
    CopyColor(&m_texShadowColor, CColor(0x00, 0x00, 0x40, 0x40).color);
    m_texShadowPos = CVector(0.0f, 100.0f, 0.0f);
    m_texShadowRadius = 500.0f;
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
    Chara.AmemSize() = 0;
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
    return reinterpret_cast<int>(&m_table[index]);
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
        return PartPcs.m_usbStreamState.m_stageLoad;
    case 3:
        return PartMng.m_pppEnvSt.m_stagePtr;
    case 4:
        return CharaPcs.GetAnimStage();
    default:
        return stage;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::create()
{
    m_noFreeMergeMask = 0;

    m_loadStages[CCharaPcs::LOAD_STAGE_MODEL] = Memory.CreateStage(0x177000, "CCharaPcs LoadModel", 0);
    m_loadStages[CCharaPcs::LOAD_STAGE_TEXTURE] = Memory.CreateStage(0x130000, "CCharaPcs LoadTex", 0);
    m_loadStages[CCharaPcs::LOAD_STAGE_WEAPON_TEXTURE] = Memory.CreateStage(0x8400, "CCharaPcs LoadWepTex", 0);
    m_loadStages[CCharaPcs::LOAD_STAGE_WEAPON_MODEL] = Memory.CreateStage(0x18000, "CCharaPcs LoadWepModel", 0);
    m_loadStages[CCharaPcs::LOAD_STAGE_FAMILY_MODEL] = Memory.CreateStage(0x10000, "CCharaPcs LoadFaModel", 0);
    m_loadStages[CCharaPcs::LOAD_STAGE_ANIM] =
        Memory.CreateStage(static_cast<s32>(Game.m_currentSceneId) == 4 ? 0x190000UL : 0x1E0000UL,
                           "CCharaPcs LoadAnim", 0);

    CHandle* sentinel = reinterpret_cast<CHandle*>(
        Memory._Alloc(0x194, CharaPcs.m_stage, "p_chara.cpp", 0xDB, 0));
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
        sentinel->m_colorPhase = 1.0f;
        sentinel->m_sortZ = 0.0f;
        sentinel->m_shadowTexturePtr = 0;
        sentinel->m_asyncState = 0;
        sentinel->m_asyncFileHandle = 0;
        sentinel->m_fogBlend = 0.0f;
        sentinel->m_unk0x158 = 0;
        sentinel->m_drawListFlagsBits.m_flag_80 = 1;
    }

    m_handleList = sentinel;
    m_handleList->m_previous = m_handleList;
    m_handleList->m_next = m_handleList;

    for (int i = 0; i < 4; i++) {
        m_cameraFrameCount[i] = 0;
        m_cameraData[i] = 0;
    }

    CLightPcs::CBumpLight bumpLight;

    bumpLight.m_type = 1;
    bumpLight.m_position.x = -533.0f;
    bumpLight.m_position.y = -131.0f;
    bumpLight.m_position.z = -117.0f;
    bumpLight.m_targetPosition.x = 4391.0f;
    bumpLight.m_targetPosition.y = -1864.0f;
    bumpLight.m_targetPosition.z = 7194.0f;
    PSVECSubtract(reinterpret_cast<Vec*>(&bumpLight.m_targetPosition), reinterpret_cast<Vec*>(&bumpLight.m_position),
                  reinterpret_cast<Vec*>(&bumpLight.m_direction));
    PSVECNormalize(reinterpret_cast<Vec*>(&bumpLight.m_direction), reinterpret_cast<Vec*>(&bumpLight.m_direction));
    bumpLight.m_bumpShade[0] = 0x80;
    bumpLight.m_bumpShade[1] = 0x80;
    bumpLight.m_bumpShade[2] = 0x00;
    bumpLight.m_bumpShade[3] = 0xFF;
    bumpLight.m_offsetX = 0.0f;
    bumpLight.m_offsetZ = 0.0f;

    g_pLight = LightPcs.AddBump(&bumpLight, static_cast<CLightPcs::TARGET>(0), Chara.GetMemoryStage(), 4);
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
    Memory.SetDefaultGroup(2);
    CharaPcs.LoadMergeFile(0, 0x10000000, 1);
    Memory.ResetDefaultGroup();
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
    g_pLight = 0;

    if (m_handleList != 0) {
        delete m_handleList;
        m_handleList = 0;
    }

    Memory.DestroyStage(m_loadStages[CCharaPcs::LOAD_STAGE_MODEL]);
    Memory.DestroyStage(m_loadStages[CCharaPcs::LOAD_STAGE_TEXTURE]);
    Memory.DestroyStage(m_loadStages[CCharaPcs::LOAD_STAGE_WEAPON_TEXTURE]);
    Memory.DestroyStage(m_loadStages[CCharaPcs::LOAD_STAGE_WEAPON_MODEL]);
    Memory.DestroyStage(m_loadStages[CCharaPcs::LOAD_STAGE_FAMILY_MODEL]);
    Memory.DestroyStage(m_loadStages[CCharaPcs::LOAD_STAGE_ANIM]);
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

    ReleaseAllAnimBank();

    for (int i = 0; i < 4; i++) {
        m_cameraFrameCount[i] = 0;
        if (m_cameraData[i] != 0) {
            delete[] m_cameraData[i];
            m_cameraData[i] = 0;
        }
    }

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        CHandle* next = handle->m_next;
        delete handle;
        handle = next;
    }

    switch (resetMode) {
    case 1:
    releaseAllArrays:
        m_loadModels.ReleaseAndRemoveAll();
        m_loadAnims.ReleaseAndRemoveAll();
        m_loadTextures.ReleaseAndRemoveAll();
        m_loadPdts.ReleaseAndRemoveAll();
        Chara.ResetAmem(0);
        break;
    case 0: {
        FreeMergeFile(~(m_noFreeMergeMask | 0x10000000U));
        m_loadPdts.ReleaseAndRemoveAll();
        int charaAmemSize = correctLoadAnimAmem();
        if (charaAmemSize < 0) {
            if (System.GetErrorLevel() >= 2U) {
                System.Printf("ガベージコレクションに失敗したので、全て消去します。\n");
            }
            goto releaseAllArrays;
        }

        Chara.ResetAmem(charaAmemSize);
        goto complete;
    }
    }

complete:
    g_pLight->m_bumpShade[3] = 0xFF;
    m_noFreeMergeMask = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80079B40
 * PAL Size: 604b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::correctLoadAnimAmem()
{
    int compactedSize;
    int chunkSize;
    int maxEnd;
    unsigned int nextOffset;
    int i;
    int loadAnimCount;
    int validAnimCount;
    int scanOffset;
    int chunkLoadCount;
    unsigned char* tempBuffer;

    if (System.GetErrorLevel() >= 3U) {
        System.Printf("amem anim ガベージコレクション開始。\n");
    }

    tempBuffer = reinterpret_cast<unsigned char*>(
        Memory._Alloc(0x80000, m_loadStages[CCharaPcs::LOAD_STAGE_ANIM], "p_chara.cpp", 0x162, 1));
    if (tempBuffer == 0) {
        if (System.GetErrorLevel() >= 2U) {
            System.Printf("\x1b[31mamem anim ガベージコレクションのためのテンポラリバッファが確保できません。\n\x1b[0m");
        }
        return -1;
    }

    loadAnimCount = m_loadAnims.GetSize();
    validAnimCount = 0;
    maxEnd = 0;
    compactedSize = 0;
    scanOffset = 0;
    chunkSize = 0;
    for (i = 0; i < loadAnimCount; i++) {
        CLoadAnim* loadAnim = m_loadAnims[static_cast<unsigned long>(i)];
        CChara::CAnim* anim = loadAnim->m_anim;
        const int animEnd = static_cast<int>(anim->GetBankSize()) + anim->GetAmemAddress();
        if (maxEnd < animEnd) {
            maxEnd = animEnd;
        }
        validAnimCount++;
    }

    if (System.GetErrorLevel() >= 3U) {
        System.Printf("amem anim ガベージコレクションしようとしているアニメーションの総数は%dです。\n", validAnimCount);
    }

    do {
        chunkLoadCount = 0;
        nextOffset = 0;
        const unsigned int scanEnd = static_cast<unsigned int>(scanOffset + 0x80000);

        for (i = 0; i < loadAnimCount; i++) {
            CLoadAnim* loadAnim = m_loadAnims[static_cast<unsigned long>(i)];
            const unsigned int animOffset = static_cast<unsigned int>(loadAnim->m_anim->GetAmemAddress());
            const int animSize = static_cast<int>(loadAnim->m_anim->GetBankSize());
            if (animOffset < static_cast<unsigned int>(scanOffset)) {
                continue;
            }
            const unsigned int animEnd = animOffset + static_cast<unsigned int>(animSize);
            if (animEnd >= scanEnd) {
                continue;
            }

            if (nextOffset < static_cast<int>(animEnd)) {
                nextOffset = static_cast<int>(animEnd);
            }
            chunkLoadCount++;

            Memory.CopyFromAMemorySync(
                tempBuffer + chunkSize,
                reinterpret_cast<void*>(animOffset + reinterpret_cast<unsigned int>(m_amemStage->GetTop())),
                static_cast<unsigned long>(animSize));

            loadAnim->m_anim->SetAmemAddress(compactedSize + chunkSize);
            chunkSize += animSize;
        }

        if (chunkLoadCount != 0) {
            const int writeBase = compactedSize + reinterpret_cast<int>(m_amemStage->GetTop());
            Memory.CopyToAMemorySync(
                tempBuffer, reinterpret_cast<void*>(writeBase),
                static_cast<unsigned long>(chunkSize));
            if (System.GetErrorLevel() >= 3U) {
                System.Printf(
                    "書き戻し %d個 %x - %x\n", chunkLoadCount, writeBase, writeBase + chunkSize);
            }
        }

        compactedSize += chunkSize;
        scanOffset = nextOffset;
        chunkSize = 0;
    } while (scanOffset < maxEnd);

    if (tempBuffer != 0) {
        delete tempBuffer;
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("amem anim ガベージコレクション終了。new size =%dbyte\n", compactedSize);
    }
    return compactedSize;
}

/*
 * --INFO--
 * PAL Address: 0x8007999C
 * PAL Size: 420b
 * EN Address: 0x80084aa4
 * EN Size: 232b
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::onScriptChanging(char*)
{
    for (int i = 0; i < 5; i++) {
        m_viewerChoiceColor[i] = CColor(0xFF, 0xFF, 0xFF, 0xFF) * (static_cast<float>(i) / 4.0f);
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
    CHandle* handle = m_handleList->m_next;

    while (m_handleList != handle) {
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

    for (int i = m_loadAnims.GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = m_loadAnims[static_cast<unsigned long>(i)];
        CChara::CAnim* anim = loadAnim->m_anim;
        if (anim->GetRef() == 1) {
            anim->ReleaseBank();
        }
    }

    for (int i = m_loadAnims.GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = m_loadAnims[static_cast<unsigned long>(i)];
        const int bankRefCount = loadAnim->m_anim->GetRef();
        if (bankRefCount == 1) {
            loadAnim->m_anim->AddHistory();
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
    for (int i = m_loadAnims.GetSize() - 1; i >= 0; i--) {
        m_loadAnims[i]->m_anim->ReleaseBank();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::ReleaseUnusedAnimBank()
{
    for (int i = m_loadAnims.GetSize() - 1; i >= 0; i--) {
        CChara::CAnim* anim = m_loadAnims[static_cast<unsigned long>(i)]->m_anim;
        if (anim->GetRef() == 1) {
            anim->ReleaseBank();
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

    int i = m_loadAnims.GetSize() - 1;
    int releaseSize = -1;
    CLoadAnim* releaseAnim = 0;

    for (; i >= 0; i--) {
        CLoadAnim* loadAnim = m_loadAnims[static_cast<unsigned long>(i)];
        CChara::CAnim* anim = loadAnim->m_anim;

        if (anim->IsBanked() > 0 && releaseSize < anim->GetHistory()) {
            releaseSize = anim->GetHistory();
            releaseAnim = loadAnim;
        }
    }

    if (releaseAnim != 0) {
        releaseAnim->m_anim->ReleaseBank();

        if (System.GetErrorLevel() >= 3U) {
            System.Printf("ヒストリー%dのアニメーション%sを開放しました。\n", releaseSize, releaseAnim->m_name);
        }

        return 1;
    }

    return 0;
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
    g_pLight->m_bumpShade[3] = (u8)alpha;
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
        LightPcs.SetAmbient(CColor(0x00, 0x00, 0x00, 0xFF).color);
        LightPcs.SetNumDiffuse(0);
        LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), 0, 0xFFFFFFFF);
    } else {
        Graphic.SetFog(1, 0);
        LightPcs.SetAmbient(m_viewerAmbientColor[0]);
        LightPcs.SetNumDiffuse(3);

        for (unsigned long lightIndex = 0; lightIndex < 3; lightIndex++) {
            LightPcs.SetDiffuse(lightIndex, m_viewerDiffuseColor[0][lightIndex], &m_viewerDiffusePos[lightIndex],
                                static_cast<int>(lightIndex == 2));
        }
    }

    if (envMode == 4) {
        GXSetProjection(CameraPcs.GetProjectionMatrix(), GX_PERSPECTIVE);
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
    CHandle* head = m_handleList;
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
 * PAL Address: 0x80079494
 * PAL Size: 252b
 * EN Address: 0x80078E74
 * EN Size: 252b
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::GetTexShadow(int startIndex, int maxCount, _GXTexObj* texObjs, Vec* worldPositions, float (*shadowMatrices)[3][4])
{
    CHandle* handle = m_handleList->m_next;
    int shadowIndex = 0;

    while (m_handleList != handle) {
        if ((handle->m_flags & 0x200) != 0 && handle->m_shadowTexturePtr != 0) {
            if (startIndex <= shadowIndex) {
                const int outIndex = shadowIndex - startIndex;
                PSMTXConcat(m_texShadowProjectionMtx, handle->m_shadowViewMtx, shadowMatrices[outIndex]);

                GXInitTexObj(
                    &texObjs[outIndex], handle->m_shadowTexturePtr, m_texShadowSize, m_texShadowSize, GX_TF_I4, GX_CLAMP, GX_CLAMP,
                    GX_FALSE);

                Mtx modelMtx;
                PSMTXCopy(handle->m_model->GetMatrix(), modelMtx);
                worldPositions[outIndex].x = modelMtx[0][3];
                worldPositions[outIndex].y = modelMtx[1][3];
                worldPositions[outIndex].z = modelMtx[2][3];
            }

            shadowIndex++;
            if (startIndex + maxCount <= shadowIndex) {
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
    InitEnv(0);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlag() & 0x8000) != 0) {
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
    InitEnv(0);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlag() & 0x8000) != 0) {
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
    CHandle* handle = m_handleList->m_next;
    int shadowCount = 0;
    for (; m_handleList != handle; handle = handle->m_next) {
        if ((handle->m_flags & 0x200) != 0) {
            shadowCount++;
        }
    }
    if (shadowCount == 0) {
        return;
    }

    _GXTexObj backBufferTexObj;

    GXSetZMode(GX_FALSE, GX_ALWAYS, GX_FALSE);
    Graphic.GetBackBufferRect2(Graphic.GetTmpFrameBuffer(), &backBufferTexObj, 0, 0, m_texShadowSize, m_texShadowSize, 0, GX_NEAR, GX_TF_RGBA8, 0);

    InitEnv(1);

    GXSetPixelFmt((GXPixelFmt)1, GX_ZC_LINEAR);
    _GXColor savedCopyClearColor = Graphic.GetCopyClearColor();
    GXSetAlphaUpdate(GX_TRUE);
    GXSetViewport(0.0f, 0.0f, static_cast<float>(m_texShadowSize), static_cast<float>(m_texShadowSize), 0.0f, 1.0f);
    GXSetScissor(0, 0, static_cast<unsigned int>(m_texShadowSize), static_cast<unsigned int>(m_texShadowSize));
    Graphic.SetCopyClear(CColor(0x00, 0x00, 0x00, 0x00).color, 0xFFFFFF);

    m_texShadowTextureOffset = 0;
    m_texShadowTextureBase = Graphic.GetTmpFrameBuffer();
    m_texShadowTextureSize = 0xD2000;
    m_texShadowTextureOffset += m_texShadowSize * m_texShadowSize * 4;
    C_MTXLightPerspective(m_texShadowProjectionMtx, CameraPcs.GetFov(), 4.0f / 3.0f, 0.5f,
                          -0.5f, 0.5f, 0.5f);

    handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlag() & 0x8000) != 0) {
            handle->draw(2, 1);
        }
        handle = handle->m_next;
    }

    Graphic.SetViewport();
    Graphic.SetStdPixelFmt();
    Graphic.SetCopyClear(savedCopyClearColor, 0xFFFFFF);
    gUtil.RenderTextureQuad(
        0.0f, 0.0f, static_cast<float>(m_texShadowSize), static_cast<float>(m_texShadowSize), &backBufferTexObj, 0, 0, 0,
        GX_BL_SRCALPHA, GX_BL_INVSRCALPHA);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::drawShadow()
{
    if (CameraPcs.GetFullScreenShadowEnable() == 0) {
        return;
    }

    InitEnv(2);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlag() & 0x8000) != 0) {
            handle->draw(1, 1);
        }
        handle = handle->m_next;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80078C8C
 * PAL Size: 284b
 * EN Address: 0x8007866C
 * EN Size: 284b
 * JP Address: TODO
 * JP Size: TODO
 */
CTextureSet* CCharaPcs::createTextureSet(void* textureData, int useWeaponStage)
{
    CTextureSet* textureSet = new (CharaPcs.m_stage, "p_chara.cpp", 0x397) CTextureSet;
    textureSet->Create(textureData,
                       GET_CHARA_ALLOC_STAGE_S(CharaPcs.GetCharaAllocStage(),
                                               CharaPcs.m_loadStages[useWeaponStage ? LOAD_STAGE_WEAPON_TEXTURE : LOAD_STAGE_TEXTURE]),
                       0, 0, 0, 0);
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

    for (int i = m_loadModels.GetSize() - 1; i >= 0; i--) {
        CLoadModel* loadModel = m_loadModels[static_cast<unsigned long>(i)];
        if ((((loadModel->m_mergeFileId < 0) || (loadModel->m_streamMode != 0)) && loadModel->GetRef() == 1) ||
            (loadModel->m_mergeFileId >= 0 && (releaseMask & loadModel->m_mergeFlags) != 0)) {
            if (loadModel->m_streamMode != 0 && loadModel->GetRef() == 1) {
                ReleaseShared(loadModel->m_model);
            } else {
                CLoadModel* releasedModel = loadModel;
                ReleaseSharedNonNull(releasedModel);
                m_loadModels.RemoveAt(static_cast<unsigned long>(i));
            }
        } else {
            activeCount++;
        }
    }

    for (int i = m_loadTextures.GetSize() - 1; i >= 0; i--) {
        CLoadTexture* loadTexture = m_loadTextures[static_cast<unsigned long>(i)];
        if ((((loadTexture->m_mergeFileId < 0) || (loadTexture->m_streamMode != 0)) && loadTexture->GetRef() == 1) ||
            (loadTexture->m_mergeFileId >= 0 && (releaseMask & loadTexture->m_mergeFlags) != 0)) {
            if (loadTexture->m_streamMode != 0 && loadTexture->GetRef() == 1) {
                ReleaseShared(loadTexture->m_textureSet);
            } else {
                CLoadTexture* releasedTexture = loadTexture;
                ReleaseSharedNonNull(releasedTexture);
                m_loadTextures.RemoveAt(static_cast<unsigned long>(i));
            }
        } else {
            activeCount++;
        }
    }

    for (int i = m_loadPdts.GetSize() - 1; i >= 0; i--) {
        CLoadPdt* loadPdt = m_loadPdts[static_cast<unsigned long>(i)];
        if ((loadPdt->m_mergeFileId < 0 && loadPdt->GetRef() == 1) ||
            (loadPdt->m_mergeFileId >= 0 && (releaseMask & loadPdt->m_mergeFlags) != 0)) {
            CLoadPdt* releasedPdt = loadPdt;
            ReleaseSharedNonNull(releasedPdt);
            m_loadPdts.RemoveAt(static_cast<unsigned long>(i));
        } else {
            activeCount++;
        }
    }

    return activeCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::releaseUnuseLoadAnim(CCharaPcs::CLoadAnim* target, int releaseMask)
{
    for (int i = m_loadAnims.GetSize() - 1; i >= 0; i--) {
        CLoadAnim* loadAnim = m_loadAnims[static_cast<unsigned long>(i)];
        if (((loadAnim->m_mergeFileId < 0) && (loadAnim->GetRef() == 1)) ||
            ((loadAnim->m_mergeFileId >= 0) && ((releaseMask & loadAnim->m_mergeFlags) != 0))) {
            if (target == 0 || target == loadAnim) {
                CRef* loadAnimRef = loadAnim;
                loadAnimRef->Release();
                m_loadAnims.RemoveAt(static_cast<unsigned long>(i));
                if (target != 0) {
                    return;
                }
            }
        }
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::DumpLoad()
{
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("model\n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("no  t num lv  mask     addr     a a-addr   a-size\n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("--- - --- --- -------- -------- - -------- --------\n");
    }
    int modelCount = m_loadModels.GetSize();
    for (int i = 0; i < modelCount; i++) {
        CLoadModel* loadModel = m_loadModels[static_cast<unsigned long>(i)];
        if (System.GetErrorLevel() >= 3U) {
            int streamMode = loadModel->m_streamMode;
            unsigned int streamSize = streamMode != 0 ? static_cast<unsigned int>(loadModel->m_streamSize) : 0;
            unsigned int streamAddr = streamMode != 0 ? loadModel->m_streamOffset : 0;

            System.Printf(
                "%3d %1d %3d %3d %08x %08x %d %08x %8d\n", i, loadModel->m_keyTag, loadModel->m_keyId,
                loadModel->m_mergeFileId, loadModel->m_mergeFlags, reinterpret_cast<unsigned int>(loadModel->m_model),
                streamMode, streamAddr, streamSize);
        }
    }

    if (System.GetErrorLevel() >= 3U) {
        System.Printf("texture\n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("no  t num t lv  mask     addr     a a-addr   a-size\n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("--- - --- - --- -------- -------- - -------- --------\n");
    }
    int textureCount = m_loadTextures.GetSize();
    for (int i = 0; i < textureCount; i++) {
        CLoadTexture* loadTexture = m_loadTextures[static_cast<unsigned long>(i)];
        if (System.GetErrorLevel() >= 3U) {
            int streamMode = loadTexture->m_streamMode;
            unsigned int streamSize = streamMode != 0 ? static_cast<unsigned int>(loadTexture->m_streamSize) : 0;
            unsigned int streamAddr = streamMode != 0 ? loadTexture->m_streamOffset : 0;

            System.Printf(
                "%3d %1d %3d %1d %3d %08x %08x %d %08x %8d\n", i, loadTexture->m_keyTag, loadTexture->m_keyId,
                loadTexture->m_variantTag, loadTexture->m_mergeFileId, loadTexture->m_mergeFlags,
                reinterpret_cast<unsigned int>(loadTexture->m_textureSet), streamMode, streamAddr, streamSize);
        }
    }

    if (System.GetErrorLevel() >= 3U) {
        System.Printf("pdt\n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("no  t num t pdt hdl  lv  mask    \n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("--- - --- - -------- --- --------\n");
    }
    int pdtCount = m_loadPdts.GetSize();
    for (int i = 0; i < pdtCount; i++) {
        CLoadPdt* loadPdt = m_loadPdts[static_cast<unsigned long>(i)];
        if (System.GetErrorLevel() >= 3U) {
            System.Printf(
                "%3d %1d %3d %1d %8d %3d %08x\n", i, loadPdt->m_keyTag, loadPdt->m_keyId,
                loadPdt->m_variantTag, loadPdt->m_pdtSlot, loadPdt->m_mergeFileId,
                loadPdt->m_mergeFlags);
        }
    }

    if (System.GetErrorLevel() >= 3U) {
        System.Printf("anim\n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("no  t num name           lv  mask     addr     banksize banksum  histroy\n");
    }
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("--- - --- -------------- --- -------- -------- -------- -------- --------\n");
    }
    int animCount = m_loadAnims.GetSize();
    int totalBankSize = 0;
    for (int i = 0; i < animCount; i++) {
        CLoadAnim* loadAnim = m_loadAnims[static_cast<unsigned long>(i)];
        if (System.GetErrorLevel() >= 3U) {
            System.Printf(
                "%3d %1d %3d %14s %3d %08x %08x %8d %8d %8d\n", i, loadAnim->m_keyTag, loadAnim->m_keyId,
                loadAnim->m_name, loadAnim->m_mergeFileId, loadAnim->m_mergeFlags,
                reinterpret_cast<unsigned int>(loadAnim->m_anim), loadAnim->m_anim->GetBankSize(), totalBankSize, loadAnim->m_anim->GetHistory());
        }
        totalBankSize += loadAnim->m_anim->GetBankSize();
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel* CCharaPcs::searchModel(int keyTag, int keyId)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_loadModels.GetSize()); i++) {
        CLoadModel* loadModel = m_loadModels[i];
        if (loadModel->m_keyTag == keyTag && loadModel->m_keyId == keyId) {
            return loadModel;
        }
    }
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture* CCharaPcs::searchTexture(int keyTag, int keyId, int variantTag)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_loadTextures.GetSize()); i++) {
        CLoadTexture* loadTexture = m_loadTextures[i];
        if (loadTexture->m_keyTag == keyTag && loadTexture->m_keyId == keyId &&
            loadTexture->m_variantTag == variantTag) {
            return loadTexture;
        }
    }
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim* CCharaPcs::searchAnim(int keyTag, int keyId, char* name)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_loadAnims.GetSize()); i++) {
        CLoadAnim* loadAnim = m_loadAnims[i];
        if (loadAnim->m_keyTag == keyTag && loadAnim->m_keyId == keyId &&
            strcmp(name, loadAnim->m_name) == 0) {
            return loadAnim;
        }
    }
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadPdt* CCharaPcs::searchPdt(int keyTag, int keyId, int variantTag)
{
    for (unsigned int i = 0; i < static_cast<unsigned int>(m_loadPdts.GetSize()); i++) {
        CLoadPdt* loadPdt = m_loadPdts[i];
        if (loadPdt->m_keyTag == keyTag && loadPdt->m_keyId == keyId && loadPdt->m_variantTag == variantTag) {
            return loadPdt;
        }
    }
    return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800783D0
 * PAL Size: 488b
 * EN Address: 0x80077DB0
 * EN Size: 488b
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::LoadCam(int index, char* fileName)
{
    char path[0x104];
    CChunkFile::CChunk chunk;

    if (m_cameraData[index] != 0) {
        delete[] m_cameraData[index];
        m_cameraData[index] = 0;
    }

    sprintf(path, "dvd/cft/%s.cmd", fileName);
    CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
    if (fileHandle == 0) {
        return;
    }

    File.Read(fileHandle);
    File.SyncCompleted(fileHandle);

    CChunkFile chunkFile(File.GetBuffer());
    while (chunkFile.GetNextChunk(chunk)) {
        switch (chunk.m_id) {
        case 'CAM ': {
            m_cameraFrameCount[index] = static_cast<int>(chunk.m_arg0);

            m_cameraData[index] = new (CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_ANIM], "p_chara.cpp", 0x4D4)
                CCameraFrame[static_cast<unsigned long>(m_cameraFrameCount[index])];

            for (int frame = 0; frame < m_cameraFrameCount[index]; frame++) {
                m_cameraData[index][frame].m_values[0].m_float = chunkFile.GetF4();
                m_cameraData[index][frame].m_values[1].m_float = chunkFile.GetF4();
                m_cameraData[index][frame].m_values[2].m_float = chunkFile.GetF4();
                m_cameraData[index][frame].m_values[3].m_float = chunkFile.GetF4();
                m_cameraData[index][frame].m_values[4].m_float = chunkFile.GetF4();
                m_cameraData[index][frame].m_values[5].m_float = chunkFile.GetF4();
                m_cameraData[index][frame].m_values[6].m_float = chunkFile.GetF4();
                m_cameraData[index][frame].m_values[7].m_float = chunkFile.GetF4();
            }
            break;
        }
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
    if (isCached(mergeFileId, mergeFlags)) {
        System.Printf("CCharaPcs.LoadMergeFile: %dはすでにキャッシングされています。\n", mergeFileId);
        return;
    }

    int mergePartCount = 1;
    for (int mergePartIndex = 0; mergePartIndex < mergePartCount; mergePartIndex++) {
        char path[0x100];
        sprintf(path, "dvd/mrg/m%04d_%02d.mrg", mergeFileId, mergePartIndex);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {

            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            CChunkFile chunkFile(File.GetBuffer());
            CChunkFile::CChunk chunk;
            while (chunkFile.GetNextChunk(chunk)) {
                switch (chunk.m_id) {
                case 'MRG ':
                    break;
                default:
                    continue;
                }

                chunkFile.PushChunk();
                while (chunkFile.GetNextChunk(chunk)) {
                    switch (chunk.m_id) {
                    case 'INFO':
                        mergePartCount = static_cast<int>(chunkFile.Get4());
                        continue;
                    case 'DATA':
                        break;
                    default:
                        continue;
                    }

                    int dataType = -1;
                    int keyTag = -1;
                    int keyId = -1;
                    int variantTag = -1;
                    int hasDynamics = 0;
                    char* animName = 0;

                    chunkFile.PushChunk();
                    while (chunkFile.GetNextChunk(chunk)) {
                        switch (chunk.m_id) {
                        case 'NAME':
                            animName = chunkFile.GetString();
                            continue;
                        case 'INFO':
                            dataType = static_cast<int>(chunkFile.Get4());
                            keyTag = static_cast<int>(chunkFile.Get4());
                            keyId = static_cast<int>(chunkFile.Get4());
                            variantTag = static_cast<int>(chunkFile.Get4());
                            hasDynamics = static_cast<int>(chunkFile.Get4());
                            continue;
                        case 'RAW ':
                            break;
                        default:
                            continue;
                        }

                        switch (dataType) {
                        case 0: {
                            CLoadModel* cachedModel = CharaPcs.searchModel(keyTag, keyId);
                            if (cachedModel == 0) {
                                cachedModel = loadModel(chunkFile.GetAddress(), keyTag, keyId, mergeFileId, mergeFlags,
                                                        streamToAmem, chunk.m_size);
                            }

                            if (hasDynamics != 0) {
                                chunkFile.GetNextChunk(chunk);
                                CMemory::CStage* dynStage = GET_CHARA_ALLOC_STAGE_S(CharaPcs.GetCharaAllocStage(), CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_MODEL]);
                                cachedModel->m_model->CreateDynamics(chunkFile.GetAddress(), dynStage);
                            }
                            break;
                        }
                        case 1: {
                            if (CharaPcs.searchTexture(keyTag, keyId, variantTag) == 0) {
                                loadTexture(chunkFile.GetAddress(), keyTag, keyId, variantTag, mergeFileId, mergeFlags,
                                            streamToAmem, chunk.m_size);
                            }
                            break;
                        }
                        case 2: {
                            if (CharaPcs.searchAnim(keyTag, keyId, animName) == 0) {
                                loadAnimBuffer(chunkFile.GetAddress(), animName, keyTag, keyId, mergeFileId, mergeFlags);
                            }
                            break;
                        }
                        case 3: {
                            Sound.LoadSe(chunkFile.GetAddress());
                            break;
                        }
                        case 4: {
                            Sound.LoadWave(chunkFile.GetAddress());
                            break;
                        }
                        case 5: {
                            CLoadPdt* loadPdt = CharaPcs.searchPdt(keyTag, keyId, variantTag);

                            void* primaryData = chunkFile.GetAddress();
                            const int primarySize = static_cast<int>(chunk.m_size);
                            if (loadPdt == 0) {
                                chunkFile.GetNextChunk(chunk);
                                void* secondaryData = chunkFile.GetAddress();
                                const int secondarySize = static_cast<int>(chunk.m_size);
                                loadPdt = new (CharaPcs.m_stage, "p_chara.cpp", 0x572) CLoadPdt;
                                loadPdt->m_keyTag = keyTag;
                                loadPdt->m_keyId = keyId;
                                loadPdt->m_variantTag = variantTag;
                                loadPdt->m_mergeFileId = mergeFileId;
                                loadPdt->m_mergeFlags = mergeFlags;
                                loadPdt->m_pdtSlot = PartPcs.LoadMonsterPdt(
                                    keyId, variantTag, primaryData, primarySize, secondaryData, secondarySize);
                                CharaPcs.m_loadPdts.Add(loadPdt);
                            }
                            break;
                        }
                        }
                    }
                    chunkFile.PopChunk();
                }
                chunkFile.PopChunk();
            }

            File.Close(fileHandle);
        } else {
            System.Printf("CCharaPcs.LoadMergeFile: %dはありません。\n", mergeFileId);
            break;
        }
    }

    System.Printf("CCharaPcs.LoadMergeFile: %d 0x%08x\n", mergeFileId, mergeFlags);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::FreeMergeFile(int releaseMask)
{
    releaseUnuseLoadModel(releaseMask);
    releaseUnuseLoadAnim(0, releaseMask);
    System.Printf("CCharaPcs.FreeMergeFile: 0x%08x\n", releaseMask);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
inline int CCharaPcs::isCached(int mergeFileId, int)
{
    unsigned int i;

    for (i = 0; i < m_loadModels.GetSize(); i++) {
        CLoadModel* loadModel = m_loadModels[i];
        if (loadModel->m_mergeFileId == mergeFileId) {
            return 1;
        }
    }
    for (i = 0; i < m_loadTextures.GetSize(); i++) {
        CLoadTexture* loadTexture = m_loadTextures[i];
        if (loadTexture->m_mergeFileId == mergeFileId) {
            return 1;
        }
    }
    for (i = 0; i < m_loadPdts.GetSize(); i++) {
        CLoadPdt* loadPdt = m_loadPdts[i];
        if (loadPdt->m_mergeFileId == mergeFileId) {
            return 1;
        }
    }
    for (i = 0; i < m_loadAnims.GetSize(); i++) {
        CLoadAnim* loadAnim = m_loadAnims[i];
        if (loadAnim->m_mergeFileId == mergeFileId) {
            return 1;
        }
    }
    return 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadModel* CCharaPcs::loadModel(void* data, int keyTag, int keyId, int mergeFileId, int mergeFlags,
                                            int streamToAmem, int size)
{
    CLoadModel* loadModel = new (CharaPcs.m_stage, "p_chara.cpp", 0x5E8) CLoadModel;
    loadModel->m_keyTag = keyTag;
    loadModel->m_keyId = keyId;
    loadModel->m_mergeFileId = mergeFileId;
    loadModel->m_mergeFlags = mergeFlags;
    CharaPcs.m_loadModels.Add(loadModel);

    if (streamToAmem == 0) {
        CChara::CModel* model = new (CharaPcs.m_stage, "p_chara.cpp", 0x5F1) CChara::CModel;
        model->Create(data, GET_CHARA_ALLOC_STAGE_S(CharaPcs.GetCharaAllocStage(), CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_MODEL]));
        loadModel->m_model = model;
    } else {
        loadModel->m_streamOffset = m_loadStreamCursor;
        loadModel->m_streamSize = size;
        loadModel->m_streamMode = 1;
        Memory.CopyToAMemorySync(
            data, reinterpret_cast<void*>(m_loadStreamCursor + reinterpret_cast<unsigned int>(m_amemWorkStage->GetTop())),
            static_cast<unsigned long>(size));
        m_loadStreamCursor += static_cast<unsigned int>(size);
    }
    return loadModel;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadTexture* CCharaPcs::loadTexture(void* data, int keyTag, int keyId, int variantTag, int mergeFileId,
                                                int mergeFlags, int streamToAmem, int size)
{
    CLoadTexture* loadTexture = new (CharaPcs.m_stage, "p_chara.cpp", 0x609) CLoadTexture;
    loadTexture->m_keyTag = keyTag;
    loadTexture->m_keyId = keyId;
    loadTexture->m_variantTag = variantTag;
    loadTexture->m_mergeFileId = mergeFileId;
    loadTexture->m_mergeFlags = mergeFlags;
    CharaPcs.m_loadTextures.Add(loadTexture);

    if (streamToAmem == 0) {
        loadTexture->m_textureSet = CharaPcs.createTextureSet(data, keyTag == 4);
    } else {
        loadTexture->m_streamOffset = m_loadStreamCursor;
        loadTexture->m_streamSize = size;
        loadTexture->m_streamMode = 1;
        Memory.CopyToAMemorySync(
            data, reinterpret_cast<void*>(m_loadStreamCursor + reinterpret_cast<unsigned int>(m_amemWorkStage->GetTop())),
            static_cast<unsigned long>(size));
        m_loadStreamCursor += static_cast<unsigned int>(size);
    }
    return loadTexture;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CLoadAnim* CCharaPcs::loadAnimBuffer(void* data, char* name, int keyTag, int keyId, int mergeFileId,
                                                int mergeFlags)
{
    CChara::CAnim* anim = new (CharaPcs.m_stage, "p_chara.cpp", 0x62A) CChara::CAnim;
    anim->Create(data, CharaPcs.m_loadStages[CCharaPcs::LOAD_STAGE_ANIM]);

    CLoadAnim* loadAnim = new (CharaPcs.m_stage, "p_chara.cpp", 0x62D) CLoadAnim;
    loadAnim->m_keyId = keyId;
    loadAnim->m_keyTag = keyTag;
    strcpy(loadAnim->m_name, name);
    loadAnim->m_anim = anim;
    loadAnim->m_mergeFileId = mergeFileId;
    loadAnim->m_mergeFlags = mergeFlags;
    CharaPcs.m_loadAnims.Add(loadAnim);
    return loadAnim;
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
    Mtx texMtx;
    Mtx44 projectionMtx;
    Mtx identityMtx;

    CameraPcs.GetViewMatrix(savedCameraMtx);

    C_MTXOrtho(projectionMtx, 0.0f, 448.0f, 0.0f, 640.0f, 10.0f, 100010.0f);
    GXSetProjection(projectionMtx, GX_ORTHOGRAPHIC);
    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);
    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_INVSRCALPHA, GX_LO_AND);

    GXSetChanMatColor(GX_COLOR0A0, CColor(0x00, 0x00, 0x00, 0xFF).color);
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

    {
        float zero = 0.0f;
        float depth = -100000.0f;
        float width = 640.0f;
        float height = 448.0f;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(zero, zero, depth);
        GXPosition3f32(width, zero, depth);
        GXPosition3f32(zero, height, depth);
        GXPosition3f32(width, height, depth);
    }

    CameraPcs.GetProjectionMatrix(projectionMtx);
    GXSetProjection(projectionMtx, GX_PERSPECTIVE);

    Vec up;
    up.x = 0.0f;
    up.y = 1.0f;
    up.z = 0.0f;
    C_MTXLookAt(lookAtMtx, &m_overlapEyePos, &up, &m_overlapTargetPos);
    CameraPcs.SetViewMatrix(lookAtMtx);

    InitEnv(0);

    CHandle* handle = m_handleList->m_next;
    while (m_handleList != handle) {
        if ((DbgMenuPcs.GetDbgFlag() & 0x8000) != 0) {
            handle->draw(0, 1);
        }
        handle = handle->m_next;
    }

    GXSetNumChans(1);
    GXSetChanCtrl(GX_COLOR0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_SPOT);
    GXSetChanCtrl(GX_ALPHA0, GX_DISABLE, GX_SRC_REG, GX_SRC_REG, GX_LIGHT_NULL, GX_DF_CLAMP, GX_AF_NONE);

    GXSetChanMatColor(GX_COLOR0A0, CColor(0x00, 0x00, 0x00, static_cast<unsigned char>(m_overlapAlpha & 0xFF)).color);
    PSMTXIdentity(identityMtx);
    GXLoadPosMtxImm(identityMtx, GX_PNMTX0);
    GXSetCullMode(GX_CULL_NONE);
    C_MTXOrtho(projectionMtx, 0.0f, 448.0f, 0.0f, 640.0f, 0.0f, -100.0f);
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

    {
        float zero = 0.0f;
        float width = 640.0f;
        float height = 448.0f;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(zero, zero, zero);
        GXPosition3f32(width, zero, zero);
        GXPosition3f32(zero, height, zero);
        GXPosition3f32(width, height, zero);
    }

    _GXSetBlendMode(GX_BM_BLEND, GX_BL_SRCALPHA, GX_BL_ONE, GX_LO_NOOP);
    GXSetChanMatColor(GX_COLOR0A0, CColor(0xFF, 0xFF, 0xFF, 0xFF).color);
    GXLoadTexObj(backBufferTex, GX_TEXMAP0);
    PSMTXScale(texMtx, 1.0f / 640.0f, 1.0f / 448.0f, 1.0f);
    GXLoadTexMtxImm(texMtx, GX_TEXMTX0, GX_MTX2x4);
    GXSetNumTexGens(1);
    GXSetTexCoordGen2(GX_TEXCOORD0, GX_TG_MTX2x4, GX_TG_TEX0, GX_TEXMTX0, GX_FALSE, GX_PTIDENTITY);
    GXClearVtxDesc();
    GXSetVtxDesc(GX_VA_POS, GX_DIRECT);
    GXSetVtxDesc(GX_VA_TEX0, GX_DIRECT);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_POS, GX_POS_XYZ, GX_F32, 0);
    GXSetVtxAttrFmt(GX_VTXFMT0, GX_VA_TEX0, GX_TEX_ST, GX_S16, 0);
    _GXSetTevOp(GX_TEVSTAGE0, GX_MODULATE);

    {
        float zero = 0.0f;
        float width = 640.0f;
        float height = 448.0f;
        GXBegin(GX_TRIANGLESTRIP, GX_VTXFMT0, 4);
        GXPosition3f32(zero, zero, zero);
        GXTexCoord2u16(0, 0);
        GXPosition3f32(width, zero, zero);
        GXTexCoord2u16(0x280, 0);
        GXPosition3f32(zero, height, zero);
        GXTexCoord2u16(0, 0x1C0);
        GXPosition3f32(width, height, zero);
        GXTexCoord2u16(0x280, 0x1C0);
    }

    CameraPcs.GetProjectionMatrix(projectionMtx);
    GXSetProjection(projectionMtx, GX_PERSPECTIVE);
    CameraPcs.SetViewMatrix(savedCameraMtx);
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
    return Memory._Alloc(size, CharaPcs.m_stage, file, line, 0);
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
	m_modelLoadRef = 0;
	m_texLoadRef = 0;

	for (int i = 0; i < 64; ++i)
	{
		m_animSlot[i] = 0;
	}

	// PDT load ref
	m_pdtLoadRef = (CLoadPdt*)nullptr;

	// Playback / state
	m_currentAnimIndex = -1;
	m_flags = 0;

	m_colorPhase = 1.0f;
	m_sortZ = 0.0f;
	m_shadowTexturePtr = nullptr;

	m_asyncState = 0;
	m_asyncFileHandle = (CFile::CHandle*)nullptr;

	m_fogBlend = 0.0f;
	m_unk0x158 = 0;
	m_drawListFlagsBits.m_flag_80 = 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CCharaPcs::CHandle::~CHandle()
{
    CancelLoadModelASync();
    PartMng.pppDeleteCHandle(this);
    Remove();
    Graphic._WaitDrawDone("p_chara.cpp", 0x717);
    FreeModel();
    FreeAnim(-1);
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

    CCharaPcs::CHandle* head = CharaPcs.m_handleList->m_previous;

    m_previous = head;
    m_next = head->m_next;
    head->m_next->m_previous = this;
    head->m_next = this;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::Remove()
{
    if (m_next != 0 && m_previous != 0) {
        m_previous->m_next = m_next;
        m_next->m_previous = m_previous;
        m_previous = 0;
        m_next = 0;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::ChangeTexture(
    int charaKind, unsigned long charaNo, unsigned long textureVariant, int mergeFileId, int mergeFlags)
{
    Graphic._WaitDrawDone("p_chara.cpp", 0x749);
    m_model->AttachTextureSet(0);

    ReleaseShared(m_textureSet);
    ReleaseShared(m_texLoadRef);

    char basePath[0x100];
    char path[0x100];
    BuildCharaBasePath(charaKind, charaNo, basePath);

    CLoadTexture* loadTexture;
    for (unsigned int i = 0; i < static_cast<unsigned int>(CharaPcs.m_loadTextures.GetSize()); i++) {
        CLoadTexture* it = CharaPcs.m_loadTextures[i];
        if (it->m_keyTag == charaKind && static_cast<unsigned long>(it->m_keyId) == charaNo &&
            static_cast<unsigned long>(it->m_variantTag) == textureVariant) {
            loadTexture = it;
            goto foundTexture;
        }
    }
    loadTexture = 0;
foundTexture:

    if (loadTexture != 0) {
        if (loadTexture->m_streamMode != 0 && loadTexture->GetRef() == 1) {
            File.LockBuffer();
            Memory.CopyFromAMemorySync(
                File.GetBuffer(),
                reinterpret_cast<void*>(
                    loadTexture->m_streamOffset +
                    reinterpret_cast<unsigned int>(CharaPcs.m_amemWorkStage->GetTop())),
                static_cast<unsigned long>(loadTexture->m_streamSize));
            loadTexture->m_textureSet = CharaPcs.createTextureSet(File.GetBuffer(), charaKind == 4);
            File.UnlockBuffer();

            if (System.GetErrorLevel() >= 3U) {
                System.Printf("Merge: \x1b[32mテクスチャをAMEMから読み込みました。type = %d number = %d tex = %d\n\x1b[0m", charaKind, static_cast<unsigned int>(charaNo),
                              static_cast<int>(textureVariant));
            }
        }

        m_texLoadRef = loadTexture;
        loadTexture->AddRef();
        m_textureSet = loadTexture->m_textureSet;
        m_textureSet->AddRef();
        goto attach;
    } else {
        if (System.GetErrorLevel() >= 1U) {
            System.Printf("\x1b[31mMerge: テクスチャをDVDから読み込みました。type = %d number = %d tex = %d\n\x1b[0m", charaKind, static_cast<unsigned int>(charaNo),
                          static_cast<int>(textureVariant));
        }

        if (textureVariant >= 1) {
            sprintf(path, "%s_%c", basePath, static_cast<int>(textureVariant) + 0x61);
        } else {
            strcpy(path, basePath);
        }
        strcat(path, ".tex");

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            m_texLoadRef = CharaPcs.loadTexture(File.GetBuffer(), charaKind, charaNo, textureVariant, mergeFileId,
                                                mergeFlags, 0, 0);
            File.Close(fileHandle);

            m_texLoadRef->AddRef();
            m_textureSet = m_texLoadRef->m_textureSet;
            m_textureSet->AddRef();
        } else {
            m_textureSet = 0;
            if (charaKind != 5 && System.GetErrorLevel() >= 2U) {
                System.Printf("テクスチャがありません。場合によってはハングするかもしれません。%s\n", path);
            }
        }
    }
attach:
    m_model->AttachTextureSet(m_textureSet);
}

/*
 * --INFO--
 * PAL Address: 0x80075E34
 * PAL Size: 2352b
 * EN Address: 0x800881D4
 * EN Size: 1624b
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::CHandle::LoadModel(
    int charaKind, unsigned long charaNo, unsigned long textureVariant, unsigned long unusedArg, int mergeFileId,
    int mergeFlags, int specialModelStage)
{
    (void)unusedArg;

    FreeModel();

    m_charaKind = charaKind;
    m_charaNo = static_cast<int>(charaNo);
    m_textureVariant = static_cast<unsigned int>(textureVariant);

    char basePath[0x100];
    char path[0x100];
    BuildCharaBasePath(charaKind, charaNo, basePath);

    CLoadModel* loadModel = CharaPcs.searchModel(charaKind, static_cast<int>(charaNo));

    if (loadModel != 0) {
        m_modelLoadRef = loadModel;

        LoadStage modelStageIndex;
        if (specialModelStage != 0) {
            LoadStage specialIndex = LOAD_STAGE_WEAPON_MODEL;
            if (m_charaKind == 3) {
                specialIndex = LOAD_STAGE_FAMILY_MODEL;
            }
            modelStageIndex = specialIndex;
        } else {
            modelStageIndex = LOAD_STAGE_MODEL;
        }

        if (loadModel->GetRef() == 1) {
            if (loadModel->m_streamMode != 0) {
                File.LockBuffer();
                Memory.CopyFromAMemorySync(
                    File.GetBuffer(),
                    reinterpret_cast<void*>(
                        loadModel->m_streamOffset +
                        reinterpret_cast<unsigned int>(CharaPcs.m_amemWorkStage->GetTop())),
                    static_cast<unsigned long>(loadModel->m_streamSize));
                CChara::CModel* model =
                    new (CharaPcs.m_stage, "p_chara.cpp", 0x7C7) CChara::CModel;
                model->Create(File.GetBuffer(), GET_CHARA_ALLOC_STAGE_S(CharaPcs.GetCharaAllocStage(), CharaPcs.m_loadStages[modelStageIndex]));
                loadModel->m_model = model;
                File.UnlockBuffer();

                if (System.GetErrorLevel() >= 3U) {
                    System.Printf("Merge: \x1b[32mモデルをAMEMから読み込みました。type = %d number = %d\n\x1b[0m", charaKind, static_cast<int>(charaNo));
                }
            }

            loadModel->AddRef();
            m_model = loadModel->m_model;
            m_model->AddRef();
            m_model->Init();
        } else {
            loadModel->AddRef();
            m_model = loadModel->m_model->Duplicate(GET_CHARA_ALLOC_STAGE_S(CharaPcs.GetCharaAllocStage(), CharaPcs.m_loadStages[modelStageIndex]));
        }
    } else {
        if (System.GetErrorLevel() >= 1U) {
            System.Printf("\x1b[31mMerge: モデルをDVDから読み込みました。type = %d number = %d\n\x1b[0m", charaKind, static_cast<int>(charaNo));
        }

        strcpy(path, basePath);
        strcat(path, ".chm");

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);

            m_modelLoadRef = CharaPcs.loadModel(File.GetBuffer(), charaKind, static_cast<int>(charaNo), mergeFileId, mergeFlags, 0, 0);
            File.Close(fileHandle);
            m_modelLoadRef->AddRef();
            m_model = m_modelLoadRef->m_model;
            m_model->AddRef();

            strcpy(path, basePath);
            strcat(path, ".chd");
            fileHandle = File.Open(path, 0, CFile::PRI_LOW);
            if (fileHandle != 0) {
                File.Read(fileHandle);
                File.SyncCompleted(fileHandle);
                m_model->CreateDynamics(File.GetBuffer(), HandleModelStage(charaKind, 0));
                File.Close(fileHandle);
                if (System.GetErrorLevel() >= 1U) {
                    System.Printf("\x1b[31mMerge: ダイナミクスをDVDから読み込みました。type = %d number = %d\n", charaKind, static_cast<int>(charaNo));
                }
            }
        } else {
            return 0;
        }
    }

    ChangeTexture(charaKind, charaNo, textureVariant, mergeFileId, mergeFlags);
    if (m_textureSet != 0 && m_textureSet->Find("n915m_2") >= 0) {
        m_model->InitMogFurTex();
    }

    if (static_cast<s32>(Game.m_currentSceneId) != 7 && charaKind == 1) {
        CLoadPdt* loadPdt = CharaPcs.searchPdt(charaKind, static_cast<int>(charaNo), static_cast<int>(textureVariant));

        if (loadPdt != 0) {
            m_pdtLoadRef = loadPdt;
            m_pdtLoadRef->AddRef();
        } else {
            loadPdt = new (CharaPcs.m_stage, "p_chara.cpp", 0x868) CLoadPdt;
            m_pdtLoadRef = loadPdt;
            m_pdtLoadRef->m_keyTag = charaKind;
            m_pdtLoadRef->m_keyId = static_cast<unsigned int>(charaNo);
            m_pdtLoadRef->m_variantTag = static_cast<int>(textureVariant);
            m_pdtLoadRef->m_mergeFileId = mergeFileId;
            m_pdtLoadRef->m_mergeFlags = mergeFlags;
            m_pdtLoadRef->m_pdtSlot =
                PartPcs.LoadMonsterPdt(static_cast<int>(charaNo), static_cast<int>(textureVariant), 0, 0, 0, 0);
            if (System.GetErrorLevel() >= 1U) {
                System.Printf("\x1b[31mMerge: モンスターPDTをDVDから読み込みました。type = %d number = %d idxTexture = %d\n\x1b[0m", charaKind, static_cast<int>(charaNo), textureVariant);
            }
            CharaPcs.m_loadPdts.Add(m_pdtLoadRef);
            m_pdtLoadRef->AddRef();
        }
    }
    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x80075920
 * PAL Size: 1300b
 * EN Address: 0x8008882c
 * EN Size: 392b
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::CHandle::LoadAnim(
    char* animName, int animIndex, int animFlags, int charaKind, int charaNo, int mergeFileId, int mergeFlags)
{
    FreeAnim(animIndex);

    if (CharaPcs.LoadAnim(charaKind == -1 ? m_charaKind : charaKind,
                         charaNo == -1 ? m_charaNo : charaNo,
                         animName, 0, mergeFileId, mergeFlags) == 0) {
        return 0;
    }

    CLoadAnim* loadAnim = CharaPcs.searchAnim(charaKind == -1 ? m_charaKind : charaKind,
                                       charaNo == -1 ? m_charaNo : charaNo, animName);

    m_animSlot[animIndex] = loadAnim;
    loadAnim->AddRef();

    m_animSlot[animIndex]->m_playbackFlags = static_cast<unsigned int>(animFlags);
    m_animSlot[animIndex]->m_anim->SetInterp(animFlags & 1);
    m_animSlot[animIndex]->m_anim->SetLastFrame(animFlags & 2);

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800756FC
 * PAL Size: 548b
 * EN Address: 0x800889b4
 * EN Size: 332b
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::LoadAnim(int charaKind, int charaNo, char* animName, int, int mergeFileId, int mergeFlags)
{
    if (CharaPcs.searchAnim(charaKind, charaNo, animName) == 0) {
        char path[0x100];
        const char** pathParts = m_modelTable[charaKind];
        sprintf(path, "dvd/char/%s/%s%03d/%s.cha", pathParts[0], pathParts[1], charaNo, animName);

        CFile::CHandle* fileHandle = File.Open(path, 0, CFile::PRI_LOW);
        if (fileHandle != 0) {
            File.Read(fileHandle);
            File.SyncCompleted(fileHandle);
            loadAnimBuffer(File.GetBuffer(), animName, charaKind, charaNo, mergeFileId, mergeFlags);
            File.Close(fileHandle);

            if (System.GetErrorLevel() >= 1U) {
                System.Printf("\x1b[31mMerge: アニメーションをDVDから読み込みました。name = %s type = %d number = %d\n\x1b[0m", animName, charaKind, charaNo);
            }
        } else {
            return 0;
        }
    }
    return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CCharaPcs::CHandle::FreeModel()
{
    Graphic._WaitDrawDone("p_chara.cpp", 0x8C9);
    PartMng.pppDeleteCHandle(this);

    ReleaseShared(m_model);
    ReleaseShared(m_textureSet);
    ReleaseShared(m_modelLoadRef);
    ReleaseShared(m_texLoadRef);
    ReleaseShared(m_pdtLoadRef);

    CharaPcs.releaseUnuseLoadModel(0);
}

/*
 * --INFO--
 * PAL Address: 0x800754E8
 * PAL Size: 532b
 * EN Address: 0x80088bec
 * EN Size: 264b
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::FreeAnim(int animIndex)
{
    if (animIndex == -1) {
        for (int i = 0; i < 64; i++) {
            ReleaseHandleAnimSlot(this, i);
        }
        CharaPcs.releaseUnuseLoadAnim(0, 0);
        return;
    }

    CLoadAnim* previousAnim = m_animSlot[animIndex];
    if (previousAnim == 0) {
        return;
    }

    ReleaseSharedNonNull(m_animSlot[animIndex]);
    CharaPcs.releaseUnuseLoadAnim(m_animSlot[animIndex], 0);
    m_animSlot[animIndex] = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80075400
 * PAL Size: 232b
 * EN Address: 0x80088cf4
 * EN Size: 304b
 * JP Address: TODO
 * JP Size: TODO
 */
int CCharaPcs::CHandle::SetAnim(int animIndex, int startFrame, int endFrame, int blendMode, int forceSet)
{
    if (m_model == 0) {
        return 0;
    }
    if (m_currentAnimIndex == animIndex && forceSet == 0) {
        goto fail;
    }

    {
        CChara::CAnim* anim;
        if (animIndex == -1) {
            anim = 0;
        } else {
            CLoadAnim* loadAnim = m_animSlot[animIndex];
            anim = loadAnim != 0 ? loadAnim->m_anim : 0;
        }

        if (anim == 0) {
            if (m_charaKind != 3 && System.GetErrorLevel() >= 2U) {
                System.Printf("アニメーションがありません。type=%d number=%d animno=%d\n", m_charaKind, m_charaNo, animIndex);
            }
            return 0;
        }

        m_model->AttachAnim(anim, startFrame, endFrame, blendMode);
        m_currentAnimIndex = animIndex;
        return 1;
    }

fail:
    return 0;
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
	unsigned int dbgMenuFlags = DbgMenuPcs.GetDbgFlag();
	if ((dbgMenuFlags & 0x8000) != 0) {
		if ((drawPass == 4) && ((m_flags & 0x10000) != 0)) {
			draw(3, 0);
		}
		draw(drawPass, (4U - drawPass | drawPass - 4U) >> 0x1F);
	}
}

/*
 * --INFO--
 * PAL Address: 0x80074598
 * PAL Size: 3556b
 * EN Address: 0x80088F08
 * EN Size: 3248b
 * JP Address: TODO
 * JP Size: TODO
 */
void CCharaPcs::CHandle::draw(int drawPass, int immediatePass)
{
    if (m_model == 0 || (m_flags & 1) == 0 || (m_flags & 0x400000) != 0 ||
        (0.0f == m_model->m_lightAlpha && (m_flags & 0x80) == 0)) {
        return;
    }

    const unsigned int flags = m_flags;
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

    if (immediatePass != 0 && drawPass == 0 && (m_model->m_lightAlpha < 1.0f || (flags & 0x40000) != 0)) {
        if (immediatePass != 0) {
            ppvDrawMng.AddPrim(-m_sortZ, this);
        }
        return;
    }

    if (drawPass == 3 && (flags & 0x81C) == 0) {
        return;
    }
    if ((drawPass == 0 || drawPass == 4) && (flags & 0x10) != 0) {
        return;
    }

    const unsigned int lightBank = (flags >> 19) & 1;
    if (drawPass != 1 && drawPass != 2 && (flags & 0x200000) == 0) {
        float phase = m_colorPhase;
        phase *= 4.0f;
        unsigned int phaseIndex = static_cast<int>(phase);
        const float blendT = static_cast<float>(fmod(static_cast<double>(phase), 1.0));
        CColor shade;
        if ((m_flags & 0x20000) != 0 && drawPass != 3) {
            shade = CColor(0xFF, 0xFF, 0xFF, 0xFF);
        } else {
            shade = CharaPcs.m_viewerChoiceColor[phaseIndex] * (1.0f - blendT) +
                    CharaPcs.m_viewerChoiceColor[phaseIndex + 1] * blendT;
        }

        LightPcs.SetAmbient((CColor3(CharaPcs.m_viewerAmbientColor[lightBank]) * shade).color);

        for (unsigned long i = 0; i < 3; i++) {
            LightPcs.SetDiffuseColor(i, (CColor3(CharaPcs.m_viewerDiffuseColor[lightBank][i]) * shade).color);
        }

        Vec lightPos;
        Mtx modelMtx;
        m_model->GetMatrix(modelMtx);
        lightPos.x = modelMtx[0][3];
        lightPos.y = modelMtx[1][3];
        lightPos.z = modelMtx[2][3];
        LightPcs.SetPosition(static_cast<CLightPcs::TARGET>(0), &lightPos, 0xFFFFFFFF);
    }

    Mtx viewMtx;
    CameraPcs.GetViewMatrix(viewMtx);

    if (drawPass == 3) {
        if ((m_flags & 4) != 0) {
            const float offsetY = 2.0f * (m_worldPosY - m_bgCharmPlaneY);
            viewMtx[1][3] += viewMtx[1][1] * offsetY;
            viewMtx[0][3] += viewMtx[0][1] * offsetY;
            viewMtx[2][3] += viewMtx[2][1] * offsetY;
            viewMtx[0][1] *= -1.0f;
            viewMtx[1][1] *= -1.0f;
            viewMtx[2][1] *= -1.0f;
        } else if ((m_flags & 8) != 0) {
            PSMTXConcat(viewMtx, CFlatCenterMatrix(), viewMtx);
        }
    } else if (drawPass == 2) {
        CVector modelPos;
        Mtx modelMtx;
        m_model->GetMatrix(modelMtx);
        modelPos.x = modelMtx[0][3];
        modelPos.y = modelMtx[1][3];
        modelPos.z = modelMtx[2][3];

        CVector delta = CVector(CharaPcs.m_texShadowPos) - modelPos;
        if (delta.x == 0.0f && delta.z == 0.0f) {
            return;
        }

        const float distRatio = PSVECMag(delta) / CharaPcs.m_texShadowRadius;
        if (distRatio > 1.0f) {
            return;
        }
        const float shadowFade = 1.0f - distRatio;
        delta.Normalize();

        C_MTXLookAt(m_shadowViewMtx,
                    modelPos + delta * static_cast<float>(CharaPcs.m_texShadowDistance) + CVector(0.0f, 10.0f, 0.0f),
                    CVector(0.0f, 1.0f, 0.0f), modelPos + CVector(0.0f, 10.0f, 0.0f));
        PSMTXCopy(m_shadowViewMtx, viewMtx);

        float nearZ;
        float farZ;
        CameraPcs.GetClip(&nearZ, &farZ);
        CColor shadowFog;
        shadowFog.color.a = 0xFF;
        shadowFog.color.b = static_cast<unsigned char>(static_cast<int>(255.0f * shadowFade));
        shadowFog.color.g = shadowFog.color.b;
        shadowFog.color.r = shadowFog.color.b;
        _GXColor shadowFogGX = shadowFog.color;
        GXSetFog(GX_FOG_PERSP_LIN, nearZ, nearZ + 1.0f, nearZ, farZ, shadowFogGX);
    }

    int restoreFog = 0;
    if (0.0f < m_fogBlend && (drawPass == 0 || drawPass == 4)) {
        float fogStart;
        float fogEnd;
        float fogBlend = 1.0f - (1.0f - m_fogBlend) * (1.0f - m_fogBlend);

        _GXColor graphicFogColor;
        float nearZ;
        float farZ;
        CameraPcs.GetClip(&nearZ, &farZ);
        graphicFogColor = Graphic.GetFogColor();
        Graphic.GetFogParam(fogStart, fogEnd);

        GXSetFog(GX_FOG_PERSP_LIN,
                 fogStart * (1.0f - fogBlend) + nearZ * fogBlend,
                 (fogEnd + 1.0f) * (1.0f - fogBlend) + (nearZ + 1.0f) * fogBlend,
                 nearZ,
                 farZ,
                 (CColor(graphicFogColor) * (1.0f - fogBlend) + CColor(0xFF, 0xFF, 0xFF, 0xFF) * fogBlend).color);
        restoreFog = 1;
    }

    if (drawPass == 1 || drawPass == 2) {
        if (drawPass == 2) {
            GXSetTexCopySrc(0, 0, static_cast<unsigned short>(CharaPcs.m_texShadowSize),
                            static_cast<unsigned short>(CharaPcs.m_texShadowSize));
            GXSetTexCopyDst(static_cast<unsigned short>(CharaPcs.m_texShadowSize),
                            static_cast<unsigned short>(CharaPcs.m_texShadowSize), GX_CTF_R4, GX_FALSE);
            m_shadowTexturePtr = reinterpret_cast<unsigned char*>(CharaPcs.m_texShadowTextureBase) +
                                 CharaPcs.m_texShadowTextureOffset;
            DCInvalidateRange(m_shadowTexturePtr, (CharaPcs.m_texShadowSize * CharaPcs.m_texShadowSize) / 2);
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
        }

        m_model->DrawShadow(viewMtx, (drawPass == 1) ? 1 : 0);

        if (drawPass == 2) {
            GXCopyTex(m_shadowTexturePtr, GX_TRUE);
            CharaPcs.m_texShadowTextureOffset += (CharaPcs.m_texShadowSize * CharaPcs.m_texShadowSize) / 2;
            GXPixModeSync();
        }
    } else {
        unsigned char charmFlag = 0;
        if (drawPass == 3 && (m_flags & 0x0C) != 0) {
            charmFlag = 1;
        }
        const unsigned int drawFlags = m_flags;
        int modelDrawFlags = (charmFlag != 0) ? 1 : 0;
        modelDrawFlags |= ((drawFlags & 0x400) != 0) ? 2 : 0;
        modelDrawFlags |= ((drawFlags & 0x2000) != 0) ? 4 : 0;
        unsigned char effectFlag = 0;
        if (drawPass == 3 && (drawFlags & 0x8000) != 0) {
            effectFlag = 1;
        }
        modelDrawFlags |= (effectFlag != 0) ? 8 : 0;
        modelDrawFlags |= ((drawFlags & 0x100000) != 0) ? 0x10 : 0;
        m_model->Draw(viewMtx, modelDrawFlags, 0);
    }

    if (drawPass == 0 || drawPass == 4) {
        m_model->DrawFur(viewMtx, static_cast<int>((m_flags >> 23) & 1));
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
    if (System.GetErrorLevel() >= 3U)
    {
        System.Printf("非同期読み込みエントリー\n");
    }

	CancelLoadModelASync();
	FreeModel();
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
            strcat(path, ".chm");
        } else if (m_asyncState == 3) {
            strcpy(path, basePath);
            strcat(path, ".chd");
        } else {
            if (m_asyncTextureVariant >= 1) {
                sprintf(path, "%s_%c", basePath, m_asyncTextureVariant + 0x61);
            } else {
                strcpy(path, basePath);
            }
            strcat(path, ".tex");
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

    if (asyncState != 2 && asyncState != 4 && asyncState != 6) {
        return;
    }
    if (!File.IsCompleted(m_asyncFileHandle)) {
        return;
    }

    if (m_asyncState == 2) {
        m_modelLoadRef = CharaPcs.loadModel(File.GetBuffer(), m_asyncCharaKind, m_asyncCharaNo, -1, 0, 0, 0);
        m_modelLoadRef->AddRef();
        m_model = m_modelLoadRef->m_model;
        m_model->AddRef();
        m_charaKind = m_asyncCharaKind;
        m_charaNo = m_asyncCharaNo;
    } else if (m_asyncState == 4) {
        m_model->CreateDynamics(File.GetBuffer(), HandleModelStage(m_asyncCharaKind, 0));
    } else {
        m_texLoadRef = CharaPcs.loadTexture(File.GetBuffer(), m_asyncCharaKind, m_asyncCharaNo, m_asyncTextureVariant, -1, 0, 0, 0);
        m_texLoadRef->AddRef();
        m_textureSet = m_texLoadRef->m_textureSet;
        m_textureSet->AddRef();
        m_model->AttachTextureSet(m_textureSet);
        m_textureVariant = m_asyncTextureVariant;
    }

    File.Close(m_asyncFileHandle);
    m_asyncFileHandle = 0;
    if (m_asyncState == 6) {
        m_asyncState = 7;
        if (System.GetErrorLevel() >= 3U) {
            System.Printf("非同期読み込み完了\n");
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
        if (System.GetErrorLevel() >= 2U) {
            System.Printf("モデル非同期読み込み中にキャンセルされました。\n");
        }
        File.Close(m_asyncFileHandle);
        m_asyncFileHandle = 0;
    }

    m_asyncState = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80073D64
 * PAL Size: 68b
 * EN Address: 0x800736CC
 * EN Size: 188b
 * JP Address: UNUSED
 * JP Size: UNUSED
 */
int CCharaPcs::CHandle::IsModelLoaded(int checkModelField)
{
#ifdef VERSION_GCCE01
    if (System.GetErrorLevel() >= 3U) {
        System.Printf("step=%d model=%x tex=%x\n", m_asyncState, m_model,
                      m_model != 0 ? m_model->m_texSet : 0);
    }
#endif
	if ((m_asyncState == 0 || m_asyncState == 7)
		&& m_model != nullptr
		&& (checkModelField == 0 || m_model->m_texSet != 0))
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
CCharaPcs::CLoadModel::~CLoadModel()
{
    ReleaseShared(m_model);
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
CCharaPcs::CLoadTexture::~CLoadTexture()
{
    ReleaseShared(m_textureSet);
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

#pragma pool_data off
CProcessCallbackTable CCharaPcs::m_table[3] = {
    {
        const_cast<char*>(s_CCharaPcs_GAME_801D9128),
        static_cast<CProcessCallback>(&CCharaPcs::create),
        static_cast<CProcessCallback>(&CCharaPcs::destroy),
        {
            {static_cast<CProcessCallback>(&CCharaPcs::calc), 0x1F, 0},
            {static_cast<CProcessCallback>(&CCharaPcs::drawBefore), 0x36, 1},
            {static_cast<CProcessCallback>(&CCharaPcs::drawShadow), 0x30, 1},
            {static_cast<CProcessCallback>(&CCharaPcs::draw), 0x3B, 1},
            {static_cast<CProcessCallback>(&CCharaPcs::drawOverlap), 0x46, 1},
            {static_cast<CProcessCallback>(&CCharaPcs::calcAfter), 0x4D, 8},
        },
    },
    {
        const_cast<char*>(s_CCharaPcs_VIEWER_801D9138),
        static_cast<CProcessCallback>(&CCharaPcs::createViewer),
        static_cast<CProcessCallback>(&CCharaPcs::destroyViewer),
        {
            {static_cast<CProcessCallback>(&CCharaPcs::calcViewer), 0x1F, 0},
            {static_cast<CProcessCallback>(&CCharaPcs::drawViewer), 0x3B, 1},
            {static_cast<CProcessCallback>(&CCharaPcs::calcAfter), 0x4D, 0},
        },
    },
    {
        const_cast<char*>(s_CCharaPcs_PART_801D914C),
        static_cast<CProcessCallback>(&CCharaPcs::create),
        static_cast<CProcessCallback>(&CCharaPcs::destroy),
        {
            {static_cast<CProcessCallback>(&CCharaPcs::calc), 0x1F, 0},
            {static_cast<CProcessCallback>(&CCharaPcs::draw), 0x3B, 1},
            {static_cast<CProcessCallback>(&CCharaPcs::calcAfter), 0x4D, 0},
        },
    },
};

