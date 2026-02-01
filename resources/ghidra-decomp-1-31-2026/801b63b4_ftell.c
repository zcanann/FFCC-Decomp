// Function: ftell
// Entry: 801b63b4
// Size: 228 bytes

int ftell(int param_1)

{
  char cVar1;
  uint uVar2;
  ushort uVar3;
  int iVar4;
  int iVar5;
  char *pcVar6;
  int iVar7;
  
  __begin_critical_region(2);
  iVar4 = 0;
  uVar3 = *(ushort *)(param_1 + 4) >> 6 & 7;
  if (((uVar3 == 1) || (uVar3 == 2)) && (*(char *)(param_1 + 10) == '\0')) {
    uVar2 = (uint)(*(byte *)(param_1 + 8) >> 5);
    if (uVar2 == 0) {
      iVar7 = *(int *)(param_1 + 0x18);
    }
    else {
      pcVar6 = *(char **)(param_1 + 0x1c);
      iVar5 = *(int *)(param_1 + 0x24) - (int)pcVar6;
      iVar7 = *(int *)(param_1 + 0x34) + iVar5;
      if (2 < uVar2) {
        iVar4 = uVar2 - 2;
        iVar7 = iVar7 - iVar4;
      }
      if ((*(byte *)(param_1 + 5) >> 3 & 1) == 0) {
        for (iVar5 = iVar5 - iVar4; iVar5 != 0; iVar5 = iVar5 + -1) {
          cVar1 = *pcVar6;
          pcVar6 = pcVar6 + 1;
          if (cVar1 == '\n') {
            iVar7 = iVar7 + 1;
          }
        }
      }
    }
  }
  else {
    iVar7 = -1;
    DAT_8032f390 = 0x28;
  }
  __end_critical_region(2);
  return iVar7;
}

