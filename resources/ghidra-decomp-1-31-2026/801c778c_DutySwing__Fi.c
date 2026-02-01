// Function: DutySwing__Fi
// Entry: 801c778c
// Size: 56 bytes

undefined4 DutySwing__Fi(uint param_1)

{
  undefined4 uVar1;
  
  if ((param_1 & 0x200) == 0) {
    uVar1 = 0x10000;
  }
  else {
    uVar1 = 0xffff0000;
  }
  return uVar1;
}

