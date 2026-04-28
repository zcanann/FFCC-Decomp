
#ifndef _FFCC_PAD_H_
#define _FFCC_PAD_H_

#include "dolphin/pad.h"
#include "ffcc/manager.h"

class CPad : public CManager
{
public:
    struct PadInput
    {
        u16 button[2];
        u16 buttonDown[2];
        u16 stickBitsPrev;
        u16 stickBits;
        u16 stickBitsDown;
        u16 buttonUp;
        u16 repeatButton;
        u8 triggerLeft;
        u8 triggerRight;
        s8 stickX;
        s8 stickY;
        s8 substickX;
        s8 substickY;
        float triggerLeftF;
        float triggerRightF;
        float stickXF;
        float stickYF;
        float substickXF;
        float substickYF;
        u16 lockedButton[3];
        u16 _pad36;
        u32 holdOverride;
        u32 digitalStickOverride;
        s8 err;
        u8 _pad41[3];
        u32 activeMask;
        u32 hasInputMask;
        u16 buttonPrev[2];
        u32 gbaMode;
    };

    struct Gba
	{
        unsigned short connected : 1;
        unsigned short noController : 1;
        unsigned short ctrlMode : 14;
        unsigned short button;
	};

    CPad()
    {
        _1b4_4_ = 0;
        _1b8_4_ = 0;
    }

    void Init();
    void Quit();
    void Frame();
    void SaveReplayData() {}
    unsigned short GetButtonDown(long);
    PadInput* GetPadInputs() { return reinterpret_cast<PadInput*>(&_4_2_); }
    const PadInput* GetPadInputs() const { return reinterpret_cast<const PadInput*>(&_4_2_); }
    PadInput* GetMergedPad() { return &GetPadInputs()[4]; }
    const PadInput* GetMergedPad() const { return &GetPadInputs()[4]; }
    short _4_2_;
    short _6_2_;
    short _8_2_;
    short _a_2_;
    unsigned char _c_1_[0x14];
    short _20_2_;
    unsigned char _22_1_[0x186];
    unsigned int _1a8_4_;
    void* _1ac_4_;
    unsigned char* _1b0_4_;
    int _1b4_4_;
    int _1b8_4_;
    int _1bc_4_;
    union {
        unsigned int _1c0_4_;
        int _448_4_;
    };
    union {
        unsigned int _1c4_4_;
        int _452_4_;
    };
    union {
        int _1c8_4_;
        int _456_4_;
    };
};

typedef char CPad_PadInput_size_check[(sizeof(CPad::PadInput) == 0x54) ? 1 : -1];

extern CPad Pad;

#endif
