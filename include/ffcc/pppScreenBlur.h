#ifndef _PPP_SCREENBLUR_H_
#define _PPP_SCREENBLUR_H_

#include "ffcc/partMng.h"

typedef struct {
    u8 data[0x80];
} pppScreenBlur;

typedef struct {
    u32 m_dataValIndex;
    u8 m_blurR;
    u8 m_blurG;
    u8 m_blurB;
    u8 m_pad7;
    s16 m_initWOrk;
} pppScreenBlurUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBlur(pppScreenBlur* blur, _pppCtrlTable* ctrlTable);
void pppCon2ScreenBlur(pppScreenBlur* blur);
void pppDesScreenBlur(_pppPObjLink* object, _pppCtrlTable* ctrlTable);
void pppFrameScreenBlur(_pppPObject* object, void* step, _pppCtrlTable* ctrlTable);
void pppRenderScreenBlur(pppScreenBlur* blur, pppScreenBlurUnkB* step, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBLUR_H_
