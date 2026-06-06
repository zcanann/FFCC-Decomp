#ifndef _PPP_POINT_H_
#define _PPP_POINT_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct PppPointDataOffsets {
    s32 m_pointOffset;
};

struct pppPointStep
{
    s32 m_graphId;
    f32 m_unknown4;
    f32 m_x;
    f32 m_y;
    f32 m_z;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppPoint(_pppPObject* pObject, pppPointStep* step, _pppCtrlTable* ctrlTable);
void pppPointCon(_pppPObject* pObject, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_POINT_H_
