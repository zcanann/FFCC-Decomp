// Function: statKorobi__10CGPartyObjFv
// Entry: 8011cab8
// Size: 292 bytes

/* WARNING: Struct "CGBaseObj": ignoring overlapping field "vtable" */

void statKorobi__10CGPartyObjFv(CGPrgObj *param_1)

{
  int iVar1;
  
  iVar1 = param_1->m_subState;
  if (iVar1 == 1) {
    if (param_1->m_subFrame == 0) {
      reqAnim__8CGPrgObjFiii(param_1,0x1f,0,0);
    }
    iVar1 = isLoopAnim__8CGPrgObjFv(param_1);
    if (iVar1 != 0) {
      changeSubStat__8CGPrgObjFi(param_1,2);
    }
  }
  else if (iVar1 < 1) {
    if (-1 < iVar1) {
      if (param_1->m_subFrame == 0) {
        damageDelete__10CGCharaObjFv();
        carry__10CGPartyObjFiP8CGObjecti((CGPartyObj *)param_1,1,(CGObject *)0x0,1);
        reqAnim__8CGPrgObjFiii(param_1,0x1e,0,0);
      }
      iVar1 = isLoopAnim__8CGPrgObjFv(param_1);
      if (iVar1 != 0) {
        changeSubStat__8CGPrgObjFi(param_1,1);
      }
    }
  }
  else if (iVar1 < 3) {
    if (param_1->m_subFrame == 0) {
      reqAnim__8CGPrgObjFiii(param_1,0x20,0,0);
    }
    iVar1 = isLoopAnim__8CGPrgObjFv(param_1);
    if (iVar1 != 0) {
      changeStat__8CGPrgObjFiii(param_1,0,0,0);
    }
  }
  return;
}

