// Function: SePlayState__10CRedDriverFi
// Entry: 801bf384
// Size: 288 bytes

int * SePlayState__10CRedDriverFi(CRedDriver *redDriver,int param_2)

{
  undefined4 uVar1;
  int *piVar2;
  int *piVar3;
  
  uVar1 = OSDisableInterrupts();
  piVar3 = *(int **)(DAT_8032f3f0 + 0xdbc);
  do {
    piVar2 = piVar3;
    if ((*piVar2 != 0) && ((param_2 == -1 || (piVar2[0x3e] == param_2)))) break;
    piVar3 = piVar2 + 0x55;
    piVar2 = (int *)0x0;
  } while (piVar3 < (int *)(*(int *)(DAT_8032f3f0 + 0xdbc) + 0x2a80));
  piVar3 = DAT_8032f3dc;
  if (piVar2 == (int *)0x0) {
    while (DAT_8032f3d8 != piVar3) {
      if (((*piVar3 != 0) &&
          ((((code *)*piVar3 == _SeBlockPlay__FPi || ((code *)*piVar3 == _SeSepPlay__FPi)) ||
           ((code *)*piVar3 == _SeSepPlaySequence__FPi)))) &&
         ((param_2 == -1 || (param_2 == piVar3[1])))) {
        piVar2 = (int *)0x1;
        break;
      }
      piVar3 = piVar3 + 8;
      if (piVar3 == DAT_8032f3d4 + 0x800) {
        piVar3 = DAT_8032f3d4;
      }
    }
  }
  OSRestoreInterrupts(uVar1);
  return piVar2;
}

