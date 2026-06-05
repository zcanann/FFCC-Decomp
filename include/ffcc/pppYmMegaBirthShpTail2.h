#ifndef _PPP_YMMEGABIRTHSHPTAIL2_H_
#define _PPP_YMMEGABIRTHSHPTAIL2_H_

#include "ffcc/partMng.h"

struct _pppPObject;
struct PYmMegaBirthShpTail2;
struct pppYmMegaBirthShpTail2UnkB;

typedef _pppPObject pppYmMegaBirthShpTail2;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppDestructYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppFrameYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, PYmMegaBirthShpTail2*, _pppCtrlTable*);
void pppRenderYmMegaBirthShpTail2(pppYmMegaBirthShpTail2*, pppYmMegaBirthShpTail2UnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMMEGABIRTHSHPTAIL2_H_
