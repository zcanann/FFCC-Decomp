// Function: GetStreamPlayPoint__10CRedDriverFiPiPi
// Entry: 801bf9d8
// Size: 156 bytes

undefined4
GetStreamPlayPoint__10CRedDriverFiPiPi
          (CRedDriver *redDriver,int param_2,undefined4 *param_3,undefined4 *param_4)

{
  uint uVar1;
  
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = 0;
  }
  uVar1 = DAT_8032f438;
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = 0;
    uVar1 = DAT_8032f438;
  }
  while ((*(int *)(uVar1 + 0x10c) == 0 || (*(int *)(uVar1 + 0x10c) != param_2))) {
    uVar1 = uVar1 + 0x130;
    if (DAT_8032f438 + 0x4c0 <= uVar1) {
      return 0;
    }
  }
  if (param_3 != (undefined4 *)0x0) {
    *param_3 = *(undefined4 *)(uVar1 + 0x11c);
  }
  if (param_4 != (undefined4 *)0x0) {
    *param_4 = *(undefined4 *)(uVar1 + 0x120);
  }
  return 1;
}

