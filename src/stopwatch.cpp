#include "ffcc/stopwatch.h"

extern "C" float __cvt_sll_flt(u32 lo, u32 hi);

static const float s_stopwatchScale = 100.0f;

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
	u32 scaled = (OS_TIMER_CLOCK / 125000) * 0x8235;
	float denom = (float)(scaled >> 3);
	float elapsed = ticks / denom;
	elapsed = s_stopwatchScale * elapsed;
	m_lastTime = elapsed;

	int next = m_frame + 1;
	m_frame = next;
	if (next == 0x5A)
	{
		m_maxTime = 0.0f;
		m_frame = 0;
	}

	if (m_maxTime < m_lastTime)
	{
		m_maxTime = m_lastTime;
		m_frame = 0;
	}
}

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
CProfile::~CProfile() {}

const char s_stopwatchDefaultName[] = "no name";

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
	OSInitStopwatch(this, (char*)s_stopwatchDefaultName);
	OSResetStopwatch(this);

	OSStopwatch tmp;
	OSInitStopwatch(&tmp, name);
	OSResetStopwatch(&tmp);

	float time = 0.0f;
	m_maxTime = time;
	m_lastTime = time;
	m_frame = 0;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
float CStopWatch::Get()
{
	volatile u32* p = (volatile u32*)&this->total;
	u32 hi = p[1];
	u32 lo = p[0];
	float ticks = __cvt_sll_flt(lo, hi);
	u32 scaled = (OS_TIMER_CLOCK / 125000) * 0x8235;
	float denom = (float)(scaled >> 3);
	ticks = ticks / denom;
	return s_stopwatchScale * ticks;
}

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
void CStopWatch::Start() { OSStartStopwatch(this); }

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
CStopWatch::~CStopWatch() {}

/*
 * --INFO--
 * PAL Address: 0x8002147C
 * PAL Size: 56b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CStopWatch::CStopWatch(char* name)
{
	OSInitStopwatch(this, name);
	OSResetStopwatch(this);
}
