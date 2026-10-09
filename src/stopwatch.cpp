#include "ffcc/stopwatch.h"

/*
 * --INFO--
 * PAL Address: 0x8002147C
 * PAL Size: 56b
 * EN Address: 0x80021270
 * EN Size: 56b
 * JP Address: 0x80020D08
 * JP Size: 56b
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
 * EN Address: 0x80021234
 * EN Size: 60b
 * JP Address: 0x80020CCC
 * JP Size: 60b
 */
CStopWatch::~CStopWatch() {}

/*
 * --INFO--
 * PAL Address: 0x80021420
 * PAL Size: 32b
 * EN Address: 0x80021214
 * EN Size: 32b
 * JP Address: 0x80020CAC
 * JP Size: 32b
 */
void CStopWatch::Reset() { OSResetStopwatch(this); }

/*
 * --INFO--
 * PAL Address: 0x80021400
 * PAL Size: 32b
 * EN Address: 0x800211F4
 * EN Size: 32b
 * JP Address: 0x80020C8C
 * JP Size: 32b
 */
void CStopWatch::Start() { OSStartStopwatch(this); }

/*
 * --INFO--
 * PAL Address: 0x800213E0
 * PAL Size: 32b
 * EN Address: 0x800211D4
 * EN Size: 32b
 * JP Address: 0x80020C6C
 * JP Size: 32b
 */
void CStopWatch::Stop() { OSStopStopwatch(this); }

/*
 * --INFO--
 * PAL Address: 0x80021368
 * PAL Size: 120b
 * EN Address: 0x8002115C
 * EN Size: 120b
 * JP Address: 0x80020BF4
 * JP Size: 120b
 */
float CStopWatch::Get()
{
	float ticks = static_cast<float>(total);
	float denom = static_cast<float>(OSMicrosecondsToTicks(33333));
	ticks = ticks / denom;
	return 100.0f * ticks;
}

/*
 * --INFO--
 * PAL Address: 0x800212F8
 * PAL Size: 112b
 * EN Address: 0x800210EC
 * EN Size: 112b
 * JP Address: 0x80020B84
 * JP Size: 112b
 */
CProfile::CProfile(char* name)
{
	CStopWatch tmp(name);

	m_lastTime = m_maxTime = 0.0f;
	m_frame = 0;
}

/*
 * --INFO--
 * PAL Address: 0x800212BC
 * PAL Size: 60b
 * EN Address: 0x800210B0
 * EN Size: 60b
 * JP Address: 0x80020B48
 * JP Size: 60b
 */
CProfile::~CProfile() {}

/*
 * --INFO--
 * PAL Address: 0x8002129C
 * PAL Size: 32b
 * EN Address: 0x80021090
 * EN Size: 32b
 * JP Address: 0x80020B28
 * JP Size: 32b
 */
void CProfile::ProfStart() { Reset(); }

/*
 * --INFO--
 * PAL Address: 0x800211D4
 * PAL Size: 200b
 * EN Address: 0x80020FC8
 * EN Size: 200b
 * JP Address: 0x80020A60
 * JP Size: 200b
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
