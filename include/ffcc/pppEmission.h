#ifndef _PPPEMISSION_H_
#define _PPPEMISSION_H_

struct _pppCtrlTable;
struct _pppPObject;
struct PEmission;

typedef _pppPObject pppEmission;
typedef PEmission pppEmissionUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEmission(pppEmission*, _pppCtrlTable*);
void pppConstruct2Emission(pppEmission*, _pppCtrlTable*);
void pppDestructEmission(pppEmission*, _pppCtrlTable*);
void pppFrameEmission(pppEmission*, pppEmissionUnkB*, _pppCtrlTable*);
void pppRenderEmission(pppEmission*, pppEmissionUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPPEMISSION_H_
