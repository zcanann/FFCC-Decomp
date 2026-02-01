// Function: SearchMusicSequence__9CRedEntryFi
// Entry: 801c2610
// Size: 92 bytes

int SearchMusicSequence__9CRedEntryFi(int param_1,int param_2)

{
  uint uVar1;
  int *piVar2;
  
  piVar2 = *(int **)(param_1 + 8);
  while ((piVar2[3] == 0 || (*piVar2 != param_2))) {
    piVar2 = piVar2 + 4;
    if ((int *)(*(int *)(param_1 + 8) + 0x40) <= piVar2) {
      return -1;
    }
  }
  uVar1 = (int)piVar2 - *(int *)(param_1 + 8);
  return ((int)uVar1 >> 4) + (uint)((int)uVar1 < 0 && (uVar1 & 0xf) != 0);
}

