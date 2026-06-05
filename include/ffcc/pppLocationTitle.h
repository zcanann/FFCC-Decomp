#ifndef _PPP_LOCATIONTITLE_H_
#define _PPP_LOCATIONTITLE_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppLocationTitle;
typedef _pppCtrlTable pppLocationTitleUnkC;

struct pppLocationTitleUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkC* param_2);
void pppDestructLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkC* param_2);
void pppFrameLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3);
void pppRenderLocationTitle(pppLocationTitle* param_1, pppLocationTitleUnkB* param_2, pppLocationTitleUnkC* param_3);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LOCATIONTITLE_H_
