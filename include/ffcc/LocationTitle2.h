#ifndef _FFCC_LOCATIONTITLE2_H_
#define _FFCC_LOCATIONTITLE2_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppLocationTitle2;
typedef _pppCtrlTable pppLocationTitle2UnkC;

struct pppLocationTitle2UnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructLocationTitle2(pppLocationTitle2*, pppLocationTitle2UnkC*);
void pppDestructLocationTitle2(pppLocationTitle2*, pppLocationTitle2UnkC*);
void pppFrameLocationTitle2(pppLocationTitle2*, pppLocationTitle2UnkB*, pppLocationTitle2UnkC*);
void pppRenderLocationTitle2(pppLocationTitle2*, pppLocationTitle2UnkB*, pppLocationTitle2UnkC*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_LOCATIONTITLE2_H_
