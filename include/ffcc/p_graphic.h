#ifndef _FFCC_P_GRAPHIC_H_
#define _FFCC_P_GRAPHIC_H_

#include "ffcc/system.h"

#include <dolphin/gx.h>
#include <dolphin/mtx.h>

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

    static u32 m_table_desc0[3];
    static u32 m_table_desc1[3];
    static u32 m_table_desc2[3];
    static u32 m_table_desc3[3];
    static u32 m_table_desc4[3];
    static u32 m_table_desc5[3];
    static u32 m_table_desc6[3];
    static u32 m_table_desc7[3];
    static u32 m_table_desc8[3];
    static u32 m_table_desc9[3];
    static u32 m_table[0x15C / sizeof(u32)];

    void Init();
    void Quit();
    int GetTable(unsigned long);

    void create();
    void destroy();

    void SetDOFParameter(signed char, signed char, float, float, float, float, float, int);
    void SetBlurParameter(int, unsigned char, unsigned char, unsigned char, unsigned char, unsigned char, short);
    void SetUseDOF(int);
    void ReqScreenCapture();

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

    CGraphicPcs()
    {
        u32* table = &m_table[1];
        table[31] = m_table_desc7[0];
        table[32] = m_table_desc7[1];
        table[36] = m_table_desc8[0];
        table[37] = m_table_desc8[1];
        table[0] = m_table_desc0[0];
        table[1] = m_table_desc0[1];
        table[2] = m_table_desc0[2];
        table[3] = m_table_desc1[0];
        table[4] = m_table_desc1[1];
        table[5] = m_table_desc1[2];
        table[6] = m_table_desc2[0];
        table[7] = m_table_desc2[1];
        table[8] = m_table_desc2[2];
        table[11] = m_table_desc3[0];
        table[12] = m_table_desc3[1];
        table[13] = m_table_desc3[2];
        table[16] = m_table_desc4[0];
        table[17] = m_table_desc4[1];
        table[18] = m_table_desc4[2];
        table[21] = m_table_desc5[0];
        table[22] = m_table_desc5[1];
        table[23] = m_table_desc5[2];
        table[26] = m_table_desc6[0];
        table[27] = m_table_desc6[1];
        table[28] = m_table_desc6[2];
        table[33] = m_table_desc7[2];
        table[38] = m_table_desc8[2];
        table[41] = m_table_desc9[0];
        table[42] = m_table_desc9[1];
        table[43] = m_table_desc9[2];
    }

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
    Vec m_dofTarget;                // 0x0D4
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

extern "C" void create__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void destroy__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void calc__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawBegin__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawWait__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawFlip__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawEnd__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void drawCopy__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void setViewport__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void preDrawEnvInit__11CGraphicPcsFv(CGraphicPcs*);
extern "C" void stdDrawEnvInit__11CGraphicPcsFv(CGraphicPcs*);

extern CGraphicPcs GraphicPcs;

#endif // _FFCC_P_GRAPHIC_H_
