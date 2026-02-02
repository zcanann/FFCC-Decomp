#ifndef _PPP_MIASMA_H_
#define _PPP_MIASMA_H_

struct Vec;
struct _pppPObject;

void CalcSphereRadius(Vec*, unsigned short);
void CreateScaleMatrix(_pppPObject*, float);

#ifdef __cplusplus
extern "C" {
#endif

void pppRenderMiasma(void);
void pppConstructMiasma(void);
void pppConstruct2Miasma(void);
void pppDestructMiasma(void);
void pppFrameMiasma(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_MIASMA_H_
