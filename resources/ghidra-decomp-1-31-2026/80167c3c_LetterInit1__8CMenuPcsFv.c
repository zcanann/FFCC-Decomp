// Function: LetterInit1__8CMenuPcsFv
// Entry: 80167c3c
// Size: 408 bytes

void LetterInit1__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  double dVar1;
  float fVar2;
  double dVar3;
  int iVar4;
  int iVar5;
  
  memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
  fVar2 = FLOAT_803330f8;
  iVar4 = *(int *)&menuPcs->field_0x850 + 8;
  iVar5 = 8;
  do {
    *(float *)(iVar4 + 0x14) = fVar2;
    *(float *)(iVar4 + 0x54) = fVar2;
    *(float *)(iVar4 + 0x94) = fVar2;
    *(float *)(iVar4 + 0xd4) = fVar2;
    *(float *)(iVar4 + 0x114) = fVar2;
    *(float *)(iVar4 + 0x154) = fVar2;
    *(float *)(iVar4 + 0x194) = fVar2;
    *(float *)(iVar4 + 0x1d4) = fVar2;
    iVar4 = iVar4 + 0x200;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 0x24) = 0x5f;
  *(undefined2 *)(iVar4 + 0xc) = 0x238;
  dVar3 = DOUBLE_803330c8;
  *(undefined2 *)(iVar4 + 0xe) = 0x178;
  fVar2 = FLOAT_803330bc;
  dVar1 = DOUBLE_803330a8;
  *(short *)(iVar4 + 8) =
       (short)(int)(((double)CONCAT44(0x43300000,0x280U - (int)*(short *)(iVar4 + 0xc) ^ 0x80000000)
                    - dVar3) * DOUBLE_803330a8);
  *(short *)(iVar4 + 10) =
       (short)(int)(((double)CONCAT44(0x43300000,0x1c0U - (int)*(short *)(iVar4 + 0xe) ^ 0x80000000)
                    - dVar3) * dVar1);
  *(float *)(iVar4 + 0x10) = fVar2;
  *(float *)(iVar4 + 0x14) = fVar2;
  *(undefined4 *)(iVar4 + 0x2c) = 0;
  *(undefined4 *)(iVar4 + 0x30) = 10;
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 100) = 0x3e;
  *(undefined2 *)(iVar4 + 0x4c) = 0xa8;
  *(undefined2 *)(iVar4 + 0x4e) = 0x60;
  *(undefined2 *)(iVar4 + 0x48) = 0x20;
  *(short *)(iVar4 + 0x4a) = 0x1a0 - *(short *)(iVar4 + 0x4e);
  *(float *)(iVar4 + 0x50) = fVar2;
  *(float *)(iVar4 + 0x54) = fVar2;
  *(undefined4 *)(iVar4 + 0x6c) = 0;
  *(undefined4 *)(iVar4 + 0x70) = 10;
  **(undefined2 **)&menuPcs->field_0x850 = 2;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x22) = 0;
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  return;
}

