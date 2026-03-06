#ifndef _PPP_KELNS_H_
#define _PPP_KELNS_H_

struct _pppPObjLink;
struct _pppPObject;
struct _pppCtrlTable;

#ifdef __cplusplus
extern "C" {
#endif

void pppKeLnsLpCon(void* pObject, void* pPart);
void pppKeLnsLpCon2(void* pObject, void* pPart);
void pppKeLnsLpDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable);
void pppKeLnsFlsCon(_pppPObjLink* obj, _pppCtrlTable* ctrlTable);
void pppKeLnsFlsDraw(_pppPObject* obj, void* stepData, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_KELNS_H_
