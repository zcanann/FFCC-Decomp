// Function: CompaInit__8CMenuPcsFv
// Entry: 801620f8
// Size: 616 bytes

void CompaInit__8CMenuPcsFv(CMenuPcs *menuPcs)

{
  float fVar1;
  float fVar2;
  float fVar3;
  int iVar4;
  int iVar5;
  
  memset(*(undefined4 *)&menuPcs->field_0x850,0,0x1008);
  fVar1 = FLOAT_80333000;
  iVar4 = *(int *)&menuPcs->field_0x850 + 8;
  iVar5 = 8;
  do {
    *(float *)(iVar4 + 0x14) = fVar1;
    *(float *)(iVar4 + 0x54) = fVar1;
    *(float *)(iVar4 + 0x94) = fVar1;
    *(float *)(iVar4 + 0xd4) = fVar1;
    *(float *)(iVar4 + 0x114) = fVar1;
    *(float *)(iVar4 + 0x154) = fVar1;
    *(float *)(iVar4 + 0x194) = fVar1;
    *(float *)(iVar4 + 0x1d4) = fVar1;
    iVar4 = iVar4 + 0x200;
    iVar5 = iVar5 + -1;
  } while (iVar5 != 0);
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 0x24) = 0x52;
  *(undefined4 *)(iVar4 + 0x20) = 4;
  *(undefined2 *)(iVar4 + 8) = 0x28;
  *(undefined2 *)(iVar4 + 10) = 0x30;
  fVar1 = FLOAT_80332ff8;
  *(undefined2 *)(iVar4 + 0xc) = 0x198;
  fVar2 = FLOAT_80333000;
  *(undefined2 *)(iVar4 + 0xe) = 0x18;
  *(float *)(iVar4 + 0x10) = fVar1;
  *(float *)(iVar4 + 0x14) = fVar1;
  *(float *)(iVar4 + 0x1c) = fVar2;
  *(undefined4 *)(iVar4 + 0x2c) = 5;
  *(undefined4 *)(iVar4 + 0x30) = 5;
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 100) = 0x51;
  *(undefined2 *)(iVar4 + 0x48) = 0x28;
  *(undefined2 *)(iVar4 + 0x4a) = 0x48;
  *(undefined2 *)(iVar4 + 0x4c) = 0x198;
  *(undefined2 *)(iVar4 + 0x4e) = 200;
  *(float *)(iVar4 + 0x50) = fVar1;
  *(float *)(iVar4 + 0x54) = fVar1;
  *(float *)(iVar4 + 0x5c) = fVar2;
  *(undefined4 *)(iVar4 + 0x6c) = 5;
  *(undefined4 *)(iVar4 + 0x70) = 5;
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 0xa4) = 0x52;
  *(undefined2 *)(iVar4 + 0x88) = 0x28;
  *(undefined2 *)(iVar4 + 0x8a) = 0x110;
  *(undefined2 *)(iVar4 + 0x8c) = 0x198;
  *(undefined2 *)(iVar4 + 0x8e) = 0x18;
  *(float *)(iVar4 + 0x90) = fVar1;
  *(float *)(iVar4 + 0x94) = fVar1;
  *(float *)(iVar4 + 0x9c) = fVar2;
  *(undefined4 *)(iVar4 + 0xac) = 5;
  *(undefined4 *)(iVar4 + 0xb0) = 5;
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 0xe4) = 0x5e;
  *(undefined2 *)(iVar4 + 200) = 0x10;
  *(undefined2 *)(iVar4 + 0xca) = 0xe;
  *(undefined2 *)(iVar4 + 0xcc) = 0x30;
  *(undefined2 *)(iVar4 + 0xce) = 0x30;
  *(float *)(iVar4 + 0xd0) = fVar1;
  *(float *)(iVar4 + 0xd4) = fVar1;
  *(float *)(iVar4 + 0xdc) = fVar2;
  *(undefined4 *)(iVar4 + 0xec) = 0;
  *(undefined4 *)(iVar4 + 0xf0) = 5;
  fVar3 = FLOAT_8033303c;
  fVar2 = FLOAT_80333038;
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 0x124) = 0x5e;
  *(undefined2 *)(iVar4 + 0x108) = 0x15;
  *(undefined2 *)(iVar4 + 0x10c) = 0x30;
  *(undefined2 *)(iVar4 + 0x10e) = 0x30;
  *(short *)(iVar4 + 0x10a) = 0x150 - *(short *)(iVar4 + 0x10e);
  *(float *)(iVar4 + 0x110) = fVar1;
  *(float *)(iVar4 + 0x114) = fVar1;
  *(float *)(iVar4 + 0x11c) = fVar2;
  *(undefined4 *)(iVar4 + 300) = 0;
  *(undefined4 *)(iVar4 + 0x130) = 5;
  iVar4 = *(int *)&menuPcs->field_0x850;
  *(undefined4 *)(iVar4 + 0x174) = 2;
  *(undefined4 *)(iVar4 + 0x164) = 0x2e;
  *(undefined2 *)(iVar4 + 0x148) = 0x10;
  *(undefined2 *)(iVar4 + 0x14a) = 8;
  *(undefined2 *)(iVar4 + 0x14c) = 0x30;
  *(undefined2 *)(iVar4 + 0x14e) = 0x140;
  *(float *)(iVar4 + 0x150) = fVar3;
  *(float *)(iVar4 + 0x154) = fVar1;
  *(undefined4 *)(iVar4 + 0x16c) = 0;
  *(undefined4 *)(iVar4 + 0x170) = 5;
  **(undefined2 **)&menuPcs->field_0x850 = 6;
  *(undefined2 *)(*(int *)&menuPcs->field_0x82c + 0x26) = 0;
  *(undefined *)(*(int *)&menuPcs->field_0x82c + 0xb) = 1;
  return;
}

