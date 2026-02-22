#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/cflat_runtime.h"
#include "ffcc/file.h"
#include "ffcc/graphic.h"

extern "C" void __dl__FPv(void* ptr);
extern "C" void pppPartInit__8CPartMngFv2(CPartMng* partMng);
extern "C" unsigned int CheckSum__FPvi(void*, int);
extern "C" void pppStopSe__FP9_pppMngStP7PPPSEST(_pppMngSt*, PPPSEST*);
extern "C" float ppvScreenMatrix[4][4];
extern "C" void __ct__9_pppMngStFv(_pppMngSt* pppMngSt);
extern "C" void __construct_array(void*, void (*)(void*), void (*)(void*, int), unsigned long, unsigned long);
extern CPartMng PartMng;
extern PPPCREATEPARAM g_dcp;
static char s_partMng_cpp_801d8230[] = "partMng.cpp";

struct CPtrArrayBare {
    unsigned long m_size;
    unsigned long m_numItems;
    unsigned long m_defaultSize;
    void* m_items;
    CMemory::CStage* m_stage;
    int m_growCapacity;
};

/*
 * --INFO--
 * PAL Address: 0x8005f61c
 * PAL Size: 8b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void SetGrow__21CPtrArray(CPtrArrayBare* ptrArray, int growCapacity)
{
    ptrArray->m_growCapacity = growCapacity;
}

/*
 * --INFO--
 * PAL Address: 0x8005f618
 * PAL Size: 4b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CFlatRuntime::CObject::onNewFinished()
{
}

/*
 * --INFO--
 * PAL Address: 0x80059220
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppShapeSt::pppShapeSt()
{
    m_refCount = 0;
    m_inUse = 0;
    m_animData = 0;
    m_displayListData = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800591A4
 * PAL Size: 124b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppShapeSt::~pppShapeSt()
{
    if (m_animData != 0) {
        __dl__FPv(m_animData);
        m_animData = 0;
    }

    if (m_displayListData != 0) {
        __dl__FPv(m_displayListData);
        m_displayListData = 0;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005961C
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppModelSt::pppModelSt()
{
    m_refCount = 0;
    m_isUsed = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800595C8
 * PAL Size: 84b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
pppModelSt::~pppModelSt()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CPartMng::CPartMng()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::Create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::Destroy()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDumpMngSt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppAmemCacheClear()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppAmemCacheCountStart()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppAmemCacheCountEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReleasePmng(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReleasePdt(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGetFreePppMngSt()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005e97c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartMng::pppGetNumFreePppMngSt()
{
    int freeCount = 0;
    char* pppMngSt = reinterpret_cast<char*>(this);

    int i = 0x30;
    do {
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 4)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 5)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 6)) == -0x1000) {
            freeCount++;
        }
        if (*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 7)) == -0x1000) {
            freeCount++;
        }
        pppMngSt += 0xAC0;
        i--;
    } while (i != 0);

    return freeCount;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGetFreePppDataMngSt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawLine(int, int, int, int, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawLine3D(Vec*, Vec*, _GXColor&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawCursor()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::render3Dcursor()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void Screen2world(Vec&, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGet2Dpos()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawStart()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::setProcSpeed(ProcSpdSt*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::drawEnd()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::initGraphicSystem()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::allFreeFPrim()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::SetFp()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::fpIDon(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::fpIDoff(unsigned short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::InitMaterialSet()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::ReadTex(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReadRsd(CChunkFile&, pppModelSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppReadShp(CChunkFile&, pppShapeSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppEditGetViewPos(Vec*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppEditGetViewMatrix(float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppEditGetProjectionMatrix(float (*) [4])
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditAllReleaseResource()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CheckSum(char*, unsigned long, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDataRcv(unsigned long, char*, unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppEditSetProjection2D()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppSetFog(unsigned char, unsigned char, unsigned char, unsigned char, float, float)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditBeforeCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditPartCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditDrawShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEditPartDrawAfter()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005a92c
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void pppSetProjection()
{
    GXSetProjection(ppvScreenMatrix, GX_PERSPECTIVE);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetRendMatrix()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppPartCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppRefCnt0Up()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDumpCacheIdx()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawPppMngSt(Vec&, _pppMngSt*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawPrio(unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawPrioPdtFpno(unsigned char, short, short)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDrawIdx(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDraw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppPartDrawAfter()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80059cac
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppPartDead()
{
    Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0xb3d);

    char* pppMngSt = reinterpret_cast<char*>(this);
    for (int i = 0; i < 0x180; i++) {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if (baseTime != -0x1000 && baseTime < 0) {
            unsigned char isFinished = *reinterpret_cast<unsigned char*>(pppMngSt + 0xe6);
            unsigned char endRequested = *reinterpret_cast<unsigned char*>(pppMngSt + 0xe5);
            if (isFinished != 0 || endRequested != 0) {
                pppEnvStPtr = reinterpret_cast<_pppEnvSt*>(*reinterpret_cast<char**>(pppMngSt) + 4);
                pppMngStPtr = reinterpret_cast<_pppMngSt*>(pppMngSt);
                _pppAllFreePObject(reinterpret_cast<_pppMngSt*>(pppMngSt));
            }
        }
        pppMngSt += 0x158;
    }

    Graphic._WaitDrawDone(s_partMng_cpp_801d8230, 0xb5d);
}

/*
 * --INFO--
 * PAL Address: 0x8005992c
 * PAL Size: 252b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void fn_8005992C(CPartMng* partMng)
{
    char* base = reinterpret_cast<char*>(partMng);
    for (int i = 0; i < 0x10; i++) {
        CFile::CHandle** handleSlot = reinterpret_cast<CFile::CHandle**>(base + 0x2378c + (i * 4));
        CFile::CHandle* handle = *handleSlot;
        if (handle != 0 && File.IsCompleted(handle)) {
            int len = File.GetLength(handle);
            void* readBuffer = File.m_readBuffer;
            void* amemCursor = *reinterpret_cast<void**>(base + 0x236f8);

            Memory.CopyToAMemorySync(readBuffer, amemCursor, (len + 0x1f) & ~0x1f);
            *reinterpret_cast<int*>(base + 0x2370c + (i * 4)) = len;
            *reinterpret_cast<unsigned int*>(base + 0x2374c + (i * 4)) = CheckSum__FPvi(readBuffer, len);
            (*reinterpret_cast<int*>(base + 0x23700))++;
            *reinterpret_cast<char**>(base + 0x236f8) += len;

            File.Close(handle);
            *handleSlot = 0;
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80059c44
 * PAL Size: 104b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void pppPartInit__8CPartMngFv2(CPartMng* partMng)
{
	char* pppMngSt = reinterpret_cast<char*>(partMng);
	int i = 0;

	*reinterpret_cast<int*>(reinterpret_cast<char*>(partMng) + 0x8) = 0;
	do {
		int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
		if (baseTime != -0x1000 && baseTime < 0) {
			_pppInitPart(reinterpret_cast<_pppMngSt*>(pppMngSt));
		}
		pppMngSt += 0x158;
		i++;
	} while (i < 0x180);
}

void CPartMng::pppPartInit()
{
    pppPartInit__8CPartMngFv2(this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppInitEnv(_pppEnvSt*, _pppDataHead*, unsigned int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppFileRead(char*, unsigned long&, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::LoadPartNoSyncCalc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPtx(const char*, int, int, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPmd(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPmd(const char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPan(CChunkFile&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPan(const char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppLoadPdt(const char*, int, int, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGetFreeDataMng()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGetDefaultCreateParam()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppCreate0(int, int, PPPCREATEPARAM*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppCreate(int, int, PPPCREATEPARAM*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppGetFreeSlot()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeleteSlot(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndSlot(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppShowSlot(int, unsigned char)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeletePart(int index)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    pppMngSt += 0x158 * index;

    int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
    if (baseTime < 0) {
        *reinterpret_cast<unsigned char*>(pppMngSt + 0xe5) = 1;
        pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                         reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
    } else {
        *reinterpret_cast<int*>(pppMngSt + 0x14) = -0x1000;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndPart(int index)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    pppMngSt += 0x158 * index;

    *reinterpret_cast<unsigned char*>(pppMngSt + 0xe4) = 1;
    pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                     reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
}

/*
 * --INFO--
 * PAL Address: 0x80057e40
 * PAL Size: 24b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
PPPIFPARAM* CPartMng::pppGetIfDt(short index)
{
	return reinterpret_cast<PPPIFPARAM*>(reinterpret_cast<char*>(this) + (index * 0x158) + 0x130);
}

/*
 * --INFO--
 * PAL Address: 0x80057e2c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartMng::pppShowIdx(short index, unsigned char visible)
{
	reinterpret_cast<unsigned char*>(this)[(index * 0x158) + 0xe9] = visible;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppFieldShowFpNo(short fieldNo, unsigned char visible)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    int i = 0x60;

    do {
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 0)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 0)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 0)) = visible;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 1)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 1)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 1)) = visible;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 2)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 2)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 2)) = visible;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) != -0x1000) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x74 + (0x158 * 3)) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76 + (0x158 * 3)) == fieldNo)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xe9 + (0x158 * 3)) = visible;
        }

        pppMngSt += 0x560;
        i--;
    } while (i != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppFieldEndFpNo(short fieldNo)
{
    char* pppMngSt = reinterpret_cast<char*>(this);

    for (int i = 0; i < 0x180; i++) {
        int baseTime = *reinterpret_cast<int*>(pppMngSt + 0x14);
        if ((baseTime != -0x1000) && (*reinterpret_cast<short*>(pppMngSt + 0x74) == 0) &&
            (*reinterpret_cast<short*>(pppMngSt + 0x76) == fieldNo)) {
            if (baseTime < 0) {
                *reinterpret_cast<unsigned char*>(pppMngSt + 0xe4) = 1;
                pppStopSe__FP9_pppMngStP7PPPSEST(reinterpret_cast<_pppMngSt*>(pppMngSt),
                                                 reinterpret_cast<PPPSEST*>(pppMngSt + 0x11c));
            } else {
                *reinterpret_cast<int*>(pppMngSt + 0x14) = -0x1000;
            }
        }
        pppMngSt += 0x158;
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetDeltaIdx(short index, long color)
{
    *reinterpret_cast<long*>(reinterpret_cast<char*>(this) + (index * 0x158) + 0x2ac0) = color;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetDeltaSlot(int slot, long color)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    int i = 0x40;

    do {
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 0)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 0)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 0)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 0)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 0)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 1)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 1)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 1)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 1)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 1)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 2)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 2)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 2)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 2)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 2)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 3)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 3)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 3)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 3)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 3)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 4)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 4)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 4)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 4)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 4)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 4)) = static_cast<unsigned char>(color & 0xff);
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 5)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 5)) == slot)) {
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa8 + (0x158 * 5)) = static_cast<unsigned char>((color >> 24) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xa9 + (0x158 * 5)) = static_cast<unsigned char>((color >> 16) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xaa + (0x158 * 5)) = static_cast<unsigned char>((color >> 8) & 0xff);
            *reinterpret_cast<unsigned char*>(pppMngSt + 0xab + (0x158 * 5)) = static_cast<unsigned char>(color & 0xff);
        }

        pppMngSt += 0x810;
        i--;
    } while (i != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppSetLocSlot(int slot, Vec* position)
{
    char* pppMngSt = reinterpret_cast<char*>(this);
    int i = 0x60;

    do {
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 0)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 0)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 0)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 0)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 0)) = position->z;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 1)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 1)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 1)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 1)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 1)) = position->z;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 2)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 2)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 2)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 2)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 2)) = position->z;
        }
        if ((*reinterpret_cast<int*>(pppMngSt + 0x14 + (0x158 * 3)) != -0x1000) &&
            (*reinterpret_cast<int*>(pppMngSt + 0x100 + (0x158 * 3)) == slot)) {
            *reinterpret_cast<float*>(pppMngSt + 0x8 + (0x158 * 3)) = position->x;
            *reinterpret_cast<float*>(pppMngSt + 0xc + (0x158 * 3)) = position->y;
            *reinterpret_cast<float*>(pppMngSt + 0x10 + (0x158 * 3)) = position->z;
        }

        pppMngSt += 0x560;
        i--;
    } while (i != 0);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeleteCHandle(CCharaPcs::CHandle*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppEndCHandle(CCharaPcs::CHandle*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppIsDeadCHandle(CCharaPcs::CHandle*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDeleteAll()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartMng::pppDestroyAll()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005f624
 * PAL Size: 184b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_partMng_cpp(void)
{
    __construct_array(reinterpret_cast<unsigned char*>(&PartMng) + 0x2A18, (void (*)(void*))__ct__9_pppMngStFv, 0,
                      sizeof(_pppMngSt), 0x180);

    g_dcp.m_soundEffectParams.m_soundEffectHandle = -1;
    g_dcp.m_soundEffectParams.m_soundEffectSlot = -1;
    g_dcp.m_soundEffectParams.m_soundEffectStopFlag = 0;
    g_dcp.m_soundEffectParams.m_soundEffectKind = 1;
    g_dcp.m_soundEffectParams.m_soundEffectStartFrame = 0;
    g_dcp.m_soundEffectParams.m_soundEffectStartedOnce = 0;
    g_dcp.m_soundEffectParams.m_soundEffectFadeFrames = 30;
    g_dcp.m_hitParamA = 0;
    g_dcp.m_hitParamB = 0;
    g_dcp.m_hitObjectCount = 0;
    g_dcp.m_hitFlags = 0;
    g_dcp.m_positionOffsetPtr = 0;
    g_dcp.m_rotationPtr = 0;
    g_dcp.m_scalePtr = 0;
    g_dcp.m_extraPositionPtr = 0;
    g_dcp.m_paramA = 0;
    g_dcp.m_paramB = 0;
    g_dcp.m_lookTargetPtr = 0;
    g_dcp.m_objectHitMask = 0;
    g_dcp.m_cylinderAttribute = 0;
    g_dcp.m_paramC = 1.0f;
    g_dcp.m_paramD = 1.0f;
    g_dcp.m_owner = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005f6dc
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __ct__9_pppMngStFv(_pppMngSt* pppMngSt)
{
    char* base = reinterpret_cast<char*>(pppMngSt);
    PPPSEST* soundEffectData = reinterpret_cast<PPPSEST*>(base + 0x11c);
    PPPIFPARAM* hitParams = reinterpret_cast<PPPIFPARAM*>(base + 0x130);

    soundEffectData->m_soundEffectHandle = -1;
    soundEffectData->m_soundEffectSlot = -1;
    soundEffectData->m_soundEffectStopFlag = 0;
    soundEffectData->m_soundEffectKind = 1;
    soundEffectData->m_soundEffectStartFrame = 0;
    soundEffectData->m_soundEffectStartedOnce = 0;
    soundEffectData->m_soundEffectFadeFrames = 30;

    hitParams->m_particleIndex = 0;
    hitParams->m_classId = 0;
    hitParams->m_hitObjectCount = 0;
    hitParams->m_hitFlags = 0;
}
