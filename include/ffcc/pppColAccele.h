#ifndef _FFCC_PPPCOLACCELE_H_
#define _FFCC_PPPCOLACCELE_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct pppColAcceleDataOffsets {
    s32 m_colorOffset;
    s32 m_accelerationOffset;
};

struct pppColorDelta
{
    short r;
    short g;
    short b;
    short a;
};

struct pppColAcceleStep
{
    int m_graphId;
    int m_pad4;
    pppColorDelta m_acceleration;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppColAccele(_pppPObject* object, pppColAcceleStep* data, _pppCtrlTable* ctrlTable);
void pppColAcceleCon(_pppPObject* object, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLACCELE_H_
