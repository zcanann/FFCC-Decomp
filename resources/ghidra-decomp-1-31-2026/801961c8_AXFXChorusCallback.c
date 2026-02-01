// Function: AXFXChorusCallback
// Entry: 801961c8
// Size: 848 bytes

void AXFXChorusCallback(undefined4 *param_1,undefined4 *param_2)

{
  uint uVar1;
  undefined4 *puVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  undefined4 *puVar5;
  undefined4 *puVar6;
  undefined4 *puVar7;
  undefined4 *puVar8;
  undefined4 *puVar9;
  undefined4 *puVar10;
  uint uVar11;
  int iVar12;
  
  puVar5 = (undefined4 *)*param_1;
  puVar7 = (undefined4 *)param_1[1];
  puVar9 = (undefined4 *)param_1[2];
  uVar1 = (*(byte *)(param_2 + 9) + 1) % 3;
  puVar2 = (undefined4 *)param_2[uVar1];
  puVar3 = (undefined4 *)param_2[uVar1 + 3];
  puVar4 = (undefined4 *)param_2[uVar1 + 6];
  iVar12 = 0x14;
  do {
    *puVar2 = *puVar5;
    *puVar3 = *puVar7;
    *puVar4 = *puVar9;
    puVar2[1] = puVar5[1];
    puVar3[1] = puVar7[1];
    puVar4[1] = puVar9[1];
    puVar2[2] = puVar5[2];
    puVar3[2] = puVar7[2];
    puVar4[2] = puVar9[2];
    puVar2[3] = puVar5[3];
    puVar3[3] = puVar7[3];
    puVar4[3] = puVar9[3];
    puVar2[4] = puVar5[4];
    puVar3[4] = puVar7[4];
    puVar4[4] = puVar9[4];
    puVar2[5] = puVar5[5];
    puVar3[5] = puVar7[5];
    puVar4[5] = puVar9[5];
    puVar6 = puVar5 + 7;
    puVar2[6] = puVar5[6];
    puVar8 = puVar7 + 7;
    puVar3[6] = puVar7[6];
    puVar10 = puVar9 + 7;
    puVar4[6] = puVar9[6];
    puVar5 = puVar5 + 8;
    puVar2[7] = *puVar6;
    puVar2 = puVar2 + 8;
    puVar7 = puVar7 + 8;
    puVar3[7] = *puVar8;
    puVar3 = puVar3 + 8;
    puVar9 = puVar9 + 8;
    puVar4[7] = *puVar10;
    puVar4 = puVar4 + 8;
    iVar12 = iVar12 + -1;
  } while (iVar12 != 0);
  param_2[0x21] = ((int)param_2[0x18] >> 0x10) + 1;
  param_2[0x20] = param_2[0x18] << 0x10;
  iVar12 = param_2[0x19];
  param_2[0x19] = iVar12 + -1;
  if (iVar12 + -1 == 0) {
    param_2[0x19] = param_2[0x1a];
    param_2[0x18] = -param_2[0x18];
  }
  uVar11 = 0;
  do {
    param_2[0x1f] = param_2[0x17];
    param_2[0x1e] = param_2[0x16];
    if (uVar11 == 1) {
      param_2[0x1c] = param_2[3];
      param_2[0x1b] = param_1[1];
      param_2[0x1d] = param_2 + 0xe;
    }
    else if ((int)uVar11 < 1) {
      if (-1 < (int)uVar11) {
        param_2[0x1c] = *param_2;
        param_2[0x1b] = *param_1;
        param_2[0x1d] = param_2 + 10;
      }
    }
    else if ((int)uVar11 < 3) {
      param_2[0x1c] = param_2[6];
      param_2[0x1b] = param_1[2];
      param_2[0x1d] = param_2 + 0x12;
    }
    iVar12 = param_2[0x21];
    if (iVar12 == 1) {
      do_src2(param_2 + 0x1b);
    }
    else if ((iVar12 < 1) && (-1 < iVar12)) {
      do_src1(param_2 + 0x1b);
    }
    uVar11 = uVar11 + 1;
  } while (uVar11 < 3);
  param_2[0x17] = (uint)param_2[0x1f] % 0x1e0;
  param_2[0x16] = param_2[0x1e];
  *(char *)(param_2 + 9) = (char)uVar1;
  return;
}

