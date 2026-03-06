#ifndef _FFCC_P_GRAPHIC_H_
#define _FFCC_P_GRAPHIC_H_

#include "ffcc/system.h"

#include <dolphin/gx.h>

class CGraphicPcs : public CProcess
{
public:
    struct ScreenFadeSlot
    {
        int m_timer;         // 0x00
        int m_duration;      // 0x04
        _GXColor m_colorA;   // 0x08
        _GXColor m_colorB;   // 0x0C
        int m_invert;        // 0x10
        int m_mode;          // 0x14
        void* m_targetObj;   // 0x18
        float m_targetYOffs; // 0x1C
        float m_phase;       // 0x20
        float m_stretch;     // 0x24
        float m_amplitude;   // 0x28
    };

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void SetDOFParameter(signed char, signed char, float, float, float, float, float, int);
    void SetBlurParameter(int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, short);

    void calc();

    void drawBegin();
    void drawWait();
    void drawFlip();
    void drawEnd();
    void drawBar();
    void drawCopy();
    void setViewport();

    void preDrawEnvInit();
    void stdDrawEnvInit();

    void calcScreenFade();
    void drawSFRect(float, float, float, float, _GXColor, _GXColor);
    void drawSFCircle(int, int, int, int, _GXColor, _GXColor);
    unsigned int GetScreenFadeExecutingBit();
    void drawScreenFade();

    CGraphicPcs();

    ScreenFadeSlot m_screenFade[4]; // 0x004
    int m_unkB4;                    // 0x0B4
    int m_unkB8;                    // 0x0B8
    int m_copySaveFlag;             // 0x0BC
    int m_dofFlag;                  // 0x0C0
    signed char m_dofFlagB;         // 0x0C4
    unsigned char _padC5[3];        // 0x0C5
    float m_dofNearZ;               // 0x0C8
    float m_dofFarZ;                // 0x0CC
    int m_dofMode;                  // 0x0D0
    float m_dofFocus;               // 0x0D4
    float m_dofBlurNear;            // 0x0D8
    float m_dofBlurFar;             // 0x0DC
    signed char m_dofFlagA;         // 0x0E0
    unsigned char _padE1[3];        // 0x0E1
    int m_blurMode;                 // 0x0E4
    int m_blurFadeOutFlag;          // 0x0E8
    unsigned char m_blurR;          // 0x0EC
    unsigned char m_blurG;          // 0x0ED
    unsigned char m_blurB;          // 0x0EE
    unsigned char m_blurStep;       // 0x0EF
    unsigned char m_blurA;          // 0x0F0
    unsigned char m_blurMode2;      // 0x0F1
    short m_blurScale;              // 0x0F2
};

extern CGraphicPcs GraphicsPcs;

#endif // _FFCC_P_GRAPHIC_H_
