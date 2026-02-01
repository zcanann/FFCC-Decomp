// Function: ExPPC_FindExceptionRecord__FPcP15MWExceptionInfo
// Entry: 801b1878
// Size: 516 bytes

void ExPPC_FindExceptionRecord__FPcP15MWExceptionInfo(uint param_1,int *param_2)

{
  bool bVar1;
  int iVar2;
  uint *puVar3;
  int *piVar4;
  uint uVar5;
  ushort *puVar6;
  int iVar7;
  ushort *puVar8;
  uint *puVar9;
  int iVar10;
  int local_28;
  int local_24;
  int local_20;
  int local_18;
  int local_10;
  
  *param_2 = 0;
  param_2[2] = 0;
  piVar4 = DAT_8032b400;
  if (DAT_8032b408 != 0) {
    for (; piVar4[3] != 0; piVar4 = piVar4 + 4) {
      if (((uint)piVar4[2] <= param_1) && (param_1 < (uint)(piVar4[2] + piVar4[3]))) {
        local_28 = *piVar4;
        local_24 = piVar4[1];
        bVar1 = true;
        local_20 = 0;
        local_18 = 0;
        local_10 = DAT_8032b404;
        goto LAB_801b190c;
      }
    }
  }
  bVar1 = false;
LAB_801b190c:
  if (bVar1) {
    iVar10 = 0;
    param_2[3] = local_20;
    param_1 = param_1 - local_20;
    param_2[4] = local_18;
    param_2[5] = local_10;
    iVar2 = (local_24 - local_28) / 0xc + (local_24 - local_28 >> 0x1f);
    iVar2 = iVar2 - (iVar2 >> 0x1f);
    while (iVar10 <= iVar2) {
      iVar7 = (iVar10 + iVar2) / 2;
      puVar9 = (uint *)(local_28 + iVar7 * 0xc);
      uVar5 = *puVar9;
      if (param_1 < uVar5) {
        iVar2 = iVar7 + -1;
      }
      else {
        if (param_1 <= uVar5 + (puVar9[1] & 0x7fffffff)) {
          param_2[1] = local_20 + uVar5;
          if ((int)puVar9[1] < 0) {
            puVar3 = puVar9 + 2;
          }
          else {
            puVar3 = (uint *)(local_18 + puVar9[2]);
          }
          *param_2 = (int)puVar3;
          puVar8 = (ushort *)*param_2;
          param_1 = param_1 - *puVar9;
          if ((*puVar8 >> 3 & 1) != 0) {
            puVar9 = (uint *)(puVar8 + 2);
            while( true ) {
              uVar5 = *puVar9;
              if (uVar5 == 0) {
                return;
              }
              if ((uVar5 <= param_1) && (param_1 <= uVar5 + (uint)*(ushort *)(puVar9 + 1) * 4))
              break;
              puVar9 = puVar9 + 2;
            }
            param_2[2] = (int)puVar8 + (uint)*(ushort *)((int)puVar9 + 6);
            return;
          }
          puVar6 = puVar8 + 1;
          while( true ) {
            if (*puVar6 == 0) {
              return;
            }
            if ((*puVar6 <= param_1) && (param_1 <= puVar6[1])) break;
            puVar6 = puVar6 + 3;
          }
          param_2[2] = (int)puVar8 + (uint)puVar6[2];
          return;
        }
        iVar10 = iVar7 + 1;
      }
    }
  }
  return;
}

