#ifndef _PPP_ERASECHARAPARTS_H_
#define _PPP_ERASECHARAPARTS_H_

struct _pppCtrlTable;
struct pppEraseCharaParts;
struct pppEraseCharaPartsUnkB;

#ifdef __cplusplus
extern "C" {
#endif

void pppConstructEraseCharaParts(pppEraseCharaParts*, _pppCtrlTable*);
void pppDestructEraseCharaParts(pppEraseCharaParts*, _pppCtrlTable*);
void pppFrameEraseCharaParts(pppEraseCharaParts*, pppEraseCharaPartsUnkB*, _pppCtrlTable*);

#ifdef __cplusplus
}
#endif

#endif // _PPP_ERASECHARAPARTS_H_
