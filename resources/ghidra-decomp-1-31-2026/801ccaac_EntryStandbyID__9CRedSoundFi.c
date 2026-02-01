// Function: EntryStandbyID__9CRedSoundFi
// Entry: 801ccaac
// Size: 80 bytes

int * EntryStandbyID__9CRedSoundFi(CRedSound *redSound,int param_2)

{
  int *piVar1;
  
  piVar1 = &DAT_8032e17c;
  do {
    if (*piVar1 == 0) {
      *piVar1 = param_2;
      return piVar1;
    }
    piVar1 = piVar1 + 1;
  } while (piVar1 < (int *)0x8032e27c);
  return (int *)0x0;
}

