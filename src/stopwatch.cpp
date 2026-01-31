#include "ffcc/stopwatch.h"

extern "C" float __cvt_sll_flt(u32 lo, u32 hi);

extern char lbl_8032F860[]; // small-data string used by target
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
	// Match target: convert accumulated ticks (total) into microseconds as float.
	u32* p = (u32*)&this->total;
	u32 lo = p[0];
	u32 hi = p[1];
	float ticks = __cvt_sll_flt(lo, hi);
	float denom = (float)(OS_TIMER_CLOCK / 125000);
	return (8.0f * ticks) / denom;
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
	u32* p = (u32*)&this->total;
	u32 lo = p[0];
	u32 hi = p[1];
	float ticks = __cvt_sll_flt(lo, hi);
	float denom = (float)(OS_TIMER_CLOCK / 125000);
	m_lastTime = (8.0f * ticks) / denom;

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
