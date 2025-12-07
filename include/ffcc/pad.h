
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

    short _4_2_;
    short _8_2_;
    int _448_4_;
    int _452_4_;
};

CPad Pad;

#endif
