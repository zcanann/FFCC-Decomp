// Function: MusicHeadAdd__9CRedEntryFP12RedMusicHEAD
// Entry: 801c29b8
// Size: 168 bytes

int MusicHeadAdd__9CRedEntryFP12RedMusicHEAD(undefined4 param_1,int param_2)

{
  int *piVar1;
  int iVar2;
  
  piVar1 = (int *)MusicOldChoice__9CRedEntryFv();
  if ((piVar1 != (int *)0x0) && (piVar1[3] != 0)) {
    MusicOldClear__9CRedEntryFv(param_1);
    piVar1 = (int *)MusicOldChoice__9CRedEntryFv(param_1);
  }
  iVar2 = 0;
  if (piVar1 != (int *)0x0) {
    piVar1[2] = param_2;
    piVar1[3] = *(int *)(param_2 + 0x10);
    *piVar1 = (int)*(short *)(param_2 + 4);
    MusicHistoryAdd__9CRedEntryFv(param_1);
    piVar1[1] = 1;
    iVar2 = param_2;
  }
  return iVar2;
}

