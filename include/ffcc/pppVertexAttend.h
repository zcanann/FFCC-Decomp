#ifndef _PPP_VERTEXATTEND_H_
#define _PPP_VERTEXATTEND_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;

struct pppVertexAttendStep
{
    u8 pad0[0xC];
    s16 m_entryIndex;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexAttend(_pppPObject* object, pppVertexAttendStep* step, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXATTEND_H_
