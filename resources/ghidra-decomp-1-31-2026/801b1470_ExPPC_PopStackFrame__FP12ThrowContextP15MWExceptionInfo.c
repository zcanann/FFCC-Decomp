// Function: ExPPC_PopStackFrame__FP12ThrowContextP15MWExceptionInfo
// Entry: 801b1470
// Size: 584 bytes

undefined4 ExPPC_PopStackFrame__FP12ThrowContextP15MWExceptionInfo(int param_1,undefined4 *param_2)

{
  undefined8 *puVar1;
  undefined4 *puVar2;
  undefined4 uVar3;
  int iVar4;
  undefined4 *puVar5;
  uint uVar6;
  undefined8 *puVar7;
  int iVar8;
  undefined8 *puVar9;
  undefined8 *puVar10;
  int iVar11;
  uint uVar12;
  
  iVar11 = **(int **)(param_1 + 0x284);
  uVar6 = *(ushort *)*param_2 >> 6 & 0x1f;
  if ((*(ushort *)*param_2 >> 1 & 1) == 0) {
    puVar9 = (undefined8 *)(iVar11 + uVar6 * -8);
    iVar4 = 0x20 - uVar6;
    uVar6 = 0x20 - iVar4;
    puVar10 = (undefined8 *)(param_1 + iVar4 * 0x10);
    if (iVar4 < 0x20) {
      uVar12 = uVar6 >> 3;
      puVar7 = puVar9;
      if (uVar12 != 0) {
        do {
          *puVar10 = *puVar7;
          puVar10[2] = puVar7[1];
          puVar10[4] = puVar7[2];
          puVar10[6] = puVar7[3];
          puVar10[8] = puVar7[4];
          puVar10[10] = puVar7[5];
          puVar10[0xc] = puVar7[6];
          puVar1 = puVar7 + 7;
          puVar7 = puVar7 + 8;
          puVar10[0xe] = *puVar1;
          puVar10 = puVar10 + 0x10;
          uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
        uVar6 = uVar6 & 7;
        if (uVar6 == 0) goto LAB_801b1608;
      }
      do {
        *puVar10 = *puVar7;
        puVar10 = puVar10 + 2;
        uVar6 = uVar6 - 1;
        puVar7 = puVar7 + 1;
      } while (uVar6 != 0);
    }
  }
  else {
    puVar9 = (undefined8 *)(iVar11 + uVar6 * -0x10);
    iVar4 = 0x20 - uVar6;
    uVar6 = 0x20 - iVar4;
    puVar10 = (undefined8 *)(param_1 + iVar4 * 0x10);
    if (iVar4 < 0x20) {
      uVar12 = uVar6 >> 2;
      puVar7 = puVar9;
      if (uVar12 != 0) {
        do {
          *(undefined4 *)(puVar10 + 1) = *(undefined4 *)(puVar7 + 1);
          *(undefined4 *)((int)puVar10 + 0xc) = *(undefined4 *)((int)puVar7 + 0xc);
          *puVar10 = *puVar7;
          *(undefined4 *)(puVar10 + 3) = *(undefined4 *)(puVar7 + 3);
          *(undefined4 *)((int)puVar10 + 0x1c) = *(undefined4 *)((int)puVar7 + 0x1c);
          puVar10[2] = puVar7[2];
          *(undefined4 *)(puVar10 + 5) = *(undefined4 *)(puVar7 + 5);
          *(undefined4 *)((int)puVar10 + 0x2c) = *(undefined4 *)((int)puVar7 + 0x2c);
          puVar10[4] = puVar7[4];
          *(undefined4 *)(puVar10 + 7) = *(undefined4 *)(puVar7 + 7);
          *(undefined4 *)((int)puVar10 + 0x3c) = *(undefined4 *)((int)puVar7 + 0x3c);
          puVar1 = puVar7 + 6;
          puVar7 = puVar7 + 8;
          puVar10[6] = *puVar1;
          puVar10 = puVar10 + 8;
          uVar12 = uVar12 - 1;
        } while (uVar12 != 0);
        uVar6 = uVar6 & 3;
        if (uVar6 == 0) goto LAB_801b1608;
      }
      do {
        *(undefined4 *)(puVar10 + 1) = *(undefined4 *)(puVar7 + 1);
        *(undefined4 *)((int)puVar10 + 0xc) = *(undefined4 *)((int)puVar7 + 0xc);
        *puVar10 = *puVar7;
        puVar10 = puVar10 + 2;
        uVar6 = uVar6 - 1;
        puVar7 = puVar7 + 2;
      } while (uVar6 != 0);
    }
  }
LAB_801b1608:
  iVar4 = 0x20 - ((int)(uint)*(ushort *)*param_2 >> 0xb);
  puVar5 = (undefined4 *)((int)puVar9 + ((int)(uint)*(ushort *)*param_2 >> 0xb) * -4);
  uVar6 = 0x20 - iVar4;
  iVar8 = param_1 + iVar4 * 4;
  if (iVar4 < 0x20) {
    uVar12 = uVar6 >> 3;
    if (uVar12 != 0) {
      do {
        *(undefined4 *)(iVar8 + 0x200) = *puVar5;
        *(undefined4 *)(iVar8 + 0x204) = puVar5[1];
        *(undefined4 *)(iVar8 + 0x208) = puVar5[2];
        *(undefined4 *)(iVar8 + 0x20c) = puVar5[3];
        *(undefined4 *)(iVar8 + 0x210) = puVar5[4];
        *(undefined4 *)(iVar8 + 0x214) = puVar5[5];
        *(undefined4 *)(iVar8 + 0x218) = puVar5[6];
        puVar2 = puVar5 + 7;
        puVar5 = puVar5 + 8;
        *(undefined4 *)(iVar8 + 0x21c) = *puVar2;
        iVar8 = iVar8 + 0x20;
        uVar12 = uVar12 - 1;
      } while (uVar12 != 0);
      uVar6 = uVar6 & 7;
      if (uVar6 == 0) goto LAB_801b16ac;
    }
    do {
      uVar3 = *puVar5;
      puVar5 = puVar5 + 1;
      *(undefined4 *)(iVar8 + 0x200) = uVar3;
      iVar8 = iVar8 + 4;
      uVar6 = uVar6 - 1;
    } while (uVar6 != 0);
  }
LAB_801b16ac:
  *(int *)(param_1 + 0x284) = iVar11;
  return *(undefined4 *)(iVar11 + 4);
}

