#ifndef _FFCC_P_CHARA_H_
#define _FFCC_P_CHARA_H_

#include "ffcc/chara.h"
#include "ffcc/file.h"
#include "ffcc/memory.h"
#include "ffcc/p_chara_viewer.h"
#include "ffcc/ref.h"
#include "ffcc/system.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

struct Vec;
class CColor;
class CColor3;
class CMemory;
class CRef;
class CTextureSet;

void GET_CHARA_ALLOC_STAGE_S(int, CMemory::CStage*);

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
        void LoadAnim(char*, int, int, int, int, int, int);
        bool IsModelLoaded(int checkModelField);
        void FreeModel();
        void FreeAnim(int);
        void SetAnim(int, int, int, int, int);
        void Calc();
        void Draw(int);
        void draw(int, int);

        void LoadModelASync(int, unsigned long, unsigned long);
        void loadModelASyncFrame();
        bool IsLoadModelASyncCompleted();
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
    {
    public:
        CLoadModel();
        ~CLoadModel();
    };

    class CLoadAnim
    {
    public:
        CLoadAnim();
        ~CLoadAnim();
    };

    class CLoadTexture
    {
    public:
        CLoadTexture();
        ~CLoadTexture();
    };

    class CLoadPdt
    {
    public:
        CLoadPdt();
        ~CLoadPdt();
    };
	
    enum RESET
	{
		TODO,
	};

    CCharaPcs();
    ~CCharaPcs();

    void Init();
    void Quit();
    void GetTable(unsigned long);
    void create();
    void createLoad();
    void destroy();
    void Reset(RESET);
    void correctLoadAnimAmem();
    void onScriptChanging(char*);
    void calc();
    void calcAfter();
    void ReleaseAllAnimBank();
    void ReleaseUnusedAnimBank();
    void TryReleaseAnimBank(int);
    void SetSpecularAlpha(int);
    void InitEnv(int);
    void GetNumTexShadow();
    void GetTexShadow(int, int, _GXTexObj*, Vec*, float(*)[3][4]);
    void draw();
    void drawBefore();
    void drawMakeTexShadow();
    void drawShadow();
    void createTextureSet(void*, int);
    void releaseUnuseLoadModel(int);
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
    void LoadAnim(int, int, char*, int, int, int);
    void GetAnimStage();
};

CCharaPcs CharaPcs;

#endif // _FFCC_P_CHARA_H_
