// Function: ReportSeLoop__10CRedDriverFi
// Entry: 801bf854
// Size: 108 bytes

undefined4 ReportSeLoop__10CRedDriverFi(CRedDriver *redDriver,int param_2)

{
  int *piVar1;
  
  piVar1 = *(int **)(DAT_8032f3f0 + 0xdbc);
  while ((*piVar1 == 0 ||
         (((param_2 != -1 && (param_2 != piVar1[0x3e])) || ((piVar1[0x40] & 1U) == 0))))) {
    piVar1 = piVar1 + 0x55;
    if ((int *)(*(int *)(DAT_8032f3f0 + 0xdbc) + 0x2a80) <= piVar1) {
      return 0;
    }
  }
  return 1;
}

