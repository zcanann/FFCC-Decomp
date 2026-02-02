#ifndef _FFCC_PPPCOLACCELE_H_
#define _FFCC_PPPCOLACCELE_H_

struct _pppPObject;

#ifdef __cplusplus
extern "C" {
#endif

void pppColAccele(_pppPObject* obj1, void* data1, _pppPObject* obj2);
void pppColAcceleCon(_pppPObject* obj, void* data);

#ifdef __cplusplus
}
#endif

#endif // _FFCC_PPPCOLACCELE_H_
