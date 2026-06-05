#ifndef _PPP_YMDEFORMATIONSCREEN_H_
#define _PPP_YMDEFORMATIONSCREEN_H_

struct _pppPObject;

typedef _pppPObject pppYmDeformationScreen;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationScreen(pppYmDeformationScreen*, void*);
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen*, void*);
void pppDestructYmDeformationScreen(pppYmDeformationScreen*, void*);
void pppFrameYmDeformationScreen(pppYmDeformationScreen*, void*, void*);
void pppRenderYmDeformationScreen(pppYmDeformationScreen*, void*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSCREEN_H_
