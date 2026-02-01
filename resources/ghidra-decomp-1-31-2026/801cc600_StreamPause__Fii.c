// Function: StreamPause__Fii
// Entry: 801cc600
// Size: 392 bytes

void StreamPause__Fii(int param_1,int param_2)

{
  undefined4 uVar1;
  uint uVar2;
  int iVar3;
  
  uVar2 = DAT_8032f438;
  if (DAT_8032f408 != 0) {
    if (param_2 == 1) {
      OSReport(s__sPause___Stream___ON__d_801e7fb0,&DAT_801e7f44,param_1);
    }
    else {
      OSReport(s__sPause___Stream___OFF__d_801e7fcb,&DAT_801e7f44,param_1);
    }
    fflush(&DAT_8021d1a8);
    uVar2 = DAT_8032f438;
  }
  do {
    if ((*(int *)(uVar2 + 0x10c) != 0) && ((param_1 == -1 || (param_1 == *(int *)(uVar2 + 0x10c)))))
    {
      iVar3 = *(int *)(uVar2 + 4);
      if (param_2 == 1) {
        if (*(int *)(iVar3 + 0x14) != 0) {
          *(undefined4 *)(iVar3 + 0x9c) = 0;
          *(uint *)(iVar3 + 0x90) = *(uint *)(iVar3 + 0x90) | 0x10;
          if (*(short *)(uVar2 + 0x2a) == 2) {
            *(undefined4 *)(iVar3 + 0x15c) = 0;
            *(uint *)(iVar3 + 0x150) = *(uint *)(iVar3 + 0x150) | 0x10;
          }
        }
      }
      else if (*(int *)(iVar3 + 0x14) != 0) {
        uVar1 = PitchCompute__Fiiii(0x3c00000,0,*(undefined4 *)(uVar2 + 0x24),0);
        if (*(short *)(uVar2 + 0x2a) == 2) {
          *(undefined4 *)(iVar3 + 0x9c) = uVar1;
          *(uint *)(iVar3 + 0x90) = *(uint *)(iVar3 + 0x90) | 0x10;
          *(undefined4 *)(iVar3 + 0x15c) = uVar1;
          *(uint *)(iVar3 + 0x150) = *(uint *)(iVar3 + 0x150) | 0x10;
        }
        else {
          *(undefined4 *)(iVar3 + 0x9c) = uVar1;
          *(uint *)(iVar3 + 0x90) = *(uint *)(iVar3 + 0x90) | 0x10;
        }
      }
    }
    uVar2 = uVar2 + 0x130;
  } while (uVar2 < DAT_8032f438 + 0x4c0);
  return;
}

