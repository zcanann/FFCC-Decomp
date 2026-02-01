// Function: RedNewA__Fiii
// Entry: 801c01e8
// Size: 576 bytes

int RedNewA__Fiii(int param_1,int param_2,int param_3)

{
  uint uVar1;
  uint uVar2;
  int iVar3;
  undefined4 uVar4;
  int iVar5;
  int iVar6;
  int iVar7;
  int iVar8;
  int *piVar9;
  int *piVar10;
  int *piVar11;
  
  if (((param_1 < 1) || (DAT_8032f4a4 == (int *)0x0)) || (DAT_8032f494 == 0)) {
    iVar3 = 0;
  }
  else if (DAT_8032f4a4[0x7ff] < 1) {
    uVar4 = OSDisableInterrupts();
    iVar6 = DAT_8032f494 + param_2;
    if (param_3 == 0) {
      param_3 = DAT_8032f49c;
    }
    param_3 = param_3 - param_2;
    uVar1 = param_1 + 0x1fU & 0xffffffe0;
    iVar7 = -1;
    piVar9 = (int *)0x0;
    for (piVar10 = DAT_8032f4a4; (piVar10[1] != 0 && (*piVar10 < iVar6)); piVar10 = piVar10 + 2) {
    }
    iVar5 = param_3;
    iVar3 = iVar6;
    iVar8 = iVar6;
    piVar11 = piVar10;
    if (piVar10[1] != 0) {
      for (; (piVar11[1] != 0 && (piVar11 < DAT_8032f4a4 + 0x800)); piVar11 = piVar11 + 2) {
        if (iVar8 < iVar6 + param_3) {
          if (((int)(iVar8 + uVar1) <= *piVar11) &&
             (iVar7 = iVar8, piVar9 = piVar11, *piVar11 - iVar8 < iVar5)) {
            iVar5 = *piVar11 - iVar8;
          }
        }
        else {
          piVar11 = DAT_8032f4a4 + 0x800;
        }
        iVar8 = *piVar11 + piVar11[1];
      }
      iVar3 = iVar7;
      piVar10 = piVar9;
      if ((((piVar11[1] == 0) && (piVar11 < DAT_8032f4a4 + 0x800)) &&
          (iVar7 = (iVar6 + param_3) - iVar8, (int)uVar1 <= iVar7)) && (iVar7 < iVar5)) {
        iVar3 = iVar8;
        piVar10 = piVar11;
      }
    }
    if ((piVar10 == (int *)0x0) || ((uint)(iVar6 + param_3) < iVar3 + uVar1)) {
      OSRestoreInterrupts(uVar4);
      iVar3 = 0;
    }
    else {
      if (0 < piVar10[1]) {
        uVar2 = (int)DAT_8032f4a4 + (0x2000 - (int)(piVar10 + 2));
        iVar6 = ((int)uVar2 >> 3) + (uint)((int)uVar2 < 0 && (uVar2 & 7) != 0);
        if (0 < iVar6) {
          memmove(piVar10 + 2,piVar10,iVar6 * 8);
        }
      }
      *piVar10 = iVar3;
      piVar10[1] = uVar1;
      OSRestoreInterrupts(uVar4);
    }
  }
  else {
    if (DAT_8032f408 != 0) {
      OSReport(s__s_sA_Memory_Bank_Full____s_801e78b5,&DAT_801e78a3,&DAT_80333d20,&DAT_80333d28);
      fflush(&DAT_8021d1a8);
    }
    iVar3 = 0;
  }
  return iVar3;
}

