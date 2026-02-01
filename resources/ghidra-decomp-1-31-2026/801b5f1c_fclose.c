// Function: fclose
// Entry: 801b5f1c
// Size: 444 bytes

int fclose(undefined4 *param_1)

{
  ushort uVar1;
  int iVar2;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  
  if (param_1 == (undefined4 *)0x0) {
    iVar2 = -1;
  }
  else {
    uVar1 = *(ushort *)(param_1 + 1) >> 6 & 7;
    if (uVar1 == 0) {
      iVar2 = 0;
    }
    else {
      if (param_1 == (undefined4 *)0x0) {
        iVar2 = __flush_all();
      }
      else if ((*(char *)((int)param_1 + 10) == '\0') && (uVar1 != 0)) {
        if ((*(byte *)(param_1 + 1) >> 3 & 7) == 1) {
          iVar2 = 0;
        }
        else {
          if (2 < *(byte *)(param_1 + 2) >> 5) {
            *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f | 0x40;
          }
          if (*(byte *)(param_1 + 2) >> 5 == 2) {
            param_1[10] = 0;
          }
          if (*(byte *)(param_1 + 2) >> 5 == 1) {
            if ((*(ushort *)(param_1 + 1) >> 6 & 7) == 1) {
              uVar5 = ftell(param_1);
            }
            else {
              uVar5 = 0;
            }
            iVar2 = __flush_buffer(param_1,0);
            if (iVar2 == 0) {
              iVar2 = 0;
              *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f;
              param_1[6] = uVar5;
              param_1[10] = 0;
            }
            else {
              *(undefined *)((int)param_1 + 10) = 1;
              iVar2 = -1;
              param_1[10] = 0;
            }
          }
          else {
            iVar2 = 0;
            *(byte *)(param_1 + 2) = *(byte *)(param_1 + 2) & 0x1f;
          }
        }
      }
      else {
        iVar2 = -1;
      }
      iVar3 = (*(code *)param_1[0x11])(*param_1);
      *(ushort *)(param_1 + 1) = *(ushort *)(param_1 + 1) & 0xfe3f;
      *param_1 = 0;
      if ((*(byte *)(param_1 + 2) >> 4 & 1) != 0) {
        free(param_1[7]);
      }
      uVar4 = 0;
      if ((iVar2 != 0) || (iVar3 != 0)) {
        uVar4 = 1;
      }
      iVar2 = (int)(-uVar4 | uVar4) >> 0x1f;
    }
  }
  return iVar2;
}

