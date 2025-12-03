#ifndef _FFCC_P_CHARA_H_
#define _FFCC_P_CHARA_H_

#include "ffcc/p_chara_viewer.h"

class Vec;
class CColor;
class CColor3;
class CMemory;

void GET_CHARA_ALLOC_STAGE_S(int, CMemory::CStage*);
void GXSetTexCoordGen(void);
void GXEnd(void);
void __sinit_p_chara_cpp(void);

class CChara
{
public:
    class CAnim
    {
    public:
        void SetAmemAddress(int);
        void GetBankSize();
        void GetAmemAddress();
        void AddHistory();
        void ReleaseBank();
        void GetHistory();
        void IsBanked();
        void SetLastFrame(int);
        void SetInterp(int);
    };

    class CModel
    {
    public:
        void GetMatrix();
        void GetMatrix(float(*)[4]);
    };
	
    void SetAmemStage(CMemory::CStage*);
    void GetMemoryStage();
    void ResetAmem(int);
};

class CCharaPcs
{
public:

    class CHandle
    {
    public:
        void* operator new(unsigned long, CMemory::CStage*, char*, int);

        CHandle();
        ~CHandle();

        void Add();
        void Remove();

        void ChangeTexture(int, unsigned long, unsigned long, int, int);
        void LoadModel(int, unsigned long, unsigned long, unsigned long, int, int, int);
        void LoadAnim(char*, int, int, int, int, int, int);
        void FreeModel();
        void FreeAnim(int);

        void SetAnim(int, int, int, int, int);
        void Calc();
        void Draw(int);
        void draw(int, int);

        void LoadModelASync(int, unsigned long, unsigned long);
        void loadModelASyncFrame();
        void IsLoadModelASyncCompleted();
        void CancelLoadModelASync();
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

#endif // _FFCC_P_CHARA_H_
