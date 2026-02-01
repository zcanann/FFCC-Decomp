// Function: SetFog__8CGraphicFii
// Entry: 80017ea8
// Size: 148 bytes

void SetFog__8CGraphicFii(CGraphic *graphic,int param_2,int param_3)

{
  undefined4 *puVar1;
  undefined4 uVar2;
  undefined4 local_18;
  float local_14;
  float local_10;
  
  if (&stack0x00000000 != (undefined *)0x10) {
    local_10 = (float)CameraPcs._256_4_;
  }
  if (&stack0x00000000 != (undefined *)0x14) {
    local_14 = (float)CameraPcs._260_4_;
  }
  if (param_3 == 0) {
    puVar1 = (undefined4 *)&graphic->field_0x7200;
  }
  else {
    puVar1 = (undefined4 *)&DAT_8032e3e8;
  }
  local_18 = *puVar1;
  uVar2 = 0;
  if (param_2 != 0) {
    uVar2 = 2;
  }
  GXSetFog((double)graphic->fogParamA,(double)graphic->fogParamB,(double)local_10,(double)local_14,
           uVar2,&local_18);
  return;
}

