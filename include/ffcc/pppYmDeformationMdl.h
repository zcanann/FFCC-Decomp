#ifndef _PPP_YMDEFORMATIONMDL_H_
#define _PPP_YMDEFORMATIONMDL_H_

struct VYmDeformationMdl;

void SetUpIndWarp(VYmDeformationMdl*);
void DisableIndWarp(void);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDeformationMdl(void);
void pppConstruct2YmDeformationMdl(void);
void pppDestructYmDeformationMdl(void);
void pppFrameYmDeformationMdl(void* pppYmDeformationMdl, void* param_2, void* param_3);
void pppRenderYmDeformationMdl(void* pppYmDeformationMdl, void* param_2, void* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDEFORMATIONMDL_H_
