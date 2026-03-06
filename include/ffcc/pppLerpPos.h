#ifndef _PPP_LERPPOS_H_
#define _PPP_LERPPOS_H_

// Forward declarations for structures
struct pppLerpPos;
struct pppLerpPosUnkB;
struct pppLerpPosUnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLerpPos(struct pppLerpPos* pppLerpPos, struct pppLerpPosUnkC* param_2);
void pppDestructLerpPos(struct pppLerpPos* pppLerpPos, struct pppLerpPosUnkC* param_2);
void pppFrameLerpPos(struct pppLerpPos* pppLerpPos, struct pppLerpPosUnkB* param_2, struct pppLerpPosUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LERPPOS_H_

