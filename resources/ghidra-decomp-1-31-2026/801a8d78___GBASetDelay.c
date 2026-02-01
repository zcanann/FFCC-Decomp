// Function: __GBASetDelay
// Entry: 801a8d78
// Size: 36 bytes

undefined8 __GBASetDelay(int param_1,undefined4 param_2,undefined4 param_3,undefined4 param_4)

{
  undefined8 uVar1;
  
  uVar1 = *(undefined8 *)(&DAT_80328350 + param_1 * 0x40);
  (&DAT_80328354)[param_1 * 0x40] = param_4;
  (&DAT_80328350)[param_1 * 0x40] = param_3;
  return uVar1;
}

