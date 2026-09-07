#ifndef _FFCC_STOPWATCH_H
#define _FFCC_STOPWATCH_H

#include <Dolphin/types.h>
#include <dolphin/os.h>

#include "ffcc/linkage.h"

class CStopWatch : public OSStopwatch
{
public:
	CStopWatch(char* name = "no name");
	~CStopWatch();

	void Reset();
	void Start();
	void Stop();
	float Get();
};

class CProfile : public CStopWatch
{
public:
	CProfile(char* name);
	~CProfile();

	void ProfStart();
	void ProfEnd();

	// Unrecovered profile storage between the stopwatch and timing fields.
	u8 _pad_0x30[0x30];
	float m_lastTime; // 0x60
	float m_maxTime;  // 0x64
	int m_frame;      // 0x68
};

STATIC_ASSERT(sizeof(CStopWatch) == 0x30);
STATIC_ASSERT(sizeof(CProfile) == 0x70);
STATIC_ASSERT(offsetof(CProfile, m_lastTime) == 0x60);

#endif // _FFCC_STOPWATCH_H
