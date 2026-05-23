#ifndef _FFCC_P_CHARA_H_
#define _FFCC_P_CHARA_H_

#include "ffcc/chara.h"
#include "ffcc/color.h"
#include "ffcc/file.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara_viewer.h"
#include "ffcc/ref.h"
#include "ffcc/system.h"
#include "ffcc/textureman.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct Vec;
class CColor;
class CColor3;
class CMemory;
class CRef;
class CTextureSet;

CMemory::CStage* GET_CHARA_ALLOC_STAGE_S(int, CMemory::CStage*);

class CCharaPcs : public CProcess
{
public:
    class CHandle
    {
    public:
        void* operator new(unsigned long, CMemory::CStage*, char*, int);

        CHandle();
        ~CHandle();

        void Add();

        void ChangeTexture(int, unsigned long, unsigned long, int, int);
        void LoadModel(int, unsigned long, unsigned long, unsigned long, int, int, int);
        int LoadAnim(char*, int, int, int, int, int, int);
        int IsModelLoaded(int checkModelField);
        void FreeModel();
        void FreeAnim(int);
        int SetAnim(int, int, int, int, int);
        void Calc();
        void Draw(int);
        void draw(int, int);

        void LoadModelASync(int, unsigned long, unsigned long);
        void loadModelASyncFrame();
        int IsLoadModelASyncCompleted();
        void CancelLoadModelASync();

        int m_charaKind;                    // 0x000
        int m_charaNo;                      // 0x004
        unsigned int m_flags;               // 0x008
        float m_sortZ;                      // 0x00C
        CRef* m_animSlot[64];               // 0x010-0x110
        int m_currentAnimIndex;             // 0x110
        float m_bgCharmPlaneY;              // 0x114
        float m_worldPosY;                  // 0x118
        float m_colorPhase;                 // 0x11C
        void* m_shadowTexturePtr;           // 0x120
        Mtx m_shadowViewMtx;                // 0x124
        float m_fogBlend;                   // 0x154
        unsigned int m_unk0x158;            // 0x158
        CHandle* m_previous;                // 0x15C
        CHandle* m_next;                    // 0x160
        int m_textureVariant;               // 0x164
        CChara::CModel* m_model;            // 0x168
        CTextureSet* m_textureSet;          // 0x16C
        CRef* m_modelLoadRef;               // 0x170
        CRef* m_texLoadRef;                 // 0x174
        CRef* m_pdtLoadRef;                 // 0x178
        int m_asyncCharaKind;               // 0x17C
        int m_asyncCharaNo;                 // 0x180
        int m_asyncTextureVariant;          // 0x184
        int m_asyncState;                   // 0x188
        CFile::CHandle* m_asyncFileHandle;  // 0x18C
        unsigned char m_drawListFlags;      // 0x190
    };

    class CLoadModel
        : public CRef
    {
    public:
        CLoadModel();
        ~CLoadModel();

        void* m_keyTag;                 // 0x08
        int m_keyId;                    // 0x0C
        int m_mergeFileId;              // 0x10
        int m_mergeFlags;               // 0x14
        CChara::CModel* m_model;        // 0x18
        int m_streamMode;               // 0x1C
        void* m_streamOffset;           // 0x20
        int m_streamSize;               // 0x24
    };

    class CLoadAnim
        : public CRef
    {
    public:
        CLoadAnim();
        ~CLoadAnim();

        void* m_keyTag;                 // 0x08
        int m_keyId;                    // 0x0C
        int m_mergeFileId;              // 0x10
        int m_mergeFlags;               // 0x14
        char m_name[16];                // 0x18
        CChara::CAnim* m_anim;          // 0x28
    };

    class CLoadTexture
        : public CRef
    {
    public:
        CLoadTexture();
        ~CLoadTexture();

        void* m_keyTag;                 // 0x08
        int m_keyId;                    // 0x0C
        int m_mergeFileId;              // 0x10
        int m_mergeFlags;               // 0x14
        void* m_variantTag;             // 0x18
        CTextureSet* m_textureSet;      // 0x1C
        int m_streamMode;               // 0x20
        void* m_streamOffset;           // 0x24
        int m_streamSize;               // 0x28
    };

    class CLoadPdt
        : public CRef
    {
    public:
        CLoadPdt();
        ~CLoadPdt();

        void* m_keyTag;                 // 0x08
        int m_keyId;                    // 0x0C
        void* m_variantTag;             // 0x10
        int m_pdtSlot;                  // 0x14
        int m_mergeFileId;              // 0x18
        int m_mergeFlags;               // 0x1C
    };
	
    enum RESET
	{
		TODO,
	};

    CCharaPcs();
    ~CCharaPcs();

    void Init();
    void Quit();
    int GetTable(unsigned long);
    void create();
    void createLoad();
    void destroy();
    void Reset(RESET);
    int correctLoadAnimAmem();
    void onScriptChanging(char*);
    void calc();
    void calcAfter();
    void ReleaseAllAnimBank();
    void ReleaseUnusedAnimBank();
    int TryReleaseAnimBank(int);
    void SetSpecularAlpha(int);
    void InitEnv(int);
    void SetTexShadowRadius(float);
    void SetTexShadowColor(_GXColor);
    void SetTexShadowPos(Vec*);
    void SetMapShadeColor(int, CColor);
    void SetNoFreeMergeMask(int);
    void SetCharaAllocStage(int);
    int GetNumTexShadow();
    void GetTexShadow(int, int, _GXTexObj*, Vec*, float(*)[3][4]);
    void draw();
    void drawBefore();
    void drawMakeTexShadow();
    void drawShadow();
    CTextureSet* createTextureSet(void*, int);
    int releaseUnuseLoadModel(int);
    void releaseUnuseLoadAnim(CCharaPcs::CLoadAnim*, int);
    void DumpLoad();
    void searchModel(int, int);
    void searchTexture(int, int, int);
    void searchAnim(int, int, char*);
    void searchPdt(int, int, int);
    void LoadCam(int, char*);
    void LoadMergeFile(int, int, int);
    void FreeMergeFile(int);
    void isCached(int, int);
    void loadModel(void*, int, int, int, int, int, int);
    void loadTexture(void*, int, int, int, int, int, int, int);
    void loadAnimBuffer(void*, char*, int, int, int, int);
    void drawOverlap();
    int LoadAnim(int, int, char*, int, int, int);
    void GetAnimStage();
    void drawViewer();
    void calcViewer();
    void createViewer();
    void destroyViewer();

    u8 _pad004[0x40];                         // 0x004
    int m_texShadowSize;                      // 0x044
    int m_texShadowDistance;                  // 0x048
    CHandle* m_handleList;                    // 0x04C
    u8 _pad050[0x70];                         // 0x050
    CMemory::CStage* m_stage;                 // 0x0C0
    CMemory::CStage* m_amemStage;             // 0x0C4
    CMemory::CStage* m_amemWorkStage;         // 0x0C8
    CMemory::CStage* m_viewerModelStage;      // 0x0CC
    CMemory::CStage* m_viewerTextureStage;    // 0x0D0
    CMemory::CStage* m_viewerAnimStage;       // 0x0D4
    u8 _pad0D8[0xC];                          // 0x0D8
    int m_charaAllocStage;                    // 0x0E4
    GXColor m_viewerAmbientColor[2];          // 0x0E8
    GXColor m_viewerDiffuseColor[2][3];       // 0x0F0
    Vec m_viewerDiffusePos[3];                // 0x108
    CColor m_viewerChoiceColor[5];            // 0x12C
    void* m_texShadowTextureBase;             // 0x140
    u32 m_texShadowTextureSize;               // 0x144
    u32 m_texShadowTextureOffset;             // 0x148
    Mtx m_texShadowProjectionMtx;             // 0x14C
    Vec m_texShadowPos;                       // 0x17C
    float m_texShadowRadius;                  // 0x188
    GXColor m_texShadowColor;                 // 0x18C
    CChara::CModel* m_viewerModel[2];         // 0x190
    CChara::CAnim* m_viewerAnim[2];           // 0x198
    CChara::CAnim* m_viewerSavedAnim;         // 0x1A0
    int m_viewerAnimLoadedCount;              // 0x1A4
    int m_viewerAnimRequestedCount;           // 0x1A8
    int m_viewerAnimLoopIndex;                // 0x1AC
    CChara::CAnim* m_viewerAnimBank[64];      // 0x1B0
    CTextureSet* m_viewerTextureSet[2];       // 0x2B0
    CTextureSet* m_viewerBackTextureSet;      // 0x2B8
    int m_viewerLoadModel;                    // 0x2BC
    char m_viewerModelPath[0x100];            // 0x2C0
    int m_viewerLoadAnim;                     // 0x3C0
    char m_viewerAnimPath[0x100];             // 0x3C4
    int m_viewerLoadTexture;                  // 0x4C4
    char m_viewerTexturePath[0x100];          // 0x4C8
    int m_viewerTexAnimDirty;                 // 0x5C8
    char m_viewerTexAnimName[0x20];           // 0x5CC
    int m_viewerTexAnimFrame;                 // 0x5EC
    int m_viewerLoadDynamics;                 // 0x5F0
    char m_viewerDynamicsPath[0x100];         // 0x5F4
    int m_viewerStepMode;                     // 0x6F4
    int m_viewerDrawGrid;                     // 0x6F8
    int m_viewerStoreSavedAnim;               // 0x6FC
    float m_viewerSavedFrame;                 // 0x700
    int m_viewerSavedAnimState;               // 0x704
    int m_viewerIFrameEnabled;                // 0x708
    int m_viewerResetIFrame;                  // 0x70C
    int m_viewerLoadAnimContinuous;           // 0x710
    u8 _pad714[4];                            // 0x714
    int m_noFreeMergeMask;                    // 0x718
};

extern CCharaPcs CharaPcs;

#endif // _FFCC_P_CHARA_H_
