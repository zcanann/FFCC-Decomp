// Function: Init__9CLightPcsFv
// Entry: 8004a294
// Size: 180 bytes

void Init__9CLightPcsFv(int param_1)

{
  float fVar1;
  float fVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  
  *(undefined *)(param_1 + 0x433c) = 0x3f;
  uVar4 = countLeadingZeros(0);
  *(undefined *)(param_1 + 0x433d) = 0x3f;
  fVar1 = FLOAT_8032fc14;
  *(undefined *)(param_1 + 0x433e) = 0x3f;
  fVar2 = FLOAT_8032fc2c;
  uVar5 = countLeadingZeros(1);
  bVar3 = -((byte)(uVar4 >> 5) & 1) & 0x3f;
  *(undefined *)(param_1 + 0x433f) = 0xff;
  *(byte *)(param_1 + 0x4340) = bVar3;
  uVar4 = countLeadingZeros(2);
  *(byte *)(param_1 + 0x4341) = bVar3;
  *(byte *)(param_1 + 0x4342) = bVar3;
  bVar3 = -((byte)(uVar5 >> 5) & 1) & 0x3f;
  *(undefined *)(param_1 + 0x4343) = 0xff;
  *(float *)(param_1 + 0x434c) = fVar1;
  *(float *)(param_1 + 0x4350) = fVar1;
  *(float *)(param_1 + 0x4354) = fVar2;
  *(byte *)(param_1 + 0x4344) = bVar3;
  *(byte *)(param_1 + 0x4345) = bVar3;
  *(byte *)(param_1 + 0x4346) = bVar3;
  bVar3 = -((byte)(uVar4 >> 5) & 1) & 0x3f;
  *(undefined *)(param_1 + 0x4347) = 0xff;
  *(float *)(param_1 + 0x4358) = fVar1;
  *(float *)(param_1 + 0x435c) = fVar1;
  *(float *)(param_1 + 0x4360) = fVar2;
  *(byte *)(param_1 + 0x4348) = bVar3;
  *(byte *)(param_1 + 0x4349) = bVar3;
  *(byte *)(param_1 + 0x434a) = bVar3;
  *(undefined *)(param_1 + 0x434b) = 0xff;
  *(float *)(param_1 + 0x4364) = fVar1;
  *(float *)(param_1 + 0x4368) = fVar1;
  *(float *)(param_1 + 0x436c) = fVar2;
  return;
}

