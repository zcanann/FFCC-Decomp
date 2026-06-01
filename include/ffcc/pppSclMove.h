#ifndef _PPP_SCLMOVE_H_
#define _PPP_SCLMOVE_H_

struct _pppCtrlTable;
struct _pppPObject;

#ifdef __cplusplus
extern "C" {
#endif

void pppSclMove(_pppPObject* param1, void* param2, _pppCtrlTable* param3);
void pppSclMoveCon(_pppPObject* param1, _pppCtrlTable* param2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCLMOVE_H_
