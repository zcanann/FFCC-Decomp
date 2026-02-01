// Function: VIGetTvFormat
// Entry: 8018d1f4
// Size: 104 bytes

undefined4 VIGetTvFormat(void)

{
  undefined4 unaff_r31;
  
  OSDisableInterrupts();
  switch(DAT_8032f124) {
  case 0:
  case 3:
  case 6:
    unaff_r31 = 0;
    break;
  case 1:
  case 4:
    unaff_r31 = 1;
    break;
  case 2:
  case 5:
    unaff_r31 = DAT_8032f124;
  }
  OSRestoreInterrupts();
  return unaff_r31;
}

