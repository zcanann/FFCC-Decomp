#ifndef _FFCC_STOPWATCH_H
#define _FFCC_STOPWATCH_H

#include <Dolphin/types.h>

#include "ffcc/manager.h"

class CStopWatch
{
public:
	CStopWatch(char*);
	~CStopWatch();

	void Reset();
	void Start();
	void Stop();
	void Get();
};

class CProfile
{
public:
	CProfile(char*);
	~CProfile();

	void ProfStart();
	void ProfEnd();
};

#endif // _FFCC_STOPWATCH_H
