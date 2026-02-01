#ifndef _PPP_YMDEFORMATIONSCREEN_H_
#define _PPP_YMDEFORMATIONSCREEN_H_

class CCameraPcs;
struct VYmDeformationScreen;
struct pppYmDeformationScreen;
struct Vec;

void SetUpIndWarp(VYmDeformationScreen*);
void pppConstructYmDeformationScreen(pppYmDeformationScreen*, void*);
void pppConstruct2YmDeformationScreen(pppYmDeformationScreen*, void*);
void pppDestructYmDeformationScreen(void);
void pppFrameYmDeformationScreen(pppYmDeformationScreen*, void*, void*);
void pppRenderYmDeformationScreen(pppYmDeformationScreen*, void*, void*);
void CCameraPcs_GetRefPosition(Vec*);

#endif // _PPP_YMDEFORMATIONSCREEN_H_
