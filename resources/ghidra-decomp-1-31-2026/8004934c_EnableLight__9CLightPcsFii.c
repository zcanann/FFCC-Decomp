// Function: EnableLight__9CLightPcsFii
// Entry: 8004934c
// Size: 152 bytes

void EnableLight__9CLightPcsFii(int param_1,uint param_2,undefined4 param_3)

{
  uint uVar1;
  undefined4 uVar2;
  
  if (param_2 == 0) {
    uVar2 = 0;
  }
  else {
    uVar2 = *(undefined4 *)(param_1 + 0xb4);
  }
  uVar1 = countLeadingZeros(param_3);
  GXSetChanCtrl(0,(-param_2 | param_2) >> 0x1f,0,uVar1 >> 5,uVar2,2,1);
  uVar1 = countLeadingZeros(param_3);
  GXSetChanCtrl(2,(-param_2 | param_2) >> 0x1f,0,uVar1 >> 5,0,0,2);
  return;
}

