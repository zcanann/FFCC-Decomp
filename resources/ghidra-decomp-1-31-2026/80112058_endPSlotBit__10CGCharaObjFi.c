// Function: endPSlotBit__10CGCharaObjFi
// Entry: 80112058
// Size: 104 bytes

void endPSlotBit__10CGCharaObjFi(int param_1,uint param_2)

{
  int iVar1;
  
  iVar1 = 0;
  do {
    if ((param_2 & 1 << iVar1) != 0) {
      EndParticleSlot__13CFlatRuntime2Fii((CFlatRuntime2 *)&CFlat,*(undefined4 *)(param_1 + 0x564));
    }
    iVar1 = iVar1 + 1;
    param_1 = param_1 + 4;
  } while (iVar1 < 0x16);
  return;
}

