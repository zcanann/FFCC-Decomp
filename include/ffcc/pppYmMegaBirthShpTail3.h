#ifndef _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
#define _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_

#include "ffcc/partMng.h"

struct _pppPObject;
struct PYmMegaBirthShpTail3;
struct pppYmMegaBirthShpTail3UnkB;
struct pppYmMegaBirthShpTail3UnkC;

typedef _pppPObject pppYmMegaBirthShpTail3;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkC*);
void pppDestructYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkC*);
void pppFrameYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, PYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkC*);
void pppRenderYmMegaBirthShpTail3(pppYmMegaBirthShpTail3*, pppYmMegaBirthShpTail3UnkB*, pppYmMegaBirthShpTail3UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPP_YMMEGABIRTHSHPTAIL3_H_
