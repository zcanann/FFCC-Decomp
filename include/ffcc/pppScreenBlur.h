#ifndef _PPP_SCREENBLUR_H_
#define _PPP_SCREENBLUR_H_

#include "ffcc/partMng.h"

struct pppScreenBlurStep {
    u32 m_dataValIndex;
    u8 m_blurR;
    u8 m_blurG;
    u8 m_blurB;
    u8 m_pad7;
    s16 m_initWOrk;
};

struct ScreenBlurDataOffsets {
    s32 m_valueOffset;
    s32 m_activeOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBlur(_pppPObject* blur, _pppCtrlTable* ctrlTable);
void pppCon2ScreenBlur(_pppPObject* blur);
void pppDesScreenBlur(_pppPObjLink* object, _pppCtrlTable* ctrlTable);
void pppFrameScreenBlur(_pppPObject* object, pppScreenBlurStep* step, _pppCtrlTable* ctrlTable);
void pppRenderScreenBlur(_pppPObject* blur, pppScreenBlurStep* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBLUR_H_
