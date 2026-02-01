// Function: RenderNoTexQuadGrouad__8CGraphicF3Vec3Vec8_GXColor8_GXColor8_GXColor8_GXColor
// Entry: 800177f0
// Size: 180 bytes

void RenderNoTexQuadGrouad__8CGraphicF3Vec3Vec8_GXColor8_GXColor8_GXColor8_GXColor
               (CGraphic *graphic,undefined4 *param_2,undefined4 *param_3,undefined4 *param_4,
               undefined4 *param_5,undefined4 *param_6,undefined4 *param_7)

{
  undefined4 uVar1;
  
  GXBegin(0x80,6,4);
  DAT_cc008000 = *param_2;
  uVar1 = param_2[2];
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = *param_4;
  DAT_cc008000 = *param_3;
  DAT_cc008000 = param_2[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = *param_5;
  DAT_cc008000 = *param_3;
  DAT_cc008000 = param_3[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = *param_7;
  DAT_cc008000 = *param_2;
  DAT_cc008000 = param_3[1];
  DAT_cc008000 = uVar1;
  DAT_cc008000 = *param_6;
  return;
}

