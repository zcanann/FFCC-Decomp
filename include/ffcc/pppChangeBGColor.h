#ifndef _FFCC_PPPCHANGEBGCOLOR_H_
#define _FFCC_PPPCHANGEBGCOLOR_H_

#include "ffcc/partMng.h"

struct _GXColor;

// Simplified structure definitions for compilation
struct pppChangeBGColor {
    char padding[0x90];  // Padding to reach field_0x88 area
};

struct pppChangeBGColorUnkB {
    char data[16];
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConChangeBGColor(_pppPObjLink*, _pppCtrlTable*);
void pppDesChangeBGColor(_pppPObjLink*, _pppCtrlTable*);
void pppFrameChangeBGColor(struct pppChangeBGColor* pppChangeBGColor, struct pppChangeBGColorUnkB* param_2,
                           _pppCtrlTable* param_3);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGEBGCOLOR_H_

