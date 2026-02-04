#ifndef _PPP_YMLASER_H_
#define _PPP_YMLASER_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmLaser(void* pppYmLaser, void* param_2);
void pppConstruct2YmLaser(void* pppYmLaser, void* param_2);
void pppDestructYmLaser(void* pppYmLaser, void* param_2);
void pppFrameYmLaser(void* pppYmLaser, void* param_2, void* param_3);
void pppRenderYmLaser(void* pppYmLaser, void* param_2, void* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMLASER_H_
