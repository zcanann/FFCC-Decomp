// Function: StreamPlayState__10CRedDriverFi
// Entry: 801bf8e8
// Size: 240 bytes

int StreamPlayState__10CRedDriverFi(CRedDriver *redDriver,int param_2)

{
  undefined4 uVar1;
  int iVar2;
  uint uVar3;
  int *piVar4;
  
  uVar1 = OSDisableInterrupts();
  iVar2 = 0;
  uVar3 = DAT_8032f438;
  do {
    if ((*(int *)(uVar3 + 0x10c) != 0) && ((param_2 == -1 || (*(int *)(uVar3 + 0x10c) == param_2))))
    {
      iVar2 = 1;
      break;
    }
    uVar3 = uVar3 + 0x130;
  } while (uVar3 < DAT_8032f438 + 0x4c0);
  piVar4 = DAT_8032f3dc;
  if (iVar2 == 0) {
    while (DAT_8032f3d8 != piVar4) {
      if (((*piVar4 != 0) && ((code *)*piVar4 == _StreamPlay__FPi)) &&
         ((param_2 == -1 || (param_2 == piVar4[1])))) {
        iVar2 = 1;
        break;
      }
      piVar4 = piVar4 + 8;
      if (piVar4 == DAT_8032f3d4 + 0x800) {
        piVar4 = DAT_8032f3d4;
      }
    }
  }
  OSRestoreInterrupts(uVar1);
  return iVar2;
}

