#ifndef _FFCC_P_GRAPHIC_H_
#define _FFCC_P_GRAPHIC_H_

#include "ffcc/system.h"

#include <dolphin/gx.h>

class CGraphicPcs : public CProcess
{
public:
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
};

#endif // _FFCC_P_GRAPHIC_H_
