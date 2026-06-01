#ifndef _FFCC_PPPCOLACCELE_H_
#define _FFCC_PPPCOLACCELE_H_

struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppColAccele(_pppPObject* object, void* data, _pppCtrlTable* ctrlTable);
void pppColAcceleCon(_pppPObject* object, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLACCELE_H_
