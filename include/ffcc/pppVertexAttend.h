#ifndef _PPP_VERTEXATTEND_H_
#define _PPP_VERTEXATTEND_H_

struct _pppPObject;
struct _pppCtrlTable;
struct pppVertexAttendStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexAttend(_pppPObject* object, pppVertexAttendStep* step, _pppCtrlTable* ctrl);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXATTEND_H_
