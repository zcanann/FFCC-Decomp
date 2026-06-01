#ifndef _FFCC_PPPANGMOVE_H_
#define _FFCC_PPPANGMOVE_H_

struct _pppCtrlTable;
struct _pppPObject;

#ifdef __cplusplus
extern "C" {
#endif

void pppAngMove(_pppPObject* dest, void* src, _pppCtrlTable* ctrlTable);
void pppAngMoveCon(_pppPObject* dest, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif
