// Function: TRKTargetInterrupt
// Entry: 801ac488
// Size: 400 bytes

undefined4 TRKTargetInterrupt(int *param_1)

{
  bool bVar1;
  undefined4 uVar2;
  
  uVar2 = 0;
  if ((*param_1 < 5) && (2 < *param_1)) {
    if (DAT_8021cfe4 != 0) {
      bVar1 = true;
      DAT_8032a3c0 = DAT_8032a3c0 & 0xfffffbff;
      if ((DAT_8021cfe4 != 0) && ((DAT_8032a4c0 & 0xffff) == 0xd00)) {
        if (DAT_8021cfe8 == 1) {
          if ((DAT_8021cff0 <= DAT_8032a248) && (DAT_8032a248 <= DAT_8021cff4)) {
            bVar1 = false;
          }
        }
        else if (((DAT_8021cfe8 < 1) && (-1 < DAT_8021cfe8)) && (DAT_8021cfec != 0)) {
          bVar1 = false;
        }
      }
      if (bVar1) {
        DAT_8021cfe4 = 0;
      }
      else {
        DAT_8021cfe4 = 1;
        MWTRACE(1,s_TargetDoStep___801e6b80);
        DAT_8032a3c0 = DAT_8032a3c0 | 0x400;
        if ((DAT_8021cfe8 == 0) || (DAT_8021cfe8 == 0x10)) {
          DAT_8021cfec = DAT_8021cfec + -1;
        }
        DAT_8032a1bc = 0;
      }
    }
    if (DAT_8021cfe4 == 0) {
      DAT_8032a1bc = 1;
      uVar2 = TRKDoNotifyStopped(0x90);
    }
  }
  return uVar2;
}

