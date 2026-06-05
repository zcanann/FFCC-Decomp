#ifndef _PPP_VERTEXAPLC_H_
#define _PPP_VERTEXAPLC_H_

struct _pppPObject;
struct _pppCtrlTable;
class PVertexApLc;
struct Vec;

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexApLcCon(_pppPObject*, _pppCtrlTable*);
void pppVertexApLc(_pppPObject*, PVertexApLc*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXAPLC_H_
