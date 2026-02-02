#ifndef _PPP_YMDEFORMATIONSCREEN_H_
#define _PPP_YMDEFORMATIONSCREEN_H_

class CCameraPcs;
struct VYmDeformationScreen;
struct pppYmDeformationScreen;
struct Vec;

void SetUpIndWarp(VYmDeformationScreen*);
void CCameraPcs_GetRefPosition(Vec*);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationScreen(pppYmDeformationScreen*, void*);
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen*, void*);
void pppDestructYmDeformationScreen(void);
void pppFrameYmDeformationScreen(pppYmDeformationScreen*, void*, void*);
void pppRenderYmDeformationScreen(pppYmDeformationScreen*, void*, void*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONSCREEN_H_
