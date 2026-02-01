// Function: Init__18CMaterialEditorPcsFv
// Entry: 8004c3c4
// Size: 452 bytes

void Init__18CMaterialEditorPcsFv(CMaterialEditorPcs *materialEditorPcs)

{
  float fVar1;
  float fVar2;
  float fVar3;
  uint uVar4;
  uint uVar5;
  byte bVar6;
  CMaterialEditorPcs *pCVar7;
  int iVar8;
  
  materialEditorPcs->field_0x8 = 0x7f;
  uVar4 = countLeadingZeros(0);
  materialEditorPcs->field_0x9 = 0x7f;
  materialEditorPcs->field_0xa = 0x7f;
  fVar2 = FLOAT_8032fcd8;
  uVar5 = countLeadingZeros(1);
  bVar6 = -((byte)(uVar4 >> 5) & 1) & 0x3f;
  materialEditorPcs->field_0xb = 0xff;
  fVar3 = FLOAT_8032fcdc;
  materialEditorPcs->field_0xc = bVar6;
  fVar1 = FLOAT_8032fcc8;
  uVar4 = countLeadingZeros(2);
  materialEditorPcs->field_0xd = bVar6;
  materialEditorPcs->field_0xe = bVar6;
  bVar6 = -((byte)(uVar5 >> 5) & 1) & 0x3f;
  materialEditorPcs->field_0xf = 0xff;
  *(float *)&materialEditorPcs->field_0x18 = fVar2;
  *(float *)&materialEditorPcs->field_0x1c = fVar2;
  *(float *)&materialEditorPcs->field_0x20 = fVar3;
  materialEditorPcs->field_0x10 = bVar6;
  materialEditorPcs->field_0x11 = bVar6;
  materialEditorPcs->field_0x12 = bVar6;
  bVar6 = -((byte)(uVar4 >> 5) & 1) & 0x3f;
  materialEditorPcs->field_0x13 = 0xff;
  *(float *)&materialEditorPcs->field_0x24 = fVar2;
  *(float *)&materialEditorPcs->field_0x28 = fVar2;
  *(float *)&materialEditorPcs->field_0x2c = fVar3;
  materialEditorPcs->field_0x14 = bVar6;
  materialEditorPcs->field_0x15 = bVar6;
  materialEditorPcs->field_0x16 = bVar6;
  materialEditorPcs->field_0x17 = 0xff;
  *(float *)&materialEditorPcs->field_0x30 = fVar2;
  *(float *)&materialEditorPcs->field_0x34 = fVar2;
  *(float *)&materialEditorPcs->field_0x38 = fVar3;
  *(float *)&materialEditorPcs->field_0x44 = fVar2;
  *(float *)&materialEditorPcs->field_0x40 = fVar2;
  *(float *)&materialEditorPcs->field_0x3c = fVar2;
  *(float *)&materialEditorPcs->field_0x50 = fVar2;
  *(float *)&materialEditorPcs->field_0x4c = fVar2;
  *(float *)&materialEditorPcs->field_0x48 = fVar2;
  *(float *)&materialEditorPcs->field_0x5c = fVar1;
  *(float *)&materialEditorPcs->field_0x58 = fVar1;
  *(float *)&materialEditorPcs->field_0x54 = fVar1;
  *(undefined4 *)&materialEditorPcs->field_0xbc = 0;
  iVar8 = 2;
  pCVar7 = materialEditorPcs;
  do {
    *(undefined4 *)&pCVar7->field_0x2bc = 0;
    *(undefined4 *)&pCVar7->field_0x2fc = 0;
    *(undefined4 *)&pCVar7->field_0x23c = 0;
    *(undefined4 *)&pCVar7->field_0x33c = 0;
    *(undefined4 *)&pCVar7->field_0x37c = 0;
    *(undefined4 *)&pCVar7->field_0x27c = 0;
    *(undefined4 *)&pCVar7->field_0x2c0 = 0;
    *(undefined4 *)&pCVar7->field_0x300 = 0;
    *(undefined4 *)&pCVar7->field_0x240 = 0;
    *(undefined4 *)&pCVar7->field_0x340 = 0;
    *(undefined4 *)&pCVar7->field_0x380 = 0;
    *(undefined4 *)&pCVar7->field_0x280 = 0;
    *(undefined4 *)&pCVar7->field_0x2c4 = 0;
    *(undefined4 *)&pCVar7->field_0x304 = 0;
    *(undefined4 *)&pCVar7->field_0x244 = 0;
    *(undefined4 *)&pCVar7->field_0x344 = 0;
    *(undefined4 *)&pCVar7->field_0x384 = 0;
    *(undefined4 *)&pCVar7->field_0x284 = 0;
    *(undefined4 *)&pCVar7->field_0x2c8 = 0;
    *(undefined4 *)&pCVar7->field_0x308 = 0;
    *(undefined4 *)&pCVar7->field_0x248 = 0;
    *(undefined4 *)&pCVar7->field_0x348 = 0;
    *(undefined4 *)&pCVar7->field_0x388 = 0;
    *(undefined4 *)&pCVar7->field_0x288 = 0;
    *(undefined4 *)&pCVar7->field_0x2cc = 0;
    *(undefined4 *)&pCVar7->field_0x30c = 0;
    *(undefined4 *)&pCVar7->field_0x24c = 0;
    *(undefined4 *)&pCVar7->field_0x34c = 0;
    *(undefined4 *)&pCVar7->field_0x38c = 0;
    *(undefined4 *)&pCVar7->field_0x28c = 0;
    *(undefined4 *)&pCVar7->field_0x2d0 = 0;
    *(undefined4 *)&pCVar7->field_0x310 = 0;
    *(undefined4 *)&pCVar7->field_0x250 = 0;
    *(undefined4 *)&pCVar7->field_0x350 = 0;
    *(undefined4 *)&pCVar7->field_0x390 = 0;
    *(undefined4 *)&pCVar7->field_0x290 = 0;
    *(undefined4 *)&pCVar7->field_0x2d4 = 0;
    *(undefined4 *)&pCVar7->field_0x314 = 0;
    *(undefined4 *)&pCVar7->field_0x254 = 0;
    *(undefined4 *)&pCVar7->field_0x354 = 0;
    *(undefined4 *)&pCVar7->field_0x394 = 0;
    *(undefined4 *)&pCVar7->field_0x294 = 0;
    *(undefined4 *)&pCVar7->field_0x2d8 = 0;
    *(undefined4 *)&pCVar7->field_0x318 = 0;
    *(undefined4 *)&pCVar7->field_0x258 = 0;
    *(undefined4 *)&pCVar7->field_0x358 = 0;
    *(undefined4 *)&pCVar7->field_0x398 = 0;
    *(undefined4 *)&pCVar7->field_0x298 = 0;
    pCVar7 = (CMaterialEditorPcs *)&pCVar7->field_0x20;
    iVar8 = iVar8 + -1;
  } while (iVar8 != 0);
  materialEditorPcs->field_0x3bc = 0;
  return;
}

