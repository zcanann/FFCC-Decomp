#ifndef _FFCC_PAD_H_
#define _FFCC_PAD_H_

struct PADStatus
{
	void operator=(PADStatus&, const PADStatus&);
};

class CPad
{
public:
    struct Gba
	{
		void operator=(CPad::Gba&, const CPad::Gba&);
	};

    CPad();

    void Init();
    void Quit();
    void Frame();
    void SaveReplayData();
};

#endif
