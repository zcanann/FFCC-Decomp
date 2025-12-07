#ifndef _PPP_YMDEFORMATIONMDL_H_
#define _PPP_YMDEFORMATIONMDL_H_

struct VYmDeformationMdl;

void SetUpIndWarp(VYmDeformationMdl*);
void DisableIndWarp(void);
void pppConstructYmDeformationMdl(void);
void pppConstruct2YmDeformationMdl(void);
void pppDestructYmDeformationMdl(void);
void pppFrameYmDeformationMdl(void);
void pppRenderYmDeformationMdl(void);
void GXSetTexCoordGen(void);

#endif // _PPP_YMDEFORMATIONMDL_H_
