#ifndef _FFCC_PPPCHANGETEX_H_
#define _FFCC_PPPCHANGETEX_H_

struct _pppCtrlTable;
struct _pppPObject;
struct ChangeTexStep;

typedef _pppPObject pppChangeTex;
typedef ChangeTexStep pppChangeTexUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppConstruct2ChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppDestructChangeTex(pppChangeTex*, _pppCtrlTable*);
void pppFrameChangeTex(pppChangeTex*, pppChangeTexUnkB*, _pppCtrlTable*);
void pppRenderChangeTex(pppChangeTex*, pppChangeTexUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCHANGETEX_H_
