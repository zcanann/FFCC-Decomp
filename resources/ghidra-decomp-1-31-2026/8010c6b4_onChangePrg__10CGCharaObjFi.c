// Function: onChangePrg__10CGCharaObjFi
// Entry: 8010c6b4
// Size: 76 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void onChangePrg__10CGCharaObjFi(CGPrgObj *param_1,int param_2)

{
  if (param_2 == 0) {
    changeStat__8CGPrgObjFiii(param_1,0,0,0);
    CancelAnim__8CGObjectFi(&param_1->object,0);
  }
  return;
}

