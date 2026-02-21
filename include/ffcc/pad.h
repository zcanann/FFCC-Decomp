
#ifndef _FFCC_PAD_H_
#define _FFCC_PAD_H_

#include "dolphin/pad.h"

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
    unsigned short GetButtonDown(long);

    void* _0_4_;
    short _4_2_;
    short _6_2_;
    short _8_2_;
    short _a_2_;
    unsigned char _c_1_[0x19c];
    unsigned int _1a8_4_;
    void* _1ac_4_;
    unsigned char* _1b0_4_;
    union {
        int _1b4_4_;
        int _448_4_;
    };
    union {
        int _1b8_4_;
        int _452_4_;
    };
    int _1bc_4_;
    unsigned int _1c0_4_;
    unsigned int _1c4_4_;
    unsigned int _1c8_4_;
};

extern CPad Pad;

#endif
