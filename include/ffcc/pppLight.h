#ifndef _PPP_LIGHT_H_
#define _PPP_LIGHT_H_


struct _pppPObject;
struct _pppCtrlTable;
struct PppLightStep;

#ifdef __cplusplus
extern "C" {
#endif

void pppLight(struct _pppPObject* param1, void* param2, void* param3);
void pppLightCon(struct _pppPObject* object, _pppCtrlTable* ctrlTable);
void pppLightCon3(struct _pppPObject* object, _pppCtrlTable* ctrlTable);

#ifdef __cplusplus
}
#endif

#endif // _PPP_LIGHT_H_
