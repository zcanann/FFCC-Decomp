// Function: SetMapTexAnim__14CMapTexAnimSetFiiii
// Entry: 8004f910
// Size: 276 bytes

void SetMapTexAnim__14CMapTexAnimSetFiiii
               (int param_1,undefined4 param_2,undefined4 param_3,int param_4,undefined param_5)

{
  double dVar1;
  int iVar2;
  bool bVar3;
  int iVar4;
  int iVar5;
  int iVar6;
  
  bVar3 = false;
  iVar4 = param_1;
  for (iVar6 = 0; dVar1 = DOUBLE_8032fd30, iVar6 < *(short *)(param_1 + 8); iVar6 = iVar6 + 1) {
    iVar5 = *(int *)(iVar4 + 0xc);
    if (*(short *)(iVar5 + 0x12) == (short)param_2) {
      if (*(char *)(iVar5 + 0x15) == '\0') {
        *(short *)(iVar5 + 0xe) = (short)param_3;
        *(float *)(iVar5 + 0x1c) =
             (float)((double)CONCAT44(0x43300000,(int)(short)param_3 ^ 0x80000000) - dVar1);
        iVar2 = param_4;
        if (*(short *)(iVar5 + 0xc) < param_4) {
          iVar2 = (int)*(short *)(iVar5 + 0xc);
        }
        *(short *)(iVar5 + 0x10) = (short)iVar2;
        *(undefined *)(iVar5 + 0x16) = param_5;
      }
      else {
        *(undefined4 *)(iVar5 + 0x30) = param_3;
        *(undefined4 *)(iVar5 + 0x2c) = param_3;
        iVar2 = param_4;
        if (*(int *)(iVar5 + 0x38) < param_4) {
          iVar2 = *(int *)(iVar5 + 0x38);
        }
        *(int *)(iVar5 + 0x34) = iVar2;
        *(undefined *)(iVar5 + 0x27) = param_5;
        *(undefined *)(iVar5 + 0x28) = 1;
      }
      bVar3 = true;
    }
    iVar4 = iVar4 + 4;
  }
  if ((!bVar3) && (System.m_execParam != 0)) {
    Printf__7CSystemFPce(&System,&DAT_801d7e98,param_2);
  }
  return;
}

