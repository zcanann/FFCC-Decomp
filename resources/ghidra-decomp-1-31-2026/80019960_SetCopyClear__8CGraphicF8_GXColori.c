// Function: SetCopyClear__8CGraphicF8_GXColori
// Entry: 80019960
// Size: 84 bytes

void SetCopyClear__8CGraphicF8_GXColori(CGraphic *graphic,undefined4 *param_2)

{
  undefined uVar1;
  undefined uVar2;
  undefined4 local_8 [2];
  
  uVar1 = *(undefined *)((int)param_2 + 1);
  graphic->field_0x735f = *(undefined *)param_2;
  uVar2 = *(undefined *)((int)param_2 + 2);
  graphic->field_0x7360 = uVar1;
  uVar1 = *(undefined *)((int)param_2 + 3);
  graphic->field_0x7361 = uVar2;
  local_8[0] = *param_2;
  graphic->field_0x7362 = uVar1;
  GXSetCopyClear(local_8,0xffffff);
  return;
}

