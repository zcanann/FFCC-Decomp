// Function: IsMenuCharaAnimIdle__8CMenuPcsFi
// Entry: 800fc1f4
// Size: 24 bytes

uint IsMenuCharaAnimIdle__8CMenuPcsFi(CMenuPcs *menuPcs,int param_2)

{
  uint uVar1;
  
  uVar1 = countLeadingZeros(*(undefined4 *)(*(int *)&menuPcs->field_0x844 + param_2 * 0x14));
  return uVar1 >> 5 & 0xff;
}

