#ifndef _PPP_YMLOOKON_H_
#define _PPP_YMLOOKON_H_

#include "ffcc/partMng.h"

struct pppYmLookOn {
    _pppPObject m_object;
};

struct pppYmLookOnStep {
    int m_graphId;
    float m_dataValIndex;
};

struct pppYmLookOnCtrl {
    unsigned char pad[0x0C];
    int* m_serializedDataOffsets;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmLookOn(struct pppYmLookOn* pppYmLookOn, struct pppYmLookOnCtrl* param_2);
void pppFrameYmLookOn(struct pppYmLookOn* pppYmLookOn, struct pppYmLookOnStep* param_2, struct pppYmLookOnCtrl* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLOOKON_H_

