#include "ffcc/p_tina.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/game.h"
#include "ffcc/p_camera.h"
#include "ffcc/p_menu.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/p_usb.h"
#include "ffcc/stopwatch.h"
extern "C" {
extern const char sDebugSpinnerText[5];
extern const float kPppHeapUseRateDivisor;
}
#include "ffcc/linkage.h"
#include "ffcc/USBStreamData.h"
#include <string.h>
#include <PowerPC_EABI_Support/Msl/MSL_C/MSL_Common/stdio.h>

extern "C" const char sNoNameProfileLabel[];
extern "C" unsigned char g_IsDrawHeapSize = 1;

extern "C" void create__8CPartPcsFv(CPartPcs*);
extern "C" void destroy__8CPartPcsFv(CPartPcs*);
extern "C" void calcInit__8CPartPcsFv(CPartPcs*);
extern "C" void calc__8CPartPcsFv(CPartPcs*);
extern "C" void calcDead__8CPartPcsFv(CPartPcs*);
extern "C" void ClearOt__8CPartPcsFv(CPartPcs*);
extern "C" void drawShadow__8CPartPcsFv(CPartPcs*);
extern "C" void drawCharaBefore__8CPartPcsFv(CPartPcs*);
extern "C" void draw__8CPartPcsFv(CPartPcs*);
extern "C" void drawAfter__8CPartPcsFv(CPartPcs*);
extern "C" void createViewer__8CPartPcsFv(CPartPcs*);
extern "C" void calcViewer__8CPartPcsFv(CPartPcs*);
extern "C" void drawShadowViewer__8CPartPcsFv(CPartPcs*);
extern "C" void drawViewer__8CPartPcsFv(CPartPcs*);
extern "C" void drawAfterViewer__8CPartPcsFv(CPartPcs*);

extern const char sTinaGbaResourceStrings[] = {
    (char)0x64, (char)0x76, (char)0x64, (char)0x2F, (char)0x67, (char)0x62, (char)0x61, (char)0x2F,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x66, (char)0x66, (char)0x63, (char)0x63,
    (char)0x5F, (char)0x63, (char)0x6C, (char)0x69, (char)0x2E, (char)0x62, (char)0x69, (char)0x6E,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x6F, (char)0x62, (char)0x6A, (char)0x64,
    (char)0x61, (char)0x74, (char)0x2E, (char)0x73, (char)0x70, (char)0x74, (char)0x00, (char)0x00,
    (char)0x69, (char)0x63, (char)0x6F, (char)0x6E, (char)0x2E, (char)0x64, (char)0x61, (char)0x74,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00, (char)0x46, (char)0x46, (char)0x20, (char)0x43,
    (char)0x72, (char)0x79, (char)0x73, (char)0x74, (char)0x61, (char)0x6C, (char)0x20, (char)0x43,
    (char)0x68, (char)0x72, (char)0x6F, (char)0x6E, (char)0x69, (char)0x63, (char)0x6C, (char)0x65,
    (char)0x73, (char)0x00, (char)0x00, (char)0x00,
};
extern const char sPartPcsGameTableName[] = "CPartPcs(GAME)";
extern const char sPartPcsViewerTableName[] = "CPartPcs(PART_VIEWER)";
extern const char sPartPcsClassName[] = "CPartPcs";
extern const char sPartPcsManagerClassName[] = "CManager";
extern const char sPartPcsProcessClassName[] = "CProcess";
extern const char sMiruraPdtPathFmt[] = "dvd/tina/stage%03d/mirura";
extern const char sLocationTitlePdtPathFmt[] = "dvd/tina/stage%03d/title";
extern const char sMenuPdtPathFmt[] = "dvd/%smenu/%s";
extern const char sMonsterPdtPathFmt[] = "dvd/tina/mon/m%03d";
extern const char sMonsterVariantPdtPathFmt[] = "dvd/tina/mon/m%03d_%c";
extern const char sFieldPdtPathFmt[] = "dvd/tina/stage%03d/fp%03d";
static const char s_p_tina_cpp[] = "p_tina.cpp";
extern const char sPartPcsTitleFmt[0x0C] = "Tina [%c]";
extern const char sPartPcsCalcProfileFmt[0x18] = "clc=%.3f%%  max=%.3f%%";
extern const char sPartPcsDrawProfileFmt[0x18] = "drw=%.3f%%  max=%.3f%%";
extern const char sPartPcsHeapProfileFmt[0x18] = "hpm=%.3f%%  max=%.3f%%";
extern const char sTinaParticleAMemFreeFmt[] = {
    (char)0x0A, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x0A, (char)0x20, (char)0x20, (char)0x20,
    (char)0x20, (char)0x20, (char)0x20, (char)0x83, (char)0x70, (char)0x81, (char)0x5B, (char)0x83,
    (char)0x65, (char)0x83, (char)0x42, (char)0x83, (char)0x4E, (char)0x83, (char)0x8B, (char)0x20,
    (char)0x41, (char)0x2D, (char)0x4D, (char)0x45, (char)0x4D, (char)0x20, (char)0x83, (char)0x74,
    (char)0x83, (char)0x8A, (char)0x81, (char)0x5B, (char)0x3D, (char)0x25, (char)0x64, (char)0x20,
    (char)0x4B, (char)0x62, (char)0x79, (char)0x74, (char)0x65, (char)0x0A, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D, (char)0x3D,
    (char)0x3D, (char)0x0A, (char)0x0A, (char)0x00,
};
extern const char sPartPcsDataStageName[0x10] = "CPartPcs.dat";
extern const char sPartPcsAmemStageName[0x10] = "CPartPcs.amem";
extern const char sChobitBasePath[] = "dvd/tina/chobit";
extern const char sChobit0Path[0x14] = "dvd/tina/chobit_0";
extern const char sChobit1Path[0x14] = "dvd/tina/chobit_1";
extern const char sChobit2Path[0x14] = "dvd/tina/chobit_2";
extern const char sChobit3Path[0x14] = "dvd/tina/chobit_3";
extern const char sChobit4Path[0x14] = "dvd/tina/chobit_4";
extern const char sPartPcsPrioTimeFmt[0x34] = "  prioTime=%d  prio=%d  pdtID=%2d  fpno=%3d   %s\n";
extern const char sTinaDeleteNoticeMsg[] = {
    (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20,
    (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20, (char)0x20,
    (char)0x82, (char)0xF0, (char)0x8D, (char)0xED, (char)0x8F, (char)0x9C, (char)0x82, (char)0xB5,
    (char)0x82, (char)0xDC, (char)0x82, (char)0xB7, (char)0x81, (char)0x42, (char)0x0A, (char)0x00,
    (char)0x00, (char)0x00, (char)0x00, (char)0x00,
};
/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: 0x80061fe0
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CPartPcs::CPartPcs()
{
}

/*
 * --INFO--
 * PAL Address: 0x80053CA0
 * PAL Size: 100b
 * EN Address: 0x80061f7c
 * EN Size: 100b
 * JP Address: TODO
 * JP Size: TODO
 */
inline CPartPcs::~CPartPcs()
{
}

CPartPcs PartPcs;
static CProcessTableCallback s_partTableDescCreate = {0, 0xFFFFFFFF,
                                                       reinterpret_cast<unsigned int>(create__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescDestroy = {0, 0xFFFFFFFF,
                                                        reinterpret_cast<unsigned int>(destroy__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescCalcInit = {0, 0xFFFFFFFF,
                                                         reinterpret_cast<unsigned int>(calcInit__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescCalc = {0, 0xFFFFFFFF,
                                                     reinterpret_cast<unsigned int>(calc__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescCalcDead = {0, 0xFFFFFFFF,
                                                         reinterpret_cast<unsigned int>(calcDead__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescClearOt = {0, 0xFFFFFFFF,
                                                        reinterpret_cast<unsigned int>(ClearOt__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescDrawShadow = {0, 0xFFFFFFFF,
                                                           reinterpret_cast<unsigned int>(drawShadow__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescDrawCharaBefore = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawCharaBefore__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescDraw = {0, 0xFFFFFFFF,
                                                     reinterpret_cast<unsigned int>(draw__8CPartPcsFv)};
static CProcessTableCallback s_partTableDescDrawAfter = {0, 0xFFFFFFFF,
                                                          reinterpret_cast<unsigned int>(drawAfter__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescCreate = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(createViewer__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescDestroy = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(destroy__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescCalcInit = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcInit__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescCalc = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcViewer__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescCalcDead = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(calcDead__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescClearOt = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(ClearOt__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescDrawShadow = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawShadowViewer__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescDraw = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawViewer__8CPartPcsFv)};
static CProcessTableCallback s_partViewerTableDescDrawAfter = {
    0, 0xFFFFFFFF, reinterpret_cast<unsigned int>(drawAfterViewer__8CPartPcsFv)};
CProcessTable CPartPcs::m_table[2] = {
    {
        const_cast<char*>(sPartPcsGameTableName),
        {
            s_partTableDescCreate.m_thisOffset, s_partTableDescCreate.m_virtualOffset, s_partTableDescCreate.m_function,
            s_partTableDescDestroy.m_thisOffset, s_partTableDescDestroy.m_virtualOffset, s_partTableDescDestroy.m_function,
            s_partTableDescCalcInit.m_thisOffset, s_partTableDescCalcInit.m_virtualOffset, s_partTableDescCalcInit.m_function,
            0x15, 0,
            s_partTableDescCalc.m_thisOffset, s_partTableDescCalc.m_virtualOffset, s_partTableDescCalc.m_function,
            0x1D, 0,
            s_partTableDescCalcDead.m_thisOffset, s_partTableDescCalcDead.m_virtualOffset, s_partTableDescCalcDead.m_function,
            0x28, 0,
            s_partTableDescClearOt.m_thisOffset, s_partTableDescClearOt.m_virtualOffset, s_partTableDescClearOt.m_function,
            0x2C, 1,
            s_partTableDescDrawShadow.m_thisOffset, s_partTableDescDrawShadow.m_virtualOffset, s_partTableDescDrawShadow.m_function,
            0x31, 1,
            s_partTableDescDrawCharaBefore.m_thisOffset, s_partTableDescDrawCharaBefore.m_virtualOffset, s_partTableDescDrawCharaBefore.m_function,
            0x38, 1,
            s_partTableDescDraw.m_thisOffset, s_partTableDescDraw.m_virtualOffset, s_partTableDescDraw.m_function,
            0x3E, 1,
            s_partTableDescDrawAfter.m_thisOffset, s_partTableDescDrawAfter.m_virtualOffset, s_partTableDescDrawAfter.m_function,
            0x40, 1,
        },
    },
    {
        const_cast<char*>(sPartPcsViewerTableName),
        {
            s_partViewerTableDescCreate.m_thisOffset, s_partViewerTableDescCreate.m_virtualOffset, s_partViewerTableDescCreate.m_function,
            s_partViewerTableDescDestroy.m_thisOffset, s_partViewerTableDescDestroy.m_virtualOffset, s_partViewerTableDescDestroy.m_function,
            s_partViewerTableDescCalcInit.m_thisOffset, s_partViewerTableDescCalcInit.m_virtualOffset, s_partViewerTableDescCalcInit.m_function,
            0x15, 0,
            s_partViewerTableDescCalc.m_thisOffset, s_partViewerTableDescCalc.m_virtualOffset, s_partViewerTableDescCalc.m_function,
            0x1D, 0,
            s_partViewerTableDescCalcDead.m_thisOffset, s_partViewerTableDescCalcDead.m_virtualOffset, s_partViewerTableDescCalcDead.m_function,
            0x28, 0,
            s_partViewerTableDescClearOt.m_thisOffset, s_partViewerTableDescClearOt.m_virtualOffset, s_partViewerTableDescClearOt.m_function,
            0x2C, 1,
            s_partViewerTableDescDrawShadow.m_thisOffset, s_partViewerTableDescDrawShadow.m_virtualOffset, s_partViewerTableDescDrawShadow.m_function,
            0x31, 1,
            s_partViewerTableDescDraw.m_thisOffset, s_partViewerTableDescDraw.m_virtualOffset, s_partViewerTableDescDraw.m_function,
            0x3E, 1,
            s_partViewerTableDescDrawAfter.m_thisOffset, s_partViewerTableDescDrawAfter.m_virtualOffset, s_partViewerTableDescDrawAfter.m_function,
            0x40, 1,
        },
    },
};
char g_MsgFlashy[0x36] =
    "\x81\x9A\x81\x99\x81\x9A\x81\x99\x81\x9A\x81\x99\x81\x9A\x81\x99"
    "\x81\x9A\x81\x99\x81\x9A\x81\x99\x81\x9A\x81\x99\x81\x9A\x81\x99"
    "\x81\x9A\x81\x99\x81\x9A\x81\x99\x81\x9A\x81\x99\x81\x9A\x81\x99"
    "\x81\x9A\x81\x99\x0A";
int g_MaxDataSize;
int g_MaxHeapSize;
extern "C" {
const char* sDebugSpinnerTextPtr;
signed char sDebugSpinnerTextPtrInit;
int s_debugSpinnerFrameCounter;
signed char s_debugSpinnerFrameCounterInit;
unsigned char g_IsCheckDrawDone;
signed char s_debugSpinnerFrameCounterPad0;
signed char s_debugSpinnerFrameCounterPad1;
signed char s_debugSpinnerFrameCounterPad2;
}

static const int kPppFieldParticleNoAutoCreate = -0x1000;

CProfile g_par_calc_prof(const_cast<char*>(sNoNameProfileLabel));
CProfile g_par_draw_prof(const_cast<char*>(sNoNameProfileLabel));

/*
 * --INFO--
 * PAL Address: 0x80053950
 * PAL Size: 16b
 * EN Address: 0x8005fa90
 * EN Size: 20b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::Init()
{
	CUSBStreamDataState* usbStream = &m_usbStreamState;
	usbStream->m_fieldLoadReq = 0;
	usbStream->m_printFreeOnNext = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005394C
 * PAL Size: 4b
 * EN Address: 0x8005faa4
 * EN Size: 4b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::Quit()
{
	// TODO
}

/*
 * --INFO--
 * PAL Address: 0x80053940
 * PAL Size: 12b
 * EN Address: 0x8005faa8
 * EN Size: 12b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::onScriptChanging(char*)
{
	CUSBStreamDataState* usbStream = &m_usbStreamState;
	usbStream->m_fieldLoadReq = 0;
}

/*
 * --INFO--
 * PAL Address: 0x8005392C
 * PAL Size: 20b
 * EN Address: 0x8005fab4
 * EN Size: 20b
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartPcs::GetTable(unsigned long index)
{
	return reinterpret_cast<int>(&CPartPcs::m_table[index]);
}

/*
 * --INFO--
 * PAL Address: 0x80053900
 * PAL Size: 44b
 * EN Address: 0x8005fac8
 * EN Size: 44b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned char pppNotAllocAmemCacheRmem(unsigned long)
{
	PartMng.pppDumpMngSt();
	return 0;
}

/*
 * --INFO--
 * PAL Address: 0x800536F0
 * PAL Size: 528b
 * EN Address: 0x8005faf4
 * EN Size: 472b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int pppFreeMngStPrioForData()
{
	_pppMngSt* selectedMngSt = 0;
	char* partMngBase = reinterpret_cast<char*>(&PartMng);
	_pppMngSt* currentMngSt = ppvMng;
	int selectedPrio = 1;
	unsigned int selectedPrioTime;
	int index = 0;
	for (int i = 0xc0; i != 0; i--) {
		CPartMng* partMng = reinterpret_cast<CPartMng*>(partMngBase);
		_pppMngSt* candidateA = partMng->m_pppMng;
		if (candidateA != currentMngSt && candidateA->m_baseTime != -0x1000 &&
		    candidateA->m_kind != 0) {
			unsigned char prioA = candidateA->m_prio;
			if (prioA > 1) {
				if (selectedPrio < prioA) {
					selectedPrioTime = candidateA->m_prioTime;
					selectedPrio = prioA;
					selectedMngSt = candidateA;
				} else if (selectedPrio == prioA) {
					unsigned int prioTimeA = candidateA->m_prioTime;
					if ((int)selectedPrioTime < (int)prioTimeA) {
						selectedPrioTime = prioTimeA;
						selectedMngSt = candidateA;
					}
				}
			}
		}

		char* nextPartMngBase = partMngBase + sizeof(_pppMngSt);
		_pppMngSt* candidateB = &partMng->m_pppMng[1];
		partMngBase = nextPartMngBase;
		partMng = reinterpret_cast<CPartMng*>(partMngBase);
		if (candidateB != currentMngSt && candidateB->m_baseTime != -0x1000 &&
		    candidateB->m_kind != 0) {
			unsigned char prioB = candidateB->m_prio;
			if (prioB > 1) {
				if (selectedPrio < prioB) {
					selectedPrioTime = candidateB->m_prioTime;
					selectedPrio = prioB;
					selectedMngSt = candidateB;
				} else if (selectedPrio == prioB) {
					unsigned int prioTimeB = candidateB->m_prioTime;
					if ((int)selectedPrioTime < (int)prioTimeB) {
						selectedPrioTime = prioTimeB;
						selectedMngSt = candidateB;
					}
				}
			}
		}

		partMngBase = reinterpret_cast<char*>(partMng) + sizeof(_pppMngSt);
		index++;
	}

	if (selectedMngSt == 0) {
		return 0;
	}

	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf(g_MsgFlashy, index);
	}
	if ((unsigned int)System.m_execParam >= 3) {
		char* pdtName = PartMng.m_pdtSlots[selectedMngSt->m_kind].m_name;
		System.Printf(
			const_cast<char*>(sPartPcsPrioTimeFmt),
			(unsigned int)selectedMngSt->m_prioTime,
			(unsigned int)selectedMngSt->m_prio,
			(int)selectedMngSt->m_kind,
			(int)selectedMngSt->m_nodeIndex,
			pdtName);
	}
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf(const_cast<char*>(sTinaDeleteNoticeMsg));
	}
	if ((unsigned int)System.m_execParam >= 3) {
		System.Printf(g_MsgFlashy);
	}

	Graphic._WaitDrawDone(const_cast<char*>(s_p_tina_cpp), 0xfc);
	_pppAllFreePObject(reinterpret_cast<_pppMngSt*>(selectedMngSt));
	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800536CC
 * PAL Size: 36b
 * EN Address: 0x8005fccc
 * EN Size: 36b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned char pppAmemDeletePmng(unsigned long)
{
	return pppFreeMngStPrioForData();
}

/*
 * --INFO--
 * PAL Address: 0x800536C4
 * PAL Size: 8b
 * EN Address: 0x8005fcf0
 * EN Size: 68b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned char pppAmemRefCntError(unsigned long)
{
	return 1;
}

/*
 * --INFO--
 * PAL Address: 0x8005357C
 * PAL Size: 328b
 * EN Address: 0x8005fe94
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::create()
{
    CUSBStreamDataState* usb = &m_usbStreamState;
    CMemory::CStage* stage;

    usb->m_freePtr = 0;
    usb->m_stageExtra = 0;
    usb->m_blockOnFrame = 0;
    usb->m_miruraEventActive = 0;
    usb->m_disableShokiDraw = 0;

    if ((int)Game.m_currentSceneId == 7) {
        stage = Memory.CreateStage(0x180000, const_cast<char*>(sPartPcsDataStageName), 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        usb->m_stageAmem = 0;
    } else {
        stage = Memory.CreateStage(0x180000, const_cast<char*>(sPartPcsDataStageName), 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        stage = Memory.CreateStage(0x400000, const_cast<char*>(sPartPcsAmemStageName), 2);
        usb->m_stageAmem = stage;
    }

    ppvAmemCacheSet.Init(
        const_cast<char*>(sPartPcsClassName),
        PartPcs.m_usbStreamState.m_stageLoad,
        PartPcs.m_usbStreamState.m_stageAmem,
        0x400,
        pppNotAllocAmemCacheRmem,
        0,
        pppAmemDeletePmng,
        0,
        pppAmemRefCntError,
        0);

    ::memset(&PartMng, 0, 0x23FD8);
    PartMng.Create();
}

/*
 * --INFO--
 * PAL Address: 0x80053444
 * PAL Size: 312b
 * EN Address: 0x8005febc
 * EN Size: 392b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::createLoad()
{
    CPartMng* state = &PartMng;
    state->m_partAMemBase = 0;
    state->m_partAMemCursor = 0;
    state->m_partLoadCacheParam = 0;
    state->m_partChunkIndex = 0;
    state->m_asyncHandleCount = 0;
    state->m_partLoadMode = 0;

    PartMng.pppLoadPtx(const_cast<char*>(sChobitBasePath), 1, 1, 0, 0);
    PartMng.pppLoadPmd(const_cast<char*>(sChobitBasePath));
    PartMng.pppLoadPan(const_cast<char*>(sChobitBasePath));
    PartMng.pppLoadPdt(const_cast<char*>(sChobit0Path), 1, 1, 0, 0);
    PartMng.pppLoadPdt(const_cast<char*>(sChobit1Path), 2, 1, 0, 0);
    PartMng.pppLoadPdt(const_cast<char*>(sChobit2Path), 3, 1, 0, 0);
    PartMng.pppLoadPdt(const_cast<char*>(sChobit3Path), 4, 1, 0, 0);
    PartMng.pppLoadPdt(const_cast<char*>(sChobit4Path), 5, 1, 0, 0);
    ppvAmemCacheSet.AmemSetLock();
}

/*
 * --INFO--
 * PAL Address: 0x800532E0
 * PAL Size: 356b
 * EN Address: 0x80060044
 * EN Size: 72b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::createViewer()
{
    CUSBStreamDataState* usb = &m_usbStreamState;
    CMemory::CStage* stage;

    USBPcs.IsBigAlloc(1);
    usb->m_freePtr = 0;
    usb->m_stageExtra = 0;
    usb->m_blockOnFrame = 0;
    usb->m_miruraEventActive = 0;
    usb->m_disableShokiDraw = 0;

    if ((int)Game.m_currentSceneId == 7) {
        stage = Memory.CreateStage(0x180000, const_cast<char*>(sPartPcsDataStageName), 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        usb->m_stageAmem = 0;
    } else {
        stage = Memory.CreateStage(0x180000, const_cast<char*>(sPartPcsDataStageName), 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        stage = Memory.CreateStage(0x400000, const_cast<char*>(sPartPcsAmemStageName), 2);
        usb->m_stageAmem = stage;
    }

    ppvAmemCacheSet.Init(
        const_cast<char*>(sPartPcsClassName),
        PartPcs.m_usbStreamState.m_stageLoad,
        PartPcs.m_usbStreamState.m_stageAmem,
        0x400,
        pppNotAllocAmemCacheRmem,
        0,
        pppAmemDeletePmng,
        0,
        pppAmemRefCntError,
        0);

    ::memset(&PartMng, 0, 0x23FD8);
    PartMng.Create();
    m_usbStreamData.CreateBuffer();
}

/*
 * --INFO--
 * PAL Address: 0x8005322C
 * PAL Size: 180b
 * EN Address: 0x8006008c
 * EN Size: 192b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::destroy()
{
    CUSBStreamDataState* usb = &m_usbStreamState;

    USBPcs.IsBigAlloc(0);
    PartMng.Destroy();

    if (usb->m_stageAmem != 0) {
        Memory.DestroyStage(usb->m_stageAmem);
    }

    ppvAmemCacheSet.AssertCache();
    ppvAmemCacheSet.Destroy();

    Memory.DestroyStage(usb->m_stageDefault);

    if (usb->m_freePtr != 0) {
        Memory.Free(usb->m_freePtr);
    }

    if (usb->m_stageExtra != 0) {
        Memory.DestroyStage(usb->m_stageExtra);
    }
}

/*
 * --INFO--
 * PAL Address: 0x800531C8
 * PAL Size: 100b
 * EN Address: 0x800601d4
 * EN Size: 100b
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
 * EN Address: 0x80060238
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::calc()
{
	PartMng.LoadPartNoSyncCalc();
	if (m_usbStreamState.m_printFreeOnNext != 0) {
		int freeSize;

		m_usbStreamState.m_printFreeOnNext = 0;
		freeSize = ppvAmemCacheSet.AmemGetFreeSize();
		System.Printf(const_cast<char*>(sTinaParticleAMemFreeFmt), freeSize / 1024);
	}
	ppvAmemCacheSet.CalcPrio();
	PartMng.pppPartCalc();
}

/*
 * --INFO--
 * PAL Address: 0x8005309C
 * PAL Size: 156b
 * EN Address: 0x800602d0
 * EN Size: 140b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::calcViewer()
{
    int packetCode;

    g_par_calc_prof.Start();
    PartMng.pppEditBeforeCalc();
    PartMng.pppEditPartCalc();
    g_par_calc_prof.Stop();

    USBPcs.mccReadData();
    if (m_usbStreamData.IsUSBStreamDataDone()) {
        packetCode = m_usbStreamData.m_packetCode;
        if (packetCode != 0) {
            PartMng.pppDataRcv(packetCode, reinterpret_cast<char*>(m_usbStreamData.m_data), m_usbStreamData.m_sizeBytes);
        }
        m_usbStreamData.SetUSBStreamDataDone();
    }
}

/*
 * --INFO--
 * PAL Address: 0x80053074
 * PAL Size: 40b
 * EN Address: 0x8006035c
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::calcDead()
{
    PartMng.pppPartDead();
}

/*
 * --INFO--
 * PAL Address: 0x8005304C
 * PAL Size: 40b
 * EN Address: 0x80060384
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::ClearOt()
{
    ppvDrawMng.ClearOt();
}

/*
 * --INFO--
 * PAL Address: 0x80052FB4
 * PAL Size: 152b
 * EN Address: 0x800603ac
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawShadow()
{
    CUSBStreamDataState* usb = &m_usbStreamState;
    CGame* game = &Game;

    if (game->m_gameWork.m_gamePaused == 0 && usb->m_disableShokiDraw == 0 &&
        static_cast<int>(CameraPcs.m_fullScreenShadowEnabled) != 0) {
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
 * PAL Address: 0x80052F1C
 * PAL Size: 152b
 * EN Address: 0x80060450
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawCharaBefore()
{
    CUSBStreamDataState* usb = &m_usbStreamState;
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
 * PAL Address: 0x80052E3C
 * PAL Size: 224b
 * EN Address: 0x800604f4
 * EN Size: 452b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::draw()
{
    CUSBStreamDataState* usb = &m_usbStreamState;
    CGame* game = &Game;

    Graphic.SetDrawDoneDebugDataPartControl(0x7fff);
    if (game->m_gameWork.m_gamePaused != 0) {
        ppvDrawMng.DrawOt();
        Graphic.SetDrawDoneDebugData(0x7f);
        return;
    }

    if (usb->m_disableShokiDraw != 0) {
        ppvDrawMng.DrawOt();
        Graphic.SetDrawDoneDebugData(0x7f);
        return;
    }

    Graphic.SetFog(1, 0);
    pppInitDrawEnv(0);
    PartMng.pppSetRendMatrix();
    PartMng.pppDraw();
    pppClearDrawEnv();
    Graphic.SetDrawDoneDebugData(0x7f);
}

/*
 * --INFO--
 * PAL Address: 0x80052DA4
 * PAL Size: 152b
 * EN Address: 0x800606b8
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawShadowViewer()
{
    Graphic._WaitDrawDone(const_cast<char*>(s_p_tina_cpp), 0x308);
    g_par_draw_prof.Start();
    g_par_calc_prof.Start();
    pppSetProjection();
    pppInitDrawEnv(0);
    PartMng.pppEditDrawShadow();
    g_par_calc_prof.Stop();
    Graphic._WaitDrawDone(const_cast<char*>(s_p_tina_cpp), 0x30f);
    g_par_draw_prof.Stop();
    pppClearDrawEnv();
}

/*
 * --INFO--
 * PAL Address: 0x80052D0C
 * PAL Size: 152b
 * EN Address: 0x80060750
 * EN Size: 152b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawViewer()
{
    Graphic._WaitDrawDone(const_cast<char*>(s_p_tina_cpp), 0x31a);
    g_par_draw_prof.Start();
    g_par_calc_prof.Start();
    pppSetProjection();
    pppInitDrawEnv(0);
    PartMng.pppEditDraw();
    g_par_calc_prof.Stop();
    Graphic._WaitDrawDone(const_cast<char*>(s_p_tina_cpp), 0x322);
    g_par_draw_prof.Stop();
    pppClearDrawEnv();
}

/*
 * --INFO--
 * PAL Address: 0x80052C78
 * PAL Size: 148b
 * EN Address: 0x800607e8
 * EN Size: 160b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawAfter()
{
    CGame* game = &Game;

    if (game->m_gameWork.m_gamePaused == 0 && m_usbStreamState.m_disableShokiDraw == 0) {
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
 * PAL Address: 0x80052BD4
 * PAL Size: 164b
 * EN Address: 0x80060888
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::DrawMenu(int fpNo)
{
    if (m_usbStreamState.m_disableShokiDraw == 0) {
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
 * PAL Address: 0x80052B10
 * PAL Size: 196b
 * EN Address: 0x80060934
 * EN Size: 208b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::DrawShoki()
{
    CUSBStreamDataState* usb = &m_usbStreamState;

    if (usb->m_disableShokiDraw == 0 && (int)Game.m_currentSceneId == 4) {
        Graphic.SetFog(1, 0);
        if (Game.m_gameWork.m_gamePaused == 0 &&
            static_cast<int>(CameraPcs.m_fullScreenShadowEnabled) != 0) {
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
 * PAL Address: 0x80052A74
 * PAL Size: 156b
 * EN Address: 0x80060a04
 * EN Size: 240b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::DrawMenuIdx(int index)
{
    if (m_usbStreamState.m_disableShokiDraw == 0) {
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
 * PAL Address: 0x80052A48
 * PAL Size: 44b
 * EN Address: 0x80060af4
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::SetParLocIdx(int index, Vec& location)
{
    PartMng.m_pppMng[index].m_position.x = location.x;
    PartMng.m_pppMng[index].m_position.y = location.y;
    PartMng.m_pppMng[index].m_position.z = location.z;
}

/*
 * --INFO--
 * PAL Address: 0x80052A1C
 * PAL Size: 44b
 * EN Address: 0x80060b84
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::GetParLocIdx(int index, Vec& location)
{
    location.x = PartMng.m_pppMng[index].m_position.x;
    location.y = PartMng.m_pppMng[index].m_position.y;
    location.z = PartMng.m_pppMng[index].m_position.z;
}

/*
 * --INFO--
 * PAL Address: 0x80052990
 * PAL Size: 140b
 * EN Address: 0x80060c30
 * EN Size: 292b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::SetParColIdx(int index, pppFVECTOR4& color)
{
	_pppMngSt& pppMngSt = PartMng.m_pppMng[index];
	float one = 1.0f;

	pppMngSt.m_userFloat0 = color.x;
	pppMngSt.m_userFloat1 = color.y;
	pppMngSt.m_scaleFactor = color.z;
	pppMngSt.m_ownerScale = color.w;

	if (one == color.x && one == color.y && one == color.z && one == color.w) {
		PartMng.m_pppMng[index].m_useOwnerScaleSign = 0;
		return;
	}

	PartMng.m_pppMng[index].m_useOwnerScaleSign = 1;
	PartMng.m_pppMng[index].m_nodeScaleInitialized = 1;
}

extern "C" {
const char sNoNameProfileLabel[] = "no name";
}

/*
 * --INFO--
 * PAL Address: 0x8005295C
 * PAL Size: 52b
 * EN Address: 0x80060d78
 * EN Size: 144b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::GetParColIdx(int index, pppFVECTOR4& color)
{
	color.x = PartMng.m_pppMng[index].m_userFloat0;
	color.y = PartMng.m_pppMng[index].m_userFloat1;
	color.z = PartMng.m_pppMng[index].m_scaleFactor;
	color.w = PartMng.m_pppMng[index].m_ownerScale;
}

/*
 * --INFO--
 * PAL Address: 0x80052764
 * PAL Size: 504b
 * EN Address: 0x80060e08
 * EN Size: 592b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::drawAfterViewer()
{
	Graphic._WaitDrawDone(const_cast<char*>(s_p_tina_cpp), 0x3f1);
	g_par_draw_prof.Start();
	g_par_calc_prof.Start();
	Graphic.SetFog(1, 0);
	pppInitDrawEnv(0);
	PartMng.pppEditPartDrawAfter();
	g_par_calc_prof.Stop();
	Graphic._WaitDrawDone(const_cast<char*>(s_p_tina_cpp), 0x3fb);
	g_par_draw_prof.Stop();
	PartMng.pppGet2Dpos();
	pppClearDrawEnv();

	if (sDebugSpinnerTextPtrInit == 0) {
		sDebugSpinnerTextPtr = sDebugSpinnerText;
		sDebugSpinnerTextPtrInit = 1;
	}
	if (s_debugSpinnerFrameCounterInit == 0) {
		s_debugSpinnerFrameCounter = 0;
		s_debugSpinnerFrameCounterInit = 1;
	}

	s_debugSpinnerFrameCounter++;
	Graphic.Printf(
		const_cast<char*>(sPartPcsTitleFmt), sDebugSpinnerTextPtr[(s_debugSpinnerFrameCounter >> 4) % 4]);

	g_par_calc_prof.ProfEnd();
	g_par_draw_prof.ProfEnd();
	Graphic.Printf(
		const_cast<char*>(sPartPcsCalcProfileFmt),
		(double)g_par_calc_prof.m_lastTime,
		(double)g_par_calc_prof.m_maxTime);
	Graphic.Printf(
		const_cast<char*>(sPartPcsDrawProfileFmt),
		(double)g_par_draw_prof.m_lastTime,
		(double)g_par_draw_prof.m_maxTime);
	Graphic.Printf(
		const_cast<char*>(sPartPcsHeapProfileFmt),
		(double)((float)gPppHeapUseRateWords[0] / kPppHeapUseRateDivisor),
		(double)((float)gPppHeapUseRateWords[1] / kPppHeapUseRateDivisor));
}

/*
 * --INFO--
 * PAL Address: 0x80052660
 * PAL Size: 260b
 * EN Address: 0x80061058
 * EN Size: 40b
 * JP Address: TODO
 * JP Size: TODO
 */
unsigned int CPartPcs::IsLoadPartCompleted()
{
    for (int i = 0; i < 16; i++) {
        if (PartMng.m_partAsyncBusy[i] != 0) {
            return 0;
        }
    }

    return 1;
}

/*
 * --INFO--
 * PAL Address: 0x800524D0
 * PAL Size: 400b
 * EN Address: 0x80061080
 * EN Size: 596b
 * JP Address: TODO
 * JP Size: TODO
 */
static void LoadFieldPdt0(int mapId, int floorId)
{
    int pdtSlot;
    char path[1024];

    g_MaxHeapSize = 0;
    g_MaxDataSize = 0;

    if (PartMng.m_partLoadMode != 3) {
        PartMng.pppReleasePdt(0);
        PartMng.pppReleasePdt(6);
        PartMng.pppReleasePdt(7);
        ppvAmemCacheSet.AmemGetLock();
        ppvAmemCacheSet.RefCnt0Compare();
    }

    PartPcs.m_usbStreamState.m_fieldLoadReq = 1;

    sprintf(path, sFieldPdtPathFmt, mapId, floorId);
    pdtSlot = PartMng.pppLoadPtx(path, 0, 1, 0, 0);
    if (pdtSlot != 0) {
        pdtSlot = PartMng.pppLoadPdt(path, 0, 1, 0, 0);
        if ((pdtSlot != 0) && (PartMng.m_partLoadMode != 2) && (PartMng.m_partLoadMode != 3)) {
            _pppDataHead* pppDataHead;
            PPPCREATEPARAM* createParam;
            int i;

            pppDataHead = PartMng.m_pdtSlots[0].m_pppDataHead;
            createParam = PartMng.pppGetDefaultCreateParam();
            i = 0;
            for (; i < static_cast<int>((unsigned int)pppDataHead->m_partCount); i++) {
                _pppFieldParticleData* fieldParticles = reinterpret_cast<_pppFieldParticleData*>(
                    PartMng.m_pdtSlots[0].m_pppDataHead + 1);
                if (fieldParticles[i].m_autoCreateMarker != kPppFieldParticleNoAutoCreate) {
                    PartMng.pppCreate(0, i, createParam, 0);
                }
            }
        }
    }
}

/*
 * --INFO--
 * PAL Address: 0x800523F8
 * PAL Size: 216b
 * EN Address: 0x800612d4
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::LoadFieldPdt(int mapId, int floorId, void* amemBase, unsigned long loadCacheParam, unsigned char mode)
{
    CPartMng* state = &PartMng;

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
 * PAL Address: 0x800522B0
 * PAL Size: 328b
 * EN Address: 0x800614cc
 * EN Size: 224b
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartPcs::LoadMonsterPdt(int monsterId, int variant, void* pdtData, int pdtCount, void* ptxData, int ptxCount)
{
    int pdtSlotIndex;
    char path[256];

    if (variant == 0) {
        sprintf(path, sMonsterPdtPathFmt, monsterId);
    } else {
        sprintf(path, sMonsterVariantPdtPathFmt, monsterId, variant + 0x61);
    }

    PartMng.m_partAMemBase = 0;
    PartMng.m_partAMemCursor = 0;
    PartMng.m_partLoadCacheParam = 0;
    PartMng.m_partChunkIndex = 0;
    PartMng.m_asyncHandleCount = 0;
    PartMng.m_partLoadMode = 0;

    pdtSlotIndex = PartMng.pppGetFreeDataMng();
    if (pdtSlotIndex == -1) {
        pdtSlotIndex = -1;
    } else {
        if (PartMng.pppLoadPtx(path, pdtSlotIndex, 1, ptxData, ptxCount) == 0) {
            PartMng.pppReleasePdt(pdtSlotIndex);
            pdtSlotIndex = -1;
        } else {
            if (PartMng.pppLoadPdt(path, pdtSlotIndex, 1, pdtData, pdtCount) == 0) {
                PartMng.pppReleasePdt(pdtSlotIndex);
                pdtSlotIndex = -1;
            } else {
                PartPcs.m_usbStreamState.m_printFreeOnNext = 1;
            }
        }
    }

    return pdtSlotIndex;
}

/*
 * --INFO--
 * PAL Address: 0x80052128
 * PAL Size: 392b
 * EN Address: 0x800615ac
 * EN Size: 308b
 * JP Address: TODO
 * JP Size: TODO
 */
int CPartPcs::LoadMenuPdt(char* fileName)
{
    int pdtSlotIndex;
    int loaded;
    CMemory::CStage* stage;
    char path[0x100];

    sprintf(path, sMenuPdtPathFmt, Game.GetLangString(), fileName);

    if (Game.m_gameWork.m_menuStageMode != 0) {
        stage = MenuPcs.m_stageF4;
    } else {
        stage = MenuPcs.m_menuStage;
    }

    m_usbStreamState.m_stageLoad = stage;
    ppvAmemCacheSet.SetRStage(stage);

    PartMng.m_partAMemBase = 0;
    PartMng.m_partAMemCursor = 0;
    PartMng.m_partLoadCacheParam = 0;
    PartMng.m_partChunkIndex = 0;
    PartMng.m_asyncHandleCount = 0;
    PartMng.m_partLoadMode = 0;

    pdtSlotIndex = PartMng.pppGetFreeDataMng();
    if (pdtSlotIndex == -1) {
        pdtSlotIndex = -1;
    } else {
        loaded = PartMng.pppLoadPtx(path, pdtSlotIndex, 0, 0, 0);
        if (loaded == 0) {
            PartMng.pppReleasePdt(pdtSlotIndex);
            pdtSlotIndex = -1;
        } else {
            loaded = PartMng.pppLoadPdt(path, pdtSlotIndex, 0, 0, 0);
            if (loaded == 0) {
                PartMng.pppReleasePdt(pdtSlotIndex);
                pdtSlotIndex = -1;
            } else {
                PartPcs.m_usbStreamState.m_printFreeOnNext = 1;
            }
        }
    }

    m_usbStreamState.m_stageLoad = m_usbStreamState.m_stageDefault;
    ppvAmemCacheSet.SetRStage(m_usbStreamState.m_stageDefault);

    return pdtSlotIndex;
}

/*
 * --INFO--
 * PAL Address: 0x80052100
 * PAL Size: 40b
 * EN Address: 0x800616e0
 * EN Size: 48b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::ReleasePdt(int pdtSlot)
{
    PartMng.pppReleasePdt(pdtSlot);
}

/*
 * --INFO--
 * PAL Address: 0x8005205C
 * PAL Size: 164b
 * EN Address: 0x80061710
 * EN Size: 292b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::StartLocationTitle()
{
    int loaded;
    char path[1024];
    CGame* game = &Game;

    sprintf(path, sLocationTitlePdtPathFmt, game->m_currentMapId);
    loaded = PartMng.pppLoadPtx(path, 6, 0, 0, 0);
    if ((loaded != 0) && ((loaded = PartMng.pppLoadPdt(path, 6, 0, 0, 0), loaded != 0))) {
        m_usbStreamState.m_blockOnFrame = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x8005201C
 * PAL Size: 64b
 * EN Address: 0x80061834
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::EndLocationTitle()
{
    PartMng.pppReleasePdt(6);
    m_usbStreamState.m_blockOnFrame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x80051F78
 * PAL Size: 164b
 * EN Address: 0x80061874
 * EN Size: 292b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::StartMiruraEvent()
{
    int loaded;
    char path[1024];
    CGame* game = &Game;

    sprintf(path, sMiruraPdtPathFmt, game->m_currentMapId);
    loaded = PartMng.pppLoadPtx(path, 7, 0, 0, 0);
    if ((loaded != 0) && ((loaded = PartMng.pppLoadPdt(path, 7, 0, 0, 0), loaded != 0))) {
        m_usbStreamState.m_miruraEventActive = 1;
    }
}

/*
 * --INFO--
 * PAL Address: 0x80051F38
 * PAL Size: 64b
 * EN Address: 0x80061998
 * EN Size: 64b
 * JP Address: TODO
 * JP Size: TODO
 */
void CPartPcs::EndMiruraEvent()
{
    PartMng.pppReleasePdt(7);
    m_usbStreamState.m_miruraEventActive = 0;
}
