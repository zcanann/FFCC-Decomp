#ifndef _FFCC_PPPANGMOVE_H_
#define _FFCC_PPPANGMOVE_H_

struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppAngMove(void* dest, void* src, _pppCtrlTable* ctrlTable);
void pppAngMoveCon(void* dest, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif
