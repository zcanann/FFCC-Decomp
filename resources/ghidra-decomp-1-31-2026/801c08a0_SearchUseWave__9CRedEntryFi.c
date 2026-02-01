// Function: SearchUseWave__9CRedEntryFi
// Entry: 801c08a0
// Size: 208 bytes

undefined4 SearchUseWave__9CRedEntryFi(undefined4 param_1,int param_2)

{
  undefined4 uVar1;
  undefined4 uVar2;
  int *piVar3;
  uint uVar4;
  int *piVar5;
  
  uVar1 = OSDisableInterrupts();
  uVar2 = 0;
  uVar4 = DAT_8032f3f0 + 0x494;
  do {
    if ((-1 < *(int *)(uVar4 + 0x470)) && (*(int *)(uVar4 + 0x47c) == param_2)) {
      uVar2 = 1;
      MusicStop__Fi(*(undefined4 *)(uVar4 + 0x470));
    }
    uVar4 = uVar4 - 0x494;
  } while (DAT_8032f3f0 <= uVar4);
  piVar5 = (int *)(DAT_8032f3f0 + 0xdbc);
  piVar3 = *(int **)(DAT_8032f3f0 + 0xdbc);
  do {
    if (((*piVar3 != 0) && (piVar3[6] != 0)) && (*(short *)(piVar3[6] + 2) == param_2)) {
      uVar2 = 1;
      SeStopID__Fi(piVar3[0x3e]);
    }
    piVar3 = piVar3 + 0x55;
  } while (piVar3 < (int *)(*piVar5 + 0x2a80));
  OSRestoreInterrupts(uVar1);
  return uVar2;
}

