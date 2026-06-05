#ifndef _PPP_SCREENBREAK_H_
#define _PPP_SCREENBREAK_H_

struct _pppCtrlTable;
struct _pppPObject;

typedef _pppPObject pppScreenBreak;

struct PScreenBreak;
struct VScreenBreak;

#ifdef __cplusplus
extern "C" {
#endif

void pppConScreenBreak(pppScreenBreak*, _pppCtrlTable*);
void pppCon2ScreenBreak(pppScreenBreak*, _pppCtrlTable*);
void pppDesScreenBreak(pppScreenBreak*, _pppCtrlTable*);
void pppFrameScreenBreak(pppScreenBreak*, PScreenBreak*, _pppCtrlTable*);
void pppRenderScreenBreak(pppScreenBreak*, PScreenBreak*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCREENBREAK_H_
