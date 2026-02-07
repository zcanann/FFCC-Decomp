#include "ffcc/stopwatch.h"

extern "C" float __cvt_sll_flt(u32 lo, u32 hi);

extern char lbl_8032F860[]; // small-data string used by target
extern float lbl_8032F850;  // 8.0f
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
	double ticks = (double)__cvt_sll_flt(*(u32*)&this->total, *((u32*)&this->total + 1));
	return lbl_8032F850 *
	       (float)(ticks / (double)(float)(((OS_TIMER_CLOCK / 500000) * 0x8235) >> 3));
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CProfile::CProfile(char* name)
{
	OSInitStopwatch(this, lbl_8032F860);
	OSResetStopwatch(this);

	OSStopwatch tmp;
	OSInitStopwatch(&tmp, name);
	OSResetStopwatch(&tmp);

	m_maxTime = lbl_8032F854;
	m_lastTime = lbl_8032F854;
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
 * Address:	TODO
 * Size:	TODO
 */
void CProfile::ProfEnd()
{
	double ticks = (double)__cvt_sll_flt(*(u32*)&this->total, *((u32*)&this->total + 1));
	m_lastTime = lbl_8032F850 *
	             (float)(ticks / (double)(float)(((OS_TIMER_CLOCK / 500000) * 0x8235) >> 3));

	u32 next = m_frame + 1;
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
