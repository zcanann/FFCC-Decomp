#ifndef _PPP_KELNS_H_
#define _PPP_KELNS_H_

struct _pppPObjLink;
struct _pppPObject;
struct _pppCtrlTable;
struct pppNoStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeLnsLpCon(_pppPObject* obj, _pppCtrlTable* ctrlTable);
void pppKeLnsLpCon2(_pppPObject* obj, _pppCtrlTable* ctrlTable);
void pppKeLnsLpDraw(_pppPObject* obj, pppNoStep* stepData, _pppCtrlTable* ctrlTable);
void pppKeLnsFlsCon(_pppPObjLink* obj, _pppCtrlTable* ctrlTable);
void pppKeLnsFlsDraw(_pppPObject* obj, pppNoStep* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KELNS_H_
