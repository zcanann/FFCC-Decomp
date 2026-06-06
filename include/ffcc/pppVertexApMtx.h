#ifndef _PPP_VERTEXAPMTX_H_
#define _PPP_VERTEXAPMTX_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;
class PVertexApMtx;
struct Vec;

struct VertexApMtxDataOffsets {
	s32 m_stateOffset;
};

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexApMtxCon(_pppPObject* obj, _pppCtrlTable* ctrl);
void pppVertexApMtx(_pppPObject*, PVertexApMtx*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXAPMTX_H_
