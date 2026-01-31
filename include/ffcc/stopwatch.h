#ifndef _FFCC_STOPWATCH_H
#define _FFCC_STOPWATCH_H

#include <Dolphin/types.h>
#include <dolphin/os.h>

#include "ffcc/manager.h"

class CStopWatch : public OSStopwatch
{
public:
	CStopWatch(char* name);
	~CStopWatch();

	void Reset();
	void Start();
	void Stop();
	float Get();
};

class CProfile : public OSStopwatch
{
public:
	CProfile(char* name);
	~CProfile();

	void ProfStart();
	void ProfEnd();

	// OSStopwatch is 0x30. These pad bytes model the real class layout up to 0x60.
	u8 _pad_0x30[0x30];
	float m_lastTime; // 0x60
	float m_maxTime;  // 0x64
	u32 m_frame;      // 0x68
};

#endif // _FFCC_STOPWATCH_H
