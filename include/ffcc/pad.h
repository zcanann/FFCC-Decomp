
#ifndef _FFCC_PAD_H_
#define _FFCC_PAD_H_

struct PADStatus
{
};

class CPad
{
public:
    struct Gba
	{
	};

    CPad();

    void Init();
    void Quit();
    void Frame();
    void SaveReplayData();
};

#endif
