// Function: Draw__9CLine
// Entry: 800c86f8
// Size: 320 bytes

void Draw__9CLine(int param_1)

{
  undefined4 *puVar1;
  float *pfVar2;
  undefined4 *puVar3;
  undefined4 *puVar4;
  int iVar5;
  uint uVar6;
  
  if (*(uint *)(param_1 + 0x18) != 0) {
    GXBegin(0xb0,0,*(uint *)(param_1 + 0x18) & 0xffff);
    uVar6 = 0;
    iVar5 = param_1;
    while (uVar6 < *(uint *)(param_1 + 0x18)) {
      puVar3 = (undefined4 *)(iVar5 + 0x38);
      uVar6 = uVar6 + 1;
      puVar4 = (undefined4 *)(iVar5 + 0x34);
      puVar1 = (undefined4 *)(iVar5 + 0x30);
      iVar5 = iVar5 + 0xc;
      DAT_cc008000 = *puVar1;
      DAT_cc008000 = *puVar4;
      DAT_cc008000 = *puVar3;
    }
    GXBegin(0xb0,0,*(uint *)(param_1 + 0x18) & 0xffff);
    uVar6 = 0;
    iVar5 = param_1;
    while (uVar6 < *(uint *)(param_1 + 0x18)) {
      pfVar2 = (float *)(iVar5 + 0x34);
      uVar6 = uVar6 + 1;
      puVar3 = (undefined4 *)(iVar5 + 0x38);
      puVar4 = (undefined4 *)(iVar5 + 0x30);
      iVar5 = iVar5 + 0xc;
      DAT_cc008000 = *puVar4;
      DAT_cc008000 = FLOAT_80330cf4 + *pfVar2;
      DAT_cc008000 = *puVar3;
    }
    GXBegin(0xa8,0,(*(uint *)(param_1 + 0x18) & 0x7fff) << 1);
    uVar6 = 0;
    iVar5 = param_1;
    while (uVar6 < *(uint *)(param_1 + 0x18)) {
      uVar6 = uVar6 + 1;
      DAT_cc008000 = *(undefined4 *)(iVar5 + 0x30);
      DAT_cc008000 = *(undefined4 *)(iVar5 + 0x34);
      DAT_cc008000 = *(undefined4 *)(iVar5 + 0x38);
      pfVar2 = (float *)(iVar5 + 0x34);
      puVar3 = (undefined4 *)(iVar5 + 0x38);
      puVar4 = (undefined4 *)(iVar5 + 0x30);
      iVar5 = iVar5 + 0xc;
      DAT_cc008000 = *puVar4;
      DAT_cc008000 = FLOAT_80330cf4 + *pfVar2;
      DAT_cc008000 = *puVar3;
    }
  }
  return;
}

