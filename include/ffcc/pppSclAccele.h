#ifndef _PPP_SCLACCELE_H_
#define _PPP_SCLACCELE_H_


struct _pppCtrlTable;
struct PppSclAcceleStep;
#ifdef __cplusplus
extern "C" {
#endif

void pppSclAccele(void* arg1, struct PppSclAcceleStep* arg2, struct _pppCtrlTable* arg3);
void pppSclAcceleCon(void* arg1, struct _pppCtrlTable* arg2);

#ifdef __cplusplus
}
#endif

#endif // _PPP_SCLACCELE_H_
