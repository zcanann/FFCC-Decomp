#ifndef _PPP_LERPPOS_H_
#define _PPP_LERPPOS_H_

// Forward declarations for structures
struct pppLerpPos;
struct UnkB;
struct UnkC;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLerpPos(struct pppLerpPos* pppLerpPos, struct UnkC* param_2);
void pppDestructLerpPos(struct pppLerpPos* pppLerpPos, struct UnkC* param_2);
void pppFrameLerpPos(struct pppLerpPos* pppLerpPos, struct UnkB* param_2, struct UnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LERPPOS_H_
