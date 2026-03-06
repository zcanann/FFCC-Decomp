#ifndef _FFCC_PPPANGLE_H_
#define _FFCC_PPPANGLE_H_

struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppAngle(void* dest, void* src, _pppCtrlTable* ctrlTable);
void pppAngleCon(void* dest, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif
