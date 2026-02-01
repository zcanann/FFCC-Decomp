// Function: onCancelStat__10CGCharaObjFi
// Entry: 801129d0
// Size: 332 bytes

void onCancelStat__10CGCharaObjFi(int param_1)

{
  int iVar1;
  int iVar2;
  
  iVar1 = *(int *)(param_1 + 0x520);
  if (iVar1 == 6) {
    iVar2 = 0;
    iVar1 = param_1;
    do {
      if ((1 << iVar2 & 0x138U) != 0) {
        EndParticleSlot__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,*(undefined4 *)(iVar1 + 0x564));
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar2 < 0x16);
    *(undefined4 *)(param_1 + 0x684) = 0xffffffff;
  }
  else if (iVar1 < 6) {
    if (iVar1 == 2) {
      iVar2 = 0;
      iVar1 = param_1;
      do {
        if ((1 << iVar2 & 0x18U) != 0) {
          EndParticleSlot__13CFlatRuntime2Fii
                    ((CFlatRuntime2 *)&CFlat,*(undefined4 *)(iVar1 + 0x564));
        }
        iVar2 = iVar2 + 1;
        iVar1 = iVar1 + 4;
      } while (iVar2 < 0x16);
    }
  }
  else if (iVar1 == 0x12) {
    iVar2 = 0;
    iVar1 = param_1;
    do {
      if ((1 << iVar2 & 1U) != 0) {
        EndParticleSlot__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,*(undefined4 *)(iVar1 + 0x564));
      }
      iVar2 = iVar2 + 1;
      iVar1 = iVar1 + 4;
    } while (iVar2 < 0x16);
  }
  *(undefined4 *)(param_1 + 0x660) = 0;
  *(undefined4 *)(param_1 + 0x668) = 0;
  (**(code **)(*(int *)(param_1 + 0x48) + 0x90))(param_1,0,0,0);
  return;
}

