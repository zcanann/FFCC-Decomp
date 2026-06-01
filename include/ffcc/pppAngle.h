#ifndef _FFCC_PPPANGLE_H_
#define _FFCC_PPPANGLE_H_

struct _pppCtrlTable;
struct _pppPObject;

#ifdef __cplusplus
extern "C" {
#endif

void pppAngle(_pppPObject* dest, void* src, _pppCtrlTable* ctrlTable);
void pppAngleCon(_pppPObject* dest, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif
