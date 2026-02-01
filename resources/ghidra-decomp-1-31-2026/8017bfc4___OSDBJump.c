// Function: __OSDBJump
// Entry: 8017bfc4
// Size: 4 bytes

undefined4 __OSDBJump(void)

{
  undefined4 uVar1;
  undefined4 *puVar2;
  undefined8 uVar3;
  
  uVar3 = func_0x00000060();
  puVar2 = (undefined4 *)(DAT_8032ef44 + ((uint)((ulonglong)uVar3 >> 0x20) & 0xff) * 4);
  uVar1 = *puVar2;
  *puVar2 = (int)uVar3;
  return uVar1;
}

