#ifndef _PPP_SCALELOOPAUTO_H_
#define _PPP_SCALELOOPAUTO_H_



struct _pppPObject;
struct pppScaleLoopAutoContext;
struct pppScaleLoopAutoStep;
#ifdef __cplusplus
extern "C" {
#endif

void pppScaleLoopAuto(struct _pppPObject* arg1, struct pppScaleLoopAutoStep* arg2, struct pppScaleLoopAutoContext* arg3);
void pppScaleLoopAutoCon(void* arg1, void* arg2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCALELOOPAUTO_H_
