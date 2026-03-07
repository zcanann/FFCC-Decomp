#include "ffcc/p_tina.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/p_game.h"
#include "ffcc/p_camera.h"
#include "ffcc/pppPart.h"
#include "ffcc/pppDrawMng.h"
#include "ffcc/stopwatch.h"
#include "ffcc/symbols_shared.h"
#include "ffcc/USBStreamData.h"

extern "C" void* __register_global_object(void* object, void* destructor, void* regmem);
extern "C" CUSBStreamData* __ct__14CUSBStreamDataFv(CUSBStreamData*);
extern "C" CProfile* __ct__8CProfileFPc(CProfile*, char*);
extern "C" CPartPcs* __dt__8CPartPcsFv(CPartPcs*, short);
extern "C" CProfile* __dt__8CProfileFv(CProfile*, short);
extern "C" int sprintf(char*, const char*, ...);
extern "C" void* memset(void*, int, unsigned long);
extern "C" int pppLoadPtx__8CPartMngFPCciiPvi(CPartMng*, const char*, int, int, void*, int);
extern "C" int pppLoadPdt__8CPartMngFPCciiPvi(CPartMng*, const char*, int, int, void*, int);
extern "C" void pppLoadPmd__8CPartMngFPCc(CPartMng*, const char*);
extern "C" void pppLoadPan__8CPartMngFPCc(CPartMng*, const char*);
extern "C" int pppGetFreeDataMng__8CPartMngFv(CPartMng*);
extern "C" char* GetLangString__5CGameFv(void*);
extern "C" void pppReleasePdt__8CPartMngFi(CPartMng*, int);
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

extern unsigned char PartPcs[];
extern unsigned char MenuPcs[];
extern unsigned char USBPcs[];
extern unsigned char ppvDrawMng[];
extern void* CAMemCacheSet;

extern char DAT_801ead4c[];
extern char s_prioTime__d_prio__d_pdtID__2d_fp_801d81a0[];
extern char DAT_801d81d4[];
extern char s_CPartPcs_801d7f54[];
extern char s_CPartPcs_dat_801d810c[];
extern char s_CPartPcs_amem_801d811c[];
extern char s_dvd_tina_chobit_801d812c[];
extern char s_dvd_tina_chobit_0_801d813c[];
extern char s_dvd_tina_chobit_1_801d8150[];
extern char s_dvd_tina_chobit_2_801d8164[];
extern char s_dvd_tina_chobit_3_801d8178[];
extern char s_dvd_tina_chobit_4_801d818c[];
extern char s_p_tina_cpp_801d8008[];
extern char s_Tina___c__801d8014[];
extern char s_clc___3f___max___3f___801d8020[];
extern char s_drw___3f___max___3f___801d8038[];
extern char s_hpm___3f___max___3f___801d8050[];
extern CProfile g_par_calc_prof;
extern CProfile g_par_draw_prof;
extern char DAT_801d8068[];
extern char s_no_name_8032fdcc[];
extern char s_dvd_tina_stage_03d_mirura_801d7f78[];
extern char s_dvd_tina_stage_03d_title_801d7f94[];
extern char s_dvd_tina_stage_03d_fp_03d_801d7fec[];
extern char s_dvd__smenu__s_801d7fb0[];
extern char s_dvd_tina_mon_m_03d_801d7fc0[];
extern char s_dvd_tina_mon_m_03d__c_801d7fd4[];
extern unsigned char ARRAY_80273928[];
extern unsigned char ARRAY_80273968[];
extern unsigned char ARRAY_802739e8[];
extern void* PTR_PTR_s_CPartPcs_801eada4;
extern unsigned int DAT_801ea9b0;
extern unsigned int DAT_801ea9b4;
extern unsigned int PTR_create__8CPartPcsFv_801ea9b8;
extern unsigned int DAT_801ea9bc;
extern unsigned int DAT_801ea9c0;
extern unsigned int PTR_destroy__8CPartPcsFv_801ea9c4;
extern unsigned int DAT_801ea9c8;
extern unsigned int DAT_801ea9cc;
extern unsigned int PTR_calcInit__8CPartPcsFv_801ea9d0;
extern unsigned int DAT_801ea9d4;
extern unsigned int DAT_801ea9d8;
extern unsigned int PTR_calc__8CPartPcsFv_801ea9dc;
extern unsigned int DAT_801ea9e0;
extern unsigned int DAT_801ea9e4;
extern unsigned int PTR_calcDead__8CPartPcsFv_801ea9e8;
extern unsigned int DAT_801ea9ec;
extern unsigned int DAT_801ea9f0;
extern unsigned int PTR_ClearOt__8CPartPcsFv_801ea9f4;
extern unsigned int DAT_801ea9f8;
extern unsigned int DAT_801ea9fc;
extern unsigned int PTR_drawShadow__8CPartPcsFv_801eaa00;
extern unsigned int DAT_801eaa04;
extern unsigned int DAT_801eaa08;
extern unsigned int DAT_801eaa10;
extern unsigned int DAT_801eaa14;
extern unsigned int PTR_drawCharaBefore__8CPartPcsFv_801eaa0c;
extern unsigned int PTR_draw__8CPartPcsFv_801eaa18;
extern unsigned int DAT_801eaa1c;
extern unsigned int DAT_801eaa20;
extern unsigned int PTR_drawAfter__8CPartPcsFv_801eaa24;
extern unsigned int DAT_801eaa28;
extern unsigned int DAT_801eaa2c;
extern unsigned int PTR_createViewer__8CPartPcsFv_801eaa30;
extern unsigned int DAT_801eaa34;
extern unsigned int DAT_801eaa38;
extern unsigned int PTR_destroy__8CPartPcsFv_801eaa3c;
extern unsigned int DAT_801eaa40;
extern unsigned int DAT_801eaa44;
extern unsigned int PTR_calcInit__8CPartPcsFv_801eaa48;
extern unsigned int DAT_801eaa4c;
extern unsigned int DAT_801eaa50;
extern unsigned int PTR_calcViewer__8CPartPcsFv_801eaa54;
extern unsigned int DAT_801eaa58;
extern unsigned int DAT_801eaa5c;
extern unsigned int PTR_calcDead__8CPartPcsFv_801eaa60;
extern unsigned int DAT_801eaa64;
extern unsigned int DAT_801eaa68;
extern unsigned int PTR_ClearOt__8CPartPcsFv_801eaa6c;
extern unsigned int DAT_801eaa70;
extern unsigned int DAT_801eaa74;
extern unsigned int PTR_drawShadowViewer__8CPartPcsFv_801eaa78;
extern unsigned int DAT_801eaa7c;
extern unsigned int DAT_801eaa80;
extern unsigned int PTR_drawViewer__8CPartPcsFv_801eaa84;
extern unsigned int DAT_801eaa88;
extern unsigned int DAT_801eaa8c;
extern unsigned int PTR_drawAfterViewer__8CPartPcsFv_801eaa90;
extern unsigned int DAT_801eaa98;
extern unsigned char PTR_s_CPartPcs_GAME__801eaa94[];
extern unsigned int DAT_801eaa9c;
extern unsigned int DAT_801eaaa0;
extern unsigned int DAT_801eaaa4;
extern unsigned int DAT_801eaaa8;
extern unsigned int DAT_801eaaac;
extern unsigned int DAT_801eaab0;
extern unsigned int DAT_801eaab4;
extern unsigned int DAT_801eaab8;
extern unsigned int DAT_801eaac4;
extern unsigned int DAT_801eaac8;
extern unsigned int DAT_801eaacc;
extern unsigned int DAT_801eaad8;
extern unsigned int DAT_801eaadc;
extern unsigned int DAT_801eaae0;
extern unsigned int DAT_801eaaec;
extern unsigned int DAT_801eaaf0;
extern unsigned int DAT_801eaaf4;
extern unsigned int DAT_801eab00;
extern unsigned int DAT_801eab04;
extern unsigned int DAT_801eab08;
extern unsigned int DAT_801eab14;
extern unsigned int DAT_801eab18;
extern unsigned int DAT_801eab1c;
extern unsigned int DAT_801eab28;
extern unsigned int DAT_801eab2c;
extern unsigned int DAT_801eab30;
extern unsigned int DAT_801eab3c;
extern unsigned int DAT_801eab40;
extern unsigned int DAT_801eab44;
extern unsigned int DAT_801eabf4;
extern unsigned int DAT_801eabf8;
extern unsigned int DAT_801eabfc;
extern unsigned int DAT_801eac00;
extern unsigned int DAT_801eac04;
extern unsigned int DAT_801eac08;
extern unsigned int DAT_801eac0c;
extern unsigned int DAT_801eac10;
extern unsigned int DAT_801eac14;
extern unsigned int DAT_801eac20;
extern unsigned int DAT_801eac24;
extern unsigned int DAT_801eac28;
extern unsigned int DAT_801eac34;
extern unsigned int DAT_801eac38;
extern unsigned int DAT_801eac3c;
extern unsigned int DAT_801eac48;
extern unsigned int DAT_801eac4c;
extern unsigned int DAT_801eac50;
extern unsigned int DAT_801eac5c;
extern unsigned int DAT_801eac60;
extern unsigned int DAT_801eac64;
extern unsigned int DAT_801eac70;
extern unsigned int DAT_801eac74;
extern unsigned int DAT_801eac78;
extern unsigned int DAT_801eac84;
extern unsigned int DAT_801eac88;
extern unsigned int DAT_801eac8c;
extern int DAT_8032ed38;
extern int DAT_8032ed3c;

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

/*
 * --INFO--
 * PAL Address: 0x80053960
 * PAL Size: 832b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" void __sinit_p_tina_cpp(void)
{
    void* object;

    *reinterpret_cast<void**>(PartPcs) = &PTR_PTR_s_CPartPcs_801eada4;
    __ct__14CUSBStreamDataFv(reinterpret_cast<CUSBStreamData*>(PartPcs + 0x8));
    __register_global_object(PartPcs, reinterpret_cast<void*>(__dt__8CPartPcsFv), ARRAY_80273928);

    DAT_801eab18 = DAT_801eaa08;
    DAT_801eab28 = DAT_801eaa10;
    DAT_801eab2c = DAT_801eaa14;
    DAT_801eaa98 = DAT_801ea9b0;
    DAT_801eaa9c = DAT_801ea9b4;
    DAT_801eaaa0 = PTR_create__8CPartPcsFv_801ea9b8;
    DAT_801eaaa4 = DAT_801ea9bc;
    DAT_801eaaa8 = DAT_801ea9c0;
    DAT_801eaaac = PTR_destroy__8CPartPcsFv_801ea9c4;
    DAT_801eaab0 = DAT_801ea9c8;
    DAT_801eaab4 = DAT_801ea9cc;
    DAT_801eaab8 = PTR_calcInit__8CPartPcsFv_801ea9d0;
    DAT_801eaac4 = DAT_801ea9d4;
    DAT_801eaac8 = DAT_801ea9d8;
    DAT_801eaacc = PTR_calc__8CPartPcsFv_801ea9dc;
    DAT_801eaad8 = DAT_801ea9e0;
    DAT_801eaadc = DAT_801ea9e4;
    DAT_801eaae0 = PTR_calcDead__8CPartPcsFv_801ea9e8;
    DAT_801eaaec = DAT_801ea9ec;
    DAT_801eaaf0 = DAT_801ea9f0;
    DAT_801eaaf4 = PTR_ClearOt__8CPartPcsFv_801ea9f4;
    DAT_801eab00 = DAT_801ea9f8;
    DAT_801eab04 = DAT_801ea9fc;
    DAT_801eab08 = PTR_drawShadow__8CPartPcsFv_801eaa00;
    DAT_801eab14 = DAT_801eaa04;
    DAT_801eab1c = PTR_drawCharaBefore__8CPartPcsFv_801eaa0c;
    DAT_801eab30 = PTR_draw__8CPartPcsFv_801eaa18;
    DAT_801eab3c = DAT_801eaa1c;
    DAT_801eab40 = DAT_801eaa20;
    DAT_801eab44 = PTR_drawAfter__8CPartPcsFv_801eaa24;
    DAT_801eac70 = DAT_801eaa7c;
    DAT_801eac74 = DAT_801eaa80;
    DAT_801eabf4 = DAT_801eaa28;
    DAT_801eabf8 = DAT_801eaa2c;
    DAT_801eabfc = PTR_createViewer__8CPartPcsFv_801eaa30;
    DAT_801eac00 = DAT_801eaa34;
    DAT_801eac04 = DAT_801eaa38;
    DAT_801eac08 = PTR_destroy__8CPartPcsFv_801eaa3c;
    DAT_801eac0c = DAT_801eaa40;
    DAT_801eac10 = DAT_801eaa44;
    DAT_801eac14 = PTR_calcInit__8CPartPcsFv_801eaa48;
    DAT_801eac20 = DAT_801eaa4c;
    DAT_801eac24 = DAT_801eaa50;
    DAT_801eac28 = PTR_calcViewer__8CPartPcsFv_801eaa54;
    DAT_801eac34 = DAT_801eaa58;
    DAT_801eac38 = DAT_801eaa5c;
    DAT_801eac3c = PTR_calcDead__8CPartPcsFv_801eaa60;
    DAT_801eac48 = DAT_801eaa64;
    DAT_801eac4c = DAT_801eaa68;
    DAT_801eac50 = PTR_ClearOt__8CPartPcsFv_801eaa6c;
    DAT_801eac5c = DAT_801eaa70;
    DAT_801eac60 = DAT_801eaa74;
    DAT_801eac64 = PTR_drawShadowViewer__8CPartPcsFv_801eaa78;
    DAT_801eac78 = PTR_drawViewer__8CPartPcsFv_801eaa84;
    DAT_801eac84 = DAT_801eaa88;
    DAT_801eac88 = DAT_801eaa8c;
    DAT_801eac8c = PTR_drawAfterViewer__8CPartPcsFv_801eaa90;

    object = __ct__8CProfileFPc(&g_par_calc_prof, s_no_name_8032fdcc);
    __register_global_object(object, reinterpret_cast<void*>(__dt__8CProfileFv), ARRAY_80273968);
    object = __ct__8CProfileFPc(&g_par_draw_prof, s_no_name_8032fdcc);
    __register_global_object(object, reinterpret_cast<void*>(__dt__8CProfileFv), ARRAY_802739e8);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CPartPcs::CPartPcs()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CPartPcs::~CPartPcs()
{
    reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 4)->~CUSBStreamData();
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
void* CPartPcs::GetTable(unsigned long index)
{
	unsigned long offset = index * 0x15c;
	return PTR_s_CPartPcs_GAME__801eaa94 + offset;
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
	_pppMngSt* pppMngSt;
	_pppMngSt* pppMngStBase;
	unsigned int prioTime = 0;
	unsigned char bestPrio = 1;
	int index = 0;
	int i = 0xc0;

	pppMngSt = 0;
	pppMngStBase = reinterpret_cast<_pppMngSt*>(&PartMng);
	do {
		_pppMngSt* current = pppMngStBase;
		if (current != pppMngStPtr && GetMngStBaseTime(current) != -0x1000 &&
			GetMngStKind(current) != 0) {
			unsigned char prio = GetMngStPrio(current);
			if (1 < prio) {
				if (bestPrio < prio) {
					prioTime = (unsigned int)GetMngStPrioTime(current);
					pppMngSt = current;
					bestPrio = prio;
				} else if (bestPrio == prio &&
					(int)prioTime < (int)(unsigned int)GetMngStPrioTime(current)) {
					prioTime = (unsigned int)GetMngStPrioTime(current);
					pppMngSt = current;
				}
			}
		}

		current = pppMngStBase + 1;
		if (current != pppMngStPtr && GetMngStBaseTime(current) != -0x1000 &&
			GetMngStKind(current) != 0) {
			unsigned char prio = GetMngStPrio(current);
			if (1 < prio) {
				if (bestPrio < prio) {
					prioTime = (unsigned int)GetMngStPrioTime(current);
					pppMngSt = current;
					bestPrio = prio;
				} else if (bestPrio == prio &&
					(int)prioTime < (int)(unsigned int)GetMngStPrioTime(current)) {
					prioTime = (unsigned int)GetMngStPrioTime(current);
					pppMngSt = current;
				}
			}
		}

		pppMngStBase += 2;
		index++;
		i--;
	} while (i != 0);

	if (pppMngSt == 0) {
		return 0;
	}

	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(DAT_801ead4c, index);
	}
	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(
			s_prioTime__d_prio__d_pdtID__2d_fp_801d81a0,
			(unsigned int)GetMngStPrioTime(pppMngSt),
			(unsigned int)GetMngStPrio(pppMngSt),
			(int)GetMngStKind(pppMngSt),
			(int)GetMngStNodeIndex(pppMngSt),
			(int)GetMngStKind(pppMngSt) * 0x38 + -0x7fd672e8);
	}
	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(DAT_801d81d4);
	}
	if (2 < (unsigned int)System.m_execParam) {
		System.Printf(DAT_801ead4c);
	}

	Graphic._WaitDrawDone(s_p_tina_cpp_801d8008, 0xfc);
	_pppAllFreePObject(pppMngSt);
	return 1;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
unsigned int pppAmemDeletePmng(unsigned long)
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);
    void* stage;

    usb->m_freePtr = 0;
    usb->m_stageExtra = 0;
    usb->m_blockOnFrame = 0;
    usb->m_miruraEventActive = 0;
    usb->m_disableShokiDraw = 0;

    stage = CreateStage__7CMemoryFUlPci(&Memory, 0x180000, s_CPartPcs_dat_801d810c, 0);
    usb->m_stageLoad = stage;
    usb->m_stageDefault = stage;

    if (Game.game.m_currentSceneId == 7) {
        usb->m_stageAmem = 0;
    } else {
        usb->m_stageAmem = CreateStage__7CMemoryFUlPci(&Memory, 0x400000, s_CPartPcs_amem_801d811c, 2);
    }

    Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl(
        CAMemCacheSet,
        s_CPartPcs_801d7f54,
        reinterpret_cast<CUSBStreamDataRaw*>(PartPcs + 8)->m_stageLoad,
        reinterpret_cast<CUSBStreamDataRaw*>(PartPcs + 8)->m_stageAmem,
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
    unsigned char* partMng = reinterpret_cast<unsigned char*>(&PartMng);

    *reinterpret_cast<unsigned int*>(partMng + 0x236F4) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x236F8) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x236FC) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23700) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23704) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23708) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x2370C) = 0;

    pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, s_dvd_tina_chobit_801d812c, 1, 1, 0, 0);
    pppLoadPmd__8CPartMngFPCc(&PartMng, s_dvd_tina_chobit_801d812c);
    pppLoadPan__8CPartMngFPCc(&PartMng, s_dvd_tina_chobit_801d812c);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, s_dvd_tina_chobit_0_801d813c, 1, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, s_dvd_tina_chobit_1_801d8150, 2, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, s_dvd_tina_chobit_2_801d8164, 3, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, s_dvd_tina_chobit_3_801d8178, 4, 1, 0, 0);
    pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, s_dvd_tina_chobit_4_801d818c, 5, 1, 0, 0);
    AmemSetLock__13CAmemCacheSetFv(CAMemCacheSet);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::createViewer()
{
    void* stage;
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    IsBigAlloc__7CUSBPcsFi(USBPcs, 1);
    usb->m_freePtr = 0;
    usb->m_stageExtra = 0;
    usb->m_blockOnFrame = 0;
    usb->m_miruraEventActive = 0;
    usb->m_disableShokiDraw = 0;

    if (Game.game.m_currentSceneId == 7) {
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x180000, s_CPartPcs_dat_801d810c, 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        usb->m_stageAmem = 0;
    } else {
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x180000, s_CPartPcs_dat_801d810c, 0);
        usb->m_stageLoad = stage;
        usb->m_stageDefault = stage;
        stage = CreateStage__7CMemoryFUlPci(&Memory, 0x400000, s_CPartPcs_amem_801d811c, 2);
        usb->m_stageAmem = stage;
    }

    Init__13CAmemCacheSetFPcPQ27CMemory6CStagePQ27CMemory6CStageiPFUl_UcUlPFUl_UcUlPFUl_UcUl(
        CAMemCacheSet,
        s_CPartPcs_801d7f54,
        usb->m_stageLoad,
        usb->m_stageAmem,
        0x400,
        reinterpret_cast<void*>(pppNotAllocAmemCacheRmem),
        0,
        reinterpret_cast<void*>(pppAmemDeletePmng),
        0,
        reinterpret_cast<void*>(pppAmemRefCntError),
        0);

    memset(&PartMng, 0, 0x23FD8);
    PartMng.Create();
    reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 8)->CreateBuffer();
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    IsBigAlloc__7CUSBPcsFi(USBPcs, 0);
    Destroy__8CPartMngFv(&PartMng);

    if (usb->m_stageAmem != 0) {
        DestroyStage__7CMemoryFPQ27CMemory6CStage(&Memory, usb->m_stageAmem);
    }

    AssertCache__13CAmemCacheSetFv(CAMemCacheSet);
    Destroy__13CAmemCacheSetFv(CAMemCacheSet);

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
	if (Game.game.m_currentSceneId == 7) {
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
	CUSBStreamData* usbStream = reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 8);

	PartMng.pppPartCalc();
	if (usbStream->m_printFreeOnNext != 0) {
		unsigned int freeSize;

		usbStream->m_printFreeOnNext = 0;
		freeSize = reinterpret_cast<CAmemCacheSet*>(CAMemCacheSet)->AmemGetFreeSize();
		System.Printf(
			DAT_801d8068, ((int)freeSize >> 10) + (unsigned int)((int)freeSize < 0 && (freeSize & 0x3ff) != 0));
	}
	reinterpret_cast<CAmemCacheSet*>(CAMemCacheSet)->CalcPrio();
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
    CUSBStreamData* usbStream = reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 8);

    OSStartStopwatch(&g_par_calc_prof);
    PartMng.pppEditBeforeCalc();
    PartMng.pppEditPartCalc();
    OSStopStopwatch(&g_par_calc_prof);

    mccReadData__7CUSBPcsFv(USBPcs);
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
    reinterpret_cast<pppDrawMng*>(ppvDrawMng)->ClearOt();
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    if (Game.game.m_gameWork.m_gamePaused == 0 && usb->m_disableShokiDraw == 0 &&
        *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&CameraPcs) + 0x1028) != 0) {
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    if (Game.game.m_gameWork.m_gamePaused == 0 && usb->m_disableShokiDraw == 0) {
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    SetDrawDoneDebugDataPartControl__8CGraphicFi(&Graphic, 0x7fff);
    if (Game.game.m_gameWork.m_gamePaused != 0) {
        DrawOt__10pppDrawMngFv(ppvDrawMng);
        SetDrawDoneDebugData__8CGraphicFSc(&Graphic, 0x7f);
        return;
    }

    if (usb->m_disableShokiDraw != 0) {
        DrawOt__10pppDrawMngFv(ppvDrawMng);
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
    Graphic._WaitDrawDone(s_p_tina_cpp_801d8008, 0x308);
    OSStartStopwatch(&g_par_draw_prof);
    OSStartStopwatch(&g_par_calc_prof);
    pppSetProjection();
    pppInitDrawEnv(0);
    PartMng.pppEditDrawShadow();
    OSStopStopwatch(&g_par_calc_prof);
    Graphic._WaitDrawDone(s_p_tina_cpp_801d8008, 0x30f);
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
    Graphic._WaitDrawDone(s_p_tina_cpp_801d8008, 0x31a);
    OSStartStopwatch(&g_par_draw_prof);
    OSStartStopwatch(&g_par_calc_prof);
    pppSetProjection();
    pppInitDrawEnv(0);
    PartMng.pppEditDraw();
    OSStopStopwatch(&g_par_calc_prof);
    Graphic._WaitDrawDone(s_p_tina_cpp_801d8008, 0x322);
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    if (Game.game.m_gameWork.m_gamePaused == 0 && usb->m_disableShokiDraw == 0) {
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    if (usb->m_disableShokiDraw == 0) {
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    if (usb->m_disableShokiDraw == 0 && Game.game.m_currentSceneId == 4) {
        Graphic.SetFog(1, 0);
        if (Game.game.m_gameWork.m_gamePaused == 0 &&
            *reinterpret_cast<unsigned char*>(reinterpret_cast<char*>(&CameraPcs) + 0x1028) != 0) {
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
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);

    if (usb->m_disableShokiDraw == 0) {
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
	_pppMngSt* pppMngSt = reinterpret_cast<_pppMngSt*>(&PartMng) + index;
	float* colorValues = reinterpret_cast<float*>(&color);

	colorValues[0] = GetMngStUserFloat0(pppMngSt);
	colorValues[1] = GetMngStUserFloat1(pppMngSt);
	colorValues[2] = GetMngStScaleFactor(pppMngSt);
	colorValues[3] = GetMngStOwnerScale(pppMngSt);
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

	Graphic._WaitDrawDone(s_p_tina_cpp_801d8008, 0x3f1);
	OSStartStopwatch(&g_par_draw_prof);
	OSStartStopwatch(&g_par_calc_prof);
	Graphic.SetFog(1, 0);
	pppInitDrawEnv(0);
	PartMng.pppEditPartDrawAfter();
	OSStopStopwatch(&g_par_calc_prof);
	Graphic._WaitDrawDone(s_p_tina_cpp_801d8008, 0x3fb);
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
		s_Tina___c__801d8014,
		(int)(char)gDebugSpinnerText[(frameSign * 4 |
								 (unsigned int)((gDebugSpinnerFrame >> 4) * 0x40000000 + frameSign) >> 0x1e) -
								frameSign]);

	g_par_calc_prof.ProfEnd();
	g_par_draw_prof.ProfEnd();
	Graphic.Printf(
		s_clc___3f___max___3f___801d8020, (double)g_par_calc_prof.m_lastTime, (double)g_par_calc_prof.m_maxTime);
	Graphic.Printf(
		s_drw___3f___max___3f___801d8038, (double)g_par_draw_prof.m_lastTime, (double)g_par_draw_prof.m_maxTime);
	Graphic.Printf(
		s_hpm___3f___max___3f___801d8050,
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
    unsigned char* busy = reinterpret_cast<unsigned char*>(&PartMng) + 0x236F4;
    int count = 2;

    do {
        if (busy[0] != 0) return 0;
        if (busy[1] != 0) return 0;
        if (busy[2] != 0) return 0;
        if (busy[3] != 0) return 0;
        if (busy[4] != 0) return 0;
        if (busy[5] != 0) return 0;
        if (busy[6] != 0) return 0;
        if (busy[7] != 0) return 0;

        busy += 8;
        count--;
    } while (count != 0);

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
    unsigned char* partMng = reinterpret_cast<unsigned char*>(&PartMng);
    int partLoadMode = *reinterpret_cast<int*>(partMng + 0x236FC);
    int pdtSlot;
    char path[1024];

    DAT_8032ed3c = 0;
    DAT_8032ed38 = 0;

    if (partLoadMode != 3) {
        pppReleasePdt__8CPartMngFi(&PartMng, 0);
        pppReleasePdt__8CPartMngFi(&PartMng, 6);
        pppReleasePdt__8CPartMngFi(&PartMng, 7);
        reinterpret_cast<CAmemCacheSet*>(CAMemCacheSet)->AmemGetLock();
        reinterpret_cast<CAmemCacheSet*>(CAMemCacheSet)->RefCnt0Compare();
    }

    reinterpret_cast<CUSBStreamDataRaw*>(PartPcs + 8)->m_fieldLoadReq = 1;

    sprintf(path, s_dvd_tina_stage_03d_fp_03d_801d7fec, mapId, floorId);
    pdtSlot = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, 0, 1, 0, 0);
    if (pdtSlot != 0) {
        pdtSlot = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, 0, 1, 0, 0);
        if ((pdtSlot != 0) && (partLoadMode != 2) && (partLoadMode != 3)) {
            PartMng.pppGetDefaultCreateParam();
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
    unsigned char* partMng = reinterpret_cast<unsigned char*>(&PartMng);

    *reinterpret_cast<unsigned int*>(partMng + 0x236F4) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23700) = 0;

    if (loadCacheParam == 0) {
        *reinterpret_cast<int*>(partMng + 0x236FC) = 0;
    } else if (mode == 1) {
        *reinterpret_cast<int*>(partMng + 0x236FC) = 2;
    } else if (mode == 2) {
        *reinterpret_cast<int*>(partMng + 0x236FC) = 3;
        for (int i = 0; i < 0x10; i++) {
            *reinterpret_cast<int*>(partMng + 0x2370C + (i * 4)) = 0;
        }
    } else {
        *reinterpret_cast<int*>(partMng + 0x236FC) = 1;
    }

    *reinterpret_cast<void**>(partMng + 0x236E8) = amemBase;
    *reinterpret_cast<void**>(partMng + 0x236EC) = amemBase;
    *reinterpret_cast<unsigned long*>(partMng + 0x23704) = loadCacheParam;
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
void CPartPcs::LoadMonsterPdt(int monsterId, int variant, void* pdtData, int pdtCount, void* ptxData, int ptxCount)
{
    int pdtSlotIndex;
    char path[260];
    unsigned char* partMng = reinterpret_cast<unsigned char*>(&PartMng);

    if (variant == 0) {
        sprintf(path, s_dvd_tina_mon_m_03d_801d7fc0, monsterId);
    } else {
        sprintf(path, s_dvd_tina_mon_m_03d__c_801d7fd4, monsterId, variant + 0x61);
    }

    *reinterpret_cast<unsigned int*>(partMng + 0x236F4) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x236F8) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x236FC) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23700) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23704) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23708) = 0;

    pdtSlotIndex = pppGetFreeDataMng__8CPartMngFv(&PartMng);
    if (pdtSlotIndex != -1) {
        if (pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, pdtSlotIndex, 1, ptxData, ptxCount) == 0) {
            pppReleasePdt__8CPartMngFi(&PartMng, pdtSlotIndex);
            pdtSlotIndex = -1;
        } else if (pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, pdtSlotIndex, 1, pdtData, pdtCount) == 0) {
            pppReleasePdt__8CPartMngFi(&PartMng, pdtSlotIndex);
            pdtSlotIndex = -1;
        } else {
            PartPcs[0x2d] = 1;
        }
    }
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
    int pdtSlotIndex;
    char* language;
    int loaded;
    void* stage;
    char path[256];
    CUSBStreamDataRaw* usb = reinterpret_cast<CUSBStreamDataRaw*>(reinterpret_cast<char*>(this) + 8);
    unsigned char* partMng = reinterpret_cast<unsigned char*>(&PartMng);

    language = GetLangString__5CGameFv(&Game.game);
    sprintf(path, s_dvd__smenu__s_801d7fb0, language, fileName);

    stage = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0xEC);
    if (Game.game.m_gameWork.m_menuStageMode != 0) {
        stage = *reinterpret_cast<void**>(reinterpret_cast<unsigned char*>(&MenuPcs) + 0xF4);
    }

    usb->m_stageLoad = stage;
    SetRStage__13CAmemCacheSetFPQ27CMemory6CStage(CAMemCacheSet, stage);

    *reinterpret_cast<unsigned int*>(partMng + 0x236F4) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x236F8) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x236FC) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23700) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23704) = 0;
    *reinterpret_cast<unsigned int*>(partMng + 0x23708) = 0;

    pdtSlotIndex = pppGetFreeDataMng__8CPartMngFv(&PartMng);
    if (pdtSlotIndex != -1) {
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
                PartPcs[0x2d] = 1;
            }
        }
    }

    usb->m_stageLoad = usb->m_stageDefault;
    SetRStage__13CAmemCacheSetFPQ27CMemory6CStage(CAMemCacheSet, usb->m_stageDefault);

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
    char path[1028];
    CUSBStreamData* usb = reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 0x10);

    sprintf(path, s_dvd_tina_stage_03d_title_801d7f94, Game.game.m_currentMapId);
    loaded = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, 6, 0, 0, 0);
    if ((loaded != 0) && ((loaded = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, 6, 0, 0, 0), loaded != 0))) {
        usb->m_blockOnFrame = 1;
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
    CUSBStreamData* usb = reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 0x10);

    pppReleasePdt__8CPartMngFi(&PartMng, 6);
    usb->m_blockOnFrame = 0;
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
    char path[1028];
    CUSBStreamData* usb = reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 0x10);

    sprintf(path, s_dvd_tina_stage_03d_mirura_801d7f78, Game.game.m_currentMapId);
    loaded = pppLoadPtx__8CPartMngFPCciiPvi(&PartMng, path, 7, 0, 0, 0);
    if ((loaded != 0) && ((loaded = pppLoadPdt__8CPartMngFPCciiPvi(&PartMng, path, 7, 0, 0, 0), loaded != 0))) {
        usb->m_miruraEventActive = 1;
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
    CUSBStreamData* usb = reinterpret_cast<CUSBStreamData*>(reinterpret_cast<char*>(this) + 0x10);

    pppReleasePdt__8CPartMngFi(&PartMng, 7);
    usb->m_miruraEventActive = 0;
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
