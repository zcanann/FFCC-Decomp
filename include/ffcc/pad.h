
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

    struct ReplayFrame
    {
        PADStatus pad[4];
        Gba gba[4];
    };

    struct ReplayBuffer
    {
        u32 cursor;
        s32 recordMode;
        s32 frameCount;
        ReplayFrame frames[0x1A5E0];
    };

    struct PadInputRawView
    {
        short _4_2_;
        short _6_2_;
        short _8_2_;
        short _a_2_;
        unsigned char _c_1_[0x14];
        short _20_2_;
        unsigned char _22_1_[0x186];
    };

    CPad()
    {
        _1b4_4_ = 0;
        _1b8_4_ = 0;
    }

    void Init();
    void Quit();
    void SaveReplayData();
    void Frame();
    unsigned short GetButtonDown(long);
    unsigned short GetDebugButtonDown(long);
    unsigned short GetDebugButton(long);
    unsigned short GetGbaButtonDown(long);
    float GetRightStickY(long);
    float GetRightStickX(long);
    float GetLeftStickY(long);
    float GetLeftStickX(long);
    float GetTriggerLeft(long);
    float GetTriggerRight(long);
    unsigned short GetButtonRepeat(long);
    unsigned short GetButton(long);
    int IsGba(long);
    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x8005396C
     * EN Size: 164b
     * JP Address: TODO
     * JP Size: TODO
     */
    int IsDebug(long port)
    {
        bool suppress = false;
        if (m_debugPadLock != 0 || (port == 0 && m_debugPadPort != -1)) {
            suppress = true;
        }
        int result;
        if (suppress) {
            result = 0;
        } else {
            unsigned int index = (port == m_debugPadPort) ? 0 : static_cast<unsigned int>(port);
            result = m_padInputs[index].holdOverride;
        }
        return result;
    }
    /*
     * --INFO--
     * PAL Address: UNUSED
     * PAL Size: TODO
     * EN Address: 0x80053964
     * EN Size: 8b
     * JP Address: TODO
     * JP Size: TODO
     */
    int GetPortEmulation() { return m_debugPadPort; }
    PadInput* GetPadInputs() { return m_padInputs; }
    const PadInput* GetPadInputs() const { return m_padInputs; }
    PadInput* GetMergedPad() { return &GetPadInputs()[4]; }
    const PadInput* GetMergedPad() const { return &GetPadInputs()[4]; }
    union {
        PadInput m_padInputs[5];
        PadInputRawView m_padInputsRaw;
    };
    unsigned int _1a8_4_;
    void* _1ac_4_;
    ReplayBuffer* m_replayBuffer;
    int _1b4_4_;
    int _1b8_4_;
    int m_replayFrame;
    union {
        unsigned int _1c0_4_;
        int _448_4_;
        int m_debugPadPort;
    };
    union {
        unsigned int _1c4_4_;
        int _452_4_;
        int m_debugPadLock;
    };
    union {
        int _1c8_4_;
        int _456_4_;
        int m_stickDigitalThreshold;
    };
};

typedef char CPad_PadInput_size_check[(sizeof(CPad::PadInput) == 0x54) ? 1 : -1];

extern CPad Pad;

/*
 * --INFO--
 * PAL Address: 0x80041F28
 * PAL Size: 100b
 * EN Address: 0x8002CEB4
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short CPad::GetButtonDown(long padIndex)
{
    bool shouldZero = false;
    unsigned int result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].buttonDown[0];
    }

    return static_cast<unsigned short>(result);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short CPad::GetDebugButtonDown(long padIndex)
{
    const bool shouldZero = padIndex == 0
        ? (m_debugPadLock != 0 || m_debugPadPort != -1)
        : m_debugPadLock != 0;
    unsigned int result;

    if (shouldZero) {
        result = 0;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].lockedButton[1];
    }

    return static_cast<unsigned short>(result);
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CPad::GetTriggerLeft(long padIndex)
{
    const bool shouldZero = padIndex == 0
        ? (m_debugPadLock != 0 || m_debugPadPort != -1)
        : m_debugPadLock != 0;
    float result;

    if (shouldZero) {
        result = 0.0f;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].triggerLeftF;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CPad::GetTriggerRight(long padIndex)
{
    const bool shouldZero = padIndex == 0
        ? (m_debugPadLock != 0 || m_debugPadPort != -1)
        : m_debugPadLock != 0;
    float result;

    if (shouldZero) {
        result = 0.0f;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].triggerRightF;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: UNUSED
 * PAL Size: TODO
 * EN Address: TODO
 * EN Size: TODO
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short CPad::GetDebugButton(long padIndex)
{
    const bool shouldZero = padIndex == 0
        ? (m_debugPadLock != 0 || m_debugPadPort != -1)
        : m_debugPadLock != 0;
    unsigned int result;

    if (shouldZero) {
        result = 0;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].lockedButton[0];
    }

    return static_cast<unsigned short>(result);
}

/*
 * --INFO--
 * PAL Address: 0x800B9AE0
 * PAL Size: 100b
 * EN Address: 0x800AA5CC
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short CPad::GetButtonRepeat(long padIndex)
{
    bool shouldZero = false;
    unsigned int result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].repeatButton;
    }

    return static_cast<unsigned short>(result);
}

/*
 * --INFO--
 * PAL Address: 0x800B9BB8
 * PAL Size: 100b
 * EN Address: 0x8004429C
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short CPad::GetButton(long padIndex)
{
    bool shouldZero = false;
    unsigned int result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].button[0];
    }

    return static_cast<unsigned short>(result);
}

/*
 * --INFO--
 * PAL Address: 0x800B9A20
 * PAL Size: 96b
 * EN Address: 0x80043E94
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CPad::GetLeftStickY(long padIndex)
{
    bool shouldZero = false;
    float result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0.0f;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].stickYF;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x800B9A80
 * PAL Size: 96b
 * EN Address: 0x80044098
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CPad::GetLeftStickX(long padIndex)
{
    bool shouldZero = false;
    float result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0.0f;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].stickXF;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x800B9960
 * PAL Size: 96b
 * EN Address: 0x80044144
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CPad::GetRightStickY(long padIndex)
{
    bool shouldZero = false;
    float result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0.0f;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].substickYF;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x800B99C0
 * PAL Size: 96b
 * EN Address: 0x800441F0
 * EN Size: 172b
 * JP Address: TODO
 * JP Size: TODO
 */
inline float CPad::GetRightStickX(long padIndex)
{
    bool shouldZero = false;
    float result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0.0f;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].substickXF;
    }

    return result;
}

/*
 * --INFO--
 * PAL Address: 0x800B9330
 * PAL Size: 100b
 * EN Address: 0x8002CE10
 * EN Size: 164b
 * JP Address: TODO
 * JP Size: TODO
 */
inline unsigned short CPad::GetGbaButtonDown(long padIndex)
{
    bool shouldZero = false;
    unsigned int result;

    if (m_debugPadLock != 0 || (padIndex == 0 && m_debugPadPort != -1)) {
        shouldZero = true;
    }

    if (shouldZero) {
        result = 0;
    } else {
        unsigned int resolvedIndex = (m_debugPadPort == padIndex) ? 0 : static_cast<unsigned int>(padIndex);
        result = GetPadInputs()[resolvedIndex].buttonDown[1];
    }

    return static_cast<unsigned short>(result);
}

#endif
