#ifndef _PPP_YMDRAWMDLTEXANM_H_
#define _PPP_YMDRAWMDLTEXANM_H_

// Forward declarations
struct pppModelSt;

void SetUpPerUV(pppModelSt*, float&, float&);

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructYmDrawMdlTexAnm(void);
void pppDestructYmDrawMdlTexAnm(void);
void pppFrameYmDrawMdlTexAnm(void);
void pppRenderYmDrawMdlTexAnm(void);

#ifdef __cplusplus
}
#endif

#endif // _PPP_YMDRAWMDLTEXANM_H_
