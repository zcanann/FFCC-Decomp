// Function: TRKTargetStepOutOfRange
// Entry: 801ac214
// Size: 184 bytes

undefined4 TRKTargetStepOutOfRange(undefined4 param_1,undefined4 param_2,int param_3)

{
  undefined4 uVar1;
  
  if (param_3 == 0) {
    DAT_8021cfe8 = 1;
    DAT_8021cfe4 = 1;
    DAT_8021cff0 = param_1;
    DAT_8021cff4 = param_2;
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

