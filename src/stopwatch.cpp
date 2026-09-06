#include "ffcc/stopwatch.h"

static const float s_stopwatchScale = 100.0f;

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

/*
 * --INFO--
 * PAL Address: 0x80021440
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CStopWatch::~CStopWatch() {}

/*
 * --INFO--
 * PAL Address: 0x80021420
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CStopWatch::Reset() { OSResetStopwatch(this); }

/*
 * --INFO--
 * PAL Address: 0x80021400
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CStopWatch::Start() { OSStartStopwatch(this); }

/*
 * --INFO--
 * PAL Address: 0x800213E0
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CStopWatch::Stop() { OSStopStopwatch(this); }

/*
 * --INFO--
 * PAL Address: 0x80021368
 * PAL Size: 120b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
float CStopWatch::Get()
{
	float ticks = static_cast<float>(total);
	float denom = static_cast<float>(OSMicrosecondsToTicks(33333));
	ticks = ticks / denom;
	return s_stopwatchScale * ticks;
}

/*
 * --INFO--
 * PAL Address: 0x800212F8
 * PAL Size: 112b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CProfile::CProfile(char* name)
{
	CStopWatch tmp(name);

	float time = 0.0f;
	m_maxTime = time;
	m_lastTime = time;
	m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800212BC
 * PAL Size: 60b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
CProfile::~CProfile() {}

/*
 * --INFO--
 * PAL Address: 0x8002129C
 * PAL Size: 32b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProfile::ProfStart() { Reset(); }

/*
 * --INFO--
 * PAL Address: 0x800211D4
 * PAL Size: 200b
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
void CProfile::ProfEnd()
{
	m_lastTime = Get();

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
