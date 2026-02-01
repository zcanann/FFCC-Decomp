// Function: SePause__Fii
// Entry: 801caf68
// Size: 312 bytes

void SePause__Fii(int param_1,int param_2)

{
  int *piVar1;
  uint uVar2;
  int iVar3;
  
  if (DAT_8032f408 != 0) {
    if (param_2 == 1) {
      OSReport(s__sPause___SE___ON__d_801e7e50,&DAT_801e7e3e,param_1);
    }
    else {
      OSReport(s__sPause___SE___OFF__d_801e7e6b,&DAT_801e7e3e,param_1);
    }
    fflush(&DAT_8021d1a8);
  }
  piVar1 = (int *)(DAT_8032f3f0 + 0xdbc);
  uVar2 = *(uint *)(DAT_8032f3f0 + 0xdbc);
  iVar3 = DAT_8032f444 + 0x1800;
  do {
    if ((*(int *)(uVar2 + 0xf8) != 0) && ((param_1 == -1 || (param_1 == *(int *)(uVar2 + 0xf8))))) {
      if (param_2 == 1) {
        if (*(int *)(iVar3 + 0x14) != 0) {
          *(undefined4 *)(iVar3 + 0x9c) = 0;
          *(uint *)(iVar3 + 0x90) = *(uint *)(iVar3 + 0x90) | 0x18;
        }
        *(uint *)(uVar2 + 0xfc) = *(uint *)(uVar2 + 0xfc) | 8;
        *(uint *)(iVar3 + 0x94) = *(uint *)(iVar3 + 0x94) | 8;
      }
      else {
        *(uint *)(iVar3 + 0xb8) = *(uint *)(iVar3 + 0xb8) | 3;
        *(uint *)(uVar2 + 0xfc) = *(uint *)(uVar2 + 0xfc) & 0xfffffff7;
        *(uint *)(iVar3 + 0x94) = *(uint *)(iVar3 + 0x94) & 0xfffffff7;
      }
    }
    uVar2 = uVar2 + 0x154;
    iVar3 = iVar3 + 0xc0;
  } while (uVar2 < *piVar1 + 0x2a80U);
  return;
}

