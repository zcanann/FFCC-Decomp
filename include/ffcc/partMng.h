#ifndef _FFCC_PARTMNG_H_
#define _FFCC_PARTMNG_H_

#include "ffcc/p_chara.h"

class CChunkFile;
class CTexture;
class CTextureSet;
class CChara;
struct Vec;
struct _GXColor;
struct _pppMngSt;
struct _pppEnvSt;
struct _pppDataHead;
struct pppShapeSt;
struct pppModelSt;
struct PPPCREATEPARAM;
struct PPPSEST;
struct PPPIFPARAM;
struct PmcomGetImageSt;
struct PmcomRendSt;

void Screen2world(Vec&, Vec&);
void pppEditGetViewPos(Vec*);
void pppEditGetViewMatrix(float (*)[4]);
void pppEditGetProjectionMatrix(float (*)[4]);
void pppEditSetProjection2D();
void pppSetProjection();
void CheckSum(char*, unsigned long, unsigned long);
void pppSetFog(unsigned char, unsigned char, unsigned char,
               unsigned char, float, float);

class CPartMng
{
public:
    CPartMng();

    void Create();
    void Destroy();

    void pppDumpMngSt();
    void pppAmemCacheClear();
    void pppAmemCacheCountStart();
    void pppAmemCacheCountEnd();

    void pppReleasePmng(int);
    void pppReleasePdt(int);

    void pppGetFreePppMngSt();
    void pppGetNumFreePppMngSt();
    void pppGetFreePppDataMngSt();

    void drawLine(int, int, int, int, _GXColor&);
    void drawLine3D(Vec*, Vec*, _GXColor&);
    void drawCursor();
    void render3Dcursor();

    void pppGet2Dpos();
    void drawStart();
    void setProcSpeed(struct ProcSpdSt*, int);
    void drawEnd();

    void initGraphicSystem();
    void allFreeFPrim();
    void SetFp();
    void fpIDon(unsigned short);
    void fpIDoff(unsigned short);

    void InitMaterialSet();
    void ReadTex(CChunkFile&);
    void pppReadRsd(CChunkFile&, pppModelSt*);
    void pppReadShp(CChunkFile&, pppShapeSt*);

    void pppEditAllReleaseResource();

    void pppDataRcv(unsigned long, char*, unsigned long);

    void pppEditBeforeCalc();
    void pppEditPartCalc();
    void pppEditDrawShadow();
    void pppEditDraw();
    void pppEditPartDrawAfter();

    void pppSetRendMatrix();
    void pppPartCalc();
    void pppRefCnt0Up();
    void pppDumpCacheIdx();

    void pppDrawPppMngSt(Vec&, _pppMngSt*);
    void pppDrawPrio(unsigned char);
    void pppDrawPrioPdtFpno(unsigned char, short, short);
    void pppDrawIdx(int);
    void pppDraw();
    void pppPartDrawAfter();
    void pppPartDead();
    void pppPartInit();

    void pppInitEnv(_pppEnvSt*, _pppDataHead*, unsigned int);
    void pppFileRead(char*, unsigned long&, void*, int);
    void LoadPartNoSyncCalc();
    void pppLoadPtx(const char*, int, int, void*, int);

    void pppLoadPmd(CChunkFile&);
    void pppLoadPmd(const char*);
    void pppLoadPan(CChunkFile&);
    void pppLoadPan(const char*);
    void pppLoadPdt(const char*, int, int, void*, int);

    void pppGetFreeDataMng();
    void pppGetDefaultCreateParam();

    void pppCreate0(int, int, PPPCREATEPARAM*, int);
    void pppCreate(int, int, PPPCREATEPARAM*, int);

    void pppGetFreeSlot();
    void pppDeleteSlot(int, int);
    void pppEndSlot(int, int);
    void pppShowSlot(int, unsigned char);

    void pppDeletePart(int);
    void pppEndPart(int);

    void pppGetIfDt(short);
    void pppShowIdx(short, unsigned char);
    void pppFieldShowFpNo(short, unsigned char);
    void pppFieldEndFpNo(short);

    void pppSetDeltaIdx(short, long);
    void pppSetDeltaSlot(int, long);
    void pppSetLocSlot(int, Vec*);

    void pppDeleteCHandle(CCharaPcs::CHandle*);
    void pppEndCHandle(CCharaPcs::CHandle*);
    void pppIsDeadCHandle(CCharaPcs::CHandle*);

    void pppDeleteAll();
    void pppDestroyAll();
};

#endif
