// Function: SetFogColor__8CGraphicF8_GXColor
// Entry: 80017f48
// Size: 36 bytes

void SetFogColor__8CGraphicF8_GXColor(CGraphic *graphic,undefined *param_2)

{
  undefined uVar1;
  undefined uVar2;
  
  uVar1 = param_2[1];
  graphic->field_0x7200 = *param_2;
  uVar2 = param_2[2];
  graphic->field_0x7201 = uVar1;
  uVar1 = param_2[3];
  graphic->field_0x7202 = uVar2;
  graphic->field_0x7203 = uVar1;
  return;
}

