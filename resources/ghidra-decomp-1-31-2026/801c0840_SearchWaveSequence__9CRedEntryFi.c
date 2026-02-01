// Function: SearchWaveSequence__9CRedEntryFi
// Entry: 801c0840
// Size: 96 bytes

int SearchWaveSequence__9CRedEntryFi(int *param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  
  piVar2 = (int *)*param_1;
  while( true ) {
    if ((int *)(*param_1 + 0x400) <= piVar2) {
      return -1;
    }
    if ((piVar2[3] != 0) && (*piVar2 == param_2)) break;
    piVar2 = piVar2 + 4;
  }
  uVar1 = (int)piVar2 - *param_1;
  return ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
}

