// Function: PitchCompute__Fiiii
// Entry: 801c2ffc
// Size: 256 bytes

int PitchCompute__Fiiii(int param_1,int param_2,int param_3,uint param_4)

{
  uint uVar1;
  int iVar2;
  uint uVar3;
  
  iVar2 = 0;
  for (uVar3 = (param_1 >> 0xc) + param_2 + (param_3 >> 0x10); (int)uVar3 < 0; uVar3 = uVar3 + 0xc00
      ) {
    iVar2 = iVar2 + -1;
  }
  uVar1 = uVar3 >> 8 & 0x7f;
  iVar2 = (int)((*(uint *)(&DAT_8021d7f0 + (uVar1 % 0xc) * 4) >> 10 - (iVar2 + uVar1 / 0xc)) *
               *(int *)(&DAT_8021d820 + (uVar3 & 0xff) * 4)) >> 0xc;
  if (param_4 != 0) {
    if ((int)param_4 < 1) {
      iVar2 = (int)(iVar2 * (param_4 & 0xff)) >> 8;
    }
    else {
      iVar2 = iVar2 + ((int)(iVar2 * (param_4 + 1)) >> 7);
    }
  }
  return iVar2;
}

