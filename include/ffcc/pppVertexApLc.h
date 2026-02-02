#ifndef _PPP_VERTEXAPLC_H_
#define _PPP_VERTEXAPLC_H_

struct _pppPObject;
class PVertexApLc;
struct Vec;

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexApLcCon(_pppPObject*, PVertexApLc*);
void pppVertexApLc(_pppPObject*, PVertexApLc*, Vec*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXAPLC_H_
