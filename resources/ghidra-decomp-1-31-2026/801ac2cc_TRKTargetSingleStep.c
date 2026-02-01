// Function: TRKTargetSingleStep
// Entry: 801ac2cc
// Size: 172 bytes

undefined4 TRKTargetSingleStep(int param_1,int param_2)

{
  undefined4 uVar1;
  
  if (param_2 == 0) {
    DAT_8021cfe8 = 0;
    DAT_8021cfe4 = 1;
    DAT_8021cfec = param_1;
    MWTRACE(1,s_TargetDoStep___801e6b80);
    DAT_8032a3c0 = DAT_8032a3c0 | 0x400;
    if ((DAT_8021cfe8 == 0) || (DAT_8021cfe8 == 0x10)) {
      DAT_8021cfec = DAT_8021cfec + -1;
    }
    uVar1 = 0;
    DAT_8032a1bc = 0;
  }
  else {
    uVar1 = 0x703;
  }
  return uVar1;
}

