#ifndef _PPP_YMDEFORMATIONSCREEN_H_
#define _PPP_YMDEFORMATIONSCREEN_H_

class CCameraPcs;
struct VYmDeformationScreen;
struct Vec;

void SetUpIndWarp(VYmDeformationScreen *);
void pppConstructYmDeformationScreen(void);
void pppConstruct2YmDeformationScreen(void);
void pppDestructYmDeformationScreen(void);
void pppFrameYmDeformationScreen(void);
void pppRenderYmDeformationScreen(void);
void GXEnd(void);
void GXSetTexCoordGen(void);
void CCameraPcs_GetRefPosition(Vec *);

#endif // _PPP_YMDEFORMATIONSCREEN_H_
