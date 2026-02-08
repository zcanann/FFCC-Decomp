#ifndef _PPP_VERTEXAPMTX_H_
#define _PPP_VERTEXAPMTX_H_

struct _pppPObject;
class PVertexApMtx;
struct Vec;

void apea(_pppPObject*, PVertexApMtx*, Vec*);

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexApMtxCon(_pppPObject* obj, PVertexApMtx* vtx);
void pppVertexApMtx(_pppPObject*, PVertexApMtx*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXAPMTX_H_
