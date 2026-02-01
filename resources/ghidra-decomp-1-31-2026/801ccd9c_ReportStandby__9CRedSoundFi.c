// Function: ReportStandby__9CRedSoundFi
// Entry: 801ccd9c
// Size: 152 bytes

undefined4 ReportStandby__9CRedSoundFi(CRedSound *redSound,int param_2)

{
  int iVar1;
  
  if (param_2 == 0) {
    iVar1 = 0;
    do {
      if ((&DAT_8032e17c)[iVar1] != 0) {
        return 1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x40);
  }
  else {
    iVar1 = 0;
    do {
      if (param_2 == (&DAT_8032e17c)[iVar1]) {
        return 1;
      }
      iVar1 = iVar1 + 1;
    } while (iVar1 < 0x40);
  }
  return 0;
}

