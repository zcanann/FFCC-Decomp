#include "ffcc/stopwatch.h"

extern "C" float __cvt_sll_flt(u32 lo, u32 hi);
extern "C" void __dl__FPv(void* ptr);

extern char lbl_8032F860;
extern float lbl_8032F850;
extern float lbl_8032F854;  // 0.0f

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CStopWatch::CStopWatch(char* name)
{
	OSInitStopwatch(this, name);
	OSResetStopwatch(this);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CStopWatch::~CStopWatch() {}

/*
 * --INFO--
 * PAL Address: 0x80021440
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
extern "C" CStopWatch* dtor_80021440(CStopWatch* stopWatch, short shouldDelete)
{
	if ((stopWatch != nullptr) && (shouldDelete > 0))
	{
		__dl__FPv(stopWatch);
	}
	return stopWatch;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CStopWatch::Reset() { OSResetStopwatch(this); }

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CStopWatch::Start() { OSStartStopwatch(this); }

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CStopWatch::Stop() { OSStopStopwatch(this); }

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CStopWatch::Get()
{
	volatile u32* p = (volatile u32*)&this->total;
	u32 lo = p[0];
	u32 hi = p[1];
	float ticks = __cvt_sll_flt(lo, hi);
	u32 scaled = (OS_TIMER_CLOCK / 500000) * 0x8235;
	float denom = (float)(scaled >> 3);
	return lbl_8032F850 * (ticks / denom);
}

/*
 * --INFO--
 * PAL Address: 0x80022FEC
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CProfile::CProfile(char* name)
{
	OSInitStopwatch(this, &lbl_8032F860);
	OSResetStopwatch(this);

	OSStopwatch tmp;
	OSInitStopwatch(&tmp, name);
	OSResetStopwatch(&tmp);

	float time = lbl_8032F854;
	m_maxTime = time;
	m_lastTime = time;
	m_frame = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CProfile::~CProfile() {}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CProfile::ProfStart() { OSResetStopwatch(this); }

/*
 * --INFO--
 * PAL Address: 0x80022ec8
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProfile::ProfEnd()
{
	u32* p = (u32*)&this->total;
	u32 lo = p[0];
	u32 hi = p[1];
	float ticks = __cvt_sll_flt(lo, hi);
	u32 scaled = (OS_TIMER_CLOCK / 500000) * 0x8235;
	float denom = (float)(scaled >> 3);
	m_lastTime = lbl_8032F850 * (ticks / denom);

	int next = m_frame + 1;
	m_frame = next;
	if (next == 0x5A)
	{
		m_maxTime = lbl_8032F854;
		m_frame = 0;
	}

	if (m_maxTime < m_lastTime)
	{
		m_maxTime = m_lastTime;
		m_frame = 0;
	}
}
