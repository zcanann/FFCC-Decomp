#ifndef _PPP_FILTER_H_
#define _PPP_FILTER_H_

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructFilter(void);
void pppDestructFilter(void);
void pppFrameFilter(void);
void pppRenderFilter(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_FILTER_H_
