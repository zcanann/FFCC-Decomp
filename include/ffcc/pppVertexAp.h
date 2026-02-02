#ifndef _PPP_VERTEXAP_H_
#define _PPP_VERTEXAP_H_

struct _pppPObject;
class PVertexAp;
struct Vec;

void apea(_pppPObject*, PVertexAp*, Vec*);

#ifdef __cplusplus
extern "C" {
#endif

void pppVertexApCon(_pppPObject*, PVertexAp*);
void pppVertexAp(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_VERTEXAP_H_
