// Function: RenderQuadNoTex__5CUtilF3Vec3Vec8_GXColor
// Entry: 80024748
// Size: 172 bytes

void RenderQuadNoTex__5CUtilF3Vec3Vec8_GXColor
               (undefined4 param_1,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4)

{
  undefined4 uVar1;
  undefined4 uVar2;
  
  GXBegin(0x80,7,4);
  DAT_cc008000 = *param_2;
  uVar1 = param_2[2];
  DAT_cc008000 = param_2[1];
  uVar2 = *param_4;
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  DAT_cc008000 = *param_3;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  DAT_cc008000 = *param_3;
  DAT_cc008000 = param_3[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_3[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = uVar2;
  return;
}

