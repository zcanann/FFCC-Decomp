#ifndef _PPP_VERTEXAP_H_
#define _PPP_VERTEXAP_H_

#include <dolphin/types.h>

struct _pppPObject;
struct _pppCtrlTable;
class PVertexAp;
struct Vec;

struct VertexApDataOffsets {
    s32 m_stateOffset;
};

void apea(_pppPObject*, PVertexAp*, Vec*);

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexApCon(_pppPObject*, _pppCtrlTable*);
void pppVertexAp(_pppPObject*, PVertexAp*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXAP_H_
