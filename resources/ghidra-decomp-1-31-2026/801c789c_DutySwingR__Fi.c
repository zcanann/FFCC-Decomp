// Function: DutySwingR__Fi
// Entry: 801c789c
// Size: 60 bytes

undefined4 DutySwingR__Fi(uint param_1)

{
  undefined4 uVar1;
  
  if (((param_1 ^ 0x200) & 0x200) == 0) {
    uVar1 = 0x10000;
  }
  else {
    uVar1 = 0xffff0000;
  }
  return uVar1;
}

