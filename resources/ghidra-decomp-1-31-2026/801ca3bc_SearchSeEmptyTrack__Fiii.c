// Function: SearchSeEmptyTrack__Fiii
// Entry: 801ca3bc
// Size: 252 bytes

int * SearchSeEmptyTrack__Fiii(int param_1,undefined4 param_2,int param_3)

{
  int *piVar1;
  int *piVar2;
  int *piVar3;
  int iVar4;
  int *piVar5;
  
  piVar5 = (int *)(DAT_8032f3f0 + 0xdbc);
  if (param_3 != 0) {
    _EraseAttribute__Fii(param_2,param_3);
  }
  do {
    piVar3 = (int *)(*piVar5 + 0x292c);
    piVar1 = piVar3;
    iVar4 = param_1;
    do {
      while (((piVar2 = piVar1, iVar4 = iVar4 + -1, iVar4 != 0 && (*piVar2 == 0)) &&
             ((*(byte *)((int)piVar2 + 0x26) & 2) == 0))) {
        piVar1 = piVar2 + -0x55;
      }
      if ((*piVar2 != 0) || ((*(byte *)((int)piVar2 + 0x26) & 2) != 0)) {
        iVar4 = 1;
        piVar3 = piVar2;
      }
      piVar3 = piVar3 + -0x55;
    } while ((iVar4 != 0) && (piVar1 = piVar3, iVar4 = param_1, (int *)*piVar5 <= piVar2));
  } while ((piVar2 < (int *)*piVar5) && (iVar4 = _EraseTime__Fi(param_2), iVar4 != 0));
  if (piVar2 < (int *)*piVar5) {
    piVar2 = (int *)0x0;
  }
  return piVar2;
}

