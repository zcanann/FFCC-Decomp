// Function: AXAcquireVoice
// Entry: 80191968
// Size: 372 bytes

int * AXAcquireVoice(uint param_1,int param_2,int param_3)

{
  int iVar1;
  undefined4 uVar2;
  int *piVar3;
  int *piVar4;
  int *piVar5;
  int *piVar6;
  undefined4 *puVar7;
  
  puVar7 = &DAT_8030cce0;
  uVar2 = OSDisableInterrupts();
  piVar4 = DAT_8030cce0;
  if (DAT_8030cce0 == (int *)0x0) {
    iVar1 = param_1 - 1;
    piVar5 = &DAT_8030cd64;
    if (1 < param_1) {
      do {
        puVar7 = puVar7 + 1;
        piVar3 = (int *)*puVar7;
        piVar4 = (int *)0x0;
        if (piVar3 != (int *)0x0) {
          piVar6 = (int *)*piVar5;
          if (piVar3 == piVar6) {
            *piVar5 = 0;
            *puVar7 = 0;
            piVar4 = piVar3;
          }
          else if (piVar6 != (int *)0x0) {
            *piVar5 = piVar6[1];
            *(undefined4 *)*piVar5 = 0;
            piVar4 = piVar6;
          }
        }
        if (piVar4 != (int *)0x0) {
          if (*(short *)((int)piVar4 + 0x146) == 1) {
            piVar4[8] = 1;
          }
          if ((code *)piVar4[4] != (code *)0x0) {
            (*(code *)piVar4[4])(piVar4);
          }
          break;
        }
        piVar5 = piVar5 + 1;
        iVar1 = iVar1 + -1;
      } while (iVar1 != 0);
    }
  }
  else {
    DAT_8030cce0 = (int *)*DAT_8030cce0;
  }
  if (piVar4 != (int *)0x0) {
    piVar5 = (int *)(&DAT_8030cce0 + param_1);
    *piVar4 = *piVar5;
    piVar4[1] = 0;
    if (*piVar4 == 0) {
      (&DAT_8030cd60)[param_1] = piVar4;
      *piVar5 = (int)piVar4;
    }
    else {
      *(int **)(*piVar5 + 4) = piVar4;
      *piVar5 = (int)piVar4;
    }
    piVar4[3] = param_1;
    piVar4[4] = param_2;
    piVar4[5] = param_3;
    __AXSetPBDefault(piVar4);
  }
  OSRestoreInterrupts(uVar2);
  return piVar4;
}

