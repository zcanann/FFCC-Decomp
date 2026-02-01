// Function: InitFrame0Info__8CMenuPcsFv
// Entry: 80101658
// Size: 212 bytes

void InitFrame0Info__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  float fVar2;
  int iVar3;
  
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 4) = 0x10;
  fVar2 = FLOAT_803313e8;
  fVar1 = FLOAT_803313dc;
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 6) = 0x10;
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 8) = 0xe8;
  *(undefined2 *)(*(int *)&menuPcs->field_0x820 + 10) = 0x168;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0xc) = fVar1;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0x10) = fVar1;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0x14) = fVar2;
  *(float *)(*(int *)&menuPcs->field_0x820 + 0x18) = fVar2;
  *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x1c) = 0;
  iVar3 = *(int *)&menuPcs->field_0x820;
  *(undefined2 *)(iVar3 + 0x20) = *(undefined2 *)(iVar3 + 4);
  *(undefined2 *)(iVar3 + 0x22) = *(undefined2 *)(iVar3 + 6);
  *(undefined2 *)(iVar3 + 0x24) = *(undefined2 *)(iVar3 + 8);
  *(undefined2 *)(iVar3 + 0x26) = *(undefined2 *)(iVar3 + 10);
  *(undefined4 *)(iVar3 + 0x28) = *(undefined4 *)(iVar3 + 0xc);
  *(undefined4 *)(iVar3 + 0x2c) = *(undefined4 *)(iVar3 + 0x10);
  *(undefined4 *)(iVar3 + 0x30) = *(undefined4 *)(iVar3 + 0x14);
  *(undefined4 *)(iVar3 + 0x34) = *(undefined4 *)(iVar3 + 0x18);
  *(undefined4 *)(iVar3 + 0x38) = *(undefined4 *)(iVar3 + 0x1c);
  iVar3 = *(int *)&menuPcs->field_0x820;
  *(short *)(iVar3 + 0x20) = 0x280 - (*(short *)(iVar3 + 8) + *(short *)(iVar3 + 4));
  *(undefined4 *)(*(int *)&menuPcs->field_0x820 + 0x38) = 8;
  return;
}

