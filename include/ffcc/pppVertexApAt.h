#ifndef _PPP_VERTEXAPAT_H_
#define _PPP_VERTEXAPAT_H_

struct _pppPObject;
struct _pppCtrlTable;
class PVertexApAt;
class PVertexApLc;

void apea(_pppPObject*, PVertexApAt*, unsigned short);

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexApAtCon(_pppPObject*, _pppCtrlTable*);
void pppVertexApAt(_pppPObject*, PVertexApAt*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXAPAT_H_
