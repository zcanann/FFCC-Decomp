// Function: GXGetViewportv
// Entry: 801a6800
// Size: 56 bytes

void GXGetViewportv(undefined4 *param_1)

{
  int iVar1;
  
  iVar1 = DAT_80333828;
  *param_1 = *(undefined4 *)(DAT_80333828 + 0x43c);
  param_1[1] = *(undefined4 *)(iVar1 + 0x440);
  param_1[2] = *(undefined4 *)(iVar1 + 0x444);
  param_1[3] = *(undefined4 *)(iVar1 + 0x448);
  param_1[4] = *(undefined4 *)(iVar1 + 0x44c);
  param_1[5] = *(undefined4 *)(iVar1 + 0x450);
  return;
}

