#include "ffcc/p_tina.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_menu.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/p_usb.h"
#include "ffcc/stopwatch.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/linkage.h"
#include "ffcc/USBStreamData.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

char* gDebugSpinnerText = 0;
unsigned char gDebugSpinnerTextInitialized = 0;
int gDebugSpinnerFrame = 0;
unsigned char gDebugSpinnerFrameInitialized = 0;
extern "C" const char s_no_name_8032fdcc[];
extern "C" {
const char s_no_name_8032fdcc[] = "no_name";
}
static char s_tinaSourceName[] = "p_tina.cpp";
static char s_tinaPrioTimeFmt[] = "prioTime:%d prio:%d pdtID:%2d fp:%08x\n";
static char s_tinaTitleFmt[] = "Tina :%c\n";
static char s_tinaCalcFmt[] = "clc :%f / max :%f\n";
static char s_tinaDrawFmt[] = "drw :%f / max :%f\n";
static char s_tinaHeapFmt[] = "hpm :%f / max :%f\n";

extern "C" CProfile* __ct__8CProfileFPc(CProfile*, char*);
extern "C" CProfile* __dt__8CProfileFv(CProfile*, short);
extern "C" int pppLoadPtx__8CPartMngFPCciiPvi(CPartMng*, const char*, int, int, void*, int);
extern "C" int pppLoadPdt__8CPartMngFPCciiPvi(CPartMng*, const char*, int, int, void*, int);
extern "C" void pppLoadPmd__8CPartMngFPCc(CPartMng*, const char*);
extern "C" void pppLoadPan__8CPartMngFPCc(CPartMng*, const char*);
extern "C" int pppGetFreeDataMng__8CPartMngFv(CPartMng*);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void pppReleasePdt__8CPartMngFi(CPartMng*, int);
extern "C" int pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(CPartMng*, int, int, PPPCREATEPARAM*, int);
extern "C" void SetRStage__13CAmemCacheSetFPQ27CMemory6CStage(void*, void*);
extern "C" void AmemSetLock__13CAmemCacheSetFv(void*);
extern "C" void AssertCache__13CAmemCacheSetFv(void*);
extern "C" void Destroy__13CAmemCacheSetFv(void*);
extern "C" void IsBigAlloc__7CUSBPcsFi(void*, int);
extern "C" void mccReadData__7CUSBPcsFv(void*);
extern "C" void* CreateStage__7CMemoryFUlPci(void*, unsigned long, const char*, int);
extern "C" void* Free__7CMemoryFPv(void*, void*);
extern "C" void DestroyStage__7CMemoryFPQ27CMemory6CStage(void*, void*);
extern "C" void Destroy__8CPartMngFv(CPartMng*);
extern "C" void DrawOt__10pppDrawMngFv(void*);
extern "C" void SetDrawDoneDebugDataPartControl__8CGraphicFi(void*, int);
extern "C" void SetDrawDoneDebugData__8CGraphicFSc(void*, signed char);
extern "C" void SetFog__8CGraphicFii(void*, int, int);
extern "C" void pppSetRendMatrix__8CPartMngFv(CPartMng*);
extern "C" void pppDraw__8CPartMngFv(CPartMng*);
extern "C" void Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl(
    void*,
    char*,
    void*,
    void*,
    int,
    void*,
    unsigned long,
    void*,
    unsigned long,
    void*,
    unsigned long);


extern char DAT_801ead4c[];
extern char DAT_801d81d4[];
extern char s_p_tina_rodata_801d7ee0[];
extern char s_CPartPcs_801d7f54[];
extern char s_CPartPcs_dat_801d810c[];
extern char s_CPartPcs_amem_801d811c[];
extern char s_dvd_tina_chobit_801d812c[];
extern char s_dvd_tina_chobit_0_801d813c[];
extern char s_dvd_tina_chobit_1_801d8150[];
extern char s_dvd_tina_chobit_2_801d8164[];
extern char s_dvd_tina_chobit_3_801d8178[];
extern char s_dvd_tina_chobit_4_801d818c[];
extern char DAT_801d8068[];
extern char s_dvd_tina_stage_03d_mirura_801d7f78[];
extern char s_dvd_tina_stage_03d_title_801d7f94[];
extern char s_dvd_tina_stage_03d_fp_03d_801d7fec[];
extern char s_dvd__smenu__s_801d7fb0[];
extern char s_dvd_tina_mon_m_03d_801d7fc0[];
extern char s_dvd_tina_mon_m_03d__c_801d7fd4[];
unsigned char ARRAY_80273968[0xC];
unsigned char ARRAY_802739e8[0xC];
int DAT_8032ed38;
int DAT_8032ed3c;
CPartPcs PartPcs;
pppDrawMng ppvDrawMng;

static int GetMngStBaseTime(const _pppMngSt* pppMngSt)
{
	return *(const int*)((const char*)pppMngSt + 0x14);
}

static int GetMngStKind(const _pppMngSt* pppMngSt)
{
	return *(const short*)((const char*)pppMngSt + 0x74);
}

static int GetMngStNodeIndex(const _pppMngSt* pppMngSt)
{
	return *(const short*)((const char*)pppMngSt + 0x76);
}

static unsigned char GetMngStPrio(const _pppMngSt* pppMngSt)
{
	return *(const unsigned char*)((const char*)pppMngSt + 0xf8);
}

static unsigned char GetMngStPrioTime(const _pppMngSt* pppMngSt)
{
	return *(const unsigned char*)((const char*)pppMngSt + 0xf9);
}

static float& GetMngStUserFloat0(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<float*>(reinterpret_cast<char*>(pppMngSt) + 0x38);
}

static float& GetMngStPositionX(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<float*>(reinterpret_cast<char*>(pppMngSt) + 0x8);
}

static float& GetMngStPositionY(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<float*>(reinterpret_cast<char*>(pppMngSt) + 0xc);
}

static float& GetMngStPositionZ(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<float*>(reinterpret_cast<char*>(pppMngSt) + 0x10);
}

static float& GetMngStUserFloat1(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<float*>(reinterpret_cast<char*>(pppMngSt) + 0x3c);
}

static float& GetMngStScaleFactor(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<float*>(reinterpret_cast<char*>(pppMngSt) + 0x40);
}

static float& GetMngStOwnerScale(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<float*>(reinterpret_cast<char*>(pppMngSt) + 0x44);
}

static unsigned char& GetMngStOwnerScaleMode(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0x48);
}

static unsigned char& GetMngStLockScaleFromOwner(_pppMngSt* pppMngSt)
{
	return *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(pppMngSt) + 0x4d);
}

struct CUSBStreamDataRaw {
    unsigned char* m_data;
    int m_headerReady;
    int m_dataReady;
    unsigned int m_sizeBytes;
    unsigned int m_packetCode;
    void* m_stageDefault;
    void* m_stageLoad;
    void* m_stageAmem;
    void* m_stageExtra;
    void* m_freePtr;
    unsigned char m_fieldLoadReq;
    unsigned char m_printFreeOnNext;
    unsigned char m_blockOnFrame;
    unsigned char m_miruraEventActive;
    unsigned char m_disableShokiDraw;
};

struct CPartPcsViewerState {
    unsigned char unk0[0x18];
    void* m_stageDefault;
    void* m_stageLoad;
    void* m_stageAmem;
    void* m_stageExtra;
    void* m_freePtr;
    unsigned char unk2C[2];
    unsigned char m_blockOnFrame;
    unsigned char m_miruraEventActive;
    unsigned char m_disableShokiDraw;
};

struct CPartMngState {
    unsigned char unk0[0x236F4];
    unsigned int m_partAMemBase;
    unsigned int m_partAMemCursor;
    unsigned int m_partLoadCacheParam;
    unsigned int m_partChunkIndex;
    unsigned int m_asyncHandleCount;
    int m_partLoadMode;
    unsigned char unk2370C[0x80];
    unsigned int m_partAsyncBusy[16];
};

struct PppPdtSlotRaw {
    _pppDataHead* m_pppDataHead;
};

static CPartMngState* GetPartMngState()
{
    return reinterpret_cast<CPartMngState*>(&PartMng);
}

static PppPdtSlotRaw* GetPartMngPdtSlots()
{
    return reinterpret_cast<PppPdtSlotRaw*>(reinterpret_cast<char*>(&PartMng) + 0x22E18);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CPartPcs::~CPartPcs()
{
}

/*
 * --INFO--
 * PAL Address: 0x80053950
 * PAL Size: 16b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::Init()
{
	CUSBStreamDataRaw* usbStream = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<unsigned char*>(this) + 0x4);
	usbStream->m_fieldLoadReq = 0;
	usbStream->m_printFreeOnNext = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::onScriptChanging(char*)
{
	CUSBStreamDataRaw* usbStream = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<unsigned char*>(this) + 0x4);
	usbStream->m_fieldLoadReq = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005392c
 * PAL Size: 20b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartPcs::GetTable(unsigned long index)
{
	unsigned long offset = index * 0x15c;
	return (int)(m_table__8CPartPcs + offset);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int pppNotAllocAmemCacheRmem(unsigned long)
{
	PartMng.pppDumpMngSt();
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800536f0
 * PAL Size: 528b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int pppFreeMngStPrioForData()
{
	struct pppMngStPrioData {
		char pad0[0x14];
		int m_baseTime;
		char pad18[0x5c];
		short m_kind;
		short m_nodeIndex;
		char pad78[0x80];
		unsigned char m_prio;
		unsigned char padF9;
		unsigned short m_prioTime;
		char padFC[0x5c];
	};

	pppMngStPrioData* selectedMngSt = 0;
	pppMngStPrioData* pppMngStBase = reinterpret_cast<pppMngStPrioData*>(&PartMng);
	unsigned int selectedPrioTime = 0;
	unsigned char selectedPrio = 1;
	int index = 0;
	char* stringBase = s_p_tina_rodata_801d7ee0;

	for (int i = 0xc0; i != 0; i--) {
		pppMngStPrioData* candidateA = pppMngStBase;
		if (reinterpret_cast<_pppMngSt*>(candidateA) != pppMngStPtr && candidateA->m_baseTime != -0x1000 &&
		    candidateA->m_kind != 0) {
			unsigned char prioA = candidateA->m_prio;
			if (prioA > 1) {
				if (selectedPrio < prioA) {
					selectedMngSt = candidateA;
					selectedPrio = prioA;
					selectedPrioTime = candidateA->m_prioTime;
				} else if (selectedPrio == prioA) {
					unsigned int prioTimeA = candidateA->m_prioTime;
					if ((int)selectedPrioTime < (int)prioTimeA) {
						selectedMngSt = candidateA;
						selectedPrioTime = prioTimeA;
					}
				}
			}
		}

		pppMngStPrioData* candidateB = candidateA + 1;
		if (reinterpret_cast<_pppMngSt*>(candidateB) != pppMngStPtr && candidateB->m_baseTime != -0x1000 &&
		    candidateB->m_kind != 0) {
			unsigned char prioB = candidateB->m_prio;
			if (prioB > 1) {
				if (selectedPrio < prioB) {
					selectedMngSt = candidateB;
					selectedPrio = prioB;
					selectedPrioTime = candidateB->m_prioTime;
				} else if (selectedPrio == prioB) {
					unsigned int prioTimeB = candidateB->m_prioTime;
					if ((int)selectedPrioTime < (int)prioTimeB) {
						selectedMngSt = candidateB;
						selectedPrioTime = prioTimeB;
					}
				}
			}
		}

		pppMngStBase += 2;
		index++;
	}

	if (selectedMngSt == 0) {
		return 0;
	}

	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(DAT_801ead4c, index);
	}
	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(
			stringBase + 0x2c0,
			(unsigned int)selectedMngSt->m_prioTime,
			(unsigned int)selectedMngSt->m_prio,
			(int)selectedMngSt->m_kind,
			(int)selectedMngSt->m_nodeIndex,
			(int)selectedMngSt->m_kind * 0x38 + -0x7fd672e8);
	}
	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(stringBase + 0x2f4);
	}
	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(DAT_801ead4c);
	}

	Graphic._WaitDrawDone(stringBase + 0x128, 0xfc);
	_pppAllFreePObject(reinterpret_cast<_pppMngSt*>(selectedMngSt));
	return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned char pppAmemDeletePmng(unsigned long)
{
	return pppFreeMngStPrioForData();
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int pppAmemRefCntError(unsigned long)
{
	return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::create0()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x8005357c
 * PAL Size: 328b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::create()
{
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 4);
    char* stringBase = DAT_801d8068;
    void* stage;

    usb->m_freePtr = 0;
    usb->m_stageExtra = 0;
    usb->m_blockOnFrame = 0;
    usb->m_miruraEventActive = 0;
    usb->m_disableShokiDraw = 0;

    if (Game.m_currentSceneId == 7) {
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x180000, stringBase + 0x22C, 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        usb->m_stageAmem = 0;
    } else {
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x180000, stringBase + 0x22C, 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        usb->m_stageAmem = CreateStage__7CMemoryFUlPci(&Memory, 0x400000, stringBase + 0x23C, 2);
    }

    Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl(
        &ppvAmemCacheSet,
        stringBase + 0x74,
        reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<unsigned char*>(&PartPcs) + 4)->m_stageLoad,
        reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<unsigned char*>(&PartPcs) + 4)->m_stageAmem,
        0x400,
        reinterpret_cast<void*>(pppNotAllocAmemCacheRmem),
        0,
        reinterpret_cast<void*>(pppAmemDeletePmng),
        0,
        reinterpret_cast<void*>(pppAmemRefCntError),
        0);

    memset(&PartMng, 0, 0x23FD8);
    PartMng.Create();
}

/*
 * --INFO--
 * PAL Address: 0x80053444
 * PAL Size: 312b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::createLoad()
{
    CPartMngState* state = reinterpret_cast<CPartMngState*>(&PartMng);
    char* stringBase = s_p_tina_rodata_801d7ee0 + 0x24C;

    state->m_partAMemBase = 0;
    state->m_partAMemCursor = 0;
    state->m_partLoadCacheParam = 0;
    state->m_partChunkIndex = 0;
    state->m_asyncHandleCount = 0;
    state->m_partLoadMode = 0;

    pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, stringBase, 1, 1, 0, 0);
    pppLoadPmd__8CPartMngFPCc(&PartMng, stringBase);
    pppLoadPan__8CPartMngFPCc(&PartMng, stringBase);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, stringBase + 0x10, 1, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, stringBase + 0x24, 2, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, stringBase + 0x38, 3, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, stringBase + 0x4C, 4, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, stringBase + 0x60, 5, 1, 0, 0);
    AmemSetLock__13CAmemCacheSetFv(&ppvAmemCacheSet);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::createViewer()
{
    CPartPcsViewerState* viewer = reinterpret_cast<CPartPcsViewerState*>(this);
    char* stringBase = s_p_tina_rodata_801d7ee0;
    void* stage;

    IsBigAlloc__7CUSBPcsFi(&USBPcs, 1);
    viewer->m_freePtr = 0;
    viewer->m_stageExtra = 0;
    viewer->m_blockOnFrame = 0;
    viewer->m_miruraEventActive = 0;
    viewer->m_disableShokiDraw = 0;

    if ((int)Game.m_currentSceneId == 7) {
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x180000, stringBase + 0x22C, 0);
        viewer->m_stageLoad = stage;
        viewer->m_stageDefault = stage;
        viewer->m_stageAmem = 0;
    } else {
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x180000, stringBase + 0x22C, 0);
        viewer->m_stageLoad = stage;
        viewer->m_stageDefault = stage;
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x400000, stringBase + 0x23C, 2);
        viewer->m_stageAmem = stage;
    }

    Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl(
        &ppvAmemCacheSet,
        stringBase + 0x74,
        reinterpret_cast<CPartPcsViewerState*>(&PartPcs)->m_stageLoad,
        reinterpret_cast<CPartPcsViewerState*>(&PartPcs)->m_stageAmem,
        0x400,
        reinterpret_cast<void*>(pppNotAllocAmemCacheRmem),
        0,
        reinterpret_cast<void*>(pppAmemDeletePmng),
        0,
        reinterpret_cast<void*>(pppAmemRefCntError),
        0);

    ::memset(&PartMng, 0, 0x23FD8);
    PartMng.Create();
    reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 4)->CreateBuffer();
}

/*
 * --INFO--
 * PAL Address: 0x8005322C
 * PAL Size: 180b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::destroy()
{
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 4);

    IsBigAlloc__7CUSBPcsFi(&USBPcs, 0);
    Destroy__8CPartMngFv(&PartMng);

    if (usb->m_stageAmem != 0) {
        DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, usb->m_stageAmem);
    }

    AssertCache__13CAmemCacheSetFv(&ppvAmemCacheSet);
    Destroy__13CAmemCacheSetFv(&ppvAmemCacheSet);

    DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, usb->m_stageDefault);

    if (usb->m_freePtr != 0) {
        Free__7CMemoryFPv(&Memory, usb->m_freePtr);
    }

    if (usb->m_stageExtra != 0) {
        DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, usb->m_stageExtra);
    }
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::ChangeDataStage(CMemory::CStage*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::ResetDataStage()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x800531c8
 * PAL Size: 100b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::calcInit()
{
	PartMng.pppRefCnt0Up();
	if ((int)Game.m_currentSceneId == 7) {
		g_par_calc_prof.ProfStart();
		g_par_draw_prof.ProfStart();
	}
	PartMng.pppPartInit();
}

/*
 * --INFO--
 * PAL Address: 0x80053138
 * PAL Size: 144b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::calc()
{
	unsigned char* raw = reinterpret_cast<unsigned char*>(this);

	PartMng.LoadPartNoSyncCalc();
	if (raw[0x2D] != 0) {
		int freeSize;

		raw[0x2D] = 0;
		freeSize = ppvAmemCacheSet.AmemGetFreeSize();
		System.Printf(DAT_801d8068, freeSize / 1024);
	}
	ppvAmemCacheSet.CalcPrio();
	PartMng.pppDumpCacheIdx();
}

/*
 * --INFO--
 * PAL Address: 0x8005309c
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::calcViewer()
{
    CUSBStreamData* usbStream = reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 4);

    OSStartStopwatch(&g_par_calc_prof);
    PartMng.pppEditBeforeCalc();
    PartMng.pppEditPartCalc();
    OSStopStopwatch(&g_par_calc_prof);

    mccReadData__7CUSBPcsFv(&USBPcs);
    if (usbStream->IsUSBStreamDataDone()) {
        if (usbStream->m_packetCode != 0) {
            PartMng.pppDataRcv(usbStream->m_packetCode, reinterpret_cast<char*>(usbStream->m_data), usbStream->m_sizeBytes);
        }
        usbStream->SetUSBStreamDataDone();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80053074
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::calcDead()
{
    PartMng.pppPartDead();
}

/*
 * --INFO--
 * PAL Address: 0x8005304c
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::ClearOt()
{
    ppvDrawMng.ClearOt();
}

/*
 * --INFO--
 * PAL Address: 0x80052fb4
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawShadow()
{
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 4);
    CGame* game = &Game;

    if (game->m_gameWork.m_gamePaused == 0 && usb->m_disableShokiDraw == 0 &&
        static_cast<int>(*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&CameraPcs) + 0x404)) != 0) {
        Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
        pppInitDrawEnv(1);
        PartMng.pppSetRendMatrix();
        PartMng.pppDrawPrio(3);
        pppClearDrawEnv();
        Graphic.SetDrawDoneDebugData(0x7f);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80052f1c
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawCharaBefore()
{
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 4);
    CGame* game = &Game;

    if (game->m_gameWork.m_gamePaused == 0 && usb->m_disableShokiDraw == 0) {
        Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
        Graphic.SetFog(1, 0);
        pppInitDrawEnv(0);
        PartMng.pppSetRendMatrix();
        PartMng.pppDrawPrio(4);
        pppClearDrawEnv();
        Graphic.SetDrawDoneDebugData(0x7f);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80052e3c
 * PAL Size: 224b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::draw()
{
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 4);
    CGame* game = &Game;

    SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic, 0x7fff);
    if (game->m_gameWork.m_gamePaused != 0) {
        DrawOt__10pppDrawMngFv(&ppvDrawMng);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x7f);
        return;
    }

    if (usb->m_disableShokiDraw != 0) {
        DrawOt__10pppDrawMngFv(&ppvDrawMng);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x7f);
        return;
    }

    SetFog__8CGraphicFii(&Graphic, 1, 0);
    pppInitDrawEnv(0);
    pppSetRendMatrix__8CPartMngFv(&PartMng);
    pppDraw__8CPartMngFv(&PartMng);
    pppClearDrawEnv();
    SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x7f);
}

/*
 * --INFO--
 * PAL Address: 0x80052da4
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawShadowViewer()
{
    Graphic._WaitDrawDone(s_tinaSourceName, 0x308);
    OSStartStopwatch(&g_par_draw_prof);
    OSStartStopwatch(&g_par_calc_prof);
    pppSetProjection();
    pppInitDrawEnv(0);
    PartMng.pppEditDrawShadow();
    OSStopStopwatch(&g_par_calc_prof);
    Graphic._WaitDrawDone(s_tinaSourceName, 0x30f);
    OSStopStopwatch(&g_par_draw_prof);
    pppClearDrawEnv();
}

/*
 * --INFO--
 * PAL Address: 0x80052d0c
 * PAL Size: 152b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawViewer()
{
    Graphic._WaitDrawDone(s_tinaSourceName, 0x31a);
    OSStartStopwatch(&g_par_draw_prof);
    OSStartStopwatch(&g_par_calc_prof);
    pppSetProjection();
    pppInitDrawEnv(0);
    PartMng.pppEditDraw();
    OSStopStopwatch(&g_par_calc_prof);
    Graphic._WaitDrawDone(s_tinaSourceName, 0x322);
    OSStopStopwatch(&g_par_draw_prof);
    pppClearDrawEnv();
}

/*
 * --INFO--
 * PAL Address: 0x80052c78
 * PAL Size: 148b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawAfter()
{
    CGame* game = &Game;

    if (game->m_gameWork.m_gamePaused == 0 &&
        *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this)      + 0x30) == 0) {
        Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
        Graphic.SetFog(1, 0);
        pppInitDrawEnv(0);
        PartMng.pppSetRendMatrix();
        PartMng.pppPartDrawAfter();
        pppClearDrawEnv();
        Graphic.SetDrawDoneDebugData(0x7f);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80052bd4
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::DrawMenu(int fpNo)
{
    if (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x30) == 0) {
        Graphic.SetFog(1, 0);
        Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
        pppInitDrawEnv(0);
        PartMng.pppSetRendMatrix();
        PartMng.pppDrawPrioPdtFpno(6, 0, static_cast<short>(fpNo));
        PartMng.drawEnd();
        pppClearDrawEnv();
        Graphic.SetDrawDoneDebugData(0x7f);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80052b10
 * PAL Size: 196b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::DrawShoki()
{
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 4);

    if (usb->m_disableShokiDraw == 0 && (int)Game.m_currentSceneId == 4) {
        Graphic.SetFog(1, 0);
        if (Game.m_gameWork.m_gamePaused == 0 &&
            (int)*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&CameraPcs) + 0x404) != 0) {
            Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
            pppInitDrawEnv(1);
            PartMng.pppSetRendMatrix();
            PartMng.pppDrawPrio(8);
            pppClearDrawEnv();
            Graphic.SetDrawDoneDebugData(0x7f);
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x80052a74
 * PAL Size: 156b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::DrawMenuIdx(int index)
{
    if (*reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(this) + 0x30) == 0) {
        Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
        Graphic.SetFog(1, 0);
        pppInitDrawEnv(0);
        PartMng.pppSetRendMatrix();
        PartMng.pppDrawIdx(index);
        PartMng.drawEnd();
        pppClearDrawEnv();
        Graphic.SetDrawDoneDebugData(0x7f);
    }
}

/*
 * --INFO--
 * PAL Address: 0x80052a48
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::SetParLocIdx(int index, Vec& location)
{
	struct PartMngPosView {
		u8 pad[0x2A20];
		float x;
		float y;
		float z;
	};
	PartMngPosView* pppMngSt = reinterpret_cast<PartMngPosView*>(reinterpret_cast<u8*>(&PartMng) + (index * 0x158));
	pppMngSt->x = location.x;
	pppMngSt->y = location.y;
	pppMngSt->z = location.z;
}

/*
 * --INFO--
 * PAL Address: 0x80052a1c
 * PAL Size: 44b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::GetParLocIdx(int index, Vec& location)
{
	struct PartMngPosView {
		u8 pad[0x2A20];
		float x;
		float y;
		float z;
	};
	PartMngPosView* pppMngSt = reinterpret_cast<PartMngPosView*>(reinterpret_cast<u8*>(&PartMng) + (index * 0x158));
	location.x = pppMngSt->x;
	location.y = pppMngSt->y;
	location.z = pppMngSt->z;
}

/*
 * --INFO--
 * PAL Address: 0x80052990
 * PAL Size: 140b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::SetParColIdx(int index, pppFVECTOR4& color)
{
	_pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(&PartMng) + index;
	float* colorValues = reinterpret_cast<float*>(&color);
	float one = kPartColorIdentityOne;

	GetMngStUserFloat0(pppMngSt) = colorValues[0];
	GetMngStUserFloat1(pppMngSt) = colorValues[1];
	GetMngStScaleFactor(pppMngSt) = colorValues[2];
	GetMngStOwnerScale(pppMngSt) = colorValues[3];

	if (one == colorValues[0] && one == colorValues[1] && one == colorValues[2] && one == colorValues[3]) {
		GetMngStOwnerScaleMode(pppMngSt) = 0;
		return;
	}

	GetMngStOwnerScaleMode(pppMngSt) = 1;
	GetMngStLockScaleFromOwner(pppMngSt) = 1;
}

/*
 * --INFO--
 * PAL Address: 0x8005295c
 * PAL Size: 52b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::GetParColIdx(int index, pppFVECTOR4& color)
{
	struct PartMngColorView {
		u8 pad[0x2A50];
		float r;
		float g;
		float b;
		float a;
	};
	PartMngColorView* pppMngSt =
	    reinterpret_cast<PartMngColorView*>(reinterpret_cast<u8*>(&PartMng) + (index * 0x158));
	float* colorValues = reinterpret_cast<float*>(&color);

	colorValues[0] = pppMngSt->r;
	colorValues[1] = pppMngSt->g;
	colorValues[2] = pppMngSt->b;
	colorValues[3] = pppMngSt->a;
}

/*
 * --INFO--
 * PAL Address: 0x80052764
 * PAL Size: 504b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawAfterViewer()
{
	int frameSign;

	Graphic._WaitDrawDone(s_tinaSourceName, 0x3f1);
	OSStartStopwatch(&g_par_draw_prof);
	OSStartStopwatch(&g_par_calc_prof);
	Graphic.SetFog(1, 0);
	pppInitDrawEnv(0);
	PartMng.pppEditPartDrawAfter();
	OSStopStopwatch(&g_par_calc_prof);
	Graphic._WaitDrawDone(s_tinaSourceName, 0x3fb);
	OSStopStopwatch(&g_par_draw_prof);
	PartMng.pppGet2Dpos();
	pppClearDrawEnv();

	if (gDebugSpinnerTextInitialized == 0) {
		gDebugSpinnerText = sDebugSpinnerText;
		gDebugSpinnerTextInitialized = 1;
	}
	if (gDebugSpinnerFrameInitialized == 0) {
		gDebugSpinnerFrame = 0;
		gDebugSpinnerFrameInitialized = 1;
	}

	gDebugSpinnerFrame++;
	frameSign = gDebugSpinnerFrame >> 0x1f;
	Graphic.Printf(
		s_tinaTitleFmt,
		(int)(char)gDebugSpinnerText[(frameSign * 4 |
								 (unsigned int)((gDebugSpinnerFrame >> 4) * 0x40000000 + frameSign) >> 0x1e) -
								frameSign]);

	g_par_calc_prof.ProfEnd();
	g_par_draw_prof.ProfEnd();
	Graphic.Printf(
		s_tinaCalcFmt, (double)g_par_calc_prof.m_lastTime, (double)g_par_calc_prof.m_maxTime);
	Graphic.Printf(
		s_tinaDrawFmt, (double)g_par_draw_prof.m_lastTime, (double)g_par_draw_prof.m_maxTime);
	Graphic.Printf(
		s_tinaHeapFmt,
		(double)((float)gPppHeapUseRateWords[0] / kPppHeapUseRateDivisor),
		(double)((float)gPppHeapUseRateWords[1] / kPppHeapUseRateDivisor));
}

/*
 * --INFO--
 * PAL Address: 0x80052660
 * PAL Size: 260b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CPartPcs::IsLoadPartCompleted()
{
    CPartMngState* state = GetPartMngState();

    for (int i = 0; i < 16; i++) {
        if (state->m_partAsyncBusy[i] != 0) {
            return 0;
        }
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800524d0
 * PAL Size: 400b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void LoadFieldPdt0(int mapId, int floorId)
{
    CPartMngState* loadState = GetPartMngState();
    PppPdtSlotRaw* pdtSlots = GetPartMngPdtSlots();
    int pdtSlot;
    char path[1024];

    DAT_8032ed3c = 0;
    DAT_8032ed38 = 0;

    if (loadState->m_partLoadMode != 3) {
        pppReleasePdt__8CPartMngFi(&PartMng, 0);
        pppReleasePdt__8CPartMngFi(&PartMng, 6);
        pppReleasePdt__8CPartMngFi(&PartMng, 7);
        ppvAmemCacheSet.AmemGetLock();
        ppvAmemCacheSet.RefCnt0Compare();
    }

    PartPcs.m_usbStreamData.m_fieldLoadReq = 1;

    sprintf(path, s_dvd_tina_stage_03d_fp_03d_801d7fec, mapId, floorId);
    pdtSlot = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, 0, 1, 0, 0);
    if (pdtSlot != 0) {
        pdtSlot = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, 0, 1, 0, 0);
        if ((pdtSlot != 0) && (loadState->m_partLoadMode != 2) && (loadState->m_partLoadMode != 3)) {
            _pppDataHead* pppDataHead;
            PPPCREATEPARAM* createParam;
            int checkOff;
            int i;

            pppDataHead = pdtSlots[0].m_pppDataHead;
            createParam = PartMng.pppGetDefaultCreateParam();
            checkOff = 0;
            for (i = 0; i < static_cast<int>((unsigned int)pppDataHead->m_partCount); i++) {
                if (*reinterpret_cast<int*>(&pdtSlots[0].m_pppDataHead[2].m_shapeGroupCount + checkOff) != -0x1000) {
                    pppCreate__8CPartMngFiiP14PPPCREATEPARAMi(&PartMng, 0, i, createParam, 0);
                }
                checkOff += 0x60;
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800523f8
 * PAL Size: 216b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::LoadFieldPdt(int mapId, int floorId, void* amemBase, unsigned long loadCacheParam, unsigned char mode)
{
    CPartMngState* state = GetPartMngState();

    state->m_partAMemBase = reinterpret_cast<unsigned int>(amemBase);
    state->m_partAMemCursor = reinterpret_cast<unsigned int>(amemBase);
    state->m_partLoadCacheParam = loadCacheParam;
    state->m_partChunkIndex = 0;
    state->m_asyncHandleCount = 0;

    if (loadCacheParam != 0) {
        if (mode == 1) {
            state->m_partLoadMode = 2;
        } else if (mode == 2) {
            state->m_partLoadMode = 3;
            for (int i = 0; i < 0x10; i++) {
                state->m_partAsyncBusy[i] = 0;
            }
        } else {
            state->m_partLoadMode = 1;
        }
    } else {
        state->m_partLoadMode = 0;
    }

    LoadFieldPdt0(mapId, floorId);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void loadPdtPtx(char*, void*, int, void*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
int CPartPcs::LoadMonsterPdt(int monsterId, int variant, void* pdtData, int pdtCount, void* ptxData, int ptxCount)
{
    int pdtSlotIndex;
    int loaded;
    char path[260];
    CPartMngState* state = GetPartMngState();

    if (variant == 0) {
        sprintf(path, s_dvd_tina_mon_m_03d_801d7fc0, monsterId);
    } else {
        sprintf(path, s_dvd_tina_mon_m_03d__c_801d7fd4, monsterId, variant + 0x61);
    }

    state->m_partAMemBase = 0;
    state->m_partAMemCursor = 0;
    state->m_partLoadCacheParam = 0;
    state->m_partChunkIndex = 0;
    state->m_asyncHandleCount = 0;
    state->m_partLoadMode = 0;

    pdtSlotIndex = pppGetFreeDataMng__8CPartMngFv(&PartMng);
    if (pdtSlotIndex == -1) {
        pdtSlotIndex = -1;
    } else {
        loaded = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, pdtSlotIndex, 1, ptxData, ptxCount);
        if (loaded == 0) {
            pppReleasePdt__8CPartMngFi(&PartMng, pdtSlotIndex);
            pdtSlotIndex = -1;
        } else {
            loaded = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, pdtSlotIndex, 1, pdtData, pdtCount);
            if (loaded == 0) {
                pppReleasePdt__8CPartMngFi(&PartMng, pdtSlotIndex);
                pdtSlotIndex = -1;
            } else {
                PartPcs.m_usbStreamData.m_printFreeOnNext = 1;
            }
        }
    }

    return pdtSlotIndex;
}

/*
 * --INFO--
 * PAL Address: 0x80052128
 * PAL Size: 392b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartPcs::LoadMenuPdt(char* fileName)
{
    char* language;
    int pdtSlotIndex;
    int loaded;
    CMemory::CStage* stage;
    char path[256];

    language = GetLangString__5CGameFv(&Game);
    sprintf(path, s_dvd__smenu__s_801d7fb0, language, fileName);

    stage = reinterpret_cast<CMemory::CStage*>(*reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0xEC));
    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = reinterpret_cast<CMemory::CStage*>(*reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0xF4));
    }

    m_usbStreamData.m_stageLoad = stage;
    SetRStage__13CAmemCacheSetFPQ27CMemory6CStage(&ppvAmemCacheSet, stage);

    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&PartMng) + 0x236F4) = 0;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&PartMng) + 0x236F8) = 0;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&PartMng) + 0x236FC) = 0;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&PartMng) + 0x23700) = 0;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&PartMng) + 0x23704) = 0;
    *reinterpret_cast<unsigned int*>(reinterpret_cast<unsigned char*>(&PartMng) + 0x23708) = 0;

    pdtSlotIndex = pppGetFreeDataMng__8CPartMngFv(&PartMng);
    if (pdtSlotIndex == -1) {
        pdtSlotIndex = -1;
    } else {
        loaded = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, pdtSlotIndex, 0, 0, 0);
        if (loaded == 0) {
            pppReleasePdt__8CPartMngFi(&PartMng, pdtSlotIndex);
            pdtSlotIndex = -1;
        } else {
            loaded = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, pdtSlotIndex, 0, 0, 0);
            if (loaded == 0) {
                pppReleasePdt__8CPartMngFi(&PartMng, pdtSlotIndex);
                pdtSlotIndex = -1;
            } else {
                reinterpret_cast<unsigned char*>(&PartPcs)[0x2d] = 1;
            }
        }
    }

    m_usbStreamData.m_stageLoad = m_usbStreamData.m_stageDefault;
    SetRStage__13CAmemCacheSetFPQ27CMemory6CStage(&ppvAmemCacheSet, m_usbStreamData.m_stageDefault);

    return pdtSlotIndex;
}

/*
 * --INFO--
 * PAL Address: 0x80052100
 * PAL Size: 40b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::ReleasePdt(int pdtSlot)
{
    pppReleasePdt__8CPartMngFi(&PartMng, pdtSlot);
}

/*
 * --INFO--
 * PAL Address: 0x8005205c
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::StartLocationTitle()
{
    int loaded;
    char path[1024];
    CGame* game = &Game;

    sprintf(path, s_dvd_tina_stage_03d_title_801d7f94, game->m_currentMapId);
    loaded = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, 6, 0, 0, 0);
    if ((loaded != 0) && ((loaded = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, 6, 0, 0, 0), loaded != 0))) {
        m_usbStreamData.m_blockOnFrame = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005201c
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::EndLocationTitle()
{
    pppReleasePdt__8CPartMngFi(&PartMng, 6);
    m_usbStreamData.m_blockOnFrame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80051f78
 * PAL Size: 164b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::StartMiruraEvent()
{
    int loaded;
    char path[1024];
    CGame* game = &Game;

    sprintf(path, s_dvd_tina_stage_03d_mirura_801d7f78, game->m_currentMapId);
    loaded = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, 7, 0, 0, 0);
    if ((loaded != 0) && ((loaded = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, 7, 0, 0, 0), loaded != 0))) {
        m_usbStreamData.m_miruraEventActive = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80051f38
 * PAL Size: 64b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::EndMiruraEvent()
{
    pppReleasePdt__8CPartMngFi(&PartMng, 7);
    m_usbStreamData.m_miruraEventActive = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::SetUSBData()
{
	// TODO
}
