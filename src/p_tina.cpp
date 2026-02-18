#include "ffcc/p_tina.h"
#include "ffcc/graphic.h"
#include "ffcc/partMng.h"
#include "ffcc/pppPart.h"
#include "ffcc/stopwatch.h"

extern CPartMng PartMng;

extern char DAT_801ead4c[];
extern char s_prioTime__d_prio__d_pdtID__2d_fp_801d81a0[];
extern char DAT_801d81d4[];
extern char s_p_tina_cpp_801d8008[];
extern char s_Tina___c__801d8014[];
extern char s_clc___3f___max___3f___801d8020[];
extern char s_drw___3f___max___3f___801d8038[];
extern char s_hpm___3f___max___3f___801d8050[];
extern int lbl_801EAE08[3];
extern char* lbl_8032ED40;
extern unsigned char lbl_8032ED44;
extern int lbl_8032ED48;
extern unsigned char lbl_8032ED4C;
extern char lbl_8032FDB0[];
extern float lbl_8032FDB8;
extern double lbl_8032FDC0;
extern CProfile g_par_calc_prof;
extern CProfile g_par_draw_prof;

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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::Init()
{
	// TODO
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
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::GetTable(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppNotAllocAmemCacheRmem(unsigned long)
{
	// TODO
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
void pppAmemDeletePmng(unsigned long)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppAmemRefCntError(unsigned long)
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::create()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::createLoad()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::createViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::destroy()
{
	// TODO
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
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::calcInit()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::calcViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::calcDead()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::ClearOt()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::drawShadow()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::drawCharaBefore()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::drawShadowViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::drawViewer()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::drawAfter()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::DrawMenu(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::DrawShoki()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::DrawMenuIdx(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::SetParLocIdx(int, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::GetParLocIdx(int, Vec&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::SetParColIdx(int, pppFVECTOR4&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::GetParColIdx(int, pppFVECTOR4&)
{
	// TODO
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

	if (lbl_8032ED44 == 0) {
		lbl_8032ED40 = lbl_8032FDB0;
		lbl_8032ED44 = 1;
	}
	if (lbl_8032ED4C == 0) {
		lbl_8032ED48 = 0;
		lbl_8032ED4C = 1;
	}

	lbl_8032ED48++;
	frameSign = lbl_8032ED48 >> 0x1f;
	Graphic.Printf(
		s_Tina___c__801d8014,
		(int)(char)lbl_8032ED40[(frameSign * 4 |
								 (unsigned int)((lbl_8032ED48 >> 4) * 0x40000000 + frameSign) >> 0x1e) -
								frameSign]);

	g_par_calc_prof.ProfEnd();
	g_par_draw_prof.ProfEnd();
	Graphic.Printf(
		s_clc___3f___max___3f___801d8020, (double)g_par_calc_prof.m_lastTime, (double)g_par_calc_prof.m_maxTime);
	Graphic.Printf(
		s_drw___3f___max___3f___801d8038, (double)g_par_draw_prof.m_lastTime, (double)g_par_draw_prof.m_maxTime);
	Graphic.Printf(
		s_hpm___3f___max___3f___801d8050,
		(double)((float)lbl_801EAE08[0] / lbl_8032FDB8),
		(double)((float)lbl_801EAE08[1] / lbl_8032FDB8));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::IsLoadPartCompleted()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void LoadFieldPdt0(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::LoadFieldPdt(int, int, void*, unsigned long, unsigned char)
{
	// TODO
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
void CPartPcs::LoadMonsterPdt(int, int, void*, int, void*, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::LoadMenuPdt(char*)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::ReleasePdt(int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::StartLocationTitle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::EndLocationTitle()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::StartMiruraEvent()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CPartPcs::EndMiruraEvent()
{
	// TODO
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
