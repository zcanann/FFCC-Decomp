// Function: SetTexShadowColor__9CCharaPcsF8_GXColor
// Entry: 800b91fc
// Size: 36 bytes

void SetTexShadowColor__9CCharaPcsF8_GXColor(CCharaPcs *charaPcs,undefined *param_2)

{
  undefined uVar1;
  undefined uVar2;
  
  uVar1 = param_2[1];
  charaPcs->field_0x18c = *param_2;
  uVar2 = param_2[2];
  charaPcs->field_0x18d = uVar1;
  uVar1 = param_2[3];
  charaPcs->field_0x18e = uVar2;
  charaPcs->field_0x18f = uVar1;
  return;
}

