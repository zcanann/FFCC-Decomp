#ifndef _PPP_VERTEXAPMTX_H_
#define _PPP_VERTEXAPMTX_H_

struct _pppPObject;
class PVertexApMtx;
struct Vec;

void pppVertexApMtxCon(_pppPObject* obj, PVertexApMtx* vtx);
void apea(_pppPObject*, PVertexApMtx*, Vec*);
void pppVertexApMtx(void);

#endif // _PPP_VERTEXAPMTX_H_
