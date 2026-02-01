// Function: __dt__10CTexScrollFv
// Entry: 8003c500
// Size: 364 bytes

char * __dt__10CTexScrollFv(char *param_1,short param_2)

{
  int iVar1;
  
  if (param_1 != (char *)0x0) {
    if (*param_1 == '\x02') {
      iVar1 = *(int *)(param_1 + 0xc);
      if (iVar1 != 0) {
        if (iVar1 != 0) {
          if (*(int *)(iVar1 + 0x18) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x18) = 0;
          }
          if (*(int *)(iVar1 + 0x1c) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x1c) = 0;
          }
          if (*(int *)(iVar1 + 0x20) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x20) = 0;
          }
          if (*(int *)(iVar1 + 0x24) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x24) = 0;
          }
          __dl__FPv(iVar1);
        }
        param_1[0xc] = '\0';
        param_1[0xd] = '\0';
        param_1[0xe] = '\0';
        param_1[0xf] = '\0';
      }
    }
    if (param_1[1] == '\x02') {
      iVar1 = *(int *)(param_1 + 0x10);
      if (iVar1 != 0) {
        if (iVar1 != 0) {
          if (*(int *)(iVar1 + 0x18) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x18) = 0;
          }
          if (*(int *)(iVar1 + 0x1c) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x1c) = 0;
          }
          if (*(int *)(iVar1 + 0x20) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x20) = 0;
          }
          if (*(int *)(iVar1 + 0x24) != 0) {
            __dl__FPv();
            *(undefined4 *)(iVar1 + 0x24) = 0;
          }
          __dl__FPv(iVar1);
        }
        param_1[0x10] = '\0';
        param_1[0x11] = '\0';
        param_1[0x12] = '\0';
        param_1[0x13] = '\0';
      }
    }
    if (0 < param_2) {
      __dl__FPv(param_1);
    }
  }
  return param_1;
}

