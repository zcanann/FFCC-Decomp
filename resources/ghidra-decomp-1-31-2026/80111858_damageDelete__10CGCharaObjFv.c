// Function: damageDelete__10CGCharaObjFv
// Entry: 80111858
// Size: 140 bytes

void damageDelete__10CGCharaObjFv(int param_1)

{
  int iVar1;
  
  StopSe3DGroup__6CSoundFi(&Sound,(int)*(short *)(param_1 + 0x30));
  iVar1 = 0;
  do {
    if ((1 << iVar1 & 0x3bU) != 0) {
      DeleteParticleSlot__13CFlatRuntime2Fii
                ((CFlatRuntime2 *)&CFlat,*(undefined4 *)(param_1 + 0x564));
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 4;
  } while (iVar1 < 0x16);
  return;
}

