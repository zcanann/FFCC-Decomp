// Function: Init__14CFunnyShapePcsFv
// Entry: 8004e5e4
// Size: 184 bytes

void Init__14CFunnyShapePcsFv(CFunnyShapePcs *funnyShapePcs)

{
  float fVar1;
  float fVar2;
  byte bVar3;
  uint uVar4;
  uint uVar5;
  
  funnyShapePcs->field_0x8 = 0x7f;
  uVar4 = countLeadingZeros(0);
  funnyShapePcs->field_0x9 = 0x7f;
  funnyShapePcs->field_0xa = 0x7f;
  uVar5 = countLeadingZeros(1);
  bVar3 = -((byte)(uVar4 >> 5) & 1) & 0x3f;
  funnyShapePcs->field_0xb = 0xff;
  fVar2 = FLOAT_8032fd24;
  funnyShapePcs->field_0xc = bVar3;
  fVar1 = FLOAT_8032fd14;
  uVar4 = countLeadingZeros(2);
  funnyShapePcs->field_0xd = bVar3;
  funnyShapePcs->field_0xe = bVar3;
  bVar3 = -((byte)(uVar5 >> 5) & 1) & 0x3f;
  funnyShapePcs->field_0xf = 0xff;
  *(float *)&funnyShapePcs->field_0x18 = fVar2;
  *(float *)&funnyShapePcs->field_0x1c = fVar2;
  *(float *)&funnyShapePcs->field_0x20 = fVar1;
  funnyShapePcs->field_0x10 = bVar3;
  funnyShapePcs->field_0x11 = bVar3;
  funnyShapePcs->field_0x12 = bVar3;
  bVar3 = -((byte)(uVar4 >> 5) & 1) & 0x3f;
  funnyShapePcs->field_0x13 = 0xff;
  *(float *)&funnyShapePcs->field_0x24 = fVar2;
  *(float *)&funnyShapePcs->field_0x28 = fVar2;
  *(float *)&funnyShapePcs->field_0x2c = fVar1;
  funnyShapePcs->field_0x14 = bVar3;
  funnyShapePcs->field_0x15 = bVar3;
  funnyShapePcs->field_0x16 = bVar3;
  funnyShapePcs->field_0x17 = 0xff;
  *(float *)&funnyShapePcs->field_0x30 = fVar2;
  *(float *)&funnyShapePcs->field_0x34 = fVar2;
  *(float *)&funnyShapePcs->field_0x38 = fVar1;
  return;
}

