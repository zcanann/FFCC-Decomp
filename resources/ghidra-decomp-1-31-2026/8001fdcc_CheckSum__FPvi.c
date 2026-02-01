// Function: CheckSum__FPvi
// Entry: 8001fdcc
// Size: 136 bytes

int CheckSum__FPvi(byte *param_1,uint param_2)

{
  byte *pbVar1;
  byte *pbVar2;
  byte *pbVar3;
  byte *pbVar4;
  byte *pbVar5;
  byte *pbVar6;
  byte *pbVar7;
  byte bVar8;
  int iVar9;
  uint uVar10;
  
  iVar9 = 0x12345678;
  if (param_2 != 0) {
    uVar10 = param_2 >> 3;
    if (uVar10 != 0) {
      do {
        bVar8 = *param_1;
        pbVar1 = param_1 + 1;
        pbVar2 = param_1 + 2;
        pbVar3 = param_1 + 3;
        pbVar4 = param_1 + 4;
        pbVar5 = param_1 + 5;
        pbVar6 = param_1 + 6;
        pbVar7 = param_1 + 7;
        param_1 = param_1 + 8;
        iVar9 = iVar9 + (uint)bVar8 + (uint)*pbVar1 + (uint)*pbVar2 + (uint)*pbVar3 + (uint)*pbVar4
                + (uint)*pbVar5 + (uint)*pbVar6 + (uint)*pbVar7;
        uVar10 = uVar10 - 1;
      } while (uVar10 != 0);
      param_2 = param_2 & 7;
      if (param_2 == 0) {
        return iVar9;
      }
    }
    do {
      bVar8 = *param_1;
      param_1 = param_1 + 1;
      iVar9 = iVar9 + (uint)bVar8;
      param_2 = param_2 - 1;
    } while (param_2 != 0);
  }
  return iVar9;
}

