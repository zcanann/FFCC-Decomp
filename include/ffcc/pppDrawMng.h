#ifndef _FFCC_PPPDRAWMNG_H_
#define _FFCC_PPPDRAWMNG_H_

#include "ffcc/p_chara_viewer.h"

struct pppOtDrawPrim;
struct _pppMngSt;

class pppDrawMng {
public:
    void ClearOt();
    void DrawOt();
    void AddPrimOt(unsigned long, pppOtDrawPrim*);
    void AddPrimOt(unsigned long, _pppMngSt*);
    void AddPrim(float, _pppMngSt*, char);
    void AddPrimOt(unsigned long, CCharaPcs::CHandle*);
    void AddPrim(float, CCharaPcs::CHandle*);
};

#endif // _FFCC_PPPDRAWMNG_H_
