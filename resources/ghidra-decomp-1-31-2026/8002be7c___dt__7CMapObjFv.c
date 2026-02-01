// Function: __dt__7CMapObjFv
// Entry: 8002be7c
// Size: 128 bytes

int __dt__7CMapObjFv(int param_1,short param_2)

{
  int *piVar1;
  
  if (param_1 != 0) {
    piVar1 = *(int **)(param_1 + 0xec);
    if (piVar1 != (int *)0x0) {
      if (piVar1 != (int *)0x0) {
        (**(code **)(*piVar1 + 8))(piVar1,1);
      }
      *(undefined4 *)(param_1 + 0xec) = 0;
    }
    Init__7CMapObjFv(param_1);
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

